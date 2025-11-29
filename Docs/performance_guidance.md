# FireUi 性能诊断与优化要点

本文结合现有代码配置与平台差异，整理 CPU 占用偏高的常见原因和优化建议，供在 Windows、Linux x86 与 NVIDIA Jetson (AGX Orin) 等平台上排查参考。

## 现象解读：CPU 百分比 ≈ 占用核数
- Windows 任务管理器显示的是“整机百分比”；Linux `top` 则是“占了多少个核 × 100%”。
- 你记录的数据大致都在 **1~2 个逻辑核** 的量级：
  - Windows: OpenGL/YUV 约 0.6 核，解帧模式约 1.6 核。
  - Ubuntu x86: OpenGL 约 0.35 核，解帧模式约 1.6 核。
  - Jetson: OpenGL 约 1.1 核，解帧模式约 1.8 核。
- 差异主要来自 **单核性能**（x86 > Orin）和 **软件/驱动路径**，而不是管线占用核数相差十倍。

## 代码层面的现状
- 默认 OpenGL 渲染参数：界面初始化时使用 `VideoMode_Opengl`，GPU 配置走 `hardware="auto"`，CPU 备用配置走 `hardware="none"` 并启用 `copyImage`，因此一旦硬件路径不可用会退回纯软件链路。【F:Src/FireGUI/Gui/Pages/FuVideoPage.cpp†L66-L90】
- 视频基类默认硬解标志为 `"none"`，OpenGL 模式下 `hardware=="none"` 会走 YUV 渲染路径（CPU 侧准备数据再上传），不是直接 NV12 硬件纹理。【F:Src/ThirdParty/TVideoSystem/VideoBase/abstractvideowidget.cpp†L60-L82】

## 优化建议
1. **确保真正启用硬件解码**
   - 针对不同平台选择匹配的后端，并在运行时/配置中显式启用：
     - x86: VAAPI / QSV（Intel）或 NVDEC（NVIDIA）。
     - Jetson: NVDEC / V4L2。确认 FFmpeg 已启用对应硬件模块。
   - 尝试将默认硬件选项改为具体后端而非 `"none"`，并在失败时记录日志回退，避免静默落回 CPU 解码。

2. **把 YUV→RGB 放到 GPU**
   - 保持解码输出为 YUV420/NV12，直接上传 Y/U/V 平面或 NV12 纹理，片段着色器做颜色变换。
   - 避免在 CPU 做 `sws_scale` + 多重 `memcpy`；对 Jetson 尤其显著。

3. **解码线程与渲染线程解耦，队列有界并丢旧帧**
   - 解码线程专注 `av_read_frame/receive_frame`，渲染线程取“最新帧”绘制。
   - 队列上限 2~3 帧，满时丢弃最旧帧，防止卡顿时延迟无限累积。

4. **启用 FFmpeg 多线程与 Release 优化**
   - `av_dict_set(&opts, "threads", "auto", 0);`；自研代码用 `-O3 -DNDEBUG`，ARM 目标可加 `-march=native`（或更具体的 A78/NEON 选项）。

5. **确认 OpenGL 路径在硬件上运行**
   - 安装/启用专有或 Mesa 驱动，避免落入 llvmpipe 软件栈；在 Jetson 上保持 `jetson_clocks`/MAXN 以稳定频率和带宽。

6. **按需减少 CPU 侧拷贝**
   - 对 CPU 备用路径，可关闭不必要的 `copyImage`，减少像素搬运；在硬件路径可行时优先使用 NV12 直通。

7. **验证路径与效果**
   - 对比 `ffplay` 硬件解码 vs. 软件解码的 CPU 占用；
   - 在应用内记录解码/渲染耗时与当前硬件模式，方便定位回退点。

## 现有实现与优化建议的对应关系

- 已有实现
  - 解复用与解码分线程：默认 `useSync=true` 时，`FFmpegThread` 只做读包入队，真实解码在 `FFmpegSync` 线程中完成，界面线程仅负责 OpenGL 上传。【F:Src/ThirdParty/TFFMpeg/Src/ffmpegthread.cpp†L200-L220】【F:Src/ThirdParty/TFFMpeg/Src/ffmpegsync.cpp†L20-L63】
  - FFmpeg 侧已设置 `threads=auto`，可自动使用多线程解码。【F:Src/ThirdParty/TFFMpeg/Src/ffmpeghelper.cpp†L17-L39】
  - OpenGL 渲染分 YUV/NV12/RGB 三路径，GPU 负责片段着色转换；但硬解回落为 `none` 时仍在 CPU 侧 `sws_scale`/拷贝后上传三平面数据。【F:Src/ThirdParty/TVideoSystem/VideoBase/abstractvideowidget.cpp†L94-L107】【F:Src/ThirdParty/TFFMpeg/Src/ffmpegthread.cpp†L332-L389】
  - 页面默认 GPU 路径用 `hardware="auto"`，但 CPU 备用路径固定 `hardware="none"` 且开启 `copyImage`。【F:Src/FireGUI/Gui/Pages/FuVideoPage.cpp†L69-L89】

- 仍需改进
  - 队列无界：`FFmpegSync::append` 只追加不裁剪，卡顿时包会无限堆积，延迟和 CPU/内存都会上升。需给队列设上限并在满时丢弃旧帧或跳到最新帧。【F:Src/ThirdParty/TFFMpeg/Src/ffmpegsync.cpp†L95-L103】
  - 硬解易退回软件：旋转、录像、滤镜等场景会把 `hardware` 置为 `"none"`，导致 OpenGL 路径变成 CPU 解码 + `sws_scale` + 拷贝。应针对目标平台明确启用 VAAPI/NVDEC/V4L2，并在 UI/配置中可选，记录回退原因。【F:Src/ThirdParty/TFFMpeg/Src/ffmpegthread.cpp†L748-L807】【F:Src/FireGUI/Gui/Pages/FuVideoPage.cpp†L77-L89】
  - CPU 颜色转换/拷贝仍存在：软解或需要缩放时执行 `sws_scale` 生成 YUV420，再上传三平面。若源已是 NV12/YUV420，可直接上传 NV12 或采用零拷贝映射减少转换。【F:Src/ThirdParty/TFFMpeg/Src/ffmpegthread.cpp†L332-L356】【F:Src/ThirdParty/TFFMpeg/Src/ffmpegthread.cpp†L377-L389】
  - 延迟控制不足：`checkRun` 只按 100×倍速限制队列，不主动丢帧；解码卡顿会造成延迟滚大。需要在解码线程侧也实现“取最新帧”或收紧最大缓存。【F:Src/ThirdParty/TFFMpeg/Src/ffmpegthread.cpp†L186-L219】

## 小结
- 目前管线在所有平台都消耗约 1~2 核，单核性能差异导致表观 CPU% 不同。
- 关键是 **启用硬件解码 + GPU 颜色转换 + 有界队列**，再辅以编译优化和正确的 OpenGL 驱动，可显著降低 Jetson 上的卡顿和 CPU 占用。

# Video thread flow overview

This document summarizes which threads handle demuxing, decoding, color conversion, and rendering in the current player pipeline.

## Threads involved
- **FFmpegThread (inherits `VideoThread`)** runs as a `QThread`.
- **FFmpegSync threads** (`audioSync` and `videoSync`) are optional `QThread`s created by `FFmpegThread` when `useSync` is enabled (default).
- **UI thread** hosts `VideoWidget`/`AbstractVideoWidget` slots that update OpenGL widgets when frame signals arrive.

## Default (`useSync = true`)
1. **Demux**: `FFmpegThread::run()` reads packets via `av_read_frame` and pushes video packets into `videoSync` and audio packets into `audioSync`.
2. **Decode + filters + colorspace/resize + copy**: `FFmpegSync::run()` dequeues packets and calls `FFmpegThread::decodeVideo1()`/`decodeAudio1()`; the video path runs `decodeVideo2()`, which applies filters, `sws_scale` to YUV420 when needed, and emits `receiveFrame` with the resulting planes.
3. **OpenGL update**: `VideoWidget` connects to `receiveFrame` and forwards data to the OpenGL widgets (`RgbWidget`/`YuvWidget`/`Nv12Widget`) on the UI thread.

## When `useSync` is disabled
- `FFmpegThread::decodeVideo0()` directly calls `decodeVideo1()`/`decodeVideo2()` in the same thread, so demuxing, decoding, conversion, and signal emission all happen inside `FFmpegThread`.

## Notes
- OpenGL uploads run where the widget slots execute (UI thread for cross-thread signals).
- Color conversion and extra copies happen in `decodeVideo2()` before emitting `receiveFrame`.

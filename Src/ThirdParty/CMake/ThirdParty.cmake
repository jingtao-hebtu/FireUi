# *  @Copyright (c) tao.jing
# *
# *

IF (NOT THIRD_PARTY_PATH)
    set(THIRD_PARTY_PATH ${CMAKE_CURRENT_SOURCE_DIR})
ELSE ()
    set(THIRD_PARTY_PATH ${THIRD_PARTY_PATH})
ENDIF ()


set(QT_LIB_PATH ${THIRD_PARTY_PATH}/Qt)
set(T_FFMPEG_DIR ${THIRD_PARTY_PATH}/TFFMpeg)
set(T_VIDEO_SYSTEM_DIR ${THIRD_PARTY_PATH}/TVideoSystem)


include(${QT_LIB_PATH}/CMake/Qt.cmake)
include(${T_FFMPEG_DIR}/CMake/TFFMpeg.cmake)
include(${T_VIDEO_SYSTEM_DIR}/CMake/TVideoSystem.cmake)

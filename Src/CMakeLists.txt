# *  @Copyright (c) tao.jing
# *
# *
cmake_minimum_required(VERSION 3.26)
project(FireUi)

# ---- Project Paths ----
IF (NOT FU_DIR)
    set (FU_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)
ELSE()
    set (FU_DIR ${FU_DIR})
ENDIF()

set (FU_SRC_DIR ${FU_DIR}/FireUi)
set (THIRD_PARTY_PATH ${FU_DIR}/ThirdParty/)


set (FIRE_GUI_SRC_DIR ${FU_DIR}/FireGUI)
add_subdirectory(FireGUI)

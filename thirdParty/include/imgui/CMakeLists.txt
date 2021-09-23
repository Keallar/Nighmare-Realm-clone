set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(imgui SHARED
    imgui.h
    imconfig.h
    imgui_internal.h
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
    imgui.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui-SFML.cpp
    imconfig-SFML.h
    imgui-SFML.h
    imgui-SFML_export.h
)

target_include_directories(
    imgui
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)


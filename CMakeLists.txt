cmake_minimum_required(VERSION 3.16)

project(rework_osm_step14 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

find_package(cppzmq CONFIG REQUIRED)
find_package(nlohmann_json CONFIG QUIET)
find_package(PostgreSQL REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(CURL QUIET)
find_package(Threads REQUIRED)

add_library(tp_imgui STATIC
    ${THIRD_PARTY_DIR}/imgui/imgui.cpp
    ${THIRD_PARTY_DIR}/imgui/imgui_draw.cpp
    ${THIRD_PARTY_DIR}/imgui/imgui_tables.cpp
    ${THIRD_PARTY_DIR}/imgui/imgui_widgets.cpp
    ${THIRD_PARTY_DIR}/imgui/backends/imgui_impl_sdl2.cpp
    ${THIRD_PARTY_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(tp_imgui PUBLIC
    ${THIRD_PARTY_DIR}/imgui
    ${THIRD_PARTY_DIR}/imgui/backends
)

target_link_libraries(tp_imgui PUBLIC
    SDL2::SDL2
    GLEW::GLEW
    OpenGL::GL
)

add_library(tp_implot STATIC
    ${THIRD_PARTY_DIR}/implot/implot.cpp
    ${THIRD_PARTY_DIR}/implot/implot_items.cpp
)

target_include_directories(tp_implot PUBLIC
    ${THIRD_PARTY_DIR}/implot
    ${THIRD_PARTY_DIR}/imgui
)

target_link_libraries(tp_implot PUBLIC
    tp_imgui
)

add_executable(rework_app

    src/main.cpp

    src/gui_app.cpp
    src/gui_tabs.cpp

    src/net/zmq_receiver.cpp

    src/core/json_parser.cpp

    src/db/pgsql_minimal.cpp

    src/network/osm_tile_fetcher.cpp
    src/network/osm_tile_texture.cpp

    src/ui/menu_bar.cpp
    src/ui/data_window.cpp
    src/ui/graph_window.cpp
    src/ui/map_window.cpp
    src/ui/ui_widget.cpp

    src/logging.cpp
    src/core/heatmap_generator.cpp
)

target_include_directories(rework_app PRIVATE
    include
    ${THIRD_PARTY_DIR}/imgui
    ${THIRD_PARTY_DIR}/implot
)

target_link_libraries(rework_app PRIVATE
    cppzmq
    PostgreSQL::PostgreSQL
    tp_imgui
    tp_implot
    Threads::Threads
)

if(CURL_FOUND)
    target_link_libraries(rework_app PRIVATE
        CURL::libcurl
    )
endif()

if(nlohmann_json_FOUND)
    target_link_libraries(rework_app PRIVATE
        nlohmann_json::nlohmann_json
    )
endif()
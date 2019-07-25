cmake_minimum_required(VERSION 3.9)
PROJECT(douml)
set(ALL_PORTS
    Windows
    Linux
)
set(PORT "Windows")
list(FIND ALL_PORTS ${PORT} RET)
if(${RET} EQUAL -1)
	message(FATAL_ERROR "please choose port")
endif()
# --------------
# Determine the compiler
# --------------
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	set(COMPILER_IS_MSVC ON)
endif()
message(${CMAKE_CXX_COMPILER_ID})
# ---------------------
# default library type
# ---------------------
option(SHARED_CORE "build as a shared libray")
set(CMAKE_POSITION_INDEPENDENT_CODE True)
# ----------
# Determine the directory
# ----------
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
message(${CMAKE_BINARY_DIR})
# -----
# Common conf
# -----

# -----
# Common files
# -----
set(srcs_common
    src/id.cpp
    src/point.cpp
    src/line.cpp
    src/rect.cpp
    src/color.cpp
    src/shape.cpp
    src/square.cpp
    src/viewlayer.cpp
    src/nodeview.cpp
    src/node.cpp
    src/render.cpp
    src/arrowhead.cpp
    src/trianglearrowhead.cpp
    src/diamondarrowhead.cpp
    src/edge.cpp
    src/graph.cpp
    src/direction.cpp
    src/bentstyle.cpp
#    src/duwindow.cpp
    src/toolitem.cpp
    src/linestyle.cpp
    src/ui/workspace.cpp
    src/ui/editorpart.cpp
    src/ui/sidebar.cpp
)
set(srcs_class_diagram
    src/classdiagram/classgraph.cpp
    src/classdiagram/notenode.cpp
    src/classdiagram/classnode.cpp
    src/classdiagram/interfacenode.cpp
    src/classdiagram/packagenode.cpp
    src/classdiagram/dependedge.cpp
    src/classdiagram/inheritedge.cpp
    src/classdiagram/implementedge.cpp
    src/classdiagram/associateedge.cpp
    src/classdiagram/aggregateedge.cpp
    src/classdiagram/composeedge.cpp
)
set(src_object_diagram
    src/objectdiagram/objectnode.cpp
    src/objectdiagram/objectgraph.cpp
)

# -----
# platform related
# -----
if("${PORT}" STREQUAL "Windows")
set(srcs
    ${srcs_common}
    ${srcs_class_diagram}
    ${srcs_object_diagram}
	src/uuid_win.cpp
    src/cairorender_win.cpp
    src/charconverter_win.cpp
)
else()
set(srcs
    ${srcs_common}
)
endif()

include_directories(
    "include"
    "D:\\source\\cairo\\Cairo-VS\\projects\\cairo\\src"
    "D:\\source\\cairo\\Cairo-VS\\cairo\\src"
    "C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\atlmfc\\include"
)
LINK_DIRECTORIES(
    "libs"
    "C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\atlmfc\\lib"
)

#
# douml_core for dll can cause memry leak wrong report so use static libray for now
#add_library(douml_core SHARED ${srcs})

add_library(douml_core ${srcs})
target_link_libraries(douml_core cairo pixman libpngd zlibd freetype)

#
# cairo_public for using cairo dll 
# _AFXDLL for using mfc dll
# DU_STATIC for douml_core static library
#target_compile_definitions(douml_core PRIVATE DU_EXPORT cairo_public _AFXDLL)
target_compile_definitions(douml_core PRIVATE DU_STATIC cairo_public _AFXDLL UNICODE _UNICODE)



# console tests
add_executable(test_id tests/test_id.cpp)
#target_compile_definitions(test_id PRIVATE _AFXDLL)
target_compile_definitions(test_id PRIVATE DU_STATIC _AFXDLL)
target_link_libraries(test_id douml_core)

add_executable(test_node tests/test_node.cpp)
target_link_libraries(test_node douml_core)

# windows tests
if("${PORT}" STREQUAL "Windows")
# nodeview
add_executable(test_node_view WIN32 tests/test_node_view.cpp)
target_compile_definitions(test_node_view PRIVATE DU_STATIC _AFXDLL)
target_link_libraries(test_node_view douml_core cairo)
# arrowhead
add_executable(test_arrowhead WIN32 tests/test_arrowhead.cpp)
target_compile_definitions(test_arrowhead PRIVATE DU_STATIC _AFXDLL)
target_link_libraries(test_arrowhead douml_core)

# graph
add_executable(test_graph WIN32 tests/test_graph.cpp)
target_compile_definitions(test_graph PRIVATE DU_STATIC _AFXDLL)
target_link_libraries(test_graph douml_core)

# classnode
add_executable(test_class_node WIN32 tests/test_class_node.cpp)
target_compile_definitions(test_class_node PRIVATE DU_STATIC _AFXDLL)
target_link_libraries(test_class_node douml_core)

# duwindow
add_executable(test_duwindow WIN32 tests/test_duwindow.cpp)
target_compile_definitions(test_duwindow PRIVATE DU_STATIC _AFXDLL UNICODE _UNICODE)
target_link_libraries(test_duwindow douml_core)

# udmenu
add_executable(test_udmenu WIN32 tests/test_udmenu.cpp)
target_compile_definitions(test_udmenu PRIVATE DU_STATIC _AFXDLL UNICODE _UNICODE)
target_link_libraries(test_udmenu douml_core)

endif()


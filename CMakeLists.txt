cmake_minimum_required(VERSION 3.20)

project(NVT VERSION 0.1 LANGUAGES CXX)

include("C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

if (ANDROID OR IOS)
    message(FATAL_ERROR "Platform not supported")
    return()
endif()

qt_add_executable(appNVT
    NVT/main.cpp
    NVT/application.hpp
    NVT/application.cpp
)

set_source_files_properties(NVT/qml/Colors.qml
    PROPERTIES
        QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(appNVT
    URI NVTModule
    QML_FILES
        "NVT/Main.qml"
        "NVT/qml/LoadPage.ui.qml"
        "NVT/qml/MetroButton.qml"
        "NVT/qml/MetroContextMenu.qml"
        "NVT/qml/MetroMenuBar.qml"
        "NVT/qml/StationLabel.qml"
        "NVT/qml/Station.qml"
        "NVT/qml/Colors.qml"
        "NVT/qml/InternalWindow.qml"
    RESOURCES
        "res/svg/blue_arrow.svg"
        "res/svg/lavender_arrow.svg"
        "res/svg/yellow_arrow.svg"
        "res/johnston-itc/johnston-itc-std-bold.otf"
        "res/johnston-itc/johnston-itc-std-medium.otf"
    SOURCES
        "NVT/application.hpp"
        QML_FILES NVT/qml/BetterButton.qml
)

add_subdirectory(NVT/timeline)
add_subdirectory(NVT/project)
add_subdirectory(NVT/launch)

set_property(TARGET appNVT PROPERTY CXX_STANDARD 23)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appNVT PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appNVT
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appNVT PRIVATE NVT/project)
# 
# target_include_directories(timelinelib PRIVATE NVT/project)
# target_link_libraries(timelinelib PRIVATE projectlib)

target_link_libraries(appNVT
    PRIVATE Qt6::Quick timelinelib projectlib launchlib
)

install(TARGETS appNVT
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

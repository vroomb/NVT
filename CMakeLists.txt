cmake_minimum_required(VERSION 3.20)

project(NVT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

# set(CMAKE_AUTORCC ON)

if (ANDROID OR IOS)
    message(FATAL_ERROR "Platform not supported")
    return()
endif()

qt_add_executable(appNVT
    main.cpp
)

set_source_files_properties(qml/Colors.qml
    PROPERTIES
        QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(appNVT
    URI NVTModule
    QML_FILES
        "Main.qml"
        "qml/LoadPage.ui.qml"
        "qml/MetroButton.qml"
        "qml/MetroContextMenu.qml"
        "qml/MetroMenuBar.qml"
        "qml/StationLabel.qml"
        "qml/Timeline.qml"
        "qml/Station.qml"
        "qml/Launch.qml"
        "qml/Colors.qml"
        "qml/Node.qml"
        "qml/InternalWindow.qml"
        "qml/Chain.qml"
        "qml/Pin.qml"
        # "qml/TilingTexture.qml"
    RESOURCES
        "res/svg/blue_arrow.svg"
        "res/svg/lavender_arrow.svg"
        "res/svg/yellow_arrow.svg"
        "res/johnston-itc/johnston-itc-std-bold.otf"
        "res/johnston-itc/johnston-itc-std-medium.otf"
    SOURCES
        application.hpp
        launch.hpp
        launch.cpp
        timeline.hpp
        timeline.cpp
        timeline_chain.hpp
        timeline_chain.cpp
        # repeating_texture.hpp
        # repeating_texture.cpp
)

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

target_link_libraries(appNVT
    PRIVATE Qt6::Quick
)

install(TARGETS appNVT
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

cmake_minimum_required(VERSION 3.20)

project(NVTtimeline VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_qml_module(timeline
    URI NVT.timeline
    QML_FILES
        "qml/Chain.qml"
        "qml/Node.qml"
        "qml/Pin.qml"
        "qml/Timeline.qml"
    SOURCES
        ../../application.hpp
        timeline_pin.hpp
        timeline_pin.cpp
        timeline_chain.hpp
        timeline_chain.cpp
        timeline_node.hpp
        timeline_node.cpp
        timeline.hpp
        timeline.cpp
)
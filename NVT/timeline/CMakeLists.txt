qt_add_library(timelinelib STATIC)

set_target_properties(timelinelib PROPERTIES AUTOMOC ON)
target_link_libraries(timelinelib PRIVATE Qt6::Quick)

qt_add_qml_module(timelinelib
    URI NVT.Timeline
    QML_FILES
        "qml/Chain.qml"
        "qml/Node.qml"
        "qml/Pin.qml"
        "qml/Timeline.qml"
    SOURCES
        application.hpp
        timeline_pin.hpp
        timeline_pin.cpp
        timeline_chain.hpp
        timeline_chain.cpp
        timeline_node.hpp
        timeline_node.cpp
        timeline.hpp
        timeline.cpp
)
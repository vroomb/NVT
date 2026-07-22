include("C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/buildsystems/vcpkg.cmake")

qt_add_library(launchlib
)

find_package(nlohmann_json CONFIG REQUIRED)

set_target_properties(launchlib
    PROPERTIES
        AUTOMOC ON
        CXX_STANDARD 23
)

target_include_directories(launchlib PUBLIC .)
target_link_libraries(launchlib
    PRIVATE Qt6::Quick
    PUBLIC nlohmann_json::nlohmann_json
)

qt_add_qml_module(launchlib
    URI NVT.Launch
    QML_FILES
        qml/LaunchWindow.qml
        qml/Launch.qml
    RESOURCES
        "../../res/svg/blue_arrow.svg"
        "../../res/svg/lavender_arrow.svg"
        "../../res/svg/yellow_arrow.svg"
        "../../res/johnston-itc/johnston-itc-std-bold.otf"
        "../../res/johnston-itc/johnston-itc-std-medium.otf"
    SOURCES
        launch.hpp
        launch_handle.hpp
        launch_handle.cpp
        launch_list.hpp
        launch_list.cpp
)

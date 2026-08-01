qt_add_executable(appNVT
    nvt.hpp
    main.cpp
    application.hpp
    application.cpp
)

set_source_files_properties(qml/Colors.qml
    PROPERTIES
        QT_QML_SINGLETON_TYPE TRUE
)

set_target_properties(appNVT PROPERTIES
    AUTOMOC ON
    CXX_STANDARD 23
)


qt_add_qml_module(appNVT
    URI NVTModule
    QML_FILES
        "qml/Main.qml"
        "qml/LoadPage.ui.qml"
        "qml/MetroButton.qml"
        "qml/MetroContextMenu.qml"
        "qml/MetroMenuBar.qml"
        "qml/StationLabel.qml"
        "qml/Station.qml"
        "qml/Colors.qml"
        "qml/InternalWindow.qml"
        "qml/BetterButton.qml"
    RESOURCES
        "../res/svg/blue_arrow.svg"
        "../res/svg/lavender_arrow.svg"
        "../res/svg/yellow_arrow.svg"
        "../res/johnston-itc/johnston-itc-std-bold.otf"
        "../res/johnston-itc/johnston-itc-std-medium.otf"
    SOURCES
        main_window.hpp
        main_window.cpp
)

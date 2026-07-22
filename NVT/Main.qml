import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import NVTModule
import NVT.Timeline
import NVT.Launch

ApplicationWindow {
    id: root
    visible: true
    visibility: Window.Maximized

    FontLoader {
        id: johnston_medium
        source: "../res/johnston-itc/johnston-itc-std-medium.otf"
    }
    FontLoader {
        id: johnston_bold
        source: "../res/johnston-itc/johnston-itc-std-bold.otf"
    }

    font.family: "Johnston ITC Std"
    font.pixelSize: 25

    width: 960
    height: 540

    background: Rectangle {
        color: "#111"
    }

    menuBar: MetroMenuBar {
        id: metroMenuBar
        height: 0
        clip: true

        onActiveFocusChanged: {
            if (focus === true) {
                metroMenuBar.height = 40;
            }
        }

        Behavior on height {
            NumberAnimation { duration: 200 }
        }

        Menu {
            title: "File"
            Action {
                text: "Launch"
                onTriggered: launchWindow.visible = true
            }
        }
    }

    Item {
        id: keyEventManager
        focus: true
        // Keys.onPressed: (event) => {
        //     if (event.key === Qt.Key_Alt) {
        //         metroMenuBar.height = 30;
        //     }
        //     else if (event.key === Qt.Key_Escape) {
        //         metroMenuBar.height = 0;
        //     }
        //     else {
        //         contentFrame.keysOnPressed(event);
        //     }
        // }
        // Keys.onReleased: (event) => {
        //     contentFrame.keysOnReleased(event);
        // }
    }

    Timeline {
        id: contentFrame
        anchors.fill: parent

        onFocused: {
            metroMenuBar.height = 0;
        }
    }

    LaunchWindow {
        id: launchWindow
        visible: false
    }
}

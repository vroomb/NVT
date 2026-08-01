import QtQuick
import QtQuick.Controls.Basic
import NVTModule
import NVT.Launch

NVTLaunchWindow {
    id: root
    // flags: Qt.FramelessWindowHint
    visible: true
    color: "transparent"

    width: 1280
    height: 720

    FontLoader {
        id: johnston_medium
        source: "../res/johnston-itc/johnston-itc-std-medium.otf"
    }
    FontLoader {
        id: johnston_bold
        source: "../res/johnston-itc/johnston-itc-std-bold.otf"
    }

    Launch {
        id: launch
        anchors.fill: parent

        Rectangle {
            color: "transparent"
            radius: launch.radius
            border.width: 0
            border.color: "#222"
            anchors.fill: parent
        }

        onLaunchRequested: location => root.launchRequested(location);
    }

    DragHandler {
        target: null
        onActiveChanged: {
            if (active) root.startSystemMove()
        }
    }
}

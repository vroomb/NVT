import QtQuick
import QtQuick.Controls.Basic
import NVTModule
import NVT.Launch

ApplicationWindow {
    id: root
    visible: true
    flags: Qt.FramelessWindowHint
    color: "transparent"

    width: 960
    height: 540

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

        BetterButton {
            id: min

            font.family: "FiraMono Nerd Font"

            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.right: close.left
            width: 50
            height: 30

            bgcolor: "#222"
            topRightRadius: 0

            text: "—"
            onClicked: root.visibility = Window.Minimized
        }

        BetterButton {
            id: close

            font.family: "FiraMono Nerd Font"

            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 5
            width: 50
            height: 30

            bgcolor: "red"
            topRightRadius: 10

            text: "⛌"
            onClicked: root.visible = false
        }

        Rectangle {
            color: "transparent"
            radius: 15
            border.width: 5
            border.color: "#222"
            anchors.fill: parent
        }
    }

    DragHandler {
        target: null
        onActiveChanged: {
            if (active) root.startSystemMove()
        }
    }
}

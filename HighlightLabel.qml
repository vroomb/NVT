import QtQuick
import QtQuick.Controls.Basic

Control {
    id: root

    property string text: ""

    property color bgcolor: "transparent"
    property color txcolor: "black"

    property color hbcolor: "blue"
    property color htcolor: "white"

    property int xinset: 5
    property int yinset: 0

    function onClicked(): void {}

    Control {
        id: control
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        width: textBlack.contentWidth + 2*root.xinset
        height: textBlack.contentHeight + 2*root.yinset
        Rectangle {
            color: root.bgcolor
            anchors.fill: parent
            Label {
                x: root.xinset
                y: root.yinset
                id: textBlack
                text: root.text
                color: root.txcolor
                font: root.font
            }
        }

        Rectangle {
            id: highlight
            z: 1
            width: 0
            height: control.height
            color: root.hbcolor
            clip: true

            Label {
                x: root.xinset
                y: root.yinset
                id: textWhite
                text: root.text
                color: root.htcolor
                height: control.height
                width: control.width
                font: root.font
            }

            Behavior on width {
                NumberAnimation {
                    duration: 200
                    easing.type: Easing.InOutQuad
                }
            }
        }

        MouseArea {
            z: 10
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.LeftButton
            onClicked: {
                root.onClicked();
            }

            onEntered: {
                highlight.width = control.width
            }
            onExited: {
                highlight.width = 0
            }
        }
    }
}

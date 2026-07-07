import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import NVTModule

Control {
    id: root

    property string text: "Judgement Day"
    property string desc: "All of the floating islands start losing their ability to float"
    property color bgcolor: "transparent"
    property color txcolor: Colors.pri
    property color hbcolor: Colors.pri
    property color htcolor: Colors.bse
    property int xinset: 5
    property int yinset: 0
    property bool buttonActiveFocusOnTab: false

    property color stationOutlineColor: Colors.pri
    property color stationInsideColor: Colors.bse
    property color lineColorStart: "transparent"
    property color lineColorEnd: "transparent"
    property int lineWidth: 10
    property int circleDia: 40

    padding: 20

    state: "passive"

    contentItem: Item {
        id: content
        property real iw: stationCircle.width + textEdit.anchors.leftMargin + stationCircle.anchors.rightMargin + textEdit.width
        property real ih: stationCircle.height + stationCircle.anchors.bottomMargin + textEdit.anchors.topMargin + textEdit.height

        clip: true

        Behavior on implicitHeight {
            PropertyAnimation {
                duration: 200
                easing: Easing.InOutQuad
            }
        }

        Behavior on implicitWidth {
            PropertyAnimation {
                duration: 200
                easing: Easing.InOutQuad
            }
        }

        Rectangle {
            id: stationCircle
            width: root.circleDia
            height: root.circleDia
            z: 1
            color: root.stationInsideColor
            radius: root.circleDia / 2
            border.width: 5
            border.color: root.stationOutlineColor
            anchors.margins: 5
        }

        TextEdit {
            id: textEdit
            anchors.left: stationCircle.right
            anchors.margins: 5
            anchors.leftMargin: 15

            font: root.font
            text: root.text
            color: root.txcolor
        }

        Rectangle {
            id: div
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 20
            color: "grey"
            height: 1
        }

        TextArea {
            id: details
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: div.bottom
            text: root.desc
            placeholderText: "Details for the event."
            anchors.margins: 10
            wrapMode: TextEdit.Wrap
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        //propagateComposedEvents: true
        //z: -1
        onEntered: {
            root.state = "hovered"
            timer.start()
            mouse.accepted = false
        }
        onExited: {
            root.state = "passive"
            mouse.accepted = false
        }
        Timer {
            id: timer
            interval: 800
            repeat: false
            onTriggered: {
                if (mouseArea.containsMouse === true) {
                    root.state = "expanded"
                }
            }
        }
    }

    background: Rectangle {
        color: Colors.bse
        opacity: 0
        border.color: "grey"
        border.width: 1
        radius: 10
        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }
    }

    states: [
        State {
            name: "passive"
            PropertyChanges {
                root.background.opacity: 0
            }
            AnchorChanges {
                target: textEdit
                anchors.top: stationCircle.bottom
            }
            AnchorChanges {
                target: div
                anchors.top: textEdit.bottom
            }
            PropertyChanges {
                content.implicitWidth: content.iw
            }
            PropertyChanges {
                content.implicitHeight: content.ih
            }
        },
        State {
            name: "hovered"
            PropertyChanges {
                root.background.opacity: 1
            }
            AnchorChanges {
                target: textEdit
                anchors.top: stationCircle.bottom
            }
            AnchorChanges {
                target: div
                anchors.top: textEdit.bottom
            }
            PropertyChanges {
                content.implicitWidth: content.iw
            }
            PropertyChanges {
                content.implicitHeight: content.ih
            }
        },
        State {
            name: "expanded"
            PropertyChanges {
                root.background.opacity: 1
            }
            AnchorChanges {
                target: textEdit
                anchors.verticalCenter: stationCircle.verticalCenter
            }
            AnchorChanges {
                target: div
                anchors.top: stationCircle.bottom
            }
            PropertyChanges {
                content.implicitWidth: 500
            }
            PropertyChanges {
                content.implicitHeight: 500
            }
        }
    ]
    transitions: [
        Transition {
            from: "hovered"
            to: "expanded"
            AnchorAnimation {
                duration: 200
            }
        }
    ]
}
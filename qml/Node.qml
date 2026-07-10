import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import NVTModule

TimelineNode {
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
    property font font

    state: "passive"

    objectName: "Node"

    Control {
        id: control

        padding: 20
        font: root.font

        x: -(padding + (circleDia / 2))
        y: -(padding + (circleDia / 2))

        contentItem: MouseArea {
            id: content

            clip: true
            drag.target: root
            hoverEnabled: true
            propagateComposedEvents: true
            acceptedButtons: Qt.LeftButton

            property real iw: stationCircle.width + title.anchors.leftMargin + stationCircle.anchors.rightMargin + title.width
            property real ih: stationCircle.height + stationCircle.anchors.bottomMargin + title.anchors.topMargin + title.height

            onEntered: {
                root.state = "hovered"
            }

            onExited: {
                root.state = "passive"
            }

            onDoubleClicked: {
                root.state = "expanded"
            }

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

            TextArea {
                id: title
                anchors.left: stationCircle.right
                anchors.margins: 5

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
                anchors.top: div.bottom
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                text: root.desc
                placeholderText: "Details for the event."
                anchors.margins: 10
                wrapMode: TextEdit.Wrap
            }
        }

        background: Rectangle {
            id: background
            color: Colors.bse
            opacity: 0
            border.color: "grey"
            border.width: 1
            radius: 10
            Behavior on opacity {
                NumberAnimation { duration: 200 }
            }
        }
    }

    states: [
        State {
            name: "passive"
            AnchorChanges {
                target: title
                anchors.top: stationCircle.bottom
            }
            AnchorChanges {
                target: div
                anchors.top: title.bottom
            }
            PropertyChanges {
                background.opacity: 0
                content.implicitWidth: content.iw
                content.implicitHeight: content.ih
                div.opacity: 0
                details.opacity: 0
            }
        },

        State {
            name: "hovered"
            AnchorChanges {
                target: title
                anchors.top: stationCircle.bottom
            }
            AnchorChanges {
                target: div
                anchors.top: title.bottom
            }
            PropertyChanges {
                background.opacity: 1
                content.implicitWidth: content.iw
                content.implicitHeight: content.ih
                div.opacity: 0
                details.opacity: 0
            }
        },

        State {
            name: "expanded"
            AnchorChanges {
                target: title
                anchors.verticalCenter: stationCircle.verticalCenter
            }
            AnchorChanges {
                target: div
                anchors.top: stationCircle.bottom
            }
            PropertyChanges {
                background.opacity: 1
                content.implicitWidth: 500
                content.implicitHeight: 500
                div.opacity: 1
                details.opacity: 1
            }
        }
    ]

    transitions: [
        Transition {
            from: "hovered"
            to: "expanded"
            SequentialAnimation {
                AnchorAnimation {
                    duration: 200
                }
                NumberAnimation {
                    targets: [div, details]
                    property: "opacity"
                    duration: 200
                    easing.type: Easing.InOutQuad
                }
            }
        },
        Transition {
            from: "expanded"
            to: "passive"
            SequentialAnimation {
                NumberAnimation {
                    targets: [div, details]
                    property: "opacity"
                    duration: 200
                    easing.type: Easing.InOutQuad
                }
                AnchorAnimation {
                    duration: 200
                }
            }
        }
    ]
}
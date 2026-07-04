import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import NVTModule

Control {
    id: root

    property string text: "hey"
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

    padding: 10

    state: "passive"

    contentItem: GridLayout {
        rows: 2
        columns: 2
        Rectangle {
            Layout.row: 0
            Layout.column: 0
            id: stationCircle
            width: root.circleDia
            height: root.circleDia
            z: 1
            color: root.stationInsideColor
            radius: root.circleDia / 2
            border.width: 5
            border.color: root.stationOutlineColor
        }

        TextEdit {
            id: textEdit

            Layout.row: 1
            Layout.column: 1
            // anchors.top: stationCircle.bottom
            // anchors.left: stationCircle.right

            font: root.font
            text: "Liverpool street"
            color: root.txcolor

            // Behavior on Layout.row {
            //     PropertyAnimation {
            //         target: textEdit
            //         properties: "y"
            //         duration: 200
            //     }
            // }
            Behavior on y {
                PropertyAnimation {
                    duration: 200
                }
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            root.state = "hovered"
            timer.start()
        }
        onExited: {
            root.state = "passive"
        }
        Timer {
            id: timer
            interval: 400
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
            PropertyChanges {
                textEdit.Layout.row: 1
            }
        },
        State {
            name: "hovered"
            PropertyChanges {
                root.background.opacity: 1
            }
        },
        State {
            name: "expanded"
            PropertyChanges {
                root.background.opacity: 1
            }
            PropertyChanges {
                textEdit.Layout.row: 0
            }
        }
    ]
}
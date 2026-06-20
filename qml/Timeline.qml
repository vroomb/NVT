import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtQuick.Shapes
import NVTModule

Control {
    id: root

    property color bcolor: "#1f1f1f"
    property color pcolor: "#ceb9d9"
    property color scolor: "#8fd8da"
    property color tcolor: "#d6da8f"

    background: Rectangle {
        color: bcolor
    }

    function round(a, b): real {
        a = a + b/2;
        return (a - (a % b));
    }

    ContextMenu.menu: MetroContextMenu {
        Action {
            text: "Add an event"
        }
    }

    property int up_mov: 0
    property int left_mov: 0
    property int down_mov: 0
    property int right_mov: 0

    property int speed: 20

    Timer {
        id: timer
        interval: 16
        running: true
        repeat: true
        onTriggered: {
            item.x += speed * (left_mov - right_mov)
            item.y += speed * (up_mov - down_mov)
        }
    }

    Keys.onPressed: (event) => {
        if (event.isAutoRepeat === false) {
            print("pressed: " + up_mov + " " + left_mov + " " + down_mov + " " + right_mov)

            if (event.key === Qt.Key_W || event.key === Qt.Key_Up)
                up_mov = 1
            if (event.key === Qt.Key_A || event.key === Qt.Key_Left)
                left_mov = 1
            if (event.key === Qt.Key_S || event.key === Qt.Key_Down)
                down_mov = 1
            if (event.key === Qt.Key_D || event.key === Qt.Key_Right)
                right_mov = 1
        }
    }

    Keys.onReleased: (event) => {
        if (event.isAutoRepeat === false) {
            print("released: " + up_mov + " " + left_mov + " " + down_mov + " " + right_mov)

            if (event.key === Qt.Key_W || event.key === Qt.Key_Up)
                up_mov = 0
            if (event.key === Qt.Key_A || event.key === Qt.Key_Left)
                left_mov = 0
            if (event.key === Qt.Key_S || event.key === Qt.Key_Down)
                down_mov = 0
            if (event.key === Qt.Key_D || event.key === Qt.Key_Right)
                right_mov = 0
        }
    }

    TimelineGraph {
        id: item

        Behavior on x {
            NumberAnimation { duration: 16 }
        }

        Behavior on y {
            NumberAnimation { duration: 16 }
        }

        Shape {
            anchors.fill: parent
            ShapePath {
                id: path
                strokeColor: "white"
                strokeWidth: 16
                fillColor: "transparent"

                startX: 300
                startY: 300

                PathLine {
                    id: path1
                    x: 100; y: 100
                }
                PathLine {
                    id: path2
                    x: 100; y: 200
                }
            }

            Rectangle {
                color: "red"
                height: 50
                width: 50
                x: path.startX
                y: path.startY
                onXChanged: {
                    path.startX = x;
                }
                onYChanged: {
                    path.startY = y;
                }
                MouseArea {
                    anchors.fill: parent
                    drag.target: parent
                }
            }

            Rectangle {
                color: "green"
                height: 50
                width: 50
                x: path1.x
                y: path1.y
                onXChanged: {
                    path1.x = x;
                }
                onYChanged: {
                    path1.y = y;
                }
                MouseArea {
                    anchors.fill: parent
                    drag.target: parent
                }
            }

            Rectangle {
                color: "blue"
                height: 50
                width: 50
                x: path2.x
                y: path2.y
                onXChanged: {
                    path2.x = x;
                }
                onYChanged: {
                    path2.y = y;
                }
                MouseArea {
                    anchors.fill: parent
                    drag.target: parent
                }
            }
        }
    }


    MouseArea {
        z: -1
        anchors.fill: parent
        drag.target: item
    }
}
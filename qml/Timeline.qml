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

    ContextMenu.menu: contextMenu

    MetroContextMenu {
        id: contextMenu
        Action {
            text: "Add an event"
            onTriggered: print("heh")
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
            timelineGraph.x += root.speed * (root.left_mov - root.right_mov)
            timelineGraph.y += root.speed * (root.up_mov - root.down_mov)
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
        id: timelineGraph

        property list<point> verts: [
            Qt.point(300, 300),
            Qt.point(300, 300),
            Qt.point(300, 300),
            Qt.point(300, 300),
        ]

        Behavior on x {
            NumberAnimation { duration: 16 }
        }

        Behavior on y {
            NumberAnimation { duration: 16 }
        }

        Item {
            objectName: "vertex1"
            x: timelineGraph.verts[1].x
            y: timelineGraph.verts[1].y
            onXChanged: {
                path1.x = x
            }
            onYChanged: {
                path1.y = y
            }
            Rectangle {
                // color: "blue"
                color: "transparent"
                height: 80
                width: 50
                x: -(width / 2)
                y: -(height / 2)
            }
        }

        Item {
            objectName: "vertex2"
            x: timelineGraph.verts[2].x
            y: timelineGraph.verts[2].y
            onXChanged: {
                path2.x = x
            }
            onYChanged: {
                path2.y = y
            }
            Rectangle {
                // color: "yellow"
                color: "transparent"
                height: 50
                width: 80
                x: -(width / 2)
                y: -(height / 2)
            }
        }

        Shape {
            anchors.fill: parent
            id: shape
            ShapePath {
                id: path
                strokeColor: "white"
                strokeWidth: 16
                fillColor: "transparent"

                startX: timelineGraph.verts[0].x
                startY: timelineGraph.verts[0].y

                PathLine {
                    id: path1
                    x: timelineGraph.verts[1].x
                    y: timelineGraph.verts[1].y
                }
                PathLine {
                    id: path2
                    x: timelineGraph.verts[2].x
                    y: timelineGraph.verts[2].y
                }
                PathLine {
                    id: path3
                    x: timelineGraph.verts[3].x
                    y: timelineGraph.verts[3].y
                }
            }

            Rectangle {
                color: "red"
                height: 50
                width: 50
                x: path.startX - (width / 2)
                y: path.startY - (height / 2)
                onXChanged: {
                    path.startX = x + (width / 2);
                    timelineGraph.update_vertices(path.startX, path.startY, path3.x, path3.y)
                }
                onYChanged: {
                    path.startY = y + (height / 2);
                    timelineGraph.update_vertices(path.startX, path.startY, path3.x, path3.y)
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
                x: path3.x - (width / 2)
                y: path3.y - (height / 2)
                onXChanged: {
                    path3.x = x + (width / 2);
                    timelineGraph.update_vertices(path.startX, path.startY, path3.x, path3.y)
                }
                onYChanged: {
                    path3.y = y + (height / 2);
                    timelineGraph.update_vertices(path.startX, path.startY, path3.x, path3.y)
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
        drag.target: timelineGraph
    }
}
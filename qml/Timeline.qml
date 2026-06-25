import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtQuick.Shapes
import NVTModule

Control {
    id: root

    background: Rectangle {
        color: Colors.bse
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
            onTriggered: timelineGraph.add_node()
        }
        Action {
            text: "Add an event"
            onTriggered: print("heh")
        }
        Action {
            text: "Add an event"
            onTriggered: print("heh")
        }
        Action {
            text: "Add an event"
            onTriggered: print("heh")
        }
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
            running = root.left_mov | root.right_mov | root.up_mov | root.down_mov;
            timelineGraph.x += root.speed * (root.left_mov - root.right_mov);
            timelineGraph.y += root.speed * (root.up_mov - root.down_mov);
        }
    }

    function keysOnPressed(event: KeyEvent) {
        if (event.isAutoRepeat === false) {
            // print("pressed: " + up_mov + " " + left_mov + " " + down_mov + " " + right_mov)

            timer.running = true;

            if      (event.key === Qt.Key_W || event.key === Qt.Key_Up)    up_mov    = 1
            else if (event.key === Qt.Key_A || event.key === Qt.Key_Left)  left_mov  = 1
            else if (event.key === Qt.Key_S || event.key === Qt.Key_Down)  down_mov  = 1
            else if (event.key === Qt.Key_D || event.key === Qt.Key_Right) right_mov = 1
        }
    }

    function keysOnReleased(event: KeyEvent) {
        if (event.isAutoRepeat === false) {
            // print("released: " + up_mov + " " + left_mov + " " + down_mov + " " + right_mov)

            if      (event.key === Qt.Key_W || event.key === Qt.Key_Up)    up_mov    = 0
            else if (event.key === Qt.Key_A || event.key === Qt.Key_Left)  left_mov  = 0
            else if (event.key === Qt.Key_S || event.key === Qt.Key_Down)  down_mov  = 0
            else if (event.key === Qt.Key_D || event.key === Qt.Key_Right) right_mov = 0
        }
    }

    TimelineGraph {
        id: timelineGraph
        x: parent.width / 2
        y: parent.height / 2

        Behavior on x {
            NumberAnimation { duration: 16 }
        }

        Behavior on y {
            NumberAnimation { duration: 16 }
        }

        Rectangle {
            id: red
            color: "red"
            height: 50
            width: 50
            onXChanged: {
                timelineGraph.update_vertices(red.x + (width/2), red.y + (height/2), green.x + (width/2), green.y + (height/2))
            }
            onYChanged: {
                timelineGraph.update_vertices(red.x + (width/2), red.y + (height/2), green.x + (width/2), green.y + (height/2))
            }
            MouseArea {
                anchors.fill: parent
                drag.target: parent
            }
        }

        Rectangle {
            id: green
            color: "green"
            height: 50
            width: 50
            onXChanged: {
                timelineGraph.update_vertices(red.x + (width/2), red.y + (height/2), green.x + (width/2), green.y + (height/2))
            }
            onYChanged: {
                timelineGraph.update_vertices(red.x + (width/2), red.y + (height/2), green.x + (width/2), green.y + (height/2))
            }
            MouseArea {
                anchors.fill: parent
                drag.target: parent
            }
        }

        onPolygonChanged: {
            pathPolyline.path = polygon
        }

        Shape {
            z: -1
            ShapePath {
                id: shapePathPolyline
                strokeColor: "white"
                strokeWidth: 16
                fillColor: "transparent"

                PathPolyline {
                    id: pathPolyline
                }
            }
        }
    }


    MouseArea {
        z: -1
        anchors.fill: parent
        drag.target: timelineGraph
    }

    // RowLayout {
    //     id: bottomthing
    //     anchors.bottom: parent.bottom
    //     anchors.horizontalCenter: timelineGraph.horizontalCenter
    //     Rectangle {
    //         height: 20
    //         width: 200
    //         color: Colors.sec
    //     }
    //     Rectangle {
    //         height: 20
    //         width: 200
    //         color: Colors.ter
    //     }
    //     Rectangle {
    //         height: 20
    //         width: 200
    //         color: Colors.sec
    //     }
    //     Rectangle {
    //         height: 20
    //         width: 200
    //         color: Colors.ter
    //     }
    //     Rectangle {
    //         height: 20
    //         width: 200
    //         color: Colors.sec
    //     }
    //     Rectangle {
    //         height: 20
    //         width: 200
    //         color: Colors.ter
    //     }
    //     Rectangle {
    //         height: 20
    //         width: 200
    //         color: Colors.sec
    //     }
    //     Rectangle {
    //         height: 20
    //         width: 200
    //         color: Colors.ter
    //     }
    //     Rectangle {
    //         height: 20
    //         width: 200
    //         color: Colors.sec
    //     }
    //     Rectangle {
    //         height: 20
    //         width: 200
    //         color: Colors.ter
    //     }
    //     Rectangle {
    //         height: 20
    //         width: 200
    //         color: Colors.sec
    //     }
    //     Rectangle {
    //         height: 20
    //         width: 200
    //         color: Colors.ter
    //     }
    //     Rectangle {
    //         height: 20
    //         width: 200
    //         color: Colors.sec
    //     }
    //     Rectangle {
    //         height: 20
    //         width: 200
    //         color: Colors.ter
    //     }
    //     Rectangle {
    //         height: 20
    //         width: 200
    //         color: Colors.sec
    //     }
    //     Rectangle {
    //         height: 20
    //         width: 200
    //         color: Colors.ter
    //     }
    // }
}
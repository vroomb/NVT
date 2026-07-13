import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtQuick.Shapes
import NVTModule

Control {
    id: root

    background: Rectangle {
        color: "#111"
    }

    function round(a, b): real {
        a = a + b/2;
        return (a - (a % b));
    }

    property point pin

    ContextMenu.menu: MetroContextMenu {
        id: contextMenu
        Action {
            text: "Add an event"
            onTriggered: {
                pin.x = pin.x - timelineGraph.x
                pin.y = pin.y - timelineGraph.y
                timelineGraph.add_node(pin)
            }
        }
    }

    ContextMenu.onRequested: position => {
        root.pin = position
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

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        drag.target: timelineGraph
        acceptedButtons: Qt.LeftButton
        onClicked: event => {
            //timelineGraph.clear_nodes()
            focus = true
            var point = Qt.point(event.x - timelineGraph.x, event.y - timelineGraph.y);
            var thing = chain.hit(point);
            print(point)
            print(thing)
            if (thing === true) {
                var ha = chain.hit_project(point);
                pin.x = ha.x;
                pin.y = ha.y;
            }
        }

        TimelineGraph {
            id: timelineGraph
            x: parent.width / 2
            y: parent.height / 2

            property real offset: 0

            onPolygonChanged: {
                chain.polygon = polygon
            }

            Behavior on x {
                NumberAnimation { duration: 16 }
            }

            Behavior on y {
                NumberAnimation { duration: 16 }
            }

            Chain {
                id: chain
                z: -1
            }

            Item {
                id: pin
                Rectangle {
                    width: 10
                    height: 10
                    radius: 5
                    color: "red"
                    x: -(width/2)
                    y: -(height/2)
                }
            }
        }
    }
}
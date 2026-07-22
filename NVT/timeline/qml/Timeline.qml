import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtQuick.Shapes
import NVT.Timeline
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

    signal focused();

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
            focus = true
            root.focused()
        }

        onPressed: event => {
            var point = Qt.point(event.x - timelineGraph.x, event.y - timelineGraph.y);
            if (chain.hit(point) === true) {
                chain.cursorEnabled = true
                chain.cursor.x = point.x
                chain.cursor.y = point.y
                drag.target = chain.cursor
            }
        }

        onReleased: event => {
            var point = Qt.point(event.x - timelineGraph.x, event.y - timelineGraph.y);
            if (chain.cursorEnabled === true) {
                chain.cursorEnabled = false;
                drag.target = timelineGraph
                chain.pin(timelineGraph.fetch_node(point));
            }
        }

        TimelineGraph {
            id: timelineGraph
            x: 100
            y: 100

            property real offset: 0

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
        }
    }
}
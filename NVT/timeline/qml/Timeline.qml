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

        padding: 0

        contentItem: ColumnLayout {
            MetroButton {
                text: "Add an event"
                onClicked: {
                    pin.x = pin.x - timelineGraph.x
                    pin.y = pin.y - timelineGraph.y
                    timelineGraph.add_node(pin)
                }
            }
            MetroButton {
                text: "Add a chain"
                onClicked: {
                    pin.x = pin.x - timelineGraph.x
                    pin.y = pin.y - timelineGraph.y
                    timelineGraph.add_chain(pin)
                }
            }
        }

        width: contextMenu.leftPadding + contentWidth + contextMenu.rightPadding;
        onContentWidthChanged: width = contextMenu.leftPadding + contentWidth + contextMenu.rightPadding;
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

        property var activeChain

        onPressed: event => {
            var point = Qt.point(event.x - timelineGraph.x, event.y - timelineGraph.y);
            activeChain = timelineGraph.fetch_chain(point)
            if (activeChain !== null) {
                activeChain.cursorEnabled = true
                activeChain.cursor.x = point.x
                activeChain.cursor.y = point.y
                drag.target = activeChain.cursor
            }
        }

        onReleased: event => {
            var point = Qt.point(event.x - timelineGraph.x, event.y - timelineGraph.y);
            if (activeChain !== null) {
                activeChain.cursorEnabled = false;
                drag.target = timelineGraph
                activeChain.pin(timelineGraph.fetch_node(point));
                activeChain = null;
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

            Rectangle {
                width: 4
                height: width
                radius: width/2
                x: -radius
                y: -radius
                color: "red"
            }
        }
    }
}
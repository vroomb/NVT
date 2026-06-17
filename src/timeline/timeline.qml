import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import "../shared"

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

    Keys.onPressed: (event) => {
        //print("pressed")
        switch (event.key) {
            case Qt.Key_W:
            case Qt.Key_Up:
                break;
            case Qt.Key_A:
            case Qt.Key_Left:
                break;
            case Qt.Key_S:
            case Qt.Key_Down:
                break;
            case Qt.Key_D:
            case Qt.Key_Right:
                break;
        }
    }

    Instantiator {

    }

    MouseArea {
        anchors.fill: parent
        drag.target: item
    }
}
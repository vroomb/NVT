import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import NVTModule

ApplicationWindow {
    visible: true

    FontLoader {
        id: johnston_medium
        source: "res/johnston-itc/johnston-itc-std-medium.otf"
    }
    FontLoader {
        id: johnston_bold
        source: "res/johnston-itc/johnston-itc-std-bold.otf"
    }

    font.family: "Johnston ITC Std"
    font.pixelSize: 25

    minimumWidth: 1280
    minimumHeight: 720

    background: Rectangle {
        color: Colors.bse
    }

    menuBar: MetroMenuBar {
        id: metroMenuBar
        height: 0
        Behavior on height {
            NumberAnimation { duration: 200 }
        }
    }

    Item {
        id: keyEventManager
        focus: true
        Keys.onPressed: (event) => {
            if (event.key === Qt.Key_Alt) {
                if (metroMenuBar.height === 0) {
                    metroMenuBar.height = 20;
                } else {
                    metroMenuBar.height = 0;
                }
            }
            else {
                // contentFrame.currentItem.keysOnPressed(event);
            }
        }
        Keys.onReleased: (event) => {
            // contentFrame.currentItem.keysOnReleased(event);
        }
    }

    Node {
        anchors.centerIn: parent
        font: parent.font
    }
}

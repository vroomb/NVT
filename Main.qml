import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import NVTModule

ApplicationWindow {
    visible: true

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

    Item {
        id: item
        objectName: "objectifying"
    }
    Item {
        id: item2
        objectName: "objectifying dos"
    }

    RepeatingTexture {
        anchors.fill: parent
        Rectangle {
            anchors.fill: parent
            color: "red"
        }

        anchorPoint: Qt.point(10, 10)
        anchorItem: item
        onAnchorItemChanged: {
            if (anchorItem != item2)
                anchorItem = item2
        }
        texture: GridLayout {
            columns: 2
            rows: 2
            Rectangle {
                height: 50
                width: 50
                color: Colors.sec
            }
            Rectangle {
                height: 50
                width: 50
                color: Colors.ter
            }
            Rectangle {
                height: 50
                width: 50
                color: Colors.ter
            }
            Rectangle {
                height: 50
                width: 50
                color: Colors.sec
            }
        }
    }

    // StackView {
    //     //focus: true
    //     id: contentFrame
    //     anchors.fill: parent
    //     initialItem: LoadPage {}
    // }
    // Component.onCompleted: {
    //     contentFrame.replace("qml/Timeline.qml")
    //     // contentFrame.replace("qml/Launch.qml")
    // }
}

import QtQuick
import QtQuick.Controls.Basic

Item {
    id: root
    MouseArea {
        drag.target: root

        width: 100
        height: 100

        x: -(width/2)
        y: -(height/2)

        Rectangle {
            color: "red"
            opacity: 0.1
            anchors.fill: parent
        }
    }
}
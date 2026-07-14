import QtQuick
import QtQuick.Controls.Basic
import NVT.Timeline

TimelinePin {
    id: root
    MouseArea {
        drag.target: root

        width: 100
        height: 100

        x: -(width/2)
        y: -(height/2)

        onPressed: event => {
            root.pressed()
            event.accepted = root.accept
        }

        onReleased: {
            root.released()
        }

        Rectangle {
            color: "red"
            anchors.fill: parent
        }
    }
}
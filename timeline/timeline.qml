import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import ".."

Control {
    id: root
    background: Rectangle {
        color: "white"
    }

    function round(a, b): real {
        a = a + b/2;
        return (a - (a % b));
    }

    Repeater {
        model: 4
        StationLabel {
            id: stationLabel
            z: mouseArea.drag.active ||  mouseArea.pressed ? 2 : 1
            text: "THAT'S A\n\nLOT OF TEXT!!!!!"
            font.family: "Johnston ITC Std"
            font.pixelSize: 30
            Drag.active: mouseArea.drag.active
            background: Rectangle {
                color: "red"
            }
            property point beginDrag
            MouseArea {
                z: 1
                id: mouseArea
                anchors.fill: parent
                drag.target: parent
                onPressed: {
                    stationLabel.beginDrag = Qt.point(stationLabel.x, stationLabel.y)
                }
                onReleased: {
                    backAnimX.from = stationLabel.x;
                    backAnimX.to = root.round(stationLabel.x, 360);
                    backAnimY.from = stationLabel.y;
                    backAnimY.to = root.round(stationLabel.y, 160);
                    backAnim.start()
                }
            }
            ParallelAnimation {
                id: backAnim
                SpringAnimation { id: backAnimX; target: stationLabel; property: "x"; duration: 500; spring: 2; damping: 0.2 }
                SpringAnimation { id: backAnimY; target: stationLabel; property: "y"; duration: 500; spring: 2; damping: 0.2 }
            }
        }
    }

    MouseArea {
        anchors.fill: parent
    }
}
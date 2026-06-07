import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Control {
    id: root
    width: 360
    font.family: "Johnson ITC Std"
    font.pixelSize: 20
    padding: 20

    property color stationOutlineColor: "#ceb9d9"
    property color stationInsideColor: "#1f1f1f"
    property color lineColorStart: "transparent"
    property color lineColorEnd: "transparent"
    property int lineWidth: 10

    property alias content: loader.sourceComponent

    contentItem: RowLayout {
        id: rowLayout

        Item {
            Layout.rightMargin: 10
            Layout.minimumWidth: stationCircle.width
            Layout.minimumHeight: stationCircle.height
            Rectangle {
                id: stationCircle
                width: 40
                height: 40
                z: 1
                color: root.stationInsideColor
                radius: 40
                border.width: 5
                border.color: root.stationOutlineColor
            }
        }


        Loader {
            id: loader
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}

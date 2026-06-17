import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Control {
    id: root
    font.family: "Johnson ITC Std"
    font.pixelSize: 20
    padding: 20

    property color stationOutlineColor: "#ceb9d9"
    property color stationInsideColor: "#1f1f1f"
    property color lineColorStart: "transparent"
    property color lineColorEnd: "transparent"
    property int lineWidth: 10
    property int circleDia: 40

    property alias content: loader.sourceComponent

    contentItem: RowLayout {
        id: rowLayout

        Item {
            Layout.rightMargin: 10
            Layout.minimumWidth: stationCircle.width
            Layout.minimumHeight: stationCircle.height
            Rectangle {
                id: stationCircle
                width: root.circleDia
                height: root.circleDia
                z: 1
                color: root.stationInsideColor
                radius: root.circleDia / 2
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

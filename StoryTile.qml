import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Control {
    id: root
    width: 360
    height: 80
    font.family: "Johnson ITC Std"
    padding: 20
    font.pixelSize: 20

    property color textColor: "black"
    property color stationOutlineColor: "#ceb9d9"
    property color stationInsideColor: "#1f1f1f"
    property color lineColor: "transparent"
    property int lineWidth: 10

    property string name: "Placeholder name"
    property string desc: "Placeholder desc"
    // required property string storyName
    // required property string storyPath

    contentItem: GridLayout {
        id: gridLayout
        rows: 2
        columns: 2

        Rectangle {
            id: stationCircle
            z: 1
            color: "#1f1f1f"
            radius: 40
            border.width: 5
            border.color: root.stationOutlineColor
            Layout.preferredHeight: 40
            Layout.preferredWidth: 40
            Layout.rowSpan: 2
            Layout.columnSpan: 1
            Layout.rightMargin: 10
            Rectangle {
                z: -1
                id: stationLine
                width: root.lineWidth
                color: root.lineColor
                height: root.height
                anchors.centerIn: parent
            }
        }

        Text {
            id: text1
            text: root.name
            verticalAlignment: Text.AlignBottom
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: root.textColor
            font.pixelSize: root.font.pixelSize
        }

        Text {
            id: text2
            text: root.desc
            verticalAlignment: Text.AlignTop
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: root.textColor
            font.pixelSize: root.font.pixelSize
        }
    }
}

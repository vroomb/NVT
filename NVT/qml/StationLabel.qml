import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import NVTModule

Control {
    id: root

    property string text: ""
    property color bgcolor: "transparent"
    property color txcolor: "black"
    property color hbcolor: "blue"
    property color htcolor: "white"
    property int xinset: 5
    property int yinset: 0
    property bool buttonActiveFocusOnTab: false

    property color stationOutlineColor: Colors.pri
    property color stationInsideColor: Colors.bse
    property color lineColorStart: "transparent"
    property color lineColorEnd: "transparent"
    property int lineWidth: 10
    property int circleDia: 40

    font.family: "Johnson ITC Std"
    font.pixelSize: 20
    padding: 20

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            metroButton.highlight = true;
            metroButton.onEntered();
        }
        onExited: {
            metroButton.highlight = false;
            metroButton.onExited()
        }
    }

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


        MetroButton {
            id: metroButton
            text: root.text
            bgcolor: root.bgcolor
            txcolor: root.txcolor
            hbcolor: root.hbcolor
            htcolor: root.htcolor
            xinset: root.xinset
            yinset: root.yinset
            activeFocusOnTab: root.buttonActiveFocusOnTab
            hover: false
        }
    }
}
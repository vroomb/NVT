import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import NVTModule

Control {
    id: root

    property alias text: metroButton.text
    property alias bgcolor: metroButton.bgcolor
    property alias txcolor: metroButton.txcolor
    property alias hbcolor: metroButton.hbcolor
    property alias htcolor: metroButton.htcolor
    property int xinset: 5
    property int yinset: 0
    property bool buttonActiveFocusOnTab: false

    property color stationOutlineColor: Colors.pri
    property color stationInsideColor: Colors.bse
    property color lineColorStart: "transparent"
    property color lineColorEnd: "transparent"
    property int lineWidth: 10
    property int circleDia: 40
    property real borderWidth: 5
    property real space: 5

    property alias bgOpacity: bg.opacity

    font.family: "Johnson ITC Std"
    font.pixelSize: 20
    padding: 20

    signal clicked();
    signal entered();
    signal exited();
    signal doubleClicked();

    MouseArea {
        id: mouseArea
        z: 100
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton
        onClicked: {
            root.clicked();
            metroButton._onClicked();
        }
        onEntered: {
            root.entered();
            metroButton._onEntered();
        }
        onExited: {
            root.exited();
            metroButton._onExited();
        }
        onDoubleClicked: {
            root.doubleClicked();
        }
    }

    contentItem: RowLayout {
        spacing: root.space

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
                border.width: root.borderWidth
                border.color: root.stationOutlineColor
            }
        }

        MetroButton {
            id: metroButton
            activeFocusOnTab: root.buttonActiveFocusOnTab
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

    background: Rectangle {
        id: bg
        opacity: 0
        radius: 15
    }
}
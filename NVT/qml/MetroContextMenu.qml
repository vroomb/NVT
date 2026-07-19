import QtQuick
import QtQuick.Controls.Basic
import NVTModule

Menu {
    id: menu

    font.family: "Johnston ITC Std"
    font.pixelSize: 18

    topPadding: 2
    bottomPadding: 2

    delegate: MenuItem {
        id: menuItem
        implicitWidth: 200
        implicitHeight: 30

        onActiveFocusChanged: {
            if (activeFocus) {
                contentItem.highlight = true;
                contentItem.onEntered();
            } else {
                contentItem.highlight = false;
                contentItem.onExited();
            }
        }

        arrow: Image {
            x: parent.width - width - 5
            anchors.verticalCenter: parent.verticalCenter
            width: 20
            height: 20
            visible: menuItem.subMenu
            source: "../../res/svg/blue_arrow.svg"
        }

        indicator: Item {
            id: thing
            implicitWidth: 30
            implicitHeight: 30
            Rectangle {
                width: 13
                height: 13
                anchors.centerIn: parent
                visible: menuItem.checkable
                border.color: "#21be2b"
                radius: 3
                Rectangle {
                    width: 7
                    height: 7
                    anchors.centerIn: parent
                    visible: menuItem.checked
                    color: "#21be2b"
                    radius: 2
                }
            }
        }

        contentItem: MetroButton {
            z: -1
            leftPadding: menuItem.indicator.width
            rightPadding: menuItem.arrow.width
            text: menuItem.text
            font: menuItem.font
            txcolor: Colors.pri
            click: false
            hover: false
            htcolor: "#292929"
            hbcolor: txcolor
        }

        background: Rectangle {
            implicitWidth: 200
            implicitHeight: 30
            opacity: enabled ? 1 : 0.3
            color: "transparent"
        }
    }

    background: Rectangle {
        implicitWidth: 200
        implicitHeight: 30
        color: "#292929"
        border.color: Colors.pri
        radius: 5
    }
}
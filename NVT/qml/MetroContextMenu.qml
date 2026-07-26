import QtQuick
import QtQuick.Controls.Basic
import NVTModule

Menu {
    id: menu

    font.family: "Johnston ITC Std"
    font.pixelSize: 18

    // delegate: MenuItem {
    //     id: menuItem

    //     onActiveFocusChanged: {
    //         if (activeFocus) {
    //             contentItem._onEntered();
    //         } else {
    //             contentItem._onExited();
    //         }
    //     }

    //     arrow: Image {
    //         x: parent.width - width - 5
    //         anchors.verticalCenter: parent.verticalCenter
    //         width: 20
    //         height: 20
    //         visible: menuItem.subMenu
    //         source: "../../res/svg/blue_arrow.svg"
    //     }

    //     indicator: Item {
    //         id: thing
    //         implicitWidth: 30
    //         implicitHeight: 30
    //         Rectangle {
    //             width: 13
    //             height: 13
    //             anchors.centerIn: parent
    //             visible: menuItem.checkable
    //             border.color: "#21be2b"
    //             radius: 3
    //             Rectangle {
    //                 width: 7
    //                 height: 7
    //                 anchors.centerIn: parent
    //                 visible: menuItem.checked
    //                 color: "#21be2b"
    //                 radius: 2
    //             }
    //         }
    //     }

    //     contentItem: MetroButton {
    //         id: metroButton
    //         z: -1
    //         text: menuItem.text
    //         font: menuItem.font
    //         txcolor: Colors.pri
    //         htcolor: "#292929"
    //         hbcolor: txcolor
    //     }

    //     background: Rectangle {
    //         // implicitWidth: metroButton.implicitBackgroundWidth
    //         // implicitHeight: metroButton.implicitBackgroundHeight
    //         opacity: enabled ? 1 : 0.3
    //         color: "transparent"
    //     }
    // }

    // contentItem: ListView {
    //     model: menu.contentModel
    //     delegate: MetroButton {
    //         txcolor: Colors.pri
    //         htcolor: "#292929"
    //         hbcolor: txcolor
    //         Component.onCompleted: {
    //             print(width);
    //             print(implicitWidth);
    //         }
    //     }
    // }

    Component.onCompleted: {
        print(contentWidth);
    }

    // background: Rectangle {
    //     color: "#292929"
    //     border.color: Colors.pri
    //     radius: 5
    //     implicitWidth: 200
    // }
}
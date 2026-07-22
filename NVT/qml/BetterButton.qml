import QtQuick
import QtQuick.Controls.Basic

AbstractButton {
    property alias bgcolor: bg.color
    property alias topRightRadius: bg.topRightRadius

    MouseArea {
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton
        onEntered: bg.opacity = 1
        onExited: bg.opacity = 0
        onClicked: parent.clicked()
        anchors.fill: parent
    }

    Label {
        text: parent.text
        anchors.centerIn: parent
    }

    background: Rectangle {
        id: bg
        topRightRadius: 15
        color: "red"
        opacity: 0

        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }
    }
}

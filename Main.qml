import QtQuick
import QtQuick.Controls.Basic
import NVTModule

ApplicationWindow {
    visible: true

    minimumWidth: 1280
    minimumHeight: 720

    background: Rectangle {
        color: "#1f1f1f"
    }

    StackView {
        focus: true
        id: contentFrame
        anchors.fill: parent
        initialItem: LoadPage {}
    }
    Component.onCompleted: {
        // contentFrame.replace("qrc:/src/timeline/timeline.qml")
        contentFrame.replace("qml/Launch.qml")
    }
}

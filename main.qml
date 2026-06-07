import QtQuick
import QtQuick.Controls.Basic

ApplicationWindow {
    minimumWidth: 1280
    minimumHeight: 720
    visible: true
    title: qsTr("Hello World")
    StackView {
        id: contentFrame
        anchors.fill: parent
        initialItem: "qrc:/load_page.qml"
    }
    Component.onCompleted: {
        contentFrame.replace("qrc:/timeline/timeline.qml")
        //contentFrame.replace("qrc:/launch/launch.qml")
    }
}

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import NVTModule
import NVT.Timeline
import NVT.Launch

Window {
    id: root
    visible: true
    visibility: Window.Maximized
    color: "#111"

    FontLoader {
        id: johnston_medium
        source: "../res/johnston-itc/johnston-itc-std-medium.otf"
    }
    FontLoader {
        id: johnston_bold
        source: "../res/johnston-itc/johnston-itc-std-bold.otf"
    }

    property font font

    font.family: "Johnston ITC Std"
    font.pixelSize: 25

    width: 960
    height: 540

    Timeline {
        id: contentFrame
        anchors.fill: parent
        font: parent.font
    }

    LaunchWindow {
        visible: true
    }
}

import QtQuick
import NVTModule

Station {
    id: root
    property string text: ""
    property color bgcolor: "transparent"
    property color txcolor: "black"
    property color hbcolor: "blue"
    property color htcolor: "white"
    property int xinset: 5
    property int yinset: 0
    property bool buttonActiveFocusOnTab: false

    // function onClicked(): void {}

    // property bool hoverEnabled: true

    // function onEntered(): void {
    //     highlight.width = control.width
    // }
    // function onExited(): void {
    //     highlight.width = 0
    // }

    content: MetroButton {
        id: metroButton
        text: root.text
        bgcolor: root.bgcolor
        txcolor: root.txcolor
        hbcolor: root.hbcolor
        htcolor: root.htcolor
        xinset: root.xinset
        yinset: root.yinset
        activeFocusOnTab: root.buttonActiveFocusOnTab
    }
}
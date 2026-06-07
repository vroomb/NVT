import QtQuick

Station {
    id: root
    property string text: ""
    property color bgcolor: "transparent"
    property color txcolor: "black"
    property color hbcolor: "blue"
    property color htcolor: "white"
    property int xinset: 5
    property int yinset: 0

    content: HighlightLabel {
        id: text1
        text: root.text
        bgcolor: root.bgcolor
        txcolor: root.txcolor
        hbcolor: root.hbcolor
        htcolor: root.htcolor
        xinset: root.xinset
        yinset: root.yinset
    }
}
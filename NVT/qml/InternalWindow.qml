import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

// hmmm, i want to make like those visual studio kind of
// internal windows. ones that you can put anywhere and make
// dynamic workspaces

Control {
    id: root
    property int w: 500
    property int h: 50
    contentItem: ColumnLayout {
        Rectangle {
            color: "red"
            implicitWidth: w
            implicitHeight: h
        }
        Rectangle {
            color: "green"
            implicitWidth: w
            implicitHeight: h
        }
        Rectangle {
            color: "blue"
            implicitWidth: w
            implicitHeight: h
        }
    }
}

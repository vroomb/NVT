import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import NVTModule

Control {
    id: root
    font.family: "Johnston ITC Std"
    // font.bold: true
    font.pixelSize: 25

    // property color bcolor: "#1f1f1f"
    // property color pcolor: "#ceb9d9"
    // property color scolor: "#8fd8da"
    // property color tcolor: "#d6da8f"

    ContextMenu.menu: MetroContextMenu {}

    FontLoader {
        id: johnston_medium
        source: "../res/johnston-itc/johnston-itc-std-medium.otf"
    }
    FontLoader {
        id: johnston_bold
        source: "../res/johnston-itc/johnston-itc-std-bold.otf"
    }

    property bool buttons_active_focus_on_tab: true

    padding: 30
    background: Rectangle {
        color: "#1f1f1f"
    }
    contentItem: ColumnLayout {
        Label {
            text: "NVT"
            color: Colors.pri
            font.pixelSize: 30
        }
        RowLayout {
            ColumnLayout {
                spacing: 0
                RowLayout {
                    Label {
                        text: "Open an existing story"
                        color: root.scolor
                        font.pixelSize: 30
                    }
                    Image {
                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 30
                        source: "../res/svg/blue_arrow.svg"
                        fillMode: Image.Stretch
                    }
                }
                StationLabel {
                    id: stationLabel1
                    text: "Find..."
                    txcolor: Colors.pri
                    htcolor: Colors.bse
                    hbcolor: Colors.pri
                    font: root.font
                    buttonActiveFocusOnTab: root.buttons_active_focus_on_tab

                    Rectangle {
                        x: 35
                        z: -1
                        width: 10
                        height: parent.parent.height - 120
                        anchors.top: stationLabel1.verticalCenter
                        color: root.scolor
                    }
                }

                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    ScrollView {
                        clip: true
                        height: (parent.height - (parent.height % 80))
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right
                        ListView {
                            boundsBehavior: Flickable.StopAtBounds
                            id: listView
                            model: LaunchModel {
                                id: thing
                            }
                            delegate: Row {
                                required property string name
                                required property string location
                                StationLabel {
                                    id: storyTile
                                    txcolor: "#ffffff"
                                    text: name + "\n" + location
                                    hbcolor: "white"
                                    htcolor: "black"
                                    font: root.font
                                    buttonActiveFocusOnTab: root.buttons_active_focus_on_tab
                                }
                            }
                        }
                    }
                }

                StationLabel {
                    text: "Browse..."
                    txcolor: Colors.pri
                    htcolor: Colors.bse
                    hbcolor: Colors.pri
                    font: root.font
                    buttonActiveFocusOnTab: root.buttons_active_focus_on_tab
                }
            }
            ColumnLayout {
                spacing: 0
                RowLayout {
                    Label {
                        text: "Create a new story"
                        color: "#d6da8f"
                        font.pixelSize: 30
                    }
                    Image {
                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 30
                        source: "../res/svg/yellow_arrow.svg"
                        fillMode: Image.Stretch
                    }
                }
                StationLabel {
                    id: stationLabel2
                    text: "Find..."
                    txcolor: Colors.pri
                    htcolor: Colors.bse
                    hbcolor: Colors.pri
                    font: root.font
                    buttonActiveFocusOnTab: root.buttons_active_focus_on_tab

                    Rectangle {
                        x: 35
                        z: -1
                        width: 10
                        height: parent.parent.height - 120
                        anchors.top: stationLabel2.verticalCenter
                        color: root.tcolor
                    }
                }

                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    ScrollView {
                        clip: true
                        height: (parent.height - (parent.height % 80))
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right
                        ListView {
                            boundsBehavior: Flickable.StopAtBounds
                            id: listView2
                            model: ListModel {
                                ListElement {
                                    name: "What"
                                }
                            }
                            delegate: Row {
                                required property string name
                                StationLabel {
                                    id: storyTile2
                                    txcolor: "#ffffff"
                                    text: name
                                    hbcolor: "white"
                                    htcolor: "black"
                                    font: root.font
                                    buttonActiveFocusOnTab: root.buttons_active_focus_on_tab
                                }
                            }
                        }
                    }
                }

                StationLabel {
                    text: "Browse..."
                    txcolor: root.pcolor
                    htcolor: root.bcolor
                    hbcolor: root.pcolor
                    font: root.font
                    buttonActiveFocusOnTab: root.buttons_active_focus_on_tab
                }
            }
        }
    }
}

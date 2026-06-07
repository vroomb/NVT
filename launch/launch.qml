import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import ".."

Control {
    id: root
    font.family: "Johnston ITC Std"
    // font.bold: true
    font.pixelSize: 25

    property color bcolor: "#1f1f1f"
    property color pcolor: "#ceb9d9"
    property color scolor: "#8fd8da"
    property color tcolor: "#d6da8f"

    FontLoader {
        id: johnston
        source: "qrc:/johnston-itc/johnston-itc-std-bold.otf"
    }

    padding: 30
    background: Rectangle {
        color: "#1f1f1f"
    }
    contentItem: ColumnLayout {
        Label {
            text: johnston.name
            color: pcolor
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
                        source: "qrc:/svg/blue_arrow.svg"
                        fillMode: Image.Stretch
                    }
                }
                StationLabel {
                    id: stationLabel1
                    text: "Find..."
                    txcolor: pcolor
                    htcolor: bcolor
                    hbcolor: pcolor
                    font: root.font

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
                            model: ListModel {
                                ListElement {
                                    sname: "Red"
                                    colorCode: "red"
                                }

                                ListElement {
                                    sname: "Green"
                                    colorCode: "green"
                                }

                                ListElement {
                                    sname: "Blue"
                                    colorCode: "blue"
                                }

                                ListElement {
                                    sname: "Blue"
                                    colorCode: "blue"
                                }

                                ListElement {
                                    sname: "Blue"
                                    colorCode: "blue"
                                }
                            }
                            delegate: Row {
                                StoryTile {
                                    id: storyTile
                                    textColor: "#ffffff"
                                    name: sname
                                    desc: colorCode
                                }
                            }
                        }
                    }
                }

                StationLabel {
                    text: "Browse..."
                    txcolor: pcolor
                    htcolor: bcolor
                    hbcolor: pcolor
                    font: root.font
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
                        source: "qrc:/svg/yellow_arrow.svg"
                        fillMode: Image.Stretch
                    }
                }
                StationLabel {
                    id: stationLabel2
                    text: "Find..."
                    txcolor: pcolor
                    htcolor: bcolor
                    hbcolor: pcolor
                    font: root.font

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
                                    sname: "Red"
                                    colorCode: "red"
                                }

                                ListElement {
                                    sname: "Green"
                                    colorCode: "green"
                                }

                                ListElement {
                                    sname: "Blue"
                                    colorCode: "blue"
                                }

                                ListElement {
                                    sname: "Blue"
                                    colorCode: "blue"
                                }

                                ListElement {
                                    sname: "Blue"
                                    colorCode: "blue"
                                }

                                ListElement {
                                    sname: "Blue"
                                    colorCode: "blue"
                                }

                                ListElement {
                                    sname: "Blue"
                                    colorCode: "blue"
                                }

                                ListElement {
                                    sname: "Blue"
                                    colorCode: "blue"
                                }

                                ListElement {
                                    sname: "Blue"
                                    colorCode: "blue"
                                }

                                ListElement {
                                    sname: "White"
                                    colorCode: "white"
                                }
                            }
                            delegate: Row {
                                StoryTile {
                                    id: storyTile2
                                    textColor: "#ffffff"
                                    name: sname
                                    desc: colorCode
                                }
                            }
                        }
                    }
                }

                StationLabel {
                    text: "Browse..."
                    txcolor: pcolor
                    htcolor: bcolor
                    hbcolor: pcolor
                    font: root.font
                }
            }
        }
    }
}

import QtQuick
import QtQuick.Layouts
import QtQuick.Dialogs
import QtQuick.Controls.Basic
import NVTModule
import NVT.Launch

Control {
    id: root
    font.family: "Johnston ITC Std"
    font.pixelSize: 20

    // ContextMenu.menu: MetroContextMenu {}

    property bool buttons_active_focus_on_tab: true
    property real radius: 15

    signal launchRequested(location: string);

    padding: 30
    bottomPadding: padding + footer.height

    background: Rectangle {
        color: "#111"
        radius: root.radius
        anchors.fill: parent
    }

    contentItem: LaunchList {
        id: launchList

        onLaunchRequested: root.launchRequested();

        projectListItem: projectList
        projectListComponent: StationLabel {
            property string name: "name"
            property string location: "location"

            font.family: "Johnston ITC Std"
            font.pixelSize: 20

            text: name + "\n" + location
            space: 2
            htcolor: "#111"
            padding: 7
            leftPadding: 20
            circleDia: 24
            borderWidth: 3
            Layout.fillWidth: true

            onEntered: {
                bgOpacity = 0.05
            }

            onExited: {
                bgOpacity = 0
            }

            onClicked: {
                parent.launchRequested(location)
            }
        }

        SwipeView {
            id: swipe
            clip: true
            interactive: false
            anchors.fill: parent

            GridLayout {
                columns: 2

                Control {
                    padding: 5
                    Layout.fillWidth: true
                    contentItem: TextField {
                        id: textField
                        background: Item {}

                        onTextChanged: {
                            launchList.find(this.text)
                        }
                    }
                    background: Rectangle {
                        color: "transparent"

                        radius: 10
                        border.color: "#1f1f1f"
                        border.width: 2
                    }
                }

                Control {
                    id: createPanel
                    padding: 5
                    contentItem: ColumnLayout {
                        MetroButton {
                            font: createPanel.font
                            text: "Create a new story"
                            color: Colors.ter
                            htcolor: "#111"

                            rightPadding: 40

                            onClicked: {
                                swipe.currentIndex = 1
                            }

                            Image {
                                source: "../res/svg/yellow_arrow.svg"
                                height: parent.font.pixelSize
                                width: parent.font.pixelSize
                                rotation: -45

                                anchors.right: parent.right
                                anchors.rightMargin: 10
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                        MetroButton {
                            font: createPanel.font
                            text: "Add an existing story"
                            color: Colors.ter
                            htcolor: "#111"

                            onClicked: {
                                folderDialog.open()
                            }

                            FolderDialog { id: folderDialog }
                        }
                    }
                    Layout.rowSpan: 2
                    Layout.minimumWidth: 200
                }

                Control {
                    id: openPanel

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    padding: 10

                    contentItem: ScrollView {
                        id: scrollView
                        ColumnLayout {
                            id: projectList
                            spacing: 0

                            function launchRequested(location: string) {
                                root.launchRequested(location)
                            }

                            Item {
                                Layout.preferredWidth: scrollView.width
                            }
                        }
                    }

                    background: Rectangle {
                        color: "transparent"

                        radius: 10
                        border.color: "#1f1f1f"
                        border.width: 2
                    }
                }
            }

            GridLayout {
                columns: 2
                MetroButton {
                    text: "Back to opening a story"
                    leftPadding: 40
                    color: Colors.sec

                    Layout.columnSpan: 2

                    onClicked: {
                        swipe.currentIndex = 0
                    }

                    Image {
                        source: "../res/svg/blue_arrow.svg"
                        height: parent.font.pixelSize
                        width: parent.font.pixelSize
                        rotation: 135

                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Label {
                    text: "Create a story"
                    font.pixelSize: 30
                    color: Colors.ter
                    Layout.columnSpan: 2

                    Image {
                        source: "../res/svg/yellow_arrow.svg"
                        height: parent.font.pixelSize
                        width: parent.font.pixelSize
                        rotation: 0

                        anchors.left: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
        }
    }

    Control {
        id: footer
        height: 70
        anchors.left: root.left
        anchors.right: root.right
        anchors.bottom: root.bottom

        RowLayout {
            anchors.leftMargin: 20
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            Label {
                text: "NVT"
                color: Colors.pri
                font.pixelSize: 35
            }

            Label {
                text: "v0.0.1"
                color: Colors.pri
                font.family: "Josefin Sans"
                font.pixelSize: 25
                Layout.topMargin: 10
            }
        }

        background: Rectangle {
            color: "#090909"
            radius: root.radius
            border.width: 5
            border.color: "transparent"
        }
    }
}

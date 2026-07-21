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

    ContextMenu.menu: MetroContextMenu {}

    property bool buttons_active_focus_on_tab: true

    signal launchRequested(location: string);

    padding: 30
    bottomPadding: padding + footer.height
    background: Rectangle {
        color: "#111"
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
            txcolor: Colors.sec
            hbcolor: Colors.sec
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

        GridLayout {
            columns: 2
            anchors.fill: parent

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
                    StationLabel {
                        font: createPanel.font
                        text: "Create a new story"
                        space: 2
                        txcolor: Colors.ter
                        hbcolor: Colors.ter
                        htcolor: "#111"
                        circleDia: 24
                        borderWidth: 3
                    }
                    StationLabel {
                        font: createPanel.font
                        text: "Add an existing story"
                        space: 2
                        txcolor: Colors.ter
                        hbcolor: Colors.ter
                        htcolor: "#111"
                        circleDia: 24
                        borderWidth: 3

                        onClicked: {
                            folderDialog.open()
                        }

                        FolderDialog {
                            id: folderDialog
                        }
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

        background: Rectangle { color: "#090909" }
    }
}

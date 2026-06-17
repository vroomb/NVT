import QtQuick
import QtQuick.Controls.Basic

AbstractButton {
    id: root

    property color bgcolor: "transparent"
    property color txcolor: "black"

    property color hbcolor: "blue"
    property color htcolor: "white"

    property int xinset: 5
    property int yinset: 0

    //padding: 0

    implicitWidth: leftPadding + control.width + rightPadding
    implicitHeight: topPadding + control.height + bottomPadding

    property bool hover: true
    property bool highlight: false

    function onEntered(): void {
        enteredAnim.start();
        _onEntered();
    }
    function onExited(): void {
        exitedAnim.start();
        _onExited();
    }
    function onClicked(): void {
        hover = false;
        enteredAnim.start();
        hover = true;
        _onClicked();
    }

    function _onEntered(): void {}
    function _onExited(): void {}
    function _onClicked(): void {
        print(text + " was clicked")
    }

    activeFocusOnTab: false
    onActiveFocusChanged: {
        if (activeFocus === true) {
            enteredAnim.start();
        } else {
            exitedAnim.start();
        }
    }

    Keys.onReturnPressed: {
        if (activeFocus === true) {
            onClicked();
        }
        print("entered pressed")
    }

    Control {
        id: control
        anchors.verticalCenter: parent.verticalCenter
        x: parent.leftPadding
        width: textBlack.contentWidth + 2*root.xinset
        height: textBlack.contentHeight + 2*root.yinset
        Rectangle {
            color: root.bgcolor
            anchors.fill: parent
            Label {
                x: root.xinset
                y: root.yinset
                id: textBlack
                text: root.text
                color: root.txcolor
                font: root.font
            }
        }

        Rectangle {
            id: highlight
            z: 1
            width: 0
            height: control.height
            color: root.hbcolor
            clip: true

            Label {
                x: root.xinset
                y: root.yinset
                id: textWhite
                text: root.text
                color: root.htcolor
                height: control.height
                width: control.width
                font: root.font
            }

            NumberAnimation {
                id: enteredAnim
                target: highlight
                property: "width"
                to: control.width
                duration: 200
                easing.type: Easing.InOutQuad
                onFinished: {
                    if ((activeFocus === false)
                            && (root.highlight === false)
                            && ((control.hovered === false) || (root.hover == false))) {
                        exitedAnim.start();
                    }
                }
            }

            SequentialAnimation {
                id: exitedAnim
                alwaysRunToEnd: true
                ParallelAnimation {
                    NumberAnimation {
                        target: highlight
                        property: "x"
                        duration: 200
                        to: control.width
                        easing.type: Easing.InOutQuad
                    }
                    NumberAnimation {
                        target: textWhite
                        property: "x"
                        duration: 200
                        to: -control.width
                        easing.type: Easing.InOutQuad
                    }
                    NumberAnimation {
                        target: highlight
                        property: "width"
                        duration: 200
                        to: 0
                        easing.type: Easing.InOutQuad
                    }
                }
                ParallelAnimation {
                    NumberAnimation {
                        target: highlight
                        property: "x"
                        duration: 0
                        to: 0
                        easing.type: Easing.InOutQuad
                    }
                    NumberAnimation {
                        target: textWhite
                        property: "x"
                        duration: 0
                        to: root.xinset
                        easing.type: Easing.InOutQuad
                    }
                }
                onFinished: {
                    if (control.hovered && root.hover === true) {
                        enteredAnim.start();
                    }
                }
            }
        }

        MouseArea {
            z: 10
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.LeftButton
            onClicked: {
                if (root.hover == true) {
                    exitedAnim.start();
                } else {
                    enteredAnim.start();
                }
                root._onClicked();
            }
            onEntered: {
                if (root.hover == true) {
                    enteredAnim.start();
                }
                root._onEntered();
            }
            onExited: {
                if (root.hover == true) {
                    exitedAnim.start();
                }
                root._onExited();
            }
        }
    }
}

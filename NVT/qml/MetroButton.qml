import QtQuick
import QtQuick.Controls.Basic
import NVTModule

// remember to fix: padding is applied twice!
// first to the root
// second to the label

AbstractButton {
    id: root

    property color color: Colors.pri

    property alias bgcolor: bg.color
    property alias txcolor: textBlack.color
    property alias hbcolor: hb.color
    property alias htcolor: textWhite.color

    property alias p: textBlack.padding
    property alias tp: textBlack.topPadding
    property alias lp: textBlack.leftPadding
    property alias rp: textBlack.rightPadding
    property alias bp: textBlack.bottomPadding

    property bool hover: true
    property bool click: true
    property bool highlight: false

    signal entered();
    signal exited();

    function _onEntered(): void {
        if (hover) {
            highlight = true;
            // print(text + " was entered");
            enteredAnim.start();
        }
        entered();
    }
    function _onExited(): void {
        if (hover) {
            highlight = false;
            // print(text + " was exited");
            exitedAnim.start();
        }
        exited();
    }
    function _onClicked(): void {
        if (click) {
            print(text + " was clicked");
            if (highlight) exitedAnim.start();
            else           enteredAnim.start();
        }
        clicked();
    }

    activeFocusOnTab: false
    onActiveFocusChanged: {
        if (activeFocus === true) {
            _onEntered();
        } else {
            _onExited();
        }
    }

    Keys.onReturnPressed: {
        if (activeFocus === true) {
            _onClicked();
        }
        print("entered pressed")
    }

    onTextChanged: {
        textBlack.text = text
        textWhite.text = text
    }

    onFontChanged: {
        textBlack.font = root.font
        textWhite.font = root.font
    }

    contentItem: Label {
        id: textBlack
        text: root.text
        font: root.font
        color: root.color

        padding: 5

        onPaddingChanged:       textWhite.padding       = padding
        onTopPaddingChanged:    textWhite.topPadding    = topPadding
        onLeftPaddingChanged:   textWhite.leftPadding   = leftPadding
        onRightPaddingChanged:  textWhite.rightPadding  = rightPadding
        onBottomPaddingChanged: textWhite.bottomPadding = bottomPadding

        background: Rectangle {
            id: bg
            color: "transparent"
        }

        Item {
            id: clipping
            clip: true
            width: textWhite.width

            x: - width - 1
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            onXChanged: {
                textWhite.x = -clipping.x
            }

            Label {
                id: textWhite
                text: root.text
                font: root.font
                color: Colors.bse

                padding:       textBlack.padding
                topPadding:    textBlack.topPadding
                leftPadding:   textBlack.leftPadding
                rightPadding:  textBlack.rightPadding
                bottomPadding: textBlack.bottomPadding

                x: -clipping.x
                anchors.top: parent.top
                anchors.bottom: parent.bottom

                background: Rectangle {
                    id: hb
                    color: root.color
                }
            }
        }
    }

    background: MouseArea {
        id: mouseArea
        z: 100

        hoverEnabled: true
        acceptedButtons: Qt.LeftButton

        onClicked: root._onClicked();
        onEntered: root._onEntered();
        onExited:  root._onExited();
    }

    NumberAnimation {
        id: enteredAnim
        target: clipping
        property: "x"
        to: 0
        duration: 200
        easing.type: Easing.InOutQuad
        onFinished: if (highlight == false) exitedAnim.start();
    }

    SequentialAnimation {
        id: exitedAnim
        alwaysRunToEnd: true
        NumberAnimation {
            target: clipping
            property: "x"
            to: textWhite.width
            duration: 200
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: clipping
            property: "x"
            to: - textWhite.width - 1
            duration: 0
            easing.type: Easing.InOutQuad
        }
        onFinished: if (highlight) enteredAnim.start();
    }
}

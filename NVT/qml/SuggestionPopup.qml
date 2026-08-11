import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    property alias placeholderText: textField.placeholderText

    contentItem: ColumnLayout {
        TextField {
            id: textField
            padding: 10
            placeholderText: "Type here..."
            background: Rectangle {
                color: "transparent"
                border.color: Colors.sec
            }
        }
        ListView {

        }
    }

    background: Rectangle {
        color: "black"
        opacity: 0.5
    }
}

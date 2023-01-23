import QtQuick 2.4
import QtQuick.Controls 2.15

Item {
    id: item1
    width: 400
    height: 400

    Column {
        id: column
        anchors.fill: parent
        spacing: 10

        TextEdit {
            id: textEdit
            text: qsTr("Text Edit")
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: row.top
            font.pixelSize: 12
            anchors.bottomMargin: 10
            anchors.topMargin: 10
            anchors.leftMargin: 10
            anchors.rightMargin: 10
        }

        Row {
            id: row
            height: button.height
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            spacing: 10
            anchors.bottomMargin: 10
            anchors.leftMargin: 10
            anchors.rightMargin: 10

            Button {
                id: button
                text: qsTr("Button")
            }

            Button {
                id: button1
                text: qsTr("Button")
            }
        }
    }
}

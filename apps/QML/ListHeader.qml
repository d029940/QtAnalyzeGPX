import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root
    property alias name: myText.text
    width: parent.width
    implicitWidth: myText.implicitWidth
    implicitHeight: col.implicitHeight

    property int mySpacing: 10

    SystemPalette {
        id: activePalette
        colorGroup: SystemPalette.Active
    }

    Rectangle {
        height: myText.implicitHeight
        width: root.width
        color: activePalette.base
        ColumnLayout {
            id: col

            //        spacing: mySpacing
            Label {
                color: activePalette.text
                id: myText
                text: name
            }

            Rectangle {
                height: 1
                width: root.width
            }
        }
    }
}

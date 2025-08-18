pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root
    property alias name: myText.text
    width: parent.width
    implicitWidth: myText.implicitWidth
    implicitHeight: rectId.height

    property int mySpacing: 10

    SystemPalette {
        id: activePalette
        colorGroup: SystemPalette.Active
    }

    Rectangle {
        id: rectId
        height: myText.implicitHeight + 2 * mySpacing
        width: root.width
        color: activePalette.base

        ColumnLayout {
            id: col
            anchors.fill: parent
            anchors.bottomMargin: myMargin
            spacing: 0

            Label {
                Layout.margins: myMargin
                color: activePalette.text
                id: myText
                text: name
            }

            //                        Rectangle {
            //                            height: 1
            //                            width: root.width
            //                        }
        }
    }
}

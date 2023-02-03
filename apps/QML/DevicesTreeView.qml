import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    property string listHeaderText
    property var myModel
    property int margin: 8

    anchors.fill: parent
    anchors.margins: margin

    ColumnLayout {
        spacing: margin

        ListHeader {
            width: root.width
            name: listHeaderText
        }

        TreeView {
            id: garminDrives
            Layout.fillHeight: true
            Layout.preferredHeight: contentHeight

            //            Layout.preferredWidth: contentWidth
            delegate: TreeViewDelegate {
                contentItem: Label {
                    id: delegatetext
                    text: model.name
                }
            }
            model: myModel
        }
    }
}

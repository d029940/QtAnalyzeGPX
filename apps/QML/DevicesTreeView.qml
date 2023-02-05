import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    property string listHeaderText
    property var myModel
    property int myMargin: 8
    required width
    required height

    anchors.fill: parent
    anchors.margins: myMargin

    ColumnLayout {
        spacing: myMargin

        ListHeader {
            name: listHeaderText
        }

        TreeView {
            id: garminDrives
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: root.height
            Layout.preferredWidth: root.width

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

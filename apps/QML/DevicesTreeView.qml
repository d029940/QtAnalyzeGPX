import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic
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
                id: treeDelegate
                implicitWidth: root.width

                Component.onCompleted: garminDrives.expandRecursively(row)

                onClicked: {
                    var mi = treeDelegate.treeView.index(row, column)
                    _controller.getSelectedRow(mi)
                }

                contentItem: Label {
                    id: label
                    text: model.name
                }
            }
            model: myModel
        }
    }
}

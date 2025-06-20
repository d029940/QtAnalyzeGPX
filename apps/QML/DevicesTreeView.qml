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

            alternatingRows: false

            property int selectedRow: 0

            delegate: TreeViewDelegate {
                id: treeDelegate
                implicitWidth: root.width
                indentation: -20    // negative indentation to remove the default indentation
                required property int index

                Component.onCompleted: garminDrives.expandRecursively(row)

                onClicked: {
                    var mi = treeDelegate.treeView.index(row, column)
                    _controller.getSelectedRow(mi)
                    garminDrives.selectedRow = row
                    // TODO: if row has children send signal to clear the table views
                }

                highlighted: hightlightRow(row, garminDrives.selectedRow, hasChildren)

                contentItem: Label {
                    id: label
                    text: model.name
                    clip: true
                }

                function hightlightRow(currentRow, selectedRow, hasChildren) {
                    if ((currentRow === selectedRow) && (!hasChildren)) {
                        return true
                    } else {
                        return false
                    }
                }
            }
            model: myModel
        }
    }
}

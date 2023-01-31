import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

ApplicationWindow {
    id: root
    visible: true
    title: qsTr("Analyze GPX file")
    color: "transparent"

    property int myMargin: 10

    // Use 80% of the screen
    width: Screen.width * 0.6
    height: Screen.height * 0.8
    minimumWidth: Screen.width * 0.4 // half of the screen width
    minimumHeight: Math.max(mainLayout.Layout.minimumHeight + 2 * myMargin,
                            Screen.height * 0.4)

    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.margins: myMargin

        // Define useable with for direct elements in mainLayout
        property double innerWidth: mainLayout.width - 2 * myMargin

        // Start out with all parts of the SplitView having the same width
        SplitView {
            id: splitView

            orientation: Qt.Horizontal
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: mainLayout.minimumWidth - (2 * myMargin)

            Rectangle {
                id: filesList
                //                SplitView.fillWidth: true
                SplitView.preferredWidth: parent.width / 4 // TODO: change if loaded with data
                SplitView.maximumWidth: parent.width * 0.8
                color: "lightBlue"
                TreeView {
                    id: garminDrives
                    anchors.fill: parent
                    // TODO: enhance delegate and model
                    delegate: Text {
                        id: del
                        text: qsTr("Drives")
                    }
                    model: _garminDrives
                }
            }

            Rectangle {
                id: tracksRect

                height: tracksView.contentHeight
                SplitView.minimumWidth: tracksView.headerItem.implicitWidth + (2 * myMargin)
                SplitView.preferredWidth: parent.width / 4
                //                SplitView.preferredWidth: tracksView.implicitWidth
                border.color: "black"

                RteTrkWptListView {
                    id: tracksView
                    listHeaderText: qsTr("Tracks")
                    roleDisplay: "Tracks"
                    myModel: 4
                }
            }

            Rectangle {
                id: routesRect

                height: routesView.contentHeight
                SplitView.minimumWidth: routesView.headerItem.implicitWidth + (2 * myMargin)
                SplitView.preferredWidth: parent.width / 4
                //                SplitView.preferredWidth: routesView.implicitWidth
                border.color: "black"

                RteTrkWptListView {
                    id: routesView
                    listHeaderText: qsTr("Routes")
                    roleDisplay: "Routes"
                    myModel: 4
                }
            }

            Rectangle {
                id: waypointsRect

                height: waypointsView.contentHeight
                SplitView.minimumWidth: waypointsView.headerItem.implicitWidth + (2 * myMargin)
                SplitView.preferredWidth: parent.width / 4

                //                SplitView.preferredWidth: waypointsView.implicitWidth
                border.color: "black"

                RteTrkWptListView {
                    id: waypointsView
                    listHeaderText: qsTr("Waypoints")
                    roleDisplay: "Waypoints"
                    myModel: 4
                }
            }
        }

        // Buttons
        RowLayout {
            id: buttonRow
            Layout.alignment: Qt.AlignBottom
            //Layout.preferredWidth: mainLayout.width
            implicitWidth: mainLayout.width

            property double buttonWidth: mainLayout.innerWidth / 4

            Button {
                id: loadGarminButton
                Layout.preferredWidth: buttonRow.buttonWidth

                text: qsTr("Load Garmin devices")
                onClicked: console.log("Load Garmin devices")
            }

            Button {
                id: deleteButton
                Layout.preferredWidth: buttonRow.buttonWidth

                text: qsTr("Delete")
                onClicked: console.log("debugButton.implicitHeight = ",
                                       debugButton.implicitHeight, "\n",
                                       "debugButton.height = ",
                                       debugButton.height, "\n",
                                       "routesView.height =",
                                       routesView.height, "\n",
                                       "routesView.width =", routesView.width)
            }

            Button {
                id: openFileButton
                Layout.preferredWidth: buttonRow.buttonWidth

                text: qsTr("Open File")
                onClicked: fileDialog.open() // or call Controller.openDialog
            }

            FileDialog {
                id: fileDialog
                nameFilters: [qsTr("GPX files (*.gpx *.GPX)")]
                //                onAccepted:
            }

            Button {
                id: exitButton
                Layout.preferredWidth: buttonRow.buttonWidth

                text: qsTr("Exit")
                onClicked: Qt.quit()
            }
        }
    }
}

pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

ApplicationWindow {
    id: root
    visible: true
    title: qsTr("Analyze GPX file")
//    color: "transparent"

    property int myMargin: 10

    // Use 80% of the screen
    width: Screen.width * 0.6
    height: Screen.height * 0.8
    minimumWidth: Screen.width * 0.4 // half of the screen width
    minimumHeight: Math.max(mainLayout.Layout.minimumHeight + 2 * myMargin,
                            Screen.height * 0.4)

    SystemPalette {
        // colors for dark, light mode
        id: activePalette
        colorGroup: SystemPalette.Active
    }

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
            Layout.preferredHeight: mainLayout.height

            Rectangle {
                id: filesList
                SplitView.fillWidth: true
                SplitView.fillHeight: true
                SplitView.preferredWidth: parent.width / 4
                SplitView.preferredHeight: parent.height

                border.color: "black"
                color: activePalette.base

                DevicesTreeView {
                    id: devicesView

                    anchors.fill: parent
                    height: parent.height
                    width: parent.width

                    myModel: _garminDrives
                    listHeaderText: qsTr("Drives")
                }
            }

            Rectangle {
                id: tracksRect

                SplitView.minimumWidth: tracksView.implicitWidth + (2 * myMargin)
                SplitView.preferredWidth: parent.width / 4

                border.color: "black"
                color: activePalette.base

                RteTrkWptListView {
                    id: tracksView
                    listHeaderText: qsTr("Tracks")
                    roleDisplay: "Tracks"
                    myModel: _tracks
                    width: parent.width
                    height: parent.height
                }
            }

            Rectangle {
                id: routesRect

                SplitView.minimumWidth: routesView.implicitWidth + (2 * myMargin)
                SplitView.preferredWidth: parent.width / 4

                border.color: "black"
                color: activePalette.base

                RteTrkWptListView {
                    id: routesView
                    listHeaderText: qsTr("Routes")
                    roleDisplay: "Routes"
                    myModel: _routes
                    width: parent.width
                    height: parent.height
                }
            }

            Rectangle {
                id: waypointsRect

                SplitView.minimumWidth: waypointsView.implicitWidth + (2 * myMargin)
                SplitView.preferredWidth: parent.width / 4

                border.color: "black"
                color: activePalette.base

                RteTrkWptListView {
                    id: waypointsView
                    listHeaderText: qsTr("Waypoints")
                    roleDisplay: "Waypoints"
                    myModel: _waypoints
                    width: parent.width
                    height: parent.height
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
                onClicked: _controller.loadGarminDirs()
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
                fileMode: FileDialog.OpenFile
                onAccepted: _controller.openGpxFile(fileDialog.selectedFile)
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

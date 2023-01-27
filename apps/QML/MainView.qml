import QtQuick 2.0
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Window {
    id: root
    visible: true
    title: qsTr("Analyze GPX file")

    property int myMargin: 10

    // Use 80% of the screen
    width: Screen.width * 0.6
    height: Screen.height * 0.8
    minimumWidth: Screen.width * 0.4 // half of the screen width
    minimumHeight: Math.max(mainLayout.Layout.minimumHeight + 2 * myMargin,
                            Screen.height * 0.4)

    // Start out with all parts of the SplitView having the same width
    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.margins: myMargin

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

        RowLayout {
            id: buttonRow
            Layout.minimumHeight: debugButton.height
            Layout.alignment: Qt.AlignBottom

            property int numberOfButtons: 4

            Button {
                id: debugButton
                width: parent.width / buttonRow.numberOfButtons

                text: qsTr("Track Routes Waypts")
                onClicked: console.log(root.width, root.minimumWidth)
                //                onClicked: console.log("TrackView height", tracksView.height,
                //                                       "TrackView contentHeight", tracksView.contentHeight,
                //                                       "TrackView implcitHeight", tracksView.implicitHeight,
                //                                       "TrackView width", tracksView.width,
                //                                       "TrackView contentWidth", tracksView.contentWidth,
                //                                       "TrackView implcitWidth", tracksView.implicitWidth,"\n",
                //                                       "RoutesView height", routesView.height,
                //                                       "RoutesView contentHeight", routesView.contentHeight,
                //                                       "RoutesView implcitHeight", routesView.implicitHeight,"\n",
                //                                       "RoutesView width", routesView.width,
                //                                       "RoutesView contentWidth", routesView.contentWidth, "\n",
                //                                       "WaypointsView height", waypointsView.height,
                //                                       "WaypointsView contentHeight", waypointsView.contentHeight, "\n",
                //                                       "WaypointsView width", waypointsView.width,
                //                                       "WaypointsView contentWidth", waypointsView.contentWidth)
            }

            Button {
                id: debugSplitview
                width: parent.width / buttonRow.numberOfButtons

                text: qsTr("SplitView")
                onClicked: console.log("splitView.contentHeight =",
                                       splitView.contentHeight,
                                       "splitView.height = ", splitView.height,
                                       "\n", "splitView.contentWidth =",
                                       splitView.contentWidth,
                                       "splitView.width =", splitView.width)
            }

            Button {
                id: deleteButton
                width: parent.width / buttonRow.numberOfButtons

                text: qsTr("Delete")
                onClicked: console.log("debugButton.implicitHeight = ",
                                       debugButton.implicitHeight, "\n",
                                       "debugButton.height = ",
                                       debugButton.height, "\n",
                                       "routesView.height =",
                                       routesView.height, "\n",
                                       "routesView.width =", routesView.width)
            }

            //            Button {
            //                id: openFile
            //                width: parent.width / buttonRow.numberOfButtons

            //                //            anchors.bottom: parent.bottom
            //                //            anchors.left: parent.left

            //                text: qsTr("Open File")
            //                onClicked: console.log("debugButton.implicitHeight = ", debugButton.implicitHeight, "\n",
            //                                       "debugButton.height = ", debugButton.height, "\n",
            //                                       "routesView.height =", routesView.height, "\n",
            //                                       "routesView.width =", routesView.width,)
            //            }
        }
    }
}

import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Dialogs

//import GarminListModel 1.0

// TODO: Many things to optimize:
// - remove magic numbers
// - Create a generic ListView
// - Make the complete Window a separate page with a frame
Window {
    id: rootItem
    visible: true
    title: qsTr("Analyze GPX file")

    signal qmlSignal

    property int myMargin: 8
    property int minimumListWidth: 100
    property int preferredListWidth: 200
    minimumWidth: mainLayout.Layout.minimumWidth + 2 * myMargin
    width: mainLayout.implicitWidth + 2 * myMargin
    minimumHeight: rowLayout.Layout.minimumHeight
    height: 800

    //    maximumHeight: 1024
    ColumnLayout {

        id: mainLayout
        anchors.fill: parent
        anchors.margins: myMargin

        RowLayout {
            id: rowLayout
            Layout.fillWidth: true
            Layout.margins: myMargin
            Layout.maximumHeight: parent.height - debugButton.height - 40
            Layout.minimumHeight: routesView.Layout.minimumHeight

            Rectangle {
                id: rectRoute
                color: "transparent"
                border.color: "red"
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: routesView.implicitWidth
                Layout.minimumWidth: minimumListWidth

                RteTrkWptListView {
                    id: routesView
                    anchors.fill: parent
                    listHeaderText: qsTr("Routes")
                    roleDisplay: "Routes"
                    myModel: 4
                }
            }

            Rectangle {
                id: rectTrack
                color: "transparent"
                border.color: "red"
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: rectTrack.implicitWidth
                Layout.minimumWidth: minimumListWidth

                RteTrkWptListView {
                    id: tracksView
                    listHeaderText: qsTr("Tracks")
                    roleDisplay: "Tracks"
                    myModel: 4
                }
            }
            Rectangle {
                id: rectWaypoint
                color: "transparent"
                border.color: "red"
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: preferredListWidth
                Layout.minimumWidth: minimumListWidth

                RteTrkWptListView {
                    id: waypointsView
                    listHeaderText: qsTr("Waypoints")
                    roleDisplay: "Waypoints"
                    myModel: 4
                }
            }
        }

        Button {
            id: debugButton
            Layout.margins: 10
            Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
            text: qsTr("Debug")
            onClicked: console.log("routesView.implcitWidth = ",
                                   routesView.implicitWidth, "\n")
        }

        Button {
            id: deleteButton
            Layout.margins: 10
            Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
            text: qsTr("Delete")
            onClicked: console.log("routesView.implcitWidth = ",
                                   routesView.implicitWidth, "\n")
        }
    }
}

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

    ListView {
        id: root

        property string listHeaderText
        property string roleDisplay
        property var myModel

        anchors.fill: parent
        anchors.margins: 10

        implicitWidth: Math.max(root.currentItem.implicitWidth, headerItem.implicitWidth) + (2 * anchors.margins)

        focus: true
        clip: true

        header: ListHeader {
            name: listHeaderText
            z: 2
        }
        headerPositioning: ListView.OverlayHeader

        model: myModel
        delegate: Rectangle {
            id: delegateRect

//            implicitWidth: t_metrics.tightBoundingRect.width + 4
            implicitWidth: mytext.paintedWidth
//            implicitWidth: contentWidth
//            implicitHeight: t_metrics.boundingRect.height + 4
            implicitHeight: mytext.paintedHeight

            Text {
                id: mytext
                anchors.centerIn: parent
                text: "GPX Route, Track and ..."
            }
            TextMetrics {
                id: t_metrics
                font: mytext.font
                text: mytext.text
            }
        }
    }








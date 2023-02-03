import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ListView {
    id: root

    property string listHeaderText
    property string roleDisplay
    property var myModel
    property int margin: 10

    anchors.fill: parent
    anchors.margins: margin

    spacing: 4

    //    implicitWidth: Math.max(root.width,
    //                            headerItem.implicitWidth) + (2 * anchors.margins)
    implicitWidth: Math.min(root.width,
                            headerItem.implicitWidth) + (2 * anchors.margins)

    focus: true
    clip: true

    header: ListHeader {
        name: listHeaderText
        z: 2
    }
    headerPositioning: ListView.OverlayHeader

    model: myModel

    delegate: Label {
        id: mytext
        text: model.name
    }
}

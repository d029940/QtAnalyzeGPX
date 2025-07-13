import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root

    property string listHeaderText
    property string roleDisplay
    property var myModel
    property int myMargin: 10
    property int mySpacing: 4
    required width
    required height

    ColumnLayout {

        anchors.fill: parent
        anchors.margins: myMargin

        ListHeader {
            id: headerTextId
            name: listHeaderText
        }

        ListView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: headerTextId.implicitWidth

            spacing: mySpacing
            clip: true

            model: myModel

            delegate: Label {
                id: mytext
                required property string name
                // text: model.name
                text: name
            }
        }
    }
}

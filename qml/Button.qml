import QtQuick 2.3

Item
{
    id: rootId
    signal clicked
    property alias text: label.text

    Rectangle
    {
        id: normalRectId
        border.color: "lightsteelblue"
        color: "gray"
        border.width: 4
        radius: 8
        width: parent.width
        height: parent.height

    }

    Rectangle
    {
        id: clickedRectId
        width: parent.width
        height: parent.height
        border.color: "lightsteelblue"
        border.width: 4
        radius: 8
        visible: false

    }
    Text
    {
        id: label
        anchors.centerIn: parent
        font.pixelSize: 24
    }
    MouseArea {
        width: parent.width
        height: parent.height
        onPressed:
        {
            clickedRectId.visible = true
            normalRectId.visible = false
        }
        onReleased:
        {
            clickedRectId.visible = false
            normalRectId.visible = true
            rootId.clicked();
        }
    }
}

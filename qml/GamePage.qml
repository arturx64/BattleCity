import QtQuick 2.3
import "qrc:/qml/."

Item
{
    objectName: "gamePageObject"
    signal handlerLoader(int idx)

    function showEndSceen(text)
    {
        endTxtId.text = text
        endAnimationId.start()
    }

    MapBoard
    {
        id: boardId
        model: MapModel
    }

    Column
    {
        anchors.right: parent.right
        Text
        {
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 24
            text: "Enemies"
        }
        GridView
        {
            width: 210;
            height: 500;

            clip: true

            model: Health.enemyHealth;
            anchors.horizontalCenter: parent.horizontalCenter


            cellWidth: 20
            cellHeight: 20
            interactive : false
            delegate: Item
            {
                width: 20
                height: 20
                Rectangle
                {
                    anchors.centerIn: parent
                    width: 15
                    height: 15
                    color: "darkcyan"
                }
            }
        }
    }

    Row
    {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        spacing: 5
        Text
        {
            font.pixelSize: 24
            text: "Health:"
        }
        GridView
        {
            width: 100;
            height: 20;

            clip: true

            model: Health.playerHealth;
            anchors.verticalCenter: parent.verticalCenter

            cellWidth: 20
            cellHeight: 20
            interactive : false
            delegate: Item
            {
                width: 20
                height: 20
                Rectangle
                {
                    anchors.centerIn: parent
                    width: 15
                    height: 15
                    color: "darkcyan"
                }
            }
        }
    }

    Text
    {
        id: endTxtId
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: -endTxtId.height
        font.pixelSize: 190
    }

    NumberAnimation {
        id: endAnimationId
        target: endTxtId
        properties: "anchors.bottomMargin"
        to:
        {
            if( parent !== null)
            return parent.height / 2 - endTxtId.height / 2
            return 0;
        }
        duration: 3000
    }
}

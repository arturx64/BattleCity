import QtQuick 2.3

Item
{
    id: rootId
    signal gameStarted

    Column
    {
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -100

        spacing: 50
        Text
        {
            id: mainTxtId
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 180
            text: "Battle City"
        }
        Button
        {
            text: "Start"
            width: 150
            height: 50
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked:
            {
                rootId.gameStarted();
            }
        }

    }
}

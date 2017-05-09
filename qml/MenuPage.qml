import QtQuick 2.3
import "qrc:/qml/."

Item
{
    signal handlerLoader(int idx)
    Menu
    {
        id: menuId
        anchors.fill: parent
        anchors.centerIn: parent
        onGameStarted:
        {
            handlerLoader(1);
        }
    }
}

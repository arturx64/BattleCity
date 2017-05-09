import QtQuick 2.3
import QtQuick.Window 2.2

Window
{
    id: rootId
    signal gameStarted

    visible: true
    height: 780
    width: 1000
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width

    function restartGame()
    {
        pageLoader.setSource(pagesList[0]);
    }

    property variant pagesList:
        [
        "pages/MenuPage.qml",
        "pages/GamePage.qml"
    ];

    signal handlerLoader(int idx)

    Rectangle
    {
        anchors.fill: parent
        color: "aliceblue"
    }

    Loader
    {
        id: pageLoader
        anchors.fill: parent
        source: pagesList[0]
    }

    Connections
    {
        target: pageLoader.item
        onHandlerLoader:
        {
            // Additional operations
            if(idx == 1)
            {
                rootId.gameStarted();
            }

            if(idx >= 0 && idx <pagesList.length)
            {
                pageLoader.setSource(pagesList[idx]);
            }
        }
    }
}

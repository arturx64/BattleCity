import EWallTypeEnum 1.0
import QtQuick 2.3

Item
{
    property alias model: gridMapId.model

    Image
    {
        fillMode: Image.Tile
        width: MapDetails.mapSize;
        height: MapDetails.mapSize
        source: "qrc:/textures/Textures/landscape.png"
    }
    GridView
    {
        id: gridMapId
        width: MapDetails.mapSize
        height: MapDetails.mapSize
        clip: true

        cellWidth: MapDetails.sectionSize
        cellHeight: MapDetails.sectionSize
        interactive : false
        delegate:cellDelegateId
    }

    Component
    {
        id: cellDelegateId
        Canvas {

            id: canvasId
            width: MapDetails.sectionSize
            height: MapDetails.sectionSize

            property var prop: damageRole;

            Component.onCompleted:
            {
                loadImage("qrc:/textures/Textures/brick.png")
                loadImage("qrc:/textures/Textures/metal.png")
                loadImage("qrc:/textures/Textures/eagle.png")
            }

            onPaint:
            {

                // get context to draw with
                var ctx = getContext("2d")

                switch(typeRole)
                {
                case EWallType.EWT_Bricks: drawBrickWall(ctx); break;
                case EWallType.EWT_Eagle: drawEagle(ctx); break;
                case EWallType.EWT_Metall: drawMetallWall(ctx); break;
                }

            }

            function drawEagle(ctx)
            {
                if(damageRole != 0)
                {
                    ctx.drawImage("qrc:/textures/Textures/eagle.png", 0, 0, MapDetails.sectionSize, MapDetails.sectionSize)
                }
                else
                {
                    ctx.clearRect(0, 0, MapDetails.sectionSize, MapDetails.sectionSize)
                }
            }

            function drawBrickWall(ctx)
            {
                if(damageRole == 65535)
                {
                    ctx.drawImage("qrc:/textures/Textures/brick.png", 0, 0, MapDetails.sectionSize, MapDetails.sectionSize)
                }

                var szSegment = MapDetails.sectionSize / 4;
                for( var index = 0; index < 16; ++index)
                {
                    var shift = 1 << index;
                    var hitBit = shift & damageRole;
                    if(!hitBit)
                    {
                        var x = parseInt(index % 4);
                        var y = parseInt(index / 4);
                        ctx.clearRect(x * szSegment, y * szSegment, szSegment, szSegment)
                    }

                }
            }

            function drawMetallWall(ctx)
            {
                ctx.drawImage("qrc:/textures/Textures/metal.png", 0, 0, MapDetails.sectionSize, MapDetails.sectionSize)
            }

            onPropChanged:
            {
                canvasId.requestPaint();
            }
        }
    }
}


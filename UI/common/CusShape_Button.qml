import QtQuick 2.12
import QtQuick.Controls 2.5
Item {
    property int radus:15
    property bool isOpen
    signal btnClicked();
    Button{
        id:btn
        anchors.fill: parent
        background: Rectangle {
            color: "transparent"
            Row{
                visible: isOpen
                anchors.left: parent.left
                anchors.leftMargin: 1
                anchors.verticalCenter: parent.verticalCenter
                spacing: 5
                Image {
                    width: 20
                    height: 20
                    source: btn.hovered?"qrc:/Image/image/normal/open_hover.png":"qrc:/Image/image/normal/open_normal.png"
                    rotation: 180
                }
                Image {
                    width: 22
                    height: 22
                    source: btn.hovered?"qrc:/Image/image/normal/detail_hover.png":"qrc:/Image/image/normal/detail.png"
                }
            }
            Row{
                visible:!isOpen
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                Image {
                    width: sourceSize.width
                    height: sourceSize.height
                    source: btn.hovered?"qrc:/Image/image/normal/historyrecord_hover.png":"qrc:/Image/image/normal/historyrecord.png"
                }
            }
            Canvas{
               id: canvas
               width: parent.width+radus
               height: parent.height
               anchors.left: parent.left
               anchors.top: parent.top
               smooth:true
               onPaint: {
                    var ctx=getContext("2d");
                    ctx.lineWidth=1;
                    ctx.beginPath()
                    ctx.roundedRect(0,0,width,height,radus,radus);
//                    ctx.moveTo(width,0);
//                    ctx.lineTo(radus,0);
//                    ctx.moveTo(0,0);
//                    ctx.arcTo(0,0,0,radus,15)

//                   ctx.moveTo(0,radus);
//                   ctx.lineTo(0,height-radus);

//                   ctx.moveTo(0,radus);
//                   ctx.lineTo(0,height-radus);

//                   ctx.arcTo(0,height-radus,radus,height,50)

//                   ctx.moveTo(radus,height);
//                   ctx.lineTo(width,height);
                   ctx.stroke();
                   ctx.beginPath();
               }
            }
        }
        onClicked: {
            btnClicked();
        }
    }
}

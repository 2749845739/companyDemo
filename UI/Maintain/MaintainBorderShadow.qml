import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    property int radus: 15
    property int currentIndex: 0
    property int shadowW: 6
    property int tabbuttonW: 204
    property alias canvas: canvas
    Canvas{
        id:canvas
        anchors.fill: parent
        smooth:true
        antialiasing: true
        onPaint: {
            var ctx = getContext("2d");
            ctx.clearRect(0,0,width,height)
            ctx.reset();  //不是QPainter不会吧之前的清掉 所以加一个reset
            if(currentIndex===0){
                ctx.beginPath();
                ctx.shadowOffsetX=6;
                ctx.shadowColor="#80000000"
                ctx.shadowBlur=6;
                ctx.lineWidth=4;
                ctx.moveTo(0,0)
                ctx.lineTo(0,height-radus-shadowW)
                ctx.stroke();
                ctx.closePath();
                ctx.restore()
            }else{
                ctx.beginPath();
                ctx.shadowOffsetX=6;
                ctx.shadowColor="#80000000"
                ctx.shadowBlur=6;
                ctx.lineWidth=4;
                ctx.moveTo(0,radus)
                ctx.lineTo(0,height-radus-shadowW)
                ctx.stroke();
                ctx.closePath();
                ctx.restore()
            }
            ctx.beginPath();
            ctx.shadowOffsetX=6;
            ctx.shadowColor="#80000000"
            ctx.shadowBlur=6;
            ctx.lineWidth=4;
            ctx.moveTo(0,height-radus-shadowW)
            ctx.arcTo(0,height-shadowW,radus,height-shadowW,radus);
            ctx.stroke();
            ctx.restore()

            ctx.beginPath();
            ctx.lineWidth=4;
            ctx.shadowOffsetX=6;
            ctx.shadowColor="#80000000"
            ctx.shadowBlur=6;
            ctx.moveTo(width-radus-shadowW,height-shadowW)
            ctx.arcTo(width-shadowW,height-shadowW,width-shadowW,height-shadowW-radus,radus);
            ctx.stroke();
            ctx.restore()

            ctx.beginPath();
            ctx.shadowOffsetY=6;
            ctx.shadowColor="#80000000"
            ctx.shadowBlur=6;
            ctx.lineWidth=4;
            ctx.moveTo(width-radus-shadowW,radus)
            ctx.arcTo(width-shadowW,radus,width-shadowW,2*radus,radus);
            ctx.stroke();
            ctx.restore()

            ctx.beginPath();
            ctx.shadowOffsetY=6;
            ctx.shadowColor="#80000000"
            ctx.shadowBlur=6;
            ctx.lineWidth=4;
            ctx.moveTo(radus,height-shadowW)
            ctx.lineTo(width-radus-shadowW,height-shadowW)
            ctx.stroke();
            ctx.closePath();
            ctx.restore()

            ctx.beginPath();
            ctx.shadowOffsetX=6;
            ctx.shadowColor="#80000000"
            ctx.shadowBlur=6;
            ctx.lineWidth=4;
            ctx.moveTo(width-shadowW,2*radus)
            ctx.lineTo(width-shadowW,height-radus-shadowW)
            ctx.stroke();
            ctx.closePath();
            ctx.restore()

            if(currentIndex==0){
                ctx.beginPath();
                ctx.shadowOffsetY=6;
                ctx.shadowOffsetX=-4;
                ctx.shadowColor="#80000000"
                ctx.shadowBlur=6;
                ctx.lineWidth=4;
                ctx.moveTo(tabbuttonW*(currentIndex+1)+radus,radus)
                ctx.lineTo(width-radus-shadowW,radus)
                ctx.stroke();
                ctx.closePath();
                ctx.restore()

                ctx.beginPath();
                ctx.shadowOffsetX=-6;
                ctx.shadowOffsetY=-1;
                ctx.shadowColor="#80000000"
                ctx.shadowBlur=6;
                ctx.lineWidth=4;
                ctx.moveTo(tabbuttonW*(currentIndex+1),0)
                ctx.arcTo(tabbuttonW*(currentIndex+1),radus,tabbuttonW*(currentIndex+1)+radus,radus,radus);
                ctx.stroke();
                ctx.restore()
            }else{
                ctx.beginPath();
                ctx.shadowOffsetY=6;
                ctx.shadowOffsetX=4;
                ctx.shadowColor="#80000000"
                ctx.shadowBlur=6;
                ctx.lineWidth=3;
                ctx.moveTo(0,radus)
                ctx.lineTo(tabbuttonW*(currentIndex)-radus,radus)
                ctx.stroke();
                ctx.closePath();
                ctx.restore()

                ctx.beginPath();
                ctx.shadowOffsetX=6;
                ctx.shadowOffsetY=1;
                ctx.shadowColor="#80000000"
                ctx.shadowBlur=6;
                ctx.lineWidth=3;
                ctx.moveTo(tabbuttonW*(currentIndex)-radus,radus)
                ctx.arcTo(tabbuttonW*(currentIndex),radus,tabbuttonW*(currentIndex),0,radus);
                ctx.stroke();
                ctx.restore()

                ctx.beginPath();
                ctx.shadowOffsetY=6;
                ctx.shadowOffsetX=-2;
                ctx.shadowColor="#80000000"
                ctx.shadowBlur=6;
                ctx.lineWidth=3;
                ctx.moveTo(tabbuttonW*(currentIndex+1)+radus,radus)
                ctx.lineTo(width-shadowW-radus,radus)
                ctx.stroke();
                ctx.closePath();
                ctx.restore()

                ctx.beginPath();
                ctx.shadowOffsetX=-6;
                ctx.shadowOffsetY=1;
                ctx.shadowColor="#80000000"
                ctx.shadowBlur=6;
                ctx.lineWidth=3;
                ctx.moveTo(tabbuttonW*(currentIndex+1),0)
                ctx.arcTo(tabbuttonW*(currentIndex+1),radus,tabbuttonW*(currentIndex+1)+radus,radus,radus);
                ctx.stroke();
                ctx.restore()

            }
        }
    }
//            Rectangle{
//                border.color: "red"
//                border.width: 1
//                anchors.fill: parent
//                color: "transparent"
//            }
}

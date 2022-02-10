import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml 2.12
Item {
    property string typeName:""
    //range信息
    property int rangeValue: 10;
    property int nowRange:0;

    //画布
    property int mW: 120;
    property int mH: 120;
    property int lineWidth: 2;

    //圆
    property double r: mH / 2; //圆心
    property double cR: r - 16 * lineWidth; //圆半径

    //Sin曲线
    property int sX: 0;
    property int sY: mH / 2;
    property int axisLength: mW;        //轴长
    property double waveWidth: 0.015;   //波浪宽度,数越小越宽
    property double waveHeight: 6;      //波浪高度,数越大越高
    property double speed: 0.15;        //波浪速度，数越大速度越快
    property double xOffset: 0;         //波浪x偏移量

    Canvas{
        id: canvas
        height: mH
        width: mW
        anchors.centerIn: parent
        onPaint: {
            var ctx = getContext("2d");

            ctx.clearRect(0, 0, mW, mH);

            //显示外圈
            ctx.beginPath();
            ctx.strokeStyle = '#148014';
            ctx.arc(r, r, cR+5, 0, 2*Math.PI);
            ctx.stroke();
            ctx.beginPath();
            ctx.arc(r, r, cR, 0, 2*Math.PI);
            ctx.clip();

            //显示sin曲线
            ctx.save();
            var points=[];
            ctx.beginPath();
            for(var x = sX; x < sX + axisLength; x += 20 / axisLength){
                var y = -Math.sin((sX + x) * waveWidth + xOffset);
                var dY = mH * (1 - nowRange / 100 );
                points.push([x, dY + y * waveHeight]);
                ctx.lineTo(x, dY + y * waveHeight);
            }

            //显示波浪
            ctx.lineTo(axisLength, mH);
            ctx.lineTo(sX, mH);
            ctx.lineTo(points[0][0],points[0][1]);
            ctx.fillStyle = '#1c86d1';
            ctx.fill();
            ctx.restore();

            //显示百分数
            ctx.save();
            var size = 0.4*cR;
            ctx.font = size + 'px sans-serif';
            ctx.textAlign = 'center';
            ctx.fillStyle = "rgba(14, 80, 14, 0.8)";
            ctx.fillText(rangeValue + '%', r, r + size / 2);
            ctx.restore();

            ctx.save();
            var sizet = 0.4*cR;
            ctx.font = size + 'px sans-serif';
            ctx.textAlign = 'center';
            ctx.fillStyle = "rgba(14, 80, 14, 0.8)";
            ctx.fillText(typeName, r, r + 2*sizet);
            ctx.restore();

            //增加Rang值
//            if(nowRange <= rangeValue){
//                nowRange += 1;
//            }

//            if(nowRange > rangeValue){
//                nowRange -= 1;
//            }
            //优化显示
            if(rangeValue<30&&rangeValue>0){
                nowRange=30;
            }else if(rangeValue===0){
                nowRange=0;
            }else if(rangeValue>30){
                nowRange=rangeValue;
            }
            xOffset += speed;
        }

        Timer{
            id: timer
            running: false
            repeat: true
            interval: 50
            onTriggered:{
                parent.requestPaint();
            }
        }
    }
    Component.onCompleted: {
        timer.start();
    }
}

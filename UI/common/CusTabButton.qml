import QtQuick 2.12
import QtQuick.Controls 2.5
Button{
    height:98
    width: 204
    property int radus: 15
    //property int indextab: 0
    property string textcontent : ""
    signal currentIndexChange();
    onClicked: {
        currentIndexChange(index);
    }
    contentItem: CusText{
        anchors.centerIn: parent
        hAlignmentType: CusText.HALIGNMENT.AlignHCenter
        textContent: modelData
        textColor:bar.currentIndex===index? "#222222":"#222222"
        fontSize: bar.currentIndex===index ? 30:24
        fontblod: true
        opacity:bar.currentIndex===index?1:0.66
    }
    background: Item{
//        Rectangle{
//            border.color: "red"
//            border.width: 1
//            anchors.fill: parent
//        }

//        CusShadow{
//            visible: bar.currentIndex===index
//            anchors.top: parent.top
//            anchors.left: parent.left
//            anchors.leftMargin: 8
//            width: parent.width-16
//            height: 20 //显示shadow 区域
//            borderpix: 4
//            shadowpix: 6
//        }
//        CusShadow{
//            //visible: index===0
//             visible: bar.currentIndex===index
//            anchors.left: parent.left
//            anchors.top: parent.top
//            anchors.topMargin: 8
//            width: 20
//            horizontal:false
//            height: parent.height-16
//            borderpix: 4
//            shadowpix: 6
//        }
//        CusShadow{
//            visible: bar.currentIndex===index
//            anchors.right: parent.right
//            anchors.rightMargin: -20
//            anchors.top: parent.top
//            anchors.topMargin: 8
//            horizontal:false
//            width: 20
//            height: parent.height-16
//            borderpix: 4
//            shadowpix: 6
//        }
        Canvas{
            visible: bar.currentIndex===index
            anchors.left: parent.left
            anchors.top: parent.top
            width: parent.width
            height: parent.height
            smooth:true
            antialiasing: true
            onPaint: {
                var ctx = getContext("2d");
                ctx.shadowOffsetX=6;
                ctx.shadowOffsetY=1;
                ctx.shadowColor="#80000000"
                ctx.shadowBlur=6;
                ctx.beginPath()
                ctx.lineWidth=4;
                ctx.moveTo(0,radus)
                ctx.lineTo(0,height)
                ctx.stroke();
                ctx.closePath();


                ctx.beginPath()
                ctx.moveTo(radus,0);
                ctx.arcTo(0,0,0,radus,radus);
                ctx.stroke();
                ctx.restore();

                ctx.beginPath()
                ctx.shadowOffsetX=-6;
                ctx.shadowOffsetY=1;
                ctx.shadowColor="#80000000"
                ctx.shadowBlur=6;
                ctx.lineWidth=4;
                ctx.moveTo(width-radus,0);
                ctx.arcTo(width,0,width,radus,radus);
                ctx.stroke();
                ctx.restore();

                ctx.beginPath()
                ctx.lineWidth=4;
                ctx.shadowColor="#80000000"
                ctx.shadowBlur=6;
                ctx.shadowOffsetY=6;
                ctx.shadowOffsetY=2;
                ctx.moveTo(radus,0)
                ctx.lineTo(width-radus,0)
                ctx.stroke();
                ctx.closePath();

                ctx.beginPath()
                ctx.shadowOffsetX=-6;
                ctx.shadowOffsetY=1;
                ctx.shadowColor="#80000000"
                ctx.shadowBlur=6;
                ctx.lineWidth=4;
                ctx.moveTo(width,radus)
                ctx.lineTo(width,height)
                ctx.stroke();
                ctx.closePath();
            }
        }
    }
}

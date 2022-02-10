import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml 2.12
import "../common"
import ".."
ScrollView{
    clip: true
    property int indexId: 0
    anchors.fill: parent
    opacity:0
    Column{
        anchors.left: parent.left
        anchors.top:parent.top
        width: parent.width
        height: parent.height
        anchors.leftMargin: 10
        spacing: 10
        Row{
            spacing: 10
            Text {
                id:light
                text:"光源"
                font.pixelSize: 20
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
        Row{
            spacing: 10
            Text {
                height: light.height
                text:"曝光时间一:"
                font.pixelSize: 15
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            CusSpinBox{
              from: 0
              to:65535
              value:boardControl.lightTime[0]
              onValueModified: {
                  boardControl.setLightInfo(0,value);
              }
            }
            Text {
                height: light.height
                text:"曝光时间二:"
                font.pixelSize: 15
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            CusSpinBox{
              from: 0
              to:65535
              value:boardControl.lightTime[1]
              onValueModified: {
                  boardControl.setLightInfo(1,value);
              }
            }
        }
//        Row{
//            spacing: 10
//            Text {
//                height: light.height
//                text:"正面透射曝光时间:"
//                font.pixelSize: 15
//                verticalAlignment: Text.AlignVCenter
//                horizontalAlignment: Text.AlignHCenter
//            }
//            CusSpinBox{
//              from: 0
//              to:100
//              value:0
//              onValueModified: {
//              }
//            }
//            Text {
//                height: light.height
//                text:"反面反透曝光时间:"
//                font.pixelSize: 15
//                verticalAlignment: Text.AlignVCenter
//                horizontalAlignment: Text.AlignHCenter
//            }
//            CusSpinBox{
//              from: 0
//              to:100
//              value:0
//              onValueModified: {
//              }
//            }
//        }
    }
    background: Rectangle{
        color: "#d2cfd0"
    }
    Behavior on opacity {
         NumberAnimation{
             to:1
             duration: 200
         }
    }
    Component.onCompleted: {
        opacity=1;
    }
}

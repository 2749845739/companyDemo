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
       anchors.fill: parent
       Row{
           height: 40
           CusCheckBox{
               id:unsound
               text:"不完善粒"
               checked: true
               onClicked: {
                   norAdjust.checked=false;
                   aiAdjust.checked=false;
                   boardControl.setTask(1);
               }
           }
       }
       Row{
           spacing: 20
           CusCheckBox{
               id:norAdjust
               text:"普通校准"
               onClicked: {
                   unsound.checked=false;
                   aiAdjust.checked=false;
                   boardControl.setTask(2);
               }
           }
           CusButtom{
               height: 40
               width: 60
               text: "抓图"
               enabled: norAdjust.checked
               backgroundColorNormal: "#cececf"
               backgroundColorHovered: "#eaf6fd"
               backgroundColorPressed: "#d7ebfa"
               backgroundColorDisable: "#b6bdc5"
               borderColor: enabled ? "#38a9e4" : "#b6bdc5"
               borderWidth: 1
               textColor: enabled ? "#38a9e4" : "#ffffff"
               onClicked: {
                   camera.captureImg();
               }
           }
       }
       Row{
           height: 40
           CusCheckBox{
               id:aiAdjust
               text:"算法校准"
               onClicked: {
                   unsound.checked=false;
                   norAdjust.checked=false;
                   boardControl.setTask(3);
               }
           }
       }

//       Row{
//           spacing: 50
//           CusButtom{
//               height: 80
//               width: 100
//               text: "普通校准"
//               backgroundColorNormal: "#cececf"
//               backgroundColorHovered: "#eaf6fd"
//               backgroundColorPressed: "#d7ebfa"
//               backgroundColorDisable: "#b6bdc5"
//               borderColor: enabled ? "#38a9e4" : "#b6bdc5"
//               borderWidth: 1
//               textColor: enabled ? "#38a9e4" : "#ffffff"
//               onClicked: {
//               }
//           }
//           CusButtom{
//               height: 80
//               width: 100
//               text: "普通校准抓图"
//               backgroundColorNormal: "#cececf"
//               backgroundColorHovered: "#eaf6fd"
//               backgroundColorPressed: "#d7ebfa"
//               backgroundColorDisable: "#b6bdc5"
//               borderColor: enabled ? "#38a9e4" : "#b6bdc5"
//               borderWidth: 1
//               textColor: enabled ? "#38a9e4" : "#ffffff"
//               onClicked: {
//               }
//           }
//           CusButtom{
//               height: 80
//               width: 100
//               text: "带算法校准"
//               backgroundColorNormal: "#cececf"
//               backgroundColorHovered: "#eaf6fd"
//               backgroundColorPressed: "#d7ebfa"
//               backgroundColorDisable: "#b6bdc5"
//               borderColor: enabled ? "#38a9e4" : "#b6bdc5"
//               borderWidth: 1
//               textColor: enabled ? "#38a9e4" : "#ffffff"
//               onClicked: {
//               }
//           }
//       }
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

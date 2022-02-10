import QtQuick 2.12
import QtQuick.Controls 2.5
import chpan 1.0
import QtQml 2.12
import ".."
import "../common"
Rectangle {
    color: "#5c646e"
    signal opensetting(int index,string source);

    ListView{
       id:listView
       objectName: "rightListView"
       model: CusConfig.rightModel
       width: parent.width
       anchors {
           //topMargin: 200
           bottom: parent.bottom
           top: parent.top
       }
       spacing: 2
       snapMode: ListView.SnapToItem
       section.criteria: ViewSection.FullString
       section.property: "group"
       section.delegate:CusButtom{
               property bool isoPen: true
               width: parent.width
               height: 40
               id: sectionBtn
               text: section
               backgroundColorNormal: "#27384f"
               backgroundColorHovered: "#5e6670"
               backgroundColorPressed: "#8f9399"
               backgroundColorDisable: "#b6bdc5"
               borderColor: enabled ? "#38a9e4" : "#b6bdc5"
               borderWidth: 1
               imgvisable: true
               textColor: enabled ? "#38a9e4" : "#ffffff"
               onClicked: {
                   isoPen=!isoPen
                   selected=!selected
                   CusConfig.updateSection(section,isoPen);
               }
           }
       delegate: Item {
           height: visible ? 30 : 0
           width: listView.width
           visible: model.visible && model.groupOpen
            CusButtom{
                width: 80
                height: 30
                anchors.centerIn: parent
                text: model.name
                backgroundColorNormal: "#cececf"
                backgroundColorHovered: "#eaf6fd"
                backgroundColorPressed: "#d7ebfa"
                backgroundColorDisable: "#b6bdc5"
                borderColor: enabled ? "#38a9e4" : "#b6bdc5"
                borderWidth: 1
                textColor: enabled ? "#38a9e4" : "#ffffff"
                onClicked: {
                    opensetting(model.indexId,model.source);
                }
            }
       }
    }
    Component.onCompleted: {
        //CusConfig.appendrightModelData(camera.listCameraId.length);
    }
    Row {
        anchors.left: parent.left
        anchors.leftMargin:(parent.width-(statusBtn.width+stopbtn.width+spacing))/2
        height: 60
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        spacing: 4
        CusRadusButton{
            id:statusBtn
            width: 60
            height: 60
            radius: 30
            selected:boardControl.isPause
            backgroundColorNormal: "#dbdbdb"
            backgroundColorHovered: "#e6e6e6"
            pressed_img:"qrc:/Image/image/Window/pause.png"
            noraml_img:"qrc:/Image/image/Window/start.png"
            onClicked: {
                if(!selected){
                    camera.setStartExposureTime();
                    boardControl.startTask("");
                }else{
                    boardControl.pauseTask();
                }
            }
        }
        CusRadusButton{
            id:stopbtn
            width: 60
            height: 60
            radius: 30
            enabled: !boardControl.isStop
            backgroundColorEnable:"#dbdbdb"
            backgroundColorNormal: "#dbdbdb"
            backgroundColorHovered: "#dbdbdb"
            pressed_img:"qrc:/Image/image/Window/stop_enable.png"
            enable_img:"qrc:/Image/image/Window/stop.png"
            noraml_img: "qrc:/Image/image/Window/stop_enable.png"
            onClicked: {
                   camera.clearWeight();
                   boardControl.stopTask();
            }
        }
    }
}

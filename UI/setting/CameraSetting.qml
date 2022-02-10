import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml 2.12
import "../common"
import ".."
ScrollView{
    clip: true
    anchors.fill: parent
    opacity: 0
    property int indexId: 0
    onIndexIdChanged: {
        console.log(camera.listCurrentExposure[indexId])
    }
    visible: {
        //return camera.listCameraId.length > 0
    }
    Row
    {
        id:title
        spacing: 20
        Text {
            id:cameraname
            text:indexId===0?"相机一":"相机二"
            font.pixelSize: 20
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            height: cameraname.height
            text:{
                "IP: "+camera.listIp[indexId]
            }
            font.pixelSize: 15
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            height: cameraname.height
            text:{
                "MAC:"+camera.listMac[indexId]
            }
            font.pixelSize: 15
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            height: cameraname.height
            text:"相机最大宽度:"+camera.listMax_w[indexId]
            font.pixelSize: 15
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            height: cameraname.height
            text:"相机最大高度:"+camera.listMax_h[indexId]
            font.pixelSize: 15
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
    Row{
        id:trigger
        spacing: 10
        anchors.left: parent.left
        anchors.top: title.bottom
        anchors.leftMargin: 10
        anchors.topMargin: 30
        width: parent.width
        Label{
            //width: 100
            height: 30
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: "相机的触发模式:"
        }
        CusCheckBox{
            id:hardTrigger
            height: 30
            text: "硬件触发"
            checked: camera.triggetMode[indexId]===0 ? true:false
            onClicked: {
                    camera.setTriggerMode(camera.listCameraId[indexId],0);
            }
        }
        CusCheckBox{
            id:softTrigger
            height: 30
            text: "软件触发"
            checked: camera.triggetMode[indexId]===1 ? true:false
            onClicked: {
                    camera.setTriggerMode(camera.listCameraId[indexId],1);
            }
        }
        CusButtom{
            height: 30
            text: "软件触发"
            backgroundColorNormal: "#cececf"
            backgroundColorHovered: "#eaf6fd"
            backgroundColorPressed: "#d7ebfa"
            backgroundColorDisable: "#b6bdc5"
            borderColor: enabled ? "#38a9e4" : "#b6bdc5"
            borderWidth: 1
            textColor: enabled ? "#38a9e4" : "#ffffff"
            onClicked: {
                camera.softTrigger(indexId);
            }
        }
    }
    Row{
       id:expose
       anchors.top: trigger.bottom
       anchors.left: parent.left
       anchors.leftMargin: 10
       anchors.topMargin: 30
       spacing: 10
       Text {
           height: cameraname.height
           text:"明场曝光时间:"
           font.pixelSize: 15
           verticalAlignment: Text.AlignVCenter
           horizontalAlignment: Text.AlignHCenter
       }
       CusSpinBox{
         from:camera.listExposureMin[indexId]
         to:camera.listExposureMax[indexId]
         value:camera.listCurrentExposure[indexId]
         onValueModified: {
             camera.setExpouseTime(camera.listCameraId[indexId],value);
         }
       }
       Text {
           height: cameraname.height
           text:"暗场曝光时间:"
           font.pixelSize: 15
           verticalAlignment: Text.AlignVCenter
           horizontalAlignment: Text.AlignHCenter
       }
       CusSpinBox{
         from:camera.listExposureMin[indexId]
         to:camera.listExposureMax[indexId]
         value:camera.darkExposureTime[indexId]
         onValueModified: {
             camera.setdarkTime(camera.listCameraId[indexId],value);
         }
       }
       Text {
           height: cameraname.height
           text:"曝光增益值:"
           font.pixelSize: 15
           verticalAlignment: Text.AlignVCenter
           horizontalAlignment: Text.AlignHCenter
       }
       CusSpinBox{
         from: camera.exposureGain_min[indexId]
         to:camera.exposureGain_max[indexId]
         value: camera.exposureGain_current[indexId]
         onValueModified: {
             camera.setExposureGain(camera.listCameraId[indexId],value);
         }
       }
       Text {
           height: cameraname.height
           text:"触发延迟:"
           font.pixelSize: 15
           verticalAlignment: Text.AlignVCenter
           horizontalAlignment: Text.AlignHCenter
       }
       CusSpinBox{
         from: camera.trigger_delay_min[indexId]
         to:camera.trigger_delay_max[indexId]
         value: camera.trigger_delay_current[indexId]
         onValueModified: {
             camera.setTrigger_delay(camera.listCameraId[indexId],value);
         }
       }
    }
    Row{
        id:rgbinfo
        anchors.top: expose.bottom
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.topMargin: 30
        spacing: 10
        Text {
            height: cameraname.height
            text:"R通道增益: "
            font.pixelSize: 15
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        CusSpinBox{
          from:  camera.listR_digitial_min[indexId];
          to:camera.listR_digitial_max[indexId];

          value:  camera.listR_digitial_current[indexId];
          onValueModified: {
              camera.setR_digitial(camera.listCameraId[indexId],value);
          }
        }
        Text {
            height: cameraname.height
            text:"G通道增益: "
            font.pixelSize: 15
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        CusSpinBox{
          from: camera.listG_digitial_min[indexId];
          to:camera.listG_digitial_max[indexId];
          value: camera.listG_digitial_current[indexId];
          onValueModified: {
              camera.setG_digitial(camera.listCameraId[indexId],value);
          }
        }
        Text {
            height: cameraname.height
            text:"B通道增益: "
            font.pixelSize: 15
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        CusSpinBox{
          from: camera.listB_digitial_min[indexId];
          to:camera.listB_digitial_max[indexId];
          value: camera.listB_digitial_current[indexId];
          onValueModified: {
              camera.setB_digitial(camera.listCameraId[indexId],value);
          }
        }
    }
    Row{
        anchors.top: rgbinfo.bottom
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.topMargin: 30
        spacing: 10
        CusCheckBox{
            text: "垂直翻转"
            checked: camera.vflip[indexId]
            onClicked: {
                   camera.setvFlip(camera.listCameraId[indexId],!camera.vflip[indexId]);
            }
        }
        CusCheckBox{
            checked: camera.hflip[indexId]
            text: "水平翻转"
            onClicked: {
                 camera.sethFlip(camera.listCameraId[indexId],!camera.hflip[indexId]);
            }
        }
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

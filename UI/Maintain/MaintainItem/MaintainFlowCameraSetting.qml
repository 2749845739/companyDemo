import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import "../../common"

Item {
    implicitWidth: 1748
    implicitHeight: 740
    property bool flowcameraVflip: true
    Connections{
        target: flowCamera
        enabled:true
        function onViewNeedUpdate(index){
             //变图必须加index
                image.imgsouce = "image://flowViewProvider/"+index
       }
    }
//    Connections{
//        target: flowStatus
//        enabled:true
//        function onSigResetStatus(){

//       }
//    }
    CusDialog{
        id:saveConfigDialog
        anchors.centerIn: Overlay.overlay
        diatype:CusDialog.DIALOGENUM.SAVECONFIG
        title: "保存配置文件提示"
        contText: "保存配置文件成功"
        onAccepted: {
            close();
        }
    }
    CusScaImage{
        id:image
        width: 904
        height: 723
    }
    Item {
        anchors.left: image.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        Column{
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            CusText{
                textContent: "流量相机"
                fontSize: 22
                fontblod: true
                textColor: "#222222"
            }
            Column{
                spacing: 5
                Row{
                    spacing: 10
                    CusText{
                        textContent: "采集帧率："
                        fontSize: 12
                        fontblod: true
                        textColor: "#004440"
                        height: 17
                    }
                    CusText{
                        textContent: flowControl.flowCameraRate[0]
                        fontSize: 12
                        fontblod: true
                        textColor: "#004440"
                        height: 17
                    }
                }

                Row{
                    spacing: 10
                    CusText{
                        textContent: "显示帧率："
                        fontSize: 12
                        fontblod: true
                        textColor: "#004440"
                        height: 17
                    }
                    CusText{
                        textContent: flowControl.flowCameraRate[2]
                        fontSize: 12
                        fontblod: true
                        textColor: "#004440"
                        height: 17
                    }
                }
                Row{
                    spacing: 10
                    CusText{
                        textContent: "丢图率："
                        fontSize: 12
                        fontblod: true
                        textColor: "#004440"
                        height: 17
                    }
                    CusText{
                        textContent: flowControl.flowCameraRate[1]
                        fontSize: 12
                        fontblod: true
                        textColor: "#004440"
                        height: 17
                    }
                }
            }
            Row{
                spacing: 10
                height: 32
                CusText{
                    width: 101
                    height: 22
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    textContent: "IP:"
                    fontSize: 16
                    anchors.verticalCenter: parent.verticalCenter
                }
                CusText{
                    width: 104
                    height: 32
                    anchors.verticalCenter: parent.verticalCenter
                    textContent: CameraProperty.ip[2]
                }
            }
            Row{
                spacing: 10
                height: 32
                CusText{
                    width: 101
                    height: 22
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    textContent: "MAC:"
                    fontSize: 16
                }
                CusText{
                    width: 104
                    height: 32
                    anchors.verticalCenter: parent.verticalCenter
                    textContent: CameraProperty.mac[2]
                }
            }
            Row{
                spacing: 10
                height: 32
                CusText{
                    width: 101
                    height: 22
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    textContent: "相机最大宽度:"
                    fontSize: 16
                    anchors.verticalCenter: parent.verticalCenter
                }
                CusText{
                    width: 104
                    height: 32
                    anchors.verticalCenter: parent.verticalCenter
                    textContent: CameraProperty.maxW[2]
                }
            }
            Row{
                spacing: 10
                height: 32
                CusText{
                    width: 101
                    height: 22
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    textContent: "相机最大高度:"
                    fontSize: 16
                    anchors.verticalCenter: parent.verticalCenter
                }
                CusText{
                    width: 104
                    height: 32
                    anchors.verticalCenter: parent.verticalCenter
                    textContent: CameraProperty.maxH[2]
                }
            }
            Row{
                spacing: 10
                height: 32
                CusText{
                    anchors.verticalCenter: parent.verticalCenter
                    width: 101
                    height: 22
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    textContent: "反射曝光时间:"
                    fontSize: 16
                }
                CusSpinBox{
                    id:cmameraThreeUp
                    to:CameraProperty.exposureTimeMax[2]
                    from: CameraProperty.exposureTimeMin[2]
                    width: 104
                    height: 32
                    value:CameraProperty.upExposureTime[2]
                    tipText: "范围:"+CameraProperty.exposureTimeMin[2]+
                    "~"+CameraProperty.exposureTimeMax[2]
                    onValueModified: {
                           CameraProperty.setExposuse(2,cmameraThreeUp.value);
                    }
                }
            }
//            Row{
//                spacing: 10
//                height: 32
//                CusText{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 101
//                    height: 22
//                    hAlignmentType:CusText.HALIGNMENT.AlignRight
//                    textContent: "透射曝光时间:"
//                    fontSize: 16
//                }
//                CusSpinBox{
//                    to:CameraProperty.exposureTimeMax[2]
//                    from: CameraProperty.exposureTimeMin[2]
//                    width: 104
//                    height: 32
//                    tipText: "范围:"+CameraProperty.exposureTimeMin[2]+
//                    "~"+CameraProperty.exposureTimeMax[2]
//                }
//            }
            Row{
                spacing: 10
                height: 32
                CusText{
                    anchors.verticalCenter: parent.verticalCenter
                    width: 101
                    height: 22
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    textContent: "曝光增益值:"
                    fontSize: 16
                }
                CusSpinBox{
                    id:cameraThreeExposureGain
                    to:CameraProperty.exposureGainMax[2]
                    from: CameraProperty.exposureGainMin[2]
                    width: 104
                    height: 32
                    value: CameraProperty.exposureGainCurrent[2]
                    tipText: "范围:"+CameraProperty.exposureGainMin[2]+
                    "~"+CameraProperty.exposureGainMax[2]
                    onValueModified: {
                           CameraProperty.setExposureGain(2,cameraThreeExposureGain.value);
                    }
                }
            }
//            Row{
//                spacing: 10
//                height: 32
//                CusText{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 101
//                    height: 22
//                    hAlignmentType:CusText.HALIGNMENT.AlignRight
//                    textContent: "触发延迟:"
//                    fontSize: 16
//                }
//                CusSpinBox{
//                    id:cameraThreeTrggerDelay
//                    to:CameraProperty.triggerDelayMax[2]
//                    from: CameraProperty.triggerDelayMin[2]
//                    width: 104
//                    height: 32
//                    value: CameraProperty.triggerDelayCurrent[2]
//                    tipText: "范围:"+CameraProperty.triggerDelayMin[2]+
//                    "~"+CameraProperty.triggerDelayMax[2]
//                    onValueChanged: {
//                           CameraProperty.setTriggerDelay(2,cameraThreeTrggerDelay.value);
//                    }
//                }
//            }
            Row{
                spacing: 10
                height: 32
                CusText{
                    anchors.verticalCenter: parent.verticalCenter
                    width: 101
                    height: 22
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    textContent: "R通道增益值:"
                    fontSize: 16
                }
                CusSpinBox{
                    id:cameraThreeR
                    to:CameraProperty.rDigitialMax[2]
                    from: CameraProperty.rDigitialMin[2]
                    width: 104
                    height: 32
                    value: CameraProperty.rDigitialCurrent[2]
                    tipText: "范围:"+CameraProperty.rDigitialMin[2]+
                    "~"+CameraProperty.rDigitialMax[2]
                    onValueModified: {
                           CameraProperty.setR_digitial(2,cameraThreeR.value);
                    }
                }
            }
            Row{
                spacing: 10
                height: 32
                CusText{
                    anchors.verticalCenter: parent.verticalCenter
                    width: 101
                    height: 22
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    textContent: "G通道增益值:"
                    fontSize: 16
                }
                CusSpinBox{
                    id:cameraThreeG
                    to:CameraProperty.gDigitialMax[2]
                    from: CameraProperty.gDigitialMin[2]
                    width: 104
                    height: 32
                    value: CameraProperty.gDigitialCurrent[2]
                    tipText: "范围:"+CameraProperty.gDigitialMin[2]+
                    "~"+CameraProperty.gDigitialMax[2]
                    onValueModified: {
                           CameraProperty.setG_digitial(2,cameraThreeG.value);
                    }
                }
            }
            Row{
                spacing: 10
                height: 32
                CusText{
                    anchors.verticalCenter: parent.verticalCenter
                    width: 101
                    height: 22
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    textContent: "B通道增益值:"
                    fontSize: 16
                }
                CusSpinBox{
                    id:cameraThreeB
                    to:CameraProperty.bDigitialMax[2]
                    from: CameraProperty.bDigitialMin[2]
                    width: 104
                    height: 32
                    value: CameraProperty.bDigitialCurrent[2]
                    tipText: "范围:"+CameraProperty.bDigitialMin[2]+
                    "~"+CameraProperty.bDigitialMax[2]
                     onValueModified: {
                           CameraProperty.setB_digitial(2,cameraThreeB.value);
                    }
                }
            }
            /*Row{
                spacing: 10
                height: 32
                CusText{
                    anchors.verticalCenter: parent.verticalCenter
                    width: 101
                    height: 22
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    textContent: "图像翻转:"
                    fontSize: 16
                }
                Item{
                    height: 22
                    width: 32+20+8
                    Row{
                        spacing: 8
                        height: 22
                        Image {
                            y:(parent.height-height)/2+7
                            source:  CameraProperty.vflip[2]?
                                         "qrc:/Image/image/maintain/selected.png":"qrc:/Image/image/maintain/select.png"
                            width: sourceSize.width
                            height: sourceSize.height
                        }
                        CusText{
                            textContent: "垂直"
                            fontSize: 16
                            width: 32
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            //flowcameraVflip=true;
                            CameraProperty.setvFlip(2,!CameraProperty.vflip[2]);
                        }
                    }
                }
                Item {
                    width: 10
                    height: 1
                }
                Item{
                    height: 22
                    width: 32+20+8
                    Row{
                        spacing: 8
                        height: 22
                        Image {
                            y:(parent.height-height)/2+7
                            source: CameraProperty.hflip[2]?
                                        "qrc:/Image/image/maintain/selected.png":"qrc:/Image/image/maintain/select.png"
                            width: sourceSize.width
                            height: sourceSize.height
                        }
                        CusText{
                            textContent: "水平"
                            fontSize: 16
                            width: 32
                        }
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            //flowcameraVflip=false;
                            CameraProperty.sethFlip(2,!CameraProperty.hflip[2]);
                        }
                    }
                }
            }*/
        }
        Row{
            spacing: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            CusRadusButton{
                text: flowControl.boardStop||flowControl.boardPause
                      ? "开始":"暂停"
                backgroundColorNormal: "#222222"
                backgroundColorEnable:"#bfbfbf"
                enabled:!flowControl.boardStoping
                radius: 4
                width: 96
                height: 40
                fontsize: 18
                onClicked: {
                    if(flowControl.boardStop||flowControl.boardPause){
                        flowControl.run();
                    }else{
                        flowControl.pause();
                    }
                }
            }
            CusRadusButton{
                text: "结束"
                enabled: flowControl.boardPause||flowControl.boardStart
                backgroundColorNormal: "#222222"
                backgroundColorEnable:"#bfbfbf"
                radius: 4
                width: 96
                height: 40
                fontsize: 18
                onClicked: {
                    flowControl.stop();
                }
            }
            CusRadusButton{
                text: "抓模板"
                backColor: "#222222"
                radius: 4
                width: 96
                height: 40
                fontsize: 18
                onClicked: {
                    saveConfigDialog.title="抓模板提示"
                    flowControl.grabImg()===0?
                        saveConfigDialog.contText="抓取成功":
                        saveConfigDialog.contText="抓取失败";
                        saveConfigDialog.open();
                }
            }
            CusRadusButton{
                text: "查看"
                backColor: "#222222"
                radius: 4
                width: 96
                height: 40
                fontsize: 18
                onClicked: {
                    flowControl.openDir();
                }
            }
            CusRadusButton{
                text: "保存"
                backColor: "#222222"
                radius: 4
                width: 96
                height: 40
                fontsize: 18
                onClicked: {
                    CameraProperty.saveCameraConfig();
                    flowControl.saveCameraConfig();
                    saveConfigDialog.title="保存配置文件提示"
                    saveConfigDialog.contText="保存配置文件成功"
                    saveConfigDialog.open();
                }
            }
        }
    }
}

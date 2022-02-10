import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import "../../common"
Item {
    implicitWidth: 1748
    implicitHeight: 740
    property bool cameraoneVflip: true
    property bool cameratwoVflip: true
    property bool cameraoneU: true
    property bool cameraoneD: true

    property bool cameratwoU: true
    property bool cameratwoD: true
    property bool ulightCheck:true
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
    Connections{
        target: lightViewProvider
        enabled:true
        function onViewNeedUpdate(index){
             //变图必须加index
            if(index%4===0){
                topOne.imgsouce = "image://inturnLightViewProvider/"+index
            }else if(index%4===1){
                topTwo.imgsouce = "image://inturnLightViewProvider/"+index
            }
            else if(index%4===2){
                bottomOne.imgsouce = "image://inturnLightViewProvider/"+index
            }
            else if(index%4===3){
                bottomTwo.imgsouce = "image://inturnLightViewProvider/"+index
            }
       }
    }
    Connections{
        target: lightView
        enabled:true
        function onViewNeedUpdate(index){
             //变图必须加index
            if(isUlignt){
                if(index%2===0){
                    topOne.imgsouce = "image://lightViewProvider/"+index
                }else if(index%2===1){
                    bottomOne.imgsouce = "image://lightViewProvider/"+index
                }
            }else{
                if(index%2===0){
                    topTwo.imgsouce = "image://lightViewProvider/"+index
                }else if(index%2===1){
                    bottomTwo.imgsouce = "image://lightViewProvider/"+index
                }
            }
       }
    }
    Connections{
        target: CameraTaskWork
        function onSigGrapImg(flag){
            saveConfigDialog.title="抓图提示"
            if(flag){
                saveConfigDialog.contText="抓图成功"
            }else{
                saveConfigDialog.contText="抓图失败"
            }
            saveConfigDialog.open();
        }
    }

    GridLayout{
        id:showImage
        width: 1086
        rows: 2
        columns: 2
        anchors.left: parent.left
        anchors.top: parent.top
        CusScaImage{
            id:topOne
            width: 538
            height: 358
        }
        CusScaImage{
            id:topTwo
            width: 538
            height: 358
        }
        CusScaImage{
            id:bottomOne
            width: 538
            height: 358
        }
        CusScaImage{
            id:bottomTwo
            width: 538
            height: 358
        }
    }
    SwipeView{
        id:view
        anchors.left: showImage.right
        anchors.leftMargin: 40
        anchors.top: parent.top
        anchors.right: parent.right
        height: parent.height
        clip: true
        orientation: Qt.Vertical
        currentIndex: indicator.currentIndex
        wheelEnabled: false
        Item {
            id: cameraSrtting
            Column{
                id:cameraone
                anchors.left: parent.left
                anchors.top: parent.top
                spacing: 5
                CusText{
                    fontSize: 24
                    textColor: "#222222"
                    textContent: "相机一"
                    fontblod: true
                }
                Item{
                    height: 5
                    width: 5
                }
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
                        textContent: CameraTaskWork.cameraOneRate[0]
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
                        textContent: CameraTaskWork.cameraOneRate[2]
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
                        textContent: CameraTaskWork.cameraOneRate[1]
                        fontSize: 12
                        fontblod: true
                        textColor: "#004440"
                        height: 17
                    }
                }
            }
            Column{
                anchors.left: parent.left
                anchors.top: cameraone.bottom
                anchors.topMargin: 8
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 100
                spacing: 12
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
                        textContent: CameraProperty.ip[0]
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
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    CusText{
                        width: 104
                        height: 32
                        anchors.verticalCenter: parent.verticalCenter
                        textContent: CameraProperty.mac[0]
                    }
                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        height: 16
                        textContent: "相机最大宽度:"
                        fontSize: 16
                        textColor: "#222222"
                        hAlignmentType:CusText.HALIGNMENT.AlignRight
                    }
                    CusText{
                        width: 104
                        height: 32
                        anchors.verticalCenter: parent.verticalCenter
                        textContent: CameraProperty.maxW[0]
                    }
                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        height: 16
                        textContent: "相机最大高度:"
                        fontSize: 16
                        textColor: "#222222"
                        hAlignmentType:CusText.HALIGNMENT.AlignRight
                    }
                    CusText{
                        anchors.verticalCenter: parent.verticalCenter
                        width: 104
                        height: 32
                        textContent: CameraProperty.maxH[0]
                    }
                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        height: 16
                        textContent: "反射曝光时间:"
                        fontSize: 16
                        textColor: "#222222"
                        hAlignmentType:CusText.HALIGNMENT.AlignRight
                    }
                     CusSpinBox{
                         id:cmameraOneUp
                         enabled: cameraoneU
                         to:CameraProperty.exposureTimeMax[0]
                         from: CameraProperty.exposureTimeMin[0]
                         width: 104
                         height: 32
                         tipText: "范围:"+CameraProperty.exposureTimeMin[0]+
                         "~"+CameraProperty.exposureTimeMax[0]
                         value:CameraProperty.upExposureTime[0]
                         onValueModified: {
                                //流量相机模式下的相机暗场曝光时间设置
                                CameraProperty.setUpExposuse(0,cmameraOneUp.value);
                               //校准模式下的相机暗场曝光时间设置
                                CameraTaskWork.setUpExposeTime(0,value);
                         }
                     }
                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        height: 16
                        textContent: "透射曝光时间:"
                        fontSize: 16
                        textColor: "#222222"
                        hAlignmentType:CusText.HALIGNMENT.AlignRight
                    }
                     CusSpinBox{
                         id:cameraoneDown
                         enabled:cameraoneD
                         to:CameraProperty.exposureTimeMax[0]
                         from: CameraProperty.exposureTimeMin[0]
                         width: 104
                         height: 32
                         tipText: "范围:"+CameraProperty.exposureTimeMin[0]+
                         "~"+CameraProperty.exposureTimeMax[0]
                         value:CameraProperty.downExposureTime[0]
                         onValueModified: {
                                CameraProperty.setDownpExposuse(0,cameraoneDown.value);
                                CameraTaskWork.setDwonExposeTime(0,value);
                         }
                     }
                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        height: 16
                        textContent: "曝光增益值:"
                        fontSize: 16
                        textColor: "#222222"
                        hAlignmentType:CusText.HALIGNMENT.AlignRight
                    }
                     CusSpinBox{
                         id:cameraoneExposureGain
                         to:CameraProperty.exposureGainMax[0]
                         from: CameraProperty.exposureGainMin[0]
                         width: 104
                         height: 32
                         value: CameraProperty.exposureGainCurrent[0]
                         tipText: "范围:"+CameraProperty.exposureGainMin[0]+
                         "~"+CameraProperty.exposureGainMax[0]
                         onValueModified: {
                                CameraProperty.setExposureGain(0,cameraoneExposureGain.value);
                         }
                     }
                }
//                Row{
//                    spacing: 10
//                    height: 32
//                    CusText{
//                        anchors.verticalCenter: parent.verticalCenter
//                        width: 100
//                        height: 16
//                        textContent: "触发延迟:"
//                        fontSize: 16
//                        textColor: "#222222"
//                        hAlignmentType:CusText.HALIGNMENT.AlignRight
//                    }
//                     CusSpinBox{
//                         id:cameraOneTrggerDelay
//                         to:CameraProperty.triggerDelayMax[0]
//                         from: CameraProperty.triggerDelayMin[0]
//                         width: 104
//                         height: 32
//                         value: CameraProperty.triggerDelayCurrent[0]
//                         tipText: "范围:"+CameraProperty.triggerDelayMin[0]+
//                         "~"+CameraProperty.triggerDelayMax[0]
//                         onValueModified: {
//                                CameraProperty.setTriggerDelay(0,cameraOneTrggerDelay.value);
//                         }
//                     }
//                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        height: 16
                        textContent: "R通道增益值:"
                        fontSize: 16
                        textColor: "#222222"
                        hAlignmentType:CusText.HALIGNMENT.AlignRight
                    }
                     CusSpinBox{
                         id:cameraOneR
                         to:CameraProperty.rDigitialMax[0]
                         from: CameraProperty.rDigitialMin[0]
                         width: 104
                         height: 32
                         value: CameraProperty.rDigitialCurrent[0]
                         tipText: "范围:"+CameraProperty.rDigitialMin[0]+
                         "~"+CameraProperty.rDigitialMax[0]
                         onValueModified: {
                                CameraProperty.setR_digitial(0,value);
                         }
                     }
                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        height: 16
                        textContent: "G通道增益值:"
                        fontSize: 16
                        textColor: "#222222"
                        hAlignmentType:CusText.HALIGNMENT.AlignRight
                    }
                     CusSpinBox{
                         id:cameraOneG
                         to:CameraProperty.gDigitialMax[0]
                         from: CameraProperty.gDigitialMin[0]
                         width: 104
                         height: 32
                         value: CameraProperty.gDigitialCurrent[0]
                         tipText: "范围:"+CameraProperty.gDigitialMin[0]+
                         "~"+CameraProperty.gDigitialMax[0]
                         onValueModified: {
                                CameraProperty.setG_digitial(0,cameraOneG.value);
                         }
                     }
                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        height: 16
                        textContent: "B通道增益值:"
                        fontSize: 16
                        textColor: "#222222"
                        hAlignmentType:CusText.HALIGNMENT.AlignRight
                    }
                     CusSpinBox{
                         id:cameraOneB
                         to:CameraProperty.bDigitialMax[0]
                         from: CameraProperty.bDigitialMin[0]
                         width: 104
                         height: 32
                         value: CameraProperty.bDigitialCurrent[0]
                         tipText: "范围:"+CameraProperty.bDigitialMin[0]+
                         "~"+CameraProperty.bDigitialMax[0]
                         onValueModified: {
                              //主意这个调的函数会设置bDigitialCurrent的值是跟value改变的值一样，
                              //若果参数不是cameraOneB.value。会调用两次，一次是你的当前参数。
                              // setB_digitial函数调用完，这个函数改变了value绑定的bDigitialCurrent的值
                              //又得调用一次。总共两次
                              //(总结就是特殊在valuechange里面调的函数会改变的value所绑定的值)
                              //通过这里我发现qml加载界面或者可以理解编译界面不是按照你代码的顺序

                              /*这里必须用value来绑定bDigitialCurrent
                              不能用spinBox的value来绑定(也会报重复绑定)   ？？？？？？？？？？？？？*/
                                CameraProperty.setB_digitial(0,cameraOneB.value);
                         }
                     }
                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        height: 16
                        textContent: "图像翻转:"
                        fontSize: 16
                        textColor: "#222222"
                        hAlignmentType:CusText.HALIGNMENT.AlignRight
                    }
                    Item{
                        height: 22
                        width: 32+20+8
                        Row{
                            spacing: 8
                            height: 22
                            Image {
                                y:(parent.height-height)/2+7
                                source: CameraProperty.vflip[0]?"qrc:/Image/image/maintain/selected.png":"qrc:/Image/image/maintain/select.png"
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
                                //cameraoneVflip=true;
                                CameraProperty.setvFlip(0,!CameraProperty.vflip[0]);
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
                                source: CameraProperty.hflip[0]?"qrc:/Image/image/maintain/selected.png":"qrc:/Image/image/maintain/select.png"
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
                                //cameraoneVflip=false;
                                CameraProperty.sethFlip(0,!CameraProperty.hflip[0]);
                            }
                        }
                    }
                }
            }

            Column{
                id:cameratwo
                anchors.right: parent.right
                anchors.rightMargin: 200
                anchors.top: parent.top
                spacing: 5
                CusText{
                    fontSize: 24
                    textColor: "#222222"
                    textContent: "相机二"
                    fontblod: true
                }
                Item{
                    height: 5
                    width: 5
                }
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
                        textContent: CameraTaskWork.cameraTwoRate[0]
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
                        textContent: CameraTaskWork.cameraTwoRate[2]
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
                        textContent: CameraTaskWork.cameraTwoRate[1]
                        fontSize: 12
                        fontblod: true
                        textColor: "#004440"
                        height: 17
                    }
                }
            }
            Column{
                id:camerapara
                anchors.right: parent.right
                anchors.top: cameratwo.bottom
                anchors.topMargin: 8
                anchors.rightMargin: 45
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 100
                spacing: 12
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
                        textContent: CameraProperty.ip[1]
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
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    CusText{
                        width: 104
                        height: 32
                        anchors.verticalCenter: parent.verticalCenter
                        textContent: CameraProperty.mac[1]
                    }
                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        height: 16
                        textContent: "相机最大宽度:"
                        fontSize: 16
                        textColor: "#222222"
                        hAlignmentType:CusText.HALIGNMENT.AlignRight
                    }
                     CusText{
                         width: 104
                         height: 32
                         anchors.verticalCenter: parent.verticalCenter
                         textContent: CameraProperty.maxW[1]
                     }
                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        height: 16
                        textContent: "相机最大高度:"
                        fontSize: 16
                        textColor: "#222222"
                        hAlignmentType:CusText.HALIGNMENT.AlignRight
                    }
                    CusText{
                        width: 104
                        height: 32
                        anchors.verticalCenter: parent.verticalCenter
                        textContent: CameraProperty.maxH[1]
                    }
                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        height: 16
                        textContent: "反射曝光时间:"
                        fontSize: 16
                        textColor: "#222222"
                        hAlignmentType:CusText.HALIGNMENT.AlignRight
                    }
                     CusSpinBox{
                         id:cmameraTwoUp
                         enabled: cameratwoU
                         to: CameraProperty.exposureTimeMax[1]
                         from: CameraProperty.exposureTimeMin[1]
                         width: 104
                         height: 32
                         value:CameraProperty.upExposureTime[1]
                         tipText: "范围:"+CameraProperty.exposureTimeMin[1]+
                         "~"+CameraProperty.exposureTimeMax[1]
                         onValueModified: {
                                CameraProperty.setUpExposuse(1,cmameraTwoUp.value);
                                CameraTaskWork.setUpExposeTime(1,value);
                         }
                     }
                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        height: 16
                        textContent: "透射曝光时间:"
                        fontSize: 16
                        textColor: "#222222"
                        hAlignmentType:CusText.HALIGNMENT.AlignRight
                    }
                     CusSpinBox{
                         id:cameraTwoDown
                         enabled: cameratwoD
                         to:CameraProperty.exposureTimeMax[1]
                         from: CameraProperty.exposureTimeMin[1]
                         width: 104
                         height: 32
                         value:CameraProperty.downExposureTime[1]
                         tipText: "范围:"+CameraProperty.exposureTimeMin[1]+
                         "~"+CameraProperty.exposureTimeMax[1]
                         onValueModified: {
                                CameraProperty.setDownpExposuse(1,cameraTwoDown.value);
                                CameraTaskWork.setDwonExposeTime(1,value);
                         }
                     }
                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        height: 16
                        textContent: "曝光增益值:"
                        fontSize: 16
                        textColor: "#222222"
                        hAlignmentType:CusText.HALIGNMENT.AlignRight
                    }
                     CusSpinBox{
                         id:cameraTwoExposureGain
                         to:CameraProperty.exposureGainMax[1]
                         from: CameraProperty.exposureGainMin[1]
                         width: 104
                         height: 32
                         value: CameraProperty.exposureGainCurrent[1]
                         tipText: "范围:"+CameraProperty.exposureGainMin[1]+
                         "~"+CameraProperty.exposureGainMax[1]
                         onValueModified: {
                                CameraProperty.setExposureGain(1,cameraTwoExposureGain.value);
                         }
                     }
                }
//                Row{
//                    spacing: 10
//                    height: 32
//                    CusText{
//                        anchors.verticalCenter: parent.verticalCenter
//                        width: 100
//                        height: 16
//                        textContent: "触发延迟:"
//                        fontSize: 16
//                        textColor: "#222222"
//                        hAlignmentType:CusText.HALIGNMENT.AlignRight
//                    }
//                     CusSpinBox{
//                         id:cameraTwoTrggerDelay
//                         to:CameraProperty.triggerDelayMax[1]
//                         from: CameraProperty.triggerDelayMin[1]
//                         width: 104
//                         height: 32
//                         value: CameraProperty.triggerDelayCurrent[1]
//                         tipText: "范围:"+CameraProperty.triggerDelayMin[1]+
//                         "~"+CameraProperty.triggerDelayMax[1]
//                         onValueModified: {
//                                CameraProperty.setTriggerDelay(1,cameraTwoTrggerDelay.value);
//                         }
//                     }
//                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        height: 16
                        textContent: "R通道增益值:"
                        fontSize: 16
                        textColor: "#222222"
                        hAlignmentType:CusText.HALIGNMENT.AlignRight
                    }
                     CusSpinBox{
                         id:cameraTwoR
                         to:CameraProperty.rDigitialMax[1]
                         from: CameraProperty.rDigitialMin[1]
                         width: 104
                         height: 32
                         value: CameraProperty.rDigitialCurrent[1]
                         tipText: "范围:"+CameraProperty.rDigitialMin[1]+
                         "~"+CameraProperty.rDigitialMax[1]
                         onValueModified: {
                                CameraProperty.setR_digitial(1,cameraTwoR.value);
                         }
                     }
                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        height: 16
                        textContent: "G通道增益值:"
                        fontSize: 16
                        textColor: "#222222"
                        hAlignmentType:CusText.HALIGNMENT.AlignRight
                    }
                     CusSpinBox{
                         id:cameraTwoG
                         to:CameraProperty.gDigitialMax[1]
                         from: CameraProperty.gDigitialMin[1]
                         width: 104
                         height: 32
                         value: CameraProperty.gDigitialCurrent[1]
                         tipText: "范围:"+CameraProperty.gDigitialMin[1]+
                         "~"+CameraProperty.gDigitialMax[1]
                         onValueModified: {
                                CameraProperty.setG_digitial(1,cameraTwoG.value);
                         }
                     }
                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        height: 16
                        textContent: "B通道增益值:"
                        fontSize: 16
                        textColor: "#222222"
                        hAlignmentType:CusText.HALIGNMENT.AlignRight
                    }
                     CusSpinBox{
                         id:cameraTwoB
                         to:CameraProperty.bDigitialMax[1]
                         from: CameraProperty.bDigitialMin[1]
                         width: 104
                         height: 32
                         value: CameraProperty.bDigitialCurrent[1]
                         tipText: "范围:"+CameraProperty.bDigitialMin[1]+
                         "~"+CameraProperty.bDigitialMax[1]
                         onValueModified: {
                                CameraProperty.setB_digitial(1,cameraTwoB.value);
                         }

                     }
                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        anchors.verticalCenter: parent.verticalCenter
                        width: 100
                        height: 16
                        textContent: "图像翻转:"
                        fontSize: 16
                        textColor: "#222222"
                        hAlignmentType:CusText.HALIGNMENT.AlignRight
                    }
                    Item{
                        height: 22
                        width: 32+20+8
                        Row{
                            spacing: 8
                            height: 22
                            Image {
                                y:(parent.height-height)/2+7
                                source: CameraProperty.vflip[1]?"qrc:/Image/image/maintain/selected.png":"qrc:/Image/image/maintain/select.png"
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
                                //cameratwoVflip=true;
                                CameraProperty.setvFlip(1,!CameraProperty.vflip[1]);
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
                                source: CameraProperty.hflip[1]?"qrc:/Image/image/maintain/selected.png":"qrc:/Image/image/maintain/select.png"
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
                                //cameratwoVflip=false;
                                CameraProperty.sethFlip(1,!CameraProperty.hflip[1]);
                            }
                        }
                    }
                }
            }
            Row{
                spacing: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                CusRadusButton{
                    text: CameraTaskWork.isStoped ||CameraTaskWork.isPause||CameraTaskWork.isStop
                          ? "开始":"暂停"
                    backgroundColorNormal: "#222222"
                    backgroundColorEnable: "#bfbfbf"
                    enabled:{
                        if(CameraTaskWork.isStop||CameraTaskWork.currentStatus!==0){
                            return false
                        }else{
                            return true
                        }
                    }
                    radius: 4
                    width: 96
                    height: 40
                    fontsize: 18
                    onClicked: {
                        if(CameraTaskWork.isStoped||CameraTaskWork.isPause||CameraTaskWork.isStop){
                            CameraTaskWork.start(true);
                        }else{
                            CameraTaskWork.start(false);
                        }
                    }
                }
                CusRadusButton{
                    enabled: CameraTaskWork.isPause || CameraTaskWork.isStart
                    text: "结束"
                    backgroundColorNormal: "#222222"
                    backgroundColorEnable:"#bfbfbf"
                    radius: 4
                    width: 96
                    height: 40
                    fontsize: 18
                    onClicked: {
                        CameraTaskWork.stop();
                    }
                }
                CusRadusButton{
                    text:!CameraTaskWork.isGraping ? "抓图":"抓图中"
                    enabled: CameraTaskWork.currentStatus!==0&&CameraTaskWork.isCalibrate&&!CameraTaskWork.isGraping
                    backgroundColorNormal: "#222222"
                    backgroundColorEnable:"#bfbfbf"
                    radius: 4
                    width: 96
                    height: 40
                    fontsize: 18
                    onClicked: {
                        Logger.d("抓图");
                        CameraTaskWork.grapImg();
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
                        CameraTaskWork.openDir()
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
                        board.saveCameraConfig();
                        saveConfigDialog.title="保存配置文件提示"
                        saveConfigDialog.contText="保存配置文件成功"
                        saveConfigDialog.open();
                    }
                }
            }
        }
        Item {
            id: motorSetting
            property bool glmotor: false
            Column{
                anchors.left: parent.left
                anchors.top: parent.top
                spacing: 30
//                Repeater{
//                    model: ["送料电机","仓门电机","刮料电机","震动器"]
                Row{
                    spacing: 10
                    CusText{
                        textContent: "送料电机"
                        fontSize: 24
                        textColor: "#222222"
                        width: 96
                        height: 34
                        fontblod: true
                    }
                    Grid{
                        columns: 2
                        Item{
                            height: 38
                            width: 1
                        }
                        Item{
                            height: 37
                            width: 1
                        }
                        Row{
                            spacing: 10
                            height: 52
                            CusText{
                                textContent:"前进速度:"
                                fontSize: 16
                                hAlignmentType:CusText.HALIGNMENT.AlignRight
                                textColor: "#222222"
                                anchors.verticalCenter: parent.verticalCenter
                                width: 69
                            }
                            CusSpinBox{
                                to:900
                                from: 9
                                width: 104
                                height: 32
                                anchors.verticalCenter: parent.verticalCenter
                                stepSize: 10
                                tipText: "范围9~900"
                                value: board.slPositiveSpeed
                                onValueModified: {
                                    board.setSmotorPositiveSpeed(1,value);
                                }
                            }
                            Item{
                                height: 1
                                width: 20
                            }
                        }
                        Row{
                            spacing: 10
                            height: 52
                            CusText{
                                textContent:"起始震动位置:"
                                fontSize: 16
                                hAlignmentType:CusText.HALIGNMENT.AlignRight
                                textColor: "#222222"
                                anchors.verticalCenter: parent.verticalCenter
                                width: 101
                            }
                            CusSpinBox{
                                to:4000
                                from: 0
                                width: 104
                                height: 32
                                anchors.verticalCenter: parent.verticalCenter
                                stepSize: 100
                                tipText: "范围0~4000"
                                value: board.slStartPosition
                                onValueModified: {
                                    board.setSmotorStartPosition(1,value);
                                }
                            }
                            Item{
                                height: 1
                                width: 20
                            }
                        }
                        Row{
                            spacing: 10
                            height: 52
                            CusText{
                                textContent:"后退速度:"
                                fontSize: 16
                                hAlignmentType:CusText.HALIGNMENT.AlignRight
                                textColor: "#222222"
                                anchors.verticalCenter: parent.verticalCenter
                                width: 69
                            }
                            CusSpinBox{
                                to:900
                                from: 9
                                width: 104
                                height: 32
                                anchors.verticalCenter: parent.verticalCenter
                                stepSize: 10
                                tipText: "范围9~900"
                                value: board.slNegativeSpeed
                                onValueModified: {
                                    board.setSmotorNegtiveSpeed(1,value);
                                }
                            }
                            Item{
                                height: 1
                                width: 20
                            }
                        }
                        Row{
                            spacing: 10
                            height: 52
                            CusText{
                                textContent:"结束震动位置:"
                                fontSize: 16
                                hAlignmentType:CusText.HALIGNMENT.AlignRight
                                textColor: "#222222"
                                anchors.verticalCenter: parent.verticalCenter
                                width: 101
                            }
                            CusSpinBox{
                                to:8500
                                from: 4000
                                width: 104
                                height: 32
                                anchors.verticalCenter: parent.verticalCenter
                                stepSize: 100
                                tipText: "范围4000~8500"
                                value: board.slStopPosition
                                onValueModified: {
                                    board.setSmotorStoPosition(1,value);
                                }
                            }
                            Item{
                                height: 1
                                width: 20
                            }
                        }
                        Row{
                            spacing: 10
                            height: 52
                            CusText{
                                textContent:"预震位置:"
                                fontSize: 16
                                hAlignmentType:CusText.HALIGNMENT.AlignRight
                                textColor: "#222222"
                                anchors.verticalCenter: parent.verticalCenter
                                width: 69
                            }
                            CusSpinBox{
                                to:4000
                                from: 0
                                width: 104
                                height: 32
                                anchors.verticalCenter: parent.verticalCenter
                                stepSize: 100
                                tipText: "范围0~4000"
                                value: board.slPrePosition
                                onValueModified: {
                                    board.setSmotorPrePosition(1,value);
                                }
                            }
                            Item{
                                height: 1
                                width: 20
                            }
                        }

                        Row{
                            spacing: 10
                            height: 52
                            CusText{
                                textContent:"拍照延时:"
                                fontSize: 16
                                hAlignmentType:CusText.HALIGNMENT.AlignRight
                                textColor: "#222222"
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            CusSpinBox{
                                to:4000
                                from: 0
                                width: 104
                                height: 32
                                anchors.verticalCenter: parent.verticalCenter
                                stepSize: 1
                                tipText: "范围0~4000"
                                value: board.triggerDlay
                                onValueModified: {
                                    board.setBoardTriggertDlay(value);
                                }
                            }
                            Item{
                                height: 1
                                width: 20
                            }
                        }
                    }
                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        textContent: "仓门电机"
                        fontSize: 24
                        textColor: "#222222"
                        width: 96
                        height: 34
                        fontblod: true
                    }
                    Grid{
                        anchors.verticalCenter: parent.verticalCenter
                        Row{
                            spacing: 10
                            height: 52
                            CusText{
                                width: 101
                                textContent:"仓门打开高度:"
                                fontSize: 16
                                hAlignmentType:CusText.HALIGNMENT.AlignRight
                                textColor: "#222222"
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            CusSpinBox{
                                to:6000
                                from: 0
                                width: 104
                                height: 32
                                anchors.verticalCenter: parent.verticalCenter
                                stepSize: 10
                                tipText: "范围0~6000"
                                value: board.cmPrePosition
                                onValueModified: {
                                    board.setSmotorPrePosition(0,value);
                                }
                            }
                            Item{
                                height: 1
                                width: 20
                            }
                        }
                    }
                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        textContent: "刮料电机"
                        fontSize: 24
                        textColor: "#222222"
                        width: 96
                        height: 34
                        fontblod: true
                    }
                    Grid{
                        anchors.verticalCenter: parent.verticalCenter
                        Row{
                            spacing: 20
                            height: 52
                            CusText{
                                width: 149
                                textContent:"振动器入料时，保持:"
                                fontSize: 16
                                hAlignmentType:CusText.HALIGNMENT.AlignRight
                                textColor: "#222222"
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            Item{
                                height: 22
                                width: 52
                                anchors.verticalCenter: parent.verticalCenter
                                Row{
                                    spacing: 8
                                    anchors.verticalCenter: parent.verticalCenter
                                    Image {
                                        y:(parent.height-height)/2
                                        source: board.openOnVibrate?"qrc:/Image/image/maintain/selected.png":"qrc:/Image/image/maintain/select.png"
                                        width: sourceSize.width
                                        height: sourceSize.height
                                    }
                                    CusText{
                                        textContent: "打开"
                                        fontSize: 16
                                        width: 32
                                    }
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        board.setDcmotorPolicy(0,true);
                                    }
                                }
                            }
                            Item{
                                height: 22
                                width: 52
                                anchors.verticalCenter: parent.verticalCenter
                                Row{
                                    spacing: 8
                                    anchors.verticalCenter: parent.verticalCenter
                                    Image {
                                        y:(parent.height-height)/2
                                        source: board.openOnVibrate?"qrc:/Image/image/maintain/select.png":"qrc:/Image/image/maintain/selected.png"
                                        width: sourceSize.width
                                        height: sourceSize.height
                                    }
                                    CusText{
                                        textContent: "关闭"
                                        fontSize: 16
                                        width: 32
                                    }
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        //motorSetting.glmotor=false;
                                        board.setDcmotorPolicy(0,false);
                                    }
                                }
                            }
                        }
                    }
                }
                Row{
                    spacing: 10
                    CusText{
                        textContent: "震动器"
                        fontSize: 24
                        textColor: "#222222"
                        width: 96
                        height: 34
                        fontblod: true
                    }
                    Grid{
                        columns: 2
                        Item{
                            height: 38
                            width: 1
                        }
                        Item{
                            height: 37
                            width: 1
                        }
//                        Row{
//                            spacing: 10
//                            height: 52
//                            CusText{
//                                textContent:"进料振动时间:"
//                                fontSize: 16
//                                hAlignmentType:CusText.HALIGNMENT.AlignRight
//                                textColor: "#222222"
//                                anchors.verticalCenter: parent.verticalCenter
//                                width: 101
//                            }
//                            CusSpinBox{
//                                to:65535
//                                from: 0
//                                width: 104
//                                height: 32
//                                anchors.verticalCenter: parent.verticalCenter
//                            }
//                            Item{
//                                height: 1
//                                width: 20
//                            }
//                        }
                        Row{
                            spacing: 10
                            height: 52
                            CusText{
                                textContent:"中心频率:"
                                fontSize: 16
                                hAlignmentType:CusText.HALIGNMENT.AlignRight
                                textColor: "#222222"
                                anchors.verticalCenter: parent.verticalCenter
                                width: 69
                            }
                            CusSpinBox{
                                to:400
                                from: 25
                                width: 104
                                height: 32
                                anchors.verticalCenter: parent.verticalCenter
                                stepSize: 1
                                tipText: "范围25~400"
                                value: board.centerRate
                                onValueModified: {
                                    //board.setZdmotorCenterRate(0,value);
                                }
                            }
                            Item{
                                height: 1
                                width: 20
                            }
                        }
//                        Row{
//                            spacing: 10
//                            height: 52
//                            CusText{
//                                textContent:"清料振动时间:"
//                                fontSize: 16
//                                hAlignmentType:CusText.HALIGNMENT.AlignRight
//                                textColor: "#222222"
//                                anchors.verticalCenter: parent.verticalCenter
//                                width: 101
//                            }
//                            CusSpinBox{
//                                to:65535
//                                from: 0
//                                width: 104
//                                height: 32
//                                anchors.verticalCenter: parent.verticalCenter
//                            }
//                            Item{
//                                height: 1
//                                width: 20
//                            }
//                        }
                        Row{
                            spacing: 10
                            height: 52
                            CusText{
                                textContent:"振动频率:"
                                fontSize: 16
                                hAlignmentType:CusText.HALIGNMENT.AlignRight
                                textColor: "#222222"
                                anchors.verticalCenter: parent.verticalCenter
                                width: 69
                            }
                            CusSpinBox{
                                to:400
                                from: 25
                                width: 104
                                height: 32
                                anchors.verticalCenter: parent.verticalCenter
                                stepSize: 1
                                tipText: "范围25~400"
                                value: board.vibrationRate
                                onValueModified: {
                                    //board.setZdmotorCenterRate(0,value);
                                }
                            }
                            Item{
                                height: 1
                                width: 20
                            }
                        }
                        Row{
                            spacing: 10
                            height: 52
                            CusText{
                                textContent:"电压:"
                                fontSize: 16
                                hAlignmentType:CusText.HALIGNMENT.AlignRight
                                textColor: "#222222"
                                anchors.verticalCenter: parent.verticalCenter
                                width: 69
                            }
                            CusSpinBox{
                                to:260
                                from: 0
                                width: 104
                                height: 32
                                anchors.verticalCenter: parent.verticalCenter
                                stepSize: 1
                                tipText: "范围0~260"
                                value: board.voltage
                                onValueModified: {
                                    //board.setZdmotorVoltage()
                                }
                            }
                            Item{
                                height: 1
                                width: 20
                            }
                        }

                        Row{
                            spacing: 10
                            height: 52
                            CusText{
                                textContent:"出料速度:"
                                fontSize: 16
                                hAlignmentType:CusText.HALIGNMENT.AlignRight
                                textColor: "#222222"
                                anchors.verticalCenter: parent.verticalCenter
                                width: 69
                            }
                            CusSpinBox{
                                to:3200
                                from: 0
                                width: 104
                                height: 32
                                anchors.verticalCenter: parent.verticalCenter
                                stepSize: 1
                                tipText: "范围0~3200"
                                value: board.outputRate
                                onValueModified: {
                                    //board.setZdmotorCenterRate(0,value);
                                }
                            }
                            Item{
                                height: 1
                                width: 20
                            }
                        }
                    }
                }
                Row{
                    spacing: 10
                    height: 32
                    CusText{
                        textContent: "称重仪"
                        fontSize: 24
                        textColor: "#222222"
                        width: 96
                        height: 34
                        fontblod: true
                    }
                    Row{
                        spacing: 20
                        CusText{
                            textContent:"称重"
                            fontSize: 16
                            hAlignmentType:CusText.HALIGNMENT.AlignRight
                            textColor: "#222222"
                            anchors.verticalCenter: parent.verticalCenter
                            width: 32
                        }
                        CusInputText{
                            width: 70
                            height: 32
                            maxlength: 3
                            content: "50"
                            fontsize: 19
                            valignment: TextInput.AlignVCenter
                            halignment: TextInput.AlignHCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        CusRadusButton{
                            text: "校准"
                            backColor: "#222222"
                            radius: 4
                            width: 76
                            height: 32
                            fontsize: 18
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                }
            }
            Row{
                spacing: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                CusRadusButton{
                    text: CameraTaskWork.isStoped ||CameraTaskWork.isPause||CameraTaskWork.isStop
                          ? "开始":"暂停"
                    enabled:{
                        if(CameraTaskWork.isStop||CameraTaskWork.currentStatus!==0){
                            return false
                        }else{
                            return true
                        }
                    }
                    backgroundColorNormal: "#222222"
                    backgroundColorEnable:"#bfbfbf"
                    radius: 4
                    width: 96
                    height: 40
                    fontsize: 18
                    onClicked: {
                        if(CameraTaskWork.isStoped||CameraTaskWork.isPause||CameraTaskWork.isStop){
                            CameraTaskWork.start(true);
                        }else{
                            CameraTaskWork.start(false);
                        }
                    }
                }
                CusRadusButton{
                    enabled: CameraTaskWork.isPause || CameraTaskWork.isStart
                    text: "结束"
                    backgroundColorNormal: "#222222"
                    backgroundColorEnable:"#bfbfbf"
                    radius: 4
                    width: 96
                    height: 40
                    fontsize: 18
                    onClicked: {
                        CameraTaskWork.stop();
                    }
                }
                CusRadusButton{
                    text: !CameraTaskWork.isGraping ? "抓图":"抓图中"
                    enabled: CameraTaskWork.currentStatus!==0&&CameraTaskWork.isCalibrate&&!CameraTaskWork.isGraping
                    backgroundColorNormal: "#222222"
                    backgroundColorEnable:"#bfbfbf"
                    radius: 4
                    width: 96
                    height: 40
                    fontsize: 18
                    onClicked: {
                        Logger.d("抓图");
                        CameraTaskWork.grapImg();
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
                        CameraTaskWork.openDir();
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
                        saveConfigDialog.title="保存配置文件提示"
                        saveConfigDialog.contText="保存配置文件成功"
                        CameraProperty.saveCameraConfig();
                        board.saveCameraConfig();
                        saveConfigDialog.open();
                    }
                }
            }
        }
    }
    PageIndicator{
        id: indicator
        interactive: true
        count: view.count
        currentIndex: view.currentIndex
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        rotation: 90
    }
}

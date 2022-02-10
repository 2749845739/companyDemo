import QtQuick 2.12
import QtQuick.Controls 2.5
import "../../common"
import "../../"
Item {
    property int modelIndex: 0
    property bool stopShowImg: flowControl.boardStop
    property bool pauseShowImg: flowControl.boardPause
    property bool nosampleOrremainSample: false
    property bool forceStop: false
    CusDialog{
        id:pdialog
        anchors.centerIn: Overlay.overlay
        diatype:CusDialog.DIALOGENUM.SAVECONFIG
        buttonColor:"#967A50"
        headerColor:"#967A50"
        title: "提示"
        onAccepted: {
             close();
            swipeview.currentIndex=1;
            nosampleOrremainSample=false;
        }
    }
    Rectangle{
        id:detecImg
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin:10
        width: 1317
        height: 883
        color: "#eee9e3"
        radius: 10
        GridView{
            id:segView
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.top: parent.top
            anchors.topMargin: 15
            width: 1302
            height: 868
            clip: true
            cellWidth: 217
            cellHeight: 217
            delegate: wheat
            model: CusConfig.showSegmodel
            ScrollBar.vertical: ScrollBar{
            }
            onCountChanged: {
                positionViewAtEnd();
            }
        }
    }
    Item {
        anchors.left: detecImg.right
        anchors.right: parent.right
        height: parent.height
        Row{
            id:up
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 590
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            spacing: 10
            height: 50
            CusText{
                width: parent.width
                //anchors.verticalCenter: parent.verticalCenter
                hAlignmentType: CusText.HALIGNMENT.AlignHCenter
                height: 33
                textContent: "样品编号："+wheatSamplieid.item.sampleid
                fontSize: 24
                textColor: "#967A50"
            }
//            TextField{
//                id:sampleid
//                readOnly: true
//                text: wheatSamplieid.item.sampleid
//                height: 33
//                font.pixelSize:24
//                color: "#967A50"
//                background:Item{
//                }
//            }
//            CusText{
//                anchors.verticalCenter: parent.verticalCenter
//                height: 33
//                textContent: GlobParameter.getSampleid()
//                fontSize: 24
//                textColor: "#967A50"
//            }
//            CusButton_Image{
//                btnImgNormal: "qrc:/Image/image/user/edit.png"
//                btnImgHovered:"qrc:/Image/image/user/edit.png"
//                btnImgPressed:"qrc:/Image/image/user/edit.png"
//                width: 50
//                height: 50
//                onClicked: {
//                }
//            }
        }
        CusText{
            anchors.top: up.bottom
            anchors.topMargin: 102
            height: 33
            textContent: {
                if(flowControl.boardPause){
                    return "检测已暂停"
                }else if(flowControl.boardStoping||flowControl.boardStop){
                    return "检测正在结束"
                }else if(!flowControl.boardPause&&!flowControl.boardStoping&&!flowControl.boardStop){
                    return "检测中"
                }else{
                    return ""
                }
            }
            fontSize: 24
            anchors.horizontalCenter: parent.horizontalCenter
            textColor: "#967A50"
        }
        Row{
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 190
            anchors.horizontalCenter: parent.horizontalCenter
            height: 77
            spacing: 155
            Item{
                width: 84
                height: 77+29+9
                Column{
                    spacing: 9
                    CusButton_Image{
                        enabled: !flowControl.boardStoping
                        btnImgNormal: flowControl.boardStop|| flowControl.boardPause ? "qrc:/Image/image/user/start.png":"qrc:/Image/image/user/pause.png"
                        btnImgHovered:flowControl.boardStop|| flowControl.boardPause ? "qrc:/Image/image/user/start.png":"qrc:/Image/image/user/pause.png"
                        btnImgPressed:flowControl.boardStop|| flowControl.boardPause ? "qrc:/Image/image/user/start.png":"qrc:/Image/image/user/pause.png"
                        btnImgDisbaled: "qrc:/Image/image/user/pausedisable.png"
                        width: 77
                        height: 77
//                        onClicked: {
//                            if(flowControl.boardStop||flowControl.boardPause){
//                                flowControl.run();
//                            }else{
//                                flowControl.pause();
//                            }
//                        }
                    }
                    CusText{
                        width: 84
                        height: 29
                        fontSize: 21
                        textColor: "#967A50"
                        textContent: flowControl.boardStop|| flowControl.boardPause ?"继续检测":"暂停检测"
                        hAlignmentType: CusText.HALIGNMENT.AlignHCenter
                    }
                }
                MouseArea{
                    anchors.fill: parent
                    enabled: !flowControl.boardStoping
                    onClicked: {
                        if(flowControl.boardStop||flowControl.boardPause){
                            flowControl.run();
                        }else{
                            flowControl.pause();
                        }
                    }
                }
            }

            Item{
                width: 84
                height: 77+29+9
                Column{
                    spacing: 9
                    anchors.horizontalCenter: parent.horizontalCenter
                    CusButton_Image{
                        enabled: flowControl.boardPause||flowControl.boardStart
                        btnImgNormal: "qrc:/Image/image/user/stop.png"
                        btnImgHovered:"qrc:/Image/image/user/stop.png"
                        btnImgPressed:"qrc:/Image/image/user/stop.png"
                        btnImgDisbaled: "qrc:/Image/image/user/stopdisable.png"
                        width: 77
                        height: 77
//                        onClicked: {
//                            flowControl.stop();
//                        }
                    }
                    CusText{
                        width: 84
                        height: 29
                        fontSize: 21
                        textColor: "#967A50"
                        textContent:"停止检测"
                        hAlignmentType: CusText.HALIGNMENT.AlignHCenter
                    }
                }
                MouseArea{
                    enabled: flowControl.boardPause||flowControl.boardStart
                    anchors.fill: parent
                    onClicked: {
                        flowControl.stop();
                        forceStop=true;
                    }
                }
            }
        }
    }
    Component{
        id:wheat
        Item {
            width: 217
            height: 217
            Rectangle{
                anchors.left: parent.left
                anchors.top: parent.top
                //anchors.topMargin: 15
                width: 202
                height: 202
                color: "#000000"
                Image{
                    anchors.fill: parent
                    fillMode:Image.PreserveAspectFit
                    source: model.sourceImg
                }
            }
        }
    }
    Timer{
        id:showTimer
        interval: 150; running: false; repeat: true
        onTriggered: {
            if(segView.count>10000){
                CusConfig.segmentModel.clear();
                return;
            }
            if(modelIndex<CusConfig.segmentModel.count){
                CusConfig.showSegmodel.append(CusConfig.segmentModel.get(modelIndex));
                modelIndex++;
            }
        }
    }


    Connections{
        target: SegGrainRequireImage
        function onSegModelUpdate(index,type){
            CusConfig.addSegmentImg("image://SegImgprovider/"+index,type)
        }
    }
    Connections{
        target: ConsumerAlgorithmDataToUI
        function onSigFilishedRound(){
            if(!stopShowImg&&!pauseShowImg)
            showTimer.start();
        }
    }
    onStopShowImgChanged: {
        if(stopShowImg){
            showTimer.stop();
            modelIndex=0;
        }
    }
    onPauseShowImgChanged: {
        if(pauseShowImg){
            showTimer.stop();
        }else{
            showTimer.start();
        }
    }

    Connections{
        id:dynamicResult
        target: algorithmResult  //编译时找不到此类型会提示。qml好像支持后面把这个类型加进来（用他之前）
        enabled: true
        function onSigDynamicFinshed(){
            if(!nosampleOrremainSample){
                swipeview.currentIndex=3
                modelIndex=0;
                CusConfig.showSegmodel.clear();
                CusConfig.segmentModel.clear();
                if(!forceStop){
                    sqlSampleId.sqlQuery([algorithmResult.allRatio[0],
                                         algorithmResult.shengya[0],
                                         algorithmResult.chongshi[0],
                                         algorithmResult.posun[0],
                                         algorithmResult.shengmei[0],
                                         algorithmResult.binban[0],
                                         algorithmResult.chimei[0],
                                         algorithmResult.heipei[0]
                                         ]);
                }
                forceStop=false;
                maintaintitle.helpDialogShow=false;
                //board.flowLightEnable(true);
            }else{
                pdialog.open();
            }
        }
    }

    Connections{
        target: flowControl
        enabled: true
        function onSignoSample(){
            nosampleOrremainSample=true;
            pdialog.contText="请确认放入物料"
            //pdialog.open();
        }
        function onSigremainSample(){
            nosampleOrremainSample=true;
            pdialog.contText="请先清料"
            pdialog.open();
        }
        function onSigenable(){
            nosampleOrremainSample=false;
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

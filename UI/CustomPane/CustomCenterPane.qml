import QtQuick 2.12
import QtQuick.Controls 2.5
import "./CustomItem"
import "../common"
import "../Maintain"
import "../"
Item {
    property alias swpindex: swipeview.currentIndex
    SwipeView{
        id:swipeview
        anchors.fill: parent
        interactive: false
        Item {
            SelectGrainPane{
                //visible: !Login.isMainTain
                anchors.left: parent.left
                anchors.leftMargin: 150
                anchors.right: parent.right
                anchors.rightMargin: 150
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                lmodel: CusConfig.userPageModel
                lightImg:"qrc:/Image/image/user/lightSelected.png"
                onSelectGrain: {
                    if(index===1){
                        GlobParameter.setGrainType(index)
                        dirver.initAllParamter();
                        //visible=false
                        //bkgrd.visible=false
                        //customcenter.visible=true
                        boardStatus.visible=true
                        wheatSamplieid.active=true;
                        wheatDetection.active=true;
                        wheatResult.active=true;
                        wheatImgResult.active=true;
                        wheatRecord.active=true;
                        swipeview.currentIndex=1;
                    }
                }
            }
        }
        Item{
            Loader{
                id:wheatSamplieid
                active: false
                anchors.top: parent.top
                anchors.topMargin: 121
                anchors.bottom: parent.bottom
                width: parent.width
                //            anchors.bottom: parent.bottom
                //            width: parent.width
                source: "qrc:/CustomPane/CustomItem/CustomSampleId.qml"
                //            CustomSampleId{

                //            }
            }
        }

        Item{
            Loader{
                id:wheatDetection
                active: false
                anchors.top: parent.top
                anchors.topMargin: 121
                anchors.bottom: parent.bottom
                width: parent.width
                source: "qrc:/CustomPane/CustomItem/CustomDetection.qml"
                //            CustomDetection{
                //                anchors.bottom: parent.bottom
                //                width: parent.width
                //            }
            }
        }
        Item{
            Loader{
                id:wheatResult
                active: false
                anchors.top: parent.top
                anchors.topMargin: 121
                anchors.bottom: parent.bottom
                width: parent.width
                source: "qrc:/CustomPane/CustomItem/CustomDetectionResult.qml"
                //            CustomDetectionResult{
                //                anchors.bottom: parent.bottom
                //                width: parent.width
                //            }
            }
        }
        Item{
            Loader{
                id:wheatImgResult
                active: false
                anchors.top: parent.top
                anchors.topMargin: 121
                anchors.bottom: parent.bottom
                width: parent.width
                source: "qrc:/CustomPane/CustomItem/CustomImgResult.qml"
                //            CustomImgResult{
                //                anchors.bottom: parent.bottom
                //                width: parent.width
                //            }
            }
        }
        Item{
            Loader{
                id:wheatRecord
                active: true
                anchors.top: parent.top
                anchors.topMargin: 121
                anchors.bottom: parent.bottom
                width: parent.width
                source: "qrc:/CustomPane/CustomItem/CustomRecord.qml"
                //            CustomImgResult{
                //                anchors.bottom: parent.bottom
                //                width: parent.width
                //            }
            }
        }
    }
    MaintainTitlePane{
        id:maintaintitle
        anchors.top:parent.top
        width: parent.width
        height: 121
        onBackTextResult: {
            CusConfig.mergeResultImg.clear();
            wheatImgResult.item.resetBtn();
        }
    }
    Connections{
        target: flowControl
        enabled: true
        function onSigKeyPressed(){
            if(swipeview.currentIndex===1){
                flowControl.clearSegResult();
                flowControl.run();
                CusConfig.segmentModel.clear();
                CusConfig.showSegmodel.clear();
                GlobParameter.setSampleid();
                wheatSamplieid.item.sampleid=GlobParameter.getSampleid();
                swipeview.currentIndex=2;
            }else if(swipeview.currentIndex===2){
                if(!flowControl.boardStoping){
                    if(flowControl.boardStop||flowControl.boardPause){
                        flowControl.run();
                    }
                    if(swipeview.currentIndex===3){
                        flowControl.pause();
                    }
                }
            }
        }
    }
}

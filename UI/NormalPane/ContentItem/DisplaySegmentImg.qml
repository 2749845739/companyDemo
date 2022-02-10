import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml 2.12
import "../.."

Rectangle {
//    gradient: Gradient {
//        GradientStop { position: 0.0; color: "#dbddde" }
//        GradientStop { position: 1.0; color: "#5fc9f8" }
//    }
    color: "#010512"
    property int imgIndex: 0
    property int modelIndex: 0
    property bool isResult: false
     GridView{
         id:view
         visible: !isResult
         anchors.fill: parent
         anchors.margins: 20
         anchors.bottomMargin: 80

         clip: true

         model: CusConfig.showSegmodel

         cellWidth: 180
         cellHeight: 180

         delegate: segImg
         ScrollBar.vertical: ScrollBar{
             id:verScroBal
         }
         onCountChanged: {
             //view.currentIndex=CusConfig.segmentModel.count;
             verScroBal.position=1;
         }

     }
     Component{
         id:segImg
         Rectangle{
             width: 170
             height: 170
             color: "black"
             Image {
                 id: disimg
                 anchors.fill: parent
                 fillMode:Image.PreserveAspectFit
                 asynchronous:true
                 //visible: model.counts%50==0
                 source:model.sourceImg
                 GridView.onAdd: SequentialAnimation {
                     NumberAnimation { target: segImg; property: "scale"; from: 0; to: 1; duration: 150; easing.type: Easing.InOutQuad }
                 }
             }
         }


     }
     GridView{
         id:view02
         visible:isResult
         anchors.fill: parent
         anchors.margins: 20
         anchors.bottomMargin: 80

         clip: true

         model: CusConfig.showSegmodel

         cellWidth: 180
         cellHeight: 180

         delegate: resulrImg
         ScrollBar.vertical: ScrollBar{
             id:verBal
         }
//         onCountChanged: {
//             //view.currentIndex=CusConfig.segmentModel.count;
//             verScroBal.position=1;
//         }

     }
     Component{
         id:resulrImg
         Rectangle{
             width: 170
             height: 170
             color: "black"
//             Row{
//                 anchors.fill: parent
                 Image {
                     id: resOne
                     anchors.fill: parent
                     fillMode:Image.PreserveAspectFit
                     asynchronous:true
                     width: 170
                     height: 170
                     source: model.sourceOne
                 }
//                 Image {
//                     id: resTwo
//                     fillMode:Image.PreserveAspectFit
//                     asynchronous:true
//                     width: 85
//                     height: 170
//                     source: model.sourceTwo
//                 }
 //            }
         }
     }
     Timer {
         id:showTimer
         property int incress: 0
         interval: 150; running: false; repeat: true
         onTriggered:{
             if(CusConfig.segmentModel.count>10000){
                 return;
             }
             if(modelIndex<CusConfig.segmentModel.count){
                 CusConfig.showSegmodel.append(CusConfig.segmentModel.get(modelIndex));
                 modelIndex++;
             }
//             if(CusConfig.segmentModel.count>50){
//                 if(++modelIndex<CusConfig.segmentModel.count){
//                     incress++;
//                     CusConfig.showSegmodel.append(CusConfig.segmentModel.get(modelIndex));
//                    if(incress===50){
//                        showTimer.stop();
//                        //incress=0
//                    }
//                 }
//             }else if(CusConfig.segmentModel.count>0&&CusConfig.segmentModel.count<50){
//                 CusConfig.showSegmodel.append(CusConfig.segmentModel.get(modelIndex++));
//                if(modelIndex==CusConfig.segmentModel.count){
//                    showTimer.stop();
//                    //incress=0
//                }
//             }
         }
     }
     Connections{
         target: managerMath
//         onAddImgtoView:{
//             CusConfig.addSegmentImg("image://providerImg/"+index);
//             //imgIndex=index
//         }
     }
     Connections{
         target: managerMath
//         onStartGeiImage:{
//             //CusConfig.segmentModel.clear();
//             modelIndex=0;
//             //showTimer.incress=0;
//            // CusConfig.showSegmodel.clear();
//             if(!isStop)
//             showTimer.start();
////             for(var i=imgIndex;i<imgIndex+1;++i){
////                 CusConfig.showSegmodel.append(CusConfig.segmentModel.get(i));
////             }
////             imgIndex+=1;
//         }
     }
     function timerStop(){
         showTimer.stop();
         modelIndex=0;
     }
}

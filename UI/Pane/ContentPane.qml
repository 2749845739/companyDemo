import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQml 2.12
import "../common"
Item {
    id:window
    Grid {
        anchors.fill: parent
        anchors.margins: 1
        id:grid
        columns: 2
        //model: 4
        clip: true
        //interactive: false
        //cellWidth: width/2
        //cellHeight: height/2
        spacing: 1
        //delegate: Rectangle{
//            border.width: 1
//            border.color: "yellow"
//            color: "black"
           Rectangle{
               color: "black"
               border.width: 1
               border.color: "yellow"
               width: parent.width/2
               height: parent.height/2
               Image {
                   id:img1
                   anchors.top: parent.top
                   anchors.topMargin: 1
                   anchors.left: parent.left
                   anchors.leftMargin: 1
                   width: parent.width-2
                   height: parent.height-2
//                   cache: false
//                   mipmap: true
               }
           }

           Rectangle{
               color: "black"
               border.width: 1
               border.color: "yellow"
               width: parent.width/2
               height: parent.height/2
               Image {
                   id:img2
                   //asynchronous: true
                   anchors.top: parent.top
                   anchors.topMargin: 1
                   anchors.left: parent.left
                   anchors.leftMargin: 1
                   width: parent.width-2
                   height: parent.height-2
                   cache: false
                   mipmap: true
                   //source: "image://ViewProvider/0"
               }
           }
           Rectangle{
               color: "black"
               border.width: 1
               border.color: "yellow"
               width: parent.width/2
               height: parent.height/2
               Image {
                   id:img3
                   //asynchronous: true
                   anchors.top: parent.top
                   anchors.topMargin: 1
                   anchors.left: parent.left
                   anchors.leftMargin: 1
                   width: parent.width-2
                   height: parent.height-2
                   cache: false
                   mipmap: true
                   //source: "image://ViewProvider/0"
               }
           }
           Rectangle{
               color: "black"
               border.width: 1
               border.color: "yellow"
               width: parent.width/2
               height: parent.height/2
               Image {
                   id:img4
                   //asynchronous: true
                   anchors.top: parent.top
                   anchors.topMargin: 1
                   anchors.left: parent.left
                   anchors.leftMargin: 1
                   width: parent.width-2
                   height: parent.height-2
                   cache: false
                   mipmap: true
                   //source: "image://ViewProvider/0"
               }
           }
        }
//        Connections{
//            target: requireImageOne
//            enabled:true
//            onViewNeedUpdate:{
//                 //变图必须加index
//                if(index%2==0){
//                    img1.source = "image://ViewProviderOne/"+index
//                }else if(index%2==1){
//                    img3.source = "image://ViewProviderOne/"+index
//                }

////                img2.source = "image://ViewProvider/"+index
////                img3.source = "image://ViewProvider/"+index
////                img4.source = anchors.fill: parent"image://ViewProvider/"+index
//           }
//        }
//        Connections{
//            target: requireImageTwo
//            onViewNeedUpdate:{
//                 //变图必须加index
//                if(index%2==0){
//                 img2.source = "image://ViewProviderTwo/"+index
//                }else if(index%2==1){
//                 img4.source = "image://ViewProviderTwo/"+index
//                }

////                img2.source = "image://ViewProvider/"+index
////                img3.source = "image://ViewProvider/"+index
////                img4.source = "image://ViewProvider/"+index
//           }
//        }
}

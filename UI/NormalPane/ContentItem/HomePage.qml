import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml 2.12
import "../.."
Item{
    signal switchSampid();
    ListView {
        id: view
        anchors.fill: parent
        //anchors.margins: 20
        clip: true
        snapMode: ListView.SnapToItem
        model: CusConfig.homePageModel
        orientation:ListView.Horizontal
        delegate: grainType
        spacing: 20
        highlight: highlightComponent
        focus: true
        ScrollBar.horizontal: ScrollBar {
            id:horScroball
            size:1
            policy: ScrollBar.AlwaysOff
            //stepSize: size/100
        }
        currentIndex: -1
    }
    Component{
        id:highlightComponent
        Image {
            id: light
            source: "qrc:/Image/image/normal/light.png"
            width: sourceSize.width
            height: sourceSize.height
        }

    }

    Component{
       id:grainType
       Rectangle{
           //height: parent.height
           width: 267;
           height: 768
           color: "transparent"
               Button{
                   id:btndelegate
                   anchors.fill: parent
                   onClicked: {
                       view.currentIndex=index;
                       if(busyIndicator.running||model.indexId!==0) return;
                       CusConfig.grainType=model.name
                       managerMath.initMathModel(model.indexId);
                       busyIndicator.running=true;
                       busyIndicator.visible=true;
                       //view.currentIndex=index;
                       //switchSampid();
                   }
                   contentItem:Image {
                       anchors.fill: parent
                       source: "qrc:/Image/image/normal/light.png"
                       width: sourceSize.width
                       height: sourceSize.height
                       visible: btndelegate.hovered
                   }
                   background: Rectangle{
                       //anchors.fill: parent
                       color: "transparent"
                       Image{
//                       anchors.top: parent.top
//                       anchors.topMargin: 300
                       anchors.bottom: parent.bottom
                       anchors.bottomMargin: 80
                       anchors.horizontalCenter: parent.horizontalCenter
                       //color: "#ffffff"
                       //anchors.centerIn: parent
                       //anchors.fill: parent
                       source:  view.currentIndex===index ? model.sourceSelect:model.source
                       width: sourceSize.width
                       height: sourceSize.height
                   }
                   }
               }
//               border.width: 1
//               border.color: "#000000"
           //}
       }
    }

    Connections{
        enabled:true
        target: managerMath
        onCreateHanderResult:{
            busyIndicator.running=!flag;
            busyIndicator.visible=!flag;
            switchSampid();
        }
    }
    Connections{
        enabled:true
        target: managerMath
//        onReleaseHanderResult:{
//            busyIndicator.running=!flag;
//            busyIndicator.visible=!flag;
//        }
    }
}

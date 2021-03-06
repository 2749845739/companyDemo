import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQml 2.12
import "./Pane"
import "./common"
import "./NormalPane"
import "./Maintain"
import "./CustomPane"
Rectangle {
    id: rootBackground
    objectName: "rootBackground"
    color: "#F6F6F6"

//    SelectGrainPane{
//        visible: Login.isMainTain
//        anchors.left: parent.left
//        anchors.leftMargin: 150
//        anchors.right: parent.right
//        anchors.rightMargin: 150
//        anchors.top: parent.top
//        anchors.bottom: parent.bottom
//        lmodel: CusConfig.maintainPageModel
//        onSelectGrain: {
//            GlobParameter.setGrainType(1)
//            dirver.initAllParamter();
//            maintaincenter.visible=true
//            visible=false
//            bkgrd.visible=false
//        }
//    }
//    SelectGrainPane{
//        visible: !Login.isMainTain
//        anchors.left: parent.left
//        anchors.leftMargin: 150
//        anchors.right: parent.right
//        anchors.rightMargin: 150
//        anchors.top: parent.top
//        anchors.bottom: parent.bottom
//        lmodel: CusConfig.userPageModel
//        lightImg:"qrc:/Image/image/user/lightSelected.png"
//        onSelectGrain: {
//            GlobParameter.setGrainType(1)
//            dirver.initAllParamter();
//            visible=false
//            bkgrd.visible=false
//            customcenter.visible=true
//            boardStatus.visible=true
//        }
//    }
//    MaintainTitlePane{
//        id:maintaintitle
//        anchors.top:parent.top
//        width: parent.width
//        height: 121
//    }
    CustomBoardStatus{
        id:boardStatus
        visible: false
        anchors.left: parent.left
        anchors.leftMargin: 55
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 17
        width: parent.width
    }
//    width: 1024
//    height: 768
//    property bool normal: !login.superAdmin
    TitlePane{
        id:title
        visible: false
        anchors.top:parent.top
        width: parent.width
        height: 60
    }
    Loader{
//        item:LeftPane{
//            id:leftpane
//        }
        visible: false
//        anchors.left:parent.left
//        anchors.top:title.bottom
//        anchors.bottom:parent.bottom
//        Component.onCompleted: {
//        }
        source: "qrc:/Pane/LeftPane.qml"
        active: false
    }
    Loader{
//        item:RightPane{
//            id:rightPane
//            visible: false
//            anchors.top: title.bottom
//            anchors.right: parent.right
//            anchors.bottom: parent.bottom
//            width: 150
//            onOpensetting: {
//                loader.source=source;
//                loader.item.indexId=index;
//                drawer.open();
//            }
//        }
        source: "qrc:/Pane/RightPane.qml"
        visible: false
        active: false
    }
    MaintainCenterPane{
        id:maintaincenter
        visible: Login.isMainTain
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: parent.width
    }
    Loader{
        visible: false
        anchors.top:title.bottom
        height: parent.height-title.height-drawer.position*parent.height*0.4
//        item:ContentPane{
//            id:contentPane
//        }
        source: "qrc:/Pane/ContentPane.qml"
        active: false
    }
    Drawer{
        id:drawer
        visible: false
        modal: false
        clip: true
        height: parent.height*0.4
        interactive:true
        closePolicy:Popup.NoAutoClose
        edge:Qt.BottomEdge
        contentItem: Loader{
            //dosomething  leter update stackviw
            id:loader
            anchors.fill: parent
            source: "qrc:/setting/CameraSetting.qml"
            active: false
        }
        background: Rectangle{
            color:"#d2cfd0"
        }
    }
    Loader{
//        item:NormalCenterPane{
//            id:normalCenter
//            visible: normal
//            anchors.left: parent.left
//            //anchors.top:normalTitle.bottom
//            //anchors.bottom:parent.bottom
//            height: parent.height
//            width: parent.width
//        }
        active: false
        visible: false
        source: "qrc:/NormalPane/NormalCenterPane.qml"
    }


//    NormalTitlePane{
//        id:normalTitle
//        visible: normal
//        anchors.top:parent.top
//        anchors.left: parent.left
//        width: parent.width
//        height: 72
//    }
    DeviceStatus{
        id:mormalStatus
        visible: false
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width
        height: 32
    }
    CustomCenterPane{
        id:customcenter
        visible: !Login.isMainTain
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: boardStatus.top
        width: parent.width
    }
    CusBusyIndicator {
        id:busyIndicator
        x:parent.width/2-width/2
        y:parent.height/2-height/2
        visible: false
        running: false
        width: 128
        height: 128
        busyRadius: 8
        busyCount: 8
        busyColor: "#d50d4f";
    }
    Image {
        id: bkgrd
        visible: customcenter.swpindex===0
        anchors.fill: parent
        source: "qrc:/Image/image/maintain/background.png"
    }
}

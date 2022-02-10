import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import "../common"
import "./MaintainItem"
Item {
    implicitWidth: 1800
    implicitHeight: 1000
    property bool isUlignt: CameraTaskWork.currentStatus===1

    enum TASKSTATUS {
        UPLIGHTON,
        DOWNLIGHTON,
        CYCLEON
    }
    Row{    //TabBar有Bug
        id: bar
        anchors.left: parent.left
        anchors.leftMargin: 55
        anchors.right: parent.right
        anchors.rightMargin: 55
        anchors.top: parent.top
        anchors.topMargin: 20
        property int currentIndex : 0
        width: parent.width
        height: 98
        spacing: 0
        Repeater{  //tabbutton和tabbar位置不重合 qml bug
            model:["硬件参数","指标参数","账户设置","其他"]
            CusTabButton{
                onCurrentIndexChange: {
                    bar.currentIndex=index
                    bordershadow.canvas.requestPaint();
                }
            }
        }
        //        background: Rectangle{//            color: "transparent"
        //        }

        //        onCurrentIndexChanged: {
        //            //birdershadow.canvas.requestPaint();
        //        }
    }
    //    StackLayout{

    //    }
    onVisibleChanged: {
        bordershadow.canvas.requestPaint();
    }

    MaintainBorderShadow{
        id:bordershadow
        anchors.left: parent.left
        anchors.leftMargin: 55
        anchors.top: bar.bottom
        currentIndex: bar.currentIndex
        anchors.right: parent.right
        anchors.rightMargin: 110
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 65
        StackLayout{
            id:stack
            anchors.left: parent.left
            anchors.leftMargin: 25
            anchors.top:parent.top
            anchors.topMargin: 18+15 //15 radus
            anchors.right: parent.right
            //height: parent.height
            anchors.bottom: parent.bottom
            SwipeView{
                id:camerSettingView
                clip: true
                width: parent.width
                height: parent.height
                interactive: false
                MaintainHardwareSetting{
                    id:hardwares
                    property int taskStatus: MaintainContentPane.TASKSTATUS.CYCLEON
                }
                MaintainFlowCameraSetting{
                }
            }
        }
    }
    Button{
        id:changePage
        property bool camerarotation: false
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 40
        enabled: CameraTaskWork.isStoped && flowControl.boardStop && CameraTaskWork.currentStatus===0
        background: Image {
            id:btnimg
            source: CameraTaskWork.isStoped && flowControl.boardStop && CameraTaskWork.currentStatus===0
                    ? "qrc:/Image/image/maintain/arrow.png":"qrc:/Image/image/maintain/arrowUnable.png"
            width: sourceSize.width
            height: sourceSize.height
            rotation:changePage.camerarotation?180:0
            Behavior on rotation {
                NumberAnimation{
                    duration: 300
                }
            }
        }
        onClicked: {
            camerarotation=!camerarotation
            camerarotation?camerSettingView.currentIndex=1:camerSettingView.currentIndex=0
            camerarotation?dirver.dcdfStart():dirver.dcdfStop();
        }
    }
    Row{
        id:camerTask
        visible:stack.currentIndex===0&&camerSettingView.currentIndex===0?true:false
        anchors.bottom:parent.bottom
        anchors.bottomMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 55
        height: 26
        spacing: 10
        Item {
            id:uplight
            height: 22
            width: imgupl.width+textupl.width
            property bool select : false
            Row{
                //anchors.fill: parent
                height: parent.height
                spacing: 8
                Image {
                    id:imgupl
                    y:(parent.height-height)/2+7
                    source: CameraTaskWork.currentStatus===1&&CameraTaskWork.isCalibrate
                            ?"qrc:/Image/image/maintain/selected.png":"qrc:/Image/image/maintain/select.png"
                    width: sourceSize.width
                    height: sourceSize.height
                }
                CusText{
                    id:textupl
                    textContent: "上光源"
                    fontSize: 16
                    textColor: CameraTaskWork.changeMode && CameraTaskWork.isPause || CameraTaskWork.isStoped ? "#000000":"#bfbfbf"
                }
            }
            MouseArea{
                anchors.fill: parent
                enabled: CameraTaskWork.changeMode && CameraTaskWork.isPause || CameraTaskWork.isStoped
                onClicked: {
                    //cameraoneVflip=true;
                    if(CameraTaskWork.currentStatus===1){
                        CameraTaskWork.setCurrntStates(0)
                        hardwares.cameraoneD=true
                        hardwares.cameratwoU=true
                    }else{
                        CameraTaskWork.setCurrntStates(1)
                        hardwares.cameraoneD=true
                        hardwares.cameratwoU=true
                        hardwares.cameraoneU=true
                        hardwares.cameratwoD=true

                        hardwares.cameraoneD=false
                        hardwares.cameratwoU=false
                    }
//                    uplight.select=!uplight.select;
//                    downlight.select=false;
//                    cycle.select=false;
//                    uplight.select?:
                }
            }
        }
        Item {
            id:downlight
            height: 22
            width: imgdownl.width+textdownl.width
            property bool select : false
            Row{
                spacing: 8
                height: parent.height
                Image {
                    id:imgdownl
                    y:(parent.height-height)/2+7
                    source: CameraTaskWork.currentStatus===2&&CameraTaskWork.isCalibrate
                            ?"qrc:/Image/image/maintain/selected.png":"qrc:/Image/image/maintain/select.png"
                    width: sourceSize.width
                    height: sourceSize.height
                }
                CusText{
                    id:textdownl
                    textContent: "下光源"
                    fontSize: 16
                    textColor: CameraTaskWork.changeMode && CameraTaskWork.isPause || CameraTaskWork.isStoped ? "#000000":"#bfbfbf"
                }
            }
            MouseArea{
                anchors.fill: parent
                enabled: CameraTaskWork.changeMode && CameraTaskWork.isPause || CameraTaskWork.isStoped
                onClicked: {
                    //cameraoneVflip=true;
                    if(CameraTaskWork.currentStatus===2){
                        CameraTaskWork.setCurrntStates(0)
                        hardwares.cameraoneU=true
                        hardwares.cameratwoD=true
                    }else{
                        CameraTaskWork.setCurrntStates(2)
                        hardwares.cameraoneD=true
                        hardwares.cameratwoU=true
                        hardwares.cameraoneU=true
                        hardwares.cameratwoD=true

                        hardwares.cameraoneU=false
                        hardwares.cameratwoD=false
                    }
//                    downlight.select=!downlight.select
//                    uplight.select=false;
//                    cycle.select=false;
//                    downlight.select?CameraTaskWork.setCurrntStates(2):CameraTaskWork.setCurrntStates(0)
                }
            }
        }
        Item {
            id:cycle
            height: 22
            width: imgcyclel.width+textcyclel.width
            property bool select : false
            Row{
                spacing: 8
                height: parent.height
                Image {
                    id:imgcyclel
                    y:(parent.height-height)/2+7
                    source: CameraTaskWork.currentStatus===3&&CameraTaskWork.isCalibrate
                            ?"qrc:/Image/image/maintain/selected.png":"qrc:/Image/image/maintain/select.png"
                    width: sourceSize.width
                    height: sourceSize.height
                }
                CusText{
                    id:textcyclel
                    textContent: "循环点亮"
                    textColor: CameraTaskWork.changeMode && CameraTaskWork.isPause || CameraTaskWork.isStoped ? "#000000":"#bfbfbf"
                    fontSize: 16
                }
            }
            MouseArea{
                anchors.fill: parent
                enabled: CameraTaskWork.changeMode && CameraTaskWork.isPause || CameraTaskWork.isStoped
                onClicked: {
                    //cameraoneVflip=true;
//                    cycle.select=!cycle.select
//                    downlight.select=false
//                    uplight.select=false;
//                    cycle.select?CameraTaskWork.setCurrntStates(3):CameraTaskWork.setCurrntStates(0)
                    CameraTaskWork.currentStatus===3?CameraTaskWork.setCurrntStates(0):CameraTaskWork.setCurrntStates(3)
                    hardwares.cameraoneD=true
                    hardwares.cameratwoU=true
                    hardwares.cameraoneU=true
                    hardwares.cameratwoD=true
                }
            }
        }
    }

    Row{
        visible:stack.currentIndex===0&&camerSettingView.currentIndex===1?true:false
        anchors.bottom:parent.bottom
        anchors.bottomMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 55
        height: 32
        spacing: 88
        width: parent.width
        Row{
            spacing: 10
            height: 32
            CusText{
                fontSize: 18
                textColor: "#222222"
                textContent: "起始线"
                width: 54

            }
            CusSpinBox{
                to:200
                from: 10
                width: 104
                height: 32
                anchors.verticalCenter: parent.verticalCenter
                value:flowControl.startLine
                tipText: "范围10~200 单位(pixel)"
                onValueModified: {
                    flowControl.setStart_Line(value)
                }
            }
        }
        Row{
            spacing: 10
            height: 32
            CusText{
                fontSize: 18
                textColor: "#222222"
                textContent: "结束线"
                width: 54
            }
            CusSpinBox{
                to:1200
                from: 800
                width: 104
                height: 32
                value: flowControl.endLine
                tipText: "范围800~1200 单位(pixel)"
                anchors.verticalCenter: parent.verticalCenter
                onValueModified: {
                    flowControl.setEnd_Line(value)
                }
            }
        }
        Row{
            spacing: 10
            height: 32
            CusText{
                fontSize: 18
                textColor: "#222222"
                textContent: "检测区域"
                width: 72
            }
            CusSpinBox{
                to:100
                from: 20
                width: 104
                height: 32
                value: flowControl.targetArea
                tipText: "范围20~100 单位(pixel)"
                anchors.verticalCenter: parent.verticalCenter
                onValueModified: {
                    flowControl.setTarget_Area(value)
                }
            }
        }
        Row{
            spacing: 10
            height: 32
            CusText{
                fontSize: 18
                textColor: "#222222"
                textContent: "第一次开始时间"
                width: 126
            }
            CusSpinBox{
                to:20
                from: 5
                width: 104
                height: 32
                tipText: "范围5~20 单位(S)"
                value: flowControl.startTime
                anchors.verticalCenter: parent.verticalCenter
                onValueModified: {
                    flowControl.setFirstTime(value)
                }
            }
        }
        Row{
            spacing: 10
            height: 32
            CusText{
                fontSize: 18
                textColor: "#222222"
                textContent: "最后一次结束时间"
                width: 144
            }
            CusSpinBox{
                to:20
                from: 5
                width: 104
                height: 32
                tipText: "范围5~20 单位(S)"
                value: flowControl.endTime
                anchors.verticalCenter: parent.verticalCenter
                onValueModified: {
                    flowControl.setLastTime(value)
                }
            }
        }
//        Row{
//            spacing: 10
//            height: 32
//            CusText{
//                fontSize: 18
//                textColor: "#222222"
//                textContent: "最后一次结束时间"
//                width: 144
//            }
//            TextInput{
//               text:flowControl.endTime
//            }
//        }
    }
}

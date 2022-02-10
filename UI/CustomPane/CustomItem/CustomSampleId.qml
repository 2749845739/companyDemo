import QtQuick 2.12
import QtQuick.Controls 2.5
import "../../common"
import "../../"
Item {
    id:root
    property string sampleid:""
    property bool recyleStatus: true
    CusKeyboard{
        id:keyboard
        visible: false
        z:100
        onKeyBoard: {
            inputSampleId.textinput.insert(inputSampleId.textinput.cursorPosition,content)
        }
        onKeyBoardback: {
            inputSampleId.textinput.remove(inputSampleId.textinput.cursorPosition-1,inputSampleId.textinput.cursorPosition)
        }
    }

    CusDialog{
        id:tdialog
        title: "提示"
        contText: "无效样品编号"
        diatype:CusDialog.DIALOGENUM.SAVECONFIG
        buttonColor:"#967A50"
        headerColor:"#967A50"
        anchors.centerIn: Overlay.overlay
        onAccepted: {
            close();
        }
    }
    Row{
        id:sample
        anchors.left: parent.left
        anchors.leftMargin: 509
        anchors.top: parent.top
        anchors.topMargin: 330
        height: 99
        Image {
            width: sourceSize.width
            height: sourceSize.height
            source: "qrc:/Image/image/user/sampleid.png"
        }
        CusInputText{
            id:inputSampleId
            width: 595
            height: 80
            anchors.verticalCenter: parent.verticalCenter
            fontsize:32
            placeTextContent:"输入待测样品编号或者扫码枪"
            closebutton: true
        }
        CusButton_Image{
            anchors.verticalCenter: parent.verticalCenter
            btnImgUrl:"qrc:/Image/image/user/keyboard.png"
            width: 100
            height: 80
            onClicked: {
                keyboard.x=inputSampleId.mapToItem(root,0,0).x-(keyboard.width-inputSampleId.width)/2;
                keyboard.y=inputSampleId.mapToItem(root,0,0).y+inputSampleId.height+6
                keyboard.visible=true;
            }
        }
    }
    Column{
        anchors.top: sample.bottom
        anchors.left: parent.left
        anchors.leftMargin: 800
        spacing: 121
        CusText{
            fontSize: 24
            textColor: "#967A50"
            textContent: "待检谷物为"+CusConfig.selectedGrainName
            width: 168
            height: 33
        }
        CusRadusButton{
            id:sureBtn
            backgroundColorNormal:"#967A50"
            backgroundColorHovered:"#967A50"
            text: "开始检测"
            fontsize: 34
            //radius: 5
            width: 288
            height: 88
            onClicked: {
//                if(inputSampleId.content===""){
//                    //tdialog.open();
//                    sqlSampleId.querySamplid(inputSampleId.content);
//                }else{
                if(recyleStatus){
                    sqlSampleId.querySamplid(inputSampleId.content);
                    sampleid=GlobParameter.getSampleid();
                }else{
                    tdialog.contText="料仓未到指定位置";
                    tdialog.open();
                }
//                }
//                flowControl.clearSegResult();
//                swipeview.currentIndex=2;
//                flowControl.run();
//                CusConfig.segmentModel.clear();
//                CusConfig.showSegmodel.clear();
            }
        }
    }
    CusDialog{
        id:sdialog
        title: "提示"
        contText: "重复编号替换,是否继续"
        diatype:CusDialog.DIALOGENUM.QUITAPP
        buttonColor:"#967A50"
        headerColor:"#967A50"
        anchors.centerIn: Overlay.overlay
        onAccepted: {
            //board.flowLightEnable(true);
            flowControl.clearSegResult();
            swipeview.currentIndex=2;
            flowControl.run();
            CusConfig.segmentModel.clear();
            CusConfig.showSegmodel.clear();
            close();
        }
    }
    Connections{
        target: sqlSampleId
        function onSigRepeatId(flag){
            if(flag){
                sdialog.open();
            }else{
                //board.flowLightEnable(true);
                flowControl.clearSegResult();
                swipeview.currentIndex=2;
                flowControl.run();
                CusConfig.segmentModel.clear();
                CusConfig.showSegmodel.clear();
            }
        }
    }
    Connections{
        target: flowControl
        enabled: true
        function onSigRecyleStatus(flag){
            recyleStatus=flag;
        }
    }

}

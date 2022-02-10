import QtQuick 2.12
import QtQuick.Controls 2.12
import "../common"
import "../CustomPane/CustomItem"
Item {
    //color: "#F6F6F6";
    signal backTextResult();
    property real frontIndex: -1
    property alias helpDialogShow: helpDialog.visible
    CusDialog{
        id:quitdialog
        anchors.centerIn: Overlay.overlay
        diatype:CusDialog.DIALOGENUM.QUITAPP
        title: "退出提示"
        onAccepted: {
            view.close();
        }
    }
    CusDialog{
        id:closeSystemdialog
        anchors.centerIn: Overlay.overlay
        diatype:CusDialog.DIALOGENUM.QUITAPP
        title: "关机提示"
        onAccepted: {
            GlobParameter.closeSystem();
        }
    }
    CustomHelpDialog{
        id:helpDialog
        anchors.centerIn: Overlay.overlay
        visible: false
    }

    Row{
        anchors.left: parent.left
        anchors.leftMargin: 70
        anchors.top: parent.top
        anchors.topMargin: 46
        height: 46
        Image {
            id: logo
            source: Login.isMainTain?
                        "qrc:/Image/image/maintain/logomaintain.png":
                        "qrc:/Image/image/user/logo.png"
            width: sourceSize.width
            height: sourceSize.height
        }
        Rectangle{
            width:52
            height: 1
        }
        CusText{
            visible: Login.isMainTain
            hAlignmentType:CusText.HALIGNMENT.AlignHCenter
            //vAlignmentType:  CusText.VALIGNMENT.AlignBottom
            width: 141
            height: 46
            fontSize: 32
            textColor: "#222222"
            textContent: "AI快检仪"
            fontblod: true
        }
    }
    CusButton_Image {
        id: quit
        visible: Login.isMainTain
        enabled: flowControl.boardStop && CameraTaskWork.isStoped
        anchors.right: parent.right
        anchors.rightMargin: 75
        anchors.topMargin: 46
        anchors.top: parent.top
        btnImgNormal: "qrc:/Image/image/maintain/quit.png"
        btnImgHovered:"qrc:/Image/image/maintain/quit.png"
        btnImgPressed:"qrc:/Image/image/maintain/quit.png"
        btnImgDisbaled: "qrc:/Image/image/maintain/quitUnable.png"
        width: 54
        height: 48
        onClicked: {
            quitdialog.open();
        }
    }
    Row{
        visible: !Login.isMainTain
        spacing: 60
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.topMargin: 46
        anchors.top: parent.top

        CusButton_Image{
            visible:customcenter.swpindex===3||customcenter.swpindex===5
            btnImgNormal: "qrc:/Image/image/user/graintype.png"
            btnImgHovered:"qrc:/Image/image/user/graintype.png"
            btnImgPressed:"qrc:/Image/image/user/graintype.png"
            width: 50
            height: 50
            z:10
            onClicked: {
                //quitdialog.open();
                customcenter.swpindex=0
                //bkgrd.visible=true;
            }
        }

        CusButton_Image{
            visible:customcenter.swpindex===1||customcenter.swpindex===0
            btnImgNormal: "qrc:/Image/image/user/record.png"
            btnImgHovered:"qrc:/Image/image/user/record.png"
            btnImgPressed:"qrc:/Image/image/user/record.png"
            width: 50
            height: 50
            z:10
            onClicked: {
                //quitdialog.open();
                if(customcenter.swpindex===0){
                    wheatRecord.item.initTable(0,new Date(),new Date());
                    wheatRecord.item.ldate = new Date();
                    wheatRecord.item.rdate = new Date();
                    wheatRecord.item.sqlSampleidcontent="";
                }else{
                    //根据所选谷物种类来筛选
                    wheatRecord.item.initTable(0,new Date(),new Date());
                    // qml 外部不能根据id索引id
//                    wheatRecord.item.cuscalendar.caleft.selectedDate = new Date();
//                    wheatRecord.item.cuscalendar.caright.selectedDate = new Date();
                    wheatRecord.item.ldate = new Date();
                    wheatRecord.item.rdate = new Date();
                    wheatRecord.item.sqlSampleidcontent="";
                }

                frontIndex=customcenter.swpindex;
                customcenter.swpindex=5;
                //根据所选谷物种类
                wheatRecord.item.grainname=0;
            }
        }

        CusButton_Image {
            id: back
            visible: customcenter.swpindex===4||customcenter.swpindex===1||customcenter.swpindex===5
            btnImgNormal: "qrc:/Image/image/user/back.png"
            btnImgHovered:"qrc:/Image/image/user/back.png"
            btnImgPressed:"qrc:/Image/image/user/back.png"
            btnImgDisbaled: "qrc:/Image/image/user/back.png"
            width: 50
            height: 50
            onClicked: {
                    if(customcenter.swpindex===4) backTextResult();
                    //customcenter.swpindex===5?customcenter.swpindex=3:
                    if(customcenter.swpindex===5){
                        customcenter.swpindex=frontIndex;
                    }else{
                        customcenter.swpindex=customcenter.swpindex-1;
                    }
            }
        }

        CusButton_Image{
            visible:customcenter.swpindex!==2
            btnImgNormal: "qrc:/Image/image/user/quit.png"
            btnImgHovered:"qrc:/Image/image/user/quit.png"
            btnImgPressed:"qrc:/Image/image/user/quit.png"
            width: 50
            height: 50
            z:10
            onClicked: {
                quitdialog.buttonColor="#967A50"
                quitdialog.headerColor="#967A50"
                quitdialog.open();
            }
        }
        CusButton_Image{
            btnImgNormal: "qrc:/Image/image/user/help.png"
            btnImgHovered:"qrc:/Image/image/user/help.png"
            btnImgPressed:"qrc:/Image/image/user/help.png"
            width: 50
            height: 50
            z:10
            onClicked: {
                helpDialog.open();
            }
        }
        CusButton_Image{
            visible:customcenter.swpindex!==2
            btnImgNormal: "qrc:/Image/image/user/closeSystem.png"
            btnImgHovered:"qrc:/Image/image/user/closeSystem.png"
            btnImgPressed:"qrc:/Image/image/user/closeSystem.png"
            width: 50
            height: 50
            z:10
            onClicked: {
                closeSystemdialog.buttonColor="#967A50"
                closeSystemdialog.headerColor="#967A50"
                closeSystemdialog.contText="确定关机?"
                closeSystemdialog.open();
            }
        }

    }

}

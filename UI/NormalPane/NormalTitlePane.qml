import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml 2.12
import "../common"
import "../"
import "ContentItem"
Item{
    property alias homeEnable: home.enabled
    property alias titleBackground: titleBackground
    HelpDialog{
        id:helppane
        visible: false
    }
    CusDialog{
        id:dialogNormal
        anchors.centerIn: Overlay.overlay
        visible: false
        height: 100
        width: 200
        title: "退出程序"
        onAccepted: {
            view.close();
        }
        closePolicy: Popup.NoAutoClose
    }
    Rectangle{
        id:titleBackground
        anchors.fill: parent
        color: "transparent"
        Row{
            anchors.left: parent.left
            anchors.leftMargin: 120
            //height: 72
            anchors.verticalCenter: parent.verticalCenter
            spacing: 24
            width: 400
            Image{
                id:log
                //anchors.right: parent.right
                width:sourceSize.width
                height: sourceSize.height
                source:"qrc:/Image/image/normal/logo.png"
            }
            Text {
                text: "粮食质量分析快检仪 -"+CusConfig.grainType
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 14
                color: "white"
            }
        }

        Row{
            id:tools
            anchors.rightMargin: 102
            //height: 72
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            spacing: 35
            CusButton_Image{
                id:home
                //anchors.right: parent.right
                enabled: CusConfig.homeEnable
                width: 32
                height: 32
                btnImgDisbaled: "qrc:/Image/image/normal/home_disable.png"
                btnImgNormal: "qrc:/Image/image/normal/home_normal.png"
                btnImgHovered: "qrc:/Image/image/normal/home_normal.png"
                btnImgPressed: "qrc:/Image/image/normal/home_normal.png"
//                btnImgUrl: hovered||pressed ? "qrc:/Image/image/normal/home_hover.png":"qrc:/Image/image/normal/home_normal.png"
                tipText: "主页"
                onClicked: {
                    CusConfig.showSegmodel.clear();
                    CusConfig.segmentModel.clear();
                    //managerMath.clearImg();
                    normalCenter.setCurrentIndex(0);
                    busyIndicator.running=true;
                    busyIndicator.visible=true;
                    managerMath.releaseModel();
                    CusConfig.homeEnable=false;
                    //resultPane.reset();
                    normalCenter.resetResult();
                }
            }
//            CusButton_Image{
//                id:swichUser
//                //anchors.right: parent.right
//                width: 32
//                height: 32
//                btnImgUrl: hovered||pressed ? "qrc:/Image/image/normal/yonghu_horver.png":"qrc:/Image/image/normal/yonghu_normal.png"
//                tipText: "切换到管理员界面"
//                onClicked: {
//                    //dialog.open();
//                }
//            }
            CusButton_Image{
                id:help
                //anchors.right: parent.right
                width: 32
                height: 32
                btnImgNormal:"qrc:/Image/image/normal/help_normal.png"
                btnImgHovered: "qrc:/Image/image/normal/help_normal.png"
                btnImgDisbaled: "qrc:/Image/image/normal/help_normal.png"
                btnImgPressed: "qrc:/Image/image/normal/help_normal.png"
//                btnImgUrl: hovered||pressed ? "qrc:/Image/image/normal/help_hover.png":"qrc:/Image/image/normal/help_normal.png"
                tipText: "帮助"
                onClicked: {
                    //dialog.open();
                   helppane.open();
                }
            }
//            CusButton_Image{
//                id:exit
//                //anchors.right: parent.right
//                width: 32
//                height: 32
//                btnImgUrl: hovered||pressed ? "qrc:/Image/image/normal/tuichu_hover.png":"qrc:/Image/image/normal/tuichu_normal.png"
//                tipText: "退出"
//                onClicked: {
//                    //dialog.open();
//                }
//            }
            CusButton_Image{
                id:close
                //anchors.right: parent.right
                width: 32
                height: 32
                btnImgUrl: hovered||pressed ? "qrc:/Image/image/normal/close_normal.png":"qrc:/Image/image/normal/close_normal.png"
                tipText: "关闭"
                onClicked: {
                    dialogNormal.open();
                }
            }
        }
        Item {
            id: blankItem
            objectName: "blankItem"
            height: parent.height
            anchors.left: parent.left
            anchors.right:tools.left
            Component.onCompleted: {
                view.setTitleItem(blankItem)
            }
            MouseArea{
                anchors.fill: parent
                property int lastX: 0
                property int lastY: 0
                onContainsPressChanged: {
                    if(containsPress){
                        cursorShape = Qt.SizeAllCursor
                        lastX = mouseX
                        lastY = mouseY
                    }else {
                        cursorShape = Qt.ArrowCursor
                    }
                }
                onPositionChanged: {
                    if(pressed){
                        if ((mouseX - lastX) !== 0 || (mouseY - lastY) !== 0)
                        {
                            view.x+=mouseX - lastX;
                            view.y+=mouseY - lastY;
                        }
                    }
                }
            }
        }
    }
}

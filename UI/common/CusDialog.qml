import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml 2.12
import QtGraphicalEffects 1.12
Dialog {
    id: dialog
    property color headerColor: "#222222"
    property color buttonColor: "#222222"
    enum DIALOGENUM {
        QUITAPP=0,
        EXPRRTEXECL,
        SAVECONFIG
    }
    property int diatype: CusDialog.DIALOGENUM.QUITAPP
    property alias contText: content.textContent
//    property alias fontSize: content.fontSize
    implicitWidth: 719
    implicitHeight: 373
    closePolicy : Popup.NoAutoClose
    modal:true
    focus: true
    header:Rectangle{
        height: 103
        color: headerColor
        CusText {
            anchors.centerIn: parent
            hAlignmentType:CusText.HALIGNMENT.AlignHCenter
            textContent: title
            textColor: "white"
            fontSize: 38
        }
    }
    background: Rectangle{
            anchors.fill: parent
            color: "#F6F6F6"
            radius: 5
            layer.enabled: true
            layer.effect: DropShadow {
                transparentBorder: true
                horizontalOffset: 4
                verticalOffset: 4
                samples: 15
                smooth: true
                cached: true
            }
        }
    contentItem: Item {
        anchors.fill: parent
        Column{
            x:(parent.width-width)/2
            y: dialog.height-103-height/2
            //+header
            width: 500
            height: 150
            spacing: 78
            CusText{
                id:content
                anchors.horizontalCenter: parent.horizontalCenter
                hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                textContent: "退出程序"
                textColor: "#222222"
                fontSize: 24
            }
            Row{
                visible: diatype===CusDialog.DIALOGENUM.QUITAPP
                anchors.horizontalCenter: parent.horizontalCenter
                //anchors.centerIn: parent
                spacing: 30
                    height: sureBtn.height+2
                    CusRadusButton{
                        id:sureBtn
                        backgroundColorNormal:buttonColor
                        backgroundColorHovered:buttonColor
                        text: "确定"
                        fontsize: 18
                        //radius: 5
                        width: 106
                        height: 47
                        onClicked: {
                            dialog.accepted()
                        }
                    }
                CusRadusButton{
                    id:cancleBtn
                    backgroundColorNormal:buttonColor
                    backgroundColorHovered:buttonColor
                    text: "取消"
                    fontsize: 18
                    //radius: 5
                    width: 106
                    height: 47
                    onClicked: {
                       dialog.close();
                    }
                }
            }
            Row{
                visible: diatype===CusDialog.DIALOGENUM.SAVECONFIG
                anchors.horizontalCenter: parent.horizontalCenter
                CusRadusButton{
                    backgroundColorNormal:buttonColor
                    backgroundColorHovered:buttonColor
                    text: "确定"
                    fontsize: 18
                    width: 106
                    height: 47
                    onClicked: {
                        dialog.accepted()
                    }
                }
            }

//            Column{
//                x:(parent.width-width)/2
//                y:(parent.height-height)/2
//                width: parent.width
//                visible: diatype===CusDialog.DIALOGENUM.EXPRRTEXECL
//                spacing: 60
//                CusText{
//                    id:content
//                    y:60
//                    width: parent.width
//                    wrap:Text.WordWrap
//                    fontSize: 10
//                    textColor: "white"
//                    textContent: "导出路径:"
//                    hAlignmentType: CusText.HALIGNMENT.AlignHCenter
//                    vAlignmentType: CusText.VALIGNMENT.AlignVCenter
//                }
//                Row{
//                    anchors.horizontalCenter: parent.horizontalCenter
//    //                anchors.verticalCenter: parent.verticalCenter
//                    spacing: 10
//                    RadusBoder{
//                        radus: 5
//                        width: 60+2
//                        height: btnC.height+2
//                    CusRadusButton{
//                        id:btnC
//                        anchors.left: parent.left
//                        anchors.leftMargin: 1
//                        anchors.top: parent.top
//                        anchors.topMargin: 1
//                        backgroundColorNormal:"#010512"
//                        backgroundColorHovered:"#010512"
//                        text: "确定"
//                        //radius: 5
//                        width: 60
//                        onClicked: {
//                            dialog.close();
//                        }
//                    }
//                    }
//                }
//            }
        }
    }
    enter: Transition {
        ParallelAnimation {
            NumberAnimation {
                target: dialog
                properties: "opacity"
                from: 0
                to: 1
                duration: 200
            }
            NumberAnimation {
                target: dialog
                properties: "width"
                from: 0
                to: width
                duration: 200
            }
            NumberAnimation {
                target: dialog
                properties: "height"
                from: 0
                to: height
                duration: 200
            }
        }
    }

    exit: Transition {
        NumberAnimation {
            target: dialog
            properties: "opacity"
            from:1
            to: 0
            duration: 200
        }
    }
    Component{
        id:buttonDelegate
        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            spacing: 10
            CusRadusButton{
                backgroundColorNormal:"#ffffff"
                backgroundColorHovered:"#cdcdcd"
                text: "确定"
                radius: 5
                width: 60
                onClicked: {
                    dialog.accepted()
                }
            }
            CusRadusButton{
                backgroundColorNormal:"#ffffff"
                backgroundColorHovered:"#cdcdcd"
                text: "取消"
                radius: 5
                width: 60
                onClicked: {
                   dialog.rejected();
                }
            }
        }
    }

    //        OpacityAnimator{
    //            target: dialog
    //            to: 1
    //            duration: 1000
    //        }
    //        NumberAnimation {
    //            target: dialog
    //            properties: "scale"
    //            to: 1
    //            duration: 500
    //        }


    //    onAccepted: console.log("Ok clicked")
    //    onRejected: console.log("Cancel clicked")
}

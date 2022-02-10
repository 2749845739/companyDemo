import QtQuick 2.15
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.12
import "../../common"
import "../../"
Popup {
    id:root
    implicitHeight: 746
    implicitWidth: 1438
    closePolicy : Popup.NoAutoClose
    modal:true
    focus: true
    contentItem: Item{
        anchors.fill: parent
        Button {
            id: closeBtn
            width: 48
            height: 48
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.rightMargin: 8
            contentItem:Item{
                Image {
                    id:leftimg
                    //anchors.centerIn: parent
                    source: "qrc:/Image/image/user/closeDialog.png"
                    width: sourceSize.width
                    height: sourceSize.height
                    visible: false
                }
                ColorOverlay{
                    anchors.centerIn: parent
                    source: leftimg
                    width: leftimg.width
                    height: leftimg.height
                    cached: true
                    color: "#967A50"
                }
            }
            onClicked: {
                root.close();
            }
            background: Rectangle{
                color: "transparent"
            }
        }
        Column{
            id:leftTools
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 76
            anchors.topMargin: 50
            width: childrenRect.width
            spacing: 10
            //height: childrenRect.height
            CusRadusButton{
                id:czzl
                selected:true
                backgroundColorNormal:"transparent"
                backgroundColorSelected:"#967A50"
                backgroundColorHovered: "transparent"
                text: "操作指南"
                fontsize: 23
                textColor: selected?"#FFFFFF":"#967A50"
                width: 136
                height: 60
                onClicked: {
                    selected=true;
                    cjwt.selected=false;
                    gysb.selected=false;
                    lxwm.selected=false;
                    one.visible=true;
                    two.visible=false;
                    three.visible=false;
                    four.visible=false;
                }
            }
            CusRadusButton{
                id:cjwt
                backgroundColorNormal:"transparent"
                backgroundColorSelected:"#967A50"
                backgroundColorHovered: "transparent"
                text: "常见问题"
                fontsize: 23
                textColor: selected?"#FFFFFF":"#967A50"
                width: 136
                height: 60
                onClicked: {
                    selected=true;
                    czzl.selected=false;
                    gysb.selected=false;
                    lxwm.selected=false;
                    one.visible=false;
                    two.visible=true;
                    three.visible=false;
                    four.visible=false;
                }
            }
            CusRadusButton{
                id:gysb
                backgroundColorNormal:"transparent"
                backgroundColorSelected:"#967A50"
                backgroundColorHovered: "transparent"
                text: "关于设备"
                fontsize: 23
                textColor: selected?"#FFFFFF":"#967A50"
                width: 136
                height: 60
                onClicked: {
                    selected=true;
                    cjwt.selected=false;
                    czzl.selected=false;
                    lxwm.selected=false;
                    one.visible=false;
                    two.visible=false;
                    three.visible=true;
                    four.visible=false;
                }
            }
            CusRadusButton{
                id:lxwm
                backgroundColorNormal:"transparent"
                backgroundColorSelected:"#967A50"
                backgroundColorHovered: "transparent"
                text: "联系我们"
                fontsize: 23
                textColor: selected?"#FFFFFF":"#967A50"
                width: 136
                height: 60
                onClicked: {
                    selected=true;
                    cjwt.selected=false;
                    gysb.selected=false;
                    czzl.selected=false;
                    one.visible=false;
                    two.visible=false;
                    three.visible=false;
                    four.visible=true;
                }
            }
        }
        Item {
            id: one
            anchors.left: leftTools.right
            anchors.top: parent.top
            anchors.topMargin: 50
            Rectangle{
                id:dl
                anchors.left: parent.left
                anchors.leftMargin: 310
                anchors.top: parent.top
                radius: 2
                border.width: 2
                border.color: "#967A50"
                width: 223
                height: 66
                CusText{
                    anchors.centerIn: parent
                    textColor: "#967A50"
                    textContent: "登录"
                    fontSize: 18
                    hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                }
                color: "transparent"
            }
            Rectangle{
                id:gwxz
                anchors.left: parent.left
                anchors.leftMargin: 310
                anchors.top: dl.bottom
                anchors.topMargin: 35
                radius: 2
                border.width: 2
                border.color: "#967A50"
                width: 223
                height: 66
                CusText{
                    anchors.centerIn: parent
                    hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                    textColor: "#967A50"
                    textContent: "谷物选择"
                    fontSize: 18
                }
                color: "transparent"
            }
            Rectangle{
                id:fyp
                anchors.left: parent.left
                anchors.leftMargin: 187
                anchors.top: gwxz.bottom
                anchors.topMargin: 35
                radius: 2
                border.width: 2
                border.color: "#967A50"
                width: 223
                height: 66
                CusText{
                    anchors.centerIn: parent
                    textColor: "#967A50"
                    textContent: "放样品\n(20~100g)"
                    fontSize: 18
                    hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                }
                color: "transparent"
            }
            Rectangle{
                anchors.left: fyp.right
                anchors.leftMargin: 40
                anchors.top: gwxz.bottom
                anchors.topMargin: 35
                radius: 2
                border.width: 2
                border.color: "#967A50"
                width: 223
                height: 66
                CusText{
                    anchors.centerIn: parent
                    textColor: "#967A50"
                    textContent: "样品编号"
                    fontSize: 18
                    hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                }
                color: "transparent"
            }
            Rectangle{
                id:ksjc
                anchors.left: parent.left
                anchors.leftMargin: 310
                anchors.top: fyp.bottom
                anchors.topMargin: 35
                radius: 2
                border.width: 2
                border.color: "#967A50"
                width: 223
                height: 66
                CusText{
                    anchors.centerIn: parent
                    textColor: "#967A50"
                    textContent: "开始检测"
                    fontSize: 18
                    hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                }
                color: "transparent"
            }
            Rectangle{
                id:jcz
                anchors.left: parent.left
                anchors.leftMargin: 310
                anchors.top: ksjc.bottom
                anchors.topMargin: 35
                radius: 2
                border.width: 2
                border.color: "#967A50"
                width: 223
                height: 66
                CusText{
                    anchors.centerIn: parent
                    textColor: "#967A50"
                    textContent: "检测中"
                    fontSize: 18
                    hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                }
                color: "transparent"
            }
            Rectangle{
                id:jcjs
                anchors.left: parent.left
                anchors.leftMargin: 310
                anchors.top: jcz.bottom
                anchors.topMargin: 35
                radius: 2
                border.width: 2
                border.color: "#967A50"
                width: 223
                height: 66
                CusText{
                    anchors.centerIn: parent
                    textColor: "#967A50"
                    textContent: "检测结束"
                    fontSize: 18
                    hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                }
                color: "transparent"
            }
            Rectangle{
                id:ckjctp
                anchors.left:jcz.right
                anchors.leftMargin: 98
                anchors.top: parent.top
                anchors.topMargin: 350
                radius: 2
                border.width: 2
                border.color: "#967A50"
                width: 178
                height: 54
                Column{
                    anchors.centerIn: parent
                    CusText{
                        height: 25
                        textColor: "#967A50"
                        textContent: "查看检测照片"
                        fontSize: 18
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                    }
                    CusText{
                        height: 25
                        textColor: "#967A50"
                        textContent: "（点击查看不完善粒图片）"
                        fontSize: 14
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                    }
                }
                color: "transparent"
            }

            Rectangle{
                id:dy
                anchors.left:jcz.right
                anchors.leftMargin: 98
                anchors.top: ckjctp.bottom
                anchors.topMargin: 20
                radius: 2
                border.width: 2
                border.color: "#967A50"
                width: 178
                height: 54
                Column{
                    anchors.centerIn: parent
                    CusText{
                        height: 25
                        textColor: "#967A50"
                        textContent: "打印"
                        fontSize: 18
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                    }
                    CusText{
                        height: 25
                        textColor: "#967A50"
                        textContent: "（单次结果）"
                        fontSize: 14
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                    }
                }
                color: "transparent"
            }
            Rectangle{
                id:cklsjl
                anchors.left:jcz.right
                anchors.leftMargin: 98
                anchors.top: dy.bottom
                anchors.topMargin: 20
                radius: 2
                border.width: 2
                border.color: "#967A50"
                width: 178
                height: 54
                Column{
                    anchors.centerIn: parent
                    CusText{
                        height: 25
                        textColor: "#967A50"
                        textContent: "查看历史记录"
                        fontSize: 18
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                    }
                    CusText{
                        height: 25
                        textColor: "#967A50"
                        textContent: "（可查询和导出）"
                        fontSize: 14
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                    }
                }
                color: "transparent"
            }
            Rectangle{
                id:hsyp
                anchors.left:jcz.right
                anchors.leftMargin: 98
                anchors.top: cklsjl.bottom
                anchors.topMargin: 20
                radius: 2
                border.width: 2
                border.color: "#967A50"
                width: 178
                height: 54
                CusText{
                    anchors.centerIn: parent
                    textColor: "#967A50"
                    textContent: "回收样品"
                    fontSize: 18
                    hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                }
                color: "transparent"
            }
            Rectangle{
                id:xyljc
                anchors.left: dy.right
                anchors.leftMargin: 48
                anchors.top: parent.top
                anchors.topMargin: 470
                radius: 2
                border.width: 2
                border.color: "#967A50"
                width: 223
                height: 66
                CusText{
                    anchors.centerIn: parent
                    textColor: "#967A50"
                    textContent: "新一轮检测"
                    fontSize: 18
                    hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                }
                color: "transparent"
            }
        }
        Item {
            id: two
            anchors.left: leftTools.right
            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            visible: false
            CusText{
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                width: 216
                height: 50
                textColor: "#967A50"
                textContent: "常见问题处理"
                fontSize: 36
                hAlignmentType:CusText.HALIGNMENT.AlignHCenter
            }
            CusText{
                id:cjwtone
                anchors.left: parent.left
                anchors.leftMargin: 127
                anchors.top: parent.top
                anchors.topMargin: 140
                fontSize: 21
                textColor: "#967A50"
                textContent: "1）查询之前检测的数据，怎么操作？"
                width: 529
                height: 30
            }
            CusText{
                id:cjwttwo
                anchors.left: parent.left
                anchors.leftMargin: 127
                anchors.top: cjwtone.bottom
                anchors.topMargin: 28
                fontSize: 21
                textColor: "#967A50"
                textContent: "点击历史记录按钮，输入样本编号或者选择日期范围后，点击查询即可"
                width: 610
                height: 62
                wrap:Text.WordWrap
            }
            CusText{
                id:cjwtthree
                anchors.left: parent.left
                anchors.leftMargin: 127
                anchors.top: cjwttwo.bottom
                anchors.topMargin: 80
                fontSize: 21
                textColor: "#967A50"
                textContent: "2）打印不出来，怎么办？"
                width: 529
                height: 30
            }
            CusText{
                anchors.left: parent.left
                anchors.leftMargin: 127
                anchors.top: cjwtthree.bottom
                anchors.topMargin: 30
                fontSize: 21
                textColor: "#967A50"
                textContent: "检查打印纸是否用完，检查打印机与设备之间的连线是否松脱"
                width: 540
                height: 30
            }
        }
        Item {
            id: three
            visible: false
            anchors.left: leftTools.right
            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            CusText{
                id:gysbtone
                anchors.left: parent.left
                anchors.leftMargin: 127
                anchors.top: parent.top
                anchors.topMargin: 140
                fontSize: 21
                textColor: "#967A50"
                textContent: "产品型号：GQ-P600"
                width: 520
                height: 30
            }
            CusText{
                id:gysbtwo
                anchors.left: parent.left
                anchors.leftMargin: 127
                anchors.top: gysbtone.bottom
                anchors.topMargin: 28
                fontSize: 21
                textColor: "#967A50"
                textContent: "软件版本号：1.0.0"
                width: 520
                height: 30
                wrap:Text.WordWrap
            }
            CusText{
                id:gysbthree
                anchors.left: parent.left
                anchors.leftMargin: 127
                anchors.top: gysbtwo.bottom
                anchors.topMargin: 28
                fontSize: 21
                textColor: "#967A50"
                textContent: "模型版本号：0.1.1"
                width: 520
                height: 30
                wrap:Text.WordWrap
            }
        }
        Item {
            id: four
            visible: false
            anchors.left: leftTools.right
            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            CusText{
                id:lxwmone
                anchors.left: parent.left
                anchors.leftMargin: 127
                anchors.top: parent.top
                anchors.topMargin: 140
                fontSize: 21
                textColor: "#967A50"
                textContent: "公司地址： 安徽省合肥市高新区创新产业园二期G3栋A座3楼"
                width: 520
                height: 30
            }
            CusText{
                id:lxwmtwo
                anchors.left: parent.left
                anchors.leftMargin: 127
                anchors.top: lxwmone.bottom
                anchors.topMargin: 28
                fontSize: 21
                textColor: "#967A50"
                textContent: "售后电话：400-808-8807"
                width: 520
                height: 30
                wrap:Text.WordWrap
            }
            CusText{
                id:lxwmthree
                anchors.left: parent.left
                anchors.leftMargin: 127
                anchors.top: lxwmtwo.bottom
                anchors.topMargin: 28
                fontSize: 21
                textColor: "#967A50"
                textContent: "邮箱：service@gaozhe.com.cn"
                width: 520
                height: 30
                wrap:Text.WordWrap
            }
            Image {
                anchors.left: parent.left
                anchors.leftMargin: 450
                anchors.top: lxwmthree.bottom
                anchors.topMargin: 120
                source: "qrc:/Image/image/user/gz.png"
                width: sourceSize.width
                height: sourceSize.height
            }
        }
    }

    background: Rectangle{
        color: "#EBECF0"
        radius: 8
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
    enter: Transition {
        ParallelAnimation {
            NumberAnimation {
                target: root
                properties: "opacity"
                from: 0
                to: 1
                duration: 200
            }
            NumberAnimation {
                target: root
                properties: "width"
                from: 0
                to: width
                duration: 200
            }
            NumberAnimation {
                target: root
                properties: "height"
                from: 0
                to: height
                duration: 200
            }
        }
    }

    exit: Transition {
        NumberAnimation {
            target: root
            properties: "opacity"
            from:1
            to: 0
            duration: 200
        }
    }
}

import QtQuick 2.12
import QtQuick.Controls 2.5
import "../../common"
import "../../"
import QtGraphicalEffects 1.12
Item {
    implicitWidth: 1700
    implicitHeight:900
    CusDialog{
        id:pdialog
        anchors.centerIn: Overlay.overlay
        diatype:CusDialog.DIALOGENUM.SAVECONFIG
        buttonColor:"#967A50"
        headerColor:"#967A50"
        title: "打印提示"
        onAccepted: {
             close();
        }
    }
    Loader{
        id:pie
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.bottom: mutilBtn.top
        anchors.bottomMargin: 50
        width: 550
        height: 450
        active: swipeview.currentIndex===3
        source: "CustomPieSeries.qml"
    }

    Item{
        anchors.left: parent.left
        anchors.leftMargin: 80
        anchors.top: pie.bottom
        anchors.topMargin: 10
        width: 520
        height: 22
        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 6
            CusText{
                width: 152
                textColor: "#967A50"
                textContent: "不完善粒占比:"
                fontSize: 24
            }
            CusText{
                width: 86
                textColor: "#967A50"
                hAlignmentType: CusText.HALIGNMENT.AlignRight
                textContent: algorithmResult.allRatio[0]+"%"
                fontSize: 24
            }
            Item {
                width: 15
                height: 1
            }
            CusText{
                width: 90
                textColor: "#967A50"
                textContent: "颗粒比："
                fontSize: 24
            }
            CusText{
                width: 72
                textColor: "#967A50"
                textContent: algorithmResult.allRatio[1]+"%"
                fontSize: 24
            }
        }
    }



    CusShadow{
        id:textResult
        anchors.bottom: mutilBtn.top
        anchors.bottomMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter
        inner: "#eee9e3"
//        border.color: "#F6F6F6"
//        border.width: 1
        width: 570
        height: 382
//        layer.effect: DropShadow {
//            transparentBorder: true
//            horizontalOffset: 4
//            verticalOffset: 4
//            samples: 15
//            smooth: true
//            cached: true
//            color: "#80000000"
//        }
        Column{
            id:res
            anchors.left: parent.left
            anchors.leftMargin: 64
            anchors.top: parent.top
            anchors.topMargin: 33
            anchors.right: parent.right
            height: 242
            spacing: 27
            Row{
                height: 28
                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/Image/image/user/sy.png"
                    width: sourceSize.width
                    height: sourceSize.height
                }
                Item {
                    width: 20
                    height: 1
                }
                CusText{
                    width: 80
                    height: 28
                    textContent: "生芽粒"
                    fontSize: 27
                }
                Item {
                    width: 28
                    height: 1
                }
                CusText{
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    width: 76
                    height: 28
                    textContent: algorithmResult.shengya[0]+"%"
                    fontSize: 27
                }
                Item {
                    width: 52
                    height: 1
                }
                CusText{
                    width: 80
                    height: 28
                    textContent: "颗粒比"
                    fontSize: 27
                }
                Item {
                    width: 28
                    height: 1
                }
                CusText{
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    width: 76
                    height: 28
                    textContent: algorithmResult.shengya[1]+"%"
                    fontSize: 27
                }
            }

            Row{
                height: 28
                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/Image/image/user/cs.png"
                    width: sourceSize.width
                    height: sourceSize.height
                }
                Item {
                    width: 20
                    height: 1
                }
                CusText{
                    width: 80
                    height: 28
                    textContent: "虫蚀粒"
                    fontSize: 27
                }
                Item {
                    width: 28
                    height: 1
                }
                CusText{
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    width: 76
                    height: 28
                    textContent: algorithmResult.chongshi[0]+"%"
                    fontSize: 27
                }
                Item {
                    width: 52
                    height: 1
                }
                CusText{
                    width: 80
                    height: 28
                    textContent: "颗粒比"
                    fontSize: 27
                }
                Item {
                    width: 28
                    height: 1
                }
                CusText{
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    width: 76
                    height: 28
                    textContent: algorithmResult.chongshi[1]+"%"
                    fontSize: 27
                }
            }
            Row{
                height: 28
                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/Image/image/user/ps.png"
                    width: sourceSize.width
                    height: sourceSize.height
                }
                Item {
                    width: 20
                    height: 1
                }
                CusText{
                    width: 80
                    height: 28
                    textContent: "破损粒"
                    fontSize: 27
                }
                Item {
                    width: 28
                    height: 1
                }
                CusText{
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    width: 76
                    height: 28
                    textContent: algorithmResult.posun[0]+"%"
                    fontSize: 27
                }
                Item {
                    width: 52
                    height: 1
                }
                CusText{
                    width: 80
                    height: 28
                    textContent: "颗粒比"
                    fontSize: 27
                }
                Item {
                    width: 28
                    height: 1
                }
                CusText{
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    width: 76
                    height: 28
                    textContent: algorithmResult.posun[1]+"%"
                    fontSize: 27
                }
            }
            Row{
                height: 28
                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/Image/image/user/sm.png"
                    width: sourceSize.width
                    height: sourceSize.height
                }
                Item {
                    width: 20
                    height: 1
                }
                CusText{
                    width: 80
                    height: 28
                    textContent: "生霉粒"
                    fontSize: 27
                }
                Item {
                    width: 28
                    height: 1
                }
                CusText{
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    width: 76
                    height: 28
                    textContent: algorithmResult.shengmei[0]+"%"
                    fontSize: 27
                }
                Item {
                    width: 52
                    height: 1
                }
                CusText{
                    width: 80
                    height: 28
                    textContent: "颗粒比"
                    fontSize: 27
                }
                Item {
                    width: 28
                    height: 1
                }
                CusText{
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    width: 76
                    height: 28
                    textContent: algorithmResult.shengmei[1]+"%"
                    fontSize: 27
                }
            }
            Row{
                height: 28
                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/Image/image/user/bb.png"
                    width: sourceSize.width
                    height: sourceSize.height
                }
                Item {
                    width: 20
                    height: 1
                }
                CusText{
                    width: 80
                    height: 28
                    textContent: "病斑粒"
                    fontSize: 27
                }
                Item {
                    width: 28
                    height: 1
                }
                CusText{
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    width: 76
                    height: 28
                    textContent: algorithmResult.binban[0]+"%"
                    fontSize: 27
                }
                Item {
                    width: 52
                    height: 1
                }
                CusText{
                    width: 80
                    height: 28
                    textContent: "颗粒比"
                    fontSize: 27
                }
                Item {
                    width: 28
                    height: 1
                }
                CusText{
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    width: 76
                    height: 28
                    textContent: algorithmResult.binban[1]+"%"
                    fontSize: 27
                }
            }
        }
        Column{
            anchors.top: res.bottom
            anchors.topMargin: 9
            anchors.left: parent.left
            anchors.leftMargin: 110
            anchors.right: parent.right
            spacing: 9
            Row{
                height: 24
                CusText{
                    width: 80
                    height: 24
                    textContent: "赤霉粒"
                    fontSize: 24
                }
                Item {
                    width: 28
                    height: 1
                }
                CusText{
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    width: 76
                    height: 24
                    textContent: algorithmResult.chimei[0]+"%"
                    fontSize: 24
                }
                Item {
                    width: 52
                    height: 1
                }
                CusText{
                    width: 80
                    height: 24
                    textContent: "颗粒比"
                    fontSize: 24
                }
                Item {
                    width: 37
                    height: 1
                }
                CusText{
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    width: 68
                    height: 24
                    textContent: algorithmResult.chimei[1]+"%"
                    fontSize: 24
                }
            }
            Row{
                height: 24
                CusText{
                    width: 80
                    height: 24
                    textContent: "黑胚粒"
                    fontSize: 24
                }
                Item {
                    width: 28
                    height: 1
                }
                CusText{
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    width: 76
                    height: 24
                    textContent: algorithmResult.heipei[0]+"%"
                    fontSize: 24
                }
                Item {
                    width: 52
                    height: 1
                }
                CusText{
                    width: 80
                    height: 24
                    textContent: "颗粒比"
                    fontSize: 24
                }
                Item {
                    width: 28
                    height: 1
                }
                CusText{
                    hAlignmentType:CusText.HALIGNMENT.AlignRight
                    width: 76
                    height: 24
                    textContent: algorithmResult.heipei[1]+"%"
                    fontSize: 24
                }
            }
        }
    }

    Item{
        anchors.right: textResult.left
        anchors.leftMargin: 70
        anchors.bottom: mutilBtn.top
        anchors.bottomMargin: 100
        width: 188
        height: 22
        z:10
        Row{
            anchors.fill: parent
            spacing: 8
            Image {
                source: "qrc:/Image/image/user/search.png"
                width: sourceSize.width
                height: sourceSize.height
                anchors.verticalCenter: parent.verticalCenter
            }
            CusText{
                anchors.verticalCenter: parent.verticalCenter
                textColor: "#967A50"
                textContent: "查看不完善粒图片"
                fontSize: 16
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                swipeview.currentIndex=4
            }
        }
    }

    Row{
        id:mutilBtn
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 120
        spacing: 480
        Item {
            width: 116
            height: 130
            Column{
                anchors.fill: parent
                spacing: 12
                Image{
                    source: "qrc:/Image/image/user/history.png"
                    width: sourceSize.width
                    height: sourceSize.height
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                CusText{
                    textColor: "#967A50"
                    fontSize: 29
                    textContent: "历史记录"
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    swipeview.currentIndex=5;
                    maintaintitle.frontIndex=3;

                    wheatRecord.item.initTable(0,new Date(),new Date());
                    wheatRecord.item.ldate = new Date();
                    wheatRecord.item.ldate = new Date();
                    wheatRecord.item.sqlSampleidcontent="";
                }
            }
        }

        Item {
            width: 144
            height: 130
            Column{
                anchors.fill: parent
                spacing: 12
                Image{
                    source: "qrc:/Image/image/user/nextDection.png"
                    width: sourceSize.width
                    height: sourceSize.height
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                CusText{
                    textColor: "#967A50"
                    fontSize: 29
                    textContent: "下一次检测"
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    swipeview.currentIndex=1;
                }
            }
        }

        Item {
            width: 173
            height: 130
            Column{
                anchors.fill: parent
                spacing: 12
                Image{
                    source: "qrc:/Image/image/user/print.png"
                    width: sourceSize.width
                    height: sourceSize.height
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                CusText{
                    textColor: "#967A50"
                    fontSize: 29
                    textContent: "打印检测结果"
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if(algorithmResult.printResult()){
                        pdialog.contText="打印成功"
                    }else{
                        pdialog.contText="打印失败"
                    }
                    pdialog.open()
                }
            }
        }
    }


}

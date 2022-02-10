import QtQuick 2.15
import QtGraphicalEffects 1.12
import QtQuick.Controls 2.5
import "../../common"
import "../../"

Item {
    id:record
    implicitHeight: 1000
    implicitWidth: 1800
    property alias grainname: combox.currentIndex
    property alias ldate: caleft.selectedDate
    property alias rdate: caright.selectedDate
    property alias sqlSampleidcontent: searchId.content
    property real pageCount: 0
    CusKeyboard{
        id:keyboard
        visible: false
        z:100
        onKeyBoard: {
            searchId.textinput.insert(searchId.textinput.cursorPosition,content)
        }
        onKeyBoardback: {
            searchId.textinput.remove(searchId.textinput.cursorPosition-1,searchId.textinput.cursorPosition)
        }
    }
    Row{
        id:topquery
        anchors.left: parent.left
        anchors.leftMargin: 86
        anchors.top: parent.top
        spacing: 11
        height: 46
        CusText{
            width: 90
            anchors.verticalCenter: parent.verticalCenter
            textContent: "谷物种类:"
            fontSize:  20
            textColor: "#222222"
        }
        CusComboBox{
            id:combox
            model: ["小麦","大米","玉米","高粱"]
            width: 102
            height: 46
        }

        Item{
            width: 70
            height: 1
        }
        CusText{
            width: 90
            anchors.verticalCenter: parent.verticalCenter
            textContent: "样品编号:"
            fontSize:  20
            textColor: "#222222"
        }
        CusInputText{
            id:searchId
            width: 132
            height: 46
            fontsize: 16
            textColor:"#000000"
        }
        CusButton_Image{
            anchors.verticalCenter: parent.verticalCenter
            btnImgUrl:"qrc:/Image/image/user/keyboardRecord.png"
            width: 66
            height: 46
            onClicked: {
                keyboard.x=searchId.mapToItem(record,0,0).x-(keyboard.width-searchId.width)/2;
                keyboard.y=searchId.mapToItem(record,0,0).y+searchId.height+6
                keyboard.visible=true;
            }
        }
        Item{
            width: 60
            height: 1
        }
        CusText{
            width: 90
            anchors.verticalCenter: parent.verticalCenter
            textContent: "查询时间:"
            fontSize:  20
            textColor: "#222222"
        }
        TextField{
            id:input
            width: 420
            height: 46
            readOnly:true
            font.pixelSize: 20
            leftPadding: 44
            text:Qt.formatDate(caleft.selectedDate,"yyyy-MM-dd")+"  ~  "+Qt.formatDate(caright.selectedDate,"yyyy-MM-dd")
            background: Rectangle{
                border.width: 2
                border.color:"#bfbfbf"
                radius: 8
                Button{
                    width: 24
                    height: 24
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    background: Item {
                        Image{
                            source: "qrc:/Image/image/user/caleder.png"
                            width: sourceSize.width
                            height: sourceSize.height
                            anchors.centerIn: parent
                        }
                    }
                    onClicked: {
                        cuscalendar.x=input.mapToItem(record,0,0).x-(cuscalendar.width-input.width)/2
                        cuscalendar.y=input.mapToItem(record,0,0).y+input.height+2
                        cuscalendar.visible=true;
                    }
                }
            }
        }
        Item{
            width: 60
            height: 1
        }
        CusRadusButton{
            text: "查询"
            width: 94
            height: 46
            backColor:"#967A50"
            onClicked: {
                let type=-1;
                if(combox.displayText=="小麦"){
                    type=0;
                }
                if(caleft.selectedDate>caright.selectedDate){
                    pdialog.title="提示"
                    pdialog.contText="所选时间有误"
                    pdialog.open()
                }

                initTable(type,caleft.selectedDate,caright.selectedDate);
//                sqlSampleId.queryRecordCount([type,
//                                         Qt.formatDate(caleft.selectedDate,"yyyy-MM-dd")+" 00:00:00",
//                                         Qt.formatDate(caright.selectedDate,"yyyy-MM-dd")+" 23:59:59",
//                                         searchId.content]);
//                sqlSampleId.queryRecord([type,
//                                         Qt.formatDate(caleft.selectedDate,"yyyy-MM-dd")+" 00:00:00",
//                                         Qt.formatDate(caright.selectedDate,"yyyy-MM-dd")+" 23:59:59",
//                                         searchId.content],0);
            }
        }
    }
    Rectangle{
        color: "#F6F6F6"
        radius: 5
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 86
        anchors.rightMargin: 86
        anchors.top: topquery.bottom
        anchors.topMargin: 30
        anchors.bottom:pageIndicator.top
        anchors.bottomMargin: 10
        CellView{
            anchors.fill: parent
            clip: true
            visible: WheatTabModel.rows>0
        }
        CusText{
            anchors.fill: parent
            textContent: "无数据"
            hAlignmentType: CusText.HALIGNMENT.AlignHCenter
            fontSize: 50
            visible: WheatTabModel.rows<=0
            textColor: "#bfbfbf"
            fontitalic:true
        }
    }
    CusPageIndicator{
        id:pageIndicator
        anchors.right: parent.right
        anchors.rightMargin: 86
        anchors.bottom:bottomBtn.top
        anchors.bottomMargin: 50
        visible: count>0
        count: if(pageCount%10===0){
//                   console.log(pageCount)
//                   console.log(pageCount%50);
//                   console.log(pageCount/50);
                   return pageCount/10
               }else{
                  if(pageCount<10) return 1
                  else return pageCount/10+1
               }

        onCurrentIndexChanged: {
            sqlSampleId.queryRecord([0,
                                     Qt.formatDate(caleft.selectedDate,"yyyy-MM-dd")+" 00:00:00",
                                     Qt.formatDate(caright.selectedDate,"yyyy-MM-dd")+" 23:59:59",
                                     searchId.content],pageIndicator.currentIndex*10);
        }
    }

    Rectangle {
        id:cuscalendar
        visible: false
        width: 552
        height: 340
        Item {
            id:catop
            anchors.left: parent.left
            anchors.top: parent.top
            width: parent.width
            height: 40
            CusText {
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.verticalCenter: parent.verticalCenter
                textContent: Qt.formatDate(caleft.selectedDate,"yyyy/MM/dd")+" -> "+
                              Qt.formatDate(caright.selectedDate,"yyyy/MM/dd")
                textColor: "#75000000"
                width: 200
                fontSize: 15
            }
            CusRadusButton{
                anchors.right: parent.right
                //anchors.top: parent.top
                anchors.rightMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                text: "确定"
                width: 50
                height: 30
                backColor:"#967A50"
                fontsize: 16
                onClicked: {
                    cuscalendar.visible=false;
                }
            }
        }
        CusCalendar{
            id:caleft
            anchors.left: parent.left
            anchors.top: catop.bottom
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            width: parent.width/2-15
        }
        CusCalendar{
            id:caright
            anchors.right: parent.right
            anchors.top: catop.bottom
            anchors.bottomMargin: 10
            width: parent.width/2-15
            anchors.bottom: parent.bottom
        }
        Rectangle{
            id:linetop
            anchors.left: caleft.right
            anchors.top: catop.bottom
            width: 30
            height: 1
            color: "#bfbfbf"
        }
        Rectangle{
            anchors.left: caleft.right
            anchors.top: linetop.bottom
            anchors.topMargin: 40-2*height
            width: 30
            height: 1
            color: "#bfbfbf"
        }
        layer.enabled: true
        layer.effect:DropShadow{
             transparentBorder: true
             cached: true
             samples: 9
             smooth: true
             horizontalOffset: 4
             verticalOffset: 4
             color: "#80000000"
             radius: 5
        }
        radius: 4
    }
    Row{
        id:bottomBtn
        spacing: 406
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
//        Item {
//            width: 144
//            height: 130
//            Column{
//                anchors.fill: parent
//                spacing: 12
//                Image{
//                    source: "qrc:/Image/image/user/nextDection.png"
//                    width: sourceSize.width
//                    height: sourceSize.height
//                    anchors.horizontalCenter: parent.horizontalCenter
//                }
//                CusText{
//                    textColor: "#967A50"
//                    fontSize: 29
//                    textContent: "下一次检测"
//                }
//            }
//            MouseArea{
//                anchors.fill: parent
////                onClicked: {
////                    swipeview.currentIndex=1;
////                }
//            }
//        }
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
                    textContent: "打印单条记录"
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    WheatTabModel.selectData();
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
                    source: "qrc:/Image/image/user/export.png"
                    width: sourceSize.width
                    height: sourceSize.height
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                CusText{
                    textColor: "#967A50"
                    fontSize: 29
                    textContent: "导出查询结果"
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    let path=WheatTabModel.checkUsbDisk();
                    if(path!==""){
                            floferDialog.folder="file://"+path
                            floferDialog.close();
                            floferDialog.open();
                    }else{
                        pdialog.title="导出提示";
                        pdialog.contText="请插入标准U盘"
                        pdialog.open();
                    }
                }
            }
        }
    }
    Component.onCompleted: {
//        let type=-1;
//        if(combox.displayText=="小麦"){
//            type=0;
//        }
//        initTable(type,caleft.selectedDate,caright.selectedDate);
//        sqlSampleId.queryRecordCount([type,
//                                 Qt.formatDate(caleft.selectedDate,"yyyy-MM-dd")+" 00:00:00",
//                                 Qt.formatDate(caright.selectedDate,"yyyy-MM-dd")+" 23:59:59",
//                                 searchId.content]);
//        sqlSampleId.queryRecord([type,
//                                 Qt.formatDate(caleft.selectedDate,"yyyy-MM-dd")+" 00:00:00",
//                                 Qt.formatDate(caright.selectedDate,"yyyy-MM-dd")+" 23:59:59",
//                                 searchId.content],0);
    }

    Popup{
        id:pupdia
        anchors.centerIn: parent
        width: 200
        height: 200
        closePolicy:Popup.NoAutoClose
        contentItem: CusBusyIndicator{
                id:busyIndicatro
                running: false
                busyColor: "#967A50"
                busyRadius:14
                busyCount: 8
        }
        background: Item {
        }
        modal: true
    }



    CusFloderDialog{
        id:floferDialog
        onFloderPath: {
            WheatTabModel.exportExcel(path);
            pupdia.open();
            busyIndicatro.running=true;
        }
    }

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

    Connections{
        target: WheatTabModel
        enabled:true
        function onEmptySelect(flag){
            if(!flag){
                if(WheatTabModel.printResult()){
                    pdialog.contText="打印成功"
                }else{
                    pdialog.contText="打印失败"
                }
            }else{
                pdialog.contText="未选中数据"
            }
            pdialog.title="打印提示";
            pdialog.open();
        }
        function onExportFinsh(flag){
            pupdia.close();
            busyIndicatro.running=false;
            if(flag){
                pdialog.contText="导出成功"
            }else{
                pdialog.contText="导出失败"
            }
            pdialog.title="导出提示";
            pdialog.open();
        }
    }

    function initTable(type,startDate,endDate){
        pageCount=sqlSampleId.queryRecordCount([type,
                                 Qt.formatDate(startDate,"yyyy-MM-dd")+" 00:00:00",
                                 Qt.formatDate(endDate,"yyyy-MM-dd")+" 23:59:59",
                                 searchId.content]);
        sqlSampleId.queryRecord([type,
                                 Qt.formatDate(startDate,"yyyy-MM-dd")+" 00:00:00",
                                 Qt.formatDate(endDate,"yyyy-MM-dd")+" 23:59:59",
                                 searchId.content],0);
    }
}

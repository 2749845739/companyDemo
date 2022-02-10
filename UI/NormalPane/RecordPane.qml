import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQml 2.12
import Qt.labs.qmlmodels 1.0
import App.Class 0.1 as Class
import "./ContentItem"
import "../common"
Item {
    property alias startTime: startTime
    property alias endTime: endTime
    Rectangle{
       color: "#010512"
       anchors.fill: parent
    CusDialog{
       id:dialogexecl
       width: 320
       height: 200
       diatype: CusDialog.DIALOGENUM.EXPRRTEXECL
       anchors.centerIn: Overlay.overlay
       visible: false
       title:"导出"
       closePolicy: Popup.NoAutoClose
    }
    CusDialog{
       id:dialogTips
       width: 320
       height: 200
       //fontSize:15
       contText: "当前条件下无历史数据"
       diatype: CusDialog.DIALOGENUM.EXPRRTEXECL
       anchors.centerIn: Overlay.overlay
       visible: false
       title:"提示"
       closePolicy: Popup.NoAutoClose
    }

    CusCalendar{
        id:startCalendar
        x:startBoder.x+80-50
        y:startBoder.mapToGlobal(0,0).y+startBoder.height+10+82
        width: startBoder.width+100
        height: 300
        visible: false
        z:10
        onDoubleClicked: {
            startTime.value=date.toLocaleDateString(Qt.locale(), "yyyy-MM-dd")+" 00:00:00";
            visible=false;
        }
    }
    CusCalendar{
        id:endCalendar
        x:endBoder.x-50+80
        y:endBoder.mapToGlobal(0,0).y+endBoder.height+10+82
        width: endBoder.width+100
        visible: false
        height: 300
        z:10
        onDoubleClicked: {
            endTime.value=date.toLocaleDateString(Qt.locale(), "yyyy-MM-dd")+" 23:59:59";
            visible=false;
        }
    }
    Row{
        id:solt
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 82
        anchors.leftMargin: 80
        anchors.right: parent.right
        anchors.rightMargin: 260
        height: 30
        //            anchors.left: parent.left
        //            anchors.top: parent.top
        Layout.fillWidth:true
        spacing: 10
        //            Label{
        //                height: 30
        //                verticalAlignment: Text.AlignVCenter
        //                horizontalAlignment: Text.AlignHCenter
        //                text: "品种:"
        //            }
        Item {
            height: 30
            width: 62
            Image {
                anchors.verticalCenter: parent.verticalCenter
                source: "qrc:/Image/image/normal/grainType.png"
                width: sourceSize.width
                height: sourceSize.height
            }
        }
       RadusBoder{
           width: 76
           height: 30
           radus: 5
           CusComboBox{
               id:grainType
               anchors.fill: parent
               model: ListModel {
                   id: cbItems
                   ListElement { text: "小麦"; value: "1" }
                   //                    ListElement { text: "玉米"; value: "2" }
                   //                    ListElement { text: "大豆"; value: "3" }
               }
           }
       }

//        Label{
//            width:30
//            verticalAlignment: Text.AlignVCenter
//            horizontalAlignment: Text.AlignHCenter
//        }
        //            Label{
        //                height: 30
        //                verticalAlignment: Text.AlignVCenter
        //                horizontalAlignment: Text.AlignHCenter
        //                text: "开始日期:"
        //            }
        Item {
            height: 30
            width: 62
            Image {
                anchors.verticalCenter: parent.verticalCenter
                source: "qrc:/Image/image/normal/startTime.png"
                width: sourceSize.width
                height: sourceSize.height
            }
        }
        RadusBoder{
            id:startBoder
            width: 150
            height: 30
            radus: 5
        InputCalendar{
            id:startTime
            //height: 30
            anchors.fill: parent
            onShow: {
                startCalendar.visible=!startCalendar.visible;
                startCalendar.focus=true;
            }
        }
        }

        //            Label{
        //                height: 30
        //                verticalAlignment: Text.AlignVCenter
        //                horizontalAlignment: Text.AlignHCenter
        //                text: "结束日期:"
        //            }
        Item {
            height: 30
            width: 62
            Image {
                anchors.verticalCenter: parent.verticalCenter
                source: "qrc:/Image/image/normal/endTime.png"
                width: sourceSize.width
                height: sourceSize.height
            }
        }
        RadusBoder{
            id:endBoder
            width: 150
            height: 30
            radus: 5
        InputCalendar{
            id:endTime
            //height: 30
            anchors.fill: parent
            onShow: {
                endCalendar.visible=!endCalendar.visible;
                endCalendar.focus=true;
            }
        }
        }
    }
    Row{
        anchors.right: parent.right
        anchors.rightMargin: 80
        anchors.top: parent.top
        anchors.topMargin: 82
        height: 30
        CusButton_Image{
            btnImgNormal:"qrc:/Image/image/normal/query.png"
            btnImgHovered:"qrc:/Image/image/normal/query.png"
            btnImgPressed:"qrc:/Image/image/normal/query.png"
            width: 61
            height: 30
            onClicked: {
                console.log(startBoder.mapToGlobal(0,0));
                console.log(startBoder.mapToGlobal(0,0).x);
                recordManager.getRocoedData(startTime.value,endTime.value,grainType.currentText);
            }
        }
        CusButton_Image{
            btnImgNormal:"qrc:/Image/image/normal/export.png"
            btnImgHovered:"qrc:/Image/image/normal/export.png"
            btnImgPressed:"qrc:/Image/image/normal/export.png"
            width: 87
            height: 30
            onClicked: {
                recordManager.exportExcel("")?dialogexecl.title="导出成功":"导出失败";
                dialogexecl.open();
            }
        }
    }

    RadusBoder{
        anchors.left: parent.left
        anchors.top: solt.bottom
        anchors.topMargin: 20
//        anchors.topMargin: 82
        anchors.bottom: back_decect.top
        anchors.bottomMargin: 5
        anchors.leftMargin: 80
        anchors.right: parent.right
        anchors.rightMargin: 80
        radus: 0
            ColumnLayout{
                //anchors.fill: parent
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.leftMargin: 5
                anchors.topMargin: 5
                anchors.rightMargin: 5
                anchors.bottomMargin: 5
                spacing:50
                /*Row{
                    id:solt
                    height: 30
                    Layout.fillWidth:true
                    Layout.fillHeight: true
                    //            anchors.left: parent.left
                    //            anchors.top: parent.top
                    Layout.fillWidth:true
                    spacing: 20
        //            Label{
        //                height: 30
        //                verticalAlignment: Text.AlignVCenter
        //                horizontalAlignment: Text.AlignHCenter
        //                text: "品种:"
        //            }
                    Item {
                        height: 30
                        width: 62
                        Image {
                            anchors.verticalCenter: parent.verticalCenter
                            source: "qrc:/Image/image/normal/grainType.png"
                            width: sourceSize.width
                            height: sourceSize.height
                        }
                    }

                    CusComboBox{
                        id:grainType
                        width: 76
                        height: 30
                        model: ListModel {
                            id: cbItems
                            ListElement { text: "小麦"; value: "1" }
        //                    ListElement { text: "玉米"; value: "2" }
        //                    ListElement { text: "大豆"; value: "3" }
                        }
                    }
                    Label{
                        width:30
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
        //            Label{
        //                height: 30
        //                verticalAlignment: Text.AlignVCenter
        //                horizontalAlignment: Text.AlignHCenter
        //                text: "开始日期:"
        //            }
                    Item {
                        height: 30
                        width: 62
                        Image {
                            anchors.verticalCenter: parent.verticalCenter
                            source: "qrc:/Image/image/normal/startTime.png"
                            width: sourceSize.width
                            height: sourceSize.height
                        }
                    }
                    InputCalendar{
                        id:startTime
                        height: 30
                        onShow: {
                            startCalendar.visible=!startCalendar.visible;
                            startCalendar.focus=true;
                        }
                    }

        //            Label{
        //                height: 30
        //                verticalAlignment: Text.AlignVCenter
        //                horizontalAlignment: Text.AlignHCenter
        //                text: "结束日期:"
        //            }
                    Item {
                        height: 30
                        width: 62
                        Image {
                            anchors.verticalCenter: parent.verticalCenter
                            source: "qrc:/Image/image/normal/endTime.png"
                            width: sourceSize.width
                            height: sourceSize.height
                        }
                    }
                    InputCalendar{
                        id:endTime
                        height: 30
                        onShow: {
                            endCalendar.visible=!endCalendar.visible;
                            endCalendar.focus=true;
                        }
                    }
                    CusButton_Image{
                        btnImgNormal:"qrc:/Image/image/normal/query.png"
                        btnImgHovered:"qrc:/Image/image/normal/query.png"
                        btnImgPressed:"qrc:/Image/image/normal/query.png"
                        width: 61
                        height: 30
                        onClicked: {
                            recordManager.getRocoedData(startTime.value,endTime.value,grainType.currentText);
                        }
                    }
                    CusButton_Image{
                        btnImgNormal:"qrc:/Image/image/normal/export.png"
                        btnImgHovered:"qrc:/Image/image/normal/export.png"
                        btnImgPressed:"qrc:/Image/image/normal/export.png"
                        width: 87
                        height: 30
                        onClicked: {
                           recordManager.exportExcel("")?dialogexecl.title="导出成功":"导出失败";
                           dialogexecl.open();
                        }
                    }
                }*/
                    GridLayout {
                        id:root
        //                anchors.left: parent.left
        //                anchors.top: parent.top
                        //            anchors.top: solt.bottom
                        //anchors.topMargin: 40
                        property int    defaultRowHeight : 30
                        property int    defaultColumnWidth : 130
                        Layout.fillWidth:true
                        Layout.fillHeight: true
                        rows: 1
                        columns:1
                        rowSpacing: 2
                        columnSpacing: 2
                        ResizableColumnHeader {             // COLUMN HEADER
                            id: columnHeaderk
                            Layout.fillWidth: true
                            height: root.defaultRowHeight
                            defaultWidth: root.defaultColumnWidth
                            spacing: 1
                            model: recordWheatModel.headerRoles
                            contentX: table.contentX
                            interactive: false
                            onColumnWidthChanged: table.forceLayout()
                        }
                        TableView{
                            id: table
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            columnSpacing: 1
                            rowSpacing: 1
                            model: recordWheatModel
                            clip: true
                            columnWidthProvider: columnHeader.columnWidthProvider
                            rowHeightProvider: function (column) { return  root.defaultRowHeight }
                            delegate: DelegateChooser{
                                role: "DelegateType"
                                DelegateChoice{
                                    roleValue: Class.TextEditor
                                    Rectangle{
                                        CusText {
                                            telide: Text.ElideRight
                                            textContent: model.CellData
                                            hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                                            vAlignmentType: CusText.VALIGNMENT.AlignVCenter
                                            anchors.fill: parent
                                        }
                                        color: "#ffffff"
                                    }
                                }
                                DelegateChoice{
                                    roleValue: Class.NumberEditor
                                    Text {
                                        text: model.CellData
                                    }
                                }
                            }
                            ScrollBar.horizontal: ScrollBar{
                            }
                            ScrollBar.vertical: ScrollBar{
                            }
                        }
                    }
                }
    }


//    CusRadusButton{
//        id:back_decect
//        anchors.left: parent.left
//        anchors.leftMargin: 10
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: 10
//        text: "返回上一页"
//        backgroundColorNormal:"#ffffff"
//        backgroundColorHovered:"#cdcdcd"
//        onClicked: {
//            stack.currentIndex=2;
//        }
//    }
    CusButton_Image{
        id:back_decect
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        width: 72
        height: 72
        btnImgNormal:"qrc:/Image/image/normal/back_normal.png"
        btnImgHovered:"qrc:/Image/image/normal/back_normal.png"
        btnImgPressed:"qrc:/Image/image/normal/back_normal.png"
        onClicked: {
            stack.currentIndex=2;
        }
    }

    Connections{
        target: recordManager
//        onEmptyRecordResult:{
//           dialogTips.contText="当前条件下无历史数据";
//           dialogTips.open();
//        }
    }
    Connections{
        target: recordManager
//        onTimeRangeError:{
//            dialogTips.contText="所选时间有误";
//            dialogTips.open();
//        }
    }
    }
}




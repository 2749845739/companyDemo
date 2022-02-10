import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import Qt.labs.qmlmodels 1.0
import App.Class 0.1 as Class
Flickable {
    id:root
    property int defauleHeight: 50
    implicitHeight: 500
    implicitWidth: 800
    interactive: true
    contentWidth: header.contentWidth+5
    contentHeight: re.height+topre.height+4
    Rectangle{
        id:topre
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 4  //是他的contentItem 所以这里跟他的content边界锚定！！！！
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.leftMargin: 4
        height: 50
        color: "#bfbfbf"
        Flickable{
            id:headflick
            //height: 30
            anchors.fill: parent
//            anchors.leftMargin: 1
//            anchors.rightMargin: 1
//            topMargin: 1
            leftMargin: 1
            topMargin: 2
            rightMargin: 1
            bottomMargin: 1
            interactive: false
            boundsBehavior: Flickable.StopAtBounds
            clip: true
            //contentX: table.contentX
            //contentWidth: header.width
            ResizableColumnHeader{
                id:header
                anchors.fill: parent
                defaultWidth: 150
                spacing: 1
                model: WheatTabModel.headRoles
                interactive: false
                onColumnWidthChanged: {
                    if(width<=root.width) root.contentX=0;
                    table.forceLayout()
                }
            }
        }
    }


    Rectangle{
        id:re
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.top: topre.bottom
        anchors.bottomMargin: 2
        anchors.leftMargin: 4
        //anchors.topMargin: 1
        height: WheatTabModel.rows*(defauleHeight+1)
//            let maxheight=root.height-headflick.height-1-2;
//            if(WheatTabModel.rowCount()*(defauleHeight+1)>root.height-headflick.height-1-2){
//                return maxheight
//            }else{
//                return WheatTabModel.rowCount()*(defauleHeight+1)
//            }

//        }
        color: "#bfbfbf"
        TableView{
            id:table
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 1
            anchors.rightMargin: 1
            anchors.bottomMargin: 2
            clip: true
            columnWidthProvider: header.columnWidthProvider
            rowHeightProvider: function(columns){return defauleHeight}
            model:WheatTabModel
            interactive: false
            rowSpacing:1
            columnSpacing:1

            //每个cellEditor角色就是item的editortype  在rolevalue取到哪个editortype就显示哪个角色
            delegate: DelegateChooser{
                role: "cellType"
                DelegateChoice{
                    roleValue: Class.WheatItem.TextEditor
                    Rectangle{
                        CusText {
                            telide: Text.ElideRight
                            textContent: model.cellData
                            anchors.fill: parent
                            hAlignmentType: CusText.HALIGNMENT.AlignHCenter
                        }
                        color: "#F6F6F6"
                    }
                }
                DelegateChoice{
                    roleValue: Class.WheatItem.CheckboxEditor
                    Rectangle {
                        Image {
                            source: model.cellData==="true"?"qrc:/Image/image/user/selected.png":"qrc:/Image/image/user/unselected.png"
                            anchors.centerIn: parent
                            width: sourceSize.width
                            height: sourceSize.height
                        }
                        color: "#F6F6F6"
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                if(model.cellData==="true"){
                                    model.cellData="false"
                                }else{
                                    model.cellData="true"
                                }
                            }
                        }
                    }
                }
            }
        }

    }


    ScrollBar.horizontal:   ScrollBar {
        orientation: Qt.Horizontal
        //policy:ScrollBar.AlwaysOn
    }
    ScrollBar.vertical:     ScrollBar {
//        onPositionChanged: {
//            if(size+position>=0.99){
//                WheatTabModel.updateData();
//            }
//        }
    }

    //    }
//    Connections{
//        target: WheatTabModel
//        function onRowsChanged(){
//            re.height=WheatTabModel.rowCount()*(defauleHeight+1)
//        }
//    }
}

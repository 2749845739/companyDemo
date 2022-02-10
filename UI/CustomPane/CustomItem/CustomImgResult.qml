import QtQuick 2.12
import QtQuick.Controls 2.5
import "../../common"
import "../.."
Item {
    implicitWidth: 1800
    implicitHeight:900
    property string granType: ""
    property string massRatio: "0.0"
    property string countRatio: "0.0"
    Row{
        id:graintypeBtn
        anchors.left: parent.left
        anchors.leftMargin: 85
        anchors.bottom: gridview.top
        anchors.bottomMargin: 46
        height: 50
        CusRadusButton{
            id:bwsl
            backgroundColorNormal:"transparent"
            backgroundColorHovered: "transparent"
            backgroundColorSelected:"#967A50"
            text: "不完善粒"
            fontsize: selected?30:24
            textColor: selected?"#FFFFFF":"#222222"
            width: 168
            height: 50
            onClicked: {
                selected=true
                syl.selected=false
                csl.selected=false
                psl.selected=false
                sml.selected=false
                bbl.selected=false
                cml.selected=false
                hpl.selected=false
                granType="不完善粒"
                massRatio=algorithmResult.allRatio[0]
                countRatio=algorithmResult.allRatio[1]
                algorithmResult.getSegTypeImg(10);
            }
        }
        CusRadusButton{
            id:syl
            backgroundColorNormal:"transparent"
            backgroundColorSelected:"#967A50"
            backgroundColorHovered: "transparent"
            text: "生芽粒"
            fontsize: selected?30:24
            textColor: selected?"#FFFFFF":"#222222"
            width: 168
            height: 50
            onClicked: {
                selected=true
                bwsl.selected=false
                csl.selected=false
                psl.selected=false
                sml.selected=false
                bbl.selected=false
                cml.selected=false
                hpl.selected=false
                granType="生芽粒"
                massRatio=algorithmResult.shengya[0]
                countRatio=algorithmResult.shengya[1]
                algorithmResult.getSegTypeImg(2);
            }
        }
        CusRadusButton{
            id:csl
            backgroundColorNormal:"transparent"
            backgroundColorSelected:"#967A50"
            backgroundColorHovered: "transparent"
            text: "虫蚀粒"
            fontsize: selected?30:24
            textColor: selected?"#FFFFFF":"#222222"
            width: 168
            height: 50
            onClicked: {
                selected=true
                syl.selected=false
                bwsl.selected=false
                psl.selected=false
                sml.selected=false
                bbl.selected=false
                cml.selected=false
                hpl.selected=false
                granType="虫蚀粒"
                massRatio=algorithmResult.chongshi[0]
                countRatio=algorithmResult.chongshi[1]
                algorithmResult.getSegTypeImg(4);
            }
        }
        CusRadusButton{
            id:psl
            backgroundColorNormal:"transparent"
            backgroundColorSelected:"#967A50"
            backgroundColorHovered: "transparent"
            text: "破损粒"
            fontsize: selected?30:24
            textColor: selected?"#FFFFFF":"#222222"
            width: 168
            height: 50
            onClicked: {
                selected=true
                syl.selected=false
                bwsl.selected=false
                csl.selected=false
                sml.selected=false
                bbl.selected=false
                cml.selected=false
                hpl.selected=false
                granType="破损粒"
                massRatio=algorithmResult.posun[0]
                countRatio=algorithmResult.posun[1]
                algorithmResult.getSegTypeImg(5);
            }
        }
        CusRadusButton{
            id:sml
            backgroundColorNormal:"transparent"
            backgroundColorSelected:"#967A50"
            backgroundColorHovered: "transparent"
            text: "生霉粒"
            fontsize: selected?30:24
            textColor: selected?"#FFFFFF":"#222222"
            width: 168
            height: 50
            onClicked: {
                selected=true
                syl.selected=false
                bwsl.selected=false
                csl.selected=false
                psl.selected=false
                bbl.selected=false
                cml.selected=false
                hpl.selected=false
                granType="生霉粒"
                massRatio=algorithmResult.shengmei[0]
                countRatio=algorithmResult.shengmei[1]
                algorithmResult.getSegTypeImg(3);
            }
        }
        CusRadusButton{
            id:bbl
            backgroundColorNormal:"transparent"
            backgroundColorSelected:"#967A50"
            backgroundColorHovered: "transparent"
            text: "病斑粒"
            fontsize: selected?30:24
            textColor: selected?"#FFFFFF":"#222222"
            width: 168
            height: 50
            onClicked: {
                selected=true
                syl.selected=false
                bwsl.selected=false
                csl.selected=false
                psl.selected=false
                sml.selected=false
                cml.selected=false
                hpl.selected=false
                granType="病斑粒"
                massRatio=algorithmResult.binban[0]
                countRatio=algorithmResult.binban[1]
                algorithmResult.getSegTypeImg(7);
            }
        }
        CusRadusButton{
            id:cml
            backgroundColorNormal:"transparent"
            backgroundColorSelected:"#967A50"
            backgroundColorHovered: "transparent"
            text: "赤霉粒"
            fontsize: selected?30:24
            textColor: selected?"#FFFFFF":"#222222"
            width: 168
            height: 50
            onClicked: {
                selected=true
                syl.selected=false
                bwsl.selected=false
                csl.selected=false
                psl.selected=false
                sml.selected=false
                bbl.selected=false
                hpl.selected=false
                granType="赤霉粒"
                massRatio=algorithmResult.chimei[0]
                countRatio=algorithmResult.chimei[1]
                algorithmResult.getSegTypeImg(1);
            }
        }
        CusRadusButton{
            id:hpl
            backgroundColorNormal:"transparent"
            backgroundColorSelected:"#967A50"
            backgroundColorHovered: "transparent"
            text: "黑胚粒"
            fontsize: selected?30:24
            textColor: selected?"#FFFFFF":"#222222"
            width: 168
            height: 50
            onClicked: {
                selected=true
                syl.selected=false
                bwsl.selected=false
                csl.selected=false
                psl.selected=false
                sml.selected=false
                bbl.selected=false
                cml.selected=false
                granType="黑胚粒"
                massRatio=algorithmResult.heipei[0]
                countRatio=algorithmResult.heipei[1]
                algorithmResult.getSegTypeImg(6);
            }
        }
    }

    Rectangle{
        id:gridview
        anchors.bottom: textresult.top
        anchors.bottomMargin: 16
        anchors.horizontalCenter: parent.horizontalCenter
        width: 1751
        height: 666
        color: "#eee9e3"
        border.color: "#F6F6F6"
        border.width: 1
        clip: true
        GridView{
            id:segView
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.top: parent.top
            anchors.topMargin: 15
            width: 1736
            height: 636
            cellWidth: 217
            cellHeight: 217
            delegate: wheat
            model: CusConfig.mergeResultImg
            ScrollBar.vertical: ScrollBar{
            }
            onCountChanged: {
                positionViewAtBeginning();
            }
        }

    }
    Component{
        id:wheat
        Item {
            width: 217
            height: 217
            Rectangle{
                anchors.left: parent.left
                anchors.top: parent.top
                //anchors.topMargin: 15
                width: 202
                height: 202
                color: "#000000"
                Image{
                    anchors.fill: parent
                    fillMode:Image.PreserveAspectFit
                    source: model.sourceImg
                }
            }
        }
    }

    Item{
        id:textresult
        width: 544
        height: 42
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
        CusText{
            width: 388
            height: 42
            visible: granType!==""
            anchors.horizontalCenter: parent.horizontalCenter
            textContent: granType+"："+massRatio+"%"
                         +"    颗粒比："+countRatio+"%"
            fontblod: true
            fontSize: 30
        }
    }
    Connections{
        target: algorithmResult
        function onSigMergeImg(fileName){
            CusConfig.filtersegImgModel(fileName)
        }
    }
    function resetBtn(){
        syl.selected=false
        bwsl.selected=false
        csl.selected=false
        psl.selected=false
        sml.selected=false
        bbl.selected=false
        cml.selected=false
        hpl.selected=false
        granType=""
    }
}

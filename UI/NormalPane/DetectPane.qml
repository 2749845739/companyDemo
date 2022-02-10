import QtQuick 2.12
import QtQuick.Controls 2.5
import "../common"
import "./ContentItem"
import "../"
Item {
    id:detect
    property bool isStop: boardControl.isStop
    property bool showResult: false
    onIsStopChanged: {
        if(isStop==true){
            CusConfig.homeEnable=true;
            displaysegview.timerStop();
        }
    }

    DisplaySegmentImg{
        id:displaysegview
        anchors.left: parent.left
        anchors.right: resultContent.left
        anchors.top:parent.top
        anchors.topMargin: 72
        anchors.bottom: parent.bottom
    }
    Rectangle{
        visible: true
        id:resultContent
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 92
        width: 260
        height: parent.height-92
        color: "#010512"
        /*Column{
            visible: !showResult
            anchors.left: parent.left
            anchors.top:parent.top
            width: parent.width
//            Row{
//                //anchors.left: parent.left
//                spacing: 4
//                height: 40
//                CusText{
//                    width: 80
//                    height: 30
//                    fontSize: 13
//                    hAlignmentType: CusText.HALIGNMENT.AlignRight
//                    textContent: "容重:"
//                }
//                CusText{
//                    width: 20
//                    height: 32
//                    fontSize: 13
//                    textContent: managerMath.volumeWeight+"g/L"
//                }
//            }
            Row{
                //anchors.left: parent.left
                spacing: 8
                height: 40
                //anchors.verticalCenter: parent.verticalCenter
                CusText{
                    anchors.verticalCenter: parent.verticalCenter
                    width: 80
                    height: 32
                    fontSize: 13
                    hAlignmentType: CusText.HALIGNMENT.AlignRight
                    textContent: "不完善粒:"
                }
                CusText{
                    anchors.verticalCenter: parent.verticalCenter
                    width: 20
                    height: 32
                    fontSize: 13
                    textContent: mathModel.unsound+"%"
                }
                Rectangle{
                    width: 15
                    height: parent.height
                    color: "transparent"
                }
//                CusButton_Image{
//                    anchors.verticalCenter: parent.verticalCenter
//                    btnImgNormal:"qrc:/Image/image/normal/document_normal.png"
//                    btnImgHovered:"qrc:/Image/image/normal/document_hover.png"
//                    btnImgPressed:"qrc:/Image/image/normal/document_hover.png"
//                    btnImgDisbaled:"qrc:/Image/image/normal/document_normal.png"
//                    tipText: "不完善粒详情"
//                    height: 32
//                    width: 24
//                }
            }
            // }

//            Row{
//                //anchors.left: parent.left
//                height: 40
//                spacing: 8
//                CusText{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 80
//                    height: 30
//                    fontSize: 13
//                    hAlignmentType: CusText.HALIGNMENT.AlignRight
//                    textContent: "杂质:"
//                }
//                CusText{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 20
//                    height: 32
//                    fontSize: 13
//                    textContent: managerMath.impurities+"%"
//                }
//                Rectangle{
//                    width: 15
//                    height: parent.height
//                    color: "transparent"
//                }
//                CusButton_Image{
//                    anchors.verticalCenter: parent.verticalCenter
//                    btnImgNormal:"qrc:/Image/image/normal/document_normal.png"
//                    btnImgHovered:"qrc:/Image/image/normal/document_hover.png"
//                    btnImgPressed:"qrc:/Image/image/normal/document_hover.png"
//                    btnImgDisbaled:"qrc:/Image/image/normal/document_normal.png"
//                    tipText: "杂质详情"
//                    height: 32
//                    width: 24
//                }
//            }
//            Row{
//                //anchors.left: parent.left
//                height: 40
//                spacing: 8
//                CusText{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 80
//                    height: 30
//                    fontSize: 13
//                    hAlignmentType: CusText.HALIGNMENT.AlignRight
//                    textContent: "水分:"
//                }
//                CusText{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 20
//                    height: 32
//                    fontSize: 13
//                    textContent: managerMath.moisture+"%"
//                }
//            }
//            Row{
//                //anchors.left: parent.left
//                height: 40
//                spacing: 8
//                CusText{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 80
//                    height: 30
//                    fontSize: 13
//                    hAlignmentType: CusText.HALIGNMENT.AlignRight
//                    textContent: "异种粮:"
//                }
//                CusText{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 20
//                    height: 32
//                    fontSize: 13
//                    textContent: managerMath.exoticWheat+"%"
//                }
//                Rectangle{
//                    width: 15
//                    height: parent.height
//                    color: "transparent"
//                }
//                CusButton_Image{
//                    anchors.verticalCenter: parent.verticalCenter
//                    btnImgNormal:"qrc:/Image/image/normal/document_normal.png"
//                    btnImgHovered:"qrc:/Image/image/normal/document_hover.png"
//                    btnImgPressed:"qrc:/Image/image/normal/document_hover.png"
//                    btnImgDisbaled:"qrc:/Image/image/normal/document_normal.png"
//                    tipText: "异种粮详情"
//                    height: 32
//                    width: 24
//                }
//            }
//            Row{
//                //anchors.left: parent.left
//                height: 40
//                spacing: 8
//                CusText{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 80
//                    height: 30
//                    fontSize: 13
//                    hAlignmentType: CusText.HALIGNMENT.AlignRight
//                    textContent: "千粒重:"
//                }
//                CusText{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 20
//                    height: 32
//                    fontSize: 13
//                    textContent: mathModel.thousandWeight+"%"
//                }
//                Rectangle{
//                    width: 15
//                    height: parent.height
//                    color: "transparent"
//                }
//            }
//            Row{
//                //anchors.left: parent.left
//                height: 40
//                spacing: 8
//                CusText{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 80
//                    height: 30
//                    fontSize: 13
//                    hAlignmentType: CusText.HALIGNMENT.AlignRight
//                    textContent: "节节麦:"
//                }
//                CusText{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 20
//                    height: 32
//                    fontSize: 13
//                    textContent: mathModel.jiejiemai+"%"
//                }
//                Rectangle{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 15
//                    height: parent.height
//                    color: "transparent"
//                }
//                CusButton_Image{
//                    anchors.verticalCenter: parent.verticalCenter
//                    btnImgNormal:"qrc:/Image/image/normal/document_normal.png"
//                    btnImgHovered:"qrc:/Image/image/normal/document_hover.png"
//                    btnImgPressed:"qrc:/Image/image/normal/document_hover.png"
//                    btnImgDisbaled:"qrc:/Image/image/normal/document_normal.png"
//                    tipText: "节节麦详情"
//                    height: 32
//                    width: 24
//                }
//            }
//            Row{
//                //anchors.left: parent.left
//                height: 40
//                spacing: 8
//                CusText{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 80
//                    height: 30
//                    fontSize: 13
//                    hAlignmentType: CusText.HALIGNMENT.AlignRight
//                    textContent: "白麦:"
//                }
//                CusText{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 20
//                    height: 32
//                    fontSize: 13
//                    textContent: mathModel.whiteWheat+"%"
//                }
//                Rectangle{
//                    width: 15
//                    height: parent.height
//                    color: "transparent"
//                }
//                CusButton_Image{
//                    anchors.verticalCenter: parent.verticalCenter
//                    btnImgNormal:"qrc:/Image/image/normal/document_normal.png"
//                    btnImgHovered:"qrc:/Image/image/normal/document_hover.png"
//                    btnImgPressed:"qrc:/Image/image/normal/document_hover.png"
//                    btnImgDisbaled:"qrc:/Image/image/normal/document_normal.png"
//                    tipText: "白麦详情"
//                    height: 32
//                    width: 24
//                }
//            }
//            Row{
//                //anchors.left: parent.left
//                height: 40
//                spacing: 8
//                CusText{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 80
//                    height: 30
//                    fontSize: 13
//                    hAlignmentType: CusText.HALIGNMENT.AlignRight
//                    textContent: "几何指标:"
//                }
//                CusText{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 20
//                    height: 32
//                    fontSize: 13
//                    textContent: "  %"
//                }
//                Rectangle{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 15
//                    height: parent.height
//                    color: "transparent"
//                }
//                CusButton_Image{
//                    anchors.verticalCenter: parent.verticalCenter
//                    btnImgNormal:"qrc:/Image/image/normal/document_normal.png"
//                    btnImgHovered:"qrc:/Image/image/normal/document_hover.png"
//                    btnImgPressed:"qrc:/Image/image/normal/document_hover.png"
//                    btnImgDisbaled:"qrc:/Image/image/normal/document_normal.png"
//                    tipText: "几何指标详情"
//                    height: 32
//                    width: 24
//                }
//            }
//            Row{
//                //anchors.left: parent.left
//                height: 40
//                spacing: 8
//                CusText{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 80
//                    height: 30
//                    fontSize: 13
//                    hAlignmentType: CusText.HALIGNMENT.AlignRight
//                    textContent: "色泽/气味:"
//                }
//                CusText{
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 20
//                    height: 32
//                    fontSize: 13
//                    textContent: "正常"
//                }
//                Rectangle{
//                    width: 15
//                    height: parent.height
//                    color: "transparent"
//                }
//            }
        }*/


        //        Row{
        //            anchors.bottom: parent.bottom
        //            anchors.bottomMargin: 30
        //            anchors.horizontalCenter: parent.horizontalCenter
        //            spacing: 40
        RadusBoder{
            id:mainRadus
            visible: !showResult
            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width-4
            height: content.height
            radus: 10
            Column
            {
                id:content
                //anchors.fill: parent
                width: parent.width
                Row{
                    width: parent.width
                    height: 40
                    CusText {
                        width: 68
                        height: 40
                        fontSize: 12
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        id:zlb
                        width: ((parent.width-68))/2
                        height: 40
                        textContent: "质量比"
                        fontSize: 12
                        textColor:"white"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        height: 40
                        width: 1
                        color: "#3C8CFF"
                    }
                    CusText {
                        width: ((parent.width-68))/2
                        height: 40
                        textContent: "颗粒比"
                        fontSize: 12
                        textColor:"white"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }
                RadusBoder{
                    width: parent.width
                    height: 1
                }
                Row{
                    width: parent.width
                    CusText {
                        property bool syclicked: false
                        id:sy
                        fontSize: 12
                        width: 68
                        height: 40
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                        textContent: "生芽:"
                        textColor: syclicked?"red":"white"
                        MouseArea {
                            enabled: isStop
                            anchors.fill: parent
                            onClicked: {
                                if(!sy.syclicked){
                                    sy.syclicked=true;
                                    //CusConfig.filtersegImgModel(2);
                                    displaysegview.isResult=true;
                                    managerMath.getSegTypeImg(2);
                                }
                                bb.bbclicked=false;
                                sm.smclicked=false;
                                cs.csclicked=false;
                                ps.psclicked=false;
                                hp.hpclicked=false;
                                binb.binbclicked=false;
                            }
                        }
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: (parent.width-68)/2
                        height: 40
                        textColor:"white"
                        textContent:  mathModel.syMassRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: (parent.width-68)/2
                        height: 40
                        textColor:"white"
                        textContent: mathModel.syParticlesRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }


                RadusBoder{
                    width: parent.width
                    height: 1
                }

                Row{
                    width: parent.width
                    CusText {
                        id:sm
                        property bool smclicked: false
                        fontSize: 12
                        width: 68
                        height: 40
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                        textContent: "生霉:"
                        textColor: smclicked?"red":"#FFFFFF"
                        MouseArea {
                            enabled: isStop
                            anchors.fill: parent
                            onClicked: {
                                if(!sm.smclicked){
                                    sm.smclicked=true;
                                    //CusConfig.filtersegImgModel(3);
                                    displaysegview.isResult=true;
                                    managerMath.getSegTypeImg(3);
                                }
                                bb.bbclicked=false;
                                sy.syclicked=false;
                                cs.csclicked=false;
                                ps.psclicked=false;
                                hp.hpclicked=false;
                                binb.binbclicked=false;
                            }
                        }
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: (parent.width-68)/2
                        height: 40
                        textColor:"white"
                        textContent: mathModel.smMassRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: (parent.width-68)/2
                        height: 40
                        textColor:"white"
                        textContent: mathModel.smParticlesRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }


                RadusBoder{
                    width: parent.width
                    height: 1
                }

                Row{
                    width: parent.width
                    CusText {
                        id:cs
                        property bool csclicked: false
                        fontSize: 12
                        width: 68
                        height: 40
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                        textContent: "虫蚀:"
                        textColor: csclicked?"red":"#FFFFFF"
                        MouseArea {
                            enabled: isStop
                            anchors.fill: parent
                            onClicked: {
                                if(!cs.csclicked){
                                    cs.csclicked=true;
                                    //CusConfig.filtersegImgModel(4);
                                    displaysegview.isResult=true;
                                    managerMath.getSegTypeImg(4);
                                }
                                bb.bbclicked=false;
                                sy.syclicked=false;
                                sm.smclicked=false;
                                ps.psclicked=false;
                                hp.hpclicked=false;
                                binb.binbclicked=false;
                            }
                        }
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: (parent.width-68)/2
                        height: 40
                        textColor:"white"
                        textContent: mathModel.csMassRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: (parent.width-68)/2
                        height: 40
                        textColor:"white"
                        textContent: mathModel.csParticlesRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }


                RadusBoder{
                    width: parent.width
                    height: 1
                }

                Row{
                    width: parent.width
                    CusText {
                        id:ps
                        property bool psclicked: false
                        fontSize: 12
                        width: 68
                        height: 40
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                        textContent: "破损:"
                        textColor: psclicked?"red":"#FFFFFF"
                        MouseArea {
                            enabled: isStop
                            anchors.fill: parent
                            onClicked: {
                                if(!ps.psclicked){
                                    ps.psclicked=true;
                                    //CusConfig.filtersegImgModel(5);
                                    displaysegview.isResult=true;
                                    managerMath.getSegTypeImg(5);
                                }
                                bb.bbclicked=false;
                                sy.syclicked=false;
                                sm.smclicked=false;
                                cs.csclicked=false;
                                hp.hpclicked=false;
                                binb.binbclicked=false;
                            }
                        }
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: (parent.width-68)/2
                        height: 40
                        textColor:"white"
                        textContent: mathModel.psMassRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: (parent.width-68)/2
                        height: 40
                        textColor:"white"
                        textContent: mathModel.psParticlesRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }


                RadusBoder{
                    width: parent.width
                    height: 1
                }

                Row{
                    width: parent.width
                    visible: mathModel.wheatUnsoundType===1 ? true:false
                    CusText {
                        id:hp
                        property bool hpclicked: false
                        fontSize: 12
                        width: 68
                        height: 40
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                        textContent: "黑胚:"
                        textColor:hpclicked?"red":"#FFFFFF"
                        MouseArea {
                            enabled: isStop
                            anchors.fill: parent
                            onClicked: {
                                if(!hp.hpclicked){
                                    hp.hpclicked=true;
                                    //CusConfig.filtersegImgModel(6);
                                    displaysegview.isResult=true;
                                    managerMath.getSegTypeImg(6);
                                }
                                bb.bbclicked=false;
                                sy.syclicked=false;
                                sm.smclicked=false;
                                cs.csclicked=false;
                                ps.psclicked=false;
                                binb.binbclicked=false;
                            }
                        }
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: (parent.width-68)/2
                        height: 40
                        textColor:"white"
                        textContent:  mathModel.hpMassRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: (parent.width-68)/2
                        height: 40
                        textColor:"white"
                        textContent: mathModel.hpParticlesRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }
                RadusBoder{
                    width: parent.width
                    visible: mathModel.wheatUnsoundType===1 ? true:false
                    height: 1
                }
                Row{
                    width: parent.width
                    visible: mathModel.wheatUnsoundType===1 ? true:false
                    CusText {
                        id:bb
                        property bool bbclicked: false
                        width: 68
                        height: 40
                        fontSize: 12
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                        textContent: "赤霉:"
                        textColor: bbclicked?"red":"#FFFFFF"
                        MouseArea {
                            enabled: isStop
                            anchors.fill: parent
                            onClicked: {
                                if(!bb.bbclicked){
                                    bb.bbclicked=true;
                                    //CusConfig.filtersegImgModel(1);
                                    displaysegview.isResult=true;
                                    managerMath.getSegTypeImg(1);
                                }
                                sy.syclicked=false;
                                sm.smclicked=false;
                                cs.csclicked=false;
                                ps.psclicked=false;
                                hp.hpclicked=false;
                                binb.binbclicked=false;
                            }
                        }
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: (parent.width-68)/2
                        height: 40
                        textColor:"white"
                        textContent: mathModel.bbMassRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: (parent.width-68)/2
                        height: 40
                        textColor:"white"
                        textContent: mathModel.bbParticlesRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }
                RadusBoder{
                    visible: mathModel.wheatUnsoundType===1 ? true:false
                    width: parent.width
                    height: 1
                }
                Row
                {
                    width: parent.width
                    CusText {
                        id:binb
                        property bool binbclicked: false
                        wrap:TextInput.WordWrap
                        fontSize: 12
                        width: 68
                        height: mathModel.wheatUnsoundType===1 ? 42:40
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                        textContent: mathModel.wheatUnsoundType===1 ? "病斑(黑胚+赤霉)":"病斑:"
                        textColor: binbclicked?"red":"#FFFFFF"
                        MouseArea {
                            enabled: isStop
                            anchors.fill: parent
                            onClicked: {
                                if(!binb.binbclicked){
                                    binb.binbclicked=true;
                                    //CusConfig.filtersegImgModel(1);
                                    displaysegview.isResult=true;
                                    if(mathModel.wheatUnsoundType===1){
                                        managerMath.getSegTypeImg(7);
                                    }else if(mathModel.wheatUnsoundType===2){
                                         managerMath.getSegTypeImg(1);
                                    }
                                   console.log(mathModel.wheatUnsoundType);
                                }
                                sy.syclicked=false;
                                sm.smclicked=false;
                                cs.csclicked=false;
                                ps.psclicked=false;
                                hp.hpclicked=false;
                                bb.bbclicked=false;
                            }
                        }
                    }
                    Rectangle{
                        width: 1
                        height: 42
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: (parent.width-68)/2
                        height: 42
                        textColor:"white"
                        textContent: mathModel.binbMassRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        height: 42
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: (parent.width-68)/2
                        height: 42
                        textColor:"white"
                        textContent: mathModel.binbParticlesRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }

                RadusBoder{
                    width: parent.width
                    height: 1
                }
                Row{
                    width: parent.width
                    id:rowBottom
                    CusText {
                        fontSize: 12
                        width: 68
                        height: 40
                        textColor:"white"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                        textContent: "总计:"
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: (parent.width-68)/2
                        height: 40
                        textColor:"white"
                        textContent: mathModel.massRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: (parent.width-68)/2
                        height: 40
                        textColor:"white"
                        textContent:mathModel.particlesRatio+"%"

                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }
            }
        }

        Rectangle{
            id:space
            anchors.left: parent.left
            anchors.top: mainRadus.bottom
            width: parent.width
            height: 40
            color: "transparent"
            CusButton_Image{
                id:history
                visible: isStop
                anchors.centerIn: parent
                width: 22
                height: 23
                btnImgNormal:"qrc:/Image/image/normal/history_record.png"
                btnImgHovered:"qrc:/Image/image/normal/history_record.png"
                btnImgPressed:"qrc:/Image/image/normal/history_record.png"
                onClicked: {
                    recordManager.getRocoedData("","");
                    stack.currentIndex=3;
                }
            }


        }
        RadusBoder{
            visible: !showResult
            anchors.left: parent.left
            anchors.top: space.bottom
            height: whitezb.height
            width: parent.width-2
            radus: 10
            Column{
                id:whitezb
                width: parent.width
                Row{
                    width: parent.width
                    height: 40
                    CusText {
                        width: 68
                        height: 40
                        fontSize: 12
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        width: ((parent.width-68))/2
                        height: 40
                        textContent: "质量比"
                        fontSize: 12
                        textColor: "white"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        height: 40
                        width: 1
                        color: "#3C8CFF"
                    }
                    CusText {
                        width: ((parent.width-68))/2
                        height: 40
                        textContent: "颗粒比"
                        fontSize: 12
                        textColor: "white"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }

                RadusBoder{
                    width: parent.width
                    height: 1
                }

                Row{
                    width: parent.width
                    CusText {
                        id:whitewheat
                        width: 68
                        height: 40
                        fontSize: 12
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                        textContent: "白麦率:"
                        textColor: "white"
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: ((parent.width-68))/2
                        height: 40
                        textColor: "white"
                        textContent: mathModel.m_white_weight_Wheat+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: ((parent.width-68))/2
                        height: 40
                        textColor: "white"
                        textContent: mathModel.white_count_Wheat+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }

                RadusBoder{
                    width: parent.width
                    height: 1
                }
                Row{
                    width: parent.width
                    CusText {
                        id:redwheat
                        width: 68
                        height: 40
                        fontSize: 12
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                        textContent: "红麦率:"
                        textColor: "white"
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: ((parent.width-68))/2
                        height: 40
                        textColor: "white"
                        textContent: mathModel.red_weight_Wheat+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "#3C8CFF"
                    }
                    CusText {
                        fontSize: 12
                        width: ((parent.width-68))/2
                        height: 40
                        textColor: "white"
                        textContent: mathModel.red_count_Wheat+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }
            }
        }
        CusRadusButton{
            width: 40
            height: 40
            radius: 20
            visible: !isStop
            id:statusBtn
            selected: boardControl.isPause
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30
            anchors.left: parent.left
            anchors.leftMargin:(parent.width - width-40)/2
            backgroundColorNormal: "transparent"
            backgroundColorHovered: "transparent"
            backgroundColorEnable: "transparent"
            pressed_img:"qrc:/Image/image/normal/pause.png"
            noraml_img:"qrc:/Image/image/normal/start.png"
            enable_img:"qrc:/Image/image/Window/start_enable.png"
            onClicked: {
                //isStop=!isStop
                //selected=!selected;
                if(!selected){
                    boardControl.startTask("");
                }else{
                    boardControl.pauseTask();
                }
                //stopbtn.enabled=true;
            }
        }
        CusButton_Image{
            id:stopButton
            //visible: !isStop
            visible: false
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30
            anchors.left: statusBtn.right
            anchors.leftMargin: 40
            width: 32
            height: 32
            btnImgNormal:"qrc:/Image/image/normal/stop.png"
            btnImgHovered:"qrc:/Image/image/normal/stop_hover.png"
            btnImgPressed:"qrc:/Image/image/normal/stop_hover.png"
            btnImgDisbaled: "qrc:/Image/image/normal/stop_enable.png"
            onClicked: {
                //statusBtn.selected=false;
                boardControl.stopTask();
                //managerMath.timerStop();
                //test
                //managerMath.dynamicResult();

                //displaysegview.timerStop();
                enabled=false;
                statusBtn.enabled=false;
            }
        }
        CusRadusButton{
            width: 72
            height: 72
            radius: 0
            visible: isStop
            id:backtoid
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30
            anchors.left: parent.left
            anchors.leftMargin:(parent.width - width-40-stopButton.width)/2
            backgroundColorNormal: "transparent"
            backgroundColorHovered: "transparent"
            pressed_img:"qrc:/Image/image/normal/back_normal.png"
            noraml_img:"qrc:/Image/image/normal/back_normal.png"
            onClicked: {
                //selected=!selected;
                //stopbtn.enabled=true;
                stack.currentIndex=1;
                resultPane.reset();
                displaysegview.isResult=false;
                mathModel.clear();
            }
        }

        CusButton_Image{
            id:printf
            visible: isStop
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30
            anchors.left: statusBtn.right
            anchors.leftMargin: 40
            width: 40
            height: 40
            btnImgNormal:"qrc:/Image/image/normal/printer_normal.png"
            btnImgHovered:"qrc:/Image/image/normal/printer_hover.png"
            btnImgPressed:"qrc:/Image/image/normal/printer_hover.png"
            onClicked: {
                recordManager.printResult();
            }
        }

        DetectResultPane{
            x: width
            y:10
            id:resultPane
            width: parent.width
        }
        //}
    }

    //    Column{
    //        visible: !showResult
    //        x: isStop?parent.width-width:parent.width
    //        anchors.verticalCenter: parent.verticalCenter
    //        spacing: 25
    //        //        CusShape_Button{
    //        //            isOpen: true
    //        //            width: 48
    //        //            height: 88
    //        //            z:10
    //        //            onBtnClicked: {
    //        //                showResult=true;
    //        //                resultPane.x=10
    //        //                resultPane.y=10
    //        //            }
    //        //        }
    //        CusShape_Button{
    //            isOpen: false
    //            width: 48
    //            height: 88
    //            z:10
    //            onBtnClicked: {
    //                recordManager.getRocoedData("","");
    //                stack.currentIndex=3;
    //            }
    //        }
    //        Behavior on x{
    //            NumberAnimation{
    //                duration: 200
    //            }
    //        }
    //    }
    function detectResulrReset(){
        resultPane.reset();
    }
    function setStartBtn(){
        //statusBtn.selected=true;
        stopButton.enabled=true;
        statusBtn.enabled=true;
        sy.syclicked=false;
        sm.smclicked=false;
        cs.csclicked=false;
        ps.psclicked=false;
        hp.hpclicked=false;
        bb.bbclicked=false;
        binb.binbclicked=false
    }
    Connections{
        target: boardControl
//        onSigStoptask:{
//            statusBtn.enabled=false;
//            stopButton.enabled=false;
//        }
    }
}

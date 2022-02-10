import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml 2.12
import "../../common"
import "../.."
Item {
    id:resultRoot
    height:330
    Rectangle{
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        height: parent.height
        radius: 10
        border.width: 1
        border.color: "#000000"
        color: "transparent"
        Row{
            anchors.fill: parent
            CusButton_Image{
                id:close
                btnImgNormal:"qrc:/Image/image/normal/open_hover.png"
                btnImgHovered:"qrc:/Image/image/normal/open_normal.png"
                btnImgPressed:"qrc:/Image/image/normal/open_normal.png"
                btnImgDisbaled:"qrc:/Image/image/normal/open_normal.png"
                //anchors.verticalCenter: parent.verticalCenter
                //y:(content.height-height)/2
                //anchors.left: parent.left
                x:4
                y:(parent.height-height)/2
                width: 34
                height: 34
                onClicked: {
                    showResult=false
                    resultRoot.x=resultRoot.width
                }
            }
            Column{
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
                        color: "black"
                    }
                    CusText {
                        width: 68
                        height: 40
                        textContent: "质量比"
                        fontSize: 12
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        height: 40
                        width: 1
                        color: "black"
                    }
                    CusText {
                        width: 78
                        height: 40
                        textContent: "颗粒比"
                        fontSize: 12
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }

                Rectangle{
                    width: parent.width
                    height: 1
                    color: "black"
                }


                Row{
                    CusText {
                        id:bb
                        property bool bbclicked: false
                        width: 68
                        height: 40
                        fontSize: 12
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                        textContent: "赤霉:"
                        textColor: bbclicked?"red":"#000000"
                        MouseArea {
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
                            }
                        }
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "black"
                    }
                    CusText {
                        fontSize: 12
                        width: 68
                        height: 40
                        textContent: mathModel.bbMassRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "black"
                    }
                    CusText {
                        fontSize: 12
                        width: 78
                        height: 40
                        textContent: mathModel.bbParticlesRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }



                Rectangle{
                    width: parent.width
                    height: 1
                    color: "black"
                }
                Row{
                    CusText {
                        property bool syclicked: false
                        id:sy
                        fontSize: 12
                        width: 68
                        height: 40
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                        textContent: "生芽:"
                        textColor: syclicked?"red":"#000000"
                        MouseArea {
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
                            }
                        }
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "black"
                    }
                    CusText {
                        fontSize: 12
                        width: 68
                        height: 40
                        textContent:  mathModel.syMassRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "black"
                    }
                    CusText {
                        fontSize: 12
                        width: 78
                        height: 40
                        textContent: mathModel.syParticlesRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }


                Rectangle{
                    width: parent.width
                    height: 1
                    color: "black"
                }

                Row{
                    CusText {
                        id:sm
                        property bool smclicked: false
                        fontSize: 12
                        width: 68
                        height: 40
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                        textContent: "生霉:"
                        textColor: smclicked?"red":"#000000"
                        MouseArea {
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
                            }
                        }
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "black"
                    }
                    CusText {
                        fontSize: 12
                        width: 68
                        height: 40
                        textContent: mathModel.smMassRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "black"
                    }
                    CusText {
                        fontSize: 12
                        width: 78
                        height: 40
                        textContent: mathModel.smParticlesRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }


                Rectangle{
                    width: parent.width
                    height: 1
                    color: "black"
                }

                Row{
                    CusText {
                        id:cs
                        property bool csclicked: false
                        fontSize: 12
                        width: 68
                        height: 40
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                        textContent: "虫蚀:"
                        textColor: csclicked?"red":"#000000"
                        MouseArea {
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
                            }
                        }
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "black"
                    }
                    CusText {
                        fontSize: 12
                        width: 68
                        height: 40
                        textContent: mathModel.csMassRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "black"
                    }
                    CusText {
                        fontSize: 12
                        width: 78
                        height: 40
                        textContent: mathModel.csParticlesRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }


                Rectangle{
                    width: parent.width
                    height: 1
                    color: "black"
                }

                Row{
                    CusText {
                        id:ps
                        property bool psclicked: false
                        fontSize: 12
                        width: 68
                        height: 40
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                        textContent: "破损:"
                        textColor: psclicked?"red":"#000000"
                        MouseArea {
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

                            }
                        }
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "black"
                    }
                    CusText {
                        fontSize: 12
                        width: 68
                        height: 40
                        textContent: mathModel.psMassRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "black"
                    }
                    CusText {
                        fontSize: 12
                        width: 78
                        height: 40
                        textContent: mathModel.psParticlesRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }


                Rectangle{
                    width: parent.width
                    height: 1
                    color: "black"
                }

                Row{
                    CusText {
                        id:hp
                        property bool hpclicked: false
                        fontSize: 12
                        width: 68
                        height: 40
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                        textContent: "黑胚:"
                        textColor:hpclicked?"red":"#000000"
                        MouseArea {
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
                            }
                        }
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "black"
                    }
                    CusText {
                        fontSize: 12
                        width: 68
                        height: 40
                        textContent:  mathModel.hpMassRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "black"
                    }
                    CusText {
                        fontSize: 12
                        width: 78
                        height: 40
                        textContent: mathModel.hpParticlesRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }


                Rectangle{
                    width: parent.width
                    height: 1
                    color: "black"
                }
                Row{
                    id:rowBottom
                    CusText {
                        fontSize: 12
                        width: 68
                        height: 40
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                        textContent: "总计:"
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "black"
                    }
                    CusText {
                        fontSize: 12
                        width: 68
                        height: 40
                        textContent: mathModel.massRatio+"%"
                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        height: 40
                        color: "black"
                    }
                    CusText {
                        fontSize: 12
                        width: 78
                        height: 40
                        textContent:mathModel.particlesRatio+"%"

                        hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                        vAlignmentType:CusText.VALIGNMENT.AlignVCenter
                    }
                }
            }
        }
    }
    Behavior on x{
        NumberAnimation{
            duration: 200
        }
    }
    function reset(){
        bb.bbclicked=false;
        sy.syclicked=false;
        sm.smclicked=false;
        cs.csclicked=false;
        ps.psclicked=false;
        hp.hpclicked=false;
        showResult=false;
        resultPane.x=resultPane.width
         CusConfig.showSegmodel.clear();
         CusConfig.segmentModel.clear();
         managerMath.clearImg();
    }

    Connections{
        target: managerMath
//         onSigresultImg:{
//            CusConfig.filtersegImgModel(fileName);
//        }
    }
}

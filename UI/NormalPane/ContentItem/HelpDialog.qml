import QtQuick 2.12
import QtQuick.Controls 2.5
import "../../common"
Popup{
    id:helpDialog
    width: 400
    height: 400
    leftMargin: 0
    closePolicy:Popup.NoAutoClose
    modal: true
    anchors.centerIn: Overlay.overlay

    background: RadusBoder{
        Rectangle{
            //anchors.fill: parent
            color: "#010512"
            anchors.left: parent.left
            anchors.leftMargin: 1
            anchors.top: parent.top
            anchors.topMargin: 1
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 1
            anchors.right: parent.right
            anchors.rightMargin: 1
            radius: 8
        }
        radus: 8
    }

    contentItem: Item {
        id: name
        Column{
            anchors.fill: parent
            Row{
                height: 40
                width: parent.width
                layoutDirection: Qt.RightToLeft
                Label{
                    width: 10
                }

                CusButton_Image{
                    btnImgUrl:hovered?"qrc:/Image/image/normal/closeDialoghover.png" :"qrc:/Image/image/normal/closeDialoghover.png"
                    btnImgNormal:"qrc:/Image/image/normal/closeDialoghover.png"
                    btnImgHovered: "qrc:/Image/image/normal/closeDialoghover.png"
                    btnImgPressed:"qrc:/Image/image/normal/closeDialoghover.png"
                    onClicked: {
                        close();
                    }
                }
            }
            Row{
                Column{
                    id:toolbar
                    width: 120
                    spacing:20
                    RadusBoder{
                        radus: 5
                        width: ljgd.width+2
                        height: ljgd.height+2
                        CusRadusButton{
                            id:ljgd
                            anchors.left: parent.left
                            anchors.leftMargin: 1
                            anchors.top: parent.top
                            anchors.topMargin: 1
                            backgroundColorNormal:"#010512"
                            backgroundColorHovered:"#010512"
                            text: "了解更多"
                            textColor: "white"
                            onClicked: {
                                Qt.openUrlExternally("http://gaozhe.com.cn/");
                            }
                        }
                    }

                    RadusBoder{
                        radus: 5
                        width: gy.width+2
                        height: gy.height+2
                        CusRadusButton{
                            id:gy
                            anchors.left: parent.left
                            anchors.leftMargin: 1
                            anchors.top: parent.top
                            anchors.topMargin: 1
                            backgroundColorNormal:"#010512"
                            backgroundColorHovered:"#010512"
                            textColor: "white"
                            text: "关于"
                        }
                    }
                    RadusBoder{
                        radus: 5
                        width: sc.width+2
                        height: sc.height+2
                        CusRadusButton{
                            id:sc
                            anchors.left: parent.left
                            anchors.leftMargin: 1
                            anchors.top: parent.top
                            anchors.topMargin: 1
                            backgroundColorNormal:"#010512"
                            backgroundColorHovered:"#010512"
                            text: "手册"
                            textColor: "white"
                            onClicked:{
                                managerMath.openchm();
                            }
                        }
                    }
                }
                SwipeView{
                    width: helpDialog.width-toolbar.width
                    height:helpDialog.height-40
                    interactive: false
                    clip: true
                    currentIndex: 0
                    Item{
                        Column{
                            anchors.fill: parent
                            Column{
                                spacing: 10
                                width: parent.width
                                //anchors.verticalCenter: parent.verticalCenter
                                CusText {
                                    width: parent.width
                                    height: 40
                                    textColor: "white"
                                    textContent: "当前软件版本:2021831112321"
                                    hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                                    fontSize: 12
                                }
                                CusText {
                                    width: parent.width
                                    height: 40
                                    fontSize: 12
                                    textColor: "white"
                                    textContent: "当前算法版本:2021831112321"
                                    hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                                }
                                CusText {
                                    width: parent.width
                                    height: 40
                                    fontSize: 12
                                    textColor: "white"
                                    textContent: "当前硬件版本:2021831112321"
                                    hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                                }
                            }

                            //                            Row{
                            //                                width: parent.width
                            //                                layoutDirection: Qt.RightToLeft
                            //                                CusRadusButton{
                            //                                    backgroundColorNormal:"#ffffff"
                            //                                    backgroundColorHovered:"#cdcdcd"
                            //                                    text: "检查更新"
                            //                                }
                            //                            }
                        }
                    }
                }
            }
        }
        RadusBoder{
            radus: 5
            width: jcgx.width+2
            height: jcgx.height+2
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.bottomMargin: 10
            anchors.rightMargin: 10
            CusRadusButton{
                id:jcgx
                anchors.left: parent.left
                anchors.leftMargin: 1
                anchors.top: parent.top
                anchors.topMargin: 1

                backgroundColorNormal:"#010512"
                backgroundColorHovered:"#010512"
                text: "检查更新"
                textColor: "white"
            }
        }
    }

}


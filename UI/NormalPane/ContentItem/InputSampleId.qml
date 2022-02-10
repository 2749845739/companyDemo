import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.12
import "../.."
import "../../common"
Item {
    property alias inputControl: inputid.content
    Rectangle{
        anchors.centerIn : parent
        color: "transparent"
        Row{
            id:rowInput
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            spacing: 10
            height: 40
//            Text {
//                text: "样本编号:"
//                horizontalAlignment: Text.AlignHCenter
//                verticalAlignment: Text.AlignVCenter
//            }
            Image {
                id: sampleidinput
                source: "qrc:/Image/image/normal/sampleid.png"
                width: sourceSize.width
                height: sourceSize.height
            }
            Item {
                width: 308
                height: 28
                Rectangle{
                    id:sampleidinputbackground
                    anchors.fill: parent
                    visible: false
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color: "#00C8D2" }
                        GradientStop { position: 1.0; color: "#3C8CFF" }
                    }
                }

                Rectangle{
                    id:mask
                    anchors.fill: parent
                    radius: 10
                    border.width: 1
                    color: "transparent"
                    visible: false
                }

                OpacityMask {
                    id: opM
                    anchors.fill: parent
                    source: sampleidinputbackground
                    maskSource: mask
                }
                CusInputText{
                    id:inputid
                    anchors.left: parent.left
                    anchors.top: parent.top
                    width: 300
                    height: 28
                }
            }


        }
        CusRadusButton{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:rowInput.bottom
            anchors.topMargin: 10
            id:statusBtn
            width: 60
            height: 60
            radius: 0
            backColor: "transparent"
            backgroundColorNormal: "transparent"
            backgroundColorHovered: "transparent"
            pressed_img:"qrc:/Image/image/normal/startDectect.png"
            noraml_img:"qrc:/Image/image/normal/startDectect.png"
            onClicked: {
                //selected=!selected;
                stack.currentIndex=2;
                //managerMath.processData(0);
                boardControl.startTask(inputid.content);
                detection.setStartBtn();

                managerMath.clearDir();
                //managerMath.timerStart();
                CusConfig.homeEnable=false;
            }
        }
    }
}

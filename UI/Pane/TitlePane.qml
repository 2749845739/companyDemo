import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml 2.12
import "../common"
Item {
    property bool isMax: view.isMax
    CusDialog{
        id:dialogClose
        anchors.centerIn: Overlay.overlay
        visible: false
        height: visible?100:0
        width: visible?200:0
        title: visible?"Title":""
        onAccepted: {
            view.close();
        }
        closePolicy: Popup.NoAutoClose
    }
    Rectangle{
        anchors.fill: parent
        color: "#3a3a3a"
        Row{
            id:toolRow
            anchors.right: parent.right
            height: 24
            spacing: 20
            anchors.rightMargin: 20
            layoutDirection:Qt.RightToLeft
            anchors.verticalCenter: parent.verticalCenter
            CusButton_Image{
                id:close
                //anchors.right: parent.right
                width: 24
                height: 24
                btnImgUrl: hovered||pressed ? "qrc:/Image/image/Window/close_white.png":"qrc:/Image/image/Window/close_gray.png"
                tipText: "关闭"
                onClicked: {
                    dialogClose.open();
                }
            }
            CusButton_Image{
                id:max
                //anchors.right: close.right
                visible: !isMax
                width: 24
                height: 24
                btnImgUrl: hovered||pressed ? "qrc:/Image/image/Window/max_white.png":"qrc:/Image/image/Window/max_gray.png"
                tipText: "最大化"
                onClicked: {
                    view.showMaximized();
                }
            }
            CusButton_Image{
                id:normal
                //anchors.right: close.right
                visible: isMax
                width: 24
                height: 24
                btnImgUrl: hovered||pressed ? "qrc:/Image/image/Window/normal_white.png":"qrc:/Image/image/Window/normal_gray.png"
                tipText: "还原"
                onClicked: {
                    view.showNormal();
                }
            }
            CusButton_Image{
                //anchors.right: max.left
                id:min
                width: 24
                height: 24
                btnImgUrl: hovered||pressed ? "qrc:/Image/image/Window/minimal_white.png":"qrc:/Image/image/Window/minimal_gray.png"
                tipText: "最小化"
                onClicked: {
                    view.showMinimized();
                }
            }
        }

        Item {
            id: blankItem
            objectName: "blankItem"
            height: parent.height
            anchors.left: parent.left
            anchors.right: toolRow.left
            Component.onCompleted: {
                view.setTitleItem(blankItem)
            }
            MouseArea{
                anchors.fill: parent
                property int lastX: 0
                property int lastY: 0
                onContainsPressChanged: {
                    if(containsPress){
                        cursorShape = Qt.SizeAllCursor
                        lastX = mouseX
                        lastY = mouseY
                    }else {
                        cursorShape = Qt.ArrowCursor
                    }
                }
                onPositionChanged: {
                    if(pressed){
                        if ((mouseX - lastX) !== 0 || (mouseY - lastY) !== 0)
                        {
                            view.x+=mouseX - lastX;
                            view.y+=mouseY - lastY;
                        }
                    }
                }
            }
        }
    }
}

import QtQuick 2.12
import QtQuick.Controls 2.12
Rectangle {
    id:root
    property alias imgsouce: picture.source
    Flickable {
        id: view
        anchors.fill: parent
        contentWidth: parent.width
        contentHeight: parent.height
        clip: true
        property var ratioX;
        property var ratioY;
        MouseArea{
            property int imgWidth:parent.width
            property int imgheight:parent.height
            anchors.fill: parent
            onWheel: {
                if (wheel.modifiers & Qt.ControlModifier) {
                } else {
                    view.ratioX=mouseX/view.contentWidth;
                    view.ratioY=mouseX/view.contentHeight;
                    imgWidth+=imgWidth * wheel.angleDelta.y / 120 / 10;
                    imgheight+=imgheight * wheel.angleDelta.y / 120 / 10;
                    if(imgheight<root.height){
                        imgheight=root.height
                    }
                    if(imgWidth<root.width){
                        imgWidth=root.width
                    }
                    view.contentWidth = imgWidth;
                    view.contentHeight = imgheight;
                    picture.width=view.contentWidth;
                    picture.height=view.contentHeight;
                    view.contentY+=view.contentY*wheel.angleDelta.y / 120 / 10;
                    view.contentX+=view.contentX*wheel.angleDelta.y / 120 / 10;
                }
            }
        }
        Image {
            id: picture
            anchors.fill: parent
            cache: false
            //source: "pics/1.png"
        }
    }
    color: "#000000"
}

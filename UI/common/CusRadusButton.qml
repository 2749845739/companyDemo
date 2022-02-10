import QtQuick 2.12
import QtQuick.Controls 2.5
import "../"
Button {
    id: cusButton
    height: CusConfig.fixedHeight
    property string enable_img
    property string noraml_img
    property string pressed_img
    property string hovered_img
    property bool selected: false
    property color backgroundColorNormal
    property color backgroundColorEnable
    property color backgroundColorHovered
    property color backgroundColorSelected
    property int fontsize: 20
    property color backColor: {
        if(!cusButton.enabled){
            return backgroundColorEnable
        }
            //return backgroundColorHovered
        else if(selected){
            return backgroundColorSelected
        }else{
            return backgroundColorNormal
        }
    }

    property  string imgSource:{
        if (!cusButton.enabled) {
            return enable_img
        } else if (cusButton.pressed || selected) {
            return pressed_img
        } else {
            return noraml_img
        }
    }

    property int radius: 4
    BasicTooptip {
        id: toolTip
        visible: cusButton.hovered && String(text).length
        delay: 500
    }
    property color textColor:"white"
    contentItem: Text {
        text: cusButton.text
        color: cusButton.textColor
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: fontsize
        Image {
            id: img
            anchors.centerIn: parent
            width: sourceSize.width
            height: sourceSize.height
            source: imgSource
        }
    }
    background: Rectangle {
        radius: cusButton.radius
        color: backColor
//        border.color: cusButton.borderColor
//        border.width: cusButton.borderWidth
    }
}

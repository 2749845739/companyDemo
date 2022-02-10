import QtQuick 2.0
import QtQuick.Controls 2.5
import "."
import ".."
Button {
    id: cusButton
    height: CusConfig.fixedHeight

    property alias tipText: toolTip.text
    property alias imgSource: img.source
    property alias tipItem: toolTip
    property alias tipVisible: toolTip.visible
    property alias tipDelay: toolTip.delay
    property alias tipTimeout: toolTip.timeout
    property bool selected: false
    property color backgroundColorNormal
    property color backgroundColorHovered
    property color backgroundColorPressed
    property color backgroundColorDisable
    property bool imgvisable: false
    property color borderColor: {
        if (!cusButton.enabled) {
            return CusConfig.controlBorderColor_disabled
        } else if (cusButton.pressed || selected) {
            return CusConfig.controlBorderColor_pressed
        } else if (cusButton.hovered) {
            return CusConfig.controlBorderColor_hovered
        } else {
            return CusConfig.controlBorderColor
        }
    }
    property int borderWidth: 1
    property int radius: 4
    property color textColor: {
        if (!cusButton.enabled) {
            return CusConfig.textColor_disabled
        } else if (cusButton.pressed || selected) {
            return CusConfig.textColor_pressed
        } else if (cusButton.hovered) {
            return CusConfig.textColor_hovered
        } else {
            return CusConfig.textColor
        }
    }
    property color backgroundColor: {
        if (!cusButton.enabled) {
            return backgroundColorDisable
        } else if (cusButton.pressed ||selected) {
            return backgroundColorPressed
        } else if (cusButton.hovered) {
            return backgroundColorHovered
        } else {
            return backgroundColorNormal
        }
    }

    BasicTooptip {
        id: toolTip
        visible: cusButton.hovered && String(text).length
        delay: 500
    }
    contentItem: Text {
        text: cusButton.text
        color: cusButton.textColor
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        Image {
            id: img
            anchors.right : parent.right
            anchors.leftMargin: 4
            width: sourceSize.width
            height: sourceSize.height
            source: "qrc:/Image/image/Window/expand.png"
            visible: imgvisable
            rotation : selected ?  180 : 0
            Behavior on rotation{
                NumberAnimation {
                    duration: 300
                }
            }
        }
    }
    background: Rectangle {
        radius: cusButton.radius
        color: cusButton.backgroundColor
        border.color: cusButton.borderColor
        border.width: cusButton.borderWidth
    }
}

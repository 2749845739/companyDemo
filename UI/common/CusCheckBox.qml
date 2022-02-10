import QtQuick 2.12
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

CheckBox {
    id: cusCheckBox
    implicitHeight: 30
    checked: false
    contentItem: Label {
        leftPadding: cusCheckBox.indicator.width + cusCheckBox.spacing
        text: cusCheckBox.text
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
        color: cusCheckBox.enabled ? "black":"black"
    }
    property color colorNormal: "#373737"
    property color colorHovered: "#d50d4f"
    property color colorPressed: "#d50d4f"
    property color colorDisable: "#d50d4f"
    readonly property string imgUrlCheck: "qrc:/Image/image/Window/Check.png"

    Image {
        id: baseImgCheck
        smooth: true
        visible: false
        source: "qrc:/Image/image/Window/Check.png"
        width: sourceSize.width
        height: sourceSize.height
    }

    indicator: Rectangle {
        implicitWidth: 24
        implicitHeight: 24
        x: cusCheckBox.leftPadding
        y: (cusCheckBox.height - height) / 2
        color: cusCheckBox.enabled ? "#f5f5f6" : "#9f9fcf"
        radius: 4
        border.width: 1
        border.color: cusCheckBox.pressed ? "#f5f5f6" : (cusCheckBox.hovered ? "#d50d4f" : "#f5f5f6")
        ColorOverlay {
            id: indicatorImg
            source: baseImgCheck
            width: baseImgCheck.width
            height: baseImgCheck.height
            anchors.centerIn: parent
            cached: true
            visible: cusCheckBox.checked
            color: {
                if (!cusCheckBox.enabled) {
                    return colorDisable
                } else if (cusCheckBox.pressed) {
                    return colorPressed
                } else if (cusCheckBox.hovered) {
                    return colorHovered
                } else {
                    return colorPressed
                }
            }
        }
    }
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        propagateComposedEvents: true
        //鼠标图标， hovered 或者 pressed时显示此图标
        cursorShape: enabled ? Qt.PointingHandCursor : Qt.ForbiddenCursor
        onDoubleClicked: { mouse.accepted = false;}
        onPositionChanged: { mouse.accepted = false;}
        onPressed:  {  mouse.accepted = false; }
        onPressAndHold: { mouse.accepted = false; }
        onClicked:  { mouse.accepted = false;}
        onReleased: { mouse.accepted = false;}
        onWheel: { wheel.accepted = false; }
    }
}


import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

Item {
    property int inputWidth: 200
    property int inputHeight: 30
    property alias value: input.text
    signal show();
    width: inputWidth
    height: inputHeight
    property color backgroundColor: "transparent"
    TextField{
        id:input
        anchors.fill: parent
        validator:RegExpValidator{ regExp: /\b\d{4,4}-\d{2,2}-\d{2,2}\s\d{2,2}:\d{2,2}:\d{2,2}\b\$/}
        focus: true
        hoverEnabled: enabled
        selectByMouse: true
        color: "white"
        maximumLength: 19
        selectionColor: "#d50d4f"
        selectedTextColor: "#d50d4f"
        font.pixelSize: 12
        Image {
            id:imgclose
            source: "qrc:/Image/image/normal/Calendar.png"
            smooth: true
            visible: false
            width: sourceSize.width
            height: sourceSize.height
        }
        background: Rectangle {
//            border.width: 1
//            border.color:"#000000"
            radius: 2
            color: "transparent"
            Button{
                id:btnIput
                anchors.right:parent.right
                anchors.top:parent.top
                anchors.bottom:parent.bottom
                width: 40
                background: Rectangle{
                     ColorOverlay{
                         //visible: input.length>0?true:false
                         source: imgclose
                         width: imgclose.width
                         height: imgclose.height
                         anchors.centerIn: parent
                         cached: true
//                         color: {
//                             if (!btnIput.enabled) {
//                                 return ""
//                             } else if (btnIput.pressed) {
//                                 return "#707070"
//                             } else if (btnIput.hovered) {
//                                 return "#515151"
//                             } else {
//                                 return ""
//                             }
//                         }
                     }
                     color: backgroundColor
                }
                onClicked: {
                   show();
                }
            }
        }
    }
}

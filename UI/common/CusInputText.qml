import QtQuick 2.15
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
Item {
    property int inputWidth: 200
    property int inputHeight: 30
    property alias content: input.text
     property alias textinput: input
    property int maxlength: 12
    property int fontsize: 19
    property string placeTextContent: ""
    property color textColor : "#967A50"
    property string textContent : ""
    width: inputWidth
    height: inputHeight
    property color backgroundColor: "transparent"
    property int halignment:Text.AlignLeft
    property int valignment:Text.AlignVCenter
    property bool closebutton: false
    TextField{
        id:input
        anchors.fill: parent
        //validator:RegExpValidator{ regExp:/d|[A-Z]|[a-z]+/ }
        focus: true
        hoverEnabled: enabled
        selectByMouse: true
        color: textColor
        maximumLength: maxlength
        selectionColor: "#9F9F9F"
        selectedTextColor: "#000000"
        font.pixelSize: fontsize
        horizontalAlignment: halignment
        verticalAlignment: valignment
        placeholderText:placeTextContent
        placeholderTextColor: "#bfbfbf"
        text: textContent
        validator: RegularExpressionValidator { regularExpression: /[0-9A-Za-z-*#@~]+/ }
        Image {
            id:imgclose
            source: "qrc:/Image/image/normal/Search_Clear.png"
            smooth: true
            visible: false
            width: sourceSize.width
            height: sourceSize.height
        }
        background: Rectangle {
            border.width: 2
            border.color:input.hovered?"#000000":"#bfbfbf"
            radius: 8
            Button{
                id:btnIput
                visible: closebutton
                anchors.right:parent.right
                anchors.rightMargin: 20
                anchors.top:parent.top
                anchors.bottom:parent.bottom
                width: 24
                background: Rectangle{
                     ColorOverlay{
                         visible: input.length>0?true:false
                         source: imgclose
                         width: imgclose.width
                         height: imgclose.height
                         anchors.centerIn: parent
                         cached: true
                         color: {
                             if (!btnIput.enabled) {
                                 return ""
                             } else if (btnIput.pressed) {
                                 return "#707070"
                             } /*else if (btnIput.hovered) {
                                 return "#515151"
                             }*/ else {
                                 return "#2c2c2c"
                             }
                         }
                     }
                     color: backgroundColor
                }
                onClicked: {
                    input.clear();
                }
            }
        }
    }
}

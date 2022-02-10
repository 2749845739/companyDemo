import QtQuick 2.12
import QtQml 2.3
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
SpinBox {
    id: cusSpinBox
    height: 30
    implicitWidth: 60
    editable: true
    leftPadding: 4
    rightPadding: 4
    focusPolicy:Qt.ClickFocus
    enabled: true
    property int fontsize: 16

    property alias tipText: toolTip.text
    property alias tipItem: toolTip
    property alias tipVisible: toolTip.visible
    property alias tipDelay: toolTip.delay
    property alias tipTimeout: toolTip.timeout

    //property int value:-999999
    property string imgUpUrlNormal : {
        if(upArea.hovered || upArea.pressed)
        {
            return  "qrc:/Image/image/Window/upSelect.png";
        }else{
            return "qrc:/Image/image/Window/upnormal.png";
        }
    }
    property string imgDownUrlNormal : {
        if(downArea.hovered || downArea.pressed)
        {
            return  "qrc:/Image/image/Window/downselect.png";
        }else{
            return "qrc:/Image/image/Window/downnomal.png";
        }
    }

    onFocusChanged: {
        if(parseInt(input.text)>cusSpinBox.to){
            input.text=cusSpinBox.to
        }
        if(parseInt(input.text)<cusSpinBox.from){
            input.text=cusSpinBox.from
        }
    }

    background: Rectangle {
        radius: 6
        color: "#F6F6F6"
        border.width: 1
        border.color: cusSpinBox.hovered || cusSpinBox.focus ? "#000000" : "#bfbfbf"
    }
    contentItem: TextInput {
        id: input
        height: 30
        font.pixelSize: fontsize
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        selectByMouse: true
        maximumLength: 64
        z: 2
        color: cusSpinBox.enabled?"#000000":"#bfbfbf"
        text:cusSpinBox.value
        //color: CusConfig.textColor
        width: cusSpinBox.width - cusSpinBox.up.indicator.width - cusSpinBox.leftPadding - cusSpinBox.rightPadding
        selectionColor: "#bfbfbf"
//        selectedTextColor:"#bfbfbf"
//        onTextChanged: {
//            cusSpinBox.value=text;
//            //cusSpinBox.valueModified();
//        }
         //这里绑定了属性，外面C++绑定没用了    以后慎用
//        Binding {
//            target: input
//            property: "text"
////            value: cusSpinBox.textFromValue ? cusSpinBox.textFromValue(cusSpinBox.value, Qt.locale()) : cusSpinBox.value
//            value: cusSpinBox.value
//        }
        //
//        Binding{
//            target: cusSpinBox
//            property: "value"
////            value: cusSpinBox.valueFromText ? cusSpinBox.valueFromText(input.text, Qt.locale()) : input.text
//            value: input.text
//        }
        readOnly: !cusSpinBox.editable
        validator: cusSpinBox.validator
        inputMethodHints: Qt.ImhFormattedNumbersOnly
    }
//    Image {
//        id: baseImage
//        source: imgUrlNormal
//        smooth: true
//        visible: false
//        width: 24
//        height: 24
//    }
    property color colorNormal: "#bfbfbf"
    property color colorHovered: "#000000"
    property color colorPressed: "#000000"
    property color colorDisable: "#bfbfbf"
    up.indicator: Item {
        x: cusSpinBox.width - width - cusSpinBox.rightPadding
        z: 3
        height: cusSpinBox.height/2
        implicitWidth: 24
        Image {
            anchors.centerIn: parent
            source: imgUpUrlNormal
            smooth: true
            //visible: false
            width: sourceSize.width
            height: sourceSize.height
        }
//        ColorOverlay {
//            anchors.centerIn: parent
//            width: baseImage.width
//            height: baseImage.height
//            cached: true
//            source: baseImage
//            color: (upArea.hovered || upArea.pressed) ? colorHovered : colorNormal
//            rotation: 180
//        }
        MouseArea {
            id: upArea
            anchors.fill: parent
            hoverEnabled: true
            enabled: cusSpinBox.enabled
            z: 5
            onClicked: {
                cusSpinBox.increase()
                cusSpinBox.valueModified();
            }
        }
    }
    down.indicator: Item {
        x: cusSpinBox.width - width - cusSpinBox.rightPadding
        y: cusSpinBox.height/2
        z: 3
        height: cusSpinBox.height/2
        implicitWidth: 24
        implicitHeight:24
//        ColorOverlay {
//            anchors.centerIn: parent
//            width: baseImage.width
//            height: baseImage.height
//            cached: true
//            source: baseImage
//            color: (downArea.hovered || downArea.pressed) ? colorHovered : colorNormal
//        }
        Image {
            anchors.centerIn: parent
            source: imgDownUrlNormal
            smooth: true
            width: sourceSize.width
            height: sourceSize.width
        }
        MouseArea {
            id: downArea
            anchors.fill: parent
            hoverEnabled: true
            enabled: cusSpinBox.enabled
            onClicked: {
                cusSpinBox.decrease()
                //MouseArea覆盖了up和down本身的东西，需要自己发valueModified信号
                cusSpinBox.valueModified();
            }
        }
    }
    BasicTooptip {
        id: toolTip
        visible: cusSpinBox.hovered && String(text).length
        delay: 500
        x:parent.width+10
        y:0
    }
}


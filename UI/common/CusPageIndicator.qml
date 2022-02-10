import QtQuick 2.15
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
Item {
    id: cusPageIndicator
    implicitHeight: 46
    width: childrenRect.width
    //every indicator width
    property int indicatorWidth: 66

    property int spacing: 10

    property int currentIndex: 0

    property int count: 0

    //middle display count
    property int middleDisplayCount: 5
    //middle start
    property int middleStartIndex: 1
    //middle step
    property int middleStep: 5

    Row {
        height: parent.height
        spacing: cusPageIndicator.spacing
        Label {
            height: parent.height
            text: count > 1 ? "共"+count+"页" : "共0项"
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            color: "#967A50"
        }
        //left button for last current
        Button {
            id: leftBtn
            background: Rectangle {
                color: "#e6e6e6"
                radius: 8
            }
            contentItem:Item{
                Image {
                    id:leftimg
                    //anchors.centerIn: parent
                    source: "qrc:/Image/image/user/leftpage.png"
                    width: sourceSize.width
                    height: sourceSize.height
                    visible: false
                }
                ColorOverlay{
                    anchors.centerIn: parent
                    source: leftimg
                    width: leftimg.width
                    height: leftimg.height
                    cached: true
                    color: currentIndex!==0?"#967A50":"#bfbfbf"
                }
            }
            width: indicatorWidth
            height: parent.height
            onClicked: {
                if (currentIndex - 1 >= 0) {
                    gotoIndex(currentIndex - 1)
                }
            }
//            backgroundColor: hovered ? CusConfig.controlColor_hovered : (pressed ? CusConfig.controlColor_pressed : CusConfig.controlColor)
//            colorNormal: CusConfig.textColor
//            colorHovered: CusConfig.textColor_hovered
//            colorPressed: CusConfig.textColor_hovered
//            colorDisable: CusConfig.textColor_disabled
            enabled: currentIndex > 0
        }
        //start button for first
        Button {
            id: startBtn
            width: indicatorWidth
            height: parent.height
            text: "1"
            //at last 1 item for begin
            visible: count > 0
            //selected: currentIndex === 0
            onClicked: {
                gotoIndex(0)
            }
            background: Rectangle{
                color: currentIndex===0?"#967A50":"#e6e6e6"
                radius: 8
            }
        }
        //last button for last 5, if need ellipsis
        Button {
            id: lastBtn
            background: Rectangle{
                Image {
                    id:imglast
                    source: /*(lastBtn.hovered||lastBtn.pressed) ?*/ "qrc:/Image/image/user/lastpage.png" /*: "qrc:/ellipsis.png"*/
                    width: sourceSize.width
                    height: sourceSize.height
                    visible: false
                }
                ColorOverlay{
                    anchors.centerIn: parent
                    source: imglast
                    width: imglast.width
                    height: imglast.height
                    cached: true
                    color: "#967A50"
                }
                radius: 8
                color: "transparent"
            }
            width: indicatorWidth
            height: parent.height
            visible: startBtn.visible && middleStartIndex > 1
            onClicked: {
                gotoLast()
            }
        }
        // middle
        Repeater {
            id: generater
            enabled: cusPageIndicator.count - 2 > 0
            model: Math.min(middleDisplayCount, cusPageIndicator.count - 2)
            delegate: Button {
                implicitWidth: indicatorWidth
                implicitHeight: cusPageIndicator.height
                text: middleStartIndex + index + 1
                background: Rectangle{
                    color: currentIndex === middleStartIndex + index?"#967A50":"#e6e6e6"
                    radius: 8
                }
                onClicked: {
                    gotoIndex(middleStartIndex + index)
                }
            }
        }
        //next button for next 5, if need ellipsis
        Button {
            id: nextBtn
            background: Rectangle{
                Image {
                    id:imgnext
                    source: /*(lastBtn.hovered||lastBtn.pressed) ?*/ "qrc:/Image/image/user/nextpage.png" /*: "qrc:/ellipsis.png"*/
                    width: sourceSize.width
                    height: sourceSize.height
                    //anchors.centerIn: parent
                    visible: false
                }
                ColorOverlay{
                    anchors.centerIn: parent
                    source: imgnext
                    width: imgnext.width
                    height: imgnext.height
                    cached: true
                    color: "#967A50"
                }
                radius: 8
                color: "transparent"
            }
            width: indicatorWidth
            height: parent.height
            visible: count > 2
                     && ((count - 1) - (middleStartIndex + generater.count) >= 1)
//            tipText: qsTr(
//                         middleStep > 1 ? "next %1 items" : "next %1 item").arg(
//                         middleStep) + CusConfig.transString
            onClicked: {
                gotoNext()
            }
        }
        //end button for end one
        Button {
            id: endBtn
            width: indicatorWidth
            height: parent.height
            text: count
            //at last 2 item, one for begin, one for end
            visible: count > 1
            background: Rectangle{
                color: currentIndex===count-1?"#967A50":"#e6e6e6"
                radius: 8
            }
            onClicked: {
                gotoIndex(count - 1)
            }
        }
        //next one for next current
        Button {
            id: rightBtn
            background: Rectangle {
                color:"#e6e6e6"
                radius: 8
            }
            contentItem: Item{
                Image {
                    //anchors.centerIn: parent
                    id:rightimg
                    source: "qrc:/Image/image/user/rightpage.png"
                    width: sourceSize.width
                    height: sourceSize.height
                    visible: false
                }
                ColorOverlay{
                    anchors.centerIn: parent
                    source: rightimg
                    width: rightimg.width
                    height: rightimg.height
                    cached: true
                    color: currentIndex+1!==count?"#967A50":"#bfbfbf"
                }
            }
            width: indicatorWidth
            height: parent.height
            onClicked: {
                if (currentIndex + 1 < count) {
                    gotoIndex(currentIndex + 1)
                }
            }
//            backgroundColor: hovered ? CusConfig.controlColor_hovered : (pressed ? CusConfig.controlColor_pressed : CusConfig.controlColor)
//            colorNormal: CusConfig.textColor
//            colorHovered: CusConfig.textColor_hovered
//            colorPressed: CusConfig.textColor_hovered
//            colorDisable: CusConfig.textColor_disabled
            enabled: currentIndex < count - 1
        }
    }
    function gotoLast() {
        var t = currentIndex - middleStep
        if (t < 0) {
            t = 0
        }
        gotoIndex(t)
    }
    function gotoNext() {
        var t = middleStartIndex + middleStep
        if (t > count - 1) {
            t = count - 1
        }
        gotoIndex(t)
    }
    function gotoIndex(targetIndex) {
        if (targetIndex < 0 || targetIndex >= count) {
            return
        }
        if (targetIndex === currentIndex) {
            return
        }
        currentIndex = targetIndex
    }
    onCurrentIndexChanged: {
        updateMiddle()
    }
    Component.onCompleted: {
        updateMiddle()
    }
    function updateMiddle() {
        if (count - 2 <= middleDisplayCount) {
            middleStartIndex = 1
        } else {
            var minV = 1
            var maxV = count - middleDisplayCount - 1
            var half = parseInt(generater.count / 2)
            var midV = currentIndex - half
            middleStartIndex = bound(minV, midV, maxV)
        }
    }
    function bound(minValue, midValue, maxValue) {
        return Math.max(minValue, Math.min(midValue, maxValue))
    }
}

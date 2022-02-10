import QtQuick 2.12
import QtQuick.Controls 2.5

Flickable {
    property string imgSouce:""
    id: flick
    clip: true
    contentWidth: photoFrame.width
    contentHeight:photoFrame.height
    Rectangle{
        id:photoFrame
        //注意这里
        width: parent.width
        height: parent.height
        color: "black"
        Behavior on scale { NumberAnimation { duration: 200 } }
        Behavior on x { NumberAnimation { duration: 200 } }
        Behavior on y { NumberAnimation { duration: 200 } }
        Image {
            id:image
            asynchronous: true
            anchors.fill: parent
            source: imgSouce
            antialiasing: true
            cache: false
            mipmap: true
            //fillMode: Image.PreserveAspectFit
        }
        PinchArea
        {
            anchors.fill: parent
            pinch.target: photoFrame
            pinch.minimumRotation: -360
            pinch.maximumRotation: 360
            pinch.minimumScale: 1
            pinch.maximumScale: 10
            pinch.minimumX:0
            pinch.minimumY:0
            pinch.dragAxis: Pinch.XAndYAxis
            onSmartZoom: {
                if (pinch.scale > 0) {
                    photoFrame.rotation = 0;
                    photoFrame.scale = Math.min(flick.width, flick.height) / Math.max(image.sourceSize.width, image.sourceSize.height) * 0.85
                    photoFrame.x = flick.contentX + (flick.width - photoFrame.width) / 2
                    photoFrame.y = flick.contentY + (flick.height - photoFrame.height) / 2
                } else {
                    photoFrame.rotation = pinch.previousAngle
                    photoFrame.scale = pinch.previousScale
                    photoFrame.x = pinch.previousCenter.x - photoFrame.width / 2
                    photoFrame.y = pinch.previousCenter.y - photoFrame.height / 2
                }
            }
            MouseArea {
                id: dragArea
                hoverEnabled: true
                anchors.fill: parent
                drag.target: photoFrame
                scrollGestureEnabled: false  // 2-finger-flick gesture should pass through to the Flickable
                propagateComposedEvents:true
                onWheel: {
                    if (wheel.modifiers & Qt.ControlModifier) {
                        photoFrame.rotation += wheel.angleDelta.y / 120 * 5;
                        if (Math.abs(photoFrame.rotation) < 4)
                            photoFrame.rotation = 0;
                    } else {
                        photoFrame.rotation += wheel.angleDelta.x / 120;
                        if (Math.abs(photoFrame.rotation) < 0.6)
                            photoFrame.rotation = 0;
                        var scaleBefore = photoFrame.scale;
                        photoFrame.scale += photoFrame.scale * wheel.angleDelta.y / 120 / 10;
                    }
                }
            }
        }
    }
}


import QtQuick 2.12
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.5
ComboBox {
     id: control
     leftPadding: 4
     rightPadding: 4
     //textRole: "text"
     property int hoveredIndex: -1
     delegate: ItemDelegate {
         width: control.width
         height: 30
         contentItem: Text {
             text: modelData
//             color: "#8a8a9b"
             font: control.font
             elide: Text.ElideRight
             verticalAlignment: Text.AlignVCenter
//             color: control.hoveredIndex
//                    === index ? "#000000" : "#000000"
         }
         background: Item {
//             width: control.width
//             height: control.height-4
             Rectangle {
                 anchors {
                     fill: parent
//                     leftMargin: 2
//                     rightMargin: 2
                 }
                 //radius: 4
                 color: (control.currentIndex === index ? "#967A50" :"#cbcbcb")
             }
         }
         highlighted: control.highlightedIndex === index
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
             enabled: control.enabled
             onContainsMouseChanged: {
                 if (containsMouse) {
                     control.hoveredIndex = index
                 } else {
                     control.hoveredIndex = -1
                 }
             }
         }
     }
     Image {
         id: baseImage
         source: "qrc:/Image/image/normal/ComboBox_Down.png"
         smooth: true
         width: sourceSize.width
         height: sourceSize.height
         visible: false
     }
     indicator: Item {
         id: canvas
         x: control.width - width - control.rightPadding
         y: control.topPadding + (control.availableHeight - height) / 2
         height: control.height - control.topPadding - control.bottomPadding
         width: height
         ColorOverlay {
             anchors {
                 centerIn: parent
             }
             source: baseImage
             width: baseImage.width
             height: baseImage.height
             cached: true
             color: {
                 if (!control.enabled) {
                     return "#767676"
                 } else if (control.pressed) {
                     return "#8a8a9b"
                 } else if (control.hovered) {
                     return "#8a8a9b"
                 } else {
                     return "#8a8a9b"
                 }
             }
             rotation:control.popup.visible ? 180 : 0
             Behavior on rotation {
                 NumberAnimation {
                     duration: 150
                 }
             }
         }

     }
     contentItem: Text {
         leftPadding: 5
         rightPadding: control.indicator.width + control.spacing
         text: control.currentText
         font: control.font
         //color: control.pressed ? "#17a81a" : "#21be2b"
         color: "#000000"
         verticalAlignment: Text.AlignVCenter
         elide: Text.ElideRight
     }

     background: Rectangle {
//         implicitWidth: 120
//         implicitHeight: 40
         color: "white"
         border.color: control.pressed ? "#FFFFFF" : "#bfbfbf"
         border.width: control.visualFocus ? 2 : 1
         radius: 5
     }

     popup: Popup {
         y: control.height - 1
         width: control.width
         implicitHeight: contentItem.implicitHeight
         padding: 1

         contentItem: ListView {
             clip: true
             implicitHeight: contentHeight
             model: control.popup.visible ? control.delegateModel : null
             currentIndex: control.highlightedIndex

             ScrollIndicator.vertical: ScrollIndicator { }
         }

         background: Rectangle {
             border.color: "#8a8a9b"
             radius: 2
         }
     }
 }

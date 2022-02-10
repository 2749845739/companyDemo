import QtQuick 2.15
import QtQuick.Controls 1.4 as Controls14
import QtQuick.Controls.Styles 1.4 as Style14
import QtQuick.Controls 2.5 as Controls2
Controls14.Calendar {
    id:ca
//    anchors.left: parent.left
//    anchors.top: parent.top
//    anchors.topMargin: 30
//    width: parent.width/2-5
    frameVisible: false
    selectedDate: new Date()
    style: Style14.CalendarStyle {
        gridVisible:false
        navigationBar:Item {
            width: parent.width
            height: 40
            Rectangle{
                anchors.top: parent.top
                anchors.left: parent.left
                width: parent.width
                height: 1
                color: "#bfbfbf"
            }
            Controls2.Button{
                anchors.left: parent.left
                anchors.top: parent.top
                width: 30
                height: parent.height
                text: "front"
                onClicked: {
                    ca.showPreviousMonth()
                }
                background: Item {
                    width: 30
                    height: parent.height
                    Image{
                        anchors.centerIn: parent
                        width: sourceSize.width
                        height: sourceSize.height
                        source: "qrc:/Image/image/user/next.png"
                        rotation: 180
                    }
                }
            }
            CusText {
                anchors.horizontalCenter: parent.horizontalCenter
                textContent: {
                    var str=styleData.title;
                    var arry = str.split(" ");
                    return arry[1]+"年"+" "+arry[0];
                }
                fontSize: 14
                fontblod: true
            }
            Controls2.Button{
                anchors.right : parent.right
                anchors.top: parent.top
                width: 30
                height: parent.height
                text: "front"
                onClicked: {
                    ca.showNextMonth()
                }
                background: Item {
                    width: 30
                    height: parent.height
                    Image{
                        anchors.centerIn: parent
                        width: sourceSize.width
                        height: sourceSize.height
                        source: "qrc:/Image/image/user/next.png"
                    }
                }
            }
            Rectangle{
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                width: parent.width
                height: 1
                color: "#bfbfbf"
            }
        }
        dayOfWeekDelegate:Item{
            height: 40
            Text {
                anchors.centerIn: parent
                text: {
                    switch(styleData.index){
                    case 0 : return "日";
                    case 1 : return "一";
                    case 2 : return "二";
                    case 3 : return "三";
                    case 4 : return "四";
                    case 5 : return "五";
                    case 6 : return "六";
                    default: break;
                    }
                }
                font.bold: true
                font.pixelSize: 14
//                fontSize: 14
//                fontblod: true
            }
        }
        dayDelegate: Item {
            implicitWidth: 24
            implicitHeight: 24
//            width: 24
//            height: 24
            Rectangle{
                anchors.fill: parent
                color: {
                    return styleData.selected ? "#967A50":"#ffffff"
                }
            }
            Controls2.Label{
                text: styleData.date.getDate()
                anchors.centerIn: parent
                color:{
                    var color = "#dddddd";
                    if(styleData.valid){
                        color = styleData.visibleMonth ? "#000000" : "#bbb";
                        if(styleData.selected){
                            color="#ffffff"
                        }
                    }
                    return color;
                }
                font.pixelSize: 14
            }
        }
    }
//    onClicked: {
//        console.log(Qt.formatDate(date,"yyyy/MM/dd"));
//    }
}

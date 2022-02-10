import QtQuick 2.12
import QtQuick.Controls 2.12
import "../common"
Item {
    Row{
        x:(parent.width-width)/2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 123
        spacing: 268
        height: camera.height+25
        Item{
            height: img.height+content.height+25
            width:158
            Column{
                id: camera
                spacing: 25
                anchors.fill: parent
                CusButton_Image {
                    id:img
                    height: 83
                    btnImgNormal: "qrc:/Image/image/maintain/camera.png"
                    btnImgHovered:"qrc:/Image/image/maintain/camera.png"
                    btnImgPressed:"qrc:/Image/image/maintain/camera.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                CusText{
                    id:content
                    width: 158
                    height: 34
                    fontSize: 24
                    fontblod: true
                    textContent: "相机参数调整"
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    swipeview.currentIndex=2;
                }
            }
        }

        Item{
            height: img.height+content.height+25
            width:158
            Column{
                id: motor
                spacing: 25
                CusButton_Image {
                    id:motorimg
                    height: 83
                    btnImgNormal: "qrc:/Image/image/maintain/motor.png"
                    btnImgHovered: "qrc:/Image/image/maintain/motor.png"
                    btnImgPressed: "qrc:/Image/image/maintain/motor.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                CusText{
                    width: 158
                    height: 34
                    fontSize: 24
                    fontblod: true
                    textContent: "电机参数设置"
                }
            }
        }
        Item{
            height: img.height+content.height+25
            width:158
            Column{
                id: indicators
                spacing: 25
                width: 158
                CusButton_Image {
                    height: 83
                    btnImgNormal: "qrc:/Image/image/maintain/indicators.png"
                    btnImgHovered: "qrc:/Image/image/maintain/indicators.png"
                    btnImgPressed: "qrc:/Image/image/maintain/indicators.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                CusText{
                    width: 158
                    height: 34
                    fontSize: 24
                    fontblod: true
                    textContent: "指标参数调整"
                }
            }
        }
        Item{
            height: img.height+content.height+25
            width:158
            Column{
                id: useraccount
                spacing: 25
                width: 158
                CusButton_Image {
                    height: 83
                    btnImgNormal: "qrc:/Image/image/maintain/usersetting.png"
                    btnImgHovered: "qrc:/Image/image/maintain/usersetting.png"
                    btnImgPressed: "qrc:/Image/image/maintain/usersetting.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                CusText{
                    width: 158
                    height: 34
                    fontSize: 24
                    fontblod: true
                    textContent: "账户设置查询"
                }
            }
        }
    }
}

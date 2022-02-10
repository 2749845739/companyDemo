import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../common"
Rectangle{
    Column{
        anchors.fill: parent
        Rectangle{
            id:showInfo
            height: (parent.height*0.5)-1
            width: parent.width
            color: "#5c646e"
            ColumnLayout{
                anchors.fill: parent
                CircleWave{
                    Layout.fillWidth: true
                    Layout.minimumWidth: 120
                    Layout.preferredWidth: 120
                    Layout.maximumWidth: 120
                    Layout.minimumHeight: 120

                    Layout.topMargin:120
                    id:cpuInfo
                    Layout.alignment: Qt.AlignHCenter|Qt.AlignVCenter
                    typeName: "CPU"
                    rangeValue: sRate.listRate[0]
                }
                CircleWave{
                    id:memeryInfo
                    Layout.fillWidth: true
                    Layout.minimumWidth: 120
                    Layout.preferredWidth: 120
                    Layout.maximumWidth: 120
                    Layout.minimumHeight: 120
                    Layout.alignment: Qt.AlignHCenter|Qt.AlignVCenter
                    typeName: "MEM"
                    rangeValue: sRate.listRate[1]
                }
            }
        }
//        CusShadow{
//            height: 40
//            horizontal:true
//            width: parent.width
//            borderpix: 10
//            shadowpix: 4
//        }
        SwipeView{
            id:swview
            clip: true  //防止显示多个界面
            orientation: Qt.Horizontal
            interactive: true
            height: (parent.height*0.5)-1  //在行列布局中貌似不能在使用锚了
            width: parent.width
            currentIndex: indicator.currentIndex
            Page{
                id:cameraInfo
                title: "cameraInfo"
                header: Rectangle {
                    height: 20
                    Text {
                        id: camera
                        anchors.fill: parent
                        text: "相机状态"
                        horizontalAlignment:Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    color: "#8bcaec"
                }
                background: Rectangle{
                    color: "#5c646e"
                }
                contentItem: Item{
                    ColumnLayout {
                        spacing: 5
                        anchors.fill: parent
                        CusButton_Image{
                            Layout.fillWidth: true
                            //在子元素里使用ColumnLayout的属性
                            Layout.alignment: Qt.AlignHCenter|Qt.AlignVCenter
                            btnImgUrl: "qrc:/Image/image/deviceStatus/networkNormal.png"
                            tipText: "网络正常"
                        }
                        CusButton_Image{
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignHCenter|Qt.AlignVCenter
                            btnImgUrl: "qrc:/Image/image/deviceStatus/powerOn.png"
                            tipText: "电源正常"
                        }
                        CusButton_Image{
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignHCenter|Qt.AlignVCenter
                            btnImgUrl: "qrc:/Image/image/deviceStatus/AC220Normal.png"
                            tipText: "线路正常"
                        }
                    }
                }
            }
            Page{
                id:motorInfo
                title: "motorInfo"
                header: Rectangle {
                    height: 20
                    Text {
                        id: motor
                        anchors.fill: parent
                        text: "电机状态"
                        horizontalAlignment:Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    color: "#8bcaec"
                }
                background: Rectangle{
                    color: "#5c646e"
                }
                contentItem: Item{
                    ColumnLayout {
                        spacing: 5
                        anchors.fill: parent
                        CusButton_Image{
                            Layout.fillWidth: true
                            //在子元素里使用ColumnLayout的属性
                            Layout.alignment: Qt.AlignHCenter|Qt.AlignVCenter
                            btnImgUrl: "qrc:/Image/image/deviceStatus/humidityAbnormal.png"
                            tipText: "温度过高"
                        }
                        CusButton_Image{
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignHCenter|Qt.AlignVCenter
                            btnImgUrl: "qrc:/Image/image/deviceStatus/IOAbnormal.png"
                            tipText: "继电器故障"
                        }
                        CusButton_Image{
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignHCenter|Qt.AlignVCenter
                            btnImgUrl: "qrc:/Image/image/deviceStatus/arming.png"
                            tipText: "线路正常"
                        }
                    }
                }
            }
            Page{
                id:lightSource
                title: "lightSource"
                header: Rectangle {
                    height: 20
                    Text {
                        id: light
                        anchors.fill: parent
                        text: "光源状态"
                        horizontalAlignment:Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    color: "#8bcaec"
                }
                background: Rectangle{
                    color: "#5c646e"
                }
                contentItem: Item{
                    ColumnLayout {
                        spacing: 5
                        anchors.fill: parent
                        CusButton_Image{
                            //在子元素里使用ColumnLayout的属性
                            Layout.alignment: Qt.AlignHCenter|Qt.AlignVCenter
                            Layout.fillWidth: true
                            btnImgUrl: "qrc:/Image/image/deviceStatus/AC24Normal.png"
                            tipText: "网络正常"
                        }
                        CusButton_Image{
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignHCenter|Qt.AlignVCenter
                            btnImgUrl: "qrc:/Image/image/deviceStatus/AC220Normal.png"
                            tipText: "电源正常"
                        }
                        CusButton_Image{
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignHCenter|Qt.AlignVCenter
                            btnImgUrl: "qrc:/Image/image/deviceStatus/RelayNormal.png"
                            tipText: "线路正常"
                        }
                    }
                }
            }
        }
    }
    //
    PageIndicator{
        id: indicator
        interactive: true
        count: swview.count
        currentIndex: swview.currentIndex
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

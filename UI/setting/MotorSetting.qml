import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml 2.12
import "../common"
import ".."
ScrollView{
    clip: true
    id:motorSetting
    property int indexId: 0
    anchors.fill: parent
    opacity:0
    Grid{
        anchors.left: parent.left
        anchors.top:parent.top
        width: parent.width
        spacing: 10
        columns:2
        Column{
            Row{
                spacing: 10
                Text {
                    id:slMotor
                    text:"送料电机:"
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
            Flow{
                width: motorSetting.width/2
                spacing: 20
//                Row {
//                    spacing: 10
//                    Text {
//                        height: slMotor.height
//                        text:"电机行程:"
//                        font.pixelSize: 15
//                        verticalAlignment: Text.AlignVCenter
//                        horizontalAlignment: Text.AlignHCenter
//                    }
//                    CusSpinBox{
//                        from: 0
//                        to:100
//                        value:0
//                        onValueModified: {
//                        }
//                    }
//                }
//                Row {
//                    spacing: 10
//                    Text {
//                        height: slMotor.height
//                        text:"电机步程:"
//                        font.pixelSize: 15
//                        verticalAlignment: Text.AlignVCenter
//                        horizontalAlignment: Text.AlignHCenter
//                    }
//                    CusSpinBox{
//                        from: 0
//                        to:100
//                        value:0
//                        onValueModified: {
//                        }
//                    }
//                }
                Row{
                    spacing: 10
                    Text {
                        height: slMotor.height
                        text:"电机方向:"
                        font.pixelSize: 15
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
//                    CusSpinBox{
//                        from: 0
//                        to:100
//                        value:0
//                        onValueModified: {
//                        }
//                    }
                    CusCheckBox{
                        text: "正向"
                        checked:boardControl.slDirection===1?true:false
                        onClicked: {
                            boardControl.setSMotorInfo(1,0,1);
                        }
                    }
                    CusCheckBox{
                        text: "反向"
                        checked:boardControl.slDirection===2?true:false
                        onClicked: {
                            boardControl.setSMotorInfo(1,0,2);
                        }
                    }
                }
                Row{
                    spacing: 10
                    Text {
                        text:"前进速度:"
                        height: slMotor.height
                        font.pixelSize: 15
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                    CusSpinBox{
                        from: 9
                        to:900
                        value:boardControl.slPositive_speed
                        onValueModified: {
                              boardControl.setSMotorInfo(1,1,value);
                        }
                    }
                }
                Row{
                    spacing: 10
                    Text {
                        text:"后退速度:"
                        height: slMotor.height
                        font.pixelSize: 15
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                    CusSpinBox{
                        from: 9
                        to:900
                        value:boardControl.slNegative_speed
                        onValueModified: {
                            boardControl.setSMotorInfo(1,2,value);
                        }
                    }
                }
                Row{
                    spacing: 10
                    Text {
                        text:"预震时电机位置:"
                        height: slMotor.height
                        font.pixelSize: 15
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                    CusSpinBox{
                        from: 0
                        to:65535
                        value:boardControl.slPosition_0
                        onValueModified: {
                            boardControl.setSMotorInfo(1,3,value);
                        }
                    }
                }
                Row{
                    spacing: 10
                    Text {
                        text:"开始震动时电机位置:"
                        height: slMotor.height
                        font.pixelSize: 15
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                    CusSpinBox{
                        from: 0
                        to:65535
                        value:boardControl.slPosition_1
                        onValueModified: {
                            boardControl.setSMotorInfo(1,4,value);
                        }
                    }
                }
                Row{
                    spacing: 10
                    Text {
                        text:"停止震动时电机位置:"
                        height: slMotor.height
                        font.pixelSize: 15
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                    CusSpinBox{
                        from: 0
                        to:65535
                        value:boardControl.slPosition_2
                        onValueModified: {
                            boardControl.setSMotorInfo(1,5,value);
                        }
                    }
                }
            }
        }
        Column{
            Row{
                spacing: 10
                Text {
                    id:cmMotor
                    text:"仓门电机:"
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
            Flow{
                width: motorSetting.width/2
                spacing: 20
                Row{
                    spacing: 10
                    Text {
                        height: cmMotor.height
                        text:"电机方向:"
                        font.pixelSize: 15
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                    CusCheckBox{
                        text: "正向"
                        checked: boardControl.cmDirection===1?true:false
                         onClicked: {
                             boardControl.setSMotorInfo(0,0,1);
                         }
                    }
                    CusCheckBox{
                        text: "反向"
                        checked: boardControl.cmDirection===2?true:false
                        onClicked: {
                            boardControl.setSMotorInfo(0,0,2);
                        }
                    }
                }
                Row{
                    spacing: 10
                    Text {
                        text:"前进速度:"
                        height: cmMotor.height
                        font.pixelSize: 15
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                    CusSpinBox{
                        from: 0
                        to:65535
                        value:boardControl.cmPositive_speed
                        onValueModified: {
                            boardControl.setSMotorInfo(0,1,value);
                        }
                    }
                }
                Row{
                    spacing: 10
                    Text {
                        text:"后退速度:"
                        height: cmMotor.height
                        font.pixelSize: 15
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                    CusSpinBox{
                        from: 0
                        to:65535
                        value:boardControl.cmNegative_speed
                        onValueModified: {
                            boardControl.setSMotorInfo(0,2,value);
                        }
                    }
                }
                Row{
                    spacing: 10
                    Text {
                        text:"仓门打开高度:"
                        height: cmMotor.height
                        font.pixelSize: 15
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                    CusSpinBox{
                        from: 0
                        to:65535
                        value:boardControl.cmPosition_0
                        onValueModified: {
                            boardControl.setSMotorInfo(0,3,value);
                        }
                    }
                }
            }
        }
        Column{
            spacing: 20
            Row{
                spacing: 10
                Text {
                    id:zdMotor
                    text:"震动器:"
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
            Row{
                spacing: 10
                width: motorSetting.width/2
                Text {
                    height: zdMotor.height
                    text:"开始进料时震动:"
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                CusSpinBox{
                    from: 0
                    to:65535
                    value:boardControl.input_vibrate
                    onValueModified: {
                        boardControl.setVibratorInfo(0,0,value);
                    }
                }
            }
            Row{
                spacing: 10
                //width: motorSetting.width/2
                Text {
                    height: cmMotor.height
                    text:"最后清料时震动:"
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                CusSpinBox{
                    from: 0
                    to:65535
                    value:boardControl.clear_vibrate
                    onValueModified: {
                        boardControl.setVibratorInfo(0,1,value);
                    }
                }
            }
        }
        Column{
            spacing: 20
            Row{
                spacing: 10
                Text {
                    id:zlMotor
                    text:"直流电机:"
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
            Row{
                spacing: 10
                width: motorSetting.width/2
                CusCheckBox{
                    text: "震动器入料时保持打开"
                    checked: boardControl.open_on_vibrate
                    onClicked: {
                        boardControl.setDCmotorInfo(0,true);
                    }
                }
            }
            Row{
                CusCheckBox{
                    text: "震动器入料时保持关闭"
                    checked: !boardControl.open_on_vibrate
                    onClicked: {
                        boardControl.setDCmotorInfo(0,false);
                    }
                }
            }
        }
        Column{
            spacing: 20
            Row{
                spacing: 10
                Text {
                    text:"相机拍照"
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
            Row{
                spacing: 10
                Text {
                    id:internal_period
                    text:"相机，给其触发信号的间隔时间:"
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                CusSpinBox{
                    from: 0
                    to:65535
                    value:boardControl.internal_period
                    onValueModified: {
                        boardControl.set_trigger_info(0,value);
                    }
                }
            }
            Row{
                spacing: 10
                Text {
                    id:external_period
                    text:"两台不同相机，给其触发信号的间隔时间:"
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                CusSpinBox{
                    from: 0
                    to:65535
                    value:boardControl.external_period
                    onValueModified: {
                          boardControl.set_trigger_info(1,value);
                    }
                }
            }
            Row{
                spacing: 10
                Text {
                    id:trigger_period
                    text:"每次触发之间的间隔时间(针对图像校准):"
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                CusSpinBox{
                    from: 0
                    to:65535
                    value:boardControl.trigger_period
                    onValueModified: {
                       boardControl.set_trigger_info(2,value);
                    }
                }
            }
            Row{
                spacing: 10
                Text {
                    id:max_trigger
                    text:"最大触发次数:"
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                CusSpinBox{
                    enabled: false
                    from: 0
                    to:65535
                    value:boardControl.max_trigger
                    onValueModified: {
                         boardControl.set_trigger_info(3,value);
                    }
                }
            }
        }
    }

    background: Rectangle{
        color: "#d2cfd0"
    }
    Behavior on opacity {
        NumberAnimation{
            to:1
            duration: 200
        }
    }
    Component.onCompleted: {
        opacity=1;
    }
}


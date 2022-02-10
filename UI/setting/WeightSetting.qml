import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml 2.12
import "../common"
import ".."
ScrollView{
    clip: true
    anchors.fill: parent
    opacity: 0
    property int indexId: 0
    Column{
        Row{
            spacing: 10
            Text {
                id:weight
                text:"称重仪:"
                font.pixelSize: 20
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
        Row{
            spacing: 20
            CusButtom{
                height: weight.height
                width: 80
                text: "校准"
                backgroundColorNormal: "#cececf"
                backgroundColorHovered: "#eaf6fd"
                backgroundColorPressed: "#d7ebfa"
                backgroundColorDisable: "#b6bdc5"
                borderColor: enabled ? "#38a9e4" : "#b6bdc5"
                borderWidth: 1
                textColor: enabled ? "#38a9e4" : "#ffffff"
                onClicked: {
                }
            }
            Text {
                text:"称重延时设置:"
                font.pixelSize: 15
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            CusSpinBox{
              from:0
              to:100
              value:0
              onValueModified: {
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

import QtQuick 2.12
import QtQuick.Controls 2.5
import QtCharts 2.15
Item {
    ChartView{
        id:chart
        anchors.fill: parent
        animationDuration:2000
        animationOptions:ChartView.AllAnimations
        antialiasing: true
        legend.visible: false
        //dropShadowEnabled:true
        backgroundColor: "#F6F6F6"
        PieSeries {
            useOpenGL: true
            PieSlice {
                label: "生芽"
                value:parseFloat(algorithmResult.shengya[0])
                labelVisible:false
                color:"#73FEFE"
            }
            PieSlice {
                label: "虫蚀"
                value:parseFloat(algorithmResult.chongshi[0])
                labelVisible: false
                color:"#FFBF00"
            }
            PieSlice {
                label: "破损"
                value:parseFloat(algorithmResult.posun[0])
                labelVisible: false
                color:"#D7D2CC"
            }
            PieSlice {
                label: "生霉"
                value:parseFloat(algorithmResult.shengmei[0])
                labelVisible: false
                color: "#FF0000"
            }
            PieSlice {
                label: "病斑"
                value:parseFloat(algorithmResult.chimei[0])
                      +parseFloat(algorithmResult.heipei[0])
                labelVisible:false
                color: "#800080"
            }
//            PieSlice {
//                label: "黑胚"
//                value:
//                labelVisible: false
//            }
            PieSlice {
                exploded:true
                explodeDistanceFactor: 0.1
                label: "正常"+String(algorithmResult.weightNormal[1])+"%"
                value:algorithmResult.weightNormal[0]
                labelVisible:true
                color: "#00FF00"
            }
        }
    }
}

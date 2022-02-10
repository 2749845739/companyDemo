import QtQuick 2.12
import QtQuick.Controls 2.5
Item {
    enum HALIGNMENT {
        AlignLeft,
        AlignRight,
        AlignHCenter,
        AlignJustify
    }
    enum VALIGNMENT {
        AlignTop,
        AlignBottom,
        AlignVCenter
    }
    implicitHeight: 32
    implicitWidth: 100
    property alias telide: content.elide
    property alias wrap: content.wrapMode
    property bool fontblod: false
    property bool fontitalic: false
    property string textContent:""
    property int hAlignmentType: CusText.HALIGNMENT.AlignLeft
    property int vAlignmentType: CusText.VALIGNMENT.AlignVCenter
    property int fontSize : 15
    property color textColor: "#000000"
    Text {
        id: content
        wrapMode:Text.NoWrap
        anchors.fill: parent
        font.pixelSize: fontSize
        font.bold:fontblod
        font.italic: fontitalic
        text: textContent
        color: textColor
        elide:Text.ElideNone
        horizontalAlignment:{
            if(hAlignmentType===CusText.HALIGNMENT.AlignLeft){
                return  Text.AlignLeft
            }else if(hAlignmentType===CusText.HALIGNMENT.AlignRight){
                return  Text.AlignRight
            }else if(hAlignmentType===CusText.HALIGNMENT.AlignHCenter){
                return  Text.AlignHCenter
            }else if(hAlignmentType===CusText.HALIGNMENT.AlignJustify)
            {
                return Text.AlignJustify
            }
        }
        verticalAlignment: {
            if(vAlignmentType===CusText.VALIGNMENT.AlignTop){
                return  Text.AlignTop
            }else if(vAlignmentType===CusText.VALIGNMENT.AlignBottom){
                return  Text.AlignBottom
            }else if(vAlignmentType===CusText.VALIGNMENT.AlignVCenter){
                return  Text.AlignVCenter
            }
        }
    }
}

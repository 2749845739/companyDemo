import QtQuick 2.12
import QtQuick.Controls 2.5
Button{
  id:cusButtonImage
  implicitHeight: 24
  implicitWidth: 24

  property alias tipText: toolTip.text
  property string btnImgNormal
  property string btnImgHovered
  property string btnImgPressed
  property string btnImgDisbaled
  property bool  selected: false

  property string btnImgUrl:{
      if(!cusButtonImage.enabled){
          return btnImgDisbaled
      }else if(cusButtonImage.pressed||selected){
          return btnImgPressed
      }else if(cusButtonImage.hovered){
          return btnImgHovered
      }else{
          return btnImgNormal
      }
  }

  background: Item {
      width: cusButtonImage.width
      height: cusButtonImage.height
      Image {
          id: backImg
          width: sourceSize.width
          height: sourceSize.height
          source:btnImgUrl
          anchors.centerIn: parent
      }
  }
  BasicTooptip{
      id:toolTip
      visible: cusButtonImage.hovered && String(text).length
      delay: 500
  }

}

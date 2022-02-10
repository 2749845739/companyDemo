import QtQuick 2.12
import QtQuick.Controls 2.5
import chpan 1.0
import ".."
ToolTip {
  id:basicTooltip
  contentItem: Text {
      id: text
      text: basicTooltip.text
      verticalAlignment: Text.AlignVCenter
      horizontalAlignment: Text.AlignHCenter
      font.family: CusConfig.fontFamily
      font.pixelSize: CusConfig.fontPixel
      elide: Text.ElideRight
      color: CusConfig.textColor
  }
}

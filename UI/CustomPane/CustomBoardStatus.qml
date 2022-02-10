import QtQuick 2.12
import QtQuick.Controls 2.5
import "../common"
Item {
    height: 30
    Row{
        height: 30
        Row{
            spacing: 10
            Image {
                source: "qrc:/Image/image/user/deviceNormal.png"
                width: sourceSize.width
                height: sourceSize.height
            }
            CusText{
                textColor: "#43913F"
                fontSize: 20
                textContent: "设备正常运行"
                width: 123
            }
        }
    }
}

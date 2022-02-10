import QtQuick 2.12
import QtGraphicalEffects 1.12
import QtQuick.Controls 2.5
Item {
    implicitWidth: 100
    implicitHeight: 100
    property color  startColor: "#00C8D2"
    property color  endColor: "#3C8CFF"
    property int radus: 0
    Rectangle{
        id:boderFill
        anchors.fill: parent
        visible: false
        color: "#00c8d2"  //!!!!!
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop { position: 0.0; color: "#00C8D2" }
            GradientStop { position: 1.0; color: "#3C8CFF" }
        }
    }
    Rectangle{
        id:mask
        anchors.fill: parent
        visible: false
        color: "transparent"
        border.width: 1
        radius: radus
    }
    OpacityMask{
        id: opM
        anchors.fill: parent
        source: boderFill
        maskSource: mask
    }
}

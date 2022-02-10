import QtQuick 2.12
import QtGraphicalEffects 1.12
Rectangle {
    implicitHeight: 300
    implicitWidth: 300
    property color inner: "white"
    Rectangle {
        anchors.fill: parent
        color: "#F6F6F6"
    }
    Rectangle {
        id: butterfly
        width: parent.width-20
        height: parent.height-20
        anchors.centerIn: parent
        color: inner
    }
    DropShadow {
        anchors.fill: butterfly
        horizontalOffset: 3
        verticalOffset: 3
        radius: 8.0
        samples: 17
        color: "#60000000"
        source: butterfly
    }
    DropShadow {
        anchors.fill: butterfly
        horizontalOffset: -3
        verticalOffset: 3
        radius: 8.0
        samples: 17
        color: "#60000000"
        source: butterfly
    }
}
/*##^##
Designer {
    D{i:0;formeditorZoom:4}
}
##^##*/

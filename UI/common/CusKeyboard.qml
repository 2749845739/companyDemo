import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.12
Rectangle {
    id:root
    implicitWidth: 718
    implicitHeight: 510
    color: "#C69C6C"
    radius: 8
    property bool selected: false
    signal keyBoard(var content);
    signal keyBoardback();
    signal keyBoardclose();
    MouseArea{
        anchors.fill: parent
        onPressed: {
            mouse.accepted=true
        }
    }

    Row{
        id:row1
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.leftMargin: 15
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 15
        height: 78
        spacing: 10
        Repeater{
            model: [1,2,3,4,5,6,7,8,9,0]
            Rectangle{
                width: 60
                height: 72
                color: "#C69C6C"
                layer.enabled: true
                radius: 10
                Button{
                    //property color bk: "white"
                    id:bton
                    width: 60
                    height: 72
                    anchors.top: parent.top
                    anchors.left: parent.left
                    text: modelData
                    font.pixelSize: 32
                    font.bold: true
                    background: Rectangle{
                        color: bton.pressed ? "#bfbfbf":"white"
                        radius: 10
                    }
//                    onClicked: {
//                        keyBoard(bton.text);
//                    }
                    onPressed: {
                        keyBoard(bton.text);
                    }
                }
                layer.effect: DropShadow {
                    transparentBorder: true
                    horizontalOffset: 0
                    verticalOffset: 4
                    samples: 15
                    smooth: true
                    cached: true
                }
            }
        }
    }
    Row{
        id:row2
        anchors.top: row1.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 15
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 15
        height: 78
        spacing: 10
        Repeater{
            model: selected ? ['Q','W','E','R','T','Y','U','I','O','P']: ['q','w','e','r','t','y','u','i','o','p']
            Rectangle{
                width: 60
                height: 72
                color: "#C69C6C"
                layer.enabled: true
                radius: 10
                Button{
                    //property color bk: "white"
                    id:bton2
                    width: 60
                    height: 72
                    anchors.top: parent.top
                    anchors.left: parent.left
                    text: modelData
                    font.pixelSize: 32
                    font.bold: false
                    background: Rectangle{
                        color: bton2.pressed ? "#bfbfbf":"white"
                        radius: 10
                    }
                    onPressed: {
                        keyBoard(bton2.text);
                    }
                }
                layer.effect: DropShadow {
                    transparentBorder: true
                    horizontalOffset: 0
                    verticalOffset: 4
                    samples: 15
                    smooth: true
                    cached: true
                }
            }
        }
    }
    Row{
        id:row3
        anchors.top: row2.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 45
        anchors.left: parent.left
        anchors.right: parent.right
        //anchors.rightMargin: 15
        height: 78
        spacing: 10
        Repeater{
            model: selected ?['A','S','D','F','G','H','J','K','L'] : ['a','s','d','f','g','h','j','k','l']
            Rectangle{
                width: 60
                height: 72
                color: "#C69C6C"
                layer.enabled: true
                radius: 10
                Button{
                    //property color bk: "white"
                    id:bton3
                    width: 60
                    height: 72
                    anchors.top: parent.top
                    anchors.left: parent.left
                    text: modelData
                    font.pixelSize: 32
                    font.bold: false
                    background: Rectangle{
                        color: bton3.pressed ? "#bfbfbf":"white"
                        radius: 10
                    }
                    onPressed: {
                        keyBoard(bton3.text);
                    }
                }
                layer.effect: DropShadow {
                    transparentBorder: true
                    horizontalOffset: 0
                    verticalOffset: 4
                    samples: 15
                    smooth: true
                    cached: true
                }
            }
        }
    }
    Rectangle{
        anchors.top: row3.bottom
        anchors.topMargin: 15
        anchors.leftMargin: 15
        anchors.left: parent.left
        width: 80
        height: 80
        layer.enabled: true
        layer.effect: DropShadow {
            transparentBorder: true
            horizontalOffset: 0
            verticalOffset: 4
            samples: 15
            smooth: true
            cached: true
        }
        radius: 10
        Button{
            id:btn_
            anchors.fill: parent
            text: "-"
            font.pixelSize: 40
            background: Rectangle{
                color: btn_.pressed?"#802c2c2c":"#BFC2C9"
                radius: 10
            }
            onPressed: {
                keyBoard(btn_.text);
            }
        }
    }

    Rectangle{
        anchors.top: row3.bottom
        anchors.topMargin: 15
        anchors.rightMargin: 15
        anchors.right: parent.right
        width: 80
        height: 80
        layer.enabled: true
        layer.effect: DropShadow {
            transparentBorder: true
            horizontalOffset: 0
            verticalOffset: 4
            samples: 15
            smooth: true
            cached: true
        }
        radius: 10
        Button{
            id:btn_x
            anchors.fill: parent
            font.pixelSize: 30
            background: Rectangle{
                Image {
                    anchors.centerIn: parent
                    source: "qrc:/Image/image/user/KeybackSpace.png"
                    width: sourceSize.width
                    height: sourceSize.height
                }
                color: btn_x.pressed?"#802c2c2c":"#BFC2C9"
                radius: 10
            }
            onPressed: {
                keyBoardback();
            }
        }
    }
    Row{
        id:row4
        anchors.top: row3.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 45+60+10
        anchors.left: parent.left
        anchors.right: parent.right
        //anchors.rightMargin: 15
        height: 78
        spacing: 10
        Repeater{
            model: selected ? ['Z','X','C','V','B','N','M']:['z','x','c','v','b','n','m']
            Rectangle{
                width: 60
                height: 72
                color: "#C69C6C"
                layer.enabled: true
                radius: 10
                Button{
                    //property color bk: "white"
                    id:bton4
                    width: 60
                    height: 72
                    anchors.top: parent.top
                    anchors.left: parent.left
                    text: modelData
                    font.pixelSize: 32
                    font.bold: false
                    background: Rectangle{
                        color: bton4.pressed ? "#bfbfbf":"white"
                        radius: 10
                    }
                    onPressed: {
                        keyBoard(bton4.text);
                    }
                }
                layer.effect: DropShadow {
                    transparentBorder: true
                    horizontalOffset: 0
                    verticalOffset: 4
                    samples: 15
                    smooth: true
                    cached: true
                }
            }
        }
    }
    Row{
        id:row5
        spacing: 28
        anchors.top: row4.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 15
        anchors.left: parent.left
        anchors.right: parent.right
        Rectangle{
            width: 80
            height: 80
            layer.enabled: true
            layer.effect: DropShadow {
                transparentBorder: true
                horizontalOffset: 0
                verticalOffset: 4
                samples: 15
                smooth: true
                cached: true
            }
            radius: 10
            Button{
                id:btn_1
                anchors.fill: parent
                font.pixelSize: 40
                text:"~"
                background: Rectangle{
                    color: btn_1.pressed?"#802c2c2c":"#BFC2C9"
                    radius: 10
                }
                onPressed: {
                    keyBoard(btn_1.text);
                }
            }
        }
        Rectangle{
            width: 80
            height: 80
            layer.enabled: true
            layer.effect: DropShadow {
                transparentBorder: true
                horizontalOffset: 0
                verticalOffset: 4
                samples: 15
                smooth: true
                cached: true
            }
            radius: 10
            Button{
                id:btn_2
                anchors.fill: parent
                font.pixelSize: 40
                text:"@"
                background: Rectangle{
                    color: btn_2.pressed?"#802c2c2c":"#BFC2C9"
                    radius: 10
                }
                onPressed: {
                    keyBoard(btn_2.text);
                }
            }
        }
        Rectangle{
            width: 80
            height: 80
            layer.enabled: true
            layer.effect: DropShadow {
                transparentBorder: true
                horizontalOffset: 0
                verticalOffset: 4
                samples: 15
                smooth: true
                cached: true
            }
            radius: 10
            Button{
                id:btn_3
                anchors.fill: parent
                font.pixelSize: 40
                text:"#"
                background: Rectangle{
                    color: btn_3.pressed?"#802c2c2c":"#BFC2C9"
                    radius: 10
                }
                onPressed: {
                    keyBoard(btn_3.text);
                }
            }
        }

        Rectangle{
            width: 80
            height: 80
            layer.enabled: true
            layer.effect: DropShadow {
                transparentBorder: true
                horizontalOffset: 0
                verticalOffset: 4
                samples: 15
                smooth: true
                cached: true
            }
            radius: 10
            Button{
                id:btn_4
                anchors.fill: parent
                font.pixelSize: 40
                text:"*"
                background: Rectangle{
                    color: btn_4.pressed?"#802c2c2c":"#BFC2C9"
                    radius: 10
                }
                onPressed: {
                    keyBoard(btn_4.text);
                }
            }
        }
        Rectangle{
            width: 80
            height: 80
            layer.enabled: true
            layer.effect: DropShadow {
                transparentBorder: true
                horizontalOffset: 0
                verticalOffset: 4
                samples: 15
                smooth: true
                cached: true
            }
            radius: 10
            Button{
                id:btn_5
                anchors.fill: parent
                font.pixelSize: 30
                background: Rectangle{
                    Image {
                        anchors.centerIn: parent
                        source:selected ?"qrc:/Image/image/user/keyUp.png":"qrc:/Image/image/user/keyDown.png"
                        width: sourceSize.width
                        height: sourceSize.height
                    }
                    color: //btn_5.pressed ? "#802c2c2c":"#BFC2C9"{
                    {
                        if(selected){
                            return "#BFC2C9"
                        }if(btn_5.pressed){
                            return "#802c2c2c"
                        }else{
                             return "white"
                        }
                    }
                    radius: 10
                }
                onClicked: {
                    //selected=!selected
                    if(selected){
                        selected=false;
                    }else{
                        selected=true;
                    }
                }
                onPressed: {
                    keyBoard(btn_5.text);
                }
            }
        }
        Rectangle{
            width: 146
            height: 80
            layer.enabled: true
            layer.effect: DropShadow {
                transparentBorder: true
                horizontalOffset: 0
                verticalOffset: 4
                samples: 15
                smooth: true
                cached: true
            }
            radius: 10
            Button{
                id:btn_6
                anchors.fill: parent
                font.pixelSize: 30
                background: Rectangle{
                    Image {
                        anchors.centerIn: parent
                        source: "qrc:/Image/image/user/keyEnter.png"
                        width: sourceSize.width
                        height: sourceSize.height
                    }
                    color: btn_6.pressed?"#802c2c2c":"#BFC2C9"
                    radius: 10
                }
                onClicked: {
                    root.visible=false;
                    keyBoardclose();
                }
                onPressed: {
                    keyBoard(btn_6.text);
                }
            }
        }
    }
    function showKeyboard(){
        root.visible=true;
    }
}

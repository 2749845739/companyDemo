import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import "../common"
Item {
    Rectangle{
        anchors.fill: parent
        color: "#707070"
        Row{
            anchors.left: parent.left
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            spacing: 12
            Image {
                id: clock
                source: "qrc:/Image/image/normal/clock.png"
                width: sourceSize.width
                height: sourceSize.height
            }
            RowLayout{
                //width: 55
                height: 32
                spacing: 0
                CusText{
                    Layout.preferredWidth: 32
                    Layout.maximumWidth:80
                    Layout.minimumWidth: 32
                    Layout.preferredHeight: 32
                    hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                    textContent: "仓门 "
                    fontSize: 10
                }
                Image {
                    id: cm
                    source: "qrc:/Image/image/normal/status_normal.png"
                    width: sourceSize.width
                    height: sourceSize.height
                }
            }
            RowLayout{
                spacing: 0
                CusText{
                    Layout.preferredWidth: 32
                    Layout.maximumWidth:80
                    Layout.minimumWidth: 32
                    Layout.preferredHeight: 32
                    hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                    textContent: "入料 "
                    fontSize: 10
                }
                Image {
                    id: rl
                    source: "qrc:/Image/image/normal/status_normal.png"
                    width: sourceSize.width
                    height: sourceSize.height
                }
            }
            RowLayout{
                spacing: 0
                CusText{
                    Layout.preferredWidth: 32
                    Layout.maximumWidth:80
                    Layout.minimumWidth: 32
                    Layout.preferredHeight: 32
                    hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                    textContent: "清料 "
                    fontSize: 10
                }
                Image {
                    id: ql
                    source: "qrc:/Image/image/normal/status_normal.png"
                    width: sourceSize.width
                    height: sourceSize.height
                }
            }
            RowLayout{
                spacing: 0
                CusText{
                    Layout.preferredWidth: 43
                    Layout.maximumWidth:80
                    Layout.minimumWidth: 32
                    Layout.preferredHeight: 32
                    hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                    textContent: "震动器 "
                    fontSize: 10
                }
                Image {
                    id: zdq
                    source: "qrc:/Image/image/normal/status_normal.png"
                    width: sourceSize.width
                    height: sourceSize.height
                }
            }
            RowLayout{
                spacing: 0
                CusText{
                    Layout.preferredWidth: 43
                    Layout.maximumWidth:80
                    Layout.minimumWidth: 32
                    Layout.preferredHeight: 32
                    hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                    textContent: "光源上 "
                    fontSize: 10
                }
                Image {
                    id: gys
                    source: "qrc:/Image/image/normal/status_normal.png"
                    width: sourceSize.width
                    height: sourceSize.height
                }
            }
            RowLayout{
                spacing: 0
                CusText{
                    Layout.preferredWidth: 43
                    Layout.maximumWidth:80
                    Layout.minimumWidth: 32
                    Layout.preferredHeight: 32
                    hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                    textContent: "光源下 "
                    fontSize: 10
                }
                Image {
                    id: gyx
                    source: "qrc:/Image/image/normal/status_normal.png"
                    width: sourceSize.width
                    height: sourceSize.height
                }
            }
            RowLayout{
                spacing: 0
                CusText{
                    Layout.preferredWidth: 43
                    Layout.maximumWidth:80
                    Layout.minimumWidth: 32
                    Layout.preferredHeight: 32
                    hAlignmentType:CusText.HALIGNMENT.AlignHCenter
                    textContent: "电子秤 "
                    fontSize: 10
                }
                Image {
                    id: dzc
                    source: "qrc:/Image/image/normal/status_normal.png"
                    width: sourceSize.width
                    height: sourceSize.height
                }
            }
        }
    }
}

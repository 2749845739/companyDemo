import QtQuick 2.12
import QtQuick.Controls 2.12
import "../common"
import ".."
Rectangle {
    SwipeView{
        id:swipeview
        anchors.fill: parent
        interactive: false
        Item {
            SelectGrainPane{
                visible: Login.isMainTain
                anchors.left: parent.left
                anchors.leftMargin: 150
                anchors.right: parent.right
                anchors.rightMargin: 150
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                lmodel: CusConfig.maintainPageModel
                onSelectGrain: {
                    GlobParameter.setGrainType(1)
                    dirver.initAllParamter();
                    maintaincenter.visible=true
                    //visible=false
                    bkgrd.visible=false
                    swipeview.currentIndex=1;
                }
            }
        }
        Item{
            MaintainHomePane{
                anchors.top: parent.top
                anchors.topMargin: 121
                anchors.bottom: parent.bottom
                width: parent.width
            }
        }

        Item{
            MaintainContentPane{
                id:paneTow
                anchors.top: parent.top
                anchors.topMargin: 121
                anchors.bottom: parent.bottom
                width: parent.width
            }
        }
    }
    MaintainTitlePane{
        id:maintaintitle
        anchors.top:parent.top
        width: parent.width
        height: 121
    }
    color: "#F6F6F6"
    //    onVisibleChanged: {
    //    }
}

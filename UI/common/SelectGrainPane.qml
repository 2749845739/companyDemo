import QtQuick 2.12
import QtQuick.Controls 2.5
import ".."
Item {
    property string lightImg: "qrc:/Image/image/maintain/lightSelected.png"
    property alias lmodel:view.model
    signal selectGrain(var index);
    ListView {
        id: view
        anchors.fill: parent
        clip: true
        snapMode: ListView.SnapToItem
        model: CusConfig.homePageModel
        orientation:ListView.Horizontal
        delegate: grainType
        spacing: 170
        highlight: highlightComponent
        focus: true
        ScrollBar.horizontal: ScrollBar {
            id:horScroball
            size:1
            policy: ScrollBar.AlwaysOff
        }
        currentIndex: -1
    }
    Component{
        id:highlightComponent
        Image {
            id: light
            source: lightImg
            width: sourceSize.width
            height: sourceSize.height
        }
    }
    Component{
        id:grainType
        Button{
            id:btndelegate
            width: 240
            height: 1080
            //propagateComposedEvents: true
            onClicked: {
                view.currentIndex=model.index
                selectGrain(model.indexId);
                CusConfig.selectedGrainName=model.name
            }
            contentItem:Image {
                anchors.fill: parent
                source: lightImg
                width: sourceSize.width
                height: sourceSize.height
                visible:/* btndelegate.hovered*/false
            }
            background: Item{
                Image{
                    anchors.top: parent.top
                    anchors.topMargin: 275
                    anchors.left: parent.left
                    anchors.horizontalCenter: parent.horizontalCenter
                    source:  view.currentIndex===model.index ? model.sourceSelect:model.source
                    width: sourceSize.width
                    height: sourceSize.height
                }
            }
        }
    }
}

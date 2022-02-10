pragma Singleton
import QtQuick 2.12
import QtQml 2.12
QtObject {
    id: config
    objectName: "config"
    property string fontFamily: "微软雅黑"
    property int fontPixel: 14
    property color textColor: "#282828"

    property bool homeEnable: false
    property string selectedGrainName: ""
    enum TriggerMode {
        HARDWARE=0,       // 硬件触发（默认）
        SOFTWARE       // 软件触发
    }
    property string grainType: ""

    property ListModel mergeResultImg: ListModel{
        id:mergeresultImg
    }

    property ListModel segmentModel: ListModel{
        id:segImgModel
    }
    property ListModel showSegmodel:ListModel{
        id:showImgModel
    }
    property ListModel maintainPageModel: ListModel{
        id:homePageModel
        ListElement{
            name:"大米"
            visible:true
            indexId:0
            source:"qrc:/Image/image/maintain/riceNormal.png"
            sourceSelect:"qrc:/Image/image/maintain/riceSelected.png"
        }
        ListElement{
            name:"小麦"
            visible:true
            indexId:1
            source:"qrc:/Image/image/maintain/wheatNormal.png"
            sourceSelect:"qrc:/Image/image/maintain/wheatSelected.png"
        }
        ListElement{
            name:"玉米"
            visible:true
            indexId:2
            source:"qrc:/Image/image/maintain/cronNormal.png"
            sourceSelect:"qrc:/Image/image/maintain/cronSelected.png"
        }
        //        ListElement{
        //            name:"大豆"
        //            visible:true
        //            indexId:3
        //            source:"qrc:/Image/image/normal/soybean.png"
        //            sourceSelect:"qrc:/Image/image/normal/soybean.png"
        //        }
        ListElement{
            name:"高粱"
            visible:true
            indexId:4
            source:"qrc:/Image/image/maintain/sorghumNormal.png"
            sourceSelect:"qrc:/Image/image/maintain/sorghumSelected.png"
        }
        //        ListElement{
        //            name:"芝麻"
        //            visible:true
        //            indexId:5
        //            source:"qrc:/Image/image/normal/sesame.png"
        //            sourceSelect:"qrc:/Image/image/normal/sesame.png"
        //        }
    }
    property ListModel wheatResultModel: ListModel{
        id:wheatResult
    }
    property ListModel userPageModel: ListModel{
        id:userPageModel
        ListElement{
            name:"大米"
            visible:true
            indexId:0
            source:"qrc:/Image/image/user/riceNormal.png"
            sourceSelect:"qrc:/Image/image/user/riceSelected.png"
        }
        ListElement{
            name:"小麦"
            visible:true
            indexId:1
            source:"qrc:/Image/image/user/wheatNormal.png"
            sourceSelect:"qrc:/Image/image/user/wheatSelected.png"
        }
        ListElement{
            name:"玉米"
            visible:true
            indexId:2
            source:"qrc:/Image/image/user/cronNormal.png"
            sourceSelect:"qrc:/Image/image/user/cronSelected.png"
        }
        //        ListElement{
        //            name:"大豆"
        //            visible:true
        //            indexId:3
        //            source:"qrc:/Image/image/normal/soybean.png"
        //            sourceSelect:"qrc:/Image/image/normal/soybean.png"
        //        }
        ListElement{
            name:"高粱"
            visible:true
            indexId:4
            source:"qrc:/Image/image/user/sorghumNormal.png"
            sourceSelect:"qrc:/Image/image/user/sorghumSelected.png"
        }
        //        ListElement{
        //            name:"芝麻"
        //            visible:true
        //            indexId:5
        //            source:"qrc:/Image/image/normal/sesame.png"
        //            sourceSelect:"qrc:/Image/image/normal/sesame.png"
        //        }
    }

    property ListModel rightModel: ListModel {
        id:rightModel
        //     ListElement{
        //         group:"camera"
        //         name:"相机一"
        //         visible:true
        //         groupOpen: true
        //     }
        //     ListElement{
        //         group:"camera"
        //         name:"相机二"
        //         visible:true
        //         groupOpen: true
        //     }
        ListElement{
            group:"PCB"
            name:"电机"
            visible:true
            groupOpen: true
            source:"qrc:/setting/MotorSetting.qml"
            indexId:0
        }
        ListElement{
            group:"PCB"
            name:"光源"
            visible:true
            groupOpen: true
            indexId:0
            source:"qrc:/setting/LightSetting.qml"
        }
        ListElement{
            group:"PCB"
            name:"称重仪"
            visible:true
            groupOpen: true
            indexId:0
            source:"qrc:/setting/WeightSetting.qml"
        }
        ListElement{
            group:"task"
            name:"校准模式"
            visible:true
            groupOpen: true
            indexId:0
            source:"qrc:/setting/AdjustSetting.qml"
        }
    }
    function appendrightModelData(length) {
        for(let i=0;i<length;i++){
            rightModel.append({
                                  group:"camera",
                                  name:"相机"+i,
                                  visible:true,
                                  groupOpen: true,
                                  source:"qrc:/setting/CameraSetting.qml",
                                  indexId:i
                              })
        }
    }
    function updateSection (section,isopen) {
        for (var i = 0; i < rightModel.count; ++i) {
            var obj = rightModel.get(i)
            if (obj["group"] === section) {
                rightModel.setProperty(i, "groupOpen", isopen)
            }
        }
    }
    function addSegmentImg(source,type){
        segImgModel.append({
                               sourceImg:source,
                               sourceType:type,
                               sourceOne:"",
                               sourceTwo:""
                           }
                           );
    }
    function filtersegImgModel(fileNames){
        mergeresultImg.clear();
        for(let i=0;i<fileNames.length;i++){
            mergeresultImg.append({
                                      sourceImg:"file:///"+fileNames[i],
                                  });
        }
    }
}

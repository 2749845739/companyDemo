import QtQuick 2.12
import QtQuick.Controls 2.5
import "./ContentItem"
import ".."
Item {
    Rectangle{
        anchors.fill: parent
        //color: "#dbdbdb"
        Image{
            source: "qrc:/Image/image/normal/background.png"
            width:1024
            height:768
        }
        SwipeView{
            interactive: false
            anchors.fill: parent
            id:stack
            clip: true
            currentIndex: 0
            HomePage{
                id:home
                onSwitchSampid: {
                    stack.currentIndex=1;
                    CusConfig.homeEnable=true;
                    //normalTitle.homeEnable=true;
                }
            }
            InputSampleId{
                id:sampleid
            }
            DetectPane{
                id:detection
                 visible:stack.currentIndex===2 ? true:false
            }
            RecordPane{
                id:recoedPane
            }
            onCurrentIndexChanged: {
                if(currentIndex===0){
                    normalTitle.titleBackground.color="transparent";
                }else if(currentIndex==1){
                    sampleid.inputControl="";
                    normalTitle.titleBackground.color="transparent";
                }else if(currentIndex==3){
                    recoedPane.startTime.value="";
                    recoedPane.endTime.value="";
                    normalTitle.titleBackground.color="#010512";
                }else{
                    normalTitle.titleBackground.color="#010512";
                }

            }
        }
    }
    function setCurrentIndex(index){
           stack.currentIndex=index;
           CusConfig.grainType="";
    }
    function resetResult(){
        detection.detectResulrReset();
    }
}

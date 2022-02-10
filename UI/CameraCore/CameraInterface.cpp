#include "CameraInterface.h"

CameraInterface::CameraInterface(){}

bool CameraInterface::findCamera()
{
    //QCoreApplication::processEvents();
    auto cam_driver = camera::driver::instance();
    // 扫描相机 std::unordered_map<std::string, std::shared_ptr<camera::camera>>
    while (true) {
        auto cameras = cam_driver->scan_camera();
        if(cameras.size()==3){
            for (auto& iter : cameras) {
                if (iter.second->ip() == "223.254.1.1") {
                     m_one = iter.second;
                }
                if (iter.second->ip() == "223.254.2.1") {
                    // cam_driver->remove_camera(iter.first);
                     m_two = iter.second;
                }
                if(iter.second->ip() == "223.254.3.1"){
                    // 开始相机
                     m_three = iter.second;
                }
            }
            m_cameraProperty=std::make_shared<CameraProperty>(m_one,m_two,m_three);
//            return true;
            break;
        }else{
            //继续找相机
            if(CMessageBox::ShowInfo("相机查找失败是否继续查找", nullptr ,CMessageBox::StandardButton::YesNo)==0){
                return false;
            }else{
                continue;
            }
        }
    }
    return true;
}




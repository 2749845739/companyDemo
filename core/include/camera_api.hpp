/**
 * @file camera_api.hpp
 * @author junjun dong (dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 1.3.0
 * @date 2021-06-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CAMERA_API_HPP_
#define CAMERA_API_HPP_

#include <cstdint>
#include <memory>
#include <vector>
#include <functional>
#include <string>
#include <utility>

#include <boost/dll/shared_library_load_mode.hpp>
#include <boost/dll/import.hpp>
#include <boost/config.hpp>
#include <boost/function.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>

namespace GCamera {

enum class CameraError : std::uint8_t {
    OK,
    ERR,
    ARG,
    MEM,
    INVALID_ID,
};

enum class CameraStatus : std::uint8_t {
    NORMAL,         // 正常状态
    CAPTURING,      // 正在进行数据抓取
    UNKNOWN,        // 未知状态
    OVERLOADING,    // 数据超载（有过多相机数据未处理）
};

enum class TriggerMode : std::uint8_t {
    HARDWARE,       // 硬件触发（默认）
    SOFTWARE,       // 软件触发
};

struct CameraInfo {
    std::uint32_t max_w;                // 相机图像最大宽度
    std::uint32_t max_h;                // 相机图像最大高度
    char mac[18];                       // 相机MAC地址
    char ip[16];                        // 相机IPv4地址
    TriggerMode trigger_mode;           // 相机的触发模式
    std::uint32_t trigger_delay[3];     // 触发延时（当前值，最小值，最大值）
    struct {
        /// 归一化的(0 ~ 2^32)曝光时间(当前值，最小值，最大值)
        std::uint32_t time[3];
        /// 归一化的(0 ~ 2^32)曝光增益值（当前值，最小值，最大值）
        std::uint32_t gain[3];
    } exposure;
    struct {
        /// 归一化的(0 ~ 2^32)数字增益R（当前值，最小值，最大值）
        std::uint32_t digital_r[3];
        /// 归一化的(0 ~ 2^32)数字增益G（当前值，最小值，最大值）
        std::uint32_t digital_g[3];
        /// 归一化的(0 ~ 2^32)数字增益B（当前值，最小值，最大值）
        std::uint32_t digital_b[3];
    } gains;
    // 颜色增强
    // 通透性
    //< 垂直翻转
    bool vflip;
    //< 水平翻转
    bool hflip;
};

/**
 * @brief 相机图像数据帧，数据格式为BGR888
 * 
 */
struct FrameInfo {
    std::uint32_t num;                      // 帧号
    std::uint32_t w;                        // 图像宽度
    std::uint32_t h;                        // 图像高度
    std::shared_ptr<std::uint8_t> data;     // 图像数据指针
};

class BOOST_SYMBOL_VISIBLE CameraApi {
 public:
    /**
     * @brief Destroy the Camera Api object
     * 
     */
    virtual ~CameraApi() {}

    /**
     * @brief 返回插件名称
     * 
     * @return std::string 插件名称
     */
    virtual std::string name() const = 0;

    /**
     * @brief 检测系统中的相机，并返回被检测到的相机id列表
     * 
     * @return std::vector<int> 相机id列表
     */
    virtual std::vector<int> findCamera() = 0;

    /**
     * @brief 打开相机
     * 
     * @param id 相机序号
     * @return CameraError 错误码
     */
    virtual CameraError openCamera(int id) = 0;

    /**
     * @brief 关闭相机
     * 
     * @param id 相机序号
     * @return CameraError 错误码
     */
    virtual CameraError closeCamera(int id) = 0;

    /**
     * @brief 获取相机信息
     * 
     * @param id 相机序号
     * @param pinfo 相机信息
     * @return CameraError 错误码
     */
    virtual CameraError infoCamera(int id, CameraInfo* pinfo) = 0;

    using statusCB = std::function<
    void(int camera_id, CameraStatus s, void* puser)>;

    /**
     * @brief 设置状态回调函数
     * 
     * @param cb 
     * @return CameraError 错误码
     */
    virtual CameraError setStatusCB(statusCB cb) {
        m_status_cb = std::move(cb);
        return CameraError::OK;
    }

    using frameCB = std::function<
    void(int camera_id, FrameInfo frame, void* puser)>;

    /**
     * @brief 设置数据帧回调函数
     * 
     * @param cb 
     * @return CameraError 错误码
     */
    virtual CameraError setFrameCB(frameCB cb) {
        m_frame_cb = std::move(cb);
        return CameraError::OK;
    }

    /**
     * @brief 开始相机取流
     * 
     * @param id 相机序号
     * @return CameraError 错误码
     */
    virtual CameraError startCamera(int id) = 0;

    /**
     * @brief 停止相机取流
     * 
     * @param id 相机序号
     * @return CameraError 错误码
     */
    virtual CameraError stopCamera(int id) = 0;

    /**
     * @brief 设置相机的曝光时间
     * 
     * @param id 相机序号
     * @param time 曝光时间（归一化到 0 ~ 2^16）
     * @return CameraError 错误码
     */
    virtual CameraError setCameraExposure(int id, std::uint32_t time) = 0;

    /**
     * @brief 设置相机R通道数字增益
     * 
     * @param id 相机序号
     * @param time 增益值（归一化到 0 ~ 2^16）
     * @return CameraError 错误码
     */
    virtual CameraError setCameraGainR(int id, std::uint32_t value) = 0;

    /**
     * @brief 设置相机G通道数字增益
     * 
     * @param id 相机序号
     * @param time 增益值（归一化到 0 ~ 2^16）
     * @return CameraError 错误码
     */
    virtual CameraError setCameraGainG(int id, std::uint32_t value) = 0;

    /**
     * @brief 设置相机B通道数字增益
     * 
     * @param id 相机序号
     * @param time 增益值（归一化到 0 ~ 2^16）
     * @return CameraError 错误码
     */
    virtual CameraError setCameraGainB(int id, std::uint32_t value) = 0;

    /**
     * @brief 设置相机曝光增益
     * 
     * @param id 相机序号
     * @param time 增益值（归一化到 0 ~ 2^16）
     * @return CameraError 错误码
     */
    virtual CameraError setCameraGainExposure(int id, std::uint32_t value) = 0;

    /**
     * @brief Set the Trigger Delay object
     * 
     * @param id 相机序号
     * @param delay 延时时间（归一化到 0 ~ 2^32）
     * @return CameraError 
     */
    virtual CameraError setTriggerDelay(int id, std::uint32_t delay) = 0;

    /**
     * @brief Set the Trigger Mode object
     * 
     * @param id 相机序号
     * @param mode 触发模式
     * @return CameraError 
     */
    virtual CameraError setTriggerMode(int id, TriggerMode mode) = 0;

    /**
     * @brief Set the Vertical Flip object
     * 
     * @param flip 
     * @return CameraError 
     */
    virtual CameraError setVerticalFlip(int id, bool flip) = 0;

    /**
     * @brief Set the Horizontal Flip object
     * 
     * @param flip 
     * @return CameraError 
     */
    virtual CameraError setHorizontalFlip(int id, bool flip) = 0;

    /**
     * @brief 软件触发一次，确定相机设置的是软件触发，且相机已经开始取流了
     * 
     * @param id 相机序号
     * @return CameraError 
     */
    virtual CameraError softTrigger(int id) const = 0;


    /**
     * @brief 通过creator symbol寻找插件
     * 
     * @tparam T 
     * @param plugins 插件路径
     * @param symbol 插件的creator symbol
     * @return std::vector<boost::shared_ptr<T>> 插件列表
     */
    template<typename T>
    static std::vector<boost::shared_ptr<T>> findPlugins(
            const std::vector<boost::dll::fs::path>& plugins,
            std::string symbol) {
        std::vector<boost::shared_ptr<T>> found_plugins;
        for (std::size_t i = 0; i < plugins.size(); ++i) {
            boost::dll::shared_library lib(
                plugins[i], boost::dll::load_mode::append_decorations);
            if (!lib.has(symbol.c_str())) {
                continue;
            }

            typedef boost::shared_ptr<T>(create_t)();
            boost::function<create_t> creator =
                boost::dll::import_alias<create_t>(
                    boost::move(lib), symbol.c_str());
            found_plugins.push_back(creator());
        }
        return found_plugins;
    }

 public:
    /// 相机状态回调函数
    statusCB m_status_cb;
    /// 相机数据帧回调函数
    frameCB m_frame_cb;
};

}  // namespace GCamera

#endif  // CAMERA_API_HPP_

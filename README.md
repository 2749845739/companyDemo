# G1000

## cmake build options:
1. main cmake
    - WITHOUT_UI: 默认`OFF`，是否编译界面
2. algorithm/graineval
    - DEMO_BY_FILES: 默认`OFF`，使用文件运行graineval算法
3. generator
    - SAVE_FC_IM: 默认`OFF`，保存监控相机图像到运行目录文件夹`fc_im`
    - TEST_READ_IM: 默认`OFF`，读取图像作为相机图像输入
4. logging
    - ENABLE_LOG: 默认`ON`，打印日志
    - LOG_NOCOLOR: 默认`OFF`，终端日志带有颜色
    - 日志等级控制环境变量`LOG_LVL`: `FATAL`, `MAJOR`, `MINOR`, `INFO`, `CALL`, `DATA`, `CMD`, `HEX`, `IMG`，默认等级`DATA`
    - 日志终端输出控制环境变量`LOG_TERM`: `OFF` -> 不在终端打印日志， `ON` -> 在终端打印日志， 默认ON
    - qt日志终端输出控制环境变量`LOG_TERMINAL`: `OFF` -> 不在终端打印日志， `ON` -> 在终端打印日志， 默认OFF

## 删除cmake缓存
ls | grep -v plugin | grep -v database | grep -v flowmodel | grep -v original | grep -v config.json | grep -v config.ini | grep -v params.txt | grep -v conf_weight.xml

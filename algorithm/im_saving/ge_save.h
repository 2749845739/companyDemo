/**
 * @file ge_save.h
 * @author junjun dong(dongjunjun@gaozhe.com.cn)
 * @brief GrainEval image saving
 * @version 0.1
 * @date 2021-12-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ALGORITHM_IM_SAVING_GE_SAVE_H_
#define ALGORITHM_IM_SAVING_GE_SAVE_H_

#include <memory>

#include "algorithm/graineval/dcdf.h"

namespace algorithm {

class ge_save {
 public:
  explicit ge_save(std::shared_ptr<dcdf> engine);
  ~ge_save();
};

}  // namespace algorithm

#endif  // ALGORITHM_IM_SAVING_GE_SAVE_H_

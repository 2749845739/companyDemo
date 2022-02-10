// 
// Copyright (C) 2018 Gaozhe Limited. All rights reserved.
// 
// The purpose of this file is to define the interface para interface
// File: gz_graineval_para.h
// Author: 007
// Date: 2018.11.6

#ifndef __GZ_GRAIN_EVAL_PARA_H__
#define __GZ_GRAIN_EVAL_PARA_H__


#include "gz_algo_type.h"


#define MAX_GRAIN_NUM  1024   /* max grain num batch in one image */


#ifdef __cplusplus
extern "C" {
#endif


// GRAIN SPECS
typedef enum __grainSpecs_E
{
    GZ_WHEAT = 0,            /* wheat */ 
    GZ_RICE = 1              /* rice */
}GZ_Grain_Specs_E;


// WHEAT UNSOUND TYPE
typedef enum __wheatUnsoundType_E
{
    WHEAT_NORMAL  = 0,       /* normal wheat */
    WHEAT_SCAB    = 1,       /* scab: bingban */
    WHEAT_SPROUT  = 2,       /* sproout: shengya */
    WHEAT_MILDEW  = 3,       /* mildew: shengmei */
    WHEAT_EATEN   = 4,       /* eaten: chongshi */
    WHEAT_BROKEN  = 5,       /* broken: posui */
    WHEAT_BLACK_EMBRYO  = 6  /*black embro: heipei*/
}GZ_Wheat_Unsound_Type_E;


// RICE UNSOUND TYPE
typedef enum __riceUnsoundType_E
{
    RICE_NORMAL  = 0,        /* normal rice */
    RICE_MILDEW  = 1,        /* mildew: shengmei */
    RICE_SPROUT  = 2,        /* sproout: shengya */
    RICE_EATEN   = 3,        /* eaten: chongshi */
    RICE_UNRIPE  = 4,        /* unripe: weishu */
    RICE_SCAB    = 5         /* scab: bingban */
}GZ_Rice_Unsound_Type_E;


// GRAIN EVALUATE SENS, DEFAULT IS NORMAL
typedef enum __grainEvalSens_E
{
    GRAIN_EVAL_NORMAL = 0,   /* normal sens, default*/
    GRAIN_EVAL_LOW    = 1,   /* low sens: maybe more wrong detection, but less miss detection */
    GRAIN_EVAL_HIGH   = 2    /* high sens: maybe more accurate, but maybe more miss detection */
}GZ_GrainEval_Sens_E;


// EVALUATE PARA 
typedef struct __grainEvalPara_S
{
    GZ_Grain_Specs_E     enEvaluateType;           // evaluate grain type: wheat or rice or other
    GZ_GrainEval_Sens_E  enEvaluateSens;           // sens of the evaluate
}GZ_GrainEval_Para_S;


// wheat item
typedef struct __wheatItems_S
{
    GZ_RECT32F_S            stWheatRect;            // wheat rect
    GZ_Wheat_Unsound_Type_E enWheatType;            // wheat type
    float                   fWei;                   // wheat weight
}GZ_Wheat_Item_S;


// rice item
typedef struct __riceItems_S
{
    GZ_RECT32F_S            stRiceRect;             // rice rect
    GZ_Rice_Unsound_Type_E  enRiceType;             // rice type
    float                   fWei;                   // rice weight
}GZ_Rice_Item_S;


// EVALUATE RESULT
// typedef struct __grainEvaluateRes_S
// {
//     GZ_Grain_Specs_E enGrainEvalType;                // evaluate grain type, which is same as the para user config;
//     GZ_S32           s32GrainNum;                    // grain num in one image, rice or wheat or others;
//     GZ_Wheat_Item_S  astWheatItems[MAX_GRAIN_NUM];   // wheat items, if config as rice, the wheat items will be empty;
//     GZ_Rice_Item_S   astRiceItems[MAX_GRAIN_NUM];    // rice items,  if config as wheat, the rice items will be empty;
//     GZ_FLOAT         f32WheatUnsoundRatio;           // unsound wheat ratio, if the type is rice, the value will return 1;
//     GZ_FLOAT         f32RiceUnsoundRatio;            // unsound rice ratio, if the type is wheat the value will return 1;
// }GZ_GrainEval_Result_S;


// typedef struct gz_wheat_batch_res_s_
// {
//     /* data */
//     GZ_S32   s32TotalNum;                   /* total wheat num in a batch */
//     GZ_FLOAT f32UnsoundWheatRatio;          /* unsound wheat ratio in batch */
//     GZ_FLOAT f32SCAB_in_UnsoundWheat;       /* bingban in unsound wheat ratio */
//     GZ_FLOAT f32SPROUT_in_UnsoundWheat;     /* shengya in unsound wheat ratio */
//     GZ_FLOAT f32MILDEW_in_UnsoundWheat;     /* shengmei in unsound wheat ratio */
//     GZ_FLOAT f32EATEN_in_UnsoundWheat;      /* chongshi in unsound wheat ratio */
//     GZ_FLOAT f32BROKEN_in_UnsoundWheat;     /* posui in unsound wheat ratio */
//     GZ_FLOAT f32BLACK_EMBRYO_in_UnsoundWheat;   /* heipei in unsound wheat ratio */
// }GZ_Wheat_Batch_Result_S;


typedef struct gz_wheat_batch_res_s_
{
    /* data */
    GZ_S32   s32TotalNum;           /* 一批样本总数量 */
    GZ_FLOAT f32UWRatio;            /* 不完善粒颗粒总比例 */
    GZ_FLOAT f32NORMALRatio;        /* 正常粒颗粒比例 */
    GZ_FLOAT f32SCABRatio;          /* 病斑粒颗粒比例 */
    GZ_FLOAT f32SPROUTRatio;        /* 生芽粒颗粒比例 */
    GZ_FLOAT f32MILDEWRatio;        /* 生霉粒颗粒比例 */
    GZ_FLOAT f32EATENRatio;         /* 虫蚀粒颗粒比例 */
    GZ_FLOAT f32BROKENRatio;        /* 破损粒颗粒比例 */
    GZ_FLOAT f32BLACKRatio;        /* 黑胚粒颗粒比例 */
}GZ_Wheat_Batch_Result_S;


// 质量比
typedef struct gz_wheat_batch_weightres_s_
{
    GZ_FLOAT f32WeightSum;          /* 总重量 */
    GZ_FLOAT f32UWWeightRatio;      /* 不完善粒重量比例 */
    GZ_FLOAT f32NORMALWeightRatio;  /* 病斑重量比例 */
    GZ_FLOAT f32SCABWeightRatio;    /* 病斑重量比例 */
    GZ_FLOAT f32SPROUTWeightRatio;  /* 生芽重量比例 */
    GZ_FLOAT f32MILDEWWeightRatio;  /* 生霉重量比例 */
    GZ_FLOAT f32EATENWeightRatio;   /* 虫蚀重量比例 */
    GZ_FLOAT f32BROKENWeightRatio;  /* 破损重量比例 */
    GZ_FLOAT f32BLACKWeightRatio;  /* 黑胚重量比例 */
}GZ_Wheat_Batch_WeightResult_S;

#ifdef __cplusplus
}
#endif
#endif //__GZ_GRAIN_PARA_H_

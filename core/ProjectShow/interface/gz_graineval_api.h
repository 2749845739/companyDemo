// 
// Copyright (C) 2018 Gaozhe Limited. All rights reserved.
// 
// The purpose of this file is to define the interface function interface
// File: gz_graineval_api.h
// Author: 007
// Date: 2018.11.6

#ifndef __GZ_GRAIN_EVAL_API_H__
#define __GZ_GRAIN_EVAL_API_H__

#include "gz_algo_type.h"
#include "gz_graineval_para.h"
#include <string>
#ifdef __cplusplus
extern "C"
{
#endif
/**********************************************************************************************
 * Func:   
 * 		GZ_GrainEval_Create
 * 
 * Desrip: 
 * 		Create grain evaluation algorithm handle, and malloc the memory for the algo
 * 
 * Para: 
 * 		In: 
 * 			s32W:         image height
 * 			s32H:         image width
 * 		Out: 
 * 			phGrainEval:  the handle of the algo
 * 		return:    
 * 			GZ_SUCCESS:   create success
 * 			GZ_FAILURE:   create failure
 * 
 * Author: 
 * 		007 @ GAOZHE
 * 
 * Version:
 * 		1.0.0Beta
 * 
 * Date: 
 * 		2018.11.06
 * 
 * Changelog:
 * 		2018.11.06: init version
 * *********************************************************************************************/
GZ_EXPORTS GZ_S32 GZ_GrainEval_Create(GZ_HANDLE &hGrainEval, std::string grain_t);


/**********************************************************************************************
 * Func:   
 * 		GZ_GrainEval_PrintLibInfo
 * 
 * Desrip: 
 * 		Print library version info and build date
 * 
 * Para: 
 * 
 * Author: 
 * 		007 @ GAOZHE
 * 
 * Version:
 * 		1.0.0Beta
 * 
 * Date: 
 * 		2018.11.06
 * 
 * Changelog:
 * 		2018.11.06: init version
 * *********************************************************************************************/
GZ_EXPORTS GZ_S32 GZ_GrainEval_PrintLibInfo();


/**********************************************************************************************
 * Func:   
 * 		GZ_GrainEval_Release
 * 
 * Desrip: 
 * 		Release the memory of the algo
 * 
 * Para: 
 * 		In:
 * 			hGrainEval:   the handle of the algo
 * 		return:    
 * 			GZ_SUCCESS:   release success
 * 			GZ_FAILURE:   release failure
 * 
 * Author: 
 * 		007 @ GAOZHE
 * 
 * Version:
 * 		1.0.0Beta
 * 
 * Date: 
 * 		2018.11.06
 * 
 * Changelog:
 * 		2018.11.06: init version
 * *********************************************************************************************/
GZ_EXPORTS GZ_S32 GZ_GrainEval_Release(GZ_HANDLE hGrainEval);



/**********************************************************************************************
 * Func:   
 * 		GZ_GrainEval_Config
 * 
 * Desrip: 
 * 		config the algo para
 * 
 * Para: 
 * 		In:
 * 			hGrainEval:       the handle of the algo
 * 			pstGrainEvalPara: the para which will be setted by user
 * 		return:    
 * 			GZ_SUCCESS:   config success
 * 			GZ_FAILURE:   config failure
 * 
 * Author: 
 * 		007 @ GAOZHE
 * 
 * Version:
 * 		1.0.0Beta
 * 
 * Date: 
 * 		2018.11.06
 * 
 * Changelog:
 * 		2018.11.06: init version
 * *********************************************************************************************/
GZ_EXPORTS GZ_S32 GZ_GrainEval_Config(GZ_HANDLE hGrainEval, GZ_GrainEval_Para_S* pstGrainEvalPara);


void GZ_SetImageName(GZ_HANDLE hGrainEval, std::string im_path, std::string im_name);

/**********************************************************************************************
 * Func:   
 * 		GZ_GrainEval_Process
 * 
 * Desrip: 
 * 		given the algo handle and the image input, will get the grain evaluation result 
 * 
 * Para: 
 * 		In: 
 * 			hGrainEval:   the handle of the algo
 * 			pstImgBG:       the first image will be evaluated
 * 			pstImgFG:       the second image will be evaluated(optional)
 * 		Out: 
 * 			pstGrainEvalRes: the reuslt of the evaluation
 * 		return:    
 * 			GZ_SUCCESS:   process success
 * 			GZ_FAILURE:   process failure
 * 
 * Author: 
 * 		007 @ GAOZHE
 * 
 * Version:
 * 		1.0.0Beta
 * 
 * Date: 
 * 		2018.11.06
 * 
 * Changelog:
 * 		2018.11.06: init version
 * *********************************************************************************************/
GZ_EXPORTS GZ_S32 GZ_GrainEval_Process(GZ_HANDLE hGrainEval, sbatch_data &input_data, GZ_GrainEval_Result_S &pstGrainEvalRes);


/**********************************************************************************************
 * Func:
 * 		GZ_GrainEval_Statistic_Wheat_Batch
 * 
 * Desrip: 
 * 		statistic the a batch result for wheat
 * 
 * Para: 
 * 		In: 
 * 			hGrainEval:             the handle of the algo
 * 			pstGrainEvalResults:    all the processed results
 * 			iBatchSize:             the size of array pstGrainEvalResults
 * 		Out: 
 * 			pstBatchRes: the reuslt of the batch
 * 		return:    
 * 			GZ_SUCCESS:   process success
 * 			GZ_FAILURE:   process failure
 * 
 * Author: 
 * 		007 @ GAOZHE
 * 
 * Version:
 * 		1.0.0Beta
 * 
 * Date: 
 * 		2019.05.24
 * 
 * Changelog:
 * 		2019.05.24: init version
 * *********************************************************************************************/
// GZ_EXPORTS GZ_S32 GZ_GrainEval_Statistic_Wheat_Batch(
//     GZ_HANDLE hGrainEval,
//     GZ_GrainEval_Result_S* pstGrainEvalResults[],
//     int iBatchSize,
//     GZ_Wheat_Batch_Result_S* pstBatchRes,
//     GZ_Wheat_Batch_WeightResult_S* pstBatchWeightRes);

struct unsound_item {
    GZ_Wheat_Unsound_Type_E unsound_type;  // 不完善粒类型
    float percents;  // 占比
};

GZ_EXPORTS GZ_S32 GZ_GrainEval_Statistic_Wheat_BatchDynamic(
    GZ_HANDLE hGrainEval,
    GZ_GrainEval_Result_S &pstGrainEvalResults);  // 颗粒总数

#ifdef __cplusplus
}
#endif

#endif //__GZ_GRAIN_API_H__
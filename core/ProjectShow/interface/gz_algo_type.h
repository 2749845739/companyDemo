/******************************************************************************** 
 * File:    gz_algo_type.h
 * Version: 1.0
 * 
 * Author: 007 @ Gaozhe
 * 
 * Date: 2018.11.6
 * 
 * Description:	Fundamental type definitions for Gaozhe algorithms
 * 
 * Copyright (C) 2018 Gaozhe Limited. All rights reserved.
 * 
 * Change log:
 * 
 * 20181106: first init.
 * 
 * 
 * ********************************************************************************/
 #include <string>
 #include<stdio.h>
 #include <vector>
 #include<memory>
 #include <unordered_map>
 #include <opencv2/imgcodecs.hpp>

#ifndef __GZ_ALGO_TYPE_H__
#define __GZ_ALGO_TYPE_H__

#ifdef __cplusplus
extern "C"
{
#endif

    typedef unsigned char      GZ_U8;
    typedef unsigned char      GZ_UCHAR;
    typedef unsigned short     GZ_U16;
    typedef unsigned int       GZ_U32;
    typedef char               GZ_S8;
    typedef short              GZ_S16;
    typedef int                GZ_S32;

#ifndef _M_IX86
    typedef unsigned long long GZ_U64;
    typedef long long          GZ_S64;
#else
    typedef __int64            GZ_U64;
    typedef __int64            GZ_S64;
#endif

    typedef char               GZ_CHAR;
    typedef char*              GZ_PCHAR;
    typedef float              GZ_FLOAT;
    typedef double             GZ_DOUBLE;
    typedef void               GZ_VOID;
    typedef unsigned long      GZ_SIZE_T;
    typedef unsigned long      GZ_LENGTH_T;

    /* Handle */
    typedef void*              GZ_HANDLE;

    typedef enum __gzBool_E
    {
        GZ_FALSE = 0,
        GZ_TRUE = 1,
    } GZ_BOOL_E;

#ifndef NULL
    #define NULL 0L
#endif

#define GZ_NULL     0L
#define GZ_NULL_PTR 0L
#define GZ_SUCCESS  0
#define GZ_FAILURE  (-1)

    /** GZ_EXPORTS */
#if defined(GZ_API_EXPORTS)
    #define GZ_EXPORTS __declspec(dllexport)
#elif defined(GZ_API_IMPORTS)
    #define GZ_EXPORTS __declspec(dllimport)
#else
    #define GZ_EXPORTS extern
#endif

    /** GZ_INLINE */
#ifndef GZ_INLINE
#if defined __cplusplus
    #define GZ_INLINE inline
#elif (defined WIN32 || defined WIN64) && !defined __GNUC__
    #define GZ_INLINE __inline
#else
    #define GZ_INLINE static
#endif
#endif

    /* Point definition (16b) */
    typedef struct __gzPoint_S
    {
        GZ_S16 s16X;
        GZ_S16 s16Y;
    } GZ_POINT_S;

    /* Point definition (32b) */
    typedef struct __gzPoint32S_S
    {
        GZ_S32 s32X;
        GZ_S32 s32Y;
    } GZ_POINT32S_S;

    /* Point definition (single-precision) */
    typedef struct __gzPoint32F_S
    {
        GZ_FLOAT f32X;
        GZ_FLOAT f32Y;
    } GZ_POINT32F_S;

    /* 3D Point definition (32b) */
    typedef struct __gzPoint3D_S
    {
        GZ_S32 s32X;
        GZ_S32 s32Y;
        GZ_S32 s32Z;
    } GZ_POINT3D_S;

    /* Line definition (32b) */
    typedef struct __gzLine_S
    {
        GZ_POINT_S stPs;      /* start point */
        GZ_POINT_S stPe;      /* end point */
    } GZ_LINE_S;

    /* Rectangle definition (32b) */
    typedef struct __gzRect_S
    {
        GZ_S16 s16X1;         /* Top left x */
        GZ_S16 s16Y1;         /* Top left y */
        GZ_S16 s16X2;         /* Bottom right x */
        GZ_S16 s16Y2;         /* Bottom right y */
    } GZ_RECT_S;


    /* Rectangle definition (32b) */
    typedef struct __gzRect2_S
    {
        GZ_S16 s16X1;         /* Top left x */
        GZ_S16 s16Y1;         /* Top left y */
        GZ_S16 s16Height;     /* height of the rect  */
        GZ_S16 s16Width;      /* width of the rect */
    } GZ_RECT2_S;


    /* Rectangle definition (float)*/
    typedef struct __gzRect32F_S
    {
        GZ_FLOAT f32X1;      /* Top left x */
        GZ_FLOAT f32Y1;      /* Top left y */
        GZ_FLOAT f32X2;      /* Bottom right x */
        GZ_FLOAT f32Y2;      /* Bottom right y */
    } GZ_RECT32F_S;

    /* Polygon definition */
    #define MAX_VERTEX_PER_POLYGON 8

    typedef struct __gzPolygon_S
    {
        GZ_U32  u32VertexNum ;                         /* Number of vertexes */
        GZ_POINT_S astVertex[MAX_VERTEX_PER_POLYGON];  /* Vertexes with clockwise order */
    } GZ_POLYGON_S;

    /* Function Status */
    typedef enum __gzStatus_E
    {
        GZ_STATUS_CHECK_LICENSE_TIMEOUT = -3,  /* Timeout error in license checking */
        GZ_STATUS_CHECK_LICENSE_FAILED  = -2,  /* Failure in license checking */
        GZ_STATUS_READ_MAC_FAILED       = -1,  /* Failed in reading MAC address */
        GZ_STATUS_OK                    =  1,  /* Success */
        GZ_STATUS_SKIP                  =  2,  /* Function is skipped */
        GZ_STATUS_FALSE                 =  3,  /* False in function */
        GZ_STATUS_INVALID_PARA          =  4,  /* Function parameters are invalid */
        GZ_STATUS_UNSUPPORT             =  5
    } GZ_STATUS_E;

    /* Pixel definition in RGB */
    typedef struct __gzPixel_S
    {
        GZ_U8 u8B;           /* Blue Channel  */
        GZ_U8 u8G;           /* Green Channel */
        GZ_U8 u8R;           /* Red Channel   */
    } GZ_PIXEL_S;

    /* Pixel definition in HSV */
    typedef struct __gzHSVPixel_S
    {
        GZ_FLOAT f32H;       /* Hue Channel  */
        GZ_FLOAT f32S;       /* Saturation Channel */
        GZ_FLOAT f32V;       /* Value Channel */
    } GZ_HSV_PIXEL_S;

    /* Pixel definition in HSL */
    typedef struct __gzHSLPixel_S
    {
        GZ_FLOAT f32H;       /* Hue Channel  */
        GZ_FLOAT f32S;       /* Saturation Channel */
        GZ_FLOAT f32L;       /* Luminance Channel  */
    } GZ_HSL_PIXEL_S;

    /* Image in RGB format */
    typedef struct __gzRGBImage_S
    {
        GZ_S32 s32W;         /* Image width  */
        GZ_S32 s32H;         /* Image height */
        GZ_U8 *pu8Data;      /* Image data buffer */
        GZ_U32 u32Time;      /* Time tag */
    } GZ_RGB_IMAGE_S;

    /* Image in HSV format */
    typedef struct __gzHSVImage_S
    {
        GZ_S32   s32W;       /* Image width  */
        GZ_S32   s32H;       /* Image height */
        GZ_FLOAT *pf32Data;  /* Image data buffer */
        GZ_U32   u32Time;    /* Time tag */
    } GZ_HSV_IMAGE_S;

    /* Image in gray scale format */
    typedef struct __gzGrayImage_S
    {
        GZ_S32 s32W;         /* Image width  */
        GZ_S32 s32H;         /* Image height */
        GZ_U8 *pu8Data;      /* Image data buffer */
    } GZ_GRAY_IMAGE_S;

    /* Image in 16b gray scale format */
    typedef struct __gzGrayImage16_S
    {
        GZ_S32 s32W;         /* Image width  */
        GZ_S32 s32H;         /* Image height */
        GZ_S16 *ps16Data;    /* Image data buffer */
    } GZ_GRAY_IMAGE16_S;

    /* Image in 32b gray scale format */
    typedef struct __gzGrayImage32_S
    {
        GZ_S32 s32W;         /* Image width  */
        GZ_S32 s32H;         /* Image height */
        GZ_S32 *ps32Data;    /* Image data buffer */
    } GZ_GRAY_IMAGE32_S;

    /* Image in YUV422 format */
    typedef struct __gzYUVImage422_S
    {
        GZ_S32 s32W;         /* Image width  */
        GZ_S32 s32H;         /* Image height */
        GZ_U8 *pu8Y;         /* Y data buffer */
        GZ_U8 *pu8U;         /* U data buffer */
        GZ_U8 *pu8V;         /* V data buffer */
        GZ_U32 u32Time;      /* Time tag */
        GZ_U32 u32Flag;      /* Reserved flag */
    } GZ_YUV_IMAGE422_S;

    /* Image in YUV420 format */
    typedef struct __gzYUVImage420_S
    {
        GZ_S32 s32W;         /* Image width  */
        GZ_S32 s32H;         /* Image height */
        GZ_U8 *pu8Y;         /* Y data buffer */
        GZ_U8 *pu8U;         /* U data buffer */
        GZ_U8 *pu8V;         /* V data buffer */
        GZ_U32 u32Time;      /* Time tag */
        GZ_U32 u32Flag;      /* Reserved flag */
    } GZ_YUV_IMAGE420_S;

    /* YUV format type */
    typedef enum __gzYUVFormat_E
    {
        GZ_YUV_FORMAT_422 = 0,
        GZ_YUV_FORMAT_420,
        GZ_YUV_FORMAT_HIS_SP422,
        GZ_YUV_FORMAT_HIS_SP420
    } GZ_YUV_FORMAT_E;

    /* Universal YUV image definition */
    typedef struct __gzYUVImage_S
    {
        GZ_S32 s32W;         /* Image width  */
        GZ_S32 s32H;         /* Image height */
        GZ_U8 *pu8Y;         /* Y data buffer */
        GZ_U8 *pu8U;         /* U data buffer */
        GZ_U8 *pu8V;         /* V data buffer */
        GZ_U32 u32Time;      /* Time tag */
        GZ_U32 u32Flag;      /* Reserved flag */
        GZ_YUV_FORMAT_E enFormat; /* YUV format */
    } GZ_YUV_IMAGE_S;

    /* 3-ch image format type */
    typedef enum __gzImageFormat_E
    {
        GZ_IMAGE_FORMAT_YUV422 = 0,
        GZ_IMAGE_FORMAT_YUV420,
        GZ_IMAGE_FORMAT_YUV422SP,
        GZ_IMAGE_FORMAT_YUV420SP,
        GZ_IMAGE_FORMAT_UYVY,
        GZ_IMAGE_FORMAT_YV12,
        GZ_IMAGE_FORMAT_YU12,
        GZ_IMAGE_FORMAT_NV12,
        GZ_IMAGE_FORMAT_NV21,
        GZ_IMAGE_FORMAT_RGB_packed,
        GZ_IMAGE_FORMAT_RGB_planar,
        GZ_IMAGE_FORMAT_BGR_packed,
        GZ_IMAGE_FORMAT_BGR_planar
    } GZ_IMAGE_FORMAT_E;

    /* 3-ch image definition */
    typedef struct __gzImage3_S
    {
        GZ_S32 s32W;         /* Image width  */
        GZ_S32 s32H;         /* Image height */
        GZ_U8 *pu8D;         /* data pointer */
        GZ_U32 u32Time;      /* Time tag */
        GZ_U32 u32Flag;      /* Reserved flag */
        GZ_IMAGE_FORMAT_E enFormat; /* image format pointer */
    } GZ_IMAGE3_S;

    /**
    * @brief 颗粒检测的类型，包含正常，边缘，杂质等类型
    */
    enum class detect_t : std::uint8_t {
        WHITE_WHEAT = 0,   /// 白麦
        RED_WHEAT = 1,     /// 红麦
        RICE = 2,   /// 大米
        CORN = 3,   /// 玉米
        IMPURITY = 4,   /// 杂质
        JIEJIEMAI = 5     /// 节节麦
    };

    enum class wheat_t : std::uint8_t {
        zc = 0,   // 正常粒
        bb,       // 病斑粒(大类，包含例如赤霉，黑胚等多种子类)
        sy,       // 生芽粒
        sm,       // 生霉粒
        cs,       // 虫蚀粒
        ps,       // 破损粒
        hp,       // 黑胚粒(隶属于病斑粒)
    };


    enum class rice_t : std::uint8_t {
        zc = 0,   // 正常粒
        hlm,      // 黄粒米
        ps,       // 破损粒
    };


    /**
    * @brief 样品的批次数据（样品的批次可能包含多个维度，pbinfo->dimension）
    * 
    */
    struct sbatch_data {
        // 各个维度上的数据
        std::vector<std::shared_ptr<cv::Mat>> vec_data;
    };


    struct GZ_GrainEval_Result_S {

        struct common{

            // 每采集完成一次图片获得重量后，由软件填入重量
            std::vector<float> weights;
            // Appearance
            // 所有颗粒的长度
            std::vector<float> lengths;
            // 所有颗粒的宽度
            std::vector<float> widths;
            // 所有颗粒的长宽比
            std::vector<float> aspect_ratio;
            // 所有颗粒的周长
            std::vector<float> perimeter;

            // 平均长度
            float avg_length=0;
            // 平均宽度
            float avg_width=0;
            // 平均长宽比
            float avg_aspect_ratio=0;
            // 平均周长
            float avg_perimeter=0;

            // 每一次采集图片的所有颗粒的小图，小图的排列顺序为（au_crop, bu_crop, ad_crop, bd_crop, au_crop_mask, bu_crop_mask）
            // 例如取图片上第i个颗粒的明场图片即 seg_result[i][0],小图在软件界面上显示完成后，由软件侧进行释放
            std::vector<std::vector<std::shared_ptr<cv::Mat>>> seg_result;

        };


        struct wheat{

            // all batch grain impurity count
            std::vector<std::vector<int>> grain_impurity_count;
            // all batch unsound count
            std::vector<std::vector<int>> normal_unsound_count;
            // all batch weight
            std::vector<std::vector<float>> batch_unsound_wei;
            //total count
            std::vector<int> final_unsound_count;
            //total weight
            std::vector<float> final_unsound_weight;
            //total white wei
            std::vector<float> white_weight;
            
            // 所有颗粒的分类结果
            std::vector<std::pair<wheat_t, float>> vec_recs;

            // ====================update once===================//
            // final result (update once)
            // 正常和不完善颗粒的质量比
            std::vector<std::pair<wheat_t, float>> weight_ratio;
            // 正常和不完善颗粒的数量比
            std::vector<std::pair<wheat_t, float>> count_ratio;
            
            // 节节麦比例
            float jiejiemai_ratio=0;
            // 千粒重
            float thousandWeight=0;
            // 容重
            float volumeWeight=0;
            // 白麦比例
            float whiteWheat_count_ratio=0;
            float whiteWheat_wei_ratio=0;
            // 异种粮比例
            float exoticWheat_ratio=0;
            // 杂质比例
            float impurity_ratio=0.0235f;
            // 水份
            float moisture=0;
            


        };

        struct rice{

            // all batch broken count
            std::vector<int> broken_count;
            // all batch whole count
            std::vector<int> whole_count;
            // all batch yellow_rice_count
            std::vector<int> yellow_rice_count;

            // 所有颗粒的分类结果
            std::vector<std::pair<rice_t, float>> vec_recs;

            // 精米面积
            std::vector<float> whole_area;
            //   碎米米面积
            std::vector<float> broken_area;
            // 垩白面积
            std::vector<float> chalky_area;
            //精米率
            float whole_ratio;
            //碎米率
            float broken_ratio;
            // 黄米率
            float yellow_ratio;
            //垩白度
            float chalky_ratio;
            

        };

        wheat wheat_result;
        rice rice_result;
        common common_result;

    };



#ifdef __cplusplus
}
#endif

#endif /*_GZ_ALGO_TYPE_H_*/



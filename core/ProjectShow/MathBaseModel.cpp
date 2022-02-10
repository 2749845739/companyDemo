#include "MathBaseModel.h"
MathBaseModel::MathBaseModel(std::shared_ptr<BaseParameter> base):m_base(base){}

void MathBaseModel::setSegtype(imgDataStruct &, GZ_GrainEval_Result_S &)
{
   qDebug()<<"MathBaseModel";
}

BaseParameter::BaseParameter()
{
    qRegisterMetaType<CVImagData>("CVImagData");
    qRegisterMetaType<imgDataStruct>("imgDataStruct");
}


#ifndef ABSTRACTALGORITHMTYPE_H
#define ABSTRACTALGORITHMTYPE_H
#include "algorithm/graineval/graineval_api.hpp"
#include <GlobalParameter.h>
class AbstractAlgorithm : public QObject{
    Q_OBJECT
public:
    explicit AbstractAlgorithm(QObject* parent);
    virtual void porcess(algorithm::result&)=0;
    virtual void dynamic_result(algorithm::result&)=0;
    virtual Q_INVOKABLE bool printResult()=0;
    virtual Q_INVOKABLE void getSegTypeImg(int)=0;
signals:
    void sigDynamicFinshed();
};

class AbstractAlgorithmTypeFactor
{
public:
    explicit AbstractAlgorithmTypeFactor();
    virtual std::shared_ptr<AbstractAlgorithm> createAlgorithm()=0;
};

#endif // ABSTRACTALGORITHMTYPE_H

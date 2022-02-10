#ifndef ALGORITHMMANAGER_H
#define ALGORITHMMANAGER_H
#define ALG_PLUGIN_NAME "algorithm_p600"
#include "CMessageBox.h"
#include <QApplication>
#include <boost/dll/shared_library.hpp>
#include <boost/dll/shared_library_load_mode.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/directory.hpp>
#include <boost/filesystem/exception.hpp>
#include <boost/filesystem/file_status.hpp>
#include "algorithm/graineval/graineval_api.hpp"
#include "generator/dcdf_generator.h"
#include <QThreadPool>
#include "AlgorithDataPool.h"
#include "AbstractAlgorithmType.h"
#include "../../algorithm/graineval/dcdf.h"
class AlgorithmProcess:public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit AlgorithmProcess(std::shared_ptr<AbstractAlgorithm> abstractAlgorithm
                              ,algorithm::result res);
    void run() override;
private:
    std::shared_ptr<AbstractAlgorithm> m_AbstractAlgorithm;
    algorithm::result m_res;
};

class AlgorithmProcessth:public QThread{
    Q_OBJECT
public:
    explicit AlgorithmProcessth(std::shared_ptr<AbstractAlgorithm> abstractAlgorithm,QObject*parent);
    void run() override;
    ~AlgorithmProcessth();
private:
    std::shared_ptr<AbstractAlgorithm> m_AbstractAlgorithm;
    bool m_isStop {false};
};
class AlgorithmMeargeImg:public QThread{
    Q_OBJECT
public:
    explicit AlgorithmMeargeImg(int index,QObject*parent);
    void run() override;
    ~AlgorithmMeargeImg();
private:
    bool m_isStop {false};
    int m_index;
};




class AlgorithmResult:public QObject,public QRunnable{
    Q_OBJECT
public:
    explicit AlgorithmResult(std::shared_ptr<AbstractAlgorithm> abstractAlgorithm,algorithm::result res);
    void run() override;
private:
    std::shared_ptr<AbstractAlgorithm> m_AbstractAlgorithm;
    algorithm::result m_res;
};

class AlgorithmManager:public algorithm::dcdf
{
public:
    explicit AlgorithmManager(std::shared_ptr<generator::dcdf_engine> dcdf_engine,
                               std::string dev_id);
    void findgraineval();
private:
    boost::shared_ptr<algorithm::graineval_api> m_plib;
};

#endif // ALGORITHMMANAGER_H

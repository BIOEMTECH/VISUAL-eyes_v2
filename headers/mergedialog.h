#ifndef MERGEDIALOG_H
#define MERGEDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QListView>
#include <QTreeView>
#include <QDebug>
#include <QSqlQuery>
#include <QProcess>
#include <QDateTime>
#include "headers/readinputinfo.h"
#include "headers/imageFusion.hpp"
#include "Includes/dicomEncoder.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace Ui {
class mergeDialog;
}

class mergeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mergeDialog(ReadInputInfo*, QWidget *, QString, QString, QString, QString, QString, QString, bool);
    ~mergeDialog();

private slots:
//    void on_pB_select_clicked();
//    void cB_convFactor_currentIndexChanged(int);
    void on_pB_ok_clicked();
    void on_pB_cancel_clicked();
//    void on_pB_merge_clicked();
    void addFrames();
    void saveSumDICOM();
    void closeEvent(QCloseEvent *);
    void saveInfoFile();

private:
    Ui::mergeDialog *ui;
    ReadInputInfo* m_readInputInfo;
    QList<cv::Mat> m_rawFrames, m_sumFrames;
    QStringList m_frameNameList, m_allFramesList, m_remainFrames;
    QString m_frameNames;
    QString m_FrameDirectory;
    QString m_OpticalPath, m_xrayPath;
    QString m_DestDirectory;
    QString m_postProcessDir;
    QString m_study;
    QString m_givenFilename;
    QHash<int,QString> m_frameTimes;
    int m_mergeFrameCount;
    bool allFramesSelected=false;
    bool m_isBeta=false;
    int rows, cols, xfusion, yfusion;
};

#endif // MERGEDIALOG_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QFileDialog>
#include<QDebug>
#include<QStringList>
#include<QDate>
#include<QErrorMessage>
#include<QVector>
#include<QSharedPointer>
#include"qcustomplot.h"
#include"Interpolation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_commandLinkButton_clicked();

    void on_commandLinkButton_1_clicked();

    void on_commandLinkButton_2_clicked();

    void on_commandLinkButton_3_clicked();

    void on_commandLinkButton_4_clicked();

    void on_commandLinkButton_5_clicked();

    void on_commandLinkButton_6_clicked();

    void on_commandLinkButton_7_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_4_stateChanged(int arg1);

    void on_checkBox_5_stateChanged(int arg1);

    void on_checkBox_6_stateChanged(int arg1);

    void on_checkBox_7_stateChanged(int arg1);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_buttonBox_2_accepted();

    void on_pushButton_3_clicked();

    void on_PlanPath_clicked();

private:
    struct DT{
        QString DAT;
        int ID;
        int state;
    };

    Ui::MainWindow *ui;
    QString del;
    QString del2;                              //for the robustness of the algorithm, the del of the dataset and adjacency may be different
    QStringList FileNames;                    //store all file names of the Dataset
    QStringList FilePaths;                    //strore all file paths of the Dataset
    QString DatasetDirctory;                    //the path of the Dataset
    QString AdjacencyDirctory;
    QString path;
    QErrorMessage EM;

    //
    QString StationID;
    QDate Date;
    QTime time;
    QString PDate;                              //previous date
    QTime start_time;
    QTime endtime;
    QTime timestep;
    QTime referrence;

    //store data of each station of the same date
    QVector<QVector<DT>> DTofEachStation;
    QVector<DT> SDT;
    //store the x and y of the plot
    QVector<double> QV_x;                       //x represents the time of the date
    QVector<double> QV_y_inflow;
    QVector<double> QV_y_outflow;
    QVector<double> InterpolateData_x;
    QVector<double> InterpolateData_y_inflow;
    QVector<double> InterpolateData_y_outflow;

    QVector<QCPGraphData> QGData_inflow;
    QVector<QCPGraphData> QGData_outflow;
    NewtonInterpolation InterpolateData;

    QCPTextElement *TextElement;
    bool flag;

    //planning path
    int*lineA;
    int*lineB;
    int*lineC;
    int**AdjacencyArray;
    int**DistanceArray;
    int**PathArray;
    int StartStaionID;
    int EndStationID;
    QString PrintedPath;
    int pathlength;



    bool* InterestedData;                       //represent the data you are interested in(tmp).Eg:if you're interested in time,InterestedData[0]=true.
    bool* DataSelected;                         //represent the data you are interested in after you clicked OK,if you clicked cancel,this will not changed    
    void getFileNames(const QString&path);
    void showErrorMessage();
    void finddel();
    bool compareDate(QString &a, QString &b);
    void formPlot();
    void printPath(const int&start,const int&end,int**P);

};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    InterestedData=new bool[7]{false};
    DataSelected=new bool[7]{false};
    lineA=new int[81]{0};
    lineB=new int[81]{0};
    lineC=new int[81]{0};
    AdjacencyArray=new int*[81];
    DistanceArray=new int*[81];
    PathArray=new int*[81];
    for(int i=0;i<81;++i){
        AdjacencyArray[i]=new int[81]{0};
        DistanceArray[i]=new int[81];
        PathArray[i]=new int[81];
    }
    for(int i=0;i<81;++i)
        for(int j=0;j<81;++j){
            PathArray[i][j]=-1;                                  //PathArray's initial value is P[i][j]=j,
            DistanceArray[i][j]=INT_MAX;                        //DistanceArray's initial value is ifinity
        }

    ui->start_time->setDisplayFormat("hh:mm");
    ui->endtime->setDisplayFormat("hh:mm");
    ui->timestep->setDisplayFormat("hh:mm");
    ui->timestep->setMinimumTime(QTime(0,1));
    ui->timestep->setMaximumTime(QTime(8,0,0));
    referrence=ui->timestep->time();
    referrence=referrence.addSecs(-60);                     //set the reference as 00:00:00
    ui->dateEdit->setDisplayFormat("yyyy-MM-dd");

    for(int i=0;i<81;++i)
        DTofEachStation.push_back(SDT);

    // Initialize the plot
    ui->plot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    ui->plot->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(12);
    ui->plot->legend->setFont(legendFont);
    ui->plot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    flag=false;
    TextElement=new QCPTextElement(ui->plot, "Title", QFont("sans", 12, QFont::Bold));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete InterestedData;
    delete DataSelected;
    delete lineA;
    delete lineB;
    delete lineC;

}

//slots

//page button
void MainWindow::on_commandLinkButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_commandLinkButton_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_commandLinkButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_commandLinkButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_commandLinkButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_commandLinkButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_commandLinkButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_commandLinkButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


//pushbutton in the Init page about data select
void MainWindow::on_pushButton_2_clicked()
{
    QFileDialog Dialog;
    DatasetDirctory =Dialog.getExistingDirectory(0,"Select Dataset","D:");
    getFileNames(DatasetDirctory);
    finddel();
}

//getfilename function
void MainWindow::getFileNames(const QString &path){
    QDir dir(path);
    QStringList NameFilter;
    NameFilter<<"*.csv";
    //if you reselect the dataset,the previous record should be cleared
    if(!FileNames.isEmpty())
        FileNames.clear();
    if(!FilePaths.isEmpty())
        FilePaths.clear();

    FileNames<<dir.entryList(NameFilter);
    QFileInfoList info_list=dir.entryInfoList(NameFilter);
    QListIterator<QFileInfo> i(info_list);
    QFileInfo info;
    while(i.hasNext()){
        info=i.next();
        FilePaths<<info.absoluteFilePath();
    }

}

void MainWindow::finddel(){
    path=FilePaths[0];
    QFile file(path);
    if(!file.open(QFile::ReadOnly|QIODevice::Text)){
        qDebug()<<"Open file failed!"<<"\n";
        EM.setWindowTitle(QString("Open sample file failed!"));
        EM.showMessage("There are some problems that we can't open this file!");
        showErrorMessage();
        ui->stackedWidget->setCurrentIndex(1);

    }
    QTextStream stream(&file);
    QString firstline=stream.readLine();
    if(firstline.contains(";"))
        del=";";
    else if(firstline.contains(("\t")))
        del="\t";
    else if(firstline.contains(","))
        del=",";
    file.close();
}

//check boxes in the data filter part
void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1==Qt::Checked){
        InterestedData[0]=true;
    }
    else{
        InterestedData[0]=false;
    }
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1==Qt::Checked){
        InterestedData[1]=true;
    }
    else{
        InterestedData[1]=false;
    }
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1==Qt::Checked){
        InterestedData[2]=true;
    }
    else{
        InterestedData[2]=false;
    }
}

void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    if(arg1==Qt::Checked){
        InterestedData[3]=true;
    }
    else{
        InterestedData[3]=false;
    }
}

void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
    if(arg1==Qt::Checked){
        InterestedData[4]=true;
    }
    else{
        InterestedData[4]=false;
    }
}

void MainWindow::on_checkBox_6_stateChanged(int arg1)
{
    if(arg1==Qt::Checked){
        InterestedData[5]=true;
    }
    else{
        InterestedData[5]=false;
    }
}

void MainWindow::on_checkBox_7_stateChanged(int arg1)
{
    if(arg1==Qt::Checked){
        InterestedData[6]=true;
    }
    else{
        InterestedData[6]=false;
    }
}

//determine the choice of the data filter
void MainWindow::on_buttonBox_accepted()
{
    for(int i=0;i<7;++i)
    DataSelected[i]=InterestedData[i];
}

void MainWindow::on_buttonBox_rejected()
{
    if(DataSelected[0]==true)
        ui->checkBox->setCheckState(Qt::Checked);
    else ui->checkBox->setCheckState(Qt::Unchecked);
    if(DataSelected[1]==true)
        ui->checkBox_2->setCheckState(Qt::Checked);
    else ui->checkBox_2->setCheckState(Qt::Unchecked);
    if(DataSelected[2]==true)
        ui->checkBox_3->setCheckState(Qt::Checked);
    else ui->checkBox_3->setCheckState(Qt::Unchecked);
    if(DataSelected[3]==true)
        ui->checkBox_4->setCheckState(Qt::Checked);
    else ui->checkBox_4->setCheckState(Qt::Unchecked);
    if(DataSelected[4]==true)
        ui->checkBox_5->setCheckState(Qt::Checked);
    else ui->checkBox_5->setCheckState(Qt::Unchecked);
    if(DataSelected[5]==true)
        ui->checkBox_6->setCheckState(Qt::Checked);
    else ui->checkBox_6->setCheckState(Qt::Unchecked);
    if(DataSelected[6]==true)
        ui->checkBox_7->setCheckState(Qt::Checked);
    else ui->checkBox_7->setCheckState(Qt::Unchecked);
}

//determine the choice of the plot you want to see
void MainWindow::showErrorMessage(){
    EM.show();
}

void MainWindow::on_buttonBox_2_accepted()
{
    //if user didn't select the necessary data:Time,StationID,Status,this part can't work
    if(!(DataSelected[0]&&DataSelected[2]&&DataSelected[4])){
        EM.setWindowTitle(QString("Lack Necessary Message"));
        EM.showMessage("Please select the necessary data in DataFilter,it should includes:Time,StationID,Status ");
        showErrorMessage();
        ui->stackedWidget->setCurrentIndex(2);
        return;
    }

    //get parameters
    StationID=ui->lineEdit->text();
    if(StationID=="54"){
        EM.setWindowTitle(QString("Input Error"));
        EM.showMessage("There is some problem so we don't have the data of Station54");
        showErrorMessage();
        return;
    }
    Date=ui->dateEdit->date();
    QString DATE=Date.toString("yyyy-MM-dd");


    start_time=ui->start_time->time();
    endtime=ui->endtime->time();
    timestep=ui->timestep->time();


    if(start_time>endtime){
        EM.setWindowTitle(QString("Input Error"));
        EM.showMessage("Please check your starttime and endtime,make sure it is correct.");
        showErrorMessage();
        return;
    }

    //if the date changes,we need to read new files,if not,we don't do anything
    if(compareDate(DATE,PDate)==false){
    PDate=DATE;
    //clear the previous data before we read new
        for(int i=0;i<81;++i)
            if(!DTofEachStation[i].isEmpty())
                DTofEachStation[i].clear();

    //get files ranges correspond to the Date
    int SF=-1,EF=-1;                                          //start file position and end file position
    QString FN;
    QString DateofFile;
    QStringList FNL;
    bool flag1=false;
    bool flag2=false;
    for(int i=0;i<FileNames.size();++i){
       FN=FileNames[i];
       FNL=FN.split("_");
       DateofFile=FNL[1];                                   //because the format of the filename is: record_2019-01-07_part00.csv
       flag1=compareDate(DATE,DateofFile);
       //find the start point
       if(flag1==true&&flag2==false){
           SF=i;
           flag2=true;
       }
       //find the end point
       if(flag1==false&&flag2==true){
           EF=i;
           break;
       }
    }
    if(SF==-1||EF==-1){
        EM.setWindowTitle(QString("Input Error"));
        EM.showMessage("Provided dataset didn't include the data of the Date you input!");
        showErrorMessage();
        return;
    }

    //read data of the same date
    QFile file;
    QString tt;
    QStringList tmp;
    DT dt;
    int count=0;
    QString line=0;

    for(int i=SF;i<EF;++i){
        path=FilePaths[i];
        file.setFileName(path);
        if(!file.open(QFile::ReadOnly|QIODevice::Text)){
            qDebug()<<"Open"<<path<<" file failed!"<<"\n";
            EM.setWindowTitle(QString("Open file failed!"));
            EM.showMessage("There are some problems that we can't open this file!");
            showErrorMessage();
            ui->stackedWidget->setCurrentIndex(1);
        }
        QTextStream stream(&file);
        while(!stream.atEnd()){
            tt=stream.readLine();
            if(count==0){
                count++;
                continue;
            }               //skip the first line
            tmp=tt.split(del);
            dt.DAT=tmp[0];
            dt.ID=tmp[2].toInt();
            dt.state=tmp[4].toInt();
            DTofEachStation[dt.ID].push_back(dt);
            //if user select the lineID data in the datafilter
            if(InterestedData[1]==true){
                line=tmp[1];
                if(line=="A"){
                    lineA[dt.ID]=1;
                }
                else if(line=="B"){
                    lineB[dt.ID]=1;
                }
                else if(line=="C"){
                    lineC[dt.ID]=1;
                }
            }

        }
        count=0;
        file.close();
    }

    }
   formPlot();

}

bool MainWindow::compareDate(QString &a, QString &b){
    if(a==b)
        return true;
    else return false;
}

void MainWindow::formPlot(){
    QV_x.clear();
    QV_y_inflow.clear();
    QV_y_outflow.clear();
    double numofstime=0,numofetime=0,numoftstep=0,numofstep=0;
    QString StringofStart_time,StringofEndtime,Stringoftimestep,StringofReference;
    StringofStart_time=Date.toString("yyyy/MM/dd");
    StringofStart_time.append(' ');
    StringofStart_time.append(start_time.toString("hh:mm"));
    //qDebug()<<StringofStart_time<<'\n';
    StringofEndtime=Date.toString("yyyy/MM/dd");
    StringofEndtime.append(' ');
    StringofEndtime.append(endtime.toString("hh:mm"));
    //qDebug()<<StringofEndtime<<'\n';
    Stringoftimestep=Date.toString("yyyy/MM/dd");
    Stringoftimestep.append(' ');
    Stringoftimestep.append(timestep.toString("hh:mm"));
    //qDebug()<<Stringoftimestep<<'\n';
    StringofReference=Date.toString("yyyy/MM/dd");
    StringofReference.append(' ');
    StringofReference.append(referrence.toString("hh:mm"));
    //qDebug()<<StringofReference<<'\n';
    QDateTime a,b,c,d;
    a=QDateTime::fromString(StringofStart_time,"yyyy/MM/dd hh:mm");
    b=QDateTime::fromString(StringofEndtime,"yyyy/MM/dd hh:mm");
    c=QDateTime::fromString(Stringoftimestep,"yyyy/MM/dd hh:mm");
    d=QDateTime::fromString(StringofReference,"yyyy/MM/dd hh:mm");
    numofstime=a.toTime_t();
    numofetime=b.toTime_t();
    numoftstep=c.toTime_t();
    numofstep=d.toTime_t();
    numofstep=numoftstep-numofstep;
    //qDebug()<<numofstep<<'\n';
    while(numofstime<numofetime){
        QV_x.push_back(numofstime);
        numofstime+=numofstep;
    }
    //QV_x.push_back(numofetime);
    numofstime=a.toTime_t();
    //qDebug()<<QV_x.size()<<'\t';

    for(int i=0;i<QV_x.size();++i){
        QV_y_inflow.push_back(0);
        QV_y_outflow.push_back(0);
    }
    QStringList toollist;
    QString t;
    QString DEL=" ";
    QDateTime time1;
    double tmptime=0;
    int count=0;
    for(int i=0;i<DTofEachStation[StationID.toInt()].size();++i){
        t=DTofEachStation[StationID.toInt()][i].DAT;
        time1=QDateTime::fromString(t,"yyyy-MM-dd hh:mm:ss");
        tmptime=time1.toTime_t();
        if(tmptime<numofstime||tmptime>numofetime)
            continue;
        for(count=0;numofstime+(count+1)*numofstep<numofetime;++count){
            if(tmptime<numofstime+(count+1)*numofstep){
                if(DTofEachStation[StationID.toInt()][i].state==1){
                    QV_y_inflow[count]++;
                    break;
                }
                else{
                    QV_y_outflow[count]++;
                    break;
                }
            }
        }
        if(count==QV_x.size()-1){
            if(DTofEachStation[StationID.toInt()][i].state==1){
                QV_y_inflow[count]++;
            }
            else
                QV_y_outflow[count]++;
        }
    }
    double max=0;
    for(int i=0;i<QV_y_inflow.size();++i){
        if(QV_y_inflow[i]>max){
            max=QV_y_inflow[i];
        }
        if(QV_y_outflow[i]>max)
            max=QV_y_outflow[i];
    }

    QString GraphTitle;
    QCPGraphData GDATA1,GDATA2;
    QGData_inflow.clear();
    QGData_outflow.clear();
    for(int i=0;i<QV_x.size();++i){
        GDATA1.key=QV_x[i];
        GDATA1.value=QV_y_inflow[i];
        GDATA2.key=QV_x[i];
        GDATA2.value=QV_y_outflow[i];
        QGData_inflow.push_back(GDATA1);
        QGData_outflow.push_back(GDATA2);
    }

    //When only a few data points are available, use Interpolation,add some points to smooth the line.

    if(QV_x.size()<6){
        double ITx=0;
        double ITy=0;
        InterpolateData_x.clear();
        InterpolateData_y_inflow.clear();
        InterpolateData_y_outflow.clear();
        for(int i=1;i<QV_x.size();++i){
            ITx=(QV_x[i]+QV_x[i-1])/2;
            InterpolateData_x.push_back(ITx);
        }
        //Train the inflow data
        InterpolateData.setTB1(QV_x,QV_y_inflow);
        for(int i=0;i<InterpolateData_x.size();++i){
            ITy=InterpolateData.ApproximateValue(InterpolateData_x[i]);
            InterpolateData_y_inflow.push_back(ITy);
        }
        //Train the outflow data
        InterpolateData.setTB1(QV_x,QV_y_outflow);
        for(int i=0;i<InterpolateData_x.size();++i){
            ITy=InterpolateData.ApproximateValue(InterpolateData_x[i]);
            InterpolateData_y_outflow.push_back(ITy);
        }

        for(int i=0;i<InterpolateData_x.size();++i){
            GDATA1.key=InterpolateData_x[i];
            GDATA1.value=InterpolateData_y_inflow[i];
            GDATA2.key=InterpolateData_x[i];
            GDATA2.value=InterpolateData_y_outflow[i];
            QGData_inflow.push_back(GDATA1);
            QGData_outflow.push_back(GDATA2);
        }
    }

    ui->plot->clearGraphs();

    GraphTitle.append("Date:");
    GraphTitle.append(PDate);
    GraphTitle.append(" Station:");
    GraphTitle.append(StationID);
    GraphTitle.append(" Inflow and Outflow graph");

    if(flag==false){
    ui->plot->plotLayout()->insertRow(0);
    ui->plot->plotLayout()->addElement(0, 0,TextElement);
    flag=true;
    }
    TextElement->setText(GraphTitle);

    ui->plot->addGraph();
    ui->plot->graph(0)->data()->set(QGData_inflow);
    ui->plot->graph(0)->setPen(QPen(QColor(255, 100, 0)));
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    ui->plot->graph(0)->setName("Inflow trend");

    ui->plot->addGraph();
    ui->plot->graph(1)->data()->set(QGData_outflow);
    ui->plot->graph(1)->setPen(QPen(Qt::blue));
    ui->plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::blue, Qt::green, 7));
    ui->plot->graph(1)->setName("Outflow trend");

    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    ui->plot->xAxis->setTicker(dateTimeTicker);
    dateTimeTicker->setDateTimeFormat("hh:mm");
    ui->plot->xAxis->setRange(QV_x.first(),QV_x.last());
    ui->plot->yAxis->setRange(-0.1*max,max*1.1);
    ui->plot->xAxis->setLabel("Time");
    ui->plot->yAxis->setLabel("Number of people");
    ui->plot->replot();
    ui->plot->update();
}

//pushbutton in the init page about adjacency select
void MainWindow::on_pushButton_3_clicked()
{
    QFileDialog Dialog;
    AdjacencyDirctory=Dialog.getOpenFileName(0,"Select Adjacency","D:");
    QFile file(AdjacencyDirctory);
    if(!file.open(QFile::ReadOnly|QIODevice::Text)){
        qDebug()<<"Open"<<AdjacencyDirctory<<" file failed!"<<"\n";
        EM.setWindowTitle(QString("Open adjacency file failed!"));
        EM.showMessage("There are some problems that we can't open this file!");
        showErrorMessage();
        ui->stackedWidget->setCurrentIndex(1);
    }
    QTextStream stream(&file);
    QString firstline=stream.readLine();
    if(firstline.contains(";"))
        del2=";";
    else if(firstline.contains(("\t")))
        del2="\t";
    else if(firstline.contains(","))
        del2=",";
    QString linedata;
    QStringList tmp;
    QString Aij;
    int i=0,j=0;
    while(!stream.atEnd()){
        linedata=stream.readLine();
        tmp=linedata.split(del2);
        for(i=1;i<tmp.size();++i)
            if(tmp[i].toInt()==1){
                AdjacencyArray[j][i-1]=1;                   //we assume the distance between each station is equal,so we set them to 1
            }
        j++;
    }
    //init the DistanceArray
    for(int i=0;i<81;++i){
        for(int j=0;j<81;++j){
            if(AdjacencyArray[i][j]==1){
            DistanceArray[i][j]=AdjacencyArray[i][j];
            PathArray[i][j]=j;
            }
        }
    }

    int TransferCost=0;                         //take transfer cost into considerarion,but it's a pity that we don't know all the line and their corresponding station
    int CostOfTwoStation=0;

    //Cal all pair shortest path(Using Floyd Algorithm,and I try to add the transfer parameters in it
    for(int tmp=0;tmp<81;++tmp)
        for(int Row=0;Row<81;++Row)
            for(int Col=0;Col<81;++Col){
                if(DistanceArray[Row][tmp]==INT_MAX||DistanceArray[tmp][Col]==INT_MAX){
                    continue;
                }
                else{

                    //if we have data we've mention about,I think we can plan more practical path,here is and example of using LineA/B/C data to do that
                    /*
                    //if Station[Row] Station[tmp] Station[Col] is adjacent in the plot
                    if(AdjacencyArray[Row][tmp]==1&&AdjacencyArray[tmp][Col]==1){
                        //if they belong to same line,that means we don't need to transfer
                        if((lineA[Row]==1&&lineA[Col]==1)||(lineB[Row]==1&&lineB[Col]==1)||(lineC[Row]==1&&lineC[Col]==1))
                            TransferCost=0;
                        //else means we need to transfer,because these two station didn't belong to the same line
                        else
                            TransferCost=1;
                    }*/
                    CostOfTwoStation=DistanceArray[Row][tmp]+DistanceArray[tmp][Col]+TransferCost;
                    if(DistanceArray[Row][Col]>CostOfTwoStation){
                        DistanceArray[Row][Col]=CostOfTwoStation;
                        PathArray[Row][Col]=tmp;
                    }
                }
            }

    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_PlanPath_clicked()
{

    QString STID,ETID;
    STID=ui->start_StationID->text();
    ETID=ui->EndStationID->text();
    StartStaionID=STID.toInt();
    EndStationID=ETID.toInt();
    if(StartStaionID<0||StartStaionID>80||EndStationID<0||EndStationID>80){
        EM.setWindowTitle(QString("Input Error"));
        EM.showMessage("Please check your StartstaionID and EndStationID,make sure it is correct.");
        showErrorMessage();
        return;
    }

    pathlength=0;
    PrintedPath.clear();
    ui->DisplayWindow->clear();

    //here is an example for the extra data we can use if we select this in the Filter!
    if(InterestedData[1]==true){
    QString A,B,C;
    A.append("LineA: ");
    B.append("LineB: ");
    C.append("LineC: ");

    for(int i=0;i<81;++i){
        if(lineA[i]==1){
            A.append(QString::number(i,10));
            A.append(" ");
        }
        if(lineB[i]==1){
            B.append(QString::number(i,10));
            B.append(" ");
        }
        if(lineC[i]==1){
            C.append(QString::number(i,10));
            C.append(" ");
        }
    }
    ui->DisplayWindow->addItem(A);
    ui->DisplayWindow->addItem(B);
    ui->DisplayWindow->addItem(C);
    }

    //print path
    PrintedPath.append("Time Minimum path:");
    qDebug()<<"Time Min Path:";
    PrintedPath.append(STID);
    qDebug()<<StartStaionID;
    qDebug()<<EndStationID;
    pathlength++;
    printPath(StartStaionID,EndStationID,PathArray);
    ui->DisplayWindow->addItem(PrintedPath);
}


void MainWindow::printPath(const int &start, const int &end, int **P){
    if(start==-1||end==-1)return;
    if(PathArray[start][end]==-1) return;

    if(PathArray[start][end]==end){
        qDebug()<<"-->";
        PrintedPath.append("-->");
        PrintedPath.append(QString::number(end,10));
        qDebug()<<end;
        pathlength++;
        if(pathlength>=10){
            ui->DisplayWindow->addItem(PrintedPath);
            PrintedPath.clear();
            pathlength=0;
            qDebug()<<'\n';

        }
    }
    else{
    printPath(start,PathArray[start][end],P);

    //take transfer cost into considerarion,but it's a pity that we don't know all the line and their corresponding station
    /*
    if(AdjacencyArray[start][PathArray[start][end]]==1&&AdjacencyArray[PathArray[start][end]][end]==1){
        if(!(lineA[start]==1&&lineA[end]==1)||(lineB[start]==1&&lineB[end]==1)||(lineC[start]==1&&lineC[end]==1)){
            QString transferline;
            QString tmp;
            if((lineA[PathArray[start][end]]==1&&lineA[end]==1))
                transferline="A";
            else if(lineB[PathArray[start][end]]==1&&lineB[end]==1)
                transferline="B";
            else if(lineC[PathArray[start][end]]==1&&lineC[end]==1){
                transferline="C";
            }
            tmp.append("Transfer to line");
            tmp.append(transferline);
            PrintedPath.append(tmp);
        }
    }
    */

    printPath(PathArray[start][end],end,P);
    }
}





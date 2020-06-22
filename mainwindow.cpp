#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->removeToolBar(ui->mainToolBar);
    this->statusBar()->setVisible(false);
    mainPalette = new QPalette;
    this->setWindowTitle("Memory Management Algorithms");
    mainPalette->setColor(QPalette::Active,QPalette::Window,Qt::white);
    this->setPalette(*mainPalette);
    segmentID = 0;
    InitUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUI()
{

    //init graph layout
    Graph = new Graphics(this);
    Graph->setStyleSheet("border:0px;");
    Graph->setVisible(false);
    graphicsLayout = new QHBoxLayout;
    graphicsLayout->addWidget(Graph);

    //init input layout
    inputLayout = new QHBoxLayout;
    InitFisrtPage();
    InitSecondPage();
    mainLayout = new QHBoxLayout;
    mainLayout->addItem(inputLayout);
    mainLayout->addItem(graphicsLayout);

    //adding main layout to central widget of window
    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
}

void MainWindow::InitFisrtPage()
{
    //title label
    firstPagetitle = new QLabel("First Please Enter Memory Size And Holes");
    QFont font("Volkhov",14,QFont::Bold,true);
    firstPagetitle->setFont(font);

    //spinboxes labels
    QFont font1("Volkhov",11,QFont::Light,true);
    memorySizeLabel = new QLabel("Memory Size :");
    memorySizeLabel->setFont(font1);
    holeAddressLabel = new QLabel("Hole Starting Address :");
    holeAddressLabel->setFont(font1);
    holeSizeLabel = new QLabel("Hole Size :");
    holeSizeLabel->setFont(font1);

    //spinboxes
    memorySize = new QSpinBox;
    memorySize->setSingleStep(100);
    memorySize->setRange(0,10000000);
    memorySize->setFont(font1);
    memorySize->setMinimumHeight(30);
    holeAddress = new QSpinBox;
    holeAddress->setSingleStep(100);
    holeAddress->setRange(0,10000000);
    holeAddress->setFont(font1);
    holeAddress->setMinimumHeight(30);
    holeSize = new QSpinBox;
    holeSize->setSingleStep(100);
    holeSize->setRange(0,10000000);
    holeSize->setFont(font1);
    holeSize->setMinimumHeight(30);

    //button
    addHoleButton = new QPushButton;
    addHoleButton->setText("Add Hole");
    addHoleButton->setFont(font1);
    addHoleButton->setMinimumHeight(30);
    next = new QPushButton;
    next->setText("Next");
    next->setFont(font1);
    next->setMinimumHeight(30);

    //adding to form layout
    firstInputPage = new QFormLayout;
    firstInputPage->setContentsMargins(10,10,10,10);
    firstInputPage->setSpacing(10);
    firstInputPage->addRow(firstPagetitle);
    firstInputPage->addRow(memorySizeLabel,memorySize);
    firstInputPage->addRow(holeAddressLabel,holeAddress);
    firstInputPage->addRow(holeSizeLabel,holeSize);
    firstInputPage->addRow(addHoleButton);
    firstInputPage->addRow(next);

    //add form lautout to input layout
    inputLayout->addItem(firstInputPage);

    //making signals for buttons
    QObject::connect(addHoleButton,SIGNAL(clicked()),this,SLOT(addHole()));
    QObject::connect(next,SIGNAL(clicked()),this,SLOT(nextPressed()));

}

void MainWindow::InitSecondPage()
{
    //title label
    secondPagetitle = new QLabel("Now You Can Enter Proccess With Allocating Algorithm");
    secondPagetitle->setVisible(false);
    QFont font("Volkhov",14,QFont::Bold,true);
    secondPagetitle->setFont(font);


    //spinboxes and combobox labels
    QFont font1("Volkhov",11,QFont::Light,true);
    processNumSegmentsLabel = new QLabel("Process Segments Number :");
    processNumSegmentsLabel->setVisible(false);
    processNumSegmentsLabel->setFont(font1);
    segmentNameLabel = new QLabel("Segment Name :");
    segmentNameLabel->setVisible(false);
    segmentNameLabel->setFont(font1);
    segmentSizeLabel = new QLabel("Segment Size :");
    segmentSizeLabel->setVisible(false);
    segmentSizeLabel->setFont(font1);
    algorithmLabel = new QLabel("Select Algorithm:");
    algorithmLabel->setVisible(false);
    algorithmLabel->setFont(font1);

    //spinboxes
    processSegmentsNumber = new QSpinBox;
    processSegmentsNumber->setSingleStep(1);
    processSegmentsNumber->setRange(0,10000000);
    processSegmentsNumber->setVisible(false);
    processSegmentsNumber->setMinimumHeight(35);
    processSegmentsNumber->setFont(font1);

    segmentSize = new QSpinBox;
    segmentSize->setSingleStep(100);
    segmentSize->setRange(0,10000000);
    segmentSize->setVisible(false);
    segmentSize->setMinimumHeight(35);
    segmentSize->setFont(font1);

    //buttons
    addSegmentButton = new QPushButton;
    addSegmentButton->setText("Add Segment");
    addSegmentButton->setVisible(false);
    addSegmentButton->setMinimumHeight(35);
    addSegmentButton->setFont(font1);
    addProccesButton = new QPushButton;
    addProccesButton->setText("Add Process");
    addProccesButton->setVisible(false);
    addProccesButton->setMinimumHeight(35);
    addProccesButton->setFont(font1);
    MemorySettingButton = new QPushButton;
    MemorySettingButton->setText("Memory Settings");
    MemorySettingButton->setVisible(false);
    MemorySettingButton->setMinimumHeight(35);
    MemorySettingButton->setFont(font1);

    //textEdit
    segmentName = new QLineEdit("");
    segmentName->setVisible(false);
    segmentName->setMinimumHeight(32);
    segmentName->setFont(font1);

    //combox
    algorithm = new QComboBox;
    algorithm->addItem("Best Fit");
    algorithm->addItem("First Fit");
    algorithm->addItem("Worst Fit");
    algorithm->setVisible(false);
    algorithm->setMinimumHeight(35);
    algorithm->setFont(font1);


    secondInputPage = new QFormLayout;
    secondInputPage->addRow(secondPagetitle);
    secondInputPage->addRow(processNumSegmentsLabel,processSegmentsNumber);
    secondInputPage->addRow(segmentNameLabel,segmentName);
    secondInputPage->addRow(segmentSizeLabel,segmentSize);
    secondInputPage->addRow(addSegmentButton);
    secondInputPage->addRow(algorithmLabel,algorithm);
    secondInputPage->addRow(addProccesButton);
    secondInputPage->addRow(MemorySettingButton);

    inputLayout->addItem(secondInputPage);
    //making signals for buttons
    QObject::connect(addSegmentButton,SIGNAL(clicked()),this,SLOT(addProcessSegments()));
    QObject::connect(addProccesButton,SIGNAL(clicked()),this,SLOT(addProcess()));
    QObject::connect(MemorySettingButton,SIGNAL(clicked()),this,SLOT(MemorySettings()));

}




void MainWindow::addHole()
{
    if(memorySize->value()<=0){
       QMessageBox::warning(this,"Set Memory Size","Please Enter Memory Size First");
    }
    else{
        if(holeSize->value() != 0 && holeAddress->value() <= memorySize->value()-1){
            if(checkMemory()){
                MemorySegment* addedHole = new MemorySegment("","",holeAddress->value(),holeSize->value(),segmentID,-1,false);
                MyMemory.push_back(addedHole);
                segmentID++;
                holeAddress->setValue(0);
                holeSize->setValue(0);
            }
        }
        else{
            if(holeSize->value() ==0)
                QMessageBox::warning(this,"Add Hole","Please Enter Hole Size");
            else if (holeAddress->value() >= memorySize->value()){
                QMessageBox::warning(this,"Address Out Of Range","Please Enter A Valid Address");
            }
        }
    }
}

bool MainWindow::checkMemory()
{
    bool checked = true;
    int totalHoleSize = 0;
    if(MyMemory.isEmpty()){
        if(holeAddress->value()>memorySize->value() || holeAddress->value()+holeSize->value()>memorySize->value()){
            QMessageBox::warning(this,"Hole Size Error","Hole Size Is Bigger Than Memory Size");
            checked = false;
        }
    }
    else{
        for(int i = 0; i<MyMemory.size();i++){
            totalHoleSize+=MyMemory[i]->segmentSize;
            if(totalHoleSize==memorySize->value()){
                QMessageBox::warning(this,"Memory Empty","Memory Totaly Contains Holes");
                checked = false;
                break;
            }
            if(holeAddress->value() >= MyMemory[i]->segmentStartAddress
                    && holeAddress->value()< MyMemory[i]->segmentStartAddress +MyMemory[i]->segmentSize){
                checked = false;
                QMessageBox::warning(this,"Hole Address Error","This Hole Starting Address Already Contain A Hole");
                break;
            }
            else if(holeAddress->value()+holeSize->value()> MyMemory[i]->segmentStartAddress &&
                    holeAddress->value()< MyMemory[i]->segmentStartAddress){
                checked = false;
                QMessageBox::warning(this,"Hole Size Error","Hole Size Is Very Big So It Entered Another Hole Space");
                break;
            }
            else if(holeAddress->value()+holeSize->value()>memorySize->value()){
                checked = false;
                QMessageBox::warning(this,"Hole Size Error","Hole Size Is Very Big It Can Not Be Put At That Address");
                break;
            }

        }

    }

    return checked;
}

void MainWindow::nextPressed()
{
    if(memorySize->value()>0){

        MemorySize = memorySize->value();
        if(MyMemory.isEmpty()){
            QMessageBox::information(this,"No Holes","No Holes Added So Memory Will Be A Reserved Memory");
        }

        //functions to adjust MyMemory to be drawn
        sortByAddress(MyMemory);
        addReservedSegments();
        sortByAddress(MyMemory);
        compactHoles();

        //to hide first page widgets
        for (int i = 0; i < firstInputPage->count(); ++i)
        {
          QWidget *widget = firstInputPage->itemAt(i)->widget();
          if (widget != nullptr)
          {
               widget->setVisible(false);
          }
        }

        // to show second page content
        for (int i = 0; i < secondInputPage->count(); ++i)
        {
          QWidget *widget = secondInputPage->itemAt(i)->widget();
          if (widget != nullptr)
          {
               widget->setVisible(true);
          }
        }

        //remove margin from first input page
        firstInputPage->setContentsMargins(0,0,0,0);
        firstInputPage->setSpacing(0);

        //to adjaust the margin of second page input
        secondInputPage->setContentsMargins(10,10,10,10);
        secondInputPage->setSpacing(50);

        // maximize window and show Graphics with Memory Drawn
        QWidget::showMaximized();
        Graph->drawMemory(MemorySize,MyMemory,&MyMemory);
        Graph->setVisible(true);


    }
    else{
        QMessageBox::warning(this,"Set Memory","Please Enter Memory Size");
    }


}

void MainWindow::sortByAddress(QVector<MemorySegment *> Memory)
{

        int min_idx;
        // One by one move boundary of unsorted subarray
        for (int i = 0; i < Memory.size()-1; i++)
        {
            // Find the minimum element in unsorted array
            min_idx = i;
            for (int j = i+1; j < Memory.size(); j++)
            if (Memory[j]->segmentStartAddress < Memory[min_idx]->segmentStartAddress)
                min_idx = j;

            // Swap the found minimum element with the first element
            swap(Memory[min_idx], Memory[i]);
        }
}

QVector<MemorySegment> MainWindow::sortBySize(QVector<MemorySegment> Holes)
{
    int min_idx;
    // One by one move boundary of unsorted subarray
    for (int i = 0; i < Holes.size()-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (int j = i+1; j < Holes.size(); j++)
        if (Holes[j].segmentSize < Holes[min_idx].segmentSize)
            min_idx = j;

        // Swap the found minimum element with the first element
        swap(&Holes[min_idx], &Holes[i]);
    }
    return Holes;
}

QVector<MemorySegment> MainWindow::sortBySizeDec(QVector<MemorySegment> Holes)
{
    int max_idx;
    // One by one move boundary of unsorted subarray
    for (int i = 0; i < Holes.size()-1; i++)
    {
        // Find the minimum element in unsorted array
        max_idx = i;
        for (int j = i+1; j < Holes.size(); j++)
        if (Holes[j].segmentSize > Holes[max_idx].segmentSize)
            max_idx = j;

        // Swap the found minimum element with the first element
        swap(&Holes[max_idx], &Holes[i]);
    }

    return Holes;
}

void MainWindow::swap(MemorySegment *segment1, MemorySegment *segment2)
{
    MemorySegment temp = *segment1;
    *segment1 = *segment2;
    *segment2 = temp;
}

void MainWindow::addReservedSegments()
{
    processID = 0;
    int MemoryHoleSize = MyMemory.size();
    if(MyMemory.isEmpty()){
        MemorySegment *MemoryReserved = new MemorySegment("Reserved Process","Reserved Segment",0,MemorySize,segmentID,processID,true);
        processID++;
        segmentID++;
        MyMemory.push_back(MemoryReserved);
    }
    else{
        for(int i=0;i<MemoryHoleSize;i++){
            //hole at begining of vector
            if(i==0){
                if(MyMemory[i]->segmentStartAddress !=0){
                    MemorySegment *MemoryReserved = new MemorySegment("Reserved Process","Reserved Segment",0,MyMemory[i]->segmentStartAddress,segmentID,processID,true);
                    processID++;
                    segmentID++;
                    MyMemory.push_back(MemoryReserved);
                }
                if(MemoryHoleSize ==1 && MyMemory[i]->segmentStartAddress+MyMemory[i]->segmentSize !=MemorySize){
                    MemorySegment *MemoryReserved = new MemorySegment("Reserved Process","Reserved Segment",MyMemory[i]->segmentStartAddress+MyMemory[i]->segmentSize,
                                                                      MemorySize-(MyMemory[i]->segmentStartAddress+MyMemory[i]->segmentSize),segmentID,processID,true);
                    processID++;
                    segmentID++;
                    MyMemory.push_back(MemoryReserved);
                }
            }
            //hole at the end
            else if(i==MemoryHoleSize-1 && MemoryHoleSize!=1){
                //if hole at end of MyMemory look after it
                if(MyMemory[i]->segmentStartAddress+MyMemory[i]->segmentSize !=MemorySize){
                    MemorySegment *MemoryReserved = new MemorySegment("Reserved Process","Reserved Segment",MyMemory[i]->segmentStartAddress+MyMemory[i]->segmentSize,
                                                                      MemorySize-(MyMemory[i]->segmentStartAddress+MyMemory[i]->segmentSize),segmentID,processID,true);
                    processID++;
                    segmentID++;
                    MyMemory.push_back(MemoryReserved);
                }
                //if hole at end of MyMemory look behind it
                if(MyMemory[i]->segmentStartAddress != MyMemory[i-1]->segmentStartAddress+MyMemory[i-1]->segmentSize ){
                    MemorySegment *MemoryReserved = new MemorySegment("Reserved Process","Reserved Segment",MyMemory[i-1]->segmentStartAddress+MyMemory[i-1]->segmentSize,
                                                                      MyMemory[i]->segmentStartAddress-(MyMemory[i-1]->segmentStartAddress+MyMemory[i-1]->segmentSize),segmentID,processID,true);
                    processID++;
                    segmentID++;
                    MyMemory.push_back(MemoryReserved);
                }
            }
            //hole at middle
            else{
                //if hole at end of MyMemory look behind it
                if( i!=0 && MyMemory[i]->segmentStartAddress != MyMemory[i-1]->segmentStartAddress+MyMemory[i-1]->segmentSize ){
                    MemorySegment *MemoryReserved = new MemorySegment("Reserved Process","Reserved Segment",MyMemory[i-1]->segmentStartAddress+MyMemory[i-1]->segmentSize,
                                                                      MyMemory[i]->segmentStartAddress-(MyMemory[i-1]->segmentStartAddress+MyMemory[i-1]->segmentSize),segmentID,processID,true);
                    processID++;
                    segmentID++;
                    MyMemory.push_back(MemoryReserved);
                }
            }
        }
    }


}

void MainWindow::compactHoles()
{
    QVector<MemorySegment *>::iterator it = MyMemory.begin();
    for(int i=0;i<MyMemory.size()-1;i++,it++){
        if(!MyMemory[i]->isProcces && !MyMemory[i+1]->isProcces){
            MyMemory[i]->segmentSize +=MyMemory[i+1]->segmentSize;
            MemorySegment *segment = MyMemory[i+1];
            QVector<MemorySegment*>::iterator eraseIt = it;
            MyMemory.erase(++eraseIt);
            delete segment;
            i--;
            it--;
        }
    }
}

void MainWindow::addProcess()
{
    if(processSegmentsNumber->value()==0){
        QMessageBox::warning(this,"Process Segments","Please Enter Process Segments First");
    }
    else if(processSegmentsNumber->value()==process.size()){
        tryAddingProcess();
    }
    else if(processSegmentsNumber->value()>process.size()){
        QMessageBox::warning(this,"Segments Number","Please Enter Enough Segments");
    }
    else if(processSegmentsNumber->value()<process.size()){
        while (processSegmentsNumber->value()!=process.size()) {
            process.pop_back();
        }
    }

}

void MainWindow::addProcessSegments()
{
    if(processSegmentsNumber->value() > 0){
        if(process.size() < processSegmentsNumber->value()){
            if(segmentName->text() !="" && segmentSize->value() >0){
                MemorySegment processSegment;
                processSegment.holeId=-1;
                processSegment.isProcces = true;
                processSegment.segmentName = segmentName->text();
                processSegment.segmentSize = segmentSize->value();
                processSegment.segmentID = segmentID;
                segmentID++;
                process.push_back(processSegment);
                segmentName->setText("");
                segmentSize->setValue(0);
            }
            else if(segmentName->text() ==""){
                QMessageBox::warning(this,"Segment Name","Please Enter Segment Name First");
            }
            else if(segmentSize->value() == 0){
                QMessageBox::warning(this,"Segment Size","Please Enter Segment Size First");
            }
        }
        else{
            QMessageBox::warning(this,"Process Segments","You Have Already Entered "+QString::number(processSegmentsNumber->value())+" Segments");
        }
    }
    else{
       QMessageBox::warning(this,"Process Segments Number","Please Enter Process Segments Number First");
    }
}

void MainWindow::tryAddingProcess()
{
    QVector<MemorySegment> Holes;
    bool canFit = true;
    int static processNameCounter = 1;

    for(int i=0;i<MyMemory.size();i++){
        if(!MyMemory[i]->isProcces)
            Holes.push_back(*MyMemory[i]);
    }
    if(algorithm->currentText()=="Best Fit"){
        Holes = sortBySize(Holes);

        for(int i=0;i<process.size();i++){
            for(int j=0;j<Holes.size();j++){
                if(process[i].segmentSize<=Holes[j].segmentSize)
                {
                    process[i].holeId = Holes[j].segmentID;
                    Holes[j].segmentSize -= process[i].segmentSize;
                    Holes=sortBySize(Holes);
                    break;
                }

            }
            if(process[i].holeId==-1){
                canFit = false;
                break;
            }
        }

        if(canFit){
            for(int i=0;i<process.size();i++){
                process[i].processID = processID;
                process[i].proccesName = "Process "+QString::number(processNameCounter);
                Graph->addProccesToHole(process[i].holeId,process[i]);
            }
            processID++;
            processNameCounter++;
            process.clear();
            processSegmentsNumber->setValue(0);
        }
        else{
            QMessageBox::warning(this,"Process Size","The Process You Have Entered Can Not Fit In Memory, Please Enter Another Process Or Deallocate Old Procesess");
            process.clear();
        }

    }
    else if(algorithm->currentText()=="First Fit"){

        for(int i=0;i<process.size();i++){
            for(int j=0;j<Holes.size();j++){
                if(process[i].segmentSize<=Holes[j].segmentSize)
                {
                    process[i].holeId = Holes[j].segmentID;
                    Holes[j].segmentSize -= process[i].segmentSize;
                    break;
                }

            }
            if(process[i].holeId==-1){
                canFit = false;
                break;
            }
        }

        if(canFit){
            for(int i=0;i<process.size();i++){
                process[i].processID = processID;
                process[i].proccesName = "Process "+QString::number(processNameCounter);
                Graph->addProccesToHole(process[i].holeId,process[i]);
            }
            processID++;
            processNameCounter++;
            process.clear();
            processSegmentsNumber->setValue(0);
        }
        else{
            QMessageBox::warning(this,"Process Size","The Process You Have Entered Can Not Fit In Memory, Please Enter Another Process Or Deallocate Old Procesess");
            process.clear();
        }

    }
    else if(algorithm->currentText()=="Worst Fit"){
        Holes = sortBySizeDec(Holes);

        for(int i=0;i<process.size();i++){
            for(int j=0;j<Holes.size();j++){
                if(process[i].segmentSize<=Holes[j].segmentSize)
                {
                    process[i].holeId = Holes[j].segmentID;
                    Holes[j].segmentSize -= process[i].segmentSize;
                    Holes=sortBySizeDec(Holes);
                    break;
                }

            }
            if(process[i].holeId==-1){
                canFit = false;
                break;
            }
        }

        if(canFit){
            for(int i=0;i<process.size();i++){
                process[i].processID = processID;
                process[i].proccesName = "Process "+QString::number(processNameCounter);
                Graph->addProccesToHole(process[i].holeId,process[i]);
            }
            processID++;
            processNameCounter++;
            process.clear();
            processSegmentsNumber->setValue(0);
        }
        else{
            QMessageBox::warning(this,"Process Size","The Process You Have Entered Can Not Fit In Memory, Please Enter Another Process Or Deallocate Old Procesess");
            process.clear();
        }

    }
}

void MainWindow::MemorySettings()
{
    settings = new MemoryConfig(&MyMemory,this);
    settings->setModal(true);
    QObject::connect(settings,SIGNAL(saved()),this,SLOT(reconstructMemory()));
    settings->exec();
}

void MainWindow::reconstructMemory()
{
        MemorySize = settings->MemorySize;
        sortByAddress(MyMemory);
        addReservedSegments();
        sortByAddress(MyMemory);
        compactHoles();
        Graph->destoryMemory();
        Graph->drawMemory(MemorySize,MyMemory,&MyMemory);
}





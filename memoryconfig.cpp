#include "memoryconfig.h"
#include "ui_memoryconfig.h"
#include <QMessageBox>


MemoryConfig::MemoryConfig(QVector<MemorySegment*> *Mymemory,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MemoryConfig)
{
    ui->setupUi(this);
    ui->setupUi(this);
    QPalette *mainPalette = new QPalette;
    this->setWindowTitle("Memory Settings");
    mainPalette->setColor(QPalette::Active,QPalette::Window,Qt::white);
    this->setPalette(*mainPalette);
    segmentID = 0;
    MyMemoryAddress = Mymemory;
    InitInterface();
}

MemoryConfig::~MemoryConfig()
{
    delete ui;
}


void MemoryConfig::InitInterface()
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
    save = new QPushButton;
    save->setText("Save");
    save->setFont(font1);
    save->setMinimumHeight(30);
    closeButton = new QPushButton;
    closeButton->setText("Close");
    closeButton->setFont(font1);
    closeButton->setMinimumHeight(30);


    //adding to form layout
    firstInputPage = new QFormLayout;
    firstInputPage->setContentsMargins(10,10,10,10);
    firstInputPage->setSpacing(10);
    firstInputPage->addRow(firstPagetitle);
    firstInputPage->addRow(memorySizeLabel,memorySize);
    firstInputPage->addRow(holeAddressLabel,holeAddress);
    firstInputPage->addRow(holeSizeLabel,holeSize);
    firstInputPage->addRow(addHoleButton);
    firstInputPage->addRow(save,closeButton);

    //add form lautout to input layout
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addItem(firstInputPage);
    this->setLayout(mainLayout);
    this->setWindowTitle("Memory Settings");


    //making signals for buttons
    QObject::connect(addHoleButton,SIGNAL(clicked()),this,SLOT(addHole()));
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(savePressed()));
    QObject::connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
}

void MemoryConfig::addHole()
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

void MemoryConfig::savePressed()
{
    if(memorySize->value()>0){

        if(MyMemory.isEmpty()){
            QMessageBox::information(this,"No Holes","No Holes Added So Memory Will Be A Reserved Memory");
        }
        updateMemory();
        MemorySize = memorySize->value();
        saved();
        close();
    }
    else{
        QMessageBox::warning(this,"Set Memory","Please Enter Memory Size");
    }

}

bool MemoryConfig::checkMemory()
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

void MemoryConfig::updateMemory()
{
    int MyMemorySize = MyMemoryAddress->size();
    for(int i=0;i<MyMemorySize;i++){
         MemorySegment *segment = MyMemoryAddress->first();
         MyMemoryAddress->pop_front();
         delete segment;
    }
    for(int i=0;i<MyMemory.size();i++){
        MemorySegment *segment = new MemorySegment(MyMemory[i]->proccesName,MyMemory[i]->segmentName,MyMemory[i]->segmentStartAddress,
                                                          MyMemory[i]->segmentSize,MyMemory[i]->segmentID,MyMemory[i]->processID,
                                                          MyMemory[i]->isProcces);
        MyMemoryAddress->push_back(segment);
    }
}



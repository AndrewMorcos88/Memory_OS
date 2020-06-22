#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QMessageBox>

//inputs and layouts
#include <QSpinBox>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QSpacerItem>
#include <QColor>
#include <QPalette>
#include <QLabel>


#include "graphicsmemorysegmnet.h"
#include "graphics.h"
#include "memorysegment.h"
#include "memoryconfig.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void InitUI();
    void InitFisrtPage();
    void InitSecondPage();
    void addHole();
    bool checkMemory();
    void nextPressed();
    void sortByAddress(QVector<MemorySegment*> MyMemory);
    QVector<MemorySegment> sortBySize(QVector<MemorySegment> Holes);
    QVector<MemorySegment> sortBySizeDec(QVector<MemorySegment> Holes);
    void swap(MemorySegment* segment1,MemorySegment* segment2);
    void addReservedSegments();
    void compactHoles();
    void addProcess();
    void addProcessSegments();
    void tryAddingProcess();
    void MemorySettings();
    void reconstructMemory();

private:

    Ui::MainWindow *ui;
    QWidget *centralWidget;
    Graphics *Graph;
    GraphicsMemorySegmnet *segment;
    QGraphicsScene *scene;
    //colors and pallete
    QPalette *mainPalette;

    //Inputs and there layout
    //buttons
    QPushButton *addHoleButton;
    QPushButton *next;
    QPushButton *addSegmentButton;
    QPushButton *addProccesButton;
    QPushButton *MemorySettingButton;
    //spin boxes
    QSpinBox *memorySize;
    QSpinBox *holeAddress;
    QSpinBox *holeSize;
    QSpinBox *processSegmentsNumber;
    QSpinBox *segmentSize;
    //layout
    QFormLayout *firstInputPage;
    QFormLayout *secondInputPage;
    QHBoxLayout *mainLayout;
    QHBoxLayout *inputLayout;
    QHBoxLayout *graphicsLayout;

    //label
    QLabel *firstPagetitle;
    QLabel *secondPagetitle;
    QLabel *memorySizeLabel;
    QLabel *holeAddressLabel;
    QLabel *holeSizeLabel;
    QLabel *processNumSegmentsLabel;
    QLabel *segmentNameLabel;
    QLabel *segmentSizeLabel;
    QLabel *algorithmLabel;
    //combobox
    QComboBox *algorithm;
    //line Edit
    QLineEdit *segmentName;

    QVector<MemorySegment*> MyMemory;
    int segmentID;
    int processID;
    QVector<MemorySegment> process;
    MemoryConfig *settings;
    int MemorySize;


};

#endif // MAINWINDOW_H

#ifndef MEMORYCONFIG_H
#define MEMORYCONFIG_H

#include <QDialog>
#include <QSpinBox>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include "memorysegment.h"

namespace Ui {
class MemoryConfig;
}

class MemoryConfig : public QDialog
{
    Q_OBJECT

public:
    explicit MemoryConfig(QVector<MemorySegment*> *MyMemory,QWidget *parent = nullptr);
    ~MemoryConfig();
    int MemorySize;


public slots:
    void InitInterface();
    void addHole();
    void savePressed();
    bool checkMemory();
    void updateMemory();

public: signals:
    void saved();


private:
    Ui::MemoryConfig *ui;
    //Inputs and there layout
    //buttons
    QPushButton *addHoleButton;
    QPushButton *closeButton;
    QPushButton *save;

    //spin boxes
    QSpinBox *memorySize;
    QSpinBox *holeAddress;
    QSpinBox *holeSize;
    //layout
    QFormLayout *firstInputPage;
    QHBoxLayout *mainLayout;
    //label
    QLabel *firstPagetitle;
    QLabel *memorySizeLabel;
    QLabel *holeAddressLabel;
    QLabel *holeSizeLabel;

    QVector<MemorySegment*> MyMemory;
    int segmentID;
    QVector<MemorySegment*> *MyMemoryAddress;
};

#endif // MEMORYCONFIG_H

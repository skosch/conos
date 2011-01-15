/****************************************************************************
** Form interface generated from reading ui file 'kpk2cmdwidgetbase.ui'
**
** Created: Tue Jan 11 10:22:39 2011
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef KPK2CMDWIDGETBASE_H
#define KPK2CMDWIDGETBASE_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QComboBox;
class QLabel;
class QFrame;
class QPushButton;
class QCheckBox;

class kpk2cmdWidgetBase : public QWidget
{
    Q_OBJECT

public:
    kpk2cmdWidgetBase( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~kpk2cmdWidgetBase();

    QComboBox* familyCombo;
    QLabel* pixmapLabel2;
    QFrame* frame3;
    QPushButton* stopBtn;
    QPushButton* readChipBtn;
    QCheckBox* preserveEEDataChkbox;
    QPushButton* programChipBtn;
    QPushButton* runBtn;
    QCheckBox* programMemoryChkbox;
    QPushButton* eraseChipBtn;
    QFrame* line1_2_2;
    QCheckBox* idMemoryChkbox;
    QPushButton* verifyChipBtn;
    QCheckBox* configurationMemoryChkbox;
    QCheckBox* eepromChkbox;
    QPushButton* blankCheckBtn;
    QFrame* line1_2;
    QFrame* frame6;
    QLabel* statusLine;
    QLabel* textLabel2;
    QLabel* busyImage;
    QLabel* textLabel1;
    QComboBox* partCombo;

public slots:
    virtual void familyComboBox(int index);
    virtual void partComboBox(int index);
    virtual void readChipButton();
    virtual void programChipButton();
    virtual void eraseChipButton();
    virtual void blankCheckButton();
    virtual void runButton();
    virtual void stopButton();
    virtual void programMemoryCheckbox(bool state);
    virtual void eepromCheckBox(bool state);
    virtual void idMemoryCheckbox(bool state);
    virtual void configurationMemoryCheckbox(bool state);
    virtual void preserveEEDataCheckbox(bool state);
    virtual void verifyChipButton();

protected:

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;
    QPixmap image4;

};

#endif // KPK2CMDWIDGETBASE_H

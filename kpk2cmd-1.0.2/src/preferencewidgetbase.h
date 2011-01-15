/****************************************************************************
** Form interface generated from reading ui file 'preferencewidgetbase.ui'
**
** Created: Tue Jan 11 10:22:39 2011
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef PREFERENCESWIDGETBASE_H
#define PREFERENCESWIDGETBASE_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QLabel;
class QCheckBox;
class QPushButton;

class preferenceswidgetbase : public QDialog
{
    Q_OBJECT

public:
    preferenceswidgetbase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~preferenceswidgetbase();

    QFrame* frame6_2;
    QLabel* textLabel1_2;
    QCheckBox* checkBox7_2;
    QCheckBox* haltMicroChkbox;
    QCheckBox* restoreLastMicroChkbox;
    QFrame* frame6;
    QLabel* textLabel1;
    QCheckBox* dashArrChkbox;
    QCheckBox* dashTeeChkbox;
    QFrame* frame6_2_2;
    QLabel* textLabel1_2_2;
    QCheckBox* programmingVerifyChkbox;
    QCheckBox* programmingEraseChkbox;
    QPushButton* cancelBtn;
    QPushButton* saveBtn;

public slots:
    virtual void cancelButton();
    virtual void saveButton();
    virtual void dashTeeCheckbox(bool check);
    virtual void dashArrCheckBox(bool check);
    virtual void restoreLastMicroCheckbox(bool check);
    virtual void haltMicroCheckbox(bool check);
    virtual void programmingEraseCheckbox(bool check);
    virtual void programmingVerifyCheckbox(bool check);

protected:

protected slots:
    virtual void languageChange();

};

#endif // PREFERENCESWIDGETBASE_H

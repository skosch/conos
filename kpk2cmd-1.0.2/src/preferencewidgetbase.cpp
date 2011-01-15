/****************************************************************************
** Form implementation generated from reading ui file 'preferencewidgetbase.ui'
**
** Created: Tue Jan 11 10:22:43 2011
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "preferencewidgetbase.h"

#include <qvariant.h>
#include <qframe.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a preferenceswidgetbase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
preferenceswidgetbase::preferenceswidgetbase( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "preferenceswidgetbase" );
    setMinimumSize( QSize( 360, 360 ) );
    setMaximumSize( QSize( 360, 360 ) );
    setPaletteBackgroundColor( QColor( 209, 210, 212 ) );

    frame6_2 = new QFrame( this, "frame6_2" );
    frame6_2->setEnabled( TRUE );
    frame6_2->setGeometry( QRect( 10, 20, 340, 100 ) );
    frame6_2->setPaletteBackgroundColor( QColor( 255, 247, 244 ) );
    frame6_2->setFrameShape( QFrame::StyledPanel );
    frame6_2->setFrameShadow( QFrame::Raised );

    textLabel1_2 = new QLabel( frame6_2, "textLabel1_2" );
    textLabel1_2->setEnabled( TRUE );
    textLabel1_2->setGeometry( QRect( 10, 10, 140, 16 ) );

    checkBox7_2 = new QCheckBox( frame6_2, "checkBox7_2" );
    checkBox7_2->setEnabled( FALSE );
    checkBox7_2->setGeometry( QRect( 50, 70, 280, 21 ) );

    haltMicroChkbox = new QCheckBox( frame6_2, "haltMicroChkbox" );
    haltMicroChkbox->setEnabled( TRUE );
    haltMicroChkbox->setGeometry( QRect( 50, 50, 260, 21 ) );

    restoreLastMicroChkbox = new QCheckBox( frame6_2, "restoreLastMicroChkbox" );
    restoreLastMicroChkbox->setEnabled( TRUE );
    restoreLastMicroChkbox->setGeometry( QRect( 30, 30, 260, 21 ) );

    frame6 = new QFrame( this, "frame6" );
    frame6->setGeometry( QRect( 10, 130, 340, 80 ) );
    frame6->setPaletteBackgroundColor( QColor( 255, 247, 244 ) );
    frame6->setFrameShape( QFrame::StyledPanel );
    frame6->setFrameShadow( QFrame::Raised );

    textLabel1 = new QLabel( frame6, "textLabel1" );
    textLabel1->setGeometry( QRect( 10, 10, 140, 16 ) );

    dashArrChkbox = new QCheckBox( frame6, "dashArrChkbox" );
    dashArrChkbox->setGeometry( QRect( 30, 50, 201, 21 ) );

    dashTeeChkbox = new QCheckBox( frame6, "dashTeeChkbox" );
    dashTeeChkbox->setGeometry( QRect( 30, 30, 240, 21 ) );

    frame6_2_2 = new QFrame( this, "frame6_2_2" );
    frame6_2_2->setEnabled( TRUE );
    frame6_2_2->setGeometry( QRect( 10, 220, 340, 80 ) );
    frame6_2_2->setPaletteBackgroundColor( QColor( 255, 247, 244 ) );
    frame6_2_2->setFrameShape( QFrame::StyledPanel );
    frame6_2_2->setFrameShadow( QFrame::Raised );

    textLabel1_2_2 = new QLabel( frame6_2_2, "textLabel1_2_2" );
    textLabel1_2_2->setGeometry( QRect( 10, 10, 140, 16 ) );

    programmingVerifyChkbox = new QCheckBox( frame6_2_2, "programmingVerifyChkbox" );
    programmingVerifyChkbox->setGeometry( QRect( 30, 50, 290, 21 ) );

    programmingEraseChkbox = new QCheckBox( frame6_2_2, "programmingEraseChkbox" );
    programmingEraseChkbox->setGeometry( QRect( 30, 30, 250, 21 ) );

    cancelBtn = new QPushButton( this, "cancelBtn" );
    cancelBtn->setGeometry( QRect( 10, 320, 91, 30 ) );

    saveBtn = new QPushButton( this, "saveBtn" );
    saveBtn->setGeometry( QRect( 270, 320, 81, 31 ) );
    languageChange();
    resize( QSize(360, 360).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( cancelBtn, SIGNAL( clicked() ), this, SLOT( cancelButton() ) );
    connect( saveBtn, SIGNAL( pressed() ), this, SLOT( saveButton() ) );
    connect( dashArrChkbox, SIGNAL( toggled(bool) ), this, SLOT( dashArrCheckBox(bool) ) );
    connect( dashTeeChkbox, SIGNAL( toggled(bool) ), this, SLOT( dashTeeCheckbox(bool) ) );
    connect( restoreLastMicroChkbox, SIGNAL( toggled(bool) ), this, SLOT( restoreLastMicroCheckbox(bool) ) );
    connect( haltMicroChkbox, SIGNAL( toggled(bool) ), this, SLOT( haltMicroCheckbox(bool) ) );
    connect( programmingEraseChkbox, SIGNAL( toggled(bool) ), this, SLOT( programmingEraseCheckbox(bool) ) );
    connect( programmingVerifyChkbox, SIGNAL( toggled(bool) ), this, SLOT( programmingVerifyCheckbox(bool) ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
preferenceswidgetbase::~preferenceswidgetbase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void preferenceswidgetbase::languageChange()
{
    setCaption( tr( "Preferences" ) );
    textLabel1_2->setText( tr( "On Startup perform:" ) );
    checkBox7_2->setText( tr( "&Auto-find microprocessor (EXPERIMENTAL)" ) );
    checkBox7_2->setAccel( QKeySequence( tr( "Alt+A" ) ) );
    haltMicroChkbox->setText( tr( "Halt microprocessor (E&XPERIMENTAL)" ) );
    haltMicroChkbox->setAccel( QKeySequence( tr( "Alt+X" ) ) );
    restoreLastMicroChkbox->setText( tr( "Restore Last Selected Microprocessor" ) );
    restoreLastMicroChkbox->setAccel( QKeySequence( QString::null ) );
    textLabel1->setText( tr( "When \"Running\" use:" ) );
    dashArrChkbox->setText( tr( "-R (Deassert /MCLR)" ) );
    dashArrChkbox->setAccel( QKeySequence( QString::null ) );
    dashTeeChkbox->setText( tr( "-T (Power Target after operations)" ) );
    dashTeeChkbox->setAccel( QKeySequence( QString::null ) );
    textLabel1_2_2->setText( tr( "When programming:" ) );
    programmingVerifyChkbox->setText( tr( "Automatically perform verify operation" ) );
    programmingVerifyChkbox->setAccel( QKeySequence( QString::null ) );
    programmingEraseChkbox->setText( tr( "Automaticall&y erase microprocessor" ) );
    programmingEraseChkbox->setAccel( QKeySequence( tr( "Alt+Y" ) ) );
    cancelBtn->setText( tr( "Ca&ncel" ) );
    saveBtn->setText( tr( "Save" ) );
    saveBtn->setAccel( QKeySequence( QString::null ) );
}

void preferenceswidgetbase::cancelButton()
{
    qWarning( "preferenceswidgetbase::cancelButton(): Not implemented yet" );
}

void preferenceswidgetbase::saveButton()
{
    qWarning( "preferenceswidgetbase::saveButton(): Not implemented yet" );
}

void preferenceswidgetbase::dashTeeCheckbox(bool)
{
    qWarning( "preferenceswidgetbase::dashTeeCheckbox(bool): Not implemented yet" );
}

void preferenceswidgetbase::dashArrCheckBox(bool)
{
    qWarning( "preferenceswidgetbase::dashArrCheckBox(bool): Not implemented yet" );
}

void preferenceswidgetbase::restoreLastMicroCheckbox(bool)
{
    qWarning( "preferenceswidgetbase::restoreLastMicroCheckbox(bool): Not implemented yet" );
}

void preferenceswidgetbase::haltMicroCheckbox(bool)
{
    qWarning( "preferenceswidgetbase::haltMicroCheckbox(bool): Not implemented yet" );
}

void preferenceswidgetbase::programmingEraseCheckbox(bool)
{
    qWarning( "preferenceswidgetbase::programmingEraseCheckbox(bool): Not implemented yet" );
}

void preferenceswidgetbase::programmingVerifyCheckbox(bool)
{
    qWarning( "preferenceswidgetbase::programmingVerifyCheckbox(bool): Not implemented yet" );
}


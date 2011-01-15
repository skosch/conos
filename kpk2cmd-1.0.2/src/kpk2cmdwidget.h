//----------
//
//				kpk2cmdwidget.h
//
// filename:	kpk2cmdwidget.h
//
// author:		lloyd sargent
//
// created:		March 25, 2008
//
// description:	This file is designed to
//
// notes:		none
//
// revisions:
//
// Copyright 2006 (c) Canna Software
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the
//   Free Software Foundation, Inc.,
//   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//



#ifndef _KPK2CMDWIDGET_H_
#define _KPK2CMDWIDGET_H_



//---------- pragmas



//---------- include files
#include "kpk2cmdwidgetbase.h"
#include "qprocess.h"
#include "qpushbutton.h"
#include "qmenubar.h"
#include "qsettings.h"
#include "preferencewidget.h"



//---------- enumerated data types
enum enumResultType
{
	eResultNotUsed,
 	eResultProgramChip,
  	eResultVerifyChip,
  	eResultReadChip,
	eResultBlankCheck,
 	eResultEraseChip,
  	eResultRunChip,
   	eResultStopChip
};

enum enumPartFamily
{
	ePartFamilyPic12,
	ePartFamilyPic14,
	ePartFamilyPic16,
	ePartFamilyPic18,
	ePartFamilyPic24,
	ePartFamilyPic30,
	ePartFamilyPic33,
};



//---------- typedefs



//---------- structs



//---------- definitions



//---------- external functions



//---------- external variables



//---------- global functions



//---------- global variables



//---------- local functions



//---------- local variables



//---------- classes
//----- this is our mime source factory (external declaration)

class csList;
class kpk2cmdWidget : public kpk2cmdWidgetBase
{
    Q_OBJECT

	QTimer *countdownTimer;
	QPixmap busyImageList[8];
	int busyImageIndex;
	
    csList *pic12;
    csList *pic14;
    csList *pic16;
    csList *pic18;
    csList *pic24;
    csList *pic30;
    csList *pic33;

	int curFamily;
	int curPart;
	QString curFilename;
	
	bool programMemory;
	bool eepromMemory;
	bool idMemory;
	bool configurationMemory;
	bool preserveEEData;

	QProcess *pk2cmdProcess;
	bool processRunningFlag;													// process is executing...
	bool processFlag;
	bool runningFlag;
	int resultType;
	
	QMenuBar *menubar;
	
	QSettings systemSettings;
	systemPreferencesItem systemPrefs;
			
public:
    kpk2cmdWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~kpk2cmdWidget();
    /*$PUBLIC_FUNCTIONS$*/

	void init(csList *inPic12, csList *inPic14, csList *inPic16,
		      csList *inPic18, csList *inPic24, csList *inPic30,
			  csList *inPic33);
	systemPreferencesItem currentPrefs();
	void updatePrefs(systemPreferencesItem newPrefs);
	void startProcess(const char *format, ...);
	void displayBusy();
	void displayNotBusy();
	void verifyChipUsingDefaultFile();

	
public slots:
    /*$PUBLIC_SLOTS$*/
    virtual void button_clicked();
    virtual void programChipButton();
    virtual void readChipButton();
    virtual void partComboBox(int index);
    virtual void familyComboBox(int familyNum);
	virtual void timerDone();
    virtual void preserveEEDataCheckbox(bool state);
    virtual void configurationMemoryCheckbox(bool state);
    virtual void idMemoryCheckbox(bool state);
    virtual void eepromCheckBox(bool state);
    virtual void programMemoryCheckbox(bool state);
    virtual void stopButton();
    virtual void runButton();
    virtual void blankCheckButton();
    virtual void eraseChipButton();
	virtual void pk2cmdStdout();
	virtual void pk2cmdFinished();
    virtual void verifyChipButton();

protected:
    /*$PROTECTED_FUNCTIONS$*/

protected slots:
    /*$PROTECTED_SLOTS$*/

};




#endif


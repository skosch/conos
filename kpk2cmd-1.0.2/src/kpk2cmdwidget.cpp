//----------
//
//				kpk2cmdwidget.cpp
//
// filename:	kpk2cmdwidget.cpp
//
// author:		lloyd sargent
//
// created:		March 25, 2008
//
// description:	This file is designed to
//
// notes:		This uses a hack in the src.pro file to run a script INSTEAD of uic so that we
//				can get to our embedded images.
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
 
 
 
//---------- pragmas
 
 
 
//---------- include files
#include <stdarg.h>

#include <qlabel.h>
#include <qcombobox.h>
#include <qimage.h>
#include <qtimer.h>
#include <qfiledialog.h>
#include <qprocess.h>
#include <qmime.h>
#include <qcheckbox.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qeventloop.h>

#include "kpk2cmdwidget.h"
#include "preferencewidget.h"
#include "csList.h"
#include "getfamilypart.h"



//---------- enumerated data types



//---------- typedefs



//---------- structs



//---------- definitions



//---------- external functions
extern QImage canna_findImage( const QString& name );							// this comes from hack.sh and hack.cpp
																				// see the source to src.pro - basically we
																				// substitute hack.sh for uic
																				// Yes, it is ugly. Yes, it works. Welcome
																				// to Linux.



//---------- external variables



//---------- global functions



//---------- global variables



//---------- local functions



//---------- local variables



//---------- classes
 



//-----
//
//				kpk2cmdWidget
//
// synopsis:	kpk2cmdWidget(parent, const char* name, WFlags fl);
//					QWidget* parent                 - 
//					const char* name                - 
//					WFlags fl                       - 
//
// description:	 is designed to
//
// errors:	
//
// returns:
//

kpk2cmdWidget::kpk2cmdWidget(QWidget* parent, const char* name, WFlags fl)
        : kpk2cmdWidgetBase(parent,name,fl)
{
	programMemory = FALSE;
	eepromMemory = FALSE;
	idMemory = FALSE;
	configurationMemory = FALSE;
	preserveEEData = FALSE;
	runningFlag = FALSE;
	processRunningFlag = FALSE;													// process is not running
}



//-----
//
//				~kpk2cmdWidget
//
// synopsis:	retval = ~kpk2cmdWidget();
//					 retval  - 
//
// description:	~kpk2cmdWidget is designed to
//
// errors:	
//
// returns:
//

kpk2cmdWidget::~kpk2cmdWidget()
{
	printf("exit\n");
}



//-----
//
//				init
//
// synopsis:	init(csList *inPic12, csList *inPic14, csList *inPic16, csList *inPic18, csList *inPic24, csList *inPic30, csList *inPic33);
//					csList *inPic12     - 
//					csList *inPic14     - 
//					csList *inPic16     - 
//					csList *inPic18     - 
//					csList *inPic24     - 
//					csList *inPic30     - 
//					csList *inPic33     - 
//
// description:	init is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::init(csList *inPic12, csList *inPic14, csList *inPic16, csList *inPic18, csList *inPic24, csList *inPic30, csList *inPic33)
{
    int index;
	csList *piclist;
	
    pic12 = inPic12;
    pic14 = inPic14;
    pic16 = inPic16;
    pic18 = inPic18;
    pic24 = inPic24;
    pic30 = inPic30;
    pic33 = inPic33;
		
    busyImageList[0] = canna_findImage(QString("spin8.png"));
    busyImageList[1] = canna_findImage(QString("spin7.png"));
    busyImageList[2] = canna_findImage(QString("spin6.png"));
    busyImageList[3] = canna_findImage(QString("spin5.png"));
    busyImageList[4] = canna_findImage(QString("spin4.png"));
    busyImageList[5] = canna_findImage(QString("spin3.png"));
    busyImageList[6] = canna_findImage(QString("spin2.png"));
    busyImageList[7] = canna_findImage(QString("spin1.png"));
													   													  
	busyImageIndex = 0;
	
	countdownTimer = new QTimer(this);
	connect(countdownTimer, SIGNAL(timeout()), this, SLOT(timerDone()));

	//----- fill out the families
	familyCombo->insertItem("PIC12", -1);
	familyCombo->insertItem("PIC14", -1);
	familyCombo->insertItem("PIC16", -1);
	familyCombo->insertItem("PIC18", -1);
	familyCombo->insertItem("PIC24", -1);
	familyCombo->insertItem("dsPIC30", -1);
	familyCombo->insertItem("dsPIC33", -1);
	
	//----- hide the busy image
	busyImage->hide();
	
	statusLine->setText("");
	
#if 0
		//----- create menubar
    menubar = new QMenuBar( this );
	
 	QPopupMenu *temppopup = new QPopupMenu( this );
    temppopup->insertItem("About",  this, SLOT(fileAbout()), 0);
	temppopup->insertItem("Preferences", this, SLOT(filePreferences()), 0);
    temppopup->insertItem("Quit", this, SLOT(fileQuit()), 0);
    menubar->insertItem( "&File", temppopup );
#endif
	//----- initialize system preferences
	systemSettings.setPath("cannasoftware.com", "kpk2cmd");
	
	systemPrefs.runningUseDashTee = systemSettings.readBoolEntry("/com.cannasoftware.kpk2cmd/preferences/running/dashTee", TRUE); 
	systemPrefs.runningUseDashArr = systemSettings.readBoolEntry("/com.cannasoftware.kpk2cmd/preferences/running/dashArr", TRUE);
	systemPrefs.startupRestoreLastMicro = systemSettings.readBoolEntry("/com.cannasoftware.kpk2cmd/preferences/startup/restoreLastMicro", FALSE);
	systemPrefs.startupHaltMicro = systemSettings.readBoolEntry("/com.cannasoftware.kpk2cmd/preferences/startup/haltMicro", FALSE);
	systemPrefs.picFamily = systemSettings.readNumEntry("/com.cannasoftware.kpk2cmd/preferences/picFamily", ePartFamilyPic12);
	QString tempPartName = systemSettings.readEntry("/com.cannasoftware.kpk2cmd/preferences/partName", "PIC12F510");
	strcpy(systemPrefs.partName, tempPartName.ascii());
	systemPrefs.programmingErase = systemSettings.readBoolEntry("/com.cannasoftware.kpk2cmd/preferences/programming/erase", FALSE);
	systemPrefs.programmingVerify = systemSettings.readBoolEntry("/com.cannasoftware.kpk2cmd/preferences/programming/verify", FALSE);
	
	//----- now, set up our defaults
	if (!systemPrefs.startupRestoreLastMicro)
	{
		systemPrefs.picFamily = ePartFamilyPic12;
		strcpy(systemPrefs.partName, "PIC12F510");
	}
		
	switch (systemPrefs.picFamily)
	{
		case ePartFamilyPic12:
			piclist = pic12;
			break;
		case ePartFamilyPic14:
			piclist = pic14;
			break;
		case ePartFamilyPic16:
			piclist = pic16;
			break;
		case ePartFamilyPic18:
			piclist = pic18;
			break;
		case ePartFamilyPic24:
			piclist = pic24;
			break;
		case ePartFamilyPic30:
			piclist = pic30;
			break;
		case ePartFamilyPic33:
			piclist = pic33;
			break;
	}
	
	//----- fill out the list...
	for (index = 0; index < piclist->count(); ++index)
	{
		picPartItem *part;
	
		part = (picPartItem *) piclist->get(index);								// get a pointer to the structure
		partCombo->insertItem(part->name, -1);
	}
	
	//----- indicate which part and family
	familyCombo->setCurrentItem(systemPrefs.picFamily);
	partCombo->setCurrentText(systemPrefs.partName);

	//----- if we have a part and we want to halt the processor, do so...
	if (systemPrefs.startupRestoreLastMicro && systemPrefs.startupHaltMicro)
	{
		runBtn->setEnabled(TRUE);
		stopBtn->setEnabled(FALSE);	
		stopButton();
	}
}



//-----
//
//				timerDone
//
// synopsis:	timerDone();
//
// description:	timerDone is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::timerDone()
{
	busyImage->setPixmap(busyImageList[busyImageIndex]);
	if (++busyImageIndex > 7)
		busyImageIndex = 0;
	countdownTimer->start(50, TRUE );
}



//-----
//
//				currentPrefs
//
// synopsis:	retval = currentPrefs();
//					systemPreferencesItem retval     - 
//
// description:	currentPrefs is designed to
//
// errors:	
//
// returns:
//

systemPreferencesItem kpk2cmdWidget::currentPrefs()
{
	return (systemPrefs);
}



//-----
//
//				updatePrefs
//
// synopsis:	updatePrefs(systemPreferencesItem newPrefs);
//					systemPreferencesItem newPrefs  - 
//
// description:	updatePrefs is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::updatePrefs(systemPreferencesItem newPrefs)
{
	systemPreferencesItem oldPrefs = systemPrefs;
	
	systemPrefs = newPrefs;
	systemSettings.writeEntry("/com.cannasoftware.kpk2cmd/preferences/startup/restoreLastMicro", systemPrefs.startupRestoreLastMicro);
	systemSettings.writeEntry("/com.cannasoftware.kpk2cmd/preferences/startup/haltMicro", systemPrefs.startupHaltMicro);
	systemSettings.writeEntry("/com.cannasoftware.kpk2cmd/preferences/running/dashTee", systemPrefs.runningUseDashTee); 
	systemSettings.writeEntry("/com.cannasoftware.kpk2cmd/preferences/running/dashArr", systemPrefs.runningUseDashArr);
	systemSettings.writeEntry("/com.cannasoftware.kpk2cmd/preferences/programming/erase", systemPrefs.programmingErase);
	systemSettings.writeEntry("/com.cannasoftware.kpk2cmd/preferences/programming/verify", systemPrefs.programmingVerify);
		
	systemPrefs.picFamily = oldPrefs.picFamily;								// make sure we don't lose the picFamily
	strcpy(systemPrefs.partName, oldPrefs.partName);						// or the part name
}



/*$SPECIALIZATION$*/
void kpk2cmdWidget::button_clicked()
{
}


//-----
//
//				partComboBox
//
// synopsis:	partComboBox(int index);
//					int index   - 
//
// description:	partComboBox is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::partComboBox(int index)
{
	csList *partlist;
	picPartItem *part;
	
	curPart = index;

	switch (systemPrefs.picFamily)
	{
		case ePartFamilyPic12:
			partlist = pic12;
			break;
		case ePartFamilyPic14:
			partlist = pic14;
			break;
		case ePartFamilyPic16:
			partlist = pic16;
			break;
		case ePartFamilyPic18:
			partlist = pic18;
			break;
		case ePartFamilyPic24:
			partlist = pic24;
			break;
		case ePartFamilyPic30:
			partlist = pic30;
			break;
		case ePartFamilyPic33:
			partlist = pic33;
			break;
	}

	part = (picPartItem *) partlist->get(curPart);								// get a pointer to the structure
	strcpy(systemPrefs.partName, part->name);									// get the part's name
	systemSettings.writeEntry("/com.cannasoftware.kpk2cmd/preferences/partName", systemPrefs.partName);
}



//-----
//
//				familyComboBox
//
// synopsis:	familyComboBox(int familyNum);
//					int familyNum   - 
//
// description:	familyComboBox is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::familyComboBox(int familyNum)
{
	csList *partlist;
	int index;

	switch (familyNum)
	{
		case ePartFamilyPic12:
			partlist = pic12;
			break;
		case ePartFamilyPic14:
			partlist = pic14;
			break;
		case ePartFamilyPic16:
			partlist = pic16;
			break;
		case ePartFamilyPic18:
			partlist = pic18;
			break;
		case ePartFamilyPic24:
			partlist = pic24;
			break;
		case ePartFamilyPic30:
			partlist = pic30;
			break;
		case ePartFamilyPic33:
			partlist = pic33;
			break;
	}
    systemPrefs.picFamily = familyNum;
	partCombo->clear();
	for (index = 0; index < partlist->count(); ++index)
	{
		picPartItem *part;

		part = (picPartItem *) partlist->get(index);							// get a pointer to the structure
		partCombo->insertItem(part->name, -1);
	}

	//----- indicate which part and family
	curPart = 0;
	familyCombo->setCurrentItem(systemPrefs.picFamily);
	partCombo->setCurrentItem(curPart);
	systemSettings.writeEntry("/com.cannasoftware.kpk2cmd/preferences/picFamily", systemPrefs.picFamily);
}



//-----
//
//				programChipButton
//
// synopsis:	programChipButton();
//
// description:	programChipButton is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::programChipButton()
{
	QFileDialog *filedialog;
	char memstr[20];
	char mempreservestr[20];
	
	filedialog = new QFileDialog(this, "Open", TRUE);
	filedialog->setDir("~");
	filedialog->setMode(QFileDialog::ExistingFile);
	filedialog->setCaption("Open hex file to program");
	filedialog->setFilter("Hex Files (*.hex)");

	//----- if programming some more, reuse the same file name
	if (!curFilename.isNull())
	{
		filedialog->setSelection(curFilename);
	}											   
	if (filedialog->exec() != QDialog::Accepted)
		return;
	
	curFilename = filedialog->selectedFile();									// get the file name

	//----- if we want to erase prior to programming, do so...
	//----- this is a cheesy way of avoiding more programming... 
	//----- a cleaner way would be to put the GUI in one thread and the process 
	//----- execution in another thread
	if (systemPrefs.programmingErase)
	{
		eraseChipButton();														// start up the erase process
		while (processRunningFlag)												// wait for it to finish while processing events
			(QApplication::eventLoop())->processEvents(0);
	}
	
	//----- create the process
	strcpy(memstr, " ");
	if (programMemory || eepromMemory || idMemory || configurationMemory)
	{
		strcpy(memstr, "-M");
		if (programMemory)
			strcat(memstr, "P");
		if (eepromMemory)
			strcat(memstr, "E");
		if (idMemory)
			strcat(memstr, "I");
		if (configurationMemory)
			strcat(memstr, "C");
	}
	
	strcpy(mempreservestr, " ");
	if (preserveEEData)
		strcpy(mempreservestr, "-Z");
	
	statusLine->setText("Programming chip...");
	resultType = eResultProgramChip;
	startProcess("/usr/bin/pk2cmd -P%s -F%s %s %s", systemPrefs.partName, curFilename.ascii(), memstr, mempreservestr);
	
	//----- see if we want to also verify it
	if (systemPrefs.programmingVerify)
	{
		while (processRunningFlag)												// wait for programming to finish while processing events
			(QApplication::eventLoop())->processEvents(0);
		verifyChipUsingDefaultFile();
	}
}



//-----
//
//				verifyChipButton
//
// synopsis:	verifyChipButton();
//
// description:	verifyChipButton is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::verifyChipButton()
{
	QFileDialog *filedialog;
	
	filedialog = new QFileDialog(this, "Open", TRUE);
	filedialog->setDir("/home");
	filedialog->setMode(QFileDialog::ExistingFile);
	filedialog->setCaption("Open hex file to program");
	filedialog->setFilter("Hex Files (*.hex)");

	//----- if verifying same file, reuse the same file name
	if (!curFilename.isNull())
	{
		filedialog->setSelection(curFilename);
	}											   
	if (filedialog->exec() != QDialog::Accepted)
		return;
	
	curFilename = filedialog->selectedFile();									// get the file name

	//----- now verify the chip
	verifyChipUsingDefaultFile();
}



//-----
//
//				verifyChipUsingDefaultFile
//
// synopsis:	verifyChipUsingDefaultFile();
//
// description:	verifyChipUsingDefaultFile is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::verifyChipUsingDefaultFile()
{
	char memstr[20];
	
	//----- create the process
	strcpy(memstr, " ");
	if (programMemory || eepromMemory || idMemory || configurationMemory)
	{
		strcpy(memstr, "-Y");
		if (programMemory)
			strcat(memstr, "P");
		if (eepromMemory)
			strcat(memstr, "E");
		if (idMemory)
			strcat(memstr, "I");
		if (configurationMemory)
			strcat(memstr, "C");
	}
	
	statusLine->setText("Verifying chip...");
	resultType = eResultVerifyChip;
	startProcess("/usr/local/bin/pk2cmd -P%s -F%s %s", systemPrefs.partName, curFilename.ascii(), memstr);
}


//-----
//
//				readChipButton
//
// synopsis:	readChipButton();
//
// description:	readChipButton is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::readChipButton()
{
	QString hexFilename;
	char memstr[20];
	QFileDialog *filedialog;
	
	//----- indicate where we want to store the file
	filedialog = new QFileDialog(this, "Save", TRUE);
	filedialog->setDir("/home");
	filedialog->setMode(QFileDialog::AnyFile);
	filedialog->setCaption("Store hex file as:");
	filedialog->setFilter("Hex Files (*.hex)");
	if (filedialog->exec() == QDialog::Rejected)
		return;
	
	curFilename = filedialog->selectedFile();									// get the file name

	//----- create the process
	strcpy(memstr, " ");
	if (programMemory || eepromMemory || idMemory || configurationMemory)
	{
		strcpy(memstr, "-G");
		if (programMemory)
			strcat(memstr, "P");
		if (eepromMemory)
			strcat(memstr, "E");
		if (idMemory)
			strcat(memstr, "I");
		if (configurationMemory)
			strcat(memstr, "C");
	}
	
	statusLine->setText("Reading chip...");
	resultType = eResultReadChip;
	startProcess("/usr/local/bin/pk2cmd -P%s -GF%s %s", systemPrefs.partName, curFilename.ascii(), memstr);
}



//-----
//
//				blankCheckButton
//
// synopsis:	blankCheckButton();
//
// description:	blankCheckButton is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::blankCheckButton()
{
	//----- create the process
	statusLine->setText("Blank Check...");
	resultType = eResultBlankCheck;
	startProcess("/usr/local/bin/pk2cmd -P%s -C", systemPrefs.partName);
}



//-----
//
//				eraseChipButton
//
// synopsis:	eraseChipButton();
//
// description:	eraseChipButton is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::eraseChipButton()
{
	//----- create the process
	statusLine->setText("Erasing Chip...");
	resultType = eResultEraseChip;
	startProcess("/usr/local/bin/pk2cmd -P%s -E", systemPrefs.partName);
}



//-----
//
//				stopButton
//
// synopsis:	stopButton();
//
// description:	stopButton is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::stopButton()
{
	//----- create the process
	statusLine->setText("Stopping microprocessor...");
	resultType = eResultStopChip;
	startProcess("/usr/local/bin/pk2cmd -P%s", systemPrefs.partName);
	runBtn->setEnabled(TRUE);
	stopBtn->setEnabled(FALSE);
	runningFlag = FALSE;
}



//-----
//
//				runButton
//
// synopsis:	runButton();
//
// description:	runButton is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::runButton()
{
	//----- create the process
	statusLine->setText("Starting microprocessor...");
	resultType = eResultRunChip;
	startProcess("/usr/local/bin/pk2cmd -P%s %s %s", 
				 systemPrefs.partName, 
	 			 systemPrefs.runningUseDashTee ? "-T" : "", 
	  			 systemPrefs.runningUseDashArr ? "-R" : "");
	runningFlag = TRUE;
}



//-----
//
//				programMemoryCheckbox
//
// synopsis:	programMemoryCheckbox(bool state);
//					bool state  - 
//
// description:	programMemoryCheckbox is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::programMemoryCheckbox(bool state)
{
	programMemory = state;
}



//-----
//
//				preserveEEDataCheckbox
//
// synopsis:	preserveEEDataCheckbox(bool state);
//					bool state  - 
//
// description:	preserveEEDataCheckbox is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::preserveEEDataCheckbox(bool state)
{
	preserveEEData = state;
}



//-----
//
//				configurationMemoryCheckbox
//
// synopsis:	configurationMemoryCheckbox(bool state);
//					bool state  - 
//
// description:	configurationMemoryCheckbox is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::configurationMemoryCheckbox(bool state)
{
	configurationMemory = state;
}



//-----
//
//				idMemoryCheckbox
//
// synopsis:	idMemoryCheckbox(bool state);
//					bool state  - 
//
// description:	idMemoryCheckbox is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::idMemoryCheckbox(bool state)
{
	idMemory = state;
}



//-----
//
//				eepromCheckBox
//
// synopsis:	eepromCheckBox(bool state);
//					bool state  - 
//
// description:	eepromCheckBox is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::eepromCheckBox(bool state)
{
	eepromMemory = state;
}



//-----
//
//				startProcess
//
// synopsis:	startProcess(const char *format, ...);
//					const char *format  - 
//					 ...                - 
//
// description:	startProcess is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::startProcess(const char *format, ...)
{
	char *str;
	char *token;
	char *holding;
    va_list variableargs;
	
    //----- first create the full line as it would be seen on the display
	str = new char[512];
	va_start(variableargs, format);
    vsnprintf(str, 512, format, variableargs);
    va_end(variableargs);

	//----- create the process...
	pk2cmdProcess = new QProcess(this);
	token = strtok_r(str, " ", &holding);

	while (token)
	{
		pk2cmdProcess->addArgument(token);
		token = strtok_r(NULL, " ", &holding);
	}
									   
#if 0
   QStringList list = pk2cmdProcess->arguments();
    QStringList::Iterator it = list.begin();
    while( it != list.end() )
	{
		printf("%s\n", ((QString) *it).ascii());
        ++it;
    }
#endif

	QStringList env;
	env += "PATH=/usr/share/pk2";
	
	connect(pk2cmdProcess, SIGNAL(readyReadStdout()), this, SLOT(pk2cmdStdout()));
	connect(pk2cmdProcess, SIGNAL(processExited()), this, SLOT(pk2cmdFinished()));
	processFlag = FALSE;														// we haven't seen anything of interest
    if (!pk2cmdProcess->start(&env))
	{
		displayNotBusy();														// indicate we are not busy
		statusLine->setText("Error: check that the right part is selected");
		delete pk2cmdProcess;
		return;
    }
	processRunningFlag = TRUE;													// process is running

	displayBusy();																// indicate we are busy

	delete str;
}


//-----
//
//				pk2cmdStdout
//
// synopsis:	pk2cmdStdout();
//
// description:	pk2cmdStdout is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::pk2cmdStdout()
{
	uint index;
	QByteArray data = pk2cmdProcess->readStdout();
	
	if (data.count() == 0)
		return;
	
	//----- skip anything that isn't useful to us...	
	for (index = 0; index < data.count(); ++index)
	{
		if ((data[index] >= 'a' && data[index] <= 'z') ||
			(data[index] >= 'A' && data[index] <= 'Z') ||
			(data[index] >= '0' && data[index] <= '9'))
		{
			processFlag = TRUE;
			break;
		}
	}
	if (index >= data.count())
		return;
									   		
	
	QString str(data);
	printf("%s\n", str.ascii());
	
	if (str.find("Could not find device") != -1)
	{
		statusLine->setText("Incorrect device was selected!");
		runningFlag = FALSE;
	}
	
	else if (str.find("No PICkit 2 found") != -1)
	{
		statusLine->setText("PICkit 2 was not found!");
		runningFlag = FALSE;
	}
	
	else
	{
		switch (resultType)
		{
			case eResultProgramChip:
				if (str.find("Program Succeeded") != -1)
					statusLine->setText("Device has been programmed");
				else
					statusLine->setText("Programming has failed!");
				break;
			case eResultReadChip:
				if (str.find("Read successfully") != -1)
					statusLine->setText("Device has been read");
				else
					statusLine->setText("Device read failed!");
				break;
			case eResultBlankCheck:
				if (str.find("Device is blank") != -1)
					statusLine->setText("Device is blank");
				else
					statusLine->setText("Device is not blank!");
				break;
			case eResultEraseChip:
				if (str.find("Operation Succeeded") != -1)
					statusLine->setText("Device has been erased");
				else
					statusLine->setText("Device erase failed!");
			case eResultVerifyChip:
				if (str.find("Operation Succeeded") != -1)
					statusLine->setText("Device has been verified");
				else
					statusLine->setText("Device verification failed!");
			case eResultRunChip:
				if (str.find("Operation Succeeded") != -1)
					statusLine->setText("Device is running.");
				else
					statusLine->setText("Device start failed!");
				break;				
			case eResultStopChip:
				if (str.find("Operation Succeeded") != -1)
					statusLine->setText("Device has been stopped");
				else
					statusLine->setText("Device reset failed!");
				break;
		}
	}
}



//-----
//
//				pk2cmdFinished
//
// synopsis:	pk2cmdFinished();
//
// description:	pk2cmdFinished is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::pk2cmdFinished()
{
	processRunningFlag = FALSE;													// process is not running
	displayNotBusy();
	delete pk2cmdProcess;
}



//-----
//
//				displayBusy
//
// synopsis:	displayBusy();
//
// description:	displayBusy is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::displayBusy()
{
	countdownTimer->start(50, TRUE);
	busyImage->show();
	
	programChipBtn->setEnabled(FALSE);
	verifyChipBtn->setEnabled(FALSE);
	readChipBtn->setEnabled(FALSE);
	eraseChipBtn->setEnabled(FALSE);
	blankCheckBtn->setEnabled(FALSE);
	runBtn->setEnabled(FALSE);
	stopBtn->setEnabled(FALSE);
	programMemoryChkbox->setEnabled(FALSE);
	eepromChkbox->setEnabled(FALSE);
	idMemoryChkbox->setEnabled(FALSE);
	configurationMemoryChkbox->setEnabled(FALSE);
	preserveEEDataChkbox->setEnabled(FALSE);
	familyCombo->setEnabled(FALSE);
	partCombo->setEnabled(FALSE);
}



//-----
//
//				displayNotBusy
//
// synopsis:	displayNotBusy();
//
// description:	displayNotBusy is designed to
//
// errors:	
//
// returns:
//

void kpk2cmdWidget::displayNotBusy()
{
	countdownTimer->stop();
	busyImage->hide();
	
	programChipBtn->setEnabled(TRUE);
	verifyChipBtn->setEnabled(TRUE);
	readChipBtn->setEnabled(TRUE);
	eraseChipBtn->setEnabled(TRUE);
	blankCheckBtn->setEnabled(TRUE);
	
	runBtn->setEnabled((runningFlag) ? FALSE : TRUE);
	stopBtn->setEnabled((runningFlag) ? TRUE : FALSE);
	
	programMemoryChkbox->setEnabled(TRUE);
	eepromChkbox->setEnabled(TRUE);
	idMemoryChkbox->setEnabled(TRUE);
	configurationMemoryChkbox->setEnabled(TRUE);
	preserveEEDataChkbox->setEnabled(TRUE);
	familyCombo->setEnabled(TRUE);
	partCombo->setEnabled(TRUE);
}













//----------
//
//				preferencewidget.cpp
//
// filename:	preferencewidget.cpp
//
// author:		lloyd sargent
//
// created:		March 28, 2008
//
// description:	This file is designed to
//
// notes:		none
//
// revisions:
//
// Copyright 2008 Canna Software. All rights reserved.
//
 
 
 
//---------- pragmas
 
 
 
//---------- include files
#include <qcheckbox.h>

#include "preferencewidget.h"


//---------- enumerated data types



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



//-----
//
//				preferencewidget
//
// synopsis:	preferencewidget(parent, const char *name);
//					QWidget *parent                     - 
//					const char *name                    - 
//
// description:	 is designed to
//
// errors:	
//
// returns:
//

preferencewidget::preferencewidget(QWidget *parent, const char *name)
    :preferenceswidgetbase(parent, name)
{
}



//-----
//
//				init 
//
// synopsis:	init (systemPreferencesItem inSystemPrefs);
//					systemPreferencesItem inSystemPrefs - 
//
// description:	init  is designed to
//
// errors:	
//
// returns:
//

void preferencewidget::init (systemPreferencesItem inSystemPrefs)
{
	systemPrefs = inSystemPrefs;												// copy the system prefs
	
	//----- do the startup flags
	haltMicroChkbox->setEnabled(FALSE);
	restoreLastMicroChkbox->setChecked(systemPrefs.startupRestoreLastMicro);	// see if we restore the last part or not
	if (systemPrefs.startupRestoreLastMicro)
	{
		haltMicroChkbox->setEnabled(TRUE);
		haltMicroChkbox->setChecked(systemPrefs.startupHaltMicro);				// if we don't restore the last part, we can't startup as halted
	}
	
	//----- do the running flags
	dashTeeChkbox->setChecked(systemPrefs.runningUseDashTee);					// set the default value
	dashArrChkbox->setChecked(systemPrefs.runningUseDashArr);					// set the default value
	
	//----- do the programming flags
	programmingEraseChkbox->setChecked(systemPrefs.programmingErase);
	programmingVerifyChkbox->setChecked(systemPrefs.programmingVerify);
}



//-----
//
//				getModifiedPrefs
//
// synopsis:	retval = getModifiedPrefs();
//					systemPreferencesItem retval     - 
//
// description:	getModifiedPrefs is designed to
//
// errors:	
//
// returns:
//

systemPreferencesItem preferencewidget::getModifiedPrefs()
{
	return (systemPrefs);
}



//-----
//
//				cancelButton
//
// synopsis:	cancelButton();
//
// description:	cancelButton is designed to
//
// errors:	
//
// returns:
//

void preferencewidget::cancelButton()
{
	done(QDialog::Rejected);
}



//-----
//
//				saveButton
//
// synopsis:	saveButton();
//
// description:	saveButton is designed to
//
// errors:	
//
// returns:
//

void preferencewidget::saveButton()
{
	done(QDialog::Accepted);
}



//-----
//
//				restoreLastMicroCheckbox
//
// synopsis:	restoreLastMicroCheckbox(bool check);
//					bool check  - 
//
// description:	restoreLastMicroCheckbox is designed to
//
// errors:	
//
// returns:
//

void preferencewidget::restoreLastMicroCheckbox(bool check)
{
	systemPrefs.startupRestoreLastMicro = check;
	if (systemPrefs.startupRestoreLastMicro)
		haltMicroChkbox->setEnabled(TRUE);
	else
		haltMicroChkbox->setEnabled(FALSE);

}



//-----
//
//				haltMicroCheckbox
//
// synopsis:	haltMicroCheckbox(bool check);
//					bool check  - 
//
// description:	haltMicroCheckbox is designed to
//
// errors:	
//
// returns:
//

void preferencewidget::haltMicroCheckbox(bool check)
{
	systemPrefs.startupHaltMicro = check;
}



//-----
//
//				programmingVerifyCheckbox
//
// synopsis:	programmingVerifyCheckbox(bool check);
//					bool check  - 
//
// description:	programmingVerifyCheckbox is designed to
//
// errors:	
//
// returns:
//

void preferencewidget::programmingVerifyCheckbox(bool check)
{
	systemPrefs.programmingVerify = check;
}



//-----
//
//				programmingEraseCheckbox
//
// synopsis:	programmingEraseCheckbox(bool check);
//					bool check  - 
//
// description:	programmingEraseCheckbox is designed to
//
// errors:	
//
// returns:
//

void preferencewidget::programmingEraseCheckbox(bool check)
{
	systemPrefs.programmingErase = check;
}



//-----
//
//				dashTeeCheckbox
//
// synopsis:	dashTeeCheckbox(bool check);
//					bool check  - 
//
// description:	dashTeeCheckbox is designed to
//
// errors:	
//
// returns:
//

void preferencewidget::dashTeeCheckbox(bool check)
{
	systemPrefs.runningUseDashTee = check;										// set the current value...
}



//-----
//
//				dashArrCheckBox
//
// synopsis:	dashArrCheckBox(bool check);
//					bool check  - 
//
// description:	dashArrCheckBox is designed to
//
// errors:	
//
// returns:
//

void preferencewidget::dashArrCheckBox(bool check)
{
	systemPrefs.runningUseDashArr = check;										// set the current value...
}










//----------
//
//				preferencewidget.h
//
// filename:	preferencewidget.h
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


#ifndef PREFERENCEWIDGET_H
#define PREFERENCEWIDGET_H



//---------- pragmas
#include "preferencewidgetbase.h"



//---------- include files



//---------- enumerated data types



//---------- typedefs
typedef struct systemPreferencesItem
{
	int picFamily;																// pic family (enumerated data type)
	char partName[32];															// part name
	bool startupRestoreLastMicro;												// on startup restore the last microprocessor
	bool startupHaltMicro;														// on startup halt the microprocessor
	bool programmingErase;														// erase prior to programmingErase
	bool programmingVerify;														// verify after programming
	bool runningUseDashTee;														// use the -T when running
	bool runningUseDashArr;														// use the -R when running
} systemPreferencesItem;



//---------- structs



//---------- definitions



//---------- external functions



//---------- external variables



//---------- global functions



//---------- global variables



//---------- local functions



//---------- local variables



//---------- classes
class preferencewidget: public preferenceswidgetbase 
{
Q_OBJECT
		
	systemPreferencesItem systemPrefs;											// system preferences
		
public:
    preferencewidget(QWidget *parent = 0, const char *name = 0);
	void init (systemPreferencesItem inSystemPrefs);
	systemPreferencesItem getModifiedPrefs();
	
public slots:
    virtual void saveButton();
    virtual void cancelButton();
    virtual void programmingVerifyCheckbox(bool check);
    virtual void programmingEraseCheckbox(bool check);
	virtual void dashTeeCheckbox(bool check);
	virtual void dashArrCheckBox(bool check);
    virtual void haltMicroCheckbox(bool check);
    virtual void restoreLastMicroCheckbox(bool check);
};

#endif

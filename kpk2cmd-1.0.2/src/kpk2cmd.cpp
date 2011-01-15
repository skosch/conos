//----------
//
//				kpk2cmd.cpp
//
// filename:	kpk2cmd.cpp
//
// author:		lloyd sargent
//
// created:		March 24, 2008
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
 
 
 
//---------- pragmas
 
 
 
//---------- include files
#include <qmainwindow.h>
#include <qapplication.h>
#include <qmessagebox.h>

#include "kpk2cmd.h"
#include "kpk2cmdwidget.h"

#include "getfamilypart.h"
#include "csList.h"



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
//				kpk2cmd
//
// synopsis:	retval = kpk2cmd();
//					 retval  - 
//
// description:	kpk2cmd is designed to
//
// errors:	
//
// returns:
//

kpk2cmd::kpk2cmd() : QMainWindow( 0, "kpk2cmd" )
{
	mainWindow = new kpk2cmdWidget( this );
	setCentralWidget(mainWindow);
	
	//----- create menubar
    menubar = new QMenuBar( this );
	
 	QPopupMenu *temppopup = new QPopupMenu( this );
    temppopup->insertItem("About",  this, SLOT(fileAbout()), 0);
	temppopup->insertItem("Preferences", this, SLOT(filePreferences()), 0);
    temppopup->insertItem("Quit", qApp, SLOT(quit()), 0);
    menubar->insertItem( "&File", temppopup );
	
	connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(justBeforeQuit()));
	
	getfamilypart *familypart = new getfamilypart();

    csList *pic12 = new csList();
    csList *pic14 = new csList();
    csList *pic16 = new csList();
    csList *pic18 = new csList();
    csList *pic24 = new csList();
    csList *pic30 = new csList();
    csList *pic33 = new csList();
	
	familypart->getparts(pic12, pic14, pic16, pic18, pic24, pic30, pic33);
	
	mainWindow->init(pic12, pic14, pic16, pic18, pic24, pic30, pic33);
	
	//----- center our window...	
	QRect geo = mainWindow->frameGeometry();
	int new_x = (QApplication::desktop()->width() - geo.width()) / 2;
	int new_y = (QApplication::desktop()->height() - geo.height()) / 2;
	move(new_x, new_y);
}



//-----
//
//				~kpk2cmd
//
// synopsis:	retval = ~kpk2cmd();
//					 retval  - 
//
// description:	~kpk2cmd is designed to
//
// errors:	
//
// returns:
//

kpk2cmd::~kpk2cmd()
{
	delete mainWindow;
}



//-----
//
//				fileAbout
//
// synopsis:	fileAbout();
//
// description:	fileAbout is designed to
//
// errors:	
//
// returns:
//

void kpk2cmd::fileAbout()
{
	QMessageBox::about(mainWindow, "About kpk2cmd...", "Version 1.02 - 'Why-Does-It-Seg-Fault?' Release\n\n"
					  							 "Kpk2cmd is a GUI front-end to the command line program\n"
					  							 "pk2cmd which is in itself a port of the command line\n"
												 "program from Microchip.\n\n"
												 "Please note, kpk2cmd is a fully original work of which\n"
												 "parts are copyright Jeff Post.\n\n"
					                             "The GUI portion of kpk2cmd is copyright Canna Software\n"
												 "and Lloyd Sargent.\n\n"
												 "Kpk2cmd has been released under the GPL license with no\n"
												 "WARRANTY and no GUARANTEE."); 
}



//-----
//
//				filePreferences
//
// synopsis:	filePreferences();
//
// description:	filePreferences is designed to
//
// errors:	
//
// returns:
//

void kpk2cmd::filePreferences()
{
	systemPreferencesItem systemPrefs;
	preferencewidget *preferences;
	preferences = new preferencewidget(this);
	
	preferences->init(mainWindow->currentPrefs());
	
	if (preferences->exec() == QDialog::Accepted) 
	{
		systemPrefs = preferences->getModifiedPrefs();
		mainWindow->updatePrefs(systemPrefs);
	}	
}



//-----
//
//				justBeforeQuit
//
// synopsis:	justBeforeQuit();
//
// description:	justBeforeQuit is designed to
//
// errors:	
//
// returns:
//

void kpk2cmd::justBeforeQuit()
{
printf("just before quit\n");
	delete mainWindow;
}


//#include "kpk2cmd.moc"

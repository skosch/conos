//----------
//
//				kpk2cmd.h
//
// filename:	kpk2cmd.h
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


#ifndef _KPK2CMD_H_
#define _KPK2CMD_H_


//---------- pragmas



//---------- include files
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <qmainwindow.h>
#include <qmenubar.h>



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



class kpk2cmdWidget;
class kpk2cmd : public QMainWindow
{
	kpk2cmdWidget *mainWindow;
	QMenuBar *menubar;
	
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    kpk2cmd();

    /**
     * Default Destructor
     */
    virtual ~kpk2cmd();
	
	
public slots:
    /*$PUBLIC_SLOTS$*/
	virtual void fileAbout();
	virtual void filePreferences();
	virtual void justBeforeQuit();		
};

#endif // _KPK2CMD_H_

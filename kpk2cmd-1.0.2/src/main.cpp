//----------
//
//				main.cpp
//
// filename:	main,cpp
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
 
 
 
//---------- pragmas
 
 
 
//---------- include files
#include "kpk2cmd.h"
#include <qapplication.h>



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
//				main
//
// synopsis:	retval = main(int argc, char **argv);
//					int retval       - 
//					int argc        - 
//					char **argv     - 
//
// description:	main is designed to
//
// errors:	
//
// returns:
//

int main(int argc, char **argv)
{
    QApplication app(argc, argv, TRUE);
    kpk2cmd *mainWin = 0;

    mainWin = new kpk2cmd();
    app.setMainWidget( mainWin );
    mainWin->show();
	
	// mainWin has WDestructiveClose flag by default, so it will delete itself.

    return app.exec();
}

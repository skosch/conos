//----------
//
//				getfamilypart.h
//
// filename:	getfamilypart.h
//
// author:		Jeff Post
//				lloyd sargent
//
// created:		March 25, 2008
//
// description:	This file is designed to
//
// notes:		none
//
// revisions:
//
// Copyright by Jeff Post, j_post <AT> pacbell <DOT> net
// Modififications copyright by Canna Software, lloyd <AT> cannasoftware <DOT> com
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


#ifndef _DAT2TEXT_H
#define _DAT2TEXT_H


//---------- pragmas



//---------- include files



//---------- enumerated data types



//---------- typedefs
typedef struct picPartItem
{
	char name[32];                                                              // basic string
	uint id;																	// four bytes describing internal ID
} picPartItem;



//---------- structs



//---------- definitions
#define	byte		unsigned char
#define	ushort		unsigned short
#define	uint		unsigned int



//---------- external functions



//---------- external variables



//---------- global functions



//---------- global variables



//---------- local functions



//---------- local variables



//---------- classes
class csList;
class getfamilypart
{
	int pic12;
    int pic14;
	int pic16;
	int pic18;
	int pic24;
	int pic30;
	int pic33;
	
public:
	getfamilypart();
	~getfamilypart();
	int getparts(csList *pic12, csList *pic14, csList *pic16,
				  csList *pic18, csList *pic24, csList *pic30,
				  csList *pic33);
	int readInt(byte *data);
	ushort readUShort(byte *data);
	int skipString(int offset);
	void usage(void);
	void sort(csList *list);
};


#endif

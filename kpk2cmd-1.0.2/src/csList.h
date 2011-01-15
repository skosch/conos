//----------
//
//				csList.h
//
// filename:	csList.h
//
// author:		Lloyd Sargent
//
// created:		March 24, 2008
//
// description:	This file is designed to
//
// notes:		none
//
// revisions:
//
// Copyright 2008 (c) Canna Software
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



#ifndef csList_h
#define	csList_h



//---------- pragmas



//---------- include files



//---------- enumerated data types



//---------- typedefs
#ifndef byte
typedef unsigned char byte;
#endif

#ifndef word
typedef unsigned short word;
#endif




//---------- definitions



//---------- classes
class csList
{
	void **list;							// current point to the list
	int listcnt;							// number of object actually in the list
	int listsize;							// list size in possible object storage

public:
	csList();
	virtual ~csList();

	int insertBefore(void *data, int size, int index);
	void set(void *object, int index);
	int add(void *object);
	int add(void *data, int size);
	void del(int index);
	int insertAfter(void *object, int index);
	int insertBefore(void *object, int index);
	void *get(int index);
	int count(void);
	csList *dup(void);
	void delAllPointers(void);
	void delAllValues(void);
	void del(void *object);
};



//---------- external functions



//---------- external variables



//---------- global functions



//---------- global variables



//---------- local functions



//---------- local variables



#endif

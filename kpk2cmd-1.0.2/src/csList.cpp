//----------
//
//				csList.cpp
//
// filename:	csList.cpp
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



//---------- include files
#include "string.h"

#include "csList.h"



//---------- enumerated data types



//---------- typedefs



//---------- definitions



//---------- classes



//---------- external functions



//---------- external variables



//---------- global functions



//---------- global variables



//---------- local functions



//---------- local variables






//-----
//
//				csList::csList
//
// synopsis:	retval = csList::csList();
//					retval	-
//
// description:	csList::csList is designed to
//
// errors:		none
//
// returns:		none
//

csList::csList()
{
    listsize = 63;                                                  // this assures we always have a trailing zero on the end
    list = (void **) new void *[listsize];                          // allocate the list
    listcnt = 0;                                                    // number of items actually in the list
}



//-----
//
//				csList::~csList
//
// synopsis:	csList::~csList();
//
// description:	csList::~csList is designed to
//
// errors:		none
//
// returns:		none
//

csList::~csList()
{
	delete list;
}



//-----
//
//				csList::add
//
// synopsis:	retval = csList::add(data, size);
//					int retval	-
//					void * data	-
//					int size	-
//
// description:	csList::add is designed to
//
// errors:		none
//
// returns:		none
//

int csList::add(void *data, int size)
{
	byte *object = (byte *) new byte[size];

	//----- copy the object data
	memmove(object, data, size);

	//----- add to the end of the list and return the index
	return (add((void *) object));
}



//-----
//
//				csList::add
//
// synopsis:	retval = csList::add(object);
//					retval	-
//					void *object	-
//
// description:	csList::add is designed to
//
// errors:		none
//
// returns:		none
//

int csList::add(void *object)
{
	void **temp;

	//----- do we need to increase the size of the list?
	if ((listcnt + 1) > listsize)
	{
		//----- create new list
		listsize += 64;
		temp = (void **) new void *[listsize * sizeof(void *)];

		memmove(temp, list, sizeof(object) * listcnt);
		delete list;
		list = temp;
	}

	list[listcnt] = object;
	++listcnt;
	return (listcnt - 1);
}




//-----
//
//				csList::insertAfter
//
// synopsis:	retval = csList::insertAfter(object, index);
//					int retval	-
//					void *object	-
//					int index	-
//
// description:	insertAfter is designed to
//
// errors:		none
//
// returns:		none
//

int csList::insertAfter(void *object, int index)
{
	void **temp;

	//----- if adding to the end of the list, use the add method
	if (index >= listcnt)
	{
		return (add(object));
	}

	//----- do we need to increase the size of the list?
	if ((listcnt + 1) > listsize)
	{
		//----- create new list
		listsize += 64;
		temp = (void **) new void *[listsize * sizeof(void *)];

		memmove(temp, list, sizeof(object) * listcnt);
		delete list;
		list = temp;
	}

	//----- move the others up to make room
	memmove(&list[index + 2], &list[index + 1], sizeof(object) * (listcnt - index - 1));

	//----- insert into the list
	list[index + 1] = object;
	++listcnt;

	return (index);
}



//-----
//
//				csList::insertBefore
//
// synopsis:	retval = csList::insertBefore(data, size, index);
//					int retval	-
//					void *data	-
//					int size	-
//					int index	-
//
// description:	csList::insertBefore is designed to
//
// errors:		none
//
// returns:		none
//

int csList::insertBefore(void *data, int size, int index)
{
	void *object = (byte *) new byte[size];

	//----- copy the object data
	memmove(object, data, size);

	//----- add to the end of the list and return the index
	return (insertBefore(object, index));
}



//-----
//
//				csList::insertBefore
//
// synopsis:	retval = csList::insertBefore(object, index);
//					int retval	-
//					void *object	-
//					int index	-
//
// description:	csList::insertBefore is designed to
//
// errors:		none
//
// returns:		none
//

int csList::insertBefore(void *object, int index)
{
	void **temp;

	//----- if adding to the end of the list, use the add method
	if (index >= listcnt)
	{
		return (add(object));
	}

	//----- do we need to increase the size of the list?
	if ((listcnt + 1) > listsize)
	{
		//----- create new list
		listsize += 64;
		temp = (void **) new void *[listsize * sizeof(void *)];

		memmove(temp, list, sizeof(object) * listcnt);
		delete list;
		list = temp;
	}

	//----- move the others up to make room
	memmove(&list[index + 1], &list[index], sizeof(object) * (listcnt - index));

	//----- insert into the list
	list[index] = object;
	++listcnt;

	return (index);
}



//-----
//
//				csList::del
//
// synopsis:	csList::del(object);
//					void *object	-
//
// description:	csList::delete is designed to
//
// errors:		none
//
// returns:		none
//

void csList::del(void *object)
{
	int index;

	//----- if the list is empty, bail
	if (!listcnt)
		return;

	//----- search for the object in our list
	for (index = 0; index < listcnt; ++index)
	{
		if (list[index] == object)
		{
			del(index);
			return;
		}
	}
	
	//----- if we reached this point, the object was not in the list
//	debugio->dbgprintf(1024, "csList::Del - Object not found!");
}



//-----
//
//				csList::del
//
// synopsis:	retval = csList::del(index);
//					retval	-
//					int index	-
//
// description:	csList::del is designed to
//
// errors:		none
//
// returns:		none
//

void csList::del(int index)
{
	//----- if the list is empty, bail
	if (!listcnt)
		return;

	//----- delete by moving the others to cover it up...
	--listcnt;
	memmove(&list[index], &list[index + 1], (sizeof(void *) * (listcnt - index)));
//	list = (void *) LocalReAlloc(list, sizeof(void *) * (listcnt), LMEM_FIXED);
}



//-----
//
//				get
//
// synopsis:	retval = get(index);
//					csList::void *retval	-
//					int index	-
//
// description:	get is designed to
//
// errors:		none
//
// returns:		none
//

void *csList::get(int index)
{
	//----- if the list is empty, return null
	if (!listcnt)
		return (NULL);

	//----- see if we attempted to overstep our bounds
	if (index >= listcnt)
		return (NULL);

	//----- else return the item
	return (list[index]);
}



//-----
//
//				csList::set
//
// synopsis:	csList::set(object, index);
//					void *object	-
//					int index	-
//
// description:	csList::set is designed to
//
// errors:		none
//
// returns:		none
//

void csList::set(void *object, int index)
{
	if (index + 1 >= listcnt)
		add(object);

	else
	{
		list[index] = object;
	}		
}



//-----
//
//				csList::count
//
// synopsis:	retval = csList::count();
//					int retval	-
//
// description:	csList::count is designed to
//
// errors:		none
//
// returns:		none
//

int csList::count(void)
{
	return (listcnt);
}



//-----
//
//				*csList::dup
//
// synopsis:	retval = *csList::dup();
//					csList retval	-
//
// description:	*csList::dup is designed to return a duplicate of this list.
//
// errors:		none
//
// returns:		none
//

csList *csList::dup(void)
{
	csList *newList = new csList();

	delete newList->list;
	newList->listcnt = listcnt;
	newList->listsize = listsize;
	newList->list = (void **) new void *[listsize * sizeof(void *)];
	memmove(newList->list, list, listcnt * sizeof(void *));

	return (newList);
}



//-----
//
//				csList::delAllPointers
//
// synopsis:	csList::delAllPointers();
//
// description:	csList::delAllPointers is designed to
//
// errors:		none
//
// returns:		none
//

void csList::delAllPointers(void)
{
	int index;

	for (index = 0; index < listcnt; ++index)
	{
		delete list[index];
	}

	delAllValues();
}



//-----
//
//				csList::delAllValues
//
// synopsis:	csList::delAllValues();
//
// description:	csList::delAllValues is designed to
//
// errors:		none
//
// returns:		none
//

void csList::delAllValues(void)
{
//	LocalFree(list);
//	list = (void *) LocalAlloc(LPTR, 1);
	listcnt = 0;
}





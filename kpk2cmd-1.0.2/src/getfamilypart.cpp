//----------
//
//				getfamilypart.cpp
//
// filename:	getfamilypart.cpp
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
 
 
 
//---------- pragmas
 
 
 
//---------- include files
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <string.h>

#include "csList.h"

#include "getfamilypart.h"




//---------- enumerated data types



//---------- typedefs



//---------- structs



//---------- definitions
#define	byte		unsigned char
#define	ushort	unsigned short
#define	uint		unsigned int



//---------- external functions



//---------- external variables



//---------- global functions



//---------- global variables



//---------- local functions



//---------- local variables
static FILE	*fp;
static FILE	*fpo;
static int numFamilies;
static int numParts;
static char inFileName[] = "/usr/share/pk2cmd/PK2DeviceFile.dat";
static char *inFile = NULL;
static char *outFile = NULL;



//---------- classes



struct stat	filestat;

byte	*buffer;

getfamilypart::getfamilypart()
{
	pic12 = 0;
    pic14 = 0;
	pic16 = 0;
	pic18 = 0;
	pic24 = 0;
	pic30 = 0;
	pic33 = 0;

}

getfamilypart::~getfamilypart()
{
}


// Get an int from the binary file in an endian independent way.


int getfamilypart::getparts(csList *pic12, csList *pic14, csList *pic16,
							 csList *pic18, csList *pic24, csList *pic30,
	   						 csList *pic33)
{
	int	tempoffset;
	int	k;
	int fsize;
	int offset;
	uint internalId;

	inFile = inFileName;

	fp = fopen(inFile, "rb");

	if (!fp)
	{
		printf("\nCan't open file %s\n\n", inFile);
		return 1;
	}

	stat(inFile, &filestat);
	fsize = (int) filestat.st_size;
	buffer = (unsigned char *) malloc(fsize);

	if (!buffer)
	{
		printf("Can't get buffer memory!\n\n");
		fclose(fp);
		return 1;
	}

//	fpo = fopen(outFile, "w");
	fpo = stdout;

	if (!fpo)
	{
		fclose(fp);
		printf("\nCan't create %s file\n\n", outFile);
		free(buffer);
		return 1;
	}

	fread((void *) buffer, sizeof(byte), fsize, fp);

	offset = skipString(12);

	tempoffset = offset;
	numFamilies = readInt((byte *) &buffer[tempoffset]);
	tempoffset += 4;
	numParts = readInt((byte *) &buffer[tempoffset]);
//	fprintf(fpo, "Number of parts: %d\n", numParts);
	tempoffset += 16;
	offset = tempoffset;

	for (k=0; k<numFamilies; k++)
	{
		offset += 6;
		offset = skipString(offset);
		offset += 38;
	}

	for (k=0; k<numParts; k++)
	{
//		fprintf(fpo, "\nPart name: ");

//printf(" len=%d ", buffer[offset] & 0xff);
int strlen = buffer[offset] & 0xff;
char partname[256];
memmove(partname, &buffer[offset + 1], strlen);
partname[strlen] = 0;
//printf("Part name = %s\n", partname);
		
		offset = skipString(offset);
		offset += 2;
		internalId = readInt((byte *) &buffer[offset]);
		offset += 200;
		
		//----- okay, now stick the part numbers in the list
		if (strncmp("PIC12", partname, 5) == 0)
		{
			picPartItem *part = new picPartItem;
			strncpy(part->name, partname, 32);
			pic12->add(part);
		}

		if (strncmp("PIC14", partname, 5) == 0)
		{
			picPartItem *part = new picPartItem;
			strncpy(part->name, partname, 32);
			pic14->add(part);
		}

		if (strncmp("PIC16", partname, 5) == 0)
		{
			picPartItem *part = new picPartItem;
			strncpy(part->name, partname, 32);
			pic16->add(part);
		}

		if (strncmp("PIC18", partname, 5) == 0)
		{
			picPartItem *part = new picPartItem;
			strncpy(part->name, partname, 32);
			pic18->add(part);
		}

		if (strncmp("PIC24", partname, 5) == 0)
		{
			picPartItem *part = new picPartItem;
			strncpy(part->name, partname, 32);
			pic24->add(part);
		}

		if (strncmp("dsPIC30", partname, 7) == 0)
		{
			picPartItem *part = new picPartItem;
			strncpy(part->name, partname, 32);
			pic30->add(part);
		}

		if (strncmp("dsPIC33", partname, 7) == 0)
		{
			picPartItem *part = new picPartItem;
			strncpy(part->name, partname, 32);
			pic33->add(part);
		}

	}
	
	//----- now sort our lists
	sort(pic12);
	sort(pic14);
	sort(pic16);
	sort(pic18);
	sort(pic24);
	sort(pic30);
	sort(pic33);

	fprintf(fpo, "\n");
	fclose(fp);
	free(buffer);
	return 0;
}



//-----
//
//				readInt
//
// synopsis:	retval = readInt(byte *data);
//					int retval   - 
//					byte *data  - 
//
// description:	readInt is designed to
//
// errors:	
//
// returns:
//

int getfamilypart::readInt(byte *data)
{
	int	val;

	val = (int) data[0] & 0xff;
	val |= (((int) data[1] & 0xff) << 8);
	val |= (((int) data[2] & 0xff) << 16);
	val |= (((int) data[3] & 0xff) << 24);
	return val;
}



//-----
//
//				readUShort
//
// synopsis:	retval = readUShort(byte *data);
//					ushort retval    - 
//					byte *data      - 
//
// description:	readUShort is designed to Get an unsigned short from the binary file in an endian independent way.
//
// errors:	
//
// returns:
//

ushort getfamilypart::readUShort(byte *data)
{
	ushort	val;

	val = (int) data[0] & 0xff;
	val |= (((int) data[1] & 0xff) << 8);
	return val;
}



//-----
//
//				skipString
//
// synopsis:	retval = skipString(int offset);
//					int retval   - 
//					int offset  - 
//
// description:	skipString is designed to skip a string in the data file.
//
// errors:	
//
// returns:
//

int getfamilypart::skipString(int offset)
{
	int	i, j;
	char	*cptr;

	cptr = (char *) (buffer + offset);
	j = (int) ((*cptr++) & 0xff);
	offset++;

	if (j > 127)
	{
		i = (int) ((*cptr++) & 0xff) - 1;
		j += (i * 128);
		offset++;
	}

	offset += j;
	return offset;
}



//-----
//
//				sort
//
// synopsis:	sort(list);
//					 csList *list  - 
//
// description:	sort is designed to
//
// errors:	
//
// returns:
//

void getfamilypart::sort(csList *list)
{
	csList *srcList = new csList();
	int index;
	int next;
	int result;
	
	//----- copy into our srcList
	for (index = 0; index < list->count(); ++index)
	{
		srcList->add(list->get(index));
	}
	
	//----- now empty list
	list->delAllValues();
	
	//----- create the new list...	
	for (index = 0; index < srcList->count(); ++index)
	{
		//----- if list is empty, put the first item in it
		if (list->count() == 0)
			list->add(srcList->get(index));
		
		//----- the remains of this is an insertion sort
		else
		{
			picPartItem *partOne;
			picPartItem *partTwo;
			
			partOne = (picPartItem *) srcList->get(index);
			result = -5;
			for (next = 0; next < list->count(); ++next)
			{
				partTwo = (picPartItem *) list->get(next);

				result = strcmp(partOne->name, partTwo->name);
				if (result == -1)
				{
					list->insertBefore(partOne, next);
					result = 0;
					break;
				}
			}
			if (result != 0)
				list->add(partOne);			
		}
	}
}

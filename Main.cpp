#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "DateTime.h" 
#include "Objects.h" 
#include "Headers.h" 
#include "Structs.h" 

#pragma warning ( disable : 4996 ) 

// O is given by instructor, for Karl-Andreas Turvas O = 4
#define O 4 
// For testing 25 < N < 35 is sufficient. N may never be 0.
#define N 35 
// Define GetDateString string length that returns DD-MM-YYYY
// AKA 10 for string and +1 for null string = 11
#define DATESTRINGLEN 11

void PrintObjects(HeaderD* pStruct7)
{
	// Initialize the traversal pointer
	HeaderD* pStructTemp = pStruct7;
	int i = 1, j = 1;

	// Traverse double linked list of headers until we hit NULL on pNext
	while (pStructTemp != NULL)
	{ 

		// Print header number and it's cBegin
		printf("[Hdr %d] %c\n", i, pStructTemp->cBegin);

			// Declare a temp pointer from header struct
			Object4* pObjectTemp = (Object4*)pStructTemp->pObject;

			// Traverse linked list of objects
			while (pObjectTemp != NULL)
			{ 

				// Print Object ID, Code and Date
				printf("\t (Obj %d) %s ", j, pObjectTemp->pID); 
				printf("%lu %s\n", pObjectTemp->Code, pObjectTemp->pDate);
				// Set traversal pointer to pNext of current Object
				pObjectTemp = pObjectTemp->pNext;
				j++;
			}

		// Set traversal pointer to pNext of current Header
		pStructTemp = pStructTemp->pNext;
		i++;
	}
}

int InsertNewObject(HeaderD** pStruct7, char* pNewID, int NewCode)
{
	// Initialize the traversal pointers 
	HeaderD* pStructTemp = *pStruct7;
	HeaderD* pStructNew = NULL;

	while (*pNewID != pStructTemp->cBegin)
	{
		printf("NewC %c, Cbegin %c \n", *pNewID, pStructTemp->cBegin);
		// If next pointer is NULL...
		// ...then create new Header for Object
		if (pStructTemp->pNext == NULL)
		{
			// Alloc memory and insert data into new Header
			pStructNew = (HeaderD*)malloc(sizeof(HeaderD));
			if (pStructNew == NULL)
			{
				printf("InsertNewObject(): malloc failed!");
				return 0;
			}
			pStructNew->pPrior = pStructTemp;
			pStructNew->pNext = NULL;
			pStructNew->cBegin = *pNewID;
			pStructNew->pObject = NULL;
			// Change pointers to insert new Header into list
			pStructTemp->pNext = pStructNew;
			pStructTemp = pStructNew;
			break;

		// If cBegin of next Header is later in...
		// ...alphabet create a new Header
		} else if (pStructTemp->pNext->cBegin > *pNewID)
		{
			// Alloc memory and insert data into new Header
			pStructNew = (HeaderD*)malloc(sizeof(HeaderD));
			if (pStructNew == NULL)
			{
				printf("InsertNewObject(): malloc failed!");
				return 0;
			}
			pStructNew->pPrior = pStructTemp;
			pStructNew->pNext = pStructTemp->pNext;
			pStructNew->cBegin = *pNewID;
			pStructNew->pObject = NULL;
			// Change pointers to insert new Header into list
			pStructTemp->pNext->pPrior = pStructNew;
			pStructTemp->pNext = pStructNew;
			pStructTemp = pStructNew;
			break;
		}

		// Set traversal pointer to pNext of current Header
		pStructTemp = pStructTemp->pNext;
	}

	// Declare a temp pointer from headers object
	Object4* pObjectTemp = (Object4*)pStructTemp->pObject;
	if (pObjectTemp != NULL) {
		while (pObjectTemp->pNext != NULL)
		{
			pObjectTemp = pObjectTemp->pNext;
		}
		// Allocate memory for new Object
		Object4* pObjectNew = (Object4*)malloc(sizeof(Object4));
		// Insert Code to new Object
		pObjectNew->Code = NewCode;
		// Insert Date to new Object
		time_t RawTime = time(NULL);
		char* pResult = (char*)malloc(DATESTRINGLEN);
		if (pResult == NULL)
		{
			printf("InsertNewObject(): malloc failed!");
			return 0;
		}
		if (GetDateString(RawTime, DATESTRINGLEN, pResult) == 1)
		{
			pObjectNew->pDate = pResult;
		}
		else {
			printf("InsertNewObject(): Unable to get date!");
			return 0;
		}
		// Allocate memory for new ID and insert into new Object
		pObjectNew->pID = (char*)malloc(strlen(pNewID));
		if (pObjectNew->pID == NULL)
		{
			printf("InsertNewObject(): malloc failed!");
			return 0;
		}
		strcpy(pObjectNew->pID, pNewID);
		// Set next in list to NULL if last Object in list
		pObjectNew->pNext = NULL;
		// Insert new Object into list 
		pObjectTemp->pNext = pObjectNew;
	}
	else 
	{
		// Allocate memory for new Object
		Object4* pObjectTemp = (Object4*)malloc(sizeof(Object4));
		if (pObjectTemp == NULL)
		{
			printf("InsertNewObject(): malloc failed!");
			return 0;
		}

		// Insert Code to new Object
		pObjectTemp->Code = NewCode;
		// Insert Date to new Object
		time_t RawTime = time(NULL);
		char* pResult = (char*)malloc(DATESTRINGLEN);
		if (pResult == NULL)
		{
			printf("InsertNewObject(): malloc failed!");
			return 0;
		}
		if (GetDateString(RawTime, DATESTRINGLEN, pResult) == 1)
		{
			pObjectTemp->pDate = pResult;
		}
		else {
			printf("InsertNewObject(): Unable to get date, exiting...");
			return 0;
		}
		// Allocate memory for new ID and insert into new Object
		pObjectTemp->pID = (char*)malloc(strlen(pNewID));
		strcpy(pObjectTemp->pID, pNewID);
		// Set next in list to NULL if last Object in list
		pObjectTemp->pNext = NULL;
		// Insert new Object into list 
		pStructTemp->pObject = pObjectTemp;
	}

	return 1;
}

int main()
{
	// Struct is given by instructor, for Karl-Andreas Turvas Struct7
	// g) Struct7 puhul: 
	HeaderD* pStruct7 = GetStruct7(O, N);
	PrintObjects(pStruct7);

	time_t RawTime = time(NULL);
	int nResult = 11; 
	char* pResult = (char*)malloc(nResult); 
	if (GetDateString(RawTime, nResult, pResult) == 1)
	{
		printf("GOT DATE %s\n", pResult);
	}


	char* pNewID = (char*)malloc(strlen("Zuehdoc") + 1);
	strcpy(pNewID, "Buehdoccc");
	printf("%c\n", *pNewID);

	if ('Z' > *pNewID) {
		printf("YES!\n");
	}

	HeaderD** ppStruct7 = &pStruct7;
	if (InsertNewObject(ppStruct7, pNewID, 197775801)) {
		printf("\n\n------------\n\n");
		PrintObjects(pStruct7);
	}
	// Last object Ypuwquch 197775800 01-10-2021
	
	//freeStruct(pStruct7);
	return 0;
}

/*
// Unnecessary free function for generated struct
void freeStruct(HeaderD* pStruct7)
{
	HeaderD* pStructTemp;
	int i, j;

	// Traverse double linked list of headers and free them until we hit NULL on pNext
	while (pStruct7 != NULL)
	{

		// Free Objects
		while (pStruct7->pObject != NULL)
		{
			// Declare a temp pointer from header struct
			Object4* pObjectTemp = (Object4*)pStruct7->pObject;
			pStruct7->pObject = pObjectTemp->pNext;
			free(pObjectTemp);
		}

		pStructTemp = pStruct7;
		pStruct7 = pStruct7->pNext;
		free(pStructTemp);
	}

}
*/

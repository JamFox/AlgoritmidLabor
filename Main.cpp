#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "ctype.h"
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

HeaderD* pHeaderDNew(char* pNewID, int NewCode, HeaderD* pStructPrior, HeaderD* pStructNext)
{
	HeaderD* pStructNew = (HeaderD*)malloc(sizeof(HeaderD));
	if (pStructNew == NULL)
	{
		printf("InsertNewObject(): malloc failed!");
		exit(EXIT_FAILURE);
	}
	pStructNew->pPrior = pStructPrior;
	pStructNew->pNext = pStructNext;
	pStructNew->cBegin = *pNewID;
	pStructNew->pObject = NULL;
	// Change pointers to insert new Header into list
	if (pStructNext != NULL)
	{
		pStructNext->pPrior = pStructNew;
	}
	return pStructNew;
}

Object4* pObject4New(char* pNewID, int NewCode, Object4* pNext) {
	// Allocate memory for new Object
	Object4* pObjectNew = (Object4*)malloc(sizeof(Object4));
	if (pObjectNew == NULL)
	{
		printf("InsertNewObject(): malloc failed!");
		exit(EXIT_FAILURE);
	}
	// Insert Code to new Object
	pObjectNew->Code = NewCode;
	// Insert Date to new Object
	time_t RawTime = time(NULL);
	char* pResult = (char*)malloc(DATESTRINGLEN);
	if (pResult == NULL)
	{
		printf("InsertNewObject(): malloc failed!");
		exit(EXIT_FAILURE);
	}
	if (GetDateString(RawTime, DATESTRINGLEN, pResult) == 1)
	{
		pObjectNew->pDate = pResult;
	}
	else {
		printf("InsertNewObject(): Unable to get date, exiting...");
		exit(EXIT_FAILURE);
	}
	// Allocate memory for new ID and insert into new Object
	pObjectNew->pID = (char*)malloc(strlen(pNewID));
	strcpy(pObjectNew->pID, pNewID);
	// Set next in list 
	pObjectNew->pNext = pNext;
	return pObjectNew;
}

bool isLetters(char* pInput)
{
	while (*pInput != '\0')
	{
		int uppercaseChar = toupper(*pInput);
		if (uppercaseChar < 'A' || uppercaseChar > 'Z') 
		{
			return false;
		}
		pInput++;
	}
	return true; 
}

int InsertNewObject(HeaderD** pStruct7, char* pNewID, int NewCode)
{
	if (!isupper(*pNewID))
	{
		printf("pNewID inst upper\n");
		return 0;
	}
	if (!isLetters(pNewID))
	{
		printf("pNewID inst letters\n");
		return 0;
	}
	// Initialize the traversal pointer 
	HeaderD* pStructTemp = *pStruct7;

	while (*pNewID != pStructTemp->cBegin)
	{
		// If next pointer is NULL...
		// ...then create new Header for Object
		if (pStructTemp->pNext == NULL)
		{
			pStructTemp->pNext = pHeaderDNew(pNewID, NewCode, pStructTemp, pStructTemp->pNext);
			pStructTemp = pStructTemp->pNext;
			break;

		// If cBegin of next Header is later in...
		// ...alphabet, create a new Header
		} else if (pStructTemp->pNext->cBegin > *pNewID)
		{
			pStructTemp = pHeaderDNew(pNewID, NewCode, pStructTemp, pStructTemp->pNext);
			break;
		}
		// Set traversal pointer to pNext of current Header
		pStructTemp = pStructTemp->pNext;
	}

	// Declare a temp pointer from headers object
	Object4* pObjectTemp = (Object4*)pStructTemp->pObject;
	if (pObjectTemp != NULL) {
		// TODO: keep sorted, dont enter to the end of list
		bool foundInsertion = false;
		char* pTempNew;
		char* pTempOld;
		while (pObjectTemp->pNext != NULL)
		{
			pTempNew = pNewID;
			pTempOld = pObjectTemp->pID;
			while (*pTempNew < *pTempOld)
			{
				printf("new %c, old %c\n", *pTempNew, *pTempOld);
				if (*pTempNew < *pTempOld)// || *pTempNew == '\0' || *pTempOld == '\0')
				{
					printf("Found insertion!\n");
					foundInsertion = true;
					break;
				}
				pTempNew++;
				pTempOld++;
			}
			if(foundInsertion)
			{
				break;
			}
			printf("new object\n");
			pObjectTemp = pObjectTemp->pNext;
		}

		pObjectTemp->pNext = pObject4New(pNewID, NewCode, NULL);
	}
	else 
	{
		pStructTemp->pObject = pObject4New(pNewID, NewCode, NULL);
	}

	return 1;
}

int main()
{
	// Struct is given by instructor, for Karl-Andreas Turvas Struct7
	// g) Struct7 puhul: 
	HeaderD* pStruct7 = GetStruct7(O, N);
	// PrintObjects(pStruct7);

	time_t RawTime = time(NULL);
	int nResult = 11; 
	char* pResult = (char*)malloc(nResult); 
	if (GetDateString(RawTime, nResult, pResult) == 1)
	{
		printf("GOT DATE %s\n", pResult);
	}


	char* pNewID = (char*)malloc(strlen("Teecccccc") + 1);
	strcpy(pNewID, "Teecccccc");
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

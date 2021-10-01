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

void PrintObjects(HeaderD* pStruct7)
{
	// Initialize the traversal pointer
	HeaderD* pStructTemp = pStruct7;
	int i, j;

	// Traverse double linked list of headers until we hit NULL on pNext
	for (i = 1; pStructTemp != NULL; i++)
	{

		// Print header number and it's cBegin
		printf("[Hdr %d] %c\n", i, pStructTemp->cBegin);

		// Declare a temp pointer from header struct
		Object4* pObjectTemp = (Object4*)pStructTemp->pObject;

		// Traverse linked list of objects
		for (j = 1; pObjectTemp->pNext != NULL; j++)
		{

			// Print Object ID, Code and Date
			printf("\t (Obj %d) %s ", j, pObjectTemp->pID);
			printf("%lu %s\n", pObjectTemp->Code, pObjectTemp->pDate);
			// Set traversal pointer to pNext of current Object
			pObjectTemp = pObjectTemp->pNext;
		}

		// Set traversal pointer to pNext of current Header
		pStructTemp = pStructTemp->pNext;
	}
}

int InsertNewObject(HeaderD** pStruct7, char* pNewID, int NewCode)
{
	// Initialize the traversal pointers 
	HeaderD* pStructTemp = *pStruct7;
	HeaderD* pStructNew;

	while (*pNewID != pStructTemp->cBegin)
	{

		// If next pointer is NULL and letters do not match
		// ...then create new Header to it
		if (pStructTemp->pNext == NULL && pStructTemp->pNext->cBegin != *pNewID)
		{
			printf("next pointer is null and letters dont match\n");
			// Alloc memory and insert data into new Header
			pStructNew = (HeaderD*)malloc(sizeof(HeaderD));
			pStructNew->pPrior = pStructTemp;
			pStructNew->pNext = NULL;
			pStructNew->cBegin = *pNewID;
			// Change pointers to insert new Header into list
			pStructTemp->pNext = pStructNew;
			pStructTemp = pStructNew;
			break;

			// If cBegin of next Header is later in...
			// ...alphabet create a new Header
		}
		else if (pStructTemp->pNext->cBegin > *pNewID)
		{
			printf("next letter is higher than newID first letter\n");
			// Alloc memory and insert data into new Header
			pStructNew = (HeaderD*)malloc(sizeof(HeaderD));
			pStructNew->pPrior = pStructTemp;
			pStructNew->pNext = pStructTemp->pNext;
			pStructNew->cBegin = *pNewID;
			// Change pointers to insert new Header into list
			pStructTemp->pNext->pPrior = pStructNew;
			pStructTemp->pNext = pStructNew;
			pStructTemp = pStructNew;
			break;
		}

		// Set traversal pointer to pNext of current Header
		pStructTemp = pStructTemp->pNext;
	}

	// Declare a temp pointer from header struct
	Object4* pObjectTemp = (Object4*)pStructTemp->pObject;
	while (pObjectTemp->pNext != NULL)
	{
		pObjectTemp = pObjectTemp->pNext;
	}
	Object4* pObjectNew = (Object4*)malloc(sizeof(Object4));
	pObjectNew->Code = NewCode;

	time_t RawTime = time(NULL);
	int nResult = 11;
	char* pResult = (char*)malloc(nResult);
	if (GetDateString(RawTime, nResult, pResult) == 1)
	{
		pObjectNew->pDate = pResult;
	}
	pObjectNew->pID = (char*)malloc(sizeof(pNewID));
	strcpy(pObjectNew->pID, pNewID);
	pObjectNew->pNext = NULL;

	pObjectTemp->pNext = pObjectNew;

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


	char* pNewID = (char*)malloc(strlen("Yyuehdoc") + 1);
	strcpy(pNewID, "Yyuehdoc");
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

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
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

				// Print Objects ID, Code and Date
				printf("\t (Obj %d) %s %lu %s\n", j, pObjectTemp->pID, pObjectTemp->Code, pObjectTemp->pDate); // Print objects number, ID, code and date
				// Set traversal pointer to pNext of current Object
				pObjectTemp = pObjectTemp->pNext;
			}

		// Set traversal pointer to pNext of current Header
		pStructTemp = pStructTemp->pNext;
	}
}

int InsertNewObject(HeaderD** pStruct7, char* pNewID, int NewCode)
{
	return 0;
}

void freeStruct(HeaderD* pStruct7)
{
	HeaderD* pStructTemp;
	int i, j;

	// Traverse double linked list of headers until we hit NULL on pNext
	while (pStruct7 != NULL)
	{
		
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
		printf("GOT DATE %s", pResult);
	}

	HeaderD** ppStruct7 = &pStruct7;
	// InsertNewObject(ppStruct7, pNewID, NewCode);
	// Last object Ypuwquch 197775800 01-10-2021
	freeStruct(pStruct7);
	return 0;
}
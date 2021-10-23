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

unsigned long int randomlx(int l, int r)
{ 
  return (rand() % (r - l + 1)) + l;
}

void PrintObjects(HeaderD* pStruct7)
{
  // Initialize the traversal pointer
  HeaderD* pStructTemp = pStruct7;
  int i = 1, j = 1;

  printf("\n\n\n--------Printing linked list:----------\n\n\n");
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

// Returns pointer to new Header
HeaderD* pHeaderDNew(char* pNewID, HeaderD* pStructPrior, HeaderD* pStructNext)
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

// Return pointer to new Object
Object4* pObject4New(char* pNewID, unsigned long int NewCode, Object4* pNextOb) {
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
    printf("InsertNewObject(): Unable to get date!");
    exit(EXIT_FAILURE);
  }
  // Allocate memory for new ID and insert into new Object
  pObjectNew->pID = (char*)malloc(strlen(pNewID));
  strcpy(pObjectNew->pID, pNewID);
  // Set next in list 
  pObjectNew->pNext = pNextOb;
  return pObjectNew;
}

// Return true if string is composed of letters
bool isLetters(char* pInput)
{
  while (*pInput != '\0')
  {
    int uppercaseChar = toupper(*pInput);
    if (uppercaseChar < 'A' || uppercaseChar > 'Z') 
    {
      printf("String is not composed of letters!\n");
      return false;
    }
    pInput++;
  }
  return true; 
}

// Returns true if strings letters are lowercase after first
bool lowerAfterFirst(char* pInput)
{
  pInput++;
  while (*pInput != '\0')
  {
    if (isupper(*pInput)) 
    {
      printf("Letters after first are not lowercase!\n");
      return false;
    }
    pInput++;
  }
  return true; 
}

// Insert new Object, create new Header if needed
int InsertNewObject(HeaderD** pStruct7, char* pNewID, int NewCode)
{
  // Print error if ID is not with first upper letter, does not consist...
  // ...fully of letters or is not lowercase after first upper letter
  if (!isupper(*pNewID) || !isLetters(pNewID) || !lowerAfterFirst(pNewID))
  {
    printf("ID does not match formatting requirements!\n");
    return 0;
  }
  // Initialize the traversal pointer 
  HeaderD* pStructTemp = *pStruct7;

  bool firstloop = true;
  // Loop through Headers until cBegin equals new IDs first letter
  while (*pNewID != pStructTemp->cBegin)
  {
    // If next pointer is NULL...
    // ...then create new Header for Object
    if (pStructTemp->pNext == NULL)
    {
      pStructTemp->pNext = pHeaderDNew(pNewID, pStructTemp, pStructTemp->pNext);
      pStructTemp = pStructTemp->pNext;
      break;
    }            
    // If cBegin of next Header is later in...
    // ...alphabet, create a new Header between
    if (pStructTemp->pNext->cBegin > *pNewID)
    {
      // If it's the first loop then there is no pPrior 
      if(firstloop == true) 
      {
        *pStruct7 = pHeaderDNew(pNewID, NULL, pStructTemp);
        pStructTemp = *pStruct7;
        break;
      }
      pStructTemp->pNext = pHeaderDNew(pNewID, pStructTemp, pStructTemp->pNext);
      pStructTemp = pStructTemp->pNext;
      break;
    }
    // Set traversal pointer to pNext of current Header
    pStructTemp = pStructTemp->pNext;
    firstloop = false;
  }

  // Declare traversal pointers
  Object4* pObjectTemp = (Object4*)pStructTemp->pObject;
  Object4* pObjectPrevious = pObjectTemp;
  firstloop = true; 
  int cmpvalue;
  // If Object ptr is not NULL, then loop through Objects to find insertion point
  for(;pObjectTemp != NULL;
      pObjectPrevious=pObjectTemp,pObjectTemp = pObjectTemp->pNext)
  {
    cmpvalue = strcmp(pNewID, pObjectTemp->pID);
    // If the new ID is earlier alphabetically than the current Object...
    // ...and it is the first loop, then exit loop...
    if (cmpvalue < 0 && firstloop == true) break;
    // ...otherwise set firstloop to false
    firstloop = false;
    if (cmpvalue == 0)
    { 
      printf("ID already exists!\n"); 
      return 0;
    }
    // If new ID is later alphabetically than the current Object...
    // ...then move on to the next Object
    if (cmpvalue < 0)
    { 
      continue;
    }
    // If new ID is earlier alphabetically than the current Object...
    // ...then insert between current and previous Object 
    if (cmpvalue > 0) 
    {
      pObjectPrevious->pNext = pObject4New(pNewID, NewCode, pObjectPrevious->pNext);
      return 1;
    }
  }
  // Add object as the first in Headers list
  pStructTemp->pObject = pObject4New(pNewID, NewCode, pObjectTemp);
  return 1;
}

Object4* RemoveExistingObject(HeaderD **pStruct7, char *pExistingID)
{
  HeaderD* pStructTemp = *pStruct7;
  // Loop through headers to find matching first letter
  while (*pExistingID != pStructTemp->cBegin)
  {
    // If next pointer is NULL, then Object did not exist
    if (pStructTemp->pNext == NULL)
    {
      printf("Header with '%c' does not exist!\n", *pExistingID);
      return NULL;
    }
    // Set traversal pointer to pNext of current Header
    pStructTemp = pStructTemp->pNext;
  }

  Object4* pObjectTemp = (Object4*)pStructTemp->pObject; 
  bool firstloop = true; 
  Object4* pObjectPrevious = pObjectTemp;
  int cmpvalue;
  // If Object ptr is not NULL, then loop through Objects to fins insertion point
  for(;pObjectTemp != NULL;
      pObjectPrevious=pObjectTemp,pObjectTemp = pObjectTemp->pNext)
  {
    cmpvalue = strcmp(pExistingID, pObjectTemp->pID);
    // If ID is found on the first loop
    if (cmpvalue == 0 && firstloop == true)
    {
      // If there are no other Object except the current one
      if (pObjectTemp->pNext == NULL)
      {
        // If the Object is last of the first Header
        if (pObjectTemp->pNext == NULL && pStructTemp->pPrior == NULL)
        {
          *pStruct7 = pStructTemp->pNext; 
        }
        if (pStructTemp->pPrior != NULL)
        {
          pStructTemp->pPrior->pNext = pStructTemp->pNext;
        }
        if (pStructTemp->pNext != NULL)
        {
          pStructTemp->pNext->pPrior = pStructTemp->pPrior;
        }
      } else {
        pStructTemp->pObject = pObjectTemp->pNext;
      }
      return pObjectTemp;
    }
    firstloop = false;
    if (cmpvalue == 0)
    { 
      pObjectPrevious->pNext = pObjectTemp->pNext;
      return pObjectTemp;
    }
  }
  printf("Could not find ID: %s\n", pExistingID);
  return NULL;
}

Node *InsertNode(Node *pTree, Object4 *pNewRecord) {
  Node *pNew = (Node*)malloc(sizeof(Node));// uus tipp
  if (pNew == NULL)
  {
    printf("InsertNode(): malloc failed!");
    exit(EXIT_FAILURE);
  }
  pNew->pObject = pNewRecord;
  pNew->pLeft = pNew->pRight = 0;
  if(!pTree)
    return pNew;// puu oli tühi
  for(Node *p = pTree; 1; ) {
    Object4* pTreeObject = (Object4*)p->pObject;
    char* pTreeID=pTreeObject->pID;
    if (strcmp(pNewRecord->pID, pTreeID)) {
      if (!p->pLeft) {// leidsime tühja koha
        p->pLeft = pNew;
        return pTree;
      }
      else
        p = p->pLeft;// liigume vasakule
    }
    else {
      if(!p->pRight) { // leidsime tühja koha
        p->pRight = pNew;
        return pTree;
      }
      else
        p = p->pRight;// liigume paremale
    }
  }
}

Node *CreateBinaryTree(HeaderD *pStruct7)
{
  Node *pBinaryTree = NULL;
  // Initialize the traversal pointer
  HeaderD* pStructTemp = pStruct7;
  int i = 1, j = 1;

  // Traverse double linked list of headers until we hit NULL on pNext
  while (pStructTemp != NULL)
  { 
    // Declare a temp pointer from header struct
    Object4* pObjectTemp = (Object4*)pStructTemp->pObject;

    // Traverse linked list of objects
    while (pObjectTemp != NULL)
    { 
      pBinaryTree = InsertNode(pBinaryTree, pObjectTemp);
      // Set traversal pointer to pNext of current Object
      pObjectTemp = pObjectTemp->pNext;
      j++;
    }
    // Set traversal pointer to pNext of current Header
    pStructTemp = pStructTemp->pNext;
    i++;
  }
  return pBinaryTree; 
}

Stack *Push(Stack *pStack, Object4 *pRecord)
{
  Stack *pNew;
  if(!pRecord)
  {
    return pStack;
  }
  pNew = (Stack *)malloc(sizeof(Stack));
  pNew->pObject = pRecord;
  pNew->pNext = pStack;
  return pNew;
}

Stack *Pop(Stack *pStack,void **pResult)
{
  Stack *p;
  if(!pStack)
  {
    *pResult = 0;
    return pStack;
  }
  *pResult = pStack->pObject;
  p = pStack->pNext;
  return p;
}

void TreeTraversal(Node *pTree)
{
  Stack *pStack = 0;
  Node *p1 = pTree, *p2;
  if (!pTree)
    return;
  do
  {
    while(p1)
    {
      pStack = Push(pStack, (Object4*)p1->pObject);
      p1 = p1->pLeft;
    }
    pStack = Pop(pStack, (void**)&p2);

    Object4* pTreeObject = (Object4*)p2->pObject;
    char* pID=pTreeObject->pID;
    printf("[Obj] %s", pID);

    p1 = p2->pRight;
  }
  while(!(!pStack && !p1));
}

int main()
{
  // Struct is given by instructor, for Karl-Andreas Turvas Struct7
  // g) Struct7 puhul: 
  HeaderD* pStruct7 = GetStruct7(O, N);
  PrintObjects(pStruct7);

  // Create strings for tests as specified in lab instructions
  const char *strings[] = {"Dx","Db","Dz","Dk","Aa","Wu","Wa","Zw","Za","wk","Wa","WW","W8","W_","Bro"};

  // Loop through strings and add them to the appropriate lists
  HeaderD** ppStruct7 = &pStruct7;
  for (int i = 0; i < 14; i++){
    if (InsertNewObject(ppStruct7, (char*)strings[i], randomlx(0, 999999)) == 0) {
      printf("InsertNewObject(): failed! Could not add %s \n\n", strings[i]);
    }
  }
  PrintObjects(pStruct7);

  Object4* pObjectTrash;
  // Loop through strings and remove them from lists
  for (int i = 0; i < 15; i++){
    pObjectTrash = RemoveExistingObject(ppStruct7, (char*)strings[i]);
    if (pObjectTrash == NULL)
    {
      printf("Could remove ID: %s\n", strings[i]);
    }
  }
  PrintObjects(pStruct7);

  Node *pBinaryTree = CreateBinaryTree(pStruct7);
  TreeTraversal(pBinaryTree);
  return 0;
}

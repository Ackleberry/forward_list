#include "stdio.h"
#include "forward_list_test_helper.h"

void TestHelper_PrintList(FwdList_t *pObj)
{
    if (FwdList_IsEmpty(pObj))
    {
        printf("H --> NULL\n");
        printf("T --> NULL\n");
    }
    else
    {
        for (FwdList_Node_t *pCur = pObj->pHead; pCur != NULL; pCur = pCur->pNext)
        {
            printf("        -------------------\n");
            if (pObj->pHead == pCur && pObj->pTail == pCur)
            {
                printf("H&T --> | Node: %p\n", pCur);
            }
            else if (pObj->pHead == pCur)
            {
                printf(" H  --> | Node: %p\n", pCur);
            }
            else if (pObj->pTail == pCur)
            {
                printf(" T  --> | Node: %p\n", pCur);
            }
            else
            {
                printf("        | Node: %p\n", pCur);
            }
            printf("        | Data: 0x");
            /* Pop the data off the list one byte at a time */
            for (size_t byte = pObj->dataSize - 1; byte < pObj->dataSize; byte--)
            {
                printf("%X", pCur->pData[byte]);
            }
            printf("\n        -------------------\n");
            printf("                |\n");
            printf("                V\n");
        }
        printf("               NULL\n");
    }
    printf("***************************\n");
}
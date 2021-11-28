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

FwdList_Insert_e TestHelper_OrderNumUp(void *pListDataVoid, void *pUserDataVoid)
{
    uint32_t *pUserData = pUserDataVoid;
    uint32_t *pListData = pListDataVoid;

    return (*pUserData >= *pListData) ? FwdList_Insert_Skip : FwdList_Insert_Before;
}

FwdList_Insert_e TestHelper_OrderNumDown(void *pListDataVoid, void *pUserDataVoid)
{
    uint32_t *pUserData = pUserDataVoid;
    uint32_t *pListData = pListDataVoid;
    FwdList_Insert_e retVal;

    if (*pUserData >= *pListData)
    {
        retVal = FwdList_Insert_Before;
    }
    else
    {
        retVal = FwdList_Insert_Skip;
    }

    return retVal;
}

FwdList_Insert_e TestHelper_GroupEvenAndOdd(void *pListDataVoid, void *pUserDataVoid)
{
    uint32_t *pUserData = pUserDataVoid;
    uint32_t *pListData = pListDataVoid;
    FwdList_Insert_e retVal;

    /* Even - Even */
    if ((*pUserData % 2 == 0) && (*pListData % 2 == 0))
    {
        retVal = FwdList_Insert_Skip;
    }
    /* Odd - Odd */
    else if ((*pUserData % 2 == 1) && (*pListData % 2 == 1))
    {
        retVal = FwdList_Insert_Skip;
    }
    /* Even - Odd */
    else if ((*pUserData % 2 == 0) && (*pListData % 2 == 1))
    {
        retVal = FwdList_Insert_Before;
    }
    /* Odd - Even */
    else
    {
        retVal = FwdList_Insert_Skip;
    }

    return retVal;
}

FwdList_Insert_e TestHelper_GroupEvenAndOddUp(void *pListDataVoid, void *pUserDataVoid)
{
    uint32_t *pUserData = pUserDataVoid;
    uint32_t *pListData = pListDataVoid;
    FwdList_Insert_e retVal;

    /* Even - Even */
    if ((*pUserData % 2 == 0) && (*pListData % 2 == 0))
    {
        if (*pUserData <= *pListData)
        {
            retVal = FwdList_Insert_Before;
        }
        else
        {
            retVal = FwdList_Insert_Skip;
        }
    }
    /* Odd - Odd */
    else if ((*pUserData % 2 == 1) && (*pListData % 2 == 1))
    {
        if (*pUserData >= *pListData)
        {
            retVal = FwdList_Insert_Skip;
        }
        else
        {
            retVal = FwdList_Insert_Before;
        }
    }
    /* Even - Odd */
    else if ((*pUserData % 2 == 0) && (*pListData % 2 == 1))
    {
        retVal = FwdList_Insert_Before;
    }
    /* Odd - Even */
    else
    {
        retVal = FwdList_Insert_Skip;
    }

    return retVal;
}

FwdList_Insert_e TestHelper_GroupEvenAndOddDown(void *pListDataVoid, void *pUserDataVoid)
{
    uint32_t *pUserData = pUserDataVoid;
    uint32_t *pListData = pListDataVoid;
    FwdList_Insert_e retVal;

    /* Even - Even */
    if ((*pUserData % 2 == 0) && (*pListData % 2 == 0))
    {
        if (*pUserData >= *pListData)
        {
            retVal = FwdList_Insert_Before;
        }
        else
        {
            retVal = FwdList_Insert_Skip;
        }
    }
    /* Odd - Odd */
    else if ((*pUserData % 2 == 1) && (*pListData % 2 == 1))
    {
        if (*pUserData <= *pListData)
        {
            retVal = FwdList_Insert_Skip;
        }
        else
        {
            retVal = FwdList_Insert_Before;
        }
    }
    /* Even - Odd */
    else if ((*pUserData % 2 == 0) && (*pListData % 2 == 1))
    {
        retVal = FwdList_Insert_Before;
    }
    /* Odd - Even */
    else
    {
        retVal = FwdList_Insert_Skip;
    }

    return retVal;
}

FwdList_Insert_e TestHelper_AddAfter(void *pListDataVoid, void *pUserDataVoid)
{
    FwdList_Insert_e retVal;
    uint32_t *pListData = pListDataVoid;

    /* Random value picked */
    if (*pListData == 3)
    {
        retVal = FwdList_Insert_After;
    }
    else
    {
        retVal = FwdList_Insert_Skip;
    }

    return retVal;
}
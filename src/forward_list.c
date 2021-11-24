/*******************************************************************************
 * @file  forward_list.c
 *
 * @brief  Singly linked list implementation
 *
 * @author  Brooks Anderson <bilbrobaggins@gmail.com>
 ******************************************************************************/

/*============================================================================*
 *                              I N C L U D E S                               *
 *============================================================================*/
#include "forward_list.h"

void            FreeList_PushFront(FwdList_t *pObj, FwdList_Node_t *pNode);
FwdList_Node_t *FreeList_PopFront(FwdList_t *pObj);
bool            FreeList_IsEmpty(FwdList_t *pObj);

/*============================================================================*
 *                      P U B L I C    F U N C T I O N S                      *
 *============================================================================*/

void FwdList_Init(FwdList_t *pObj, void *pNodeBuf, size_t nodeBufSize,
                  void *pDataBuf, size_t dataBufSize, size_t dataSize)
{
    pObj->pHead       = NULL;
    pObj->pTail       = NULL;
    pObj->pFreeHead   = NULL;
    pObj->pFreeTail   = NULL;
    pObj->pNodeBuf    = pNodeBuf;
    pObj->nodeBufSize = nodeBufSize;
    pObj->pDataBuf    = pDataBuf;
    pObj->dataBufSize = dataBufSize;
    pObj->dataSize    = dataSize;

    /* Initailize and push all nodes onto the free list */
    size_t totalNodes = (pObj->nodeBufSize / sizeof(FwdList_Node_t));
    for (size_t node = 0; node < totalNodes; node++)
    {
        /* Make each node point to its data section */
        pObj->pNodeBuf[node].pData = &pObj->pDataBuf[node * pObj->dataSize];

        FreeList_PushFront(pObj, &pObj->pNodeBuf[node]);
    }
}

bool FwdList_IsEmpty(FwdList_t *pObj)
{
    return ((pObj->pHead == NULL) && (pObj->pTail == NULL));
}

bool FwdList_IsFull(FwdList_t *pObj)
{
    return FreeList_IsEmpty(pObj);
}

FwdList_Error_e FwdList_PushFront(FwdList_t *pObj, void *pDataInVoid)
{
    FwdList_Error_e err = FwdList_Error_None;

    FwdList_Node_t *pNode = FreeList_PopFront(pObj);

    if (pNode == NULL)
    {
        err = FwdList_Error;
    }
    else
    {
        /* Push the data into the list one byte at a time */
        for (size_t byte = 0; byte < pObj->dataSize; byte++)
        {
            pNode->pData[byte] = ((uint8_t *)pDataInVoid)[byte];
        }

        if (FwdList_IsEmpty(pObj))
        {
            pNode->pNext = NULL;
            pObj->pTail = pNode;
        }
        else
        {
            pNode->pNext = pObj->pHead;
        }

        pObj->pHead = pNode;
    }

    return err;
}

FwdList_Error_e FwdList_PushBack(FwdList_t *pObj, void *pDataInVoid)
{
    FwdList_Error_e err = FwdList_Error_None;

    FwdList_Node_t *pNode = FreeList_PopFront(pObj);

    if (pNode == NULL)
    {
        err = FwdList_Error;
    }
    else
    {
        /* Push the data into the list one byte at a time */
        for (size_t byte = 0; byte < pObj->dataSize; byte++)
        {
            pNode->pData[byte] = ((uint8_t *)pDataInVoid)[byte];
        }

        if (FwdList_IsEmpty(pObj))
        {
            pObj->pHead = pNode;
        }
        else
        {
            pObj->pTail->pNext = pNode;
        }

        pObj->pTail         = pNode;
        pObj->pTail->pNext  = NULL;
    }

    return err;
}

FwdList_Error_e FwdList_PopFront(FwdList_t *pObj, void *pDataOutVoid)
{
    FwdList_Error_e err = FwdList_Error_None;

    if (FwdList_IsEmpty(pObj))
    {
        err = FwdList_Error;
    }
    else
    {
        /* Pop the data off the list one byte at a time */
        for (size_t byte = 0; byte < pObj->dataSize; byte++)
        {
            ((uint8_t *)pDataOutVoid)[byte] = pObj->pHead->pData[byte];
        }

        FwdList_Node_t *pNewHead = pObj->pHead->pNext;
        FreeList_PushFront(pObj, pObj->pHead);
        pObj->pHead = pNewHead;

        /* Only 1 node exists, update the tail */
        if (pObj->pHead == NULL)
        {
            pObj->pTail = NULL;
        }
    }

    return err;
}

FwdList_Error_e FwdList_PopBack(FwdList_t *pObj, void *pDataOutVoid)
{
    FwdList_Error_e err = FwdList_Error_None;

    if (FwdList_IsEmpty(pObj))
    {
        err = FwdList_Error;
    }
    else
    {
        /* Pop the data off the list one byte at a time */
        for (size_t byte = 0; byte < pObj->dataSize; byte++)
        {
            ((uint8_t *)pDataOutVoid)[byte] = pObj->pTail->pData[byte];
        }

        FwdList_Node_t *pNewTail = pObj->pHead;
        if (pNewTail->pNext == NULL)
        {
            /* Only 1 node exists */
            FreeList_PushFront(pObj, pObj->pTail);
            pObj->pHead = NULL;
            pObj->pTail = NULL;
        }
        else
        {
            /* Find the node before the tail */
            while (pNewTail->pNext != pObj->pTail)
            {
                pNewTail = pNewTail->pNext;
            }

            FreeList_PushFront(pObj, pObj->pTail);
            pNewTail->pNext = NULL;
            pObj->pTail = pNewTail;
        }
    }

    return err;
}

FwdList_Error_e FwdList_PeekFront(FwdList_t *pObj, void *pDataOutVoid)
{
    FwdList_Error_e err = FwdList_Error_None;
    FwdList_Node_t *pHead = pObj->pHead;
    FwdList_Node_t *pTail = pObj->pTail;

    err = FwdList_PopFront(pObj, pDataOutVoid);

    if (err == FwdList_Error_None)
    {
        pObj->pHead = pHead;
        pObj->pTail = pTail;
    }
    return err;
}

FwdList_Error_e FwdList_PeekBack(FwdList_t *pObj, void *pDataOutVoid)
{
    FwdList_Error_e err = FwdList_Error_None;
    FwdList_Node_t *pHead = pObj->pHead;
    FwdList_Node_t *pTail = pObj->pTail;

    err = FwdList_PopBack(pObj, pDataOutVoid);

    if (err == FwdList_Error_None)
    {
        pObj->pHead = pHead;
        pObj->pTail = pTail;
    }

    return err;
}

/*============================================================================*
 *                     P R I V A T E    F U N C T I O N S                     *
 *============================================================================*/

void FreeList_PushFront(FwdList_t *pObj, FwdList_Node_t *pNode)
{
    if (pNode != NULL)
    {
        if (pObj->pFreeHead == NULL)
        {
            pNode->pNext = NULL;
            pObj->pFreeTail = pNode;
        }
        else
        {
            pNode->pNext = pObj->pFreeHead;
        }

        pObj->pFreeHead = pNode;
    }
}

FwdList_Node_t *FreeList_PopFront(FwdList_t *pObj)
{
    FwdList_Node_t *pFreeNode;

    if (FreeList_IsEmpty(pObj))
    {
        pFreeNode = NULL;
    }
    else
    {
        pFreeNode = pObj->pFreeHead;
        FwdList_Node_t *pNewFreeHead = pObj->pFreeHead->pNext;

        if (pNewFreeHead == NULL)
        {
            pObj->pFreeTail = NULL;
        }
        else
        {
            pObj->pFreeHead->pNext = NULL;
        }

        pObj->pFreeHead = pNewFreeHead;
    }

    return pFreeNode;
}

bool FreeList_IsEmpty(FwdList_t *pObj)
{
    return ((pObj->pFreeHead == NULL) && (pObj->pFreeTail == NULL));
}

bool FreeList_IsFull(FwdList_t *pObj)
{
    return FwdList_IsEmpty(pObj);
}
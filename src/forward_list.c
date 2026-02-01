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

void            _FwdList_Free(FwdList_t *pObj, FwdList_Node_t *pNode);
FwdList_Node_t *_FwdList_Alloc(FwdList_t *pObj);

/*============================================================================*
 *                      P U B L I C    F U N C T I O N S                      *
 *============================================================================*/

void FwdList_Init(FwdList_t *pObj, void *pNodeBuf, size_t nodeBufSize,
                  void *pDataBuf, size_t dataBufSize, size_t dataSize)
{
    pObj->pHead       = NULL;
    pObj->pTail       = NULL;
    pObj->count       = 0;

    pObj->pFreeHead   = NULL;

    pObj->pNodeBuf    = pNodeBuf;
    pObj->nodeBufSize = nodeBufSize;

    pObj->pDataBuf    = pDataBuf;
    pObj->dataBufSize = dataBufSize;
    pObj->dataSize    = dataSize;

    /* Push all nodes onto the available memory list */
    size_t totalNodes = (pObj->nodeBufSize / sizeof(FwdList_Node_t));
    for (size_t node = 0; node < totalNodes; node++)
    {
        /* Make each node point to its cooresponding data section */
        pObj->pNodeBuf[node].pData = &pObj->pDataBuf[node * pObj->dataSize];
        _FwdList_Free(pObj, &pObj->pNodeBuf[node]);
    }
}

bool FwdList_IsEmpty(FwdList_t *pObj)
{
    return ((pObj->pHead == NULL) && (pObj->pTail == NULL));
}

bool FwdList_IsFull(FwdList_t *pObj)
{
    return pObj->count == (pObj->nodeBufSize / sizeof(FwdList_Node_t));
}

size_t FwdList_Count(FwdList_t *pObj)
{
    return pObj->count;
}

FwdList_Error_e FwdList_PushFront(FwdList_t *pObj, void *pDataInVoid)
{
    FwdList_Error_e err = FwdList_Error_None;

    FwdList_Node_t *pNode = _FwdList_Alloc(pObj);

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
        pObj->count++;
    }

    return err;
}

FwdList_Error_e FwdList_PushBack(FwdList_t *pObj, void *pDataInVoid)
{
    FwdList_Error_e err = FwdList_Error_None;

    FwdList_Node_t *pNode = _FwdList_Alloc(pObj);

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
        pObj->count++;
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
        _FwdList_Free(pObj, pObj->pHead);
        pObj->pHead = pNewHead;

        /* Only 1 node exists, update the tail */
        if (pObj->pHead == NULL)
        {
            pObj->pTail = NULL;
        }
        pObj->count--;
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
            _FwdList_Free(pObj, pObj->pTail);
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

            _FwdList_Free(pObj, pObj->pTail);
            pNewTail->pNext = NULL;
            pObj->pTail = pNewTail;
        }
        pObj->count--;
    }

    return err;
}

FwdList_Error_e FwdList_PeekFront(FwdList_t *pObj, void *pDataOutVoid)
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
    }

    return err;
}

FwdList_Error_e FwdList_PeekBack(FwdList_t *pObj, void *pDataOutVoid)
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
    }

    return err;
}

FwdList_Error_e FwdList_Reverse(FwdList_t *pObj)
{
    FwdList_Error_e err = FwdList_Error_None;

    FwdList_Node_t *pPrev = NULL;
    FwdList_Node_t *pCurr = NULL;
    FwdList_Node_t *pNext = pObj->pHead;
    while (pNext != NULL)
    {
        /* Advance cursors */
        pPrev = pCurr;
        pCurr = pNext;
        pNext = pNext->pNext;

        /* Reverse current node */
        pCurr->pNext = pPrev;
    }

    /* Update head and tail pointers */
    pObj->pTail = pObj->pHead;
    pObj->pHead = pCurr;

    return err;
}

FwdList_Iter_t FwdList_Begin(FwdList_t *pObj)
{
    FwdList_Iter_t iter;

    iter.index = 0;
    iter.pData = (pObj->pHead != NULL) ? pObj->pHead->pData : NULL;
    iter._pNext = (pObj->pHead != NULL) ? pObj->pHead->pNext : NULL;

    return iter;
}

void FwdList_Next(FwdList_Iter_t *pIter)
{
    if (pIter != NULL) {
        pIter->index++;
        FwdList_Node_t *pNode = (FwdList_Node_t *)pIter->_pNext;
        pIter->pData = (pNode != NULL) ? pNode->pData : NULL;
        pIter->_pNext = (pNode != NULL) ? pNode->pNext : NULL;
    }
}

/*============================================================================*
 *                     P R I V A T E    F U N C T I O N S                     *
 *============================================================================*/

/*******************************************************************************
 * @brief  Adds a node onto the available memory list
 *
 * @details  This function emulates free() but operates within the user
 *           provided memory pool.
 *
 * @param pObj   Pointer to the forward list object
 * @param pNode  Pointer to the node that will be added to the free list
 ******************************************************************************/
void _FwdList_Free(FwdList_t *pObj, FwdList_Node_t *pNode)
{
    if (pNode != NULL)
    {
        pNode->pNext = (pObj->pFreeHead == NULL) ? NULL : pObj->pFreeHead;
        pObj->pFreeHead = pNode;
    }
}

/*******************************************************************************
 * @brief  Removes a node from the available memory list.
 *
 * @details  This function emulates malloc() but operates within the user
 *           provided memory pool.
 *
 * @param pObj  Pointer to the forward list object
 *
 * @returns Pointer to the next available node. NULL if no node is available.
 ******************************************************************************/
FwdList_Node_t *_FwdList_Alloc(FwdList_t *pObj)
{
    FwdList_Node_t *pFreeNode;

    if (pObj->pFreeHead == NULL)
    {
        pFreeNode = NULL;
    }
    else
    {
        pFreeNode = pObj->pFreeHead;
        FwdList_Node_t *pNewFreeHead = pFreeNode->pNext;
        pFreeNode->pNext = NULL;
        pObj->pFreeHead = pNewFreeHead;
    }

    return pFreeNode;
}

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

FwdList_Node_t *FwdList_GetFreeNode(FwdList_t *pObj);

/*============================================================================*
 *                      P U B L I C    F U N C T I O N S                      *
 *============================================================================*/

void FwdList_Init(FwdList_t *pObj, void *pNodeBuf, size_t nodeBufSize,
                  void *pDataBuf, size_t dataBufSize, size_t dataSize)
{
    pObj->pHead = NULL;
    pObj->pTail = NULL;

    pObj->pNodeBuf    = pNodeBuf;
    pObj->nodeBufSize = nodeBufSize;

    pObj->pDataBuf    = pDataBuf;
    pObj->dataBufSize = dataBufSize;
    pObj->dataSize    = dataSize;

    pObj->nodesInUse  = 0;

    size_t totalNodes = (pObj->nodeBufSize / sizeof(FwdList_Node_t));
    for (size_t node = 0; node < totalNodes; node++)
    {
        pObj->pNodeBuf[node].inUse = false;
    }
}

bool FwdList_IsEmpty(FwdList_t *pObj)
{
    return (pObj->pHead == NULL);
}

bool FwdList_IsFull(FwdList_t *pObj)
{
    return (pObj->nodesInUse == (pObj->nodeBufSize / sizeof(FwdList_Node_t)));
}

FwdList_Error_e FwdList_PushFront(FwdList_t *pObj, void *pDataInVoid)
{
    FwdList_Error_e err = FwdList_Error_None;

    FwdList_Node_t *pNode = FwdList_GetFreeNode(pObj);

    if (pNode != NULL)
    {
        pNode->inUse = true;
        pObj->nodesInUse++;

        /* Push the data into the list one byte at a time */
        uint8_t *pDataIn = (uint8_t *)pDataInVoid;
        for (size_t byte = 0; byte < pObj->dataSize; byte++)
        {
            pNode->pData[byte] = pDataIn[byte];
        }

        if (pObj->pHead != NULL)
        {
            pNode->pNext = pObj->pHead;
        }
        else
        {
            pNode->pNext = NULL;
            pObj->pTail = pNode;
        }

        pObj->pHead = pNode;
    }
    else
    {
        err = FwdList_Error;
    }

    return err;
}

FwdList_Error_e FwdList_PushBack(FwdList_t *pObj, void *pDataInVoid)
{
    FwdList_Error_e err = FwdList_Error_None;

    FwdList_Node_t *pNode = FwdList_GetFreeNode(pObj);

    if (pNode != NULL)
    {
        pNode->inUse = true;
        pObj->nodesInUse++;

        /* Push the data into the list one byte at a time */
        uint8_t *pDataIn = (uint8_t *)pDataInVoid;
        for (size_t byte = 0; byte < pObj->dataSize; byte++)
        {
            pNode->pData[byte] = pDataIn[byte];
        }

        pNode->pNext  = NULL;

        if (pObj->pTail != NULL)
        {
            pObj->pTail->pNext = pNode;
        }
        else
        {
            pObj->pHead = pNode;
        }

        pObj->pTail = pNode;
    }
    else
    {
        err = FwdList_Error;
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
        FwdList_Node_t *pNewHead = pObj->pHead->pNext;
        pObj->pHead->pNext      = NULL;

        /* Pop the data off the list one byte at a time */
        uint8_t *pDataOut = (uint8_t *)pDataOutVoid;
        for (size_t byte = 0; byte < pObj->dataSize; byte++)
        {
            pDataOut[byte] = pObj->pHead->pData[byte];
        }

        pObj->pHead->inUse = false;
        pObj->nodesInUse--;
        pObj->pHead = pNewHead;
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
        uint8_t *pDataOut = (uint8_t *)pDataOutVoid;
        for (size_t byte = 0; byte < pObj->dataSize; byte++)
        {
            pDataOut[byte] = pObj->pTail->pData[byte];
        }

        /* Find the new tail node */
        FwdList_Node_t *pNewTail = pObj->pHead;
        while ((pNewTail->pNext != NULL) && (pNewTail->pNext != pObj->pTail))
        {
            pNewTail = pNewTail->pNext;
        }

        /* Only 1 node exists */
        if (pNewTail->pNext == NULL)
        {
            pObj->pHead->inUse = false;
            pObj->nodesInUse--;
            pObj->pHead = NULL;
            pObj->pTail = NULL;
        }
        else
        {
            pObj->pTail->inUse = false;
            pObj->nodesInUse--;
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

FwdList_Node_t *FwdList_GetFreeNode(FwdList_t *pObj)
{
    /* Find the first free node starting from the beginning of the node buffer */
    FwdList_Node_t *pFreeNode = NULL;

    size_t totalNodes = (pObj->nodeBufSize / sizeof(FwdList_Node_t));
    for (size_t node = 0; node < totalNodes; node++)
    {
        if (pObj->pNodeBuf[node].inUse == false)
        {
            pFreeNode = &pObj->pNodeBuf[node];

            /* Make the node points its data section */
            pFreeNode->pData = &pObj->pDataBuf[node * pObj->dataSize];
            break;
        }
    }

    return pFreeNode;
}
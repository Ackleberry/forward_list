/*******************************************************************************
 * @file  forward_list.h
 *
 * @brief  Singly linked list function prototypes
 *
 * @author  Brooks Anderson <bilbrobaggins@gmail.com>
 ******************************************************************************/

#ifndef FORWARD_LIST_H_INCLUDED
#define FORWARD_LIST_H_INCLUDED

/*============================================================================*
 *                              I N C L U D E S                               *
 *============================================================================*/
#include <stddef.h>
#include <stdbool.h>

#include "forward_list_t.h"

/*============================================================================*
 *                 F U N C T I O N    D E C L A R A T I O N S                 *
 *============================================================================*/

/*******************************************************************************
 * @brief  Initializes the forward list object
 *
 * @details  The caller is responsible for allocating the list object, and
 *           deque buffer.
 *
 * @param pObj         Pointer to the forward list object
 * @param pNodeBuf     Pointer to the node buffer
 * @param nodeBufSize  Size of the node buffer. Must be an integer multiple of
 *                     d
 * @param pDataBuf     Pointer to the data buffer
 * @param dataBufSize  Size of the data buffer. Must be an integer multiple of
 *                     dataSize.
 * @param dataSize     Size of the data type being stored by the list
 ******************************************************************************/
void FwdList_Init(FwdList_t *pObj, void *pNodeBuf, size_t nodeBufSize,
                  void *pDataBuf, size_t dataBufSize, size_t dataSize);

/*******************************************************************************
 * @brief  Check if the deque is empty
 *
 * @param pObj  Pointer to the deque object
 *
 * @returns true if empty
 ******************************************************************************/
bool FwdList_IsEmpty(FwdList_t *pObj);

/*******************************************************************************
 * @brief Check if the deque is full
 *
 * @param pObj  Pointer to the deque object
 *
 * @returns true if full
 ******************************************************************************/
bool FwdList_IsFull(FwdList_t *pObj);

/*******************************************************************************
 * @brief  Pushes data onto the front of the deque
 *
 * @param pObj         Pointer to the deque object
 * @param pDataInVoid  Pointer to the data that will be pushed
 *
 * @returns Deque error flag
 ******************************************************************************/
FwdList_Error_e FwdList_PushFront(FwdList_t *pObj, void *pDataInVoid);

/*******************************************************************************
 * @brief  Pushes data onto the back of the deque
 *
 * @details This function is equivalent to a Queue_Push(), Stack_Push()
 *
 * @param pObj         Pointer to the deque object
 * @param pDataInVoid  Pointer to the data that will be pushed
 *
 * @returns Deque error flag
 ******************************************************************************/
FwdList_Error_e FwdList_PushBack(FwdList_t *pObj, void *pDataInVoid);

/*******************************************************************************
 * @brief  Pops data member off the front of the deque
 *
 * @details This function is equivalent to a Queue_Pop()
 *
 * @param pObj          Pointer to the deque object
 * @param pDataOutVoid  Pointer to the data that will be popped
 *
 * @returns Deque error flag
 ******************************************************************************/
FwdList_Error_e FwdList_PopFront(FwdList_t *pObj, void *pDataOutVoid);

/*******************************************************************************
 * @brief  Pops data member off the rear of the deque
 *
 * @details This function is equivalent to a Stack_Pop()
 *
 * @param pObj          Pointer to the deque object
 * @param pDataOutVoid  Pointer to the data that will be popped
 *
 * @returns Deque error flag
 ******************************************************************************/
FwdList_Error_e FwdList_PopBack(FwdList_t *pObj, void *pDataOutVoid);

/*******************************************************************************
 * @brief  Peek at the data at the front of the deque
 *
 * @param  pObj          Pointer to the deque object
 * @param  pDataOutVoid  Pointer to the peeked data
 *
 * @returns Deque error flag
 ******************************************************************************/
FwdList_Error_e FwdList_PeekFront(FwdList_t *pObj, void *pDataOutVoid);

/*******************************************************************************
 * @brief  Peek at the data at the back of the deque
 *
 * @param  pObj          Pointer to the deque object
 * @param  pDataOutVoid  Pointer to the peeked data
 *
 * @returns Deque error flag
 ******************************************************************************/
FwdList_Error_e FwdList_PeekBack(FwdList_t *pObj, void *pDataOutVoid);


#endif /* FORWARD_LIST_H_INCLUDED */
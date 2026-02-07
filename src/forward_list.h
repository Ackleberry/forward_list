/*******************************************************************************
 * @file    forward_list.h
 *
 * @brief   Singly linked list function prototypes
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
 * @brief    Initializes the forward list object
 *
 * @details  The caller is responsible for allocating the list object, node and
 *           data buffers.
 *
 * @param pObj         Pointer to the forward list object
 * @param pNodeBuf     Pointer to the node buffer
 * @param nodeBufSize  Size of the node buffer.
 * @param pDataBuf     Pointer to the data buffer.
 * @param dataBufSize  Size of the data buffer.
 * @param dataSize     Size of the data type being stored by the list
 *
 * @note  Node and Data buffers must have the same number of elements. The data
 *        buffer must also be an integer multiple of `dataSize`.
 ******************************************************************************/
void FwdList_Init(FwdList_t *pObj, void *pNodeBuf, size_t nodeBufSize,
                  void *pDataBuf, size_t dataBufSize, size_t dataSize);

/*******************************************************************************
 * @brief  Check if the forward list is empty
 *
 * @param pObj  Pointer to the forward list object
 *
 * @returns true if empty
 ******************************************************************************/
bool FwdList_IsEmpty(FwdList_t *pObj);

/*******************************************************************************
 * @brief Returns the number of elements in the list
 *
 * @param pObj  Pointer to the forward list object
 *
 * @returns The number of elements in the list
 ******************************************************************************/
size_t FwdList_Count(FwdList_t *pObj);

/*******************************************************************************
 * @brief Check if the forward list is full
 *
 * @param pObj  Pointer to the forward list object
 *
 * @returns true if full
 ******************************************************************************/
bool FwdList_IsFull(FwdList_t *pObj);

/*******************************************************************************
 * @brief  Pushes data onto the front of the forward list
 *
 * @details  This function is equivalent to a Stack_Push()
 *
 * @param pObj         Pointer to the forward list object
 * @param pDataInVoid  Pointer to the data that will be pushed
 *
 * @returns forward list error flag
 ******************************************************************************/
FwdList_Error_e FwdList_PushFront(FwdList_t *pObj, void *pDataInVoid);

/*******************************************************************************
 * @brief  Pops data member off the front of the forward list
 *
 * @details  This function is equivalent to a Stack_Pop(), or Queue_Pop()
 *
 * @param pObj          Pointer to the forward list object
 * @param pDataOutVoid  Pointer to the data that will be popped
 *
 * @returns forward list error flag
 ******************************************************************************/
FwdList_Error_e FwdList_PopFront(FwdList_t *pObj, void *pDataOutVoid);

/*******************************************************************************
 * @brief  Pushes data onto the back of the forward list
 *
 * @details  This function is equivalent to a Queue_Push()
 *
 * @param pObj         Pointer to the forward list object
 * @param pDataInVoid  Pointer to the data that will be pushed
 *
 * @returns forward list error flag
 ******************************************************************************/
FwdList_Error_e FwdList_PushBack(FwdList_t *pObj, void *pDataInVoid);

/*******************************************************************************
 * @brief  Pops data member off the rear of the forward list
 *
 * @note   Use with caution. Singly linked lists back pops are not efficient!
 *         This function has O(N) complexity.
 *
 * @param pObj          Pointer to the forward list object
 * @param pDataOutVoid  Pointer to the data that will be popped
 *
 * @returns forward list error flag
 ******************************************************************************/
FwdList_Error_e FwdList_PopBack(FwdList_t *pObj, void *pDataOutVoid);

/*******************************************************************************
 * @brief  Peek at the data at the front of the forward list
 *
 * @param  pObj          Pointer to the forward list object
 * @param  pDataOutVoid  Pointer to the peeked data
 *
 * @returns forward list error flag
 ******************************************************************************/
FwdList_Error_e FwdList_PeekFront(FwdList_t *pObj, void *pDataOutVoid);

/*******************************************************************************
 * @brief  Peek at the data at the back of the forward list
 *
 * @param  pObj          Pointer to the forward list object
 * @param  pDataOutVoid  Pointer to the peeked data
 *
 * @returns forward list error flag
 ******************************************************************************/
FwdList_Error_e FwdList_PeekBack(FwdList_t *pObj, void *pDataOutVoid);

/*******************************************************************************
 * @brief  Reverses the node order of the forward list
 *
 * @param  pObj  Pointer to the forward list object
 *
 * @returns forward list error flag
 ******************************************************************************/
FwdList_Error_e FwdList_Reverse(FwdList_t *pObj);

/*******************************************************************************
 * @brief  Returns an iterator to the beginning of the list
 *
 * @param  pObj  Pointer to the forward list object
 *
 * @returns Iterator object
 ******************************************************************************/
FwdList_Iter_t FwdList_Begin(FwdList_t *pObj);

/*******************************************************************************
 * @brief  Advances an iterator to the next list item
 *
 * @param  pIter  Pointer to the iterator object
 ******************************************************************************/
void FwdList_Next(FwdList_Iter_t *pIter);

/*******************************************************************************
 * @brief  Inserts data before iterator. Iterator is updated to point to the
 *         newly inserted data.
 *
 * @param pObj         Pointer to the forward list object
 * @param pIter        Pointer to the list iterator. 
 * @param pDataInVoid  Pointer to the data that will be pushed
 *
 * @returns forward list error flag
 ******************************************************************************/
FwdList_Error_e FwdList_Insert(FwdList_t *pObj, FwdList_Iter_t *pIter, void *pDataInVoid);

/**
 * Possible Functions:
 * FwdList_Remove(<obj>, <pos>)

 * 
 * Possible Insert/Get/Remove Use Cases:
 * > We don't want the caller to use get() for iteration since its O(n) and iteration is already O(n), makine O(n^2)
 * > Best part is removal doesn't have to free()
 * > Whats the best way to remove items from the list? Iteration? Get/Remove for loop?
 * > FwdList_PeekFront and FwdList_PeekBack are not really needed if we have get()
 * > Get() shouldn't really be in the API because it promotes bad iteration practice.
 * > C++ forward list does not have insert() only insertAfter()
 * > Use a forward list only if you don't need to insert before
 * > Doubly linked list in C++ does not have an insert_after() because you can just advance the iterator.
 */

#endif /* FORWARD_LIST_H_INCLUDED */
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
 * @brief  Inserts data into the linked list
 *
 * @details  For an insert to take place, a compare function is needed to help
 *           find the desired node to perform the insertion on. Depending on the
 *           compare functions return value, the insertion can be before or
 *           after the found node.
 *
 * @param pObj         Pointer to the forward list object
 * @param pCompFn      Caller defined compare function that determines which
 *                     node to get. See function signature for `CompareFnPtr_t`.
 * @param pDataInVoid  Pointer to the data that will be used in the comparison
 *
 * @returns forward list error flag
 ******************************************************************************/
FwdList_Error_e FwdList_Insert(FwdList_t *pObj, CompareFnPtr_t pCompFn,
                                                void *pDataInVoid);

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

#endif /* FORWARD_LIST_H_INCLUDED */
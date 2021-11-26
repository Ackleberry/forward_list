/*******************************************************************************
 * @file  deque_t.h
 *
 * @brief  Singly linked list type definitions
 *
 * @author Brooks Anderson <bilbrobaggins@gmail.com>
 ******************************************************************************/
#ifndef FORWARD_LIST_T_H_INCLUDED
#define FORWARD_LIST_T_H_INCLUDED

/*============================================================================*
 *                              I N C L U D E S                               *
 *============================================================================*/
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/*============================================================================*
 *                                D E F I N E S                               *
 *============================================================================*/

/*============================================================================*
 *                           E N U M E R A T I O N S                          *
 *============================================================================*/

/**
 * @brief Error flag
**/
typedef enum FwdList_Error_e
{
    FwdList_Error_None = 0,
    FwdList_Error      = 1,
} FwdList_Error_e;

/*============================================================================*
 *                             S T R U C T U R E S                            *
 *============================================================================*/

/*******************************************************************************
 * @brief  Data agnostic compare function pointer that compares 2
 *
 * @param pObj           Pointer to the forward list object
 * @param pListDataVoid  Node data within the list that is compared to user data
 * @param pUserDataVoid  User data that is compared to the existing list data
 *
 * @returns true, if the comparison is met
 ******************************************************************************/
typedef bool (*CompareFnPtr_t)(void *pListDataVoid, void *pUserDataVoid);

typedef struct FwdList_Node_t
{
    struct FwdList_Node_t *pNext;
    uint8_t               *pData;
} FwdList_Node_t;

/**
 * @brief  Singly Linked List Object
 *
 * @note   This object should never be directly manipulated by the caller.
**/
typedef struct FwdList_t
{
    FwdList_Node_t *pHead;          /*!< Head node cursor */
    FwdList_Node_t *pTail;          /*!< Tail node cursor */
    FwdList_Node_t *pFreeHead;      /*!< Head cursor for free nodes */
    FwdList_Node_t *pFreeTail;      /*!< Tail cursor for free nodes */
    FwdList_Node_t *pNodeBuf;       /*!< Pointer to the node buffer */
    uint8_t        *pDataBuf;       /*!< Pointer to the data buffer */
    size_t          nodeBufSize;    /*!< Size of the node buffer */
    size_t          dataBufSize;    /*!< Size of the data buffer */
    size_t          dataSize;       /*!< Size of the data type to be stored */
} FwdList_t;

#endif /* FORWARD_LIST_T_H_INCLUDED */
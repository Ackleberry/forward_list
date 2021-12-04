/*******************************************************************************
 * @file  forward_list_t.h
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

/**
 * @brief Insert options
**/
typedef enum FwdList_Insert_e
{
    FwdList_Insert_Skip   = 0, /*!< Don't insert, skip to the next node. If last
                               node is skipped then insert at the end of list */
    FwdList_Insert_Before = 1, /*!< Insert before node that meets condition */
    FwdList_Insert_After  = 2, /*!< Insert after node that meets condition */
} FwdList_Insert_e;

/*============================================================================*
 *                             S T R U C T U R E S                            *
 *============================================================================*/

typedef struct FwdList_Node_t
{
    struct FwdList_Node_t *pNext; /*!< Pointer to the next node in the list */
    uint8_t               *pData; /*!< Pointer to nodes data */
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

/*============================================================================*
 *                     F U N C T I O N    P O I N T E R S                     *
 *============================================================================*/

/*******************************************************************************
 * @brief   Data agnostic compare function pointer
 *
 * @details The caller must define this function so the module knows the
 *          insertion strategy.
 *          Examples: ascending, decending, alphabetical, etc
 *
 * @param pListDataVoid  Node data within the list that is compared to user data
 * @param pUserDataVoid  User data that is compared to the existing list data
 *
 * @returns FwdList_Insert_e
 ******************************************************************************/
typedef FwdList_Insert_e (*CompareFnPtr_t)(void *pListDataVoid,
                                           void *pUserDataVoid);

#endif /* FORWARD_LIST_T_H_INCLUDED */
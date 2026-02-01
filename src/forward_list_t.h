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

/*============================================================================*
 *                             S T R U C T U R E S                            *
 *============================================================================*/

typedef struct FwdList_Node_t
{
    uint8_t               *pData; /*!< Pointer to nodes data */
    struct FwdList_Node_t *pNext; /*!< Pointer to the next node in the list */
} FwdList_Node_t;

/**
 * Holds the state of a list iteration
 */
typedef struct FwdList_Iter_t
{
    size_t          index;  /*!< Current index */
    void           *pData;  /*!< Pointer to the current data */
    void           *_pNext; /*!< For internal use only */
} FwdList_Iter_t;

/**
 * @brief  Singly Linked List Object
 *
 * @note   This object should never be directly manipulated by the caller.
**/
typedef struct FwdList_t
{
    FwdList_Node_t *pHead;          /*!< Head node cursor */
    FwdList_Node_t *pTail;          /*!< Tail node cursor */
    size_t          count;          /*!< Number of in use nodes */
    FwdList_Node_t *pFreeHead;      /*!< Head cursor for free nodes */
    FwdList_Node_t *pNodeBuf;       /*!< Pointer to the node buffer */
    uint8_t        *pDataBuf;       /*!< Pointer to the data buffer */
    size_t          nodeBufSize;    /*!< Size of the node buffer */
    size_t          dataBufSize;    /*!< Size of the data buffer */
    size_t          dataSize;       /*!< Size of the data type to be stored */
} FwdList_t;

#endif /* FORWARD_LIST_T_H_INCLUDED */
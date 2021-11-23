#ifndef FORDWARD_LIST_SUITE_INCLUDED
#define FORDWARD_LIST_SUITE_INCLUDED

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "greatest.h"
#include "forward_list_test_helper.h"
#include "forward_list.h"

/* Declare a local suite. */
SUITE(FwdList_Suite);

TEST List_can_report_empty(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    /*****************     Act       *****************/
    bool isEmpty = FwdList_IsEmpty(&list);

    /*****************    Assert     *****************/
    ASSERT_EQ(true, isEmpty);

    PASS();
}

TEST List_can_report_not_full(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint8_t dataIn = 42;
    FwdList_PushFront(&list, &dataIn);

    /*****************     Act       *****************/
    bool isFull = FwdList_IsFull(&list);

    /*****************    Assert     *****************/
    ASSERT_EQ(false, isFull);

    PASS();
}

TEST List_can_report_not_empty_when_pushed_from_back(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint8_t dataIn = 42;
    FwdList_PushBack(&list, &dataIn);

    /*****************     Act       *****************/
    bool isEmpty = FwdList_IsEmpty(&list);

    /*****************    Assert     *****************/
    ASSERT_EQ(false, isEmpty);

    PASS();
}

TEST List_can_report_not_empty_when_pushed_from_front(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint8_t dataIn = 42;
    FwdList_PushFront(&list, &dataIn);

    /*****************     Act       *****************/
    bool isEmpty = FwdList_IsEmpty(&list);

    /*****************    Assert     *****************/
    ASSERT_EQ(false, isEmpty);

    PASS();
}

TEST List_can_report_full_when_pushed_from_back(void)
{
   /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint8_t dataIn = 42;
    FwdList_PushBack(&list, &dataIn);
    FwdList_PushBack(&list, &dataIn);
    FwdList_PushBack(&list, &dataIn);
    FwdList_PushBack(&list, &dataIn);

    /*****************     Act       *****************/
    bool isFull = FwdList_IsFull(&list);

    /*****************    Assert     *****************/
    ASSERT_EQ(true, isFull);

    PASS();
}

TEST List_can_report_full_when_pushed_from_front(void)
{
   /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint8_t dataIn = 42;
    FwdList_PushFront(&list, &dataIn);
    FwdList_PushFront(&list, &dataIn);
    FwdList_PushFront(&list, &dataIn);
    FwdList_PushFront(&list, &dataIn);

    /*****************     Act       *****************/
    bool isFull = FwdList_IsFull(&list);

    /*****************    Assert     *****************/
    ASSERT_EQ(true, isFull);

    PASS();
}

TEST List_front_pop_fails_if_underflow(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    /*****************     Act       *****************/
    uint8_t dataOut;
    FwdList_Error_e err = FwdList_PopFront(&list, &dataOut);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error, err);

    PASS();
}

TEST List_back_pop_fails_if_underflow(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    /*****************     Act       *****************/
    uint8_t dataOut;
    FwdList_Error_e err = FwdList_PopBack(&list, &dataOut);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error, err);

    PASS();
}

TEST List_back_push_fails_due_to_overflow_when_pushed_from_back(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    /* Fill the deque up */
    uint8_t dataIn = 5;
    FwdList_PushBack(&list, &dataIn);
    FwdList_PushBack(&list, &dataIn);
    FwdList_PushBack(&list, &dataIn);
    FwdList_PushBack(&list, &dataIn);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_PushBack(&list, &dataIn);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error, err);

    PASS();
}

TEST List_back_push_fails_due_to_overflow_when_pushed_from_front(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    /* Fill the deque up */
    uint8_t dataIn = 5;
    FwdList_PushFront(&list, &dataIn);
    FwdList_PushFront(&list, &dataIn);
    FwdList_PushFront(&list, &dataIn);
    FwdList_PushFront(&list, &dataIn);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_PushBack(&list, &dataIn);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error, err);

    PASS();
}

TEST List_front_push_fails_due_to_overflow_when_pushed_from_back(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    /* Fill the deque up */
    uint8_t dataIn = 5;
    FwdList_PushBack(&list, &dataIn);
    FwdList_PushBack(&list, &dataIn);
    FwdList_PushBack(&list, &dataIn);
    FwdList_PushBack(&list, &dataIn);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_PushFront(&list, &dataIn);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error, err);

    PASS();
}

TEST List_front_push_fails_due_to_overflow_when_pushed_from_front(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    /* Fill the deque up */
    uint8_t dataIn = 5;
    FwdList_PushFront(&list, &dataIn);
    FwdList_PushFront(&list, &dataIn);
    FwdList_PushFront(&list, &dataIn);
    FwdList_PushFront(&list, &dataIn);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_PushFront(&list, &dataIn);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error, err);

    PASS();
}

TEST List_can_front_pop_1_byte_data_types_when_pushed_from_back(void)
{
    /*****************    Arrange    *****************/
    uint8_t dataIn = 42;
    uint8_t dataOut;

    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));
    FwdList_PushBack(&list, &dataIn);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_PopFront(&list, &dataOut);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(dataIn, dataOut);

    PASS();
}

TEST List_can_front_pop_4_byte_data_types_when_pushed_from_back(void)
{
    /*****************    Arrange    *****************/
    uint32_t dataIn = 42;
    uint32_t dataOut;

    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint32_t       dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));
    FwdList_PushBack(&list, &dataIn);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_PopFront(&list, &dataOut);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(dataIn, dataOut);

    PASS();
}

TEST List_can_front_pop_1_byte_data_types_when_pushed_from_front(void)
{
    /*****************    Arrange    *****************/
    uint8_t dataIn = 42;
    uint8_t dataOut;

    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));
    FwdList_PushFront(&list, &dataIn);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_PopFront(&list, &dataOut);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(dataIn, dataOut);

    PASS();
}

TEST List_can_front_pop_4_byte_data_types_when_pushed_from_front(void)
{
    /*****************    Arrange    *****************/
    uint32_t dataIn = 42;
    uint32_t dataOut;

    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint32_t       dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));
    FwdList_PushFront(&list, &dataIn);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_PopFront(&list, &dataOut);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(dataIn, dataOut);

    PASS();
}

TEST List_can_back_pop_1_byte_data_types_when_pushed_from_back(void)
{
    /*****************    Arrange    *****************/
    uint8_t dataIn = 42;
    uint8_t dataOut;

    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));
    FwdList_PushBack(&list, &dataIn);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_PopBack(&list, &dataOut);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(dataIn, dataOut);

    PASS();
}

TEST List_can_back_pop_4_byte_data_types_when_pushed_from_back(void)
{
    /*****************    Arrange    *****************/
    uint32_t dataIn = 42;
    uint32_t dataOut;

    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint32_t       dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));
    FwdList_PushBack(&list, &dataIn);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_PopBack(&list, &dataOut);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(dataIn, dataOut);

    PASS();
}

TEST List_can_back_pop_1_byte_data_types_when_pushed_from_front(void)
{
    /*****************    Arrange    *****************/
    uint8_t dataIn = 42;
    uint8_t dataOut;

    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));
    FwdList_PushFront(&list, &dataIn);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_PopBack(&list, &dataOut);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(dataIn, dataOut);

    PASS();
}

TEST List_can_back_pop_4_byte_data_types_when_pushed_from_front(void)
{
    /*****************    Arrange    *****************/
    uint32_t dataIn = 42;
    uint32_t dataOut;

    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint32_t       dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));
    FwdList_PushFront(&list, &dataIn);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_PopBack(&list, &dataOut);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(dataIn, dataOut);

    PASS();
}

TEST List_can_peek_at_next_element_to_be_front_popped_when_pushed_from_back(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint32_t       dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[] = { 999, 244, 1500, 1 };
    uint32_t peekData;
    uint32_t poppedData;

    FwdList_PushBack(&list, &dataIn[0]);
    FwdList_PushBack(&list, &dataIn[1]);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_PeekFront(&list, &peekData);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(dataIn[0], peekData);
    FwdList_PopFront(&list, &poppedData);
    ASSERT_EQ(peekData, poppedData);

    PASS();
}

TEST List_can_peek_at_next_element_to_be_front_popped_when_pushed_from_front(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint32_t       dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[] = { 999, 244, 1500, 1 };
    uint32_t peekData;
    uint32_t poppedData;

    FwdList_PushFront(&list, &dataIn[0]);
    FwdList_PushFront(&list, &dataIn[1]);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_PeekFront(&list, &peekData);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(dataIn[1], peekData);
    FwdList_PopFront(&list, &poppedData);
    ASSERT_EQ(peekData, poppedData);

    PASS();
}

TEST List_can_peek_at_next_element_to_be_back_popped_when_pushed_from_back(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint32_t       dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[] = { 999, 244, 1500, 1 };
    uint32_t peekData;
    uint32_t poppedData;

    FwdList_PushBack(&list, &dataIn[0]);
    FwdList_PushBack(&list, &dataIn[1]);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_PeekBack(&list, &peekData);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(dataIn[1], peekData);
    FwdList_PopBack(&list, &poppedData);
    ASSERT_EQ(peekData, poppedData);

    PASS();
}

TEST List_can_peek_at_next_element_to_be_back_popped_when_pushed_from_front(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint32_t       dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[] = { 999, 244, 1500, 1 };
    uint32_t peekData;
    uint32_t poppedData;

    FwdList_PushFront(&list, &dataIn[0]);
    FwdList_PushFront(&list, &dataIn[1]);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_PeekBack(&list, &peekData);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(dataIn[0], peekData);
    FwdList_PopBack(&list, &poppedData);
    ASSERT_EQ(peekData, poppedData);

    PASS();
}

TEST List_can_empty_a_full_buffer_of_1_byte_data_types_by_push_back_and_pop_front(void)
{
    /*****************    Arrange    *****************/
    uint8_t err = (uint8_t)FwdList_Error_None;
    uint8_t dataIn[]  = { 50, 51, 52, 53 };
    uint8_t dataOut[] = {  0,  0,  0,  0 };

    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    /* Fill the List up */
    for (uint8_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= FwdList_PushBack(&list, &dataIn[i]);
    }

    /*****************     Act       *****************/
    /* Empty the List */
    for (uint8_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= FwdList_PopFront(&list, &dataOut[i]);
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ(true,  FwdList_IsEmpty(&list));
    ASSERT_EQ(dataIn[0], dataOut[0]);
    ASSERT_EQ(dataIn[1], dataOut[1]);
    ASSERT_EQ(dataIn[2], dataOut[2]);
    ASSERT_EQ(dataIn[3], dataOut[3]);

    PASS();
}

TEST List_can_empty_a_full_buffer_of_1_byte_data_types_by_push_front_and_pop_back(void)
{
    /*****************    Arrange    *****************/
    uint8_t err = (uint8_t)FwdList_Error_None;
    uint8_t dataIn[]  = { 50, 51, 52, 53 };
    uint8_t dataOut[] = {  0,  0,  0,  0 };

    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    /* Fill the List up */
    for (uint8_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= FwdList_PushFront(&list, &dataIn[i]);
    }

    /*****************     Act       *****************/
    /* Empty the List */
    for (uint8_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= FwdList_PopBack(&list, &dataOut[i]);
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ(true,  FwdList_IsEmpty(&list));
    ASSERT_EQ(dataIn[0], dataOut[0]);
    ASSERT_EQ(dataIn[1], dataOut[1]);
    ASSERT_EQ(dataIn[2], dataOut[2]);
    ASSERT_EQ(dataIn[3], dataOut[3]);

    PASS();
}

TEST List_can_empty_a_full_buffer_of_1_byte_data_types_by_push_front_and_pop_front(void)
{
    /*****************    Arrange    *****************/
    uint8_t err = (uint8_t)FwdList_Error_None;
    uint8_t dataIn[]  = { 50, 51, 52, 53 };
    uint8_t dataOut[] = {  0,  0,  0,  0 };

    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));


    /* Fill the List up */
    for (uint8_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= FwdList_PushFront(&list, &dataIn[i]);
    }

    /*****************     Act       *****************/
    /* Empty the List */
    for (uint8_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= FwdList_PopFront(&list, &dataOut[i]);
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ(true,  FwdList_IsEmpty(&list));
    ASSERT_EQ(dataIn[3], dataOut[0]);
    ASSERT_EQ(dataIn[2], dataOut[1]);
    ASSERT_EQ(dataIn[1], dataOut[2]);
    ASSERT_EQ(dataIn[0], dataOut[3]);

    PASS();
}

TEST List_can_empty_a_full_buffer_of_1_byte_data_types_by_push_back_and_pop_back(void)
{
    /*****************    Arrange    *****************/
    uint8_t err = (uint8_t)FwdList_Error_None;
    uint8_t dataIn[]  = { 50, 51, 52, 53 };
    uint8_t dataOut[] = {  0,  0,  0,  0 };

    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));


    /* Fill the List up */
    for (uint8_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= FwdList_PushBack(&list, &dataIn[i]);
    }

    /*****************     Act       *****************/
    /* Empty the List */
    for (uint8_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= FwdList_PopBack(&list, &dataOut[i]);
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ(true,  FwdList_IsEmpty(&list));
    ASSERT_EQ(dataIn[3], dataOut[0]);
    ASSERT_EQ(dataIn[2], dataOut[1]);
    ASSERT_EQ(dataIn[1], dataOut[2]);
    ASSERT_EQ(dataIn[0], dataOut[3]);

    PASS();
}

TEST List_can_empty_a_full_buffer_of_4_byte_data_types_by_push_back_and_pop_front(void)
{
    /*****************    Arrange    *****************/
    uint8_t  err = (uint8_t)FwdList_Error_None;
    uint32_t dataIn[]  = { 50, 51, 52, 53 };
    uint32_t dataOut[] = {  0,  0,  0,  0 };

    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint32_t       dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    /* Fill the List up */
    for (uint8_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= FwdList_PushBack(&list, &dataIn[i]);
    }

    /*****************     Act       *****************/
    /* Empty the List */
    for (uint8_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= FwdList_PopFront(&list, &dataOut[i]);
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ(true,  FwdList_IsEmpty(&list));
    ASSERT_EQ(dataIn[0], dataOut[0]);
    ASSERT_EQ(dataIn[1], dataOut[1]);
    ASSERT_EQ(dataIn[2], dataOut[2]);
    ASSERT_EQ(dataIn[3], dataOut[3]);

    PASS();
}

TEST List_can_empty_a_full_buffer_of_4_byte_data_types_by_push_front_and_pop_back(void)
{
    /*****************    Arrange    *****************/
    uint8_t  err = (uint8_t)FwdList_Error_None;
    uint32_t dataIn[]  = { 50, 51, 52, 53 };
    uint32_t dataOut[] = {  0,  0,  0,  0 };

    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint32_t       dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    /* Fill the List up */
    for (uint8_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= FwdList_PushFront(&list, &dataIn[i]);
    }

    /*****************     Act       *****************/
    /* Empty the List */
    for (uint8_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= FwdList_PopBack(&list, &dataOut[i]);
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ(true,  FwdList_IsEmpty(&list));
    ASSERT_EQ(dataIn[0], dataOut[0]);
    ASSERT_EQ(dataIn[1], dataOut[1]);
    ASSERT_EQ(dataIn[2], dataOut[2]);
    ASSERT_EQ(dataIn[3], dataOut[3]);

    PASS();
}

TEST List_can_empty_a_full_buffer_of_4_byte_data_types_by_push_front_and_pop_front(void)
{
    /*****************    Arrange    *****************/
    uint8_t  err = (uint8_t)FwdList_Error_None;
    uint32_t dataIn[]  = { 50, 51, 52, 53 };
    uint32_t dataOut[] = {  0,  0,  0,  0 };

    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint32_t       dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));


    /* Fill the List up */
    for (uint8_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= FwdList_PushFront(&list, &dataIn[i]);
    }

    /*****************     Act       *****************/
    /* Empty the List */
    for (uint8_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= FwdList_PopFront(&list, &dataOut[i]);
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ(true,  FwdList_IsEmpty(&list));
    ASSERT_EQ(dataIn[3], dataOut[0]);
    ASSERT_EQ(dataIn[2], dataOut[1]);
    ASSERT_EQ(dataIn[1], dataOut[2]);
    ASSERT_EQ(dataIn[0], dataOut[3]);

    PASS();
}

TEST List_can_empty_a_full_buffer_of_4_byte_data_types_by_push_back_and_pop_back(void)
{
    /*****************    Arrange    *****************/
    uint8_t  err = (uint8_t)FwdList_Error_None;
    uint32_t dataIn[]  = { 50, 51, 52, 53 };
    uint32_t dataOut[] = {  0,  0,  0,  0 };

    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint32_t       dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));


    /* Fill the List up */
    for (uint8_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= FwdList_PushBack(&list, &dataIn[i]);
    }

    /*****************     Act       *****************/
    /* Empty the List */
    for (uint8_t i = 0; i < ELEMENTS_IN(dataIn); i++)
    {
        err |= FwdList_PopBack(&list, &dataOut[i]);
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ(true,  FwdList_IsEmpty(&list));
    ASSERT_EQ(dataIn[3], dataOut[0]);
    ASSERT_EQ(dataIn[2], dataOut[1]);
    ASSERT_EQ(dataIn[1], dataOut[2]);
    ASSERT_EQ(dataIn[0], dataOut[3]);

    PASS();
}

TEST List_can_partially_fill_and_empty_multiple_times()
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[7];
    int32_t        dataBuf[7];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint8_t err = (uint8_t)FwdList_Error_None;

    int32_t dataIn[7] =
    {
        [0] = INT32_MIN,
        [1] = 121,
        [2] = -121,
        [3] = 7,
        [4] = INT32_MAX,
        [5] = -99,
        [6] = 99,
    };
    int32_t dataOut[7] = { 0 };
    uint8_t isFull = 0;
    uint8_t isEmpty = 1;

    /*****************     Act       *****************/
    for (uint16_t i = 0; i < 1000; i++)
    {
        err |= (uint8_t)FwdList_PushFront(&list, &dataIn[i % ELEMENTS_IN(dataBuf)]);
        err |= (uint8_t)FwdList_PushBack(&list, &dataIn[i % ELEMENTS_IN(dataBuf)]);
        err |= (uint8_t)FwdList_PopFront(&list, &dataOut[i % ELEMENTS_IN(dataBuf)]);
        err |= (uint8_t)FwdList_PopBack(&list, &dataOut[i % ELEMENTS_IN(dataBuf)]);

        isFull |= (uint8_t)FwdList_IsFull(&list);
        isEmpty &= (uint8_t)FwdList_IsEmpty(&list);
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(0U, isFull);
    ASSERT_EQ(1U, isEmpty);
    ASSERT_EQ(FwdList_Error_None, (FwdList_Error_e)err);

    PASS();
}

SUITE(FwdList_Suite)
{
    /* Unit Tests */
    RUN_TEST(List_can_report_empty);
    RUN_TEST(List_can_report_not_full);

    RUN_TEST(List_can_report_not_empty_when_pushed_from_back);
    RUN_TEST(List_can_report_not_empty_when_pushed_from_front);

    RUN_TEST(List_can_report_full_when_pushed_from_back);
    RUN_TEST(List_can_report_full_when_pushed_from_front);

    RUN_TEST(List_front_pop_fails_if_underflow);
    RUN_TEST(List_back_pop_fails_if_underflow);

    RUN_TEST(List_back_push_fails_due_to_overflow_when_pushed_from_back);
    RUN_TEST(List_back_push_fails_due_to_overflow_when_pushed_from_front);
    RUN_TEST(List_front_push_fails_due_to_overflow_when_pushed_from_back);
    RUN_TEST(List_front_push_fails_due_to_overflow_when_pushed_from_front);

    RUN_TEST(List_can_front_pop_1_byte_data_types_when_pushed_from_back);
    RUN_TEST(List_can_front_pop_4_byte_data_types_when_pushed_from_back);

    RUN_TEST(List_can_front_pop_1_byte_data_types_when_pushed_from_front);
    RUN_TEST(List_can_front_pop_4_byte_data_types_when_pushed_from_front);

    RUN_TEST(List_can_back_pop_1_byte_data_types_when_pushed_from_back);
    RUN_TEST(List_can_back_pop_4_byte_data_types_when_pushed_from_back);

    RUN_TEST(List_can_back_pop_1_byte_data_types_when_pushed_from_front);
    RUN_TEST(List_can_back_pop_4_byte_data_types_when_pushed_from_front);

    RUN_TEST(List_can_peek_at_next_element_to_be_front_popped_when_pushed_from_back);
    RUN_TEST(List_can_peek_at_next_element_to_be_front_popped_when_pushed_from_front);
    RUN_TEST(List_can_peek_at_next_element_to_be_back_popped_when_pushed_from_back);
    RUN_TEST(List_can_peek_at_next_element_to_be_back_popped_when_pushed_from_front);

    /* Integration Tests */
    RUN_TEST(List_can_empty_a_full_buffer_of_1_byte_data_types_by_push_back_and_pop_front);
    RUN_TEST(List_can_empty_a_full_buffer_of_1_byte_data_types_by_push_front_and_pop_back);
    RUN_TEST(List_can_empty_a_full_buffer_of_1_byte_data_types_by_push_front_and_pop_front);
    RUN_TEST(List_can_empty_a_full_buffer_of_1_byte_data_types_by_push_back_and_pop_back);

    RUN_TEST(List_can_empty_a_full_buffer_of_4_byte_data_types_by_push_back_and_pop_front);
    RUN_TEST(List_can_empty_a_full_buffer_of_4_byte_data_types_by_push_front_and_pop_back);
    RUN_TEST(List_can_empty_a_full_buffer_of_4_byte_data_types_by_push_front_and_pop_front);
    RUN_TEST(List_can_empty_a_full_buffer_of_4_byte_data_types_by_push_back_and_pop_back);

    RUN_TEST(List_can_partially_fill_and_empty_multiple_times);
}

#endif /* FORDWARD_LIST_SUITE_INCLUDED */
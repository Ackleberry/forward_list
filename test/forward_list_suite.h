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

TEST List_can_peek_front_without_memory_leak(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint32_t       dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[] = { 999, 244, 1500, 1 };
    uint32_t peekData;
    uint32_t poppedData[4] = {0};

    FwdList_PushBack(&list, &dataIn[0]);
    FwdList_PushBack(&list, &dataIn[1]);
    FwdList_PushBack(&list, &dataIn[2]);
    FwdList_PushBack(&list, &dataIn[3]);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_PeekFront(&list, &peekData);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(dataIn[0], peekData);
    ASSERT_EQ(true,  FwdList_IsFull(&list));
    ASSERT_EQ(false, FwdList_IsEmpty(&list));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &poppedData[0]));
    ASSERT_EQ(dataIn[0], poppedData[0]);
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &poppedData[1]));
    ASSERT_EQ(dataIn[1], poppedData[1]);
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &poppedData[2]));
    ASSERT_EQ(dataIn[2], poppedData[2]);
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &poppedData[3]));
    ASSERT_EQ(dataIn[3], poppedData[3]);
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ(true,  FwdList_IsEmpty(&list));

    PASS();
}

TEST List_can_peek_back_without_memory_leak(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint32_t       dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[] = { 999, 244, 1500, 1 };
    uint32_t peekData;
    uint32_t poppedData[4] = {0};

    FwdList_PushFront(&list, &dataIn[0]);
    FwdList_PushFront(&list, &dataIn[1]);
    FwdList_PushFront(&list, &dataIn[2]);
    FwdList_PushFront(&list, &dataIn[3]);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_PeekBack(&list, &peekData);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(dataIn[0], peekData);
    ASSERT_EQ(true,  FwdList_IsFull(&list));
    ASSERT_EQ(false, FwdList_IsEmpty(&list));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &poppedData[0]));
    ASSERT_EQ(dataIn[3], poppedData[0]);
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &poppedData[1]));
    ASSERT_EQ(dataIn[2], poppedData[1]);
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &poppedData[2]));
    ASSERT_EQ(dataIn[1], poppedData[2]);
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &poppedData[3]));
    ASSERT_EQ(dataIn[0], poppedData[3]);
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ(true,  FwdList_IsEmpty(&list));

    PASS();
}

TEST List_can_insert_a_number_in_ascending_order(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[5];
    uint32_t       dataBuf[5];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[5] = { 11, 3, 4, 8, 9 };
    FwdList_Insert(&list, TestHelper_OrderNumUp, &dataIn[0]);
    FwdList_Insert(&list, TestHelper_OrderNumUp, &dataIn[1]);
    FwdList_Insert(&list, TestHelper_OrderNumUp, &dataIn[2]);
    FwdList_Insert(&list, TestHelper_OrderNumUp, &dataIn[3]);

    /*****************     Act       *****************/
    FwdList_Insert(&list, TestHelper_OrderNumUp, &dataIn[4]);

    /*****************    Assert     *****************/
    uint32_t dataOut[5] = { 0 };

    /* Testing front and back asserts head and tail are updated properly */
    ASSERT_EQ(FwdList_Error_None, FwdList_PeekFront(&list, &dataOut[0]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PeekBack(&list, &dataOut[1]));
    ASSERT_EQ(3,  dataOut[0]);
    ASSERT_EQ(11, dataOut[1]);

    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[0]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[1]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[2]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[3]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopBack(&list, &dataOut[4]));
    ASSERT_EQ(3, dataOut[0]);
    ASSERT_EQ(4, dataOut[1]);
    ASSERT_EQ(8, dataOut[2]);
    ASSERT_EQ(9, dataOut[3]);
    ASSERT_EQ(11, dataOut[4]);

    PASS();
}

TEST List_can_insert_a_number_in_decending_order(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[5];
    uint32_t       dataBuf[5];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[5] = { 3, 7, 11, 8, 1 };
    FwdList_Insert(&list, TestHelper_OrderNumDown, &dataIn[0]);
    FwdList_Insert(&list, TestHelper_OrderNumDown, &dataIn[1]);
    FwdList_Insert(&list, TestHelper_OrderNumDown, &dataIn[2]);
    FwdList_Insert(&list, TestHelper_OrderNumDown, &dataIn[3]);

    /*****************     Act       *****************/
    FwdList_Insert(&list, TestHelper_OrderNumDown, &dataIn[4]);

    /*****************    Assert     *****************/
    uint32_t dataOut[5] = { 0 };

    /* Testing front and back asserts head and tail are updated properly */
    ASSERT_EQ(FwdList_Error_None, FwdList_PeekFront(&list, &dataOut[0]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PeekBack(&list, &dataOut[1]));
    ASSERT_EQ(11,  dataOut[0]);
    ASSERT_EQ(1, dataOut[1]);
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[0]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[1]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[2]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[3]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopBack(&list, &dataOut[4]));
    ASSERT_EQ(11, dataOut[0]);
    ASSERT_EQ(8, dataOut[1]);
    ASSERT_EQ(7, dataOut[2]);
    ASSERT_EQ(3, dataOut[3]);
    ASSERT_EQ(1, dataOut[4]);

    PASS();
}

TEST List_can_can_group_even_and_odd_numbers_in_the_order_they_arrive(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[9];
    uint32_t       dataBuf[9];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[9] = { 1, 2, 3, 4, 5, 4, 3, 2, 1 };
    FwdList_Insert(&list, TestHelper_GroupEvenAndOdd, &dataIn[0]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOdd, &dataIn[1]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOdd, &dataIn[2]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOdd, &dataIn[3]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOdd, &dataIn[4]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOdd, &dataIn[5]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOdd, &dataIn[6]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOdd, &dataIn[7]);

    /*****************     Act       *****************/
    FwdList_Insert(&list, TestHelper_GroupEvenAndOdd, &dataIn[8]);

    /*****************    Assert     *****************/
    uint32_t dataOut[9] = { 0 };

    /* Testing front and back asserts head and tail are updated properly */
    ASSERT_EQ(FwdList_Error_None, FwdList_PeekFront(&list, &dataOut[0]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PeekBack(&list, &dataOut[1]));
    ASSERT_EQ(2, dataOut[0]);
    ASSERT_EQ(1, dataOut[1]);
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[0]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[1]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[2]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[3]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[4]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[5]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[6]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[7]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopBack(&list, &dataOut[8]));
    ASSERT_EQ(2, dataOut[0]);
    ASSERT_EQ(4, dataOut[1]);
    ASSERT_EQ(4, dataOut[2]);
    ASSERT_EQ(2, dataOut[3]);
    ASSERT_EQ(1, dataOut[4]);
    ASSERT_EQ(3, dataOut[5]);
    ASSERT_EQ(5, dataOut[6]);
    ASSERT_EQ(3, dataOut[7]);
    ASSERT_EQ(1, dataOut[8]);

    PASS();
}

TEST List_can_group_even_and_odd_numbers_in_ascending_order(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[9];
    uint32_t       dataBuf[9];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[9] = { 1, 2, 3, 4, 5, 4, 3, 2, 1 };
    FwdList_Insert(&list, TestHelper_GroupEvenAndOddUp, &dataIn[0]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOddUp, &dataIn[1]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOddUp, &dataIn[2]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOddUp, &dataIn[3]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOddUp, &dataIn[4]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOddUp, &dataIn[5]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOddUp, &dataIn[6]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOddUp, &dataIn[7]);

    /*****************     Act       *****************/
    FwdList_Insert(&list, TestHelper_GroupEvenAndOddUp, &dataIn[8]);

    /*****************    Assert     *****************/
    uint32_t dataOut[9] = { 0 };

    /* Testing front and back asserts head and tail are updated properly */
    ASSERT_EQ(FwdList_Error_None, FwdList_PeekFront(&list, &dataOut[0]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PeekBack(&list, &dataOut[1]));
    ASSERT_EQ(2, dataOut[0]);
    ASSERT_EQ(5, dataOut[1]);
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[0]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[1]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[2]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[3]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[4]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[5]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[6]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[7]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopBack(&list, &dataOut[8]));
    ASSERT_EQ(2, dataOut[0]);
    ASSERT_EQ(2, dataOut[1]);
    ASSERT_EQ(4, dataOut[2]);
    ASSERT_EQ(4, dataOut[3]);
    ASSERT_EQ(1, dataOut[4]);
    ASSERT_EQ(1, dataOut[5]);
    ASSERT_EQ(3, dataOut[6]);
    ASSERT_EQ(3, dataOut[7]);
    ASSERT_EQ(5, dataOut[8]);

    PASS();
}

TEST List_can_group_even_and_odd_numbers_in_decending_order(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[9];
    uint32_t       dataBuf[9];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[9] = { 1, 2, 3, 4, 5, 4, 3, 2, 1 };
    FwdList_Insert(&list, TestHelper_GroupEvenAndOddDown, &dataIn[0]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOddDown, &dataIn[1]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOddDown, &dataIn[2]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOddDown, &dataIn[3]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOddDown, &dataIn[4]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOddDown, &dataIn[5]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOddDown, &dataIn[6]);
    FwdList_Insert(&list, TestHelper_GroupEvenAndOddDown, &dataIn[7]);

    /*****************     Act       *****************/
    FwdList_Insert(&list, TestHelper_GroupEvenAndOddDown, &dataIn[8]);

    /*****************    Assert     *****************/
    uint32_t dataOut[9] = { 0 };

    /* Testing front and back asserts head and tail are updated properly */
    ASSERT_EQ(FwdList_Error_None, FwdList_PeekFront(&list, &dataOut[0]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PeekBack(&list, &dataOut[1]));
    ASSERT_EQ(4, dataOut[0]);
    ASSERT_EQ(1, dataOut[1]);
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[0]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[1]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[2]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[3]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[4]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[5]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[6]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[7]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopBack(&list, &dataOut[8]));
    ASSERT_EQ(4, dataOut[0]);
    ASSERT_EQ(4, dataOut[1]);
    ASSERT_EQ(2, dataOut[2]);
    ASSERT_EQ(2, dataOut[3]);
    ASSERT_EQ(5, dataOut[4]);
    ASSERT_EQ(3, dataOut[5]);
    ASSERT_EQ(3, dataOut[6]);
    ASSERT_EQ(1, dataOut[7]);
    ASSERT_EQ(1, dataOut[8]);

    PASS();
}

TEST List_can_insert_after_a_specified_condition(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[5];
    uint32_t       dataBuf[5];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[5] = { 1, 2, 3, 4, 5 };
    FwdList_PushBack(&list, &dataIn[0]);
    FwdList_PushBack(&list, &dataIn[1]);
    FwdList_PushBack(&list, &dataIn[2]);
    FwdList_PushBack(&list, &dataIn[3]);

    /*****************     Act       *****************/
    FwdList_Insert(&list, TestHelper_AddAfter, &dataIn[4]);

    /*****************    Assert     *****************/
    uint32_t dataOut[5] = { 0 };

    /* Testing front and back asserts head and tail are updated properly */
    ASSERT_EQ(FwdList_Error_None, FwdList_PeekFront(&list, &dataOut[0]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PeekBack(&list, &dataOut[1]));
    ASSERT_EQ(1, dataOut[0]);
    ASSERT_EQ(4, dataOut[1]);
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[0]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[1]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[2]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[3]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[4]));
    ASSERT_EQ(1, dataOut[0]);
    ASSERT_EQ(2, dataOut[1]);
    ASSERT_EQ(3, dataOut[2]);
    ASSERT_EQ(5, dataOut[3]);
    ASSERT_EQ(4, dataOut[4]);

    PASS();
}

TEST List_can_reverse_a_list_with_0_nodes(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[5];
    uint32_t       dataBuf[5];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_Reverse(&list);

    /*****************    Assert     *****************/
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(true, FwdList_IsEmpty(&list));

    PASS();
}

TEST List_can_reverse_a_list_with_1_nodes(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[5];
    uint32_t       dataBuf[5];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[1] = { 11 };
    FwdList_PushBack(&list, &dataIn[0]);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_Reverse(&list);

    /*****************    Assert     *****************/
    uint32_t dataOut[1] = { 0 };
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(false, FwdList_IsEmpty(&list));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[0]));
    ASSERT_EQ(11, dataOut[0]);

    PASS();
}

TEST List_can_reverse_a_list_with_2_nodes(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[5];
    uint32_t       dataBuf[5];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[2] = { 11, 32 };
    FwdList_PushBack(&list, &dataIn[0]);
    FwdList_PushBack(&list, &dataIn[1]);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_Reverse(&list);

    /*****************    Assert     *****************/
    uint32_t dataOut[2] = { 0 };
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(false, FwdList_IsEmpty(&list));
    /* Testing front and back asserts head and tail are updated properly */
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[0]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopBack(&list, &dataOut[1]));
    ASSERT_EQ(32, dataOut[0]);
    ASSERT_EQ(11, dataOut[1]);

    PASS();
}

TEST List_can_reverse_a_list_with_4_nodes(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[5];
    uint32_t       dataBuf[5];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[4] = { 11, 32, 5, 99 };
    FwdList_PushBack(&list, &dataIn[0]);
    FwdList_PushBack(&list, &dataIn[1]);
    FwdList_PushBack(&list, &dataIn[2]);
    FwdList_PushBack(&list, &dataIn[3]);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_Reverse(&list);

    /*****************    Assert     *****************/
    uint32_t dataOut[4] = { 0 };
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(false, FwdList_IsEmpty(&list));
    /* Testing front and back asserts head and tail are updated properly */
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[0]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[1]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[2]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopBack(&list, &dataOut[3]));
    ASSERT_EQ(99, dataOut[0]);
    ASSERT_EQ(5, dataOut[1]);
    ASSERT_EQ(32, dataOut[2]);
    ASSERT_EQ(11, dataOut[3]);

    PASS();
}

TEST List_can_reverse_a_list_with_8_nodes(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[8];
    uint32_t       dataBuf[8];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[8] = { 11, 32, 5, 99, 2, 7, 81, 42};
    FwdList_PushBack(&list, &dataIn[0]);
    FwdList_PushBack(&list, &dataIn[1]);
    FwdList_PushBack(&list, &dataIn[2]);
    FwdList_PushBack(&list, &dataIn[3]);
    FwdList_PushBack(&list, &dataIn[4]);
    FwdList_PushBack(&list, &dataIn[5]);
    FwdList_PushBack(&list, &dataIn[6]);
    FwdList_PushBack(&list, &dataIn[7]);

    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_Reverse(&list);

    /*****************    Assert     *****************/
    uint32_t dataOut[8] = { 0 };
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(false, FwdList_IsEmpty(&list));
    /* Testing front and back asserts head and tail are updated properly */
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[0]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[1]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[2]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[3]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[4]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[5]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[6]));
    ASSERT_EQ(FwdList_Error_None, FwdList_PopBack(&list, &dataOut[7]));
    ASSERT_EQ(42, dataOut[0]);
    ASSERT_EQ(81, dataOut[1]);
    ASSERT_EQ(7, dataOut[2]);
    ASSERT_EQ(2, dataOut[3]);
    ASSERT_EQ(99, dataOut[4]);
    ASSERT_EQ(5, dataOut[5]);
    ASSERT_EQ(32, dataOut[6]);
    ASSERT_EQ(11, dataOut[7]);

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

TEST List_can_partially_fill_and_empty_multiple_times(void)
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
    RUN_TEST(List_can_peek_front_without_memory_leak);
    RUN_TEST(List_can_peek_back_without_memory_leak);

    RUN_TEST(List_can_insert_a_number_in_ascending_order);
    RUN_TEST(List_can_insert_a_number_in_decending_order);
    RUN_TEST(List_can_can_group_even_and_odd_numbers_in_the_order_they_arrive);
    RUN_TEST(List_can_group_even_and_odd_numbers_in_ascending_order);
    RUN_TEST(List_can_group_even_and_odd_numbers_in_decending_order);
    RUN_TEST(List_can_insert_after_a_specified_condition);

    RUN_TEST(List_can_reverse_a_list_with_0_nodes);
    RUN_TEST(List_can_reverse_a_list_with_1_nodes);
    RUN_TEST(List_can_reverse_a_list_with_2_nodes);
    RUN_TEST(List_can_reverse_a_list_with_4_nodes);
    RUN_TEST(List_can_reverse_a_list_with_8_nodes);

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
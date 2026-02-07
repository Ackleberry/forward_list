#ifndef FORWARD_LIST_SUITE_INCLUDED
#define FORWARD_LIST_SUITE_INCLUDED

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

TEST List_can_report_not_full_when_emtpy(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    /*****************     Act       *****************/
    bool isFull = FwdList_IsFull(&list);

    /*****************    Assert     *****************/
    ASSERT_EQ(false, isFull);

    PASS();
}

TEST List_can_report_not_full_when_partially_full(void)
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

TEST List_can_get_count_when_empty(void)
{
    /*****************    Arrange    *****************/
    FwdList_t      list;
    FwdList_Node_t nodeBuf[4];
    uint8_t        dataBuf[4];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    /*****************     Act       *****************/
    size_t count = FwdList_Count(&list);

    /*****************    Assert     *****************/
    ASSERT_EQ(0, count);

    PASS();
}

TEST List_can_get_count_when_partially_full(void)
{
    /*****************    Arrange    *****************/
    size_t         max_count = 4;
    FwdList_t      list;
    FwdList_Node_t nodeBuf[max_count];
    uint8_t        dataBuf[max_count];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint8_t dataIn = 42;
    FwdList_PushFront(&list, &dataIn);
    FwdList_PushBack(&list, &dataIn);

    /*****************     Act       *****************/
    size_t count = FwdList_Count(&list);

    /*****************    Assert     *****************/
    ASSERT_EQ(2, count);

    PASS();
}

TEST List_can_get_count_when_full(void)
{
    /*****************    Arrange    *****************/
    size_t         max_count = 4;
    FwdList_t      list;
    FwdList_Node_t nodeBuf[max_count];
    uint8_t        dataBuf[max_count];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint8_t dataIn = 42;
    FwdList_PushFront(&list, &dataIn);
    FwdList_PushBack(&list, &dataIn);
    FwdList_PushFront(&list, &dataIn);
    FwdList_PushBack(&list, &dataIn);

    /*****************     Act       *****************/
    size_t count = FwdList_Count(&list);

    /*****************    Assert     *****************/
    ASSERT_EQ(max_count, count);

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

    /* Fill the list up */
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

    /* Fill the list up */
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

    /* Fill the list up */
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

    /* Fill the list up */
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

TEST List_iterator_begins_with_index_0_and_null_data_if_list_is_empty(void)
{
    /*****************    Arrange    *****************/
    const size_t   listSize = 4;
    FwdList_t      list;
    FwdList_Node_t nodeBuf[listSize];
    uint32_t       dataBuf[listSize];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

                        
    /*****************     Act       *****************/
    FwdList_Iter_t it = FwdList_Begin(&list);

    /*****************    Assert     *****************/
    ASSERT_EQ(true, FwdList_IsEmpty(&list));
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ(0, FwdList_Count(&list));
    ASSERT_EQ_FMT(0, it.index, "%zu");
    ASSERT_EQ(NULL, it.pData);

    PASS();
}

TEST List_iterator_begins_with_index_0_and_data_if_list_is_not_empty(void)
{
    /*****************    Arrange    *****************/
    const size_t   listSize = 4;
    FwdList_t      list;
    FwdList_Node_t nodeBuf[listSize];
    uint32_t       dataBuf[listSize];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[] = { 15 };
    FwdList_PushFront(&list, &dataIn[0]);    
    
    /*****************     Act       *****************/
    FwdList_Iter_t it = FwdList_Begin(&list);

    /*****************    Assert     *****************/
    ASSERT_EQ(false, FwdList_IsEmpty(&list));
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ(1, FwdList_Count(&list));
    ASSERT_EQ_FMT(0, it.index, "%zu");
    ASSERT_NEQ(NULL, it.pData);

    PASS();
}

TEST List_iterator_does_not_advance_if_there_are_no_available_nodes(void)
{
    /*****************    Arrange    *****************/
    const size_t   listSize = 4;
    FwdList_t      list;
    FwdList_Node_t nodeBuf[listSize];
    uint32_t       dataBuf[listSize];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));  
      
    FwdList_Iter_t it = FwdList_Begin(&list);

    /*****************     Act       *****************/
    FwdList_Next(&it);
    FwdList_Next(&it);
    FwdList_Next(&it);

    /*****************    Assert     *****************/
    ASSERT_EQ(true, FwdList_IsEmpty(&list));
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ(0, FwdList_Count(&list));
    ASSERT_EQ_FMT(0, it.index, "%zu");
    ASSERT_EQ(NULL, it.pData);

    PASS();
}

TEST List_iterator_does_advance_if_there_are_available_nodes(void)
{
    /*****************    Arrange    *****************/
    const size_t   listSize = 4;
    FwdList_t      list;
    FwdList_Node_t nodeBuf[listSize];
    uint32_t       dataBuf[listSize];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[] = { 15, 7, 5, 3 };
    FwdList_PushFront(&list, &dataIn[0]);    
    FwdList_PushFront(&list, &dataIn[1]);    
    FwdList_PushFront(&list, &dataIn[2]);    
    FwdList_PushFront(&list, &dataIn[3]);    
    FwdList_Iter_t it = FwdList_Begin(&list);
    
    /*****************     Act       *****************/
    FwdList_Next(&it);
    FwdList_Next(&it);
    FwdList_Next(&it);

    /*****************    Assert     *****************/
    ASSERT_EQ(false, FwdList_IsEmpty(&list));
    ASSERT_EQ(true, FwdList_IsFull(&list));
    ASSERT_EQ(4, FwdList_Count(&list));

    ASSERT_EQ_FMT(3, it.index, "%zu");
    ASSERT_NEQ(NULL, it.pData);

    PASS();
}

TEST List_can_iterate_through_data(void)
{
    /*****************    Arrange    *****************/
    const size_t   listSize = 4;
    FwdList_t      list;
    FwdList_Node_t nodeBuf[listSize];
    uint32_t       dataBuf[listSize];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[] = { 999, 244, 1500, 1 };
    uint32_t dataOut[listSize];

    FwdList_PushBack(&list, &dataIn[0]);
    FwdList_PushBack(&list, &dataIn[1]);
    FwdList_PushBack(&list, &dataIn[2]);
    FwdList_PushBack(&list, &dataIn[3]);

    /*****************     Act       *****************/
    for (FwdList_Iter_t it = FwdList_Begin(&list); it.pData != NULL; FwdList_Next(&it))
    {
        dataOut[it.index] = *(uint32_t *)it.pData;
    }

    /*****************    Assert     *****************/
    for (size_t x = 0; x < listSize; x++)
    {
        ASSERT_EQ(dataIn[x], dataOut[x]);
    }

    PASS();
}

TEST List_can_insert_data_into_an_empty_list(void)
{
    /*****************    Arrange    *****************/
    const size_t   listSize = 4;
    FwdList_t      list;
    FwdList_Node_t nodeBuf[listSize];
    uint32_t       dataBuf[listSize];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t insertData = 7;
    uint32_t dataOut;

    /*****************     Act       *****************/
    FwdList_Iter_t it = FwdList_Begin(&list);
    FwdList_Insert(&list, &it, &insertData);

    /*****************    Assert     *****************/
    ASSERT_EQ(false, FwdList_IsEmpty(&list));
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ(1, FwdList_Count(&list));
    ASSERT_EQ(0, it.index);
    ASSERT_EQ(insertData, *(uint32_t *)it.pData);
    ASSERT_EQ(FwdList_Error_None, FwdList_PeekFront(&list, &dataOut));
    ASSERT_EQ(insertData, dataOut);
    ASSERT_EQ(FwdList_Error_None, FwdList_PeekBack(&list, &dataOut));
    ASSERT_EQ(insertData, dataOut);
    ASSERT_EQ(FwdList_Error_None, FwdList_PopBack(&list, &dataOut));
    ASSERT_EQ(insertData, dataOut);
    ASSERT_EQ(true, FwdList_IsEmpty(&list));
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ(0, FwdList_Count(&list));

    PASS();
}

TEST List_can_insert_data_into_a_list_with_1_existing_item(void)
{
    /*****************    Arrange    *****************/
    const size_t   listSize = 4;
    FwdList_t      list;
    FwdList_Node_t nodeBuf[listSize];
    uint32_t       dataBuf[listSize];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[] = { 15, 9 };
    FwdList_Iter_t it = FwdList_Begin(&list);
    FwdList_Insert(&list, &it, &dataIn[0]);
    
    /*****************     Act       *****************/
    FwdList_Error_e err = FwdList_Insert(&list, &it, &dataIn[1]);

    /*****************    Assert     *****************/
    uint32_t dataOut;
    ASSERT_EQ(FwdList_Error_None, err);
    ASSERT_EQ(false, FwdList_IsEmpty(&list));
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ(2, FwdList_Count(&list));
    ASSERT_EQ_FMT(0, it.index, "%zu");
    ASSERT_EQ(dataIn[1], *(uint32_t *)it.pData);
    ASSERT_EQ(FwdList_Error_None, FwdList_PeekFront(&list, &dataOut));
    ASSERT_EQ_FMT(dataIn[1], dataOut, "%d");
    ASSERT_EQ(FwdList_Error_None, FwdList_PeekBack(&list, &dataOut));
    ASSERT_EQ_FMT(dataIn[0], dataOut, "%d");
    ASSERT_EQ(FwdList_Error_None, FwdList_PopBack(&list, &dataOut));
    ASSERT_EQ_FMT(dataIn[0], dataOut, "%d");
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut));
    ASSERT_EQ_FMT(dataIn[1], dataOut, "%d");
    ASSERT_EQ(true, FwdList_IsEmpty(&list));
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ(0, FwdList_Count(&list));

    PASS();
}

TEST List_can_insert_data_into_the_beginning_of_a_list(void)
{
    /*****************    Arrange    *****************/
    const size_t   listSize = 5;
    FwdList_t      list;
    FwdList_Node_t nodeBuf[listSize];
    uint32_t       dataBuf[listSize];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[] = { 1000, 100, 10, 1 };
    FwdList_PushBack(&list, &dataIn[0]);    
    FwdList_PushBack(&list, &dataIn[1]);    
    FwdList_PushBack(&list, &dataIn[2]);    
    FwdList_PushBack(&list, &dataIn[3]);
    uint32_t insertData = 2000;
    
    /*****************     Act       *****************/
    for (FwdList_Iter_t it = FwdList_Begin(&list); it.pData != NULL; FwdList_Next(&it))
    {
        if (insertData > *(uint32_t *)it.pData) {
            FwdList_Insert(&list, &it, &insertData);
            break;
        }
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(false, FwdList_IsEmpty(&list));
    ASSERT_EQ(true, FwdList_IsFull(&list));
    ASSERT_EQ_FMT(5, FwdList_Count(&list), "%zu");

    uint32_t dataOut[listSize];
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[0]));
    ASSERT_EQ_FMT(insertData, dataOut[0], "%zu");
    
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[1]));
    ASSERT_EQ_FMT(dataIn[0], dataOut[1], "%zu");
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[2]));
    ASSERT_EQ_FMT(dataIn[1], dataOut[2], "%zu");
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[3]));
    ASSERT_EQ_FMT(dataIn[2], dataOut[3], "%zu");
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[4]));
    ASSERT_EQ_FMT(dataIn[3], dataOut[4], "%zu");

    ASSERT_EQ(true, FwdList_IsEmpty(&list));
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ_FMT(0, FwdList_Count(&list), "%zu");

    PASS();
}

TEST List_can_insert_data_into_the_middle_of_a_list(void)
{
    /*****************    Arrange    *****************/
    const size_t   listSize = 5;
    FwdList_t      list;
    FwdList_Node_t nodeBuf[listSize];
    uint32_t       dataBuf[listSize];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[] = { 1000, 100, 10, 1 };
    FwdList_PushBack(&list, &dataIn[0]);    
    FwdList_PushBack(&list, &dataIn[1]);    
    FwdList_PushBack(&list, &dataIn[2]);    
    FwdList_PushBack(&list, &dataIn[3]);
    uint32_t insertData = 50;
    
    /*****************     Act       *****************/
    for (FwdList_Iter_t it = FwdList_Begin(&list); it.pData != NULL; FwdList_Next(&it))
    {
        if (insertData > *(uint32_t *)it.pData) {
            FwdList_Insert(&list, &it, &insertData);
            break;
        }
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(false, FwdList_IsEmpty(&list));
    ASSERT_EQ(true, FwdList_IsFull(&list));
    ASSERT_EQ_FMT(5, FwdList_Count(&list), "%zu");

    uint32_t dataOut[listSize];
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[0]));
    ASSERT_EQ_FMT(dataIn[0], dataOut[0], "%zu");
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[1]));
    ASSERT_EQ_FMT(dataIn[1], dataOut[1], "%zu");

    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[2]));
    ASSERT_EQ_FMT(insertData, dataOut[2], "%zu");

    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[3]));
    ASSERT_EQ_FMT(dataIn[2], dataOut[3], "%zu");
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[4]));
    ASSERT_EQ_FMT(dataIn[3], dataOut[4], "%zu");

    ASSERT_EQ(true, FwdList_IsEmpty(&list));
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ_FMT(0, FwdList_Count(&list), "%zu");

    PASS();
}

TEST List_can_insert_data_at_end_of_list(void)
{
    /*****************    Arrange    *****************/
    const size_t   listSize = 5;
    FwdList_t      list;
    FwdList_Node_t nodeBuf[listSize];
    uint32_t       dataBuf[listSize];
    FwdList_Init(&list, &nodeBuf, sizeof(nodeBuf),
                        &dataBuf, sizeof(dataBuf), sizeof(dataBuf[0]));

    uint32_t dataIn[] = { 10000, 1000, 100, 10 };
    FwdList_PushBack(&list, &dataIn[0]);    
    FwdList_PushBack(&list, &dataIn[1]);    
    FwdList_PushBack(&list, &dataIn[2]);    
    FwdList_PushBack(&list, &dataIn[3]);
    uint32_t insertData = 1;

    FwdList_Iter_t it = FwdList_Begin(&list);
    while (it.pData != NULL)
    {
        if (insertData > *(uint32_t *)it.pData) {
            FwdList_Insert(&list, &it, &insertData);
            break;
        }
        FwdList_Next(&it);
    }
    
    /*****************     Act       *****************/
    if (it.pData == NULL) 
    {
        FwdList_Insert(&list, &it, &insertData);
    }

    /*****************    Assert     *****************/
    ASSERT_EQ(false, FwdList_IsEmpty(&list));
    ASSERT_EQ(true, FwdList_IsFull(&list));
    ASSERT_EQ_FMT(5, FwdList_Count(&list), "%zu");

    uint32_t dataOut[listSize];
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[0]));
    ASSERT_EQ_FMT(dataIn[0], dataOut[0], "%zu");
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[1]));
    ASSERT_EQ_FMT(dataIn[1], dataOut[1], "%zu");    
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[2]));
    ASSERT_EQ_FMT(dataIn[2], dataOut[2], "%zu");
    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[3]));
    ASSERT_EQ_FMT(dataIn[3], dataOut[3], "%zu");

    ASSERT_EQ(FwdList_Error_None, FwdList_PopFront(&list, &dataOut[4]));
    ASSERT_EQ_FMT(insertData, dataOut[4], "%zu");

    ASSERT_EQ(true, FwdList_IsEmpty(&list));
    ASSERT_EQ(false, FwdList_IsFull(&list));
    ASSERT_EQ_FMT(0, FwdList_Count(&list), "%zu");

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
    RUN_TEST(List_can_report_not_full_when_emtpy);
    RUN_TEST(List_can_report_not_full_when_partially_full);

    RUN_TEST(List_can_report_not_empty_when_pushed_from_back);
    RUN_TEST(List_can_report_not_empty_when_pushed_from_front);

    RUN_TEST(List_can_report_full_when_pushed_from_back);
    RUN_TEST(List_can_report_full_when_pushed_from_front);

    RUN_TEST(List_can_get_count_when_empty);
    RUN_TEST(List_can_get_count_when_partially_full);
    RUN_TEST(List_can_get_count_when_full);

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

    RUN_TEST(List_iterator_begins_with_index_0_and_null_data_if_list_is_empty);
    RUN_TEST(List_iterator_begins_with_index_0_and_data_if_list_is_not_empty);
    RUN_TEST(List_iterator_does_not_advance_if_there_are_no_available_nodes);
    RUN_TEST(List_iterator_does_advance_if_there_are_available_nodes);
    RUN_TEST(List_can_iterate_through_data);

    RUN_TEST(List_can_insert_data_into_an_empty_list);
    RUN_TEST(List_can_insert_data_into_a_list_with_1_existing_item);
    RUN_TEST(List_can_insert_data_into_the_beginning_of_a_list);
    RUN_TEST(List_can_insert_data_into_the_middle_of_a_list);
    RUN_TEST(List_can_insert_data_at_end_of_list);

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

#endif /* FORWARD_LIST_SUITE_INCLUDED */
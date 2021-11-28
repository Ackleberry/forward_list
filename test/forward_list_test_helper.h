#ifndef FORWARD_LIST_TEST_HELPER_H_INCLUDED
#define FORWARD_LIST_TEST_HELPER_H_INCLUDED

#include <stdint.h>
#include "forward_list_test_helper_t.h"
#include "forward_list.h"

void             TestHelper_PrintList(FwdList_t *pObj);
FwdList_Insert_e TestHelper_OrderNumUp(void *pListDataVoid, void *pUserDataVoid);
FwdList_Insert_e TestHelper_OrderNumDown(void *pListDataVoid, void *pUserDataVoid);
FwdList_Insert_e TestHelper_GroupEvenAndOdd(void *pListDataVoid, void *pUserDataVoid);
FwdList_Insert_e TestHelper_GroupEvenAndOddUp(void *pListDataVoid, void *pUserDataVoid);
FwdList_Insert_e TestHelper_GroupEvenAndOddDown(void *pListDataVoid, void *pUserDataVoid);
FwdList_Insert_e TestHelper_AddAfter(void *pListDataVoid, void *pUserDataVoid);

#endif /* FORWARD_LIST_TEST_HELPER_H_INCLUDED */

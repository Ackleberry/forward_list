#include "forward_list_test_helper.h"

bool TestHelper_OrderNumUp(void *pListDataVoid, void *pUserDataVoid)
{
    uint32_t *pUserData = pUserDataVoid;
    uint32_t *pListData = pListDataVoid;

    return (*pUserData >= *pListData ? false : true);
}

bool TestHelper_OrderNumDown(void *pListDataVoid, void *pUserDataVoid)
{
    uint32_t *pUserData = pUserDataVoid;
    uint32_t *pListData = pListDataVoid;

    return (*pUserData <= *pListData ? false : true);
}
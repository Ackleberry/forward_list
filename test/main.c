/**
 * @file   main.c
 * @author Brooks Anderson
 * @date   09/09/2021
 * @brief
 */

#include <stdio.h>

#include "greatest.h"

#include "forward_list_suite.h"

GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
    GREATEST_MAIN_BEGIN(); /* command-line arguments, initialization. */

    printf("\n*********          Begin Unit Tests          *********\n");

    RUN_SUITE(FwdList_Suite);

    printf("\n*********          End Unit Tests            *********\n");

    GREATEST_MAIN_END(); /* display results */
}
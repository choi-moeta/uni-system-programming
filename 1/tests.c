/**
 * \file  tests.c
 * \brief Unit tests for functions.
 *
 * \details Unit tests for functions.
 */

#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include <CUnit/CUnit.h>
#include "functions.h"

/** \brief Tests for function convertLine
 */

void testConvertLine() {
    CU_ASSERT_STRING_EQUAL(convertLine("RegiSTER"), "rEGIster");
    CU_ASSERT_STRING_EQUAL(convertLine("trimspaces   "), "TRIMSPACES");
    CU_ASSERT_STRING_EQUAL(convertLine("sOme 'Quotes' Here"), "SoME 'Quotes' hERE");
    CU_ASSERT_STRING_EQUAL(convertLine("	TA		BS	"), "  ta    bs");
}

/** \brief Main function
 *
 * \details Initializationfor unit tests.
 *
 * \return           Error upon error.
 */

int main()
{
    CU_pSuite suite;
    CU_initialize_registry();
    suite = CU_add_suite("main_suite", NULL, NULL);
    CU_ADD_TEST(suite, testConvertLine);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();
}
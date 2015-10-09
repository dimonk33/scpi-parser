/*-
 * Copyright (c) 2013 Jan Breuer
 *                    Richard.hmm
 * Copyright (c) 2012 Jan Breuer
 *
 * All Rights Reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * File:   test_scpi_utils.c
 * Author: Jan Breuer
 *
 * Created on 26.11.2012, 11:22:00
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "CUnit/Basic.h"

#include "scpi/scpi.h"
#include "../src/utils_private.h"

/*
 * CUnit Test Suite
 */

static int init_suite(void) {
    return 0;
}

static int clean_suite(void) {
    return 0;
}

static void test_strnpbrk() {
    char str[] = "ahoj";

    CU_ASSERT(strnpbrk(str, 4, "a") == (str + 0));
    CU_ASSERT(strnpbrk(str, 4, "h") == (str + 1));
    CU_ASSERT(strnpbrk(str, 4, "b") == NULL);
    CU_ASSERT(strnpbrk(str, 1, "h") == NULL);
    CU_ASSERT(strnpbrk(str, 4, "xo") == (str + 2));

    CU_ASSERT(strnpbrk(str, 4, "j") == (str + 3));

}

static void test_Int32ToStr() {
    const size_t max=32+1;
    int32_t val[] = {0, 1, -1, INT32_MIN, INT32_MAX, 0x01234567, 0x89abcdef};
    int N = sizeof(val) / sizeof(int32_t);
    int i;
    char str[max];
    char ref[max];
    size_t len;

    // test signed conversion to decimal numbers
    for (i=0; i<N; i++) {
        len = SCPI_Int32ToStr(val[i], str, max);
        snprintf(ref, max, "%"PRIi32, val[i]);
        CU_ASSERT(len == strlen(ref));
        CU_ASSERT_STRING_EQUAL(str, ref);
    }
}

static void test_UInt32ToStrBase() {
    const size_t max=32+1;
    uint32_t val[] = {0, 1, -1, INT32_MIN, INT32_MAX, 0x01234567, 0x89abcdef};
    int N = sizeof(val) / sizeof(uint32_t);
    int i;
    char str[max];
    char ref[max];
    size_t len;

    // test conversion to decimal numbers
    for (i=0; i<N; i++) {
        len = SCPI_UInt32ToStrBase(val[i], str, max, 10);
        snprintf(ref, max, "%"PRIu32, val[i]);
        CU_ASSERT(len == strlen(ref));
        CU_ASSERT_STRING_EQUAL(str, ref);
    }

    // test conversion to hexadecimal numbers
    for (i=0; i<N; i++) {
        len = SCPI_UInt32ToStrBase(val[i], str, max, 16);
        snprintf(ref, max, "%"PRIX32, val[i]);
        CU_ASSERT(len == strlen(ref));
        CU_ASSERT_STRING_EQUAL(str, ref);
    }

    // test conversion to octal numbers
    for (i=0; i<N; i++) {
        len = SCPI_UInt32ToStrBase(val[i], str, max, 8);
        snprintf(ref, max, "%"PRIo32, val[i]);
        CU_ASSERT(len == strlen(ref));
        CU_ASSERT_STRING_EQUAL(str, ref);
    }

    // test conversion to binary numbers
    len = SCPI_UInt32ToStrBase(0, str, max, 2);
    CU_ASSERT(len == 1);
    CU_ASSERT_STRING_EQUAL(str, "0");

    len = SCPI_UInt32ToStrBase(1, str, max, 2);
    CU_ASSERT(len == 1);
    CU_ASSERT_STRING_EQUAL(str, "1");

    len = SCPI_UInt32ToStrBase(-1, str, max, 2);
    CU_ASSERT(len == 32);
    CU_ASSERT_STRING_EQUAL(str, "11111111111111111111111111111111");

    len = SCPI_UInt32ToStrBase(0x01234567, str, max, 2);
    CU_ASSERT(len == 25);
    CU_ASSERT_STRING_EQUAL(str, "1001000110100010101100111");

    len = SCPI_UInt32ToStrBase(0x89abcdef, str, max, 2);
    CU_ASSERT(len == 32);
    CU_ASSERT_STRING_EQUAL(str, "10001001101010111100110111101111");
}

static void test_Int64ToStr() {
    const size_t max=64+1;
    int64_t val[] = {0, 1, -1, INT64_MIN, INT64_MAX, 0x0123456789abcdef, 0xfedcba9876543210};
    int N = sizeof(val) / sizeof(int64_t);
    int i;
    char str[max];
    char ref[max];
    size_t len;

    // test conversion to decimal numbers
    for (i=0; i<N; i++) {
        len = SCPI_Int64ToStr(val[i], str, max);
        snprintf(ref, max, "%"PRIi64, val[i]);
        CU_ASSERT(len == strlen(ref));
        CU_ASSERT_STRING_EQUAL(str, ref);
    }
}

static void test_UInt64ToStrBase() {
    const size_t max=64+1;
    uint64_t val[] = {0, 1, -1, INT64_MIN, INT64_MAX, 0x0123456789abcdef, 0xfedcba9876543210};
    int N = sizeof(val) / sizeof(uint64_t);
    int i;
    char str[max];
    char ref[max];
    size_t len;

    // test conversion to decimal numbers
    for (i=0; i<N; i++) {
        len = SCPI_UInt64ToStrBase(val[i], str, max, 10);
        snprintf(ref, max, "%"PRIu64, val[i]);
        CU_ASSERT(len == strlen(ref));
        CU_ASSERT_STRING_EQUAL(str, ref);
    }

    // test conversion to hexadecimal numbers
    for (i=0; i<N; i++) {
        len = SCPI_UInt64ToStrBase(val[i], str, max, 16);
        snprintf(ref, max, "%"PRIX64, val[i]);
        CU_ASSERT(len == strlen(ref));
        CU_ASSERT_STRING_EQUAL(str, ref);
    }

    // test conversion to octal numbers
    for (i=0; i<N; i++) {
        len = SCPI_UInt64ToStrBase(val[i], str, max, 8);
        snprintf(ref, max, "%"PRIo64, val[i]);
        CU_ASSERT(len == strlen(ref));
        CU_ASSERT_STRING_EQUAL(str, ref);
    }

    // test conversion to binary numbers
    len = SCPI_UInt64ToStrBase(0, str, max, 2);
    CU_ASSERT(len == 1);
    CU_ASSERT_STRING_EQUAL(str, "0");

    len = SCPI_UInt64ToStrBase(1, str, max, 2);
    CU_ASSERT(len == 1);
    CU_ASSERT_STRING_EQUAL(str, "1");

    len = SCPI_UInt64ToStrBase(-1, str, max, 2);
    CU_ASSERT(len == 64);
    CU_ASSERT_STRING_EQUAL(str, "1111111111111111111111111111111111111111111111111111111111111111");

    len = SCPI_UInt64ToStrBase(0x0123456789abcdef, str, max, 2);
    CU_ASSERT(len == 57);
    CU_ASSERT_STRING_EQUAL(str, "100100011010001010110011110001001101010111100110111101111");

    len = SCPI_UInt64ToStrBase(0xfedcba9876543210, str, max, 2);
    CU_ASSERT(len == 64);
    CU_ASSERT_STRING_EQUAL(str, "1111111011011100101110101001100001110110010101000011001000010000");
}

static void test_floatToStr() {
    const size_t max=49+1;
    float val[] = {1, -1, 1.1, -1.1, 1e3, 1e30, -1.3e30, -1.3e-30};
    int N = sizeof(val) / sizeof(float);
    int i;
    char str[max];
    char ref[max];
    size_t len;

    for (i=0; i<N; i++) {
        len = SCPI_FloatToStr(val[i], str, max);
        snprintf(ref, max, "%g", val[i]);
        CU_ASSERT(len == strlen(ref));
        CU_ASSERT_STRING_EQUAL(str, ref);
    }
}

static void test_doubleToStr() {
    const size_t max=49+1;
    double val[] = {1, -1, 1.1, -1.1, 1e3, 1e30, -1.3e30, -1.3e-30};
    int N = sizeof(val) / sizeof(double);
    int i;
    char str[max];
    char ref[max];
    size_t len;

    for (i=0; i<N; i++) {
        len = SCPI_DoubleToStr(val[i], str, max);
        snprintf(ref, max, "%lg", val[i]);
        CU_ASSERT(len == strlen(ref));
        CU_ASSERT_STRING_EQUAL(str, ref);
    }
}

static void test_strBaseToInt32() {
    size_t result;
    int32_t val;

#define TEST_STR_TO_INT32(s, r, v, b)                   \
    do {                                                \
        result = strBaseToInt32(s, &val, b);            \
        CU_ASSERT_EQUAL(val, v);                        \
        CU_ASSERT_EQUAL(result, r);                     \
    } while(0)                                          \

    // TODO: extend to corner cases, use scanf as reference
    TEST_STR_TO_INT32("", 0, 0, 10);
    TEST_STR_TO_INT32("1", 1, 1, 10);
    TEST_STR_TO_INT32("10", 2, 10, 10);
    TEST_STR_TO_INT32("-50", 3, -50, 10);
    TEST_STR_TO_INT32("100MHz", 3, 100, 10);
    TEST_STR_TO_INT32("MHz", 0, 0, 10);
    TEST_STR_TO_INT32("1.4", 1, 1, 10);
    TEST_STR_TO_INT32(" 1", 2, 1, 10);
    TEST_STR_TO_INT32(" +100", 5, 100, 10); // space and +
    TEST_STR_TO_INT32("FF", 2, 255, 16); // hexadecimal FF
    TEST_STR_TO_INT32("77", 2, 63, 8); // octal 77
    TEST_STR_TO_INT32("18", 1, 1, 8); // octal 1, 8 is ignored
}

static void test_strBaseToUInt32() {
    size_t result;
    uint32_t val;

#define TEST_STR_TO_UINT32(s, r, v, b)                  \
    do {                                                \
        result = strBaseToUInt32(s, &val, b);           \
        CU_ASSERT_EQUAL(val, v);                        \
        CU_ASSERT_EQUAL(result, r);                     \
    } while(0)                                          \

    // TODO: extend to corner cases, use scanf as reference
    TEST_STR_TO_UINT32("", 0, 0, 10);
    TEST_STR_TO_UINT32("1", 1, 1, 10);
    TEST_STR_TO_UINT32("10", 2, 10, 10);
    TEST_STR_TO_UINT32("100MHz", 3, 100, 10);
    TEST_STR_TO_UINT32("MHz", 0, 0, 10);
    TEST_STR_TO_UINT32("1.4", 1, 1, 10);
    TEST_STR_TO_UINT32(" 1", 2, 1, 10);
    TEST_STR_TO_UINT32(" +100", 5, 100, 10); // space and +
    TEST_STR_TO_UINT32("FF", 2, 255, 16); // hexadecimal FF
    TEST_STR_TO_UINT32("77", 2, 63, 8); // octal 77
    TEST_STR_TO_UINT32("18", 1, 1, 8); // octal 1, 8 is ignored
    TEST_STR_TO_UINT32("FFFFFFFF", 8, 0xffffffffu, 16); // octal 1, 8 is ignored
}

static void test_strBaseToInt64() {
    size_t result;
    int64_t val;

#define TEST_STR_TO_INT64(s, r, v, b)                   \
    do {                                                \
        result = strBaseToInt64(s, &val, b);            \
        CU_ASSERT_EQUAL(val, v);                        \
        CU_ASSERT_EQUAL(result, r);                     \
    } while(0)                                          \

    // TODO: extend to corner cases, use scanf as reference
    TEST_STR_TO_INT64("", 0, 0, 10);
    TEST_STR_TO_INT64("1", 1, 1, 10);
    TEST_STR_TO_INT64("10", 2, 10, 10);
    TEST_STR_TO_INT64("-50", 3, -50, 10);
    TEST_STR_TO_INT64("100MHz", 3, 100, 10);
    TEST_STR_TO_INT64("MHz", 0, 0, 10);
    TEST_STR_TO_INT64("1.4", 1, 1, 10);
    TEST_STR_TO_INT64(" 1", 2, 1, 10);
    TEST_STR_TO_INT64(" +100", 5, 100, 10); // space and +
    TEST_STR_TO_INT64("FF", 2, 255, 16); // hexadecimal FF
    TEST_STR_TO_INT64("77", 2, 63, 8); // octal 77
    TEST_STR_TO_INT64("18", 1, 1, 8); // octal 1, 8 is ignored
}

static void test_strBaseToUInt64() {
    size_t result;
    uint64_t val;

#define TEST_STR_TO_UINT64(s, r, v, b)                  \
    do {                                                \
        result = strBaseToUInt64(s, &val, b);           \
        CU_ASSERT_EQUAL(val, v);                        \
        CU_ASSERT_EQUAL(result, r);                     \
    } while(0)                                          \

    // TODO: extend to corner cases, use scanf as reference
    TEST_STR_TO_UINT64("", 0, 0, 10);
    TEST_STR_TO_UINT64("1", 1, 1, 10);
    TEST_STR_TO_UINT64("10", 2, 10, 10);
    TEST_STR_TO_UINT64("100MHz", 3, 100, 10);
    TEST_STR_TO_UINT64("MHz", 0, 0, 10);
    TEST_STR_TO_UINT64("1.4", 1, 1, 10);
    TEST_STR_TO_UINT64(" 1", 2, 1, 10);
    TEST_STR_TO_UINT64(" +100", 5, 100, 10); // space and +
    TEST_STR_TO_UINT64("FF", 2, 255, 16); // hexadecimal FF
    TEST_STR_TO_UINT64("77", 2, 63, 8); // octal 77
    TEST_STR_TO_UINT64("18", 1, 1, 8); // octal 1, 8 is ignored
    TEST_STR_TO_UINT64("FFFFFFFF", 8, 0xffffffffu, 16); // octal 1, 8 is ignored
}

static void test_strToDouble() {
    double val;
    size_t result;

#define TEST_STR_TO_DOUBLE(s, r, v)                     \
    do {                                                \
        result = strToDouble(s, &val);                  \
        CU_ASSERT_EQUAL(result, r);                     \
        CU_ASSERT_DOUBLE_EQUAL(v, val, 0.000001);       \
    } while(0);                                         \

    TEST_STR_TO_DOUBLE("", 0, 0.0);

    TEST_STR_TO_DOUBLE(" 1", 2, 1.0);

    TEST_STR_TO_DOUBLE("1", 1, 1.0);
    TEST_STR_TO_DOUBLE("10", 2, 10.0);
    TEST_STR_TO_DOUBLE("10MHz", 2, 10.0);
    TEST_STR_TO_DOUBLE("MHz", 0, 0.0);
    TEST_STR_TO_DOUBLE("1E", 1, 1.0);
    TEST_STR_TO_DOUBLE("1E3", 3, 1000.0);

    TEST_STR_TO_DOUBLE("1.2", 3, 1.2);
    TEST_STR_TO_DOUBLE("10.2", 4, 10.2);
    TEST_STR_TO_DOUBLE("10.2MHz", 4, 10.2);
    TEST_STR_TO_DOUBLE("MHz", 0, 0.0);
    TEST_STR_TO_DOUBLE("1.2E", 3, 1.2);
    TEST_STR_TO_DOUBLE("1.2E3", 5, 1200.0);

    TEST_STR_TO_DOUBLE("-1.2", 4, -1.2);

}

static void test_compareStr() {

    CU_ASSERT_TRUE(compareStr("abcd", 1, "afgh", 1));
    CU_ASSERT_TRUE(compareStr("ABCD", 4, "abcd", 4));
    CU_ASSERT_TRUE(compareStr("AbCd", 3, "AbCE", 3));
    CU_ASSERT_TRUE(compareStr("ABCD", 1, "a", 1));

    CU_ASSERT_FALSE(compareStr("abcd", 1, "efgh", 1));
    CU_ASSERT_FALSE(compareStr("ABCD", 4, "abcd", 3));
}

static void test_compareStrAndNum() {
    int32_t num;

    CU_ASSERT_TRUE(compareStrAndNum("abcd", 1, "afgh", 1, NULL));
    CU_ASSERT_TRUE(compareStrAndNum("ABCD", 4, "abcd", 4, NULL));
    CU_ASSERT_TRUE(compareStrAndNum("AbCd", 3, "AbCE", 3, NULL));
    CU_ASSERT_TRUE(compareStrAndNum("ABCD", 1, "a", 1, NULL));

    CU_ASSERT_FALSE(compareStrAndNum("abcd", 1, "efgh", 1, NULL));
    CU_ASSERT_FALSE(compareStrAndNum("ABCD", 4, "abcd", 3, NULL));

    CU_ASSERT_TRUE(compareStrAndNum("abcd", 4, "abcd1", 5, NULL));
    CU_ASSERT_TRUE(compareStrAndNum("abcd", 4, "abcd123", 7, NULL));
    CU_ASSERT_FALSE(compareStrAndNum("abcd", 4, "abcd12A", 7, NULL));
    CU_ASSERT_FALSE(compareStrAndNum("abcd", 4, "abcdB12", 7, NULL));
    CU_ASSERT_FALSE(compareStrAndNum("abdd", 4, "abcd132", 7, NULL));

#define TEST_COMPARE_STR_AND_NUM(s1, l1, s2, l2, v, r)              \
    do {                                                            \
        num = -1;                                                    \
        CU_ASSERT_EQUAL(compareStrAndNum(s1, l1, s2, l2, &num),r);  \
        CU_ASSERT_EQUAL(num, v);                                    \
    } while(0);                                                     \

    TEST_COMPARE_STR_AND_NUM("abcd", 4, "abcd", 4, -1, TRUE);
    TEST_COMPARE_STR_AND_NUM("abcd", 4, "abcd1", 5, 1, TRUE);
    TEST_COMPARE_STR_AND_NUM("abcd", 4, "abcd123", 7, 123, TRUE);
    TEST_COMPARE_STR_AND_NUM("abcd", 4, "abcd12A", 7, -1, FALSE);
    TEST_COMPARE_STR_AND_NUM("abcd", 4, "abcdB12", 7, -1, FALSE);
    TEST_COMPARE_STR_AND_NUM("abdd", 4, "abcd132", 7, -1, FALSE);
}

static void test_matchPattern() {
    scpi_bool_t result;

#define TEST_MATCH_PATTERN(p, s, r)                             \
    do {                                                        \
        result = matchPattern(p, strlen(p), s, strlen(s), NULL);\
        CU_ASSERT_EQUAL(result, r);                             \
    } while(0)                                                  \

    TEST_MATCH_PATTERN("A", "a", TRUE);
    TEST_MATCH_PATTERN("Ab", "a", TRUE);
    TEST_MATCH_PATTERN("Ab", "ab", TRUE);
    TEST_MATCH_PATTERN("Ab", "aB", TRUE);
    TEST_MATCH_PATTERN("AB", "a", FALSE);
    TEST_MATCH_PATTERN("Ab#", "aB", TRUE);
    TEST_MATCH_PATTERN("Ab#", "aB10", TRUE);
    TEST_MATCH_PATTERN("Ab#", "a10", TRUE);
}

static void test_matchCommand() {
    scpi_bool_t result;
    int32_t values[20];

    #define TEST_MATCH_COMMAND(p, s, r)                         \
    do {                                                        \
        result = matchCommand(p, s, strlen(s), NULL, 0, 0);     \
        CU_ASSERT_EQUAL(result, r);                             \
    } while(0)                                                  \

    #define NOPAREN(...) __VA_ARGS__

    #define TEST_MATCH_COMMAND2(p, s, r, v)                     \
    do {                                                        \
        int32_t evalues[] = {NOPAREN v};                        \
        unsigned int cnt = (sizeof(evalues)/4);                 \
        result = matchCommand(p, s, strlen(s), values, 20, -1); \
        CU_ASSERT_EQUAL(result, r);                             \
        {unsigned int i; for (i = 0; i<cnt; i++) {              \
            CU_ASSERT_EQUAL(evalues[i], values[i]);             \
        }}                                                      \
    } while(0)                                                  \

    TEST_MATCH_COMMAND("A", "a", TRUE);
    TEST_MATCH_COMMAND("Ab", "a", TRUE);
    TEST_MATCH_COMMAND("Ab", "ab", TRUE);
    TEST_MATCH_COMMAND("Ab", "aB", TRUE);
    TEST_MATCH_COMMAND("AB", "a", FALSE);
    TEST_MATCH_COMMAND("ABc:AACddd", "ab:aac", TRUE);
    TEST_MATCH_COMMAND("ABc:AACddd", "abc:aac", TRUE);
    TEST_MATCH_COMMAND("ABc:AACddd", "abc:aacddd", TRUE);
    TEST_MATCH_COMMAND("ABc:AACddd", "abc:aacdd", FALSE);
    TEST_MATCH_COMMAND("ABc:AACddd", "a:aac", FALSE);
    TEST_MATCH_COMMAND("ABc:AACddd", ":ab:aac", TRUE);
    TEST_MATCH_COMMAND("ABc:AACddd", ":abc:aac", TRUE);
    TEST_MATCH_COMMAND("ABc:AACddd", ":abc:aacddd", TRUE);
    TEST_MATCH_COMMAND("ABc:AACddd", ":abc:aacdd", FALSE);
    TEST_MATCH_COMMAND("ABc:AACddd", ":a:aac", FALSE);
    TEST_MATCH_COMMAND("?", "?", TRUE);
    TEST_MATCH_COMMAND("A?", "A?", TRUE);
    TEST_MATCH_COMMAND("A", "A?", FALSE);
    TEST_MATCH_COMMAND("A?", "A", FALSE);
    TEST_MATCH_COMMAND("[:ABc]:AACddd", ":ab:aac", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("[:ABc]:AACddd", "aac", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("[:ABc]:AACddd", "aac?", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("[:ABc]:AACddd?", ":ab:aac?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("[:ABc]:AACddd?", "aac?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("[:ABc]:AACddd?", "aac", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd]:CDe", "ab:bc:cd", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd]:CDe", "ab:cd", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd]:CDe", "ab:cd?", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd]:CDe?", "ab:bc:cd?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd]:CDe?", "ab:cd?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd]:CDe?", "ab:cd", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("ABc:BCd[:CDe]", "ab:bc:cd", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc:BCd[:CDe]", "ab:bc", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc:BCd[:CDe]", "ab:bc?", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("ABc:BCd[:CDe]?", "ab:bc:cd?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc:BCd[:CDe]?", "ab:bc?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc:BCd[:CDe]?", "ab:bc", FALSE); // test optional keyword

    TEST_MATCH_COMMAND("[:ABc]:BCd[:CDe]", "ab:bc:cd", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("[:ABc]:BCd[:CDe]", "ab:bc", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("[:ABc]:BCd[:CDe]", "bc:cd", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("[:ABc]:BCd[:CDe]", "ab:bc?", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("[:ABc]:BCd[:CDe]", "bc:cd?", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("[:ABc]:BCd[:CDe]?", "ab:bc:cd?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("[:ABc]:BCd[:CDe]?", "ab:bc?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("[:ABc]:BCd[:CDe]?", "bc:cd?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("[:ABc]:BCd[:CDe]?", "ab:bc", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("[:ABc]:BCd[:CDe]?", "bc:cd", FALSE); // test optional keyword

    TEST_MATCH_COMMAND("ABc[:BCd][:CDe]", "ab:bc:cd", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe]", "ab:bc", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe]", "ab:cd", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe]", "ab:bc?", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe]", "ab:cd?", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe]?", "ab:bc:cd?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe]?", "ab:bc?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe]?", "ab:cd?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe]?", "ab:bc", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe]?", "ab:cd", FALSE); // test optional keyword

    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]", "ab:bc:cd:de", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]", "ab:bc:cd", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]", "ab:bc:de", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]", "ab:cd:de", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]", "ab:bc", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]", "ab:cd", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]", "ab:de", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]", "ab", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]", "ab:bc:cd?", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]", "ab:bc:de?", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]", "ab:cd:de?", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]", "ab:bc?", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]", "ab:cd?", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]", "ab:de?", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]", "ab?", FALSE); // test optional keyword

    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]?", "ab:bc:cd:de?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]?", "ab:bc:cd?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]?", "ab:bc:de?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]?", "ab:cd:de?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]?", "ab:bc?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]?", "ab:cd?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]?", "ab:de?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]?", "ab?", TRUE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]?", "ab:bc:cd", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]?", "ab:bc:de", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]?", "ab:cd:de", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]?", "ab:bc", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]?", "ab:cd", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]?", "ab:de", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("ABc[:BCd][:CDe][:DEf]?", "ab", FALSE); // test optional keyword
    TEST_MATCH_COMMAND("*IDN?", "idn", FALSE); // common command
    TEST_MATCH_COMMAND("*IDN?", "idn?", FALSE); // common command
    TEST_MATCH_COMMAND("*IDN?", "*idn", FALSE); // common command
    TEST_MATCH_COMMAND("*IDN?", "*idn?", TRUE); // common command
    TEST_MATCH_COMMAND("*IDN?", ":idn", FALSE); // common command
    TEST_MATCH_COMMAND("*IDN?", ":idn?", FALSE); // common command
    TEST_MATCH_COMMAND("*IDN?", ":*idn", FALSE); // common command
    TEST_MATCH_COMMAND("*IDN?", ":*idn?", FALSE); // common command

    TEST_MATCH_COMMAND("MEASure[:SCALar]:CURRent[:DC]?", ":MEAS?", FALSE);
    TEST_MATCH_COMMAND("MEASure[:SCALar]:CURRent[:DC]?", "MEAS?", FALSE);
    TEST_MATCH_COMMAND("MEASure[:SCALar]:CURRent[:DC]?", ":MEAS:DC?", FALSE);
    TEST_MATCH_COMMAND("MEASure[:SCALar]:CURRent[:DC]?", "MEAS:DC?", FALSE);
    TEST_MATCH_COMMAND("MEASure[:SCALar]:CURRent[:DC]?", ":MEAS:CURR?", TRUE);
    TEST_MATCH_COMMAND("MEASure[:SCALar]:CURRent[:DC]?", "MEAS:CURR?", TRUE);
    TEST_MATCH_COMMAND("MEASure[:SCALar]:CURRent[:DC]?", ":MEAS:SCAL:CURR?", TRUE);
    TEST_MATCH_COMMAND("MEASure[:SCALar]:CURRent[:DC]?", "MEAS:SCAL:CURR?", TRUE);
    TEST_MATCH_COMMAND("MEASure[:SCALar]:CURRent[:DC]?", ":MEAS:SCAL:CURR:DC?", TRUE);
    TEST_MATCH_COMMAND("MEASure[:SCALar]:CURRent[:DC]?", "MEAS:SCAL:CURR:DC?", TRUE);
    TEST_MATCH_COMMAND("MEASure[:SCALar]:CURRent[:DC]?", ":MEAS:CURR:DC?", TRUE);
    TEST_MATCH_COMMAND("MEASure[:SCALar]:CURRent[:DC]?", "MEAS:CURR:DC?", TRUE);

    TEST_MATCH_COMMAND("ABCdef#", "abc", TRUE); // test numeric parameter
    TEST_MATCH_COMMAND("ABCdef#", "abc1324", TRUE); // test numeric parameter
    TEST_MATCH_COMMAND("ABCdef#", "abcDef1324", TRUE); // test numeric parameter
    TEST_MATCH_COMMAND("ABCdef#", "abcDef124b", FALSE); // test numeric parameter

    TEST_MATCH_COMMAND("OUTPut#:MODulation#:FM#", "abc", FALSE); // test numeric parameter
    TEST_MATCH_COMMAND("OUTPut#:MODulation#:FM#", "outp1:mod10:fm", TRUE); // test numeric parameter
    TEST_MATCH_COMMAND("OUTPut#:MODulation#:FM#", "output1:mod10:fm", TRUE); // test numeric parameter
    TEST_MATCH_COMMAND("OUTPut#:MODulation#:FM#", "outp1:modulation:fm5", TRUE); // test numeric parameter
    TEST_MATCH_COMMAND("OUTPut#:MODulation#:FM#", "output:mod:fm", TRUE); // test numeric parameter
    TEST_MATCH_COMMAND("OUTPut#:MODulation#:FM#", "outp1:mod10a:fm", FALSE); // test numeric parameter
    TEST_MATCH_COMMAND("OUTPut#[:MODulation#]:FM#", "outp1:fm", TRUE); // test numeric parameter
    TEST_MATCH_COMMAND("OUTPut#[:MODulation#]:FM#", "outp1:mod10:fm", TRUE); // test numeric parameter
    TEST_MATCH_COMMAND("OUTPut#[:MODulation#]:FM#", "outp1:fm2", TRUE); // test numeric parameter
    TEST_MATCH_COMMAND("OUTPut#[:MODulation#]:FM#", "output:fm", TRUE); // test numeric parameter

    TEST_MATCH_COMMAND2("OUTPut#:MODulation#:FM#", "outp3:mod10:fm", TRUE, (3, 10, -1)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#:MODulation#:FM#", "output3:mod10:fm", TRUE, (3, 10, -1)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#:MODulation#:FM#", "outp30:modulation:fm5", TRUE, (30, -1, 5)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#:MODulation#:FM#", "output:mod:fm", TRUE, (-1, -1, -1)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#[:MODulation#]:FM#", "outp3:fm", TRUE, (3, -1, -1)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#[:MODulation#]:FM#", "outp3:mod10:fm", TRUE, (3, 10, -1)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#[:MODulation#]:FM#", "outp3:fm2", TRUE, (3, -1, 2)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#[:MODulation#]:FM#", "output:fm", TRUE, (-1, -1, -1)); // test numeric parameter

    TEST_MATCH_COMMAND2("OUTPut#:MODulation:FM#", "outp3:mod:fm", TRUE, (3, -1)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#:MODulation:FM#", "output3:mod:fm", TRUE, (3, -1)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#:MODulation:FM#", "outp30:modulation:fm5", TRUE, (30, 5)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#:MODulation:FM#", "output:mod:fm", TRUE, (-1, -1)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#[:MODulation]:FM#", "outp3:fm", TRUE, (3, -1)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#[:MODulation]:FM#", "outp3:mod:fm", TRUE, (3, -1)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#[:MODulation]:FM#", "outp3:fm2", TRUE, (3, 2)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#[:MODulation]:FM#", "output:fm", TRUE, (-1, -1)); // test numeric parameter

    TEST_MATCH_COMMAND2("OUTPut#:MODulation#:FM", "outp3:mod10:fm", TRUE, (3, 10)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#:MODulation#:FM", "output3:mod10:fm", TRUE, (3, 10)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#:MODulation#:FM", "outp30:modulation:fm", TRUE, (30, -1)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#:MODulation#:FM", "output:mod:fm", TRUE, (-1, -1)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#[:MODulation#]:FM", "outp3:fm", TRUE, (3, -1)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#[:MODulation#]:FM", "outp3:mod10:fm", TRUE, (3, 10)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#[:MODulation#]:FM", "outp3:fm", TRUE, (3, -1)); // test numeric parameter
    TEST_MATCH_COMMAND2("OUTPut#[:MODulation#]:FM", "output:fm", TRUE, (-1, -1)); // test numeric parameter
}

static void test_composeCompoundCommand(void) {

#define TEST_COMPOSE_COMMAND(b, c1_len, c2_pos, c2_len, c2_final, r)    \
    {                                                                   \
        char buffer[100];                                               \
        scpi_token_t cmd_prev, cmd_curr;                                \
        cmd_prev.ptr = buffer;                                          \
        cmd_prev.len = c1_len;                                          \
        cmd_curr.ptr = buffer + c2_pos;                                 \
        cmd_curr.len = c2_len;                                          \
        scpi_bool_t res;                                                \
                                                                        \
        strcpy(buffer, b);                                              \
        res = composeCompoundCommand(&cmd_prev, &cmd_curr);             \
        CU_ASSERT_EQUAL(res, r);                                        \
        CU_ASSERT_EQUAL(cmd_curr.len, strlen(c2_final));                \
        CU_ASSERT_STRING_EQUAL(cmd_curr.ptr, c2_final);                 \
    }\

    TEST_COMPOSE_COMMAND("A:B;C", 3, 4, 1, "A:C", TRUE);
    TEST_COMPOSE_COMMAND("A:B;DD", 3, 4, 2, "A:DD", TRUE);
    TEST_COMPOSE_COMMAND("A:B", 0, 0, 3, "A:B", TRUE);
    TEST_COMPOSE_COMMAND("*IDN? ; ABC", 5, 8, 3, "ABC", TRUE);
    TEST_COMPOSE_COMMAND("A:B;*IDN?", 3, 4, 5, "*IDN?", TRUE);
    TEST_COMPOSE_COMMAND("A:B;:C", 3, 4, 2, ":C", TRUE);
    TEST_COMPOSE_COMMAND("B;C", 1, 2, 1, "C", TRUE);
    TEST_COMPOSE_COMMAND("A:B;C:D", 3, 4, 3, "A:C:D", TRUE);
    TEST_COMPOSE_COMMAND(":A:B;C", 4, 5, 1, ":A:C", TRUE);
    TEST_COMPOSE_COMMAND(":A:B;:C", 4, 5, 2, ":C", TRUE);
    TEST_COMPOSE_COMMAND(":A;C", 2, 3, 1, ":C", TRUE);
}

int main() {
    unsigned int result;
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("SCPI Utils", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if (0
            || (NULL == CU_add_test(pSuite, "strnpbrk", test_strnpbrk))
            || (NULL == CU_add_test(pSuite, "Int32ToStr", test_Int32ToStr))
            || (NULL == CU_add_test(pSuite, "UInt32ToStrBase", test_UInt32ToStrBase))
            || (NULL == CU_add_test(pSuite, "Int64ToStr", test_Int64ToStr))
            || (NULL == CU_add_test(pSuite, "UInt64ToStrBase", test_UInt64ToStrBase))
            || (NULL == CU_add_test(pSuite, "floatToStr", test_floatToStr))
            || (NULL == CU_add_test(pSuite, "doubleToStr", test_doubleToStr))
            || (NULL == CU_add_test(pSuite, "strBaseToInt32", test_strBaseToInt32))
            || (NULL == CU_add_test(pSuite, "strBaseToUInt32", test_strBaseToUInt32))
            || (NULL == CU_add_test(pSuite, "strBaseToInt64", test_strBaseToInt64))
            || (NULL == CU_add_test(pSuite, "strBaseToUInt64", test_strBaseToUInt64))
            || (NULL == CU_add_test(pSuite, "strToDouble", test_strToDouble))
            || (NULL == CU_add_test(pSuite, "compareStr", test_compareStr))
            || (NULL == CU_add_test(pSuite, "compareStrAndNum", test_compareStrAndNum))
            || (NULL == CU_add_test(pSuite, "matchPattern", test_matchPattern))
            || (NULL == CU_add_test(pSuite, "matchCommand", test_matchCommand))
            || (NULL == CU_add_test(pSuite, "composeCompoundCommand", test_composeCompoundCommand))
            ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    result = CU_get_number_of_tests_failed();
    CU_cleanup_registry();
    return result ? result : CU_get_error();
}

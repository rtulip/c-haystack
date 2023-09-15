#include <stdio.h>
#include "sv.h"
#include <assert.h>
#include <execinfo.h>

#define array_len(array) (sizeof(array)/sizeof(array[0]))
#define TEST(fn) ((test_fn_t){.fn_name = #fn, .fn_ptr = fn})

typedef struct test_fn_t {
    const char* fn_name;
    void (*fn_ptr)(void);
} test_fn_t;


static void _test_sv_new(void) {
    StringView sv1 = sv_new("Hello World!");
    assert(sv1.length == 12);
}

static void _test_sv_copy(void) {
    StringView sv1 = sv_new("Hello World!");
    StringView sv2 = sv1;
    assert(sv1.length == sv2.length);
    assert(sv1.slice == sv2.slice);
}

static void _test_sv_split_at_pattern(void) {
    // Test Expected case
    {
        StringView sv = sv_new("Hello World");        
        StringView hello = sv_split_at_pattern(&sv, " ");
        assert(sv_equals(&hello, "Hello"));
        assert(sv_equals(&sv, "World"));
    }

    // Test only first match is removed.
    {
        StringView sv = sv_new("Hello   World");
        StringView hello = sv_split_at_pattern(&sv, " ");
        assert(sv_equals(&hello, "Hello"));
        assert(sv_equals(&sv, "  World"));
    }

    // Test longer pattern
    {
        StringView sv = sv_new("HelloPatternWorld");
        StringView hello = sv_split_at_pattern(&sv, "Pattern");
        assert(sv_equals(&hello, "Hello"));
        assert(sv_equals(&sv, "World"));
    }

    // Test pattern not found
    {
        StringView sv = sv_new("Hello World");
        StringView empty = sv_split_at_pattern(&sv, "foo");
        assert(sv_equals(&empty, ""));
        assert(sv_equals(&sv, "Hello World"));
    }

}

static void _sv_test_substr(void)
{
    StringView sv = sv_new("Hello World");

    {
        StringView test = sv_substring(&sv, 0, 12);
        assert(sv_equals(&test, ""));
    }

    {
        StringView test = sv_substring(&sv, 0, 11);
        assert(sv_equals(&test, "Hello World"));
    }

    {
        StringView test = sv_substring(&sv, 11, 0);
        assert(sv_equals(&test, ""));
    }

    {
        StringView test = sv_substring(&sv, 5, 5);
        assert(sv_equals(&test, ""));
    }

    {
        StringView test = sv_substring(&sv, 0, 5); 
        assert(sv_equals(&test, "Hello"));
    }

    {
        StringView test = sv_substring(&sv, 5, 6);
        assert(sv_equals(&test, " "));
    }

    {
        StringView test = sv_substring(&sv, 6, 11);
        assert(sv_equals(&test, "World"));
    } 

}

int main(void)
{
    
    register_sv_printf();

    test_fn_t tests[] = {
        TEST(_test_sv_new),
        TEST(_test_sv_copy),
        TEST(_test_sv_split_at_pattern),
        TEST(_sv_test_substr),
    };
    
    for (size_t i = 0; i < array_len(tests); i++) {
        printf("===== %s =====\n", tests[i].fn_name);
        tests[i].fn_ptr();
    }

    printf("----- All tests complete -----\n");


    return 0;

}
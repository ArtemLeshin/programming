#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

void shellSort(int array[], int len);

static void test_regular_array(void **state) {
    int arr[] = {5, 2, 9, 1, 5, 6};
    int expected[] = {1, 2, 5, 5, 6, 9};
    shellSort(arr, 6);
    
    for (int i = 0; i < 6; i++) {
        assert_int_equal(arr[i], expected[i]);
    }
}

static void test_reverse_array(void **state) {
    int arr[] = {30, 20, 10};
    int expected[] = {10, 20, 30};
    shellSort(arr, 3);
    
    for (int i = 0; i < 3; i++) {
        assert_int_equal(arr[i], expected[i]);
    }
}

static void test_ascending_array(void **state) {
    int arr[] = {1, 2, 3, 7, 24};
    int expected[] = {1, 2, 3, 7, 24};
    shellSort(arr, 5);
    
    for (int i = 0; i < 5; i++) {
        assert_int_equal(arr[i], expected[i]);
    }
}

static void test_all_equal(void **state) {
    int arr[] = {2, 2, 2, 2, 2};
    int expected[] = {2, 2, 2, 2, 2};
    shellSort(arr, 5);
    
    for (int i = 0; i < 5; i++) {
        assert_int_equal(arr[i], expected[i]);
    }
}

static void test_empty_array(void **state) {
    int arr[] = {};
    shellSort(arr, 0);
    assert_true(1);  
}

static void test_duplicates(void **state) {
    int arr[] = {10, 2, 4, 2, 1};
    int expected[] = {1, 2, 2, 4, 10};
    shellSort(arr, 5);
    
    for (int i = 0; i < 5; i++) {
        assert_int_equal(arr[i], expected[i]);
    }
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_regular_array),
        cmocka_unit_test(test_reverse_array),
        cmocka_unit_test(test_ascending_array),
        cmocka_unit_test(test_all_equal),
        cmocka_unit_test(test_empty_array),
        cmocka_unit_test(test_duplicates),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
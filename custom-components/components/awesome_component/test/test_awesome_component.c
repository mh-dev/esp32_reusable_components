#include "unity.h"
#include "awesome_component.h"

TEST_CASE("add_successful", "[awesome_component]") {
    int number1 = 123;
    int number2 = 321;
    int result = awesome_component_add(number1, number2);

    TEST_ASSERT_EQUAL_INT32(444, result);
}

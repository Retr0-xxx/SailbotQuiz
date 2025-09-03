#include "stdio.h"
#include "cutest/CuTest.h"
#include "standard_calc.h"

/**************** Tests for bound_to_180() *******************/
void test_bound_basic1(CuTest *tc) {
    CuAssertDblEquals(tc, 0, bound_to_180(0), 0.0001);
}

/**************** Tests for is_angle_between() *******************/
void test_between_basic1(CuTest *tc) {
    CuAssertTrue(tc, is_angle_between(0, 1, 2));
}

//ADDED TESTS
/*************** bound_to_180() tests ****************/

void test_bound_zero(CuTest* tc) {
    CuAssertDblEquals(tc, 0.0, bound_to_180(0.0f), 1e-6);
}

void test_bound_identity_positive(CuTest* tc) {
    CuAssertDblEquals(tc, 135.0, bound_to_180(135.0f), 1e-6);
}

void test_bound_wrap_positive(CuTest* tc) {
    // 200 -> -160
    CuAssertDblEquals(tc, -160.0, bound_to_180(200.0f), 1e-6);
}

void test_bound_wrap_many_turns(CuTest* tc) {
    // 720 -> 0
    CuAssertDblEquals(tc, 0.0, bound_to_180(720.0f), 1e-6);
}

void test_bound_negative_in_range(CuTest* tc) {
    CuAssertDblEquals(tc, -30.0, bound_to_180(-30.0f), 1e-6);
}

void test_bound_negative_large(CuTest* tc) {
    // -540 -> -180
    CuAssertDblEquals(tc, -180.0, bound_to_180(-540.0f), 1e-6);
}

void test_bound_edge_180_maps_to_minus180(CuTest* tc) {
    CuAssertDblEquals(tc, -180.0, bound_to_180(180.0f), 1e-6);
}

void test_bound_edge_minus181(CuTest* tc) {
    // -181 -> 179
    CuAssertDblEquals(tc, 179.0, bound_to_180(-181.0f), 1e-6);
}

void test_bound_edge_181(CuTest* tc) {
    // 181 -> -179
    CuAssertDblEquals(tc, -179.0, bound_to_180(181.0f), 1e-6);
}

void test_bound_360_is_zero(CuTest* tc) {
    CuAssertDblEquals(tc, 0.0, bound_to_180(360.0f), 1e-6);
}

/*************** is_angle_between() tests ************/

void test_between_basic_true(CuTest* tc) {
    CuAssertTrue(tc, is_angle_between(0.0f, 45.0f, 90.0f));
}

void test_between_basic_false(CuTest* tc) {
    CuAssertTrue(tc, !is_angle_between(0.0f, -45.0f, 90.0f));
}

void test_between_includes_first_endpoint(CuTest* tc) {
    CuAssertTrue(tc, is_angle_between(45.0f, 45.0f, 90.0f));
}

void test_between_includes_second_endpoint(CuTest* tc) {
    CuAssertTrue(tc, is_angle_between(45.0f, 90.0f, 90.0f));
}

void test_between_wraparound_forward(CuTest* tc) {
    // From 170 to -170 (i.e., +20° through 180 wrap), 175 is between
    CuAssertTrue(tc, is_angle_between(170.0f, 175.0f, -170.0f));
}

void test_between_wraparound_backward(CuTest* tc) {
    // From 10 down to -20 (i.e., -30° direction), 5 is between
    CuAssertTrue(tc, is_angle_between(10.0f, 5.0f, -20.0f));
}

void test_between_reflex_false(CuTest* tc) {
    // Going negative from 350 to 300, 10 lies the other way
    CuAssertTrue(tc, !is_angle_between(350.0f, 10.0f, 300.0f));
}

void test_between_same_start_end_only_same_middle_true(CuTest* tc) {
    CuAssertTrue(tc, is_angle_between(10.0f, 10.0f, 10.0f));   // same angle
    CuAssertTrue(tc, !is_angle_between(10.0f, 20.0f, 10.0f));  // different middle
}

void test_between_near_180_wrap_true(CuTest* tc) {
    // Short positive arc from 179 to -170 is +11°, -179 (i.e., +2° from 179) is between
    CuAssertTrue(tc, is_angle_between(179.0f, -179.0f, -170.0f));
}

void test_between_outside_due_to_wrap(CuTest* tc) {
    // Short arc from 179 to -179 is +2°, -170 is outside
    CuAssertTrue(tc, !is_angle_between(179.0f, -170.0f, -179.0f));
}

int main(int argc, char const *argv[]) {
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, test_bound_basic1);
    SUITE_ADD_TEST(suite, test_between_basic1);

     /* bound_to_180 */
    SUITE_ADD_TEST(suite, test_bound_zero);
    SUITE_ADD_TEST(suite, test_bound_identity_positive);
    SUITE_ADD_TEST(suite, test_bound_wrap_positive);
    SUITE_ADD_TEST(suite, test_bound_wrap_many_turns);
    SUITE_ADD_TEST(suite, test_bound_negative_in_range);
    SUITE_ADD_TEST(suite, test_bound_negative_large);
    SUITE_ADD_TEST(suite, test_bound_edge_180_maps_to_minus180);
    SUITE_ADD_TEST(suite, test_bound_edge_minus181);
    SUITE_ADD_TEST(suite, test_bound_edge_181);
    SUITE_ADD_TEST(suite, test_bound_360_is_zero);

    /* is_angle_between */
    SUITE_ADD_TEST(suite, test_between_basic_true);
    SUITE_ADD_TEST(suite, test_between_basic_false);
    SUITE_ADD_TEST(suite, test_between_includes_first_endpoint);
    SUITE_ADD_TEST(suite, test_between_includes_second_endpoint);
    SUITE_ADD_TEST(suite, test_between_wraparound_forward);
    SUITE_ADD_TEST(suite, test_between_wraparound_backward);
    SUITE_ADD_TEST(suite, test_between_reflex_false);
    SUITE_ADD_TEST(suite, test_between_same_start_end_only_same_middle_true);
    SUITE_ADD_TEST(suite, test_between_near_180_wrap_true);
    SUITE_ADD_TEST(suite, test_between_outside_due_to_wrap);

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    return suite->failCount > 0 ? 1 : 0;
}

#ifndef CSE167_MathTestBench_h
#define CSE167_MathTestBench_h

#include <iostream>

class MathTestBench
{
    
private:
    
    //Helper Functions
    static void printTestLine(std::string, bool);
    static void printTestsPassedLine(std::string, int, int);
    static bool approx(float, float);
    
    //Vector 3 Tests
    static bool test_v3_add(void);
    static bool test_v3_op_plus(void);
    static bool test_v3_subtract(void);
    static bool test_v3_op_minus(void);
    static bool test_v3_negate(void);
    static bool test_v3_scale(void);
    static bool test_v3_multiply_v(void);
    static bool test_v3_op_star_v(void);
    static bool test_v3_multiply_f(void);
    static bool test_v3_op_star_f(void);
    static bool test_v3_dot(void);
    static bool test_v3_cross(void);
    static bool test_v3_angle(void);
    static bool test_v3_magnitude(void);
    static bool test_v3_magnitude_2(void);
    static bool test_v3_normalize(void);
    static bool test_v3_normalize_2(void);
    
    //Vector 4 Tests
    static bool test_v4_add(void);
    static bool test_v4_op_plus(void);
    static bool test_v4_subtract(void);
    static bool test_v4_op_minus(void);
    static bool test_v4_dehomogenize(void);
    static bool test_v4_dehomogenize_2(void);
    
    //Matrix 4 Tests
    static bool test_m4_multiply_m4(void);
    static bool test_m4_op_star_m4(void);
    static bool test_m4_multiply_v4(void);
    static bool test_m4_op_star_v4(void);
    static bool test_m4_multiply_v3(void);
    static bool test_m4_op_star_v3(void);
    static bool test_m4_makeRotateX(void);
    static bool test_m4_makeRotateY(void);
    static bool test_m4_makeRotateZ(void);
    static bool test_m4_makeRotateArbitrary(void);
    static bool test_m4_makeScale_f3(void);
    static bool test_m4_makeScale_f(void);
    static bool test_m4_makeTranslate_f3(void);
    static bool test_m4_makeTranslate_v3(void);
    static bool test_m4_transpose(void);
    static bool test_m4_inverse(void);
    static bool test_m4_orthoNormalInverse(void);
    
public:
    
    static void runTests(void);
    
};

#endif

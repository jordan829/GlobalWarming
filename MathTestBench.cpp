#include "MathTestBench.h"
#include <math.h>
#include <iomanip>
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include <string>

#define TEST_NAME_COL_WIDTH 46
#define PI_OVER_2 1.57079

//
void MathTestBench::runTests()
{
    std::cout << "CSE 167 - Math Library Test Bench" << std::endl;
    std::cout << std::left;
    std::cout << std::endl;
    
    
    //Vector 3 Tests
    std::cout << "Vector3 Tests:" << std::endl;
    int vector3Tests = 0;
    int vector3Passes = 0;
    vector3Passes += (++vector3Tests, ((int)test_v3_add()));
    vector3Passes += (++vector3Tests, ((int)test_v3_op_plus()));
    vector3Passes += (++vector3Tests, ((int)test_v3_subtract()));
    vector3Passes += (++vector3Tests, ((int)test_v3_op_minus()));
    vector3Passes += (++vector3Tests, ((int)test_v3_negate()));
    vector3Passes += (++vector3Tests, ((int)test_v3_scale()));
    vector3Passes += (++vector3Tests, ((int)test_v3_multiply_v()));
    vector3Passes += (++vector3Tests, ((int)test_v3_op_star_v()));
    vector3Passes += (++vector3Tests, ((int)test_v3_multiply_f()));
    vector3Passes += (++vector3Tests, ((int)test_v3_op_star_f()));
    vector3Passes += (++vector3Tests, ((int)test_v3_dot()));
    vector3Passes += (++vector3Tests, ((int)test_v3_cross()));
    vector3Passes += (++vector3Tests, ((int)test_v3_angle()));
    vector3Passes += (++vector3Tests, ((int)test_v3_magnitude()));
    vector3Passes += (++vector3Tests, ((int)test_v3_magnitude_2()));
    vector3Passes += (++vector3Tests, ((int)test_v3_normalize()));
    vector3Passes += (++vector3Tests, ((int)test_v3_normalize_2()));
    printTestsPassedLine("Vector3 Tests Overall", vector3Passes, vector3Tests);
    std::cout << std::endl;
    
    
    //Vector 4 Tests
    std::cout << "Vector4 Tests:" << std::endl;
    int vector4Tests = 0;
    int vector4Passes = 0;
    vector4Passes += (++vector4Tests, ((int)test_v4_add()));
    vector4Passes += (++vector4Tests, ((int)test_v4_op_plus()));
    vector4Passes += (++vector4Tests, ((int)test_v4_subtract()));
    vector4Passes += (++vector4Tests, ((int)test_v4_op_minus()));
    vector4Passes += (++vector4Tests, ((int)test_v4_dehomogenize()));
    vector4Passes += (++vector4Tests, ((int)test_v4_dehomogenize_2()));
    printTestsPassedLine("Vector4 Tests Overall", vector4Passes, vector4Tests);
    std::cout << std::endl;
    
    
    //Matrix 4 Tests
    std::cout << "Matrix4 Tests:" << std::endl;
    int matrix4Tests = 0;
    int matrix4Passes = 0;
    matrix4Passes += (++matrix4Tests, ((int)test_m4_multiply_m4()));
    matrix4Passes += (++matrix4Tests, ((int)test_m4_op_star_m4()));
    matrix4Passes += (++matrix4Tests, ((int)test_m4_multiply_v4()));
    matrix4Passes += (++matrix4Tests, ((int)test_m4_op_star_v4()));
    matrix4Passes += (++matrix4Tests, ((int)test_m4_multiply_v3()));
    matrix4Passes += (++matrix4Tests, ((int)test_m4_op_star_v3()));
    matrix4Passes += (++matrix4Tests, ((int)test_m4_makeRotateX()));
    matrix4Passes += (++matrix4Tests, ((int)test_m4_makeRotateY()));
    matrix4Passes += (++matrix4Tests, ((int)test_m4_makeRotateZ()));
    matrix4Passes += (++matrix4Tests, ((int)test_m4_makeRotateArbitrary()));
    matrix4Passes += (++matrix4Tests, ((int)test_m4_makeScale_f3()));
    matrix4Passes += (++matrix4Tests, ((int)test_m4_makeScale_f()));
    matrix4Passes += (++matrix4Tests, ((int)test_m4_makeTranslate_f3()));
    matrix4Passes += (++matrix4Tests, ((int)test_m4_makeTranslate_v3()));
    matrix4Passes += (++matrix4Tests, ((int)test_m4_transpose()));
    //matrix4Passes += (++matrix4Tests, ((int)test_m4_inverse()));
    //matrix4Passes += (++matrix4Tests, ((int)test_m4_orthoNormalInverse()));
    printTestsPassedLine("Matrix4 Tests Overall", matrix4Passes, matrix4Tests);
    std::cout << std::endl;
    
    printTestsPassedLine("Test Bench Overall", (vector3Passes + vector4Passes + matrix4Passes), (vector3Tests + vector4Tests + matrix4Tests));
    std::cout << std::endl;
    
    std::cout << "Done!" << std::endl;
}

//Helper Functions
void MathTestBench::printTestLine(std::string name, bool pass)
{
    std::cout << std::setw(TEST_NAME_COL_WIDTH) << name;
    std::cout << std::setw(0) << ": " << (pass ? "Pass" : "FAIL");
    std::cout << std::endl;
}

void MathTestBench::printTestsPassedLine(std::string name, int passed, int total)
{
    std::cout << std::setw(TEST_NAME_COL_WIDTH) << name;
    std::cout << std::setw(0) << ": " << ((passed == total) ? "Pass" : "***FAIL***");
    std::cout << " (" << passed << "/" << total << ")";
    std::cout << std::endl;
}

bool MathTestBench::approx(float a, float b)
{
    static const float delta = 0.0005;
    return fabs(a-b) < delta;
}


//Vector 3 Tests
bool MathTestBench::test_v3_add(void)
{
    bool pass = 0x0;
    
    Vector3 a(1, 2, 3);
    Vector3 b(9, 8, 7);
    Vector3 c = a.add(b);
    
    pass = approx(c[0], 10) && approx(c[1], 10) && approx(c[2], 10);
    
    printTestLine("Vector3.add", pass);
    return pass;
}

bool MathTestBench::test_v3_op_plus(void)
{
    bool pass = 0x0;
    
    Vector3 a(1, 2, 3);
    Vector3 b(9, 8, 7);
    Vector3 c = a + b;
    
    pass = approx(c[0], 10) && approx(c[1], 10) && approx(c[2], 10);
    
    printTestLine("Vector3.(+)", pass);
    return pass;
}

bool MathTestBench::test_v3_subtract(void)
{
    bool pass = 0x0;
    
    Vector3 a(1, 2, 3);
    Vector3 b(9, 8, 7);
    Vector3 c = a.subtract(b);
    
    pass = approx(c[0], -8) && approx(c[1], -6) && approx(c[2], -4);
    
    printTestLine("Vector3.subtract", pass);
    return pass;
}

bool MathTestBench::test_v3_op_minus(void)
{
    bool pass = 0x0;
    
    Vector3 a(1, 2, 3);
    Vector3 b(9, 8, 7);
    Vector3 c = a - b;
    
    pass = approx(c[0], -8) && approx(c[1], -6) && approx(c[2], -4);
    
    printTestLine("Vector3.(-)", pass);
    return pass;
}

bool MathTestBench::test_v3_negate(void)
{
    bool pass = 0x0;
    
    Vector3 a(1, 2, 3);
    Vector3 b = a.negate();
    
    pass = approx(b[0], -1) && approx(b[1], -2) && approx(b[2], -3);
    
    printTestLine("Vector3.negate", pass);
    return pass;
}

bool MathTestBench::test_v3_scale(void)
{
    bool pass = 0x0;
    
    Vector3 a(1, 2, 3);
    Vector3 b = a.scale(2.0);
    
    pass = approx(b[0], 2) && approx(b[1], 4) && approx(b[2], 6);
    
    printTestLine("Vector3.scale", pass);
    return pass;
}

bool MathTestBench::test_v3_multiply_v(void)
{
    bool pass = 0x0;
    
    Vector3 a(1, 2, 3);
    Vector3 b(9, 8, 7);
    Vector3 c = a.multiply(b);
    
    pass = approx(c[0], 9) && approx(c[1], 16) && approx(c[2], 21);
    
    printTestLine("Vector3.multiply(Vector3)", pass);
    return pass;
}

bool MathTestBench::test_v3_op_star_v(void)
{
    bool pass = 0x0;
    
    Vector3 a(1, 2, 3);
    Vector3 b(9, 8, 7);
    Vector3 c = a * b;
    
    pass = approx(c[0], 9) && approx(c[1], 16) && approx(c[2], 21);
    
    printTestLine("Vector3.(*)(Vector3)", pass);
    return pass;
}

bool MathTestBench::test_v3_multiply_f(void)
{
    bool pass = 0x0;
    
    Vector3 a(1, 2, 3);
    float b = 13.1;
    Vector3 c = a.multiply(b);
    
    pass = approx(c[0], 13.1) && approx(c[1], 26.2) && approx(c[2], 39.3);
    
    printTestLine("Vector3.multiply(float)", pass);
    return pass;
}

bool MathTestBench::test_v3_op_star_f(void)
{
    bool pass = 0x0;
    
    Vector3 a(1, 2, 3);
    float b = 13.1;
    Vector3 c = a * b;
    
    pass = approx(c[0], 13.1) && approx(c[1], 26.2) && approx(c[2], 39.3);
    
    printTestLine("Vector3.(*)(float)", pass);
    return pass;
}

bool MathTestBench::test_v3_dot(void)
{
    bool pass = 0x0;
    
    Vector3 a(1, 2, 3);
    Vector3 b(-3, 4, -5);
    float c = a.dot(b);
    
    pass = approx(c, -10);
    
    printTestLine("Vector3.dot", pass);
    return pass;
}

bool MathTestBench::test_v3_cross(void)
{
    bool pass = 0x0;
    
    Vector3 a(0, 0, 1);
    Vector3 b(1, 0, 0);
    Vector3 c = a.cross(b);
    
    pass = approx(c[0], 0) && approx(c[1], 1) && approx(c[2], 0);
    
    printTestLine("Vector3.cross", pass);
    return pass;
}

bool MathTestBench::test_v3_angle(void)
{
    bool pass = 0x0;
    
    Vector3 a(1, 0, 0);
    Vector3 b(0, 0, 1);
    float c = a.angle(b);
    
    pass = approx(c, PI_OVER_2);
    
    printTestLine("Vector3.angle", pass);
    return pass;
}

bool MathTestBench::test_v3_magnitude(void)
{
    bool pass = 0x0;
    
    Vector3 a(3, 0, 4);
    float b = a.magnitude();
    
    pass = approx(b, 5);
    
    printTestLine("Vector3.magnitude", pass);
    return pass;
}

bool MathTestBench::test_v3_magnitude_2(void)
{
    bool pass = 0x0;
    
    Vector3 a(0, 0, 0);
    float b = a.magnitude();
    
    pass = approx(b, 0);
    
    printTestLine("Vector3.magnitude (zero length)", pass);
    return pass;
}

bool MathTestBench::test_v3_normalize(void)
{
    bool pass = 0x0;
    
    Vector3 a(1, 1, 1);
    float r = 1.0 / a.magnitude();
    Vector3 b = a.normalize();
    
    pass = approx(b[0], r) && approx(b[1], r) && approx(b[2], r);
    
    printTestLine("Vector3.normalize", pass);
    return pass;
}

bool MathTestBench::test_v3_normalize_2(void)
{
    bool pass = 0x0;
    
    Vector3 a(0, 0, 0);
    Vector3 b = a.normalize();
    
    float r = 0.0;
    pass = approx(b[0], r) && approx(b[1], r) && approx(b[2], r);
    
    printTestLine("Vector3.normalize (zero length)", pass);
    return pass;
}


//Vector 4 Tests
bool MathTestBench::test_v4_add(void)
{
    bool pass = 0x0;
    
    Vector4 a(1, 2, 3, 1);
    Vector4 b(9, 8, 7, 0);
    Vector4 c = a.add(b);
    
    pass = approx(c[0], 10) && approx(c[1], 10) && approx(c[2], 10) && approx(c[3], 1);
    
    printTestLine("Vector4.add", pass);
    return pass;
}

bool MathTestBench::test_v4_op_plus(void)
{
    bool pass = 0x0;
    
    Vector4 a(1, 2, 3, 1);
    Vector4 b(9, 8, 7, 0);
    Vector4 c = a + b;
    
    pass = approx(c[0], 10) && approx(c[1], 10) && approx(c[2], 10) && approx(c[3], 1);
    
    printTestLine("Vector4.(+)", pass);
    return pass;
}

bool MathTestBench::test_v4_subtract(void)
{
    bool pass = 0x0;
    
    Vector4 a(1, 2, 3, 1);
    Vector4 b(9, 8, 7, 1);
    Vector4 c = a.subtract(b);
    
    pass = approx(c[0], -8) && approx(c[1], -6) && approx(c[2], -4) && approx(c[3], 0);
    
    printTestLine("Vector4.subtract", pass);
    return pass;
}

bool MathTestBench::test_v4_op_minus(void)
{
    bool pass = 0x0;
    
    Vector4 a(1, 2, 3, 1);
    Vector4 b(9, 8, 7, 1);
    Vector4 c = a - b;
    
    pass = approx(c[0], -8) && approx(c[1], -6) && approx(c[2], -4) && approx(c[3], 0);
    
    printTestLine("Vector4.(-)", pass);
    return pass;
}

bool MathTestBench::test_v4_dehomogenize(void)
{
    bool pass = 0x0;
    
    Vector4 a(10, 20, 30, 10);
    Vector4 b = a.dehomogenize();
    
    pass = approx(b[0], 1) && approx(b[1], 2) && approx(b[2], 3) && approx(b[3],1);
    
    printTestLine("Vector4.dehomogenize", pass);
    return pass;
}

bool MathTestBench::test_v4_dehomogenize_2(void)
{
    bool pass = 0x0;
    
    Vector4 a(10, 20, 30, 0);
    Vector4 b = a.dehomogenize();
    
    //There is no best way to define the bevahior of dehomogenizing with a
    //'w' component of 0
    //So this only checks to make sure that your code doesn't crash with
    //a divide-by-zero error
    pass = !!(&b);
    
    printTestLine("Vector4.dehomogenize (zero w-component)", pass);
    return pass;
}


//Matrix 4 Tests
bool MathTestBench::test_m4_multiply_m4(void)
{
    bool pass = 0x0;
    
    Matrix4 a(1,0,0,0,0,2,0,0,0,0,3,0,0,0,0,1);
    Matrix4 b(5,0,0,0,0,6,0,0,0,0,7,0,0,0,0,1);
    
    Matrix4 c = a.multiply(b);
    
    pass = approx(c.get(0, 0), 5) && approx(c.get(1, 1), 12) && approx(c.get(2, 2), 21) && approx(c.get(3, 3), 1);
    
    printTestLine("Matrix4.multiply(Matrix4)", pass);
    return pass;
}

bool MathTestBench::test_m4_op_star_m4(void)
{
    bool pass = 0x0;
    
    Matrix4 a(1,0,0,0,0,2,0,0,0,0,3,0,0,0,0,1);
    Matrix4 b(5,0,0,0,0,6,0,0,0,0,7,0,0,0,0,1);
    
    Matrix4 c = a * b;
    
    pass = approx(c.get(0, 0), 5) && approx(c.get(1, 1), 12) && approx(c.get(2, 2), 21) && approx(c.get(3, 3), 1);
    
    printTestLine("Matrix4.(*)(Matrix4)", pass);
    return pass;
}

bool MathTestBench::test_m4_multiply_v4(void)
{
    bool pass = 0x0;
    
    Matrix4 a(1,0,0,0,0,2,0,0,0,0,3,0,0,0,0,1);
    Vector4 b(6, 7, 8, 1);
    
    Vector4 c = a.multiply(b);
    
    pass = approx(c[0], 6) && approx(c[1], 14) && approx(c[2], 24) && approx(c[3], 1);
    
    printTestLine("Matrix4.multiply(Vector4)", pass);
    return pass;
}

bool MathTestBench::test_m4_op_star_v4(void)
{
    bool pass = 0x0;
    
    Matrix4 a(1,0,0,0,0,2,0,0,0,0,3,0,0,0,0,1);
    Vector4 b(6, 7, 8, 1);
    
    Vector4 c = a * b;
    
    pass = approx(c[0], 6) && approx(c[1], 14) && approx(c[2], 24) && approx(c[3], 1);
    
    printTestLine("Matrix4.(*)(Matrix4)", pass);
    return pass;
}

bool MathTestBench::test_m4_multiply_v3(void)
{
    bool pass = 0x0;
    
    Matrix4 a(1,0,0,0,0,2,0,0,0,0,3,0,0,0,0,1);
    Vector3 b(6, 7, 8);
    
    Vector3 c = a.multiply(b);
    
    pass = approx(c[0], 6) && approx(c[1], 14) && approx(c[2], 24);
    
    printTestLine("Matrix4.multiply(Vector3)", pass);
    return pass;
}

bool MathTestBench::test_m4_op_star_v3(void)
{
    bool pass = 0x0;
    
    Matrix4 a(1,0,0,0,0,2,0,0,0,0,3,0,0,0,0,1);
    Vector3 b(6, 7, 8);
    
    Vector3 c = a * b;
    
    pass = approx(c[0], 6) && approx(c[1], 14) && approx(c[2], 24);
    
    printTestLine("Matrix4.(*)(Matrix4)", pass);
    return pass;
}

bool MathTestBench::test_m4_makeRotateX(void)
{
    bool pass = 0x0;
    
    Matrix4 a;
    a.makeRotateX(PI_OVER_2);
    
    Vector4 b(0, 0, -1, 0);
    
    b = a * b;
    
    pass = approx(b[0], 0) && approx(b[1], 1) && approx(b[2], 0);
    
    printTestLine("Matrix4.makeRotateX", pass);
    return pass;
}

bool MathTestBench::test_m4_makeRotateY(void)
{
    bool pass = 0x0;
    
    Matrix4 a;
    a.makeRotateY(PI_OVER_2);
    
    Vector4 b(0, 0, 1, 0);
    
    b = a * b;
    
    pass = approx(b[0], 1) && approx(b[1], 0) && approx(b[2], 0);
    
    printTestLine("Matrix4.makeRotateY", pass);
    return pass;
}

bool MathTestBench::test_m4_makeRotateZ(void)
{
    bool pass = 0x0;
    
    Matrix4 a;
    a.makeRotateZ(PI_OVER_2);
    
    Vector4 b(1, 0, 0, 0);
    
    b = a * b;
    
    pass = approx(b[0], 0) && approx(b[1], 1) && approx(b[2], 0);
    
    printTestLine("Matrix4.makeRotateZ", pass);
    return pass;
}

bool MathTestBench::test_m4_makeRotateArbitrary(void)
{
    bool pass = 0x0;
    
    Vector3 axis(0, 0, 1);
    Matrix4 a;
    a.makeRotateArbitrary(axis, PI_OVER_2);
    
    Vector4 b(1, 0, 0, 0);
    
    b = a * b;
    
    pass = approx(b[0], 0) && approx(b[1], 1) && approx(b[2], 0);
    
    printTestLine("Matrix4.makeRotateArbitrary", pass);
    return pass;
}

bool MathTestBench::test_m4_makeScale_f3(void)
{
    bool pass = 0x0;
    
    Matrix4 a;
    a.makeScale(2.0, 3.0, 4.0);
    
    Vector4 b(1, 1, 1, 0);
    
    b = a * b;
    
    pass = approx(b[0], 2) && approx(b[1], 3) && approx(b[2], 4);
    
    printTestLine("Matrix4.makeScale(float, float, float)", pass);
    return pass;
}

bool MathTestBench::test_m4_makeScale_f(void)
{
    bool pass = 0x0;
    
    Matrix4 a;
    a.makeScale(2.0);
    
    Vector4 b(1, 2, 3, 0);
    
    b = a * b;
    
    pass = approx(b[0], 2) && approx(b[1], 4) && approx(b[2], 6);
    
    printTestLine("Matrix4.makeScale(float)", pass);
    return pass;
}

bool MathTestBench::test_m4_makeTranslate_f3(void)
{
    bool pass = 0x0;
    
    Matrix4 a;
    a.makeTranslate(2.0, 3.0, 4.0);
    
    Vector4 b(1, 1, 1, 1);
    
    b = a * b;
    
    pass = approx(b[0], 3) && approx(b[1], 4) && approx(b[2], 5);
    
    printTestLine("Matrix4.makeTranslate(float, float ,float)", pass);
    return pass;
}

bool MathTestBench::test_m4_makeTranslate_v3(void)
{
    bool pass = 0x0;
    
    Vector3 trans(2, 3, 4);
    Matrix4 a;
    a.makeTranslate(trans);
    
    Vector4 b(1, 1, 1, 1);
    
    b = a * b;
    
    pass = approx(b[0], 3) && approx(b[1], 4) && approx(b[2], 5);
    
    printTestLine("Matrix4.makeTranslate(Vector3)", pass);
    return pass;
}

bool MathTestBench::test_m4_transpose(void)
{
    bool pass = 0x0;
    
    Matrix4 a(1,1,1,1, 0,0,0,0, 0,0,0,0, 0,0,0,0);
    Matrix4 b(1,0,0,0, 1,0,0,0, 1,0,0,0, 1,0,0,0);
    
    a = a.transpose();
    
    pass = 0x1;
    float *aptr = a.ptr(), *bptr = b.ptr();
    for(int i = 0; i < 16; ++i)
        if(!approx(*(aptr + i), *(bptr + i)))
            pass = 0x0;
    
    printTestLine("Matrix4.transpose", pass);
    return pass;
}

bool MathTestBench::test_m4_inverse(void)
{
    bool pass = 0x0;
    
    //Test
    
    printTestLine("Matrix4.inverse", pass);
    return pass;
}

bool MathTestBench::test_m4_orthoNormalInverse(void)
{
    bool pass = 0x0;
    
    //Test
    
    printTestLine("Matrix4.orthonormalInverse", pass);
    return pass;
}

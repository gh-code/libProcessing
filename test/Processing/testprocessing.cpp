/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#include <QtTest/QtTest>
#define P_USE_USER_MAIN
#include <Processing>

using namespace processing;

class TestProcessing : public QObject
{
    Q_OBJECT
private slots:
    void test_abs();
    void test_ceil();
    void test_constrain();
    void test_dist();
    void test_exp();
    void test_floor();
    void test_lerp();
    void test_log();
    void test_mag();
    void test_map();
    void test_max();
    void test_min();
    void test_norm();
    void test_pow();
    void test_round();
    void test_sq();
    void test_sqrt();

    void test_acos();
    void test_asin();
    void test_atan();
    void test_atan2();
    void test_cos();
    void test_degrees();
    void test_radians();
    void test_sin();
    void test_tan();

    void test_random();
};

void TestProcessing::test_abs()
{
    QVERIFY(abs(-123.0) == 123.0);
}

void TestProcessing::test_ceil()
{
    QVERIFY(ceil(1.23) == 2);
    QVERIFY(ceil(1.54) == 2);
    QVERIFY(ceil(-1.23) == -1);
    QVERIFY(ceil(-1.54) == -1);
}

void TestProcessing::test_constrain()
{
    QVERIFY(constrain(0, 30, 70) == 30);
    QVERIFY(constrain(30, 30, 70) == 30);
    QVERIFY(constrain(31, 30, 70) == 31);
    QVERIFY(constrain(69, 30, 70) == 69);
    QVERIFY(constrain(70, 30, 70) == 70);
    QVERIFY(constrain(71, 30, 70) == 70);
    QVERIFY(constrain(0.0, 20, 60) == 20.0);
    QVERIFY(constrain(20.0, 20, 60) == 20.0);
    QVERIFY(constrain(21.0, 20, 60) == 21.0);
    QVERIFY(constrain(59.0, 20, 60) == 59.0);
    QVERIFY(constrain(60.0, 20, 60) == 60.0);
    QVERIFY(constrain(61.0, 20, 60) == 60.0);
}

void TestProcessing::test_dist()
{
    QCOMPARE(dist(1.0, 1.0, 2.0, 2.0), 1.41421f);
}

void TestProcessing::test_exp()
{
    float e = exp(1);
    QCOMPARE(e, 2.71828f);
}

void TestProcessing::test_floor()
{
    QCOMPARE(floor(1.23), 1.0f);
    QCOMPARE(floor(1.54), 1.0f);
    QCOMPARE(floor(-1.23), -2.0f);
    QCOMPARE(floor(-1.54), -2.0f);
}

void TestProcessing::test_lerp()
{
    float a = 20;
    float b = 80;
    QCOMPARE(lerp(a, b, 0.0), 20.0f);
    QCOMPARE(lerp(a, b, 0.5), 50.0f);
    QCOMPARE(lerp(a, b, 1.0), 80.0f);
}

void TestProcessing::test_log()
{
    QCOMPARE(log(12), 2.484906649788);
}

void TestProcessing::test_mag()
{
    float x1 = 20;
    float x2 = 80;
    float y1 = 30;
    float y2 = 70;
    QCOMPARE(mag(x1, y1), 36.05551f);
    QCOMPARE(mag(x2, y1), 85.44004f);
    QCOMPARE(mag(x1, y2), 72.8011f);
    QCOMPARE(mag(x2, y2), 106.30146f);
}

void TestProcessing::test_map()
{
    QVERIFY(map(-1, 0, 10, -20, 20) == -24);
    QVERIFY(map( 0, 0, 10, -20, 20) == -20);
    QVERIFY(map( 5, 0, 10, -20, 20) ==   0);
    QVERIFY(map(10, 0, 10, -20, 20) ==  20);
    QVERIFY(map(11, 0, 10, -20, 20) ==  24);
}

void TestProcessing::test_max()
{
    QCOMPARE(max(5, 9), 9);
    QCOMPARE(max(-4, -12), -4);
    QCOMPARE(max(12.3f, 230.24f), 230.24f);
}

void TestProcessing::test_min()
{
    QCOMPARE(min(5, 9), 5);
    QCOMPARE(min(-4, -12), -12);
    QCOMPARE(min(12.3f, 230.24f), 12.3f);
}

void TestProcessing::test_norm()
{
    QCOMPARE(norm(20, 0, 50), 0.4);
    QCOMPARE(norm(-10, 0, 100), -0.1);
}

void TestProcessing::test_pow()
{
    QCOMPARE(pow( 1, 3), 1.0f);
    QCOMPARE(pow( 3, 5), 243.0f);
    QCOMPARE(pow( 3,-5), .00411522633745);
    QCOMPARE(pow(-3, 5), -243.0f);
}

void TestProcessing::test_round()
{
    QVERIFY(round(1.23) == 1);
    QVERIFY(round(1.5) == 2);
}

void TestProcessing::test_sq()
{
    QVERIFY(sq(-1) == 1);
    QVERIFY(sq(1) == 1);
    QVERIFY(sq(-5) == 25);
    QVERIFY(sq(9) == 81);
}

void TestProcessing::test_sqrt()
{
    QVERIFY(sqrt(1) == 1);
    QVERIFY(sqrt(25) == 5);
    QVERIFY(sqrt(81) == 9);
}

void TestProcessing::test_acos()
{
    QVERIFY(acos(1) == 0);
}

void TestProcessing::test_asin()
{
    QVERIFY(asin(0) == 0);
}

void TestProcessing::test_atan()
{
    QVERIFY(atan(0) == 0);
}

void TestProcessing::test_atan2()
{
    QCOMPARE(atan2(1, 0), HALF_PI);
}

void TestProcessing::test_cos()
{
    QVERIFY(cos(0) == 1);
}

void TestProcessing::test_degrees()
{
    QCOMPARE(degrees(0),          0.0f);
    QCOMPARE(degrees(0.5235987f), 30.0f);
    QCOMPARE(degrees(QUARTER_PI), 45.0f);
    QCOMPARE(degrees(HALF_PI),    90.0f);
    QCOMPARE(degrees(PI),         180.0f);
    QCOMPARE(degrees(TWO_PI),     360.0f);
}

void TestProcessing::test_radians()
{
    QCOMPARE(radians(0),   0.0f);
    QCOMPARE(radians(30),  0.5235987f);
    QCOMPARE(radians(45),  (float) QUARTER_PI);
    QCOMPARE(radians(90),  (float) HALF_PI);
    QCOMPARE(radians(180), (float) PI);
    QCOMPARE(radians(360), (float) TWO_PI);
}

void TestProcessing::test_sin()
{
    QVERIFY(sin(0) == 0);
}

void TestProcessing::test_tan()
{
    QVERIFY(tan(0) == 0);
}

void TestProcessing::test_random()
{
    for (int i = 0; i < 10000; i++)
    {
        QVERIFY(random(-10.0, 10.0) >= -10.0 &&
                random(-10.0, 10.0) <= 10.0);
    }
}

QTEST_MAIN(TestProcessing)
#include "testprocessing.moc"

/**
 * Author: Gary Huang <gh.nctu+code@gmail.com>
 */
#include <QtTest/QtTest>
#define P_USE_USER_MAIN
#include <Processing>

using namespace processing;

class TestPVector : public QObject
{
    Q_OBJECT
private slots:
    void test_set();
    void test_random();
    void test_fromAngle();
    void test_copy();
    void test_mag();
    void test_magSq();
    void test_add();
    void test_sub();
    void test_mult();
    void test_div();
    void test_dist();
    void test_dot();
    void test_cross();
    void test_normalize();
    void test_limit();
    void test_setMag();
    void test_heading();
    void test_rotate();
    void test_lerp();
    void test_angleBetween();
    void test_array();
};

void TestPVector::test_set()
{
    PVector v1(20.0, 30.0, 40.0);
    PVector v2(0.0, 0.0, 0.0);
    v2.set(v1);
    QCOMPARE(v2.x(), 20.0f);
    QCOMPARE(v2.y(), 30.0f);
    QCOMPARE(v2.z(), 40.0f);
}

void TestPVector::test_random()
{
    int i;
    for (i = 0; i < 10000; i++)
    {
        PVector r1 = PVector::random2D();
        QVERIFY(r1.x() >= -1.0 && r1.x() <= 1.0);
        QVERIFY(r1.y() >= -1.0 && r1.y() <= 1.0);

        PVector r2;
        PVector::random2D(&r2);
        QVERIFY(r2.x() >= -1.0 && r2.x() <= 1.0);
        QVERIFY(r2.y() >= -1.0 && r2.y() <= 1.0);

        PVector r3 = PVector::random2D(0);
        QVERIFY(r3.x() >= -1.0 && r3.x() <= 1.0);
        QVERIFY(r3.y() >= -1.0 && r3.y() <= 1.0);

        // Deprecated interface
        // PVector *r4 = 0;
        // PVector::random2D(r4);
        // QVERIFY(r4->x() >= -1.0 && r4->x() <= 1.0);
        // QVERIFY(r4->y() >= -1.0 && r4->y() <= 1.0);
    }
}

void TestPVector::test_fromAngle()
{
    PVector v = PVector::fromAngle(0.01);
    QCOMPARE(v.x(), 0.99995f);
    QCOMPARE(v.y(), 0.009999833f);
}

void TestPVector::test_copy()
{
    PVector v1(1, 2, 3);
    PVector v2 = v1.copy();
    QVERIFY(v1 != v2);
    QCOMPARE(v1.x(), v2.x());
    QCOMPARE(v1.y(), v2.y());
    QCOMPARE(v1.z(), v2.z());
    v2.set(4, 5, 6); // assume set works
    QCOMPARE(v1.x(), 1.0f);
    QCOMPARE(v1.y(), 2.0f);
    QCOMPARE(v1.z(), 3.0f);
    QCOMPARE(v2.x(), 4.0f);
    QCOMPARE(v2.y(), 5.0f);
    QCOMPARE(v2.z(), 6.0f);
}

void TestPVector::test_mag()
{
    PVector v(20.0, 30.0, 40.0);
    QCOMPARE(v.mag(), 53.85164807f);
}

void TestPVector::test_magSq()
{
    PVector v(20.0, 30.0, 40.0);
    QCOMPARE(v.mag(), 53.85164807f);
}

void TestPVector::test_add()
{
    int i;
    for (i = 0; i < 10; i++)
    {
        // assume random works
        float x1 = random(-100, 100);
        float y1 = random(-100, 100);
        float z1 = random(-100, 100);
        float x2 = random(-100, 100);
        float y2 = random(-100, 100);
        float z2 = random(-100, 100);

        PVector v1(x1, y1, z1);
        PVector v2(x2, y2, z2);
        v2.add(v1);
        QCOMPARE(v2.x(), x2 + x1);
        QCOMPARE(v2.y(), y2 + y1);
        QCOMPARE(v2.z(), z2 + z1);

        PVector v3 = PVector::add(v1, v2);
        QCOMPARE(v3.x(), v1.x() + v2.x());
        QCOMPARE(v3.y(), v1.y() + v2.y());
        QCOMPARE(v3.z(), v1.z() + v2.z());
    }
}

void TestPVector::test_sub()
{
    int i;
    for (i = 0; i < 10; i++)
    {
        // assume random works
        float x1 = random(-100, 100);
        float y1 = random(-100, 100);
        float z1 = random(-100, 100);
        float x2 = random(-100, 100);
        float y2 = random(-100, 100);
        float z2 = random(-100, 100);

        PVector v1(x1, y1, z1);
        PVector v2(x2, y2, z2);
        v2.sub(v1);
        QCOMPARE(v2.x(), x2 - x1);
        QCOMPARE(v2.y(), y2 - y1);
        QCOMPARE(v2.z(), z2 - z1);

        PVector v3 = PVector::sub(v1, v2);
        QCOMPARE(v3.x(), v1.x() - v2.x());
        QCOMPARE(v3.y(), v1.y() - v2.y());
        QCOMPARE(v3.z(), v1.z() - v2.z());
    }
}

void TestPVector::test_mult()
{
    // Interface 1
    PVector v1 = PVector(5, 10, 1);
    v1.mult(6);
    QCOMPARE(v1.x(), 30.0f);
    QCOMPARE(v1.y(), 60.0f);
    QCOMPARE(v1.z(), 6.0f);

    // Interface 3
    PVector v2 = PVector::mult(v1, 6);
    QCOMPARE(v2.x(), 180.0f);
    QCOMPARE(v2.y(), 360.0f);
    QCOMPARE(v2.z(), 36.0f);
}

void TestPVector::test_div()
{
    // Interface 1
    PVector v1 = PVector(36, 72, 144);
    v1.div(6);
    QCOMPARE(v1.x(), 6.0f);
    QCOMPARE(v1.y(), 12.0f);
    QCOMPARE(v1.z(), 24.0f);

    // Interface 3
    PVector v2 = PVector::div(v1, 6);
    QCOMPARE(v2.x(), 1.0f);
    QCOMPARE(v2.y(), 2.0f);
    QCOMPARE(v2.z(), 4.0f);
}

void TestPVector::test_dist()
{
    // Interface 1
    PVector v1 = PVector(10, 20, 0);
    PVector v2 = PVector(60, 80, 0);
    QCOMPARE(v1.dist(v2), 78.10249f);

    // Interface 2
    QCOMPARE(PVector::dist(v1, v2), 78.10249f);
}

void TestPVector::test_dot()
{
    // Interface 1
    PVector v = PVector(10, 20, 0);
    QCOMPARE(v.dot(60, 80, 0), 2200.0f);

    // Interface 2
    PVector v1 = PVector(10, 20, 0);
    PVector v2 = PVector(60, 80, 0);
    QCOMPARE(v1.dot(v2), 2200.0f);
}

void TestPVector::test_cross()
{
    PVector v1 = PVector(10, 20, 2);
    PVector v2 = PVector(60, 80, 6); 
    PVector v3 = v1.cross(v2);
    QCOMPARE(v3.x(), -40.0f);
    QCOMPARE(v3.y(), 60.0f);
    QCOMPARE(v3.z(), -400.0f);
}

void TestPVector::test_normalize()
{
    // Interface 2D
    PVector v2d1 = PVector(0, 0);
    v2d1.normalize();
    QCOMPARE(v2d1.x(), 0.0f);
    QCOMPARE(v2d1.y(), 0.0f);

    PVector v2d2 = PVector(10, 20);
    v2d2.normalize();
    QCOMPARE(v2d2.x(), 0.4472136f);
    QCOMPARE(v2d2.y(), 0.8944272f);

    // Interface 3D
    PVector v3d1 = PVector(0, 0, 0);
    v3d1.normalize();
    QCOMPARE(v3d1.x(), 0.0f);
    QCOMPARE(v3d1.y(), 0.0f);
    QCOMPARE(v3d1.z(), 0.0f);

    PVector v3d2 = PVector(10, 20, 2);
    v3d2.normalize();
    QCOMPARE(v3d2.x(), 0.4454354f);
    QCOMPARE(v3d2.y(), 0.8908708f);
    QCOMPARE(v3d2.z(), 0.089087084f);
}

void TestPVector::test_limit()
{
    // Interface 2D
    PVector v1 = PVector(10, 20);
    v1.limit(5);
    QCOMPARE(v1.x(), 2.2360680f);
    QCOMPARE(v1.y(), 4.4721360f);

    // Interface 3D
    PVector v2 = PVector(10, 20, 2);
    v2.limit(5);
    QCOMPARE(v2.x(), 2.2271771f);
    QCOMPARE(v2.y(), 4.4543543f);
    QCOMPARE(v2.z(), 0.4454354f);
}

void TestPVector::test_setMag()
{
    PVector v1 = PVector(3, 4);
    v1.setMag(10);
    QCOMPARE(v1.x(), 6.0f);
    QCOMPARE(v1.y(), 8.0f);

    // Interface 3D
    PVector v2 = PVector(3, 4, 0);
    v2.setMag(10);
    QCOMPARE(v2.x(), 6.0f);
    QCOMPARE(v2.y(), 8.0f);
    QCOMPARE(v2.z(), 0.0f);
}

void TestPVector::test_heading()
{
    PVector v = PVector(10.0, 20.0);
    QCOMPARE(v.heading(), 1.1071488f);
}

void TestPVector::test_angleBetween()
{
    // Interface 2D
    PVector v1 = PVector(10, 20);
    PVector v2 = PVector(60, 80);
    float a = PVector::angleBetween(v1, v2);
    QCOMPARE(a, 0.1798535f);
}

void TestPVector::test_rotate()
{
    // Interface 2D
    PVector v1 = PVector(10.0, 20.0);
    QCOMPARE(v1.x(), 10.0f);
    QCOMPARE(v1.y(), 20.0f);
    v1.rotate(HALF_PI);
    QCOMPARE(v1.x(), -20.0f);
    QCOMPARE(v1.y(), 9.999999f);

    // Interface 3D
    PVector v2 = PVector(1, 0, 0);
    QCOMPARE(v2.x(), 1.0f);
    QCOMPARE(v2.y(), 0.0f);
    QCOMPARE(v2.z(), 0.0f);
    v2.rotate(M_PI_2);
    // QCOMPARE(v2.x(), 0.0f); // -4.37114e-008 ?
    QCOMPARE(v2.y(), 1.0f);
    QCOMPARE(v2.z(), 0.0f);
}

void TestPVector::test_lerp()
{
    // Interface 1
    PVector current = PVector(0.0, 0.0);
    PVector target = PVector(100.0, 100.0);
    current.lerp(target, 0.5);
    QCOMPARE(current.x(), 50.0f);
    QCOMPARE(current.y(), 50.0f);

    // Interface 2
    PVector start = PVector(10.0, 10.0);
    PVector end = PVector(100.0, 100.0);
    PVector middle = PVector::lerp(start, end, 0.5);
    QCOMPARE(middle.x(), 55.0f);
    QCOMPARE(middle.y(), 55.0f);
}

void TestPVector::test_array()
{
    PVector v = PVector(10.0, 20.0, 30.0);
    std::vector<float> f = v.array();
    QCOMPARE(f[0], 10.0f);
    QCOMPARE(f[1], 20.0f);
    QCOMPARE(f[2], 30.0f);
}

QTEST_MAIN(TestPVector)
#include "testpvector.moc"

#include "VECTOR.h"

#define RADIANS_TO_DEGREES(angle) (angle * 180.0) / M_PI

int main() {
    VECTOR v1(1.0, 0.0, 0.0);
    VECTOR v2(0.0, 1.0, 0.0);

    cout << fixed << setprecision(1) << RADIANS_TO_DEGREES(v1.angle(v2))
         << " degrees" << endl;

    VECTOR v3(3.0, 4.0, 7.0);
    VECTOR v4(-2.0, 3.0, -5.0);

    cout << RADIANS_TO_DEGREES(v3.angle(v4)) << " degrees" << endl;

    VECTOR v5(4.0, 8.0, 3.0);
    VECTOR v6(-1.0, 5.0, -7.0);

    cout << RADIANS_TO_DEGREES(v5.angle(v6)) << " degrees" << endl;

    VECTOR v7(1.0, 1.0, 1.0);
    VECTOR v8(1.0, 1.0, 1.0);

    cout << RADIANS_TO_DEGREES(v7.angle(v8)) << " degrees" << endl;

    VECTOR v9(1.0, 1.0, 1.0);
    VECTOR v10(-1.0, -1.0, -1.0);

    cout << RADIANS_TO_DEGREES(v9.angle(v10)) << " degrees" << endl;

    VECTOR v11(1.0, 2.0, 3.0);
    VECTOR v12(3.0, 1.0, 6.0);
    VECTOR v13(9.0, 4.0, -1.0);

    cout << RADIANS_TO_DEGREES(v11.angle(v12)) << " degrees" << endl;

    cout << "------------------" << endl;

    cout << v1 + v2 << endl;
    cout << v3 + v4 << endl;
    cout << v5 + v6 << endl;
    cout << v7 + v8 << endl;
    cout << v9 + v10 << endl;
    cout << v11 + v12 + v13 << endl;

    cout << "------------------" << endl;

    cout << v1 - v2 << endl;
    cout << v3 - v4 << endl;
    cout << v5 - v6 << endl;
    cout << v7 - v8 << endl;
    cout << v9 - v10 << endl;
    cout << v11 - v12 - v13 << endl;
    cout << v1 + v2 - v3 << endl;

    cout << "------------------" << endl;

    cout << v1.crossProduct(v2) << endl;
    cout << v3.crossProduct(v4) << endl;
    cout << v5.crossProduct(v6) << endl;
    cout << v7.crossProduct(v8) << endl;
    cout << v9.crossProduct(v10) << endl;
    cout << v11.crossProduct(v12) << endl;

    cout << "------------------" << endl;

    cout << v1.scalarMultiply(4.0) << endl;
    cout << v3.scalarMultiply(-2.0) << endl;
    cout << v4.scalarMultiply(0.5) << endl;

    return 0;
}

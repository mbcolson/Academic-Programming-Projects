#include "VECTOR.h"

#define RADIANS_TO_DEGREES(angle) (angle * 180.0) / M_PI

int main()
{
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

    cout << RADIANS_TO_DEGREES(v11.angle(v12)) << " degrees" << endl;

    cout << "-----------------" << endl;

    cout << v1.add(v2) << endl;
    cout << v3.add(v4) << endl;
    cout << v5.add(v6) << endl;
    cout << v7.add(v8) << endl;
    cout << v9.add(v10) << endl;
    cout << v11.add(v12) << endl;

    cout << "-----------------" << endl;

    cout << v1.subtract(v2) << endl;
    cout << v3.subtract(v4) << endl;
    cout << v5.subtract(v6) << endl;
    cout << v7.subtract(v8) << endl;
    cout << v9.subtract(v10) << endl;
    cout << v11.subtract(v12) << endl;

    cout << "-----------------" << endl;

    cout << v1.crossProduct(v2) << endl;
    cout << v3.crossProduct(v4) << endl;
    cout << v5.crossProduct(v6) << endl;
    cout << v7.crossProduct(v8) << endl;
    cout << v9.crossProduct(v10) << endl;
    cout << v11.crossProduct(v12) << endl;

    return 0;
}

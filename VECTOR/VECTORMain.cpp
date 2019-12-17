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

    return 0;
}

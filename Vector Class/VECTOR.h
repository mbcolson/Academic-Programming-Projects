#ifndef VECTOR_H_
#define VECTOR_H_

#include <bits/stdc++.h>
using namespace std;

// This class represents vectors in 3d space

class VECTOR
{
    private:
        // vector coordinates
        long double x, y, z;

    public:
        VECTOR();

        VECTOR(long double x, long double y, long double z);

        // Returns the dot product of this vector and vector 'v'
        long double dotProduct(const VECTOR &v) const;

        // Returns the cross product of this vector and vector 'v'
        const VECTOR crossProduct(const VECTOR &v) const;

        // Returns the length of this vector
        long double length() const;

        // Returns the angle between this vector and vector 'v' in radians
        long double angle(const VECTOR &v) const;

        // Returns the vector sum of this vector and vector 'v'
        const VECTOR add(const VECTOR &v) const;

        // Returns the vector difference of this vector and vector 'v'
        const VECTOR subtract(const VECTOR &v) const;

        friend ostream &operator<<(ostream &output, const VECTOR &v);
};

#endif /* VECTOR_H_ */
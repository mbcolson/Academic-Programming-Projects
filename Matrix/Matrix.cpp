#include "Matrix.h"

Matrix::Matrix(size_t _m, size_t _n) : m(_m), n(_n) {
    a.resize(m);
    fill(a.begin(), a.end(), vector<ll>(n, 0));
}

void Matrix::set(size_t i, size_t j, ll val) {
    if (i >= m or j >= n) {
        printf("Matrix::set: Index out of range\n");
        return; 
    }

    a[i][j] = val;
}

ll Matrix::get(size_t i, size_t j) const {
    if (i >= m or j >= n) {
        printf("Matrix::get: Index out of range\n");
        abort(); 
    }

    return a[i][j];
}

size_t Matrix::num_of_rows() const {
    return m;
}
     
size_t Matrix::num_of_columns() const {
    return n;
}

Matrix& Matrix::operator+=(Matrix& rhs) {
    if (m != rhs.m or n != rhs.n) {
        printf("Matrix::operator+=: Invalid matrix sizes");
        abort(); 
    }

    for(size_t i = 0; i < m; i++)
        for(size_t j = 0; j < n; j++)
            a[i][j] += rhs.get(i, j);
 
    return *this;
} 

Matrix operator+(Matrix lhs, Matrix& rhs) {
    lhs += rhs;
    return lhs;
}

Matrix& Matrix::operator*=(Matrix& rhs) {
    if (n != rhs.m) {
        printf("Matrix::operator*=: Invalid matrix sizes");
        abort();
    }

    Matrix tmp(m, rhs.n);

    for(size_t i = 0, k; i < m; i++) {
        for(size_t j = 0; j < rhs.n; j++) {
            ll sum = 0; 
               
            for(k = 0; k < rhs.m; k++)
                sum += a[i][k] * rhs.get(k,j);

            tmp.set(i, j, sum);
        }
    }

    *this = tmp;

    return *this;
}

Matrix operator*(Matrix lhs, Matrix& rhs) {
    lhs *= rhs;
    return lhs;
}

const Matrix& Matrix::transpose() {
    Matrix tmp(n, m);

    for(size_t i = 0; i < n; i++) {
        for(size_t j = 0; j < m; j++) {
            tmp.set(i, j, a[j][i]);
        }
    } 

    *this = tmp;
    return *this; 
}

ll Matrix::det() {
    if (m != n) {
        printf("Matrix::det: Invalid matrix size, must be a square matrix");
        abort();
    }

    if (m == 1)
        return a[0][0];
   
    return determinant(); 
}
    
ll Matrix::determinant() {
    if (m == 2)
        return ((a[0][0] * a[1][1]) - (a[0][1] * a[1][0]));

    ll sum = 0, sign = 1; 

    for(size_t i = 0; i < m; i++) {
        sum += sign * a[i][0] * (subMatrix(*this, i)).determinant();
        sign = -sign;
    }

    return sum;
}

Matrix Matrix::subMatrix(const Matrix& A, size_t r) const {
    if(r >= m) {
        printf("Matrix::subMatrix: Index out of range");
        abort();
    }

    Matrix tmp(A.num_of_rows() - 1, A.num_of_columns() - 1);

    for(size_t i = 0, x = 0; i < m; i++) {
        if (i == r) {
            x = 1;
            continue;
        }

        for(size_t j = 1; j < n; j++)
            tmp.set(i - x, j - 1, A.get(i, j));
    } 

    return tmp;
}

void Matrix::print() {
    for(size_t i = 0; i < m; i++) {
        for(size_t j = 0; j < n; j++) {
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }
}

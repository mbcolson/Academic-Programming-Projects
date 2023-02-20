#ifndef MATRIX_H
#define MATRIX_H

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class Matrix {
   public:
     Matrix(size_t _m, size_t _n);

     void set(size_t i, size_t j, ll val);

     ll get(size_t i, size_t j) const;

     size_t num_of_rows() const;

     size_t num_of_columns() const;

     Matrix& operator+=(Matrix& rhs);

     friend Matrix operator+(Matrix lhs, Matrix& rhs);

     Matrix& operator*=(Matrix& rhs);

     friend Matrix operator*(Matrix lhs, Matrix& rhs);

     const Matrix& transpose();

     ll det();

     void print();

   private:
     size_t m, n;
     vector<vector<ll>> a;

     ll determinant();

     Matrix subMatrix(const Matrix& A, size_t r) const;
};

#endif

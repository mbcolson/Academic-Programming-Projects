#include "Matrix.h"

#define ROWS 7 
#define COLS 7 

int main() {
    srand(time(NULL));

    Matrix A(ROWS,COLS);
    Matrix B(ROWS,COLS);
    Matrix C(ROWS,COLS);
    Matrix D(3,8);
    Matrix E(ROWS,COLS);
    Matrix F(ROWS,COLS);
    Matrix G(ROWS,COLS);
    Matrix H(ROWS,COLS);

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            A.set(i, j, rand() % 15);
            B.set(i, j, rand() % 15);
            E.set(i, j, rand() % 15);
            F.set(i, j, rand() % 15);
            G.set(i, j, rand() % 15);
            H.set(i, j, rand() % 15);
        }
    }
    
    C = A * B;

    cout << "A = " << endl;

    A.print();

    cout << endl << "B = " << endl;

    B.print();

    cout << endl << "C = A * B" << endl;

    C.print();

    cout << endl;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 8; j++)
           D.set(i, j, rand() % 15);
    }

    cout << "D = " << endl;

    D.print();

    cout << endl;

    D.transpose();

    cout << "D.transpose() = " << endl;

    D.print();

    ll a_det = A.det(), b_det = B.det(), c_det = C.det();

    cout << endl << "A.det() is: " << a_det << endl;
   
    cout << endl << "B.det() is: " << b_det << endl;

    cout << endl << "A.det() * B.det() is: " << a_det * b_det << endl;

    cout << endl << "C.det() is: " << c_det << endl;
    
    cout << endl << "E = " << endl;

    E.print();

    cout << endl << "F = " << endl;

    F.print();

    cout << endl << "E += F" << endl;

    E += F;

    cout << endl << "E = " << endl;

    E.print();

    cout << endl << "F = " << endl;

    F.print();

    cout << endl << "G = " << endl;

    G.print();

    cout << endl << "H = " << endl;

    H.print();

    cout << endl << "G *= H" << endl;

    G *= H;

    cout << endl << "G = " << endl;

    G.print();

    cout << endl << "H = " << endl;

    H.print();

    return 0;
}

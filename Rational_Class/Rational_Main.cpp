#include "Rational.h"
using namespace std;

int main() {
     Rational r1(2,5), r2(3,7), r3(1,1), r4(8,11), r5(1,1), r6(2,3), r7(3,5), r8(3,1);
     
     long l1 = 3, l2 = 4, l3 = 7;
     
     cout << endl << "Enter a rational to store in r5 (example: 5/7): ";
     cin >> r5;
     
     cout << "r5(in reduced form) is: " << r5 << endl;
     
     cout << "r1 is: " << r1 << endl;
     cout << "r2 is: " << r2 << endl;
     cout << "r3 is: " << r3 << endl;
     cout << "r4 is: " << r4 << endl;
     cout << "r5 is: " << r5 << endl;
     cout << "r6 is: " << r6 << endl;
     cout << "r7 is: " << r7 << endl;
     cout << "l1 is: " << l1 << endl;
     cout << "l2 is: " << l2 << endl;
     cout << "l3 is: " << l3 << endl;
     
     r1 += r2;
     
     cout << "r1 += r2" << endl;
     cout << "r1 is now: " << r1 << endl;
     cout << "r3 is: " << r3 << endl;
     cout << "r4 is: " << r4 << endl;
     
     r3 = r1 + r4;
     
     cout << "r3 = r1 + r4" << endl;
     cout << "r3 is now: " << r3 << endl;
     
     r4++;
     cout << "r4++ is: " << r4 << endl;
     
     ++r3;
     cout << "++r3 is: " << r3 << endl;
     
     r1--;
     cout << "r1-- is: " << r1 << endl;
     
     --r2;
     cout << "--r2 is: " << r2 << endl;
     
     cout << "r3 is: " << r3 << endl;
     cout << "r4 is: " << r4 << endl;
     
     r1 = r3 - r4;
     
     cout << "r1 = r3 - r4" << endl;
     cout << "r1 is now: " << r1 << endl;
     cout << "r4 is: " << r4 << endl;
     
     r1 *= r4;
     
     cout << "r1 *= r4" << endl;
     cout << "r1 is now: " << r1 << endl;
     cout << "r3 is: " << r3 << endl;
     cout << "r4 is: " << r4 << endl;
     
     r3 /= r4;
     
     cout << "r3 /= r4" << endl;
     cout << "r3 is now: " << r3 << endl;
     cout << "r4 is: " << r4 << endl;
     
     -r4;
     
     cout << "-r4" << endl;
     
     r3 = r1 + r4;
     
     cout << "r3 = r1 + r4" << endl;
     cout << "r3 is now: " << r3 << endl;
     
     r4++;
     
     cout << "r4++ is: " << r4 << endl;
     
     ++r3;
     
     cout << "++r3 is: " << r3 << endl;
     
     r1--;
     
     cout << "r1-- is: " << r1 << endl;
     
     --r2;
     
     cout << "--r2 is: " << r2 << endl;
     cout << "r3 is: " << r3 << endl;
     cout << "r4 is: " << r4 << endl;
     
     r1 = r3 - r4;
     
     cout << "r1 = r3 - r4" << endl;
     cout << "r1 is now: " << r1 << endl;
     cout << "r4 is: " << r4 << endl;
     
     r1 *= r4;
     
     cout << "r1 *= r4" << endl;
     cout << "r1 is now: " << r1 << endl;
     cout << "r3 is: " << r3 << endl;
     cout << "r4 is: " << r4 << endl;
     
     r3 /= r4;
     
     cout << "r3 /= r4" << endl;
     cout << "r3 is now: " << r3 << endl;
     cout << "r4 is: " << r4 << endl;
     
     -r4;
     
     cout << "-r4" << endl;
     cout << "r4 is now: " << r4 << endl;
     cout << "r2 is: " << r2 << endl;
     
     +r2;
     
     cout << "+r2" << endl;
     cout << "r2 is now: " << r2 << endl;
     
     r5 += 2;
     
     cout << "r5 += 2" << endl;
     cout << "r5 is now: " << r5 << endl;
     cout << "r2 and r5 are: " << (r2 == r5 ? "equal" : "not equal") << endl;
     cout << "r1 is " << (r1 < r2 ? "< r2" : ">= r2") << endl;
     cout << "r2 is " << (r2 < l1 ? "< l1" : ">= l1") << endl;
     cout << "r3 and r4 are: " << (r2 != r5 ? "not equal" : "equal") << endl;
     cout << "r5 is " << (r2 >= l2 ? ">= l2" : "< l2") << endl;
     cout << "r6 and l3 are: " << (r6 != l3 ? "not equal" : "equal") << endl;
     cout << "r8 and l1 are: " << (r8 == l1 ? "equal" : "not equal") << endl;
     cout << "r6 is: " << r6 << endl;
     cout << "r6.pow(3)" << endl;
     cout << "r6 is now: " << r6.pow(3) << endl;
     cout << "r7 is: " << r7 << endl;
     cout << "r7.pow(-2)" << endl;
     cout << "r7 is now: " << r7.pow(-2) << endl;
     cout << "r4 is: " << r4 << endl;
     cout << "r4.pow(0)" << endl;
     cout << "r4 is now: " << r4.pow(0) << endl << endl; 

     return 0;
}

#include<iostream>
#include "./BigInt.cpp"
using namespace std;


int main(){
    // BigInteger a = BIGInt(123849584858474398434884);
    // BigInteger b = BIGInt(98765432109876543210);
    // cout << a + b<< "\n";
    BigInteger c = BIGInt(-7);
    BigInteger d = BIGInt(2);
    BigInteger e = BIGInt(1111111111111111111111111111111111111111);
    // cout<< c*e*d <<endl;
    // cout<< c-d-e <<endl;
    // cout<< c*d <<endl;
    cout<<e/d<<endl;
    return 0;
}
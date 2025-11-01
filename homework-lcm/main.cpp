#include <iostream>

using namespace std;


unsigned long long int mod(unsigned long long int a, unsigned long long int b){
     while (a >= b){
	a -= b;}
    return a;}


unsigned long long int gcd(unsigned long long int a, unsigned long long int b){
    while (a != 0 && b != 0){
	if (a > b){a = mod(a,b);}
	else {b = mod(b,a);}}
    return a+b;}

unsigned long long int mp(unsigned long long int a, unsigned long long int k){
    unsigned long long int result = 0;
    while(k != 0){
	k--;
	result += a;}
    return result;}


unsigned long long int division(unsigned long long int a, unsigned long long int b){
    unsigned long k = 0;
    while(a >= b){
	k++;
	a-=b;}
    return k;}

unsigned long long int lcm(unsigned long long int a, unsigned long long int b){           
    return division(mp(a,b),gcd(a,b));}



int main(){
    unsigned long long int a,b;
    cin >> a >> b;
    cout << lcm(a,b) << endl;
    }

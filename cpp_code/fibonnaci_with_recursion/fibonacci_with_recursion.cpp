#include <iostream>
using namespace std;
int fib(int);
int main()
{
    int num;
    cout<<"enter the number: ";
    cin>>num;
    cout<<"fibonacci of the number "<<num<<" is "<<fib(num);

}
int fib( int n)
{
    if (n==1 || n==2)
        return 1;
    else
        return fib(n-1)+fib(n-2);
}
#include<iostream>
using namespace std;
long long N(long long m, long long n)
{
    long long a = 1024; //初始空間2^10
    long long top = 0;
    long long* s = new long long[a];
    s[top] = m;
    top++;
    while (top > 0)
    {
        top--;
        m= s[top];
        if(m==0)
        {
            n++;
        }
        else if (n == 0)
        {
            if (top + 1 >= a) //空間不夠 *2
            {
                a *= 2;
                long long* news = new long long[a];
                for (long long i = 0; i < top; i++) {
                    news[i] = s[i];
                }
                delete[] s;
                s = news;
            }
            s[top] = m - 1;
            top++;
            n = 1;
        }
        else
        {
            if (top + 2 >= a) {
                a *= 2;
                long long* news = new long long[a];
                for (long long i = 0; i < top; ++i) {
                    news[i] = s[i];
                }
                delete[] s;
                s = news;
            }
            //A(m-1,(m,n-1))
            s[top] = m - 1;
            top++;
            s[top] = m;
            top++;
            n = n - 1;
        }
    }
    delete[] s;
    return n;
}
int main()
{
    long long m, n;
    cin >> m >> n;
    cout << N(m, n) << endl;
    return 0;
}
#include<iostream>
using namespace std;
long long A(long long m, long long n)
{
	if (m == 0)
	{
		return ++n;
	}
	else if (n == 0)
	{
		return A(m - 1, 1);
	}
	else
	{
		return A(m - 1, A(m, n - 1));
	}
}
int main()
{
	long long m, n;
	cin >> m >> n;
	cout << A(m, n)<<endl;
	return 0;
}
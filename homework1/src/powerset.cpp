#include <iostream>
#include <string>
using namespace std;
void powereset(string A[], string s[], int a, int n, int b)
{    
    if (a == n) 
    {
        cout << "{";
        for (int j = 0; j < b; j++) 
        {
            cout << s[j];
            if (j != b - 1) cout << ",";
        }
        cout << "}" << endl;
        return ;
    }
    powereset(A, s, a + 1, n, b); // 不加當前 A[i]，處理下一個元素
    s[b] = A[a]; // 加入當前A[i]到子集
    powereset(A, s, a + 1, n, b + 1); // 處理下一個元素
}

int main() {
    int n;
    cout << "n:";
    cin >> n;
    string* A = new string[n];
    string* s = new string[n];
    cout << "集合元素 : ";
    for (int i = 0; i < n; i++) 
    {
        cin >> A[i];
    }
    cout << "集合的冪集為:" << endl;
    powereset(A, s, 0, n, 0);
    delete[] A;
    delete[] s;
    return 0;
}
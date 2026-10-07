# 41443103

題目一

## 解題說明

本題要求用遞迴和非遞迴兩種方式計算Ackermann函數。

Ackermann函數定義:

$$
A(m,n)=
\begin{cases}
n+1 & m=0\\
A(m-1,1) & m>0,\ n=0\\
A(m-1,A(m,n-1)) & otherwise\\
\end{cases}
$$

### 解題策略

#### 遞迴
1. 使用遞迴函式依照定義拆解成三個判斷式 $m=0$, $n=0$,和其餘狀況($m>0$ $and$ $n>0$)。
2. 當 $m=0$時，返回 $n+1$ 作為遞迴的結束條件。
3. 當 $n=0$ 與其餘，則前者呼叫 $A(m-1,1)$，後者呼叫巢狀 $A(m-1, A(m,n-1))$。
4. 主程式輸入m和n並呼叫遞迴函式後，輸出計算結果。
#### 非遞迴
1. 使用動態陣列模擬堆疊，避免造成溢位。
2. 當空間不足時，將陣列空間乘2。
3. 使用while迴圈取出堆疊頂端top的 $m$ 值，依判斷式進行條件判斷後執行。
4. 遇到其餘情況的巢狀時，將依序放入堆疊。
5. 主程式輸入m和n後，進迴圈計算結束後，釋放動態記憶體並輸出結果。

## 程式實作

以下為主要程式碼：
#### 遞迴
```cpp
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
```
#### 非遞迴
```cpp
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
```

## 效能分析

1. 時間複雜度： $O(A(m, n))$。
2. 空間複雜度： $O(A(m, n))$，非遞迴較不容易產生溢位。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $m$ | 輸入參數 $n$ | 預期輸出 | 實際輸出 遞迴 | 實際輸出 非遞迴 |
|----------|--------------|--------------|----------|----------|----------|
| 測試一   | $m = 0$      | $n = 0$      | 1        | 1        | 1        |
| 測試二   | $m = 1$      | $n = 1$      | 3        | 3        | 3        |
| 測試三   | $m = 3$      | $n = 3$      | 61        | 61        | 61        |
| 測試四   | $m = 4$      | $n = 2$      | $2^{65,536} - 3$ | 異常拋出  | 異常拋出  |
| 測試五   | $m = -1$     | $n = -1$     | 異常拋出 | 異常拋出 | 異常拋出  |

### 編譯與執行指令

```shell
$ g++ main.cpp --std=c++17 -o main.exe
$ .\main.exe
3 3
61
```

### 結論

1. 遞迴與非遞迴版本皆能正確且精確地計算出 Ackermann 在合法範圍內的數值。
2. 非遞迴版本透過動態陣列模擬堆疊並具備容量自動倍增機制，成功在主記憶體中完成狀態維護與展開。
3. 測試案例涵蓋了基礎邊界條件，驗證了程式的運算正確性
4. 同時涵蓋了極端條件，例如數值過大或輸入無效範圍時，因突破 long long 範圍或超越定義域而產生的極限與異常現象。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **程式邏輯簡單直觀**  
   遞迴的寫法能夠清楚表達「將問題拆解為更小的子問題」的核心概念。  
   例如，計算 $\Sigma(n)$ 的過程可分解為：  

   $$
   \Sigma(n) = n + \Sigma(n-1)
   $$

   當 $n$ 等於 1 或 0 時，直接返回結果，結束遞迴。

2. **易於理解與實現**  
   遞迴的程式碼更接近數學公式的表示方式，特別適合新手學習遞迴的基本概念。  
   以本程式為例：  

   ```cpp
   int sigma(int n) {
       if (n < 0)
           throw "n < 0";
       else if (n <= 1)
           return n;
       return n + sigma(n - 1);
   }
   ```

3. **遞迴的語意清楚**  
   在程式中，每次遞迴呼叫都代表一個「子問題的解」，而最終遞迴的返回結果會逐層相加，完成整體問題的求解。  
   這種設計簡化了邏輯，不需要額外變數來維護中間狀態。

透過遞迴實作 Sigma 計算，程式邏輯簡單且易於理解，特別適合展示遞迴的核心思想。然而，遞迴會因堆疊深度受到限制，當 $n$ 值過大時，應考慮使用迭代版本來避免 Stack Overflow 問題。

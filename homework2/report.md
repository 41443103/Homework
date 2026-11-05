# 41443103
### 作業二
## 解題說明

本題要求使用者輸入兩多項式計算相加、相乘，排序後輸出，輸入X值計算多項式值，使用多載<<與>>。

使用者可選擇輸入幾項後，先係數後指數( 2 3 -> $2x^3$ )，每單位依次輸入。

### 解題策略

1. ​使用物件導向將各功能分開實現
   Term和Polynomial類別
   加法 Add
   乘法 Mult
   求值 Eval(x)
2. ​陣列空間不足自動倍增
3. 多載輸入、出運算子，使多項式排序與合併

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
using namespace std;
class Polynomial;
class Term
{
    friend Polynomial; 
    friend ostream& operator<<(ostream& os, const Polynomial& p);
private:
    float coef; //係數
    int exp; //指數
};

class Polynomial
{
    friend ostream& operator<<(ostream& os, const Polynomial& p);
    friend istream& operator>>(istream& is, Polynomial& p);
private:
    Term* termArray; //非零項的陣列
    int capacity; //陣列大小
    int terms; //非零項

    void newTerm(float theCoef, int theExp) 
    {
        if (terms == capacity) 
        {
            capacity *= 2;
            Term* temp = new Term[capacity];
            for (int i = 0; i < terms; i++) 
            {
                temp[i] = termArray[i];
            }
            delete[] termArray;
            termArray = temp;
        }
        termArray[terms].coef = theCoef;
        termArray[terms].exp = theExp;
        terms++;
    }
public:
    Polynomial() : capacity(2), terms(0)
    {
        termArray = new Term[capacity];
    }
    ~Polynomial()
    {
        delete[] termArray;
    }
    Polynomial(const Polynomial& other) 
    {
        capacity = other.capacity;
        terms = other.terms;
        termArray = new Term[capacity];
        for (int i = 0; i < terms; i++) 
        {
            termArray[i] = other.termArray[i];
        }
    }
    Polynomial& operator=(const Polynomial& other) 
    {
        if (this != &other) 
        {
            delete[] termArray;
            capacity = other.capacity;
            terms = other.terms;
            termArray = new Term[capacity];
            for (int i = 0; i < terms; i++) 
            {
                termArray[i] = other.termArray[i];
            }
        }
        return *this;
    }
//相加
    Polynomial Add(const Polynomial& b) 
    {
        Polynomial c;
        int aPos = 0, bPos = 0;
        while ((aPos < terms) && (bPos < b.terms)) 
        {
            if (termArray[aPos].exp == b.termArray[bPos].exp) 
            {
                float t = termArray[aPos].coef + b.termArray[bPos].coef;
                if (t != 0) c.newTerm(t, termArray[aPos].exp);
                aPos++; bPos++;
            }
            else if (termArray[aPos].exp < b.termArray[bPos].exp) 
            {
                c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
                bPos++;
            }
            else 
            {
                c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
                aPos++;
            }
        }
        for (; aPos < terms; aPos++)
            c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
        for (; bPos < b.terms; bPos++)
            c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);

        return c;
    }
//相乘
    Polynomial Mult(Polynomial poly) 
    {
        Polynomial c;
        for (int i = 0; i < terms; i++) 
        {
            for (int j = 0; j < poly.terms; j++) 
            {
                float newCoef = termArray[i].coef * poly.termArray[j].coef;
                int newExp = termArray[i].exp + poly.termArray[j].exp;
                Polynomial temp;
                temp.newTerm(newCoef, newExp);
                c = c.Add(temp);
            }
        }
        return c;
    }
    float Eval(float f) 
    {
        float result = 0;
        for (int i = 0; i < terms; i++) 
        {
            float termVal = termArray[i].coef;
            for (int j = 0; j < termArray[i].exp; j++) 
            {
                termVal *= f;
            }
            result += termVal;
        }
        return result;
    }
};
//帶入X
ostream& operator<<(ostream& os, const Polynomial& p) 
{
    if (p.terms == 0) 
    {
        os << "0";
        return os;
    }
    for (int i = 0; i < p.terms; i++) 
    {
        os << p.termArray[i].coef << "x^" << p.termArray[i].exp;
        if (i < p.terms - 1) os << " + ";
    }
    return os;
}
istream& operator>>(istream& is, Polynomial& p) 
{
    delete[] p.termArray;
    p.capacity = 2;
    p.terms = 0;
    p.termArray = new Term[p.capacity];
    int numTerms;
    cout << "請輸入非零項的數量: ";
    is >> numTerms;
    for (int i = 0; i < numTerms; i++) 
    {
        float c;
        int e;
        cout << "請輸入第 " << i + 1 << " 項的係數與指數 (3 2 代表 3x^2): ";
        is >> c >> e;
        if (c != 0) 
        {
            Polynomial temp;
            temp.newTerm(c, e);
            p = p.Add(temp);
        }
    }
    return is;
}
int main() 
{
    Polynomial p1, p2;
    cout << "輸入第一個多項式" << endl;
    cin >> p1;
    cout  << p1 << endl;
    cout << "輸入第二個多項式" << endl;
    cin >> p2;
    cout << p2 << endl;
    Polynomial p3 = p1.Add(p2);
    cout << "相加:" << p3 << endl;
    Polynomial p4 = p1.Mult(p2);
    cout << "相乘:" << p4 << endl;
    float val;
    cout << "\n請輸入X值:";
    cin >> val;
    cout << "p1=" << p1.Eval(val) << endl;
    cout << "p2=" << p2.Eval(val) << endl;
    return 0;
}
```

## 效能分析

#### 空間複雜度：
- newTerm: $O(1)$
- Add: $O(n+m)$
- Mult: $O(n*m^2)$
- Eval: $O(n)$

#### 時間複雜度：
- newTerm: $O(1)$
- Add: $O(n+m)$
- Mult: $O(n*m^2)$
- Eval: $O(n)$

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $m$ | 輸入參數 $n$ | 預期輸出 | 實際輸出 遞迴 | 實際輸出 非遞迴 |
|----------|--------------|--------------|----------|----------|----------|
| 測試一   | $m = 0$      | $n = 0$      | 1        | 1        | 1        |
| 測試二   | $m = 1$      | $n = 1$      | 3        | 3        | 3        |
| 測試三   | $m = 3$      | $n = 3$      | 61        | 61        | 61        |
| 測試四   | $m = 4$      | $n = 2$      | $2^{65,536} - 3$ | 異常輸出  | 異常輸出  |
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

### 選擇遞迴與非遞迴的差異

#### 遞迴
1. 定義上直觀性
本身的數學定義即為巢狀遞迴結構，無損地將數學公式轉譯為程式碼，邏輯單純且直觀。
2. 依賴系統呼叫堆疊
​資料結構使用系統內建的呼叫堆疊
，自動在背景記錄每一層的參數與返回位置，無須手動編寫記憶體管理程式碼。
3. 系統呼叫堆疊空間有限
當輸入數值較大（例如 $m > 4 ）時，堆疊會迅速耗盡，導致程式發生溢位而異常終止。

#### 非遞迴
1. 手動模擬堆疊
透過宣告一維陣列，並利用top與 while 來手動控制狀態的推入與彈出，還原巢狀遞迴的運算順序，相比遞迴較複雜。
2. 動態記憶體與空間擴增
無法預測總需要多少空間，堆疊空間即將用盡時，自動將陣列容量乘以 2，並將舊資料移到新陣列中，兼具彈性與效率。
3. ​提升系統強固性與安全性
將記憶體從受限的系統呼叫堆疊轉移至動態陣列，繞過了系統預設的堆疊大小限制，降低因過度遞迴而崩潰的風險。

無論採用遞迴或非遞迴，兩者由於 Ackermann 函數的數值成長呈爆炸性，當輸入 m 稍大時，必然會面臨整數型態的溢位極限。因此，非遞迴架構的核心在於使程式在合法範圍內運行得更為穩定。


## 題目二
## 解題說明

本題要求​給定個有 $n$個元素的集合 $S$，並輸出所有可能子集所組成的冪集合。

### 解題策略

1. 對每個元素進行兩種選擇，不加入當前元素，或加入當前元素進入下一個子問題。
2. 條件中止值為 a 等於集合大小 n 時，即完成一個子集的組合，直接輸出結果並返回。
3. 由使用者輸入集合大小與內容，配置動態陣列儲存資料，呼叫遞迴函式後釋放記憶體。

## 程式實作

以下為主要程式碼：
#### 遞迴
```cpp
#include <iostream>
#include <string>
using namespace std;
void powereset(string A[], string s[], int a, int n, int b)
{    
    if (a==n) 
    {
        cout << "{";
        for (int j=0; j<b; j++) 
        {
            cout << s[j];
            if (j!=b-1) cout << ",";
        }
        cout << "}" << endl;
        return ;
    }
    powereset(A, s, a + 1, n, b); // 不加當前 A[i]，處理下一個元素
    s[b]=A[a]; // 加入當前A[i]到子集
    powereset(A, s, a + 1, n, b + 1); // 處理下一個元素
}

int main() {
    int n;
    cout<<"n:";
    cin>>n;
    string* A=new string[n];
    string* s=new string[n];
    cout<<"集合元素 : ";
    for (int i=0; i<n;i++) 
    {
        cin >> A[i];
    }
    cout << "集合的冪集為:" << endl;
    powereset(A, s, 0, n, 0);
    delete[] A;
    delete[] s;
    return 0;
}
```

## 效能分析

1. 空間複雜度： $O(n)$
2. 時間複雜度： $O(n*2^n)$

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $n$ | 輸入元素  | 預期輸出 | 實際輸出 |
|----------|--------------|--------------|----------|----------|
| 測試一   | $n = 1$      | a      | () (a)       | () (a)       |
| 測試二   | $n = 2$      | ab     |() (b) (a) (a,b)  | () (b) (a) (a,b) |
| 測試三   | $n = 3$      | abc    | () (c) (b) (b,c) (a) (a,c) (a,b) (a,b,c) | () (c) (b) (b,c) (a) (a,c) (a,b) (a,b,c) |

### 編譯與執行指令

```shell
$ g++ main.cpp --std=c++17 -o main.exe
$ .\main.exe
n:3
集合元素 : a b c
集合的冪集為:
{}
{c}
{b}
{b,c}
{a}
{a,c}
{a,b}
{a,b,c}
```

### 結論

1. 程式能正確生成並列舉出給定集合的所有冪集（Power Set）組合。
2. 透過遞迴與「包含或不包含」的決策樹概念，結合動態記憶體配置與釋放，確保程式在執行過程中的資料正確性與記憶體安全。
3. 時間複雜度為 $O(2^n)$，能有效處理一般規模的集合，但在 $n$值過大時，輸出與遞迴次數會呈指數級成長，較沒效率。

## 申論及開發報告

### 選擇遞迴與動態陣列的原因
使用遞迴與動態陣列來計算集合冪集（Power Set）的主要原因如下：

 1. 透過參數記錄當前處理的索引與子集長度，使程式邏輯與遞迴終止條件（$a == n$）明確清晰。
 2. 使用遞迴來模擬「包含與不包含」的二元決策樹，將 $n$ 個元素的冪集問題拆解為逐個元素取捨的子問題，完美對應 $2^n$ 種子集組合。
 3. 利用動態陣列依據使用者輸入的集合大小 $n$ 配置記憶體，確保資源妥善利用並避免空間浪費。

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
- newTerm: $O(1)$ 當須擴充陣列時會配置一個新陣列，此時短暫同時存在新舊陣列
- Add: $O(n+m)$ 建立一個新多項式來儲存結果，其非零項最多為 $n+m$ 個
- Mult: $O(n*m^2)$ 相乘後最多會含有nm個不同項
- Eval: $O(n)$ 僅使用常數額外的變數儲存累加結果

#### 時間複雜度：
- newTerm: $O(1)$
- Add: $O(n+m)$ 
- Mult: $O(n*m^2)$
- Eval: $O(n)$

## 測試與驗證

### 測試案例

| 測試案例 | 輸入多項式一 | 輸入多項式二 |x值| 預期輸出 | 實際輸出|
|---------|-------------|-------------|--|----------|----------|
| 測試一   | $x^3+2x^2+3x$ | $3x^2-1x$ |1|相加: $1x^3+5x^2+2x^1$ ,相乘: $3x^5 + 5x^4 + 7x^3 + -3x^2$ ,p1=6,p2=2 |相加: $1x^3 + 5x^2 + 2x^1$ ,相乘: $3x^5 + 5x^4 + 7x^3 + -3x^2$ ,p1=6,p2=2|
| 測試二   | $x^2+4x^5-3x^3$  | $2x+5x^4$ |1| 相加: $4x^5 + 5x^4 + -3x^3 + 1x^2 + 2x^1$ , 相乘: $20x^9 + -15x^7 + 13x^6 + -6x^4 + 2x^3$ ,p1=2,p2=7       |相加: $4x^5 + 5x^4 + -3x^3 + 1x^2 + 2x^1$ , 相乘: $20x^9 + -15x^7 + 13x^6 + -6x^4 + 2x^3$ ,p1=2,p2=7|
| 測試三   | $x^4-2X+0$      | $3X^4-3X^3$|1|相加: $4x^4 + -3x^3 + -2x^1$ ,相乘: $3x^8 + -3x^7 + -6x^5 + 6x^4$ ,p1=-1,p2=0|相加: $4x^4 + -3x^3 + -2x^1$ ,相乘: $3x^8 + -3x^7 + -6x^5 + 6x^4$ ,p1=-1,p2=0|
| 測試四   | $3x^2+2x^3$ | $-3x^2-2x^3$ |1|相加: $0$ ,相乘: $-4x^6 + -12x^5 + -9x^4$ ,p1=5,p2=-5 |相加: $0$ ,相乘: $-4x^6 + -12x^5 + -9x^4$ ,p1=5,p2=-5|


### 編譯與執行指令

```shell
g++ main.cpp --std=c++17 -o main.exe

echo "=== 測試一 ==="
./main.exe << 'EOF'
3
1 3
2 2
3 1
2
3 2
-1 1
1
EOF

echo -e "\n=== 測試二 ==="
./main.exe << 'EOF'
3
1 2
4 5
-3 3
2
2 1
5 4
1
EOF

echo -e "\n=== 測試三 ==="
./main.exe << 'EOF'
2
1 4
-2 1
2
3 4
-3 3
1
EOF

echo -e "\n=== 測試四 ==="
./main.exe << 'EOF'
2
3 2
2 3
2
-3 2
-2 3
1
EOF
```

### 結論

1. 透過物件導向與動態記憶體配置，實作具備容量自動倍增機制的Polynomial類別，確保在運作時的穩定。
2. 實作相加 (Add) 與相乘 (Mult) ，並結合雙指標線性掃描與暫時物件累加，確保運算結果能自動完成排序與同類項合併。
3. 透過多載運算子 << 與 >>，直覺的格式化輸出，以及具備排序的互動式輸入機制。
 
## 申論及開發報告

### 動態陣列的選擇

1. 結構設計與記憶體彈性：
多項式的非零項數量在編譯期往往無法預測。採用動態配置，能夠在執行期依實際非零項動態增長，避免了固定大小陣列容易浪費空間或空間不足的缺點。

2. 自動擴容機制與均攤成本：
當非零項超過目前容量時，程式會自動觸發倍增擴容，配置新記憶體、複製並釋放舊記憶體，讓動態新增項目的均攤時間複雜度維持在常數級別。

3. 物件導向與記憶體安全：
手動管理動態記憶體時，若缺乏妥善的記憶體管理，容易造成記憶體洩漏。透過實作解構子、建構子與多載，確保物件能安全釋放資源。


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
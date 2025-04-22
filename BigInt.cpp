#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class BigInteger
{
private:
    
    string number;
    bool negative;
    static void stripZeros(string &s)
    {
        while (s.size() > 1 && s[0] == '0')
            s.erase(s.begin());
    }

    static int absCompare(const string &a, const string &b)
    {
        if (a.size() != b.size())
            return a.size() < b.size() ? -1 : +1;
        if (a == b)
            return 0;
        return a < b ? -1 : +1;
    }

    // addition
    static string addString(const string &a, const string &b)
    {
        string res;
        int carry = 0, i = a.size() - 1, j = b.size() - 1;
        while (i >= 0 || j >= 0 || carry)
        {
            int da = i >= 0 ? a[i--] - '0' : 0;
            int db = j >= 0 ? b[j--] - '0' : 0;
            int s = da + db + carry;
            carry = s / 10;
            res.push_back(char('0' + (s % 10)));
        }
        reverse(res.begin(), res.end());
        return res;
    }

    // subtraction
    static string subString(const string &a, const string &b)
    {
        string x = a, y = b, result;
        int borrow = 0, i = x.size() - 1, j = y.size() - 1;
        while (i >= 0)
        {
            int dx = (x[i] - '0') - borrow;
            int dy = j >= 0 ? y[j] - '0' : 0;
            if (dx < dy)
            {
                dx += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }
            result.push_back(char('0' + (dx - dy)));
            --i;
            --j;
        }
        while (result.size() > 1 && result.back() == '0')
            result.pop_back();
        reverse(result.begin(), result.end());
        return result;
    }

    // multiplication 
    static string mulString(const string &a, const string &b)
    {
        if (a == "0" || b == "0")
            return "0";
        int n = a.size(), m = b.size();
        vector<int> buf(n + m);
        for (int i = n - 1; i >= 0; --i)
        {
            int da = a[i] - '0';
            for (int j = m - 1; j >= 0; --j)
            {
                int db = b[j] - '0';
                int sum = buf[i + j + 1] + da * db;
                buf[i + j + 1] = sum % 10;
                buf[i + j] += sum / 10;
            }
        }
        string prod;
        size_t idx = 0;
        while (idx < buf.size() && buf[idx] == 0)
            ++idx;
        for (; idx < buf.size(); ++idx)
            prod.push_back(char('0' + buf[idx]));
        return prod;
    }
     

    // divition
    static string divString(const string &a, const string &b)
    {
        bool negA = false, negB = false;
        string x = a, y = b;
        if (!x.empty() && x[0] == '-')
        {
            negA = true;
            x.erase(x.begin());
        }
        if (!y.empty() && y[0] == '-')
        {
            negB = true;
            y.erase(y.begin());
        }

       
        stripZeros(x);
        stripZeros(y);

        if (y == "0")
            throw invalid_argument("division by zero");

        if (absCompare(x, y) < 0)
            return "0";

        bool negRes = negA ^ negB; 

        string result;
        string remainder;

      
        for (char digit : x)
        {
            remainder.push_back(digit);
            stripZeros(remainder);
            if (remainder.empty())
                remainder = "0";

            int low = 0, high = 9, q = 0;
            while (low <= high)
            {
                int mid = (low + high) / 2;
                string prod = mulString(y, string(1, char('0' + mid)));
                if (absCompare(prod, remainder) <= 0)
                {
                    q = mid;
                    low = mid + 1;
                }
                else
                {
                    high = mid - 1;
                }
            }

            result.push_back(char('0' + q));
            string sub = mulString(y, string(1, char('0' + q)));
            remainder = subString(remainder, sub);
        }

        stripZeros(result);
        if (result.empty())
            result = "0";

        if (result == "0")
            negRes = false;

        if (negRes)
            result.insert(result.begin(), '-');

        return result;
    }

public:
    BigInteger(string s = "0")
    {
        if (s[0] == '-')
        {
            negative = true;
            s.erase(s.begin());
        }
        else
        {
            negative = false;
        }
        stripZeros(s);
        if (s == "0")
            negative = false;
        number = move(s);
    }

    // unary minus
    BigInteger operator-() const
    {
        BigInteger r = *this;
        if (r.number != "0") // keep zero non-negative
            r.negative = !r.negative;
        return r;
    }

    // addition
    BigInteger operator+(BigInteger const &o) const
    {
        if (negative == o.negative)
        {
            return BigInteger((negative ? "-" : "") +
                              addString(number, o.number));
        }
        int cmp = absCompare(number, o.number);
        if (cmp == 0)
        {
            return BigInteger("0");
        }
        if (cmp > 0)
        { 
            auto mag = subString(number, o.number);
            return BigInteger((negative ? "-" : "") + mag);
        }
        else
        {
            auto mag = subString(o.number, number);
            return BigInteger((o.negative ? "-" : "") + mag);
        }
    }

    BigInteger &operator+=(BigInteger const &o)
    {
        *this = *this + o;
        return *this;
    }

    // subtraction
    BigInteger operator-(BigInteger const &o) const
    {
        return *this + (-o);
    }

    BigInteger &operator-=(BigInteger const &o)
    {
        *this = *this - o;
        return *this;
    }

    // multiplication
    BigInteger operator*(BigInteger const &o) const
    {
        auto mag = mulString(number, o.number);
        bool sign = (negative != o.negative) && mag != "0";
        return BigInteger((sign ? "-" : "") + mag);
    }

    BigInteger &operator*=(BigInteger const &o)
    {
        *this = *this * o;
        return *this;
    }

    BigInteger operator/(BigInteger const &o) const
    {
        string mag = divString(number, o.number);

        bool sign = (negative != o.negative) && (mag != "0");

        return BigInteger((sign ? "-" : "") + mag);
    }

    BigInteger &operator/=(BigInteger const &o)
    {
        string mag = divString(number, o.number);

        negative = (negative != o.negative) && (mag != "0");
        number = move(mag);

        return *this;
    }
    // printing
    friend ostream &operator<<(ostream &os, BigInteger const &x)
    {
        return os << (x.negative ? "-" : "") << x.number;
    }
};

// user-defined literal
BigInteger operator"" _big(char const *str, size_t)
{
    return BigInteger(string(str));
}
#define BIGInt(x) BigInteger(#x)
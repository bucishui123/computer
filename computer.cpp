#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>
#include <vector>
#include <sstream>
#include <stack>
#include"computer.h"
using namespace std;

Real_number::Real_number(int r, int n, int o) : result(r), num(n), oper(o) { /*cout << "OK" << endl;*/ }
Complex_number::Complex_number(int r, int i) : real(r), imag(i) { /*cout << "OK" << endl;*/ }

static int precedence(char op)
{
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

static vector<string> pares_real_expression(const string& line)  //中缀表达式 -> 后缀表达式
{
    vector<string> output;                                       //后缀表达式队列
    stack<char> op_stack;
                                                  
    auto is_oper = [](char c)                                    // Lambda 表达式
        {
            return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
        };

    for (size_t i = 0; i < line.size(); i++)
    {
        char c = line[i];
        if (c == ' ') continue;

        //数字处理
        if (isdigit(c) || c == '.')
        {
            string num;
            while (i < line.size() && (isdigit(line[i]) || line[i] == '.'))
            {
                num += line[i];
                i++;
            }
            i--;
            output.push_back(num);
        }

        //左括号
        else if (c == '(')
        {
            op_stack.push(c);
        }

        //右括号
        else if (c == ')')
        {
            while (!op_stack.empty() && op_stack.top()!= '(')
            {
                output.push_back(string(1, op_stack.top()));
                op_stack.pop();
            }
            if (!op_stack.empty()) op_stack.pop();
        }
        //运算符
        else if (is_oper(c))
        {
            if (c == '-' && (i == 0 || (!isdigit(line[i-1]) && isdigit(line[i-1]) != ')')))
            {
                string num;
                num = '-';
                i++;
                while (i<line.size() && (isdigit(line[i]) || line[i] == '.'))
                {
                    num += line[i];
                    i++;
                }
                i--;
                output.push_back(num);
                continue;
            }

            while (!op_stack.empty() && op_stack.top() != '(' && precedence(op_stack.top()) >= precedence(c))
            {
                output.push_back(string(1, op_stack.top()));
                op_stack.pop();
            }
            op_stack.push(c);
        }
    }
    
    while (!op_stack.empty())
    {
        output.push_back(string(1, op_stack.top()));
        op_stack.pop();
    }

    return output;
}

/*初始化空栈
从左到有扫描表达式token
遇到操作数直接压入栈
遇到运算符弹出栈顶两个元素（先出为右操作数，后出为左操作数），执行对应运算，将结果压回栈
扫描完毕后，栈中仅剩一个元素即为计算结果，若多于一个或少于一个及表达式非法
*/

static double rpnCount (const vector<string>& tokens)
{
    stack<double> token_stack;
    double result = 0;
    for (const string& token : tokens) //[3,4,2,*,+]
    //for(size_t i=0; i<tokens.size(); i++)
    {
        //const string& token = tokens[i];
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1))
            token_stack.push(stod(token));        // [3,4,2]
        else
        {
            char c = token[0];               //*,+
            double a = token_stack.top();    //右操作数
            token_stack.pop();
            
            double b = token_stack.top();    //左操作数
            token_stack.pop();
            switch (c)
            {
            case'+':
                result = b + a;               //3+8=11
                token_stack.push(result);     //[11]
                break;
            case'-':
                result = b - a;
                token_stack.push(result);
                break;
            case'*':
                result = b * a;                //2*4=8
                token_stack.push(result);      //[3,8]
                break;
            case'/':
                if (a == 0)
                    throw runtime_error("Error: 除数不能为零！");
                result = b / a;
                token_stack.push(result);
                break;
            case'^':
                result = pow(b, a);
                token_stack.push(result);
                break;
            default:
                throw runtime_error("Error：未知运算符");  //std::runtime_error
            }
        }
    }
    if (token_stack.size() != 1 || token_stack.empty())
        throw runtime_error("Error: 错误的表达式！");

    return token_stack.top();
}

void Real_number::display()
{
    // cout<<"====display运算器====" << endl;
    char input;
    cout << "按 R 开始运算，按 Q 退出: ";
    cin >> input;
    cin.ignore(10000, '\n');

    if (input == 'Q' || input == 'q')
        return; // 不要 exit，让程序自然结束

    if (input == 'R' || input == 'r')
    {
        //cout << "请输入: ";
        string line;
        double result;

        getline(cin, line);
        if (line == "= " || line == "=")
        {
            cout << "无效的表达式！" << endl;
            return;
        }
        result = rpnCount(pares_real_expression(line));
        cout << result << endl;
    }
}

std::istream &operator>>(std::istream &in, Complex_number &comp)
{
    in >> comp.real >> comp.imag;
    return in;
}
std::ostream &operator<<(std::ostream &out, const Complex_number &comp)
{
    if (comp.imag > 0)
        out << comp.real << "+" << comp.imag << "i";
    else if (comp.imag < 0)
        out << comp.real << comp.imag << "i";
    else
        out << comp.real << endl;

    return out;
}
Complex_number operator+(const Complex_number &comp1, const Complex_number &comp2)
{
    Complex_number Cn(comp1.real + comp2.real, comp1.imag + comp2.imag);
    return Cn;
}
Complex_number operator-(const Complex_number &comp1, const Complex_number &comp2)
{
    Complex_number Cn(comp1.real - comp2.real, comp1.imag - comp2.imag);
    return Cn;
}
Complex_number operator*(const Complex_number &comp1, const Complex_number &comp2)
{
    // (a+bi)(c+di) = (ac-bd) + (ad+bc)i
    Complex_number Cn(comp1.real * comp2.real - comp1.imag * comp2.imag,
                      comp1.real * comp2.imag + comp1.imag * comp2.real);
    return Cn;
}
Complex_number operator/(const Complex_number &comp1, const Complex_number &comp2)
{
    // (a+bi)/(c+di) = (ac+bd)/(c2+d2) + (bc-ad)/(c2+d2)i
    int denominator = comp2.real * comp2.real + comp2.imag * comp2.imag;

    if (denominator == 0)   //分母为0-报错
    {
        std::cout << "Error: 除数不能为零" << std::endl;
        return Complex_number(0, 0);
    }
    Complex_number Cn((comp1.real * comp2.real + comp1.imag * comp2.imag) / denominator,
                      (comp1.imag * comp2.real - comp1.real * comp2.imag) / denominator);
    return Cn;
}

static Complex_number parse_complex(const string &s) // 解析复数表达式字符串
{
    int real = 0, imag = 0;
    int sigen = 1;            // 符号位，1表示正，-1表示负
    int num = 0;              // 暂存当前累积的数字
    bool reading_real = true; // 当前在读实部还是虚部
    bool has_num = false;     // 是否已读到数字，用于判断i前有没有数字

    for (size_t i = 0; i < s.size(); ++i)
    {
        char c = s[i];
        if (c == ' ')
            continue; // 跳过空格
        if (c == '+' || c == '-')
        {
            if (has_num)
            {
                if (reading_real) real = num * sigen;
                else imag = num * sigen;  //可以用于处理异常输入（2i+1）,(2i=3i) ...
            }
            // 重置状态
            sigen = (c == '+') ? 1 : -1;
            num = 0;
            has_num = false;
            reading_real = true;
        }
        else if (c == 'i')
        {
            if (!has_num)
                num = 1;
            imag = num * sigen;
            // 重置状态
            reading_real = false;
            has_num = false;
        }
        else if (isdigit(c))
        {
            num = num * 10 + (c - '0');
            has_num = true;
        }
        else if (c == '(' || c == ')' || c == ' ')
        {
            continue; // 跳过括号和空格
        }
    }
    if (has_num)
    {
        if (reading_real)
            real = num * sigen;
        else
            imag = num * sigen;
    }
    return Complex_number(real, imag);
}

void Complex_number::display()
{
    Complex_number result(0, 0);
    char oper;
    cout << "按 R 开始运算，按 Q 退出: ";
    cin >> oper;
    cin.ignore(10000, '\n');

    if (oper == 'Q' || oper == 'q')
        return;
    if (oper != 'R' && oper != 'r')
    {
        cout << "Error" << endl;
        return;
    }
    else //(oper == 'R' || oper == 'r')
    {
        cout << "请输入表达式：" << endl;
        string line;
        while (getline(cin, line))
        {
            if (line.empty())
                continue;
            if (line == "=" || line == "= ")
                break;

            // size_t pos = line.find('+');
            // if (pos == string::npos) pos = line.find('-');
            int depth = 0;
            size_t pos = string::npos;
            for (size_t i = 0; i < line.size(); ++i)
            {
                char c = line[i];
                if (c == '(')
                    depth++;
                else if (c == ')')
                    depth--;
                else if ((c == '+' || c == '-' || c == '*' || c == '/') && depth == 0)
                {
                    pos = i;
                    break;
                }
            }
            if (pos == string::npos)
            {
                cout << "Error: 无效的表达式" << endl;
                continue;
            }

            string left = line.substr(0, pos);
            string right = line.substr(pos + 1);
            if (right.back() == '=')
                right.pop_back(); // 去掉等号

            Complex_number left_comp = parse_complex(left);
            Complex_number right_comp = parse_complex(right);
            char input_op = line[pos];

            switch (input_op)
            {
            case '+':
                result = result + left_comp + right_comp;
                break;
            case '-':
                result = result + left_comp - right_comp;
                break;
            case '*':
                result = result + left_comp * right_comp;
                break;
            case '/':
                result = result + left_comp / right_comp;
                break;
            default:
                cout << "Error: 无效的运算符" << endl;
                continue;
            }
            cout << "当前结果: " << result << endl;
            if (line.back() == '=')
                break;
        }
        cout << "最终结果: " << result << endl;
    }
}
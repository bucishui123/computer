#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>
#include <vector>
#include <sstream>
#include"computer.h"
using namespace std;

Real_number::Real_number(int r, int n, int o) :result(r), num(n), oper(o) { /*cout << "OK" << endl;*/ }
Complex_number::Complex_number(int r, int i) :real(r), imag(i) { /*cout << "OK" << endl;*/ }

void Real_number::display()
{
    //cout<<"====display函数被调用====" << endl;
    char input;
    cout << "按 R 开始计算，按 Q 退出: ";
    cin >> input;

    if (input == 'Q' || input == 'q') return; // 不要 exit，让程序自然结束

    if (input == 'R' || input == 'r')
    {
        //cout << "请输入初始值: ";
        cin >> result;
        while (true)
        {
            cin >> oper;
            if (oper == '=') break;

            cin >> num;
            switch (oper)
            {
            case '+': result += num; break;
            case '-': result -= num; break;
            case '*': result *= num; break;
            case '/':
                if (num != 0) result /= num;
                else cout << "除数不能为0" << endl;
                break;
            default: cout << "Error" << endl; break;
            }
            //cout << "Result: " << result << endl;
        }
        cout << "End result: " << result << endl;
    }
}

std::istream& operator>>(std::istream& in, Complex_number& comp)
{
    in >> comp.real >> comp.imag;
    return in;
}
std::ostream& operator<<(std::ostream& out, const Complex_number& comp)
{
    if (comp.imag > 0)
        out << comp.real << "+" << comp.imag << "i";
    else if (comp.imag < 0)
        out << comp.real << comp.imag << "i";
    else
        out << comp.real << endl;

	return out;
}
Complex_number operator+(const Complex_number& comp1, const Complex_number& comp2)
{
    Complex_number Cn(comp1.real + comp2.real, comp1.imag + comp2.imag);
    return Cn;
}
Complex_number operator-(const Complex_number& comp1, const Complex_number& comp2)
{
    Complex_number Cn(comp1.real - comp2.real, comp1.imag - comp2.imag);
	return Cn;
}

static Complex_number parse_complex(const string& s) // 解释器解析复数字符串
{
    int real = 0, imag = 0;
	int sigen = 1; // 符号位，1表示正数，-1表示负数
	int num = 0; // 暂存区（当前累积的数字）
	bool reading_real = true; // 当前读的是实部还是虚部
	bool has_num = false; // 是否已经读过数字（用于判断i前面有没有数字）

    for (size_t i = 0;i < s.size();++i)
    {
		char c = s[i];
		if (c == ' ') continue; // 跳过空格
        if (c == '+' || c == '-')
        {
            if (has_num)
            {
                if (reading_real) real = num * sigen;
                else imag = num * sigen;
            }
            // 重置状态
            sigen = (c == '+') ? 1 : -1;
            num = 0;
            has_num = false;
            reading_real = true;
        }
        else if (c == 'i')
        {
            if (!has_num) num = 1;
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
        if (reading_real)real = num * sigen;
        else imag = num * sigen;
    }
    return Complex_number(real, imag);
}

void Complex_number::display()
{
    Complex_number result(0, 0);
    char oper;
    cout << "按 R 开始计算，按 Q 退出: ";
    cin >> oper;
    cin.ignore(10000,'\n');

    if (oper == 'Q' || oper == 'q') return;
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
            if (line.empty()) continue;
            if (line == "=" || line == "= ") break;

            //size_t pos = line.find('+');
            //if (pos == string::npos) pos = line.find('-');
            int depth = 0;
            size_t pos = string::npos;
            for (size_t i = 0; i < line.size(); ++i) {
                char c = line[i];
                if (c == '(') depth++;
                else if (c == ')') depth--;
                else if ((c == '+' || c == '-') && depth == 0) {
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
            if (right.back() == '=') right.pop_back(); // 去掉等号

            Complex_number left_comp = parse_complex(left);
            Complex_number right_comp = parse_complex(right);
            char input_op = line[pos];

            switch (input_op)
            {
            case'+':
                result = result + left_comp + right_comp;
                break;
            case'-':
                result = result + left_comp - right_comp;
                break;
            default:
                cout << "Error: 无效的运算符" << endl;
                continue;
            }
            cout << "当前结果: " << result << endl;
            if (line.back() == '=') break;
        }
        cout << "最终结果: " << result << endl;
    }
}
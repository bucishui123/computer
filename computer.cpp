#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>
#include <vector>
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

void Complex_number::display()
{
	Complex_number result;
    char input;
    cout << "按 R 开始计算，按 Q 退出: ";
	cin >> input;

    if (input == 'Q' || input == 'q') return;

    if (input == 'R' || input == 'r')
    {
        std::cout << "请输入复数 (实部 虚部) 和运算符 (+, -, = 结束): ";
        while (true)
        {
            Complex_number temp;
           
            cin >> temp;
            char oper;
            cin >> oper;
            if (oper == '=') break;
            switch (oper)
            {
            case '+':
                result = result + temp;
				break;
            case '-':
                result = result - temp;;
                break;
            default:
                cout << "Error" << endl;
				continue;
            }
            cout << "当前结果：" << result << endl;
        }
        cout << "End result:" << result << endl;
    }
}
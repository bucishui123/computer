#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>
#include <vector>
#include"computer.h"
/*double add(double number1, double number2, char operator_zjx)
{
    return number1 + number2;
}

double minus_zjx(double number1, double number2, char operator_zjx)
{
    return number1 - number2;
}

double ride_zjx(double number1, double number2, char operator_zjx)
{
    return number1 * number2;
}

double get_zjx(double number1, double number2, char operator_zjx)
{
    return number1 / number2;
}
*/
using namespace std;

Real_number::Real_number(int r, int n, int o) :result(r), num(n), oper(o) 
    { cout << "OK" << endl; }
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

        //cout << "当前结果: " << result << endl;
        //cout << "请输入 运算符 数字 (例如 + 5)，输入 = 结束:" << endl;

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
            cout << "Result: " << result << endl;
        }
        cout << "End result: " << result << endl;
    }
}
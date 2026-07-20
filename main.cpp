#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
#include"computer.h"
using namespace std;
/*int main()
{
	double number1, number2;
	char operator_zjx;
	double end=0;
	cout << "请输入简单运算式子：";

	cin >> number1 >> operator_zjx >> number2;

	if (operator_zjx == '+')
	{
		end = add(number1, number2, operator_zjx);
	}

	if (operator_zjx == '-')
	{
		end = minus_zjx(number1, number2, operator_zjx);
	}

	if (operator_zjx == '*')
	{
		end = ride_zjx(number1, number2, operator_zjx);
	}

	if (operator_zjx == '/')
	{
		end = get_zjx(number1, number2, operator_zjx);
	}

	cout << end << endl;

	return 0;
}*/

int main()
{
	//system("chcp 65001 > nul");
	Shape* sp;
	Real_number Rn;
	sp = &Rn;
	sp->display();
	system("pause");
	return 0;
}

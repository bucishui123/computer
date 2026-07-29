#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
#include"computer.h"

int main()
{
	system("chcp 936 > nul");
	Shape* sp;
    Real_number Rn;
	Complex_number Cn;

	char oper;
	std::cout << "按 R 进行实数运算，按 C 进行复数运算: " <<;
	std::cin >> oper;
	if (oper == 'R' || oper == 'r')
	{
		sp = &Rn;
		sp->display();
		system("pause");
	}

	if (oper == 'C' || oper == 'c')
	{
		sp = &Cn;
		sp->display();
		system("pause");
	}
	return 0;
}

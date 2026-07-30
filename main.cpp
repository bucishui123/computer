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
	try {
		std::cout << "按 R 进行实数运算，按 C 进行复数运算: ";
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
	}
	catch(const std::runtime_error& s){
		std::cerr << "程序发生错误：" << std::endl
			      << s.what() << std::endl;
		return 404;
	}
	return 0;
}

#pragma once
#ifndef COMPUTREAM_H
#define COMPUTREAM_H

class Shape
{
public:
	virtual void display() {}
};
class Real_number :public Shape//实数运算
{
private:
	int result;  //结果值
	int num;  //当前输入
	char oper; //运算符
public:
	Real_number(int r = 0, int n = 0, int o = 0);
	//void input();
	void display();
};
//double add(double number1, double number2, char operator_zjx);
//double minus_zjx(double number1, double number2, char operator_zjx);
//double ride_zjx(double number1, double number2, char operator_zjx);
//double get_zjx(double number1, double number2, char operator_zjx);

#endif // !COMPUTREAM_H

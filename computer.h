#pragma once
#include<iostream>
#include<string>
#ifndef COMPUTREAM_H
#define COMPUTREAM_H

//在这里定义class！
class Shape
{
public:
	virtual void display() = 0;
};
/// <summary>
/// 实数运算类
/// </summary>
class Real_number :public Shape                                         //实数运算
{
private:
	int result;                                                         //结果值
	int num;                                                            //当前输入
	char oper;                                                          //运算符
public:
	Real_number(int r = 0, int n = 0, int o = 0);
	//void input();
	void display();
};
/// <summary>
/// 复数运算类
/// </summary>
class Complex_number :public Shape                                      //复数运算
{
private:
	int real;
	int imag;
public:
	Complex_number(int r=0, int i=0);
	void display();
	friend std::istream& operator>>(std::istream&, Complex_number&);
	friend std::ostream& operator<<(std::ostream&, const Complex_number&);
	friend Complex_number operator+(const Complex_number&, const Complex_number&);
	friend Complex_number operator-(const Complex_number&, const Complex_number&);
};

//在这里定义函数！
std::istream& operator>>(std::istream& in, Complex_number& comp);
std::ostream& operator<<(std::ostream& out, const Complex_number& comp);
Complex_number operator+(const Complex_number& comp1, const Complex_number& comp2);
Complex_number operator-(const Complex_number& comp1, const Complex_number& comp2);

//static int precedence(char op);
//static vector<std::string> pares_real_expression(const std::string& line);
static Complex_number parse_complex(const std::string& s);
#endif // !COMPUTREAM_H

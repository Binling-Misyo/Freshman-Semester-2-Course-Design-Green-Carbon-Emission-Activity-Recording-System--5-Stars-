#ifndef OTHERFUN_H
#define OTHERFUN_H

#include <iostream>
#include <vector>
using namespace std;

class OtherFun {//辅助函数类 
public:
	//加密函数
	static string pwX(string pw, int key);
	//解密函数 
	static string pwK(string pw);
	//双精度形式字符串转双精度  
	static double strtodb(string token);
	static int w(int num);//返回一个整数占多少位(此程序中"0"视为占0位） 
	//格式化分割每行数据
	static vector<string> spilt(string s, char c);
	//改变字体颜色
	static void setColor(int color);
}; 
#endif

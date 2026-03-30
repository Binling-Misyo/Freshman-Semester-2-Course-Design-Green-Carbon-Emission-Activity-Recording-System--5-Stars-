#include"../include/otherfun.h" 
#include <windows.h>
#include<cmath>
#include<sstream>

#define pwkey 3 

// OtherFun 成员函数实现
string OtherFun::pwX(string pw, int key)
{
	string ret = "";
	for (int i = 0; i < pw.size(); i++)
	{
		if (pw[i] >= 'a' && pw[i] <= 'z')
		{
			unsigned char ch = pw[i] + (key % 26);
			if (ch > 'z') ch -= 26;
			ret.push_back(ch);
		}
		else if (pw[i] >= 'A' && pw[i] <= 'Z')
		{
			unsigned char ch = pw[i] + (key % 26);
			if (ch > 'Z') ch -= 26;
			ret.push_back(ch);
		}
		else ret.push_back(pw[i]);
	}
	return ret;
}

string OtherFun::pwK(string pw)
{
	return pwX(pw, 26 - (pwkey % 26));
}

double OtherFun::strtodb(string token)
{
	string zheng = "";
	string xiao = "";
	string* p = &zheng;
	int pt = 0;
	for (int i = 0; i < token.size(); i++)
	{
		if (token[i] != '.')
		{
			p[pt].push_back(token[i]);
		}
		else
		{
			pt = 0;
			p = &xiao;
			continue;
		}
	}
	int z = 0, x = 0;
	for (int i = 0; i < zheng.size(); i++)
	{
		z *= 10;
		z += zheng[i] - '0';
	}
	for (int i = 0; i < xiao.size(); i++)
	{
		x *= 10;
		x += xiao[i] - '0';
	}
	int xw = w(x);
	double re = z + (x * pow(0.1, xw));
	return re;
}

int OtherFun::w(int num)
{
	int r = 0;
	while (num) {
		r++;
		num /= 10;
	}
	return r;
}

vector<string> OtherFun::spilt(string s, char c)
{
	vector<string> kens;
	istringstream liu(s);
	string temp;
	while (getline(liu, temp, c))
	{
		kens.push_back(temp);
	}
	return kens;
}

void OtherFun::setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

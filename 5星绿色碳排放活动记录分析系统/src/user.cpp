#include "../include/user.h"
#include "../include/otherfun.h"
#include<vector>

#define fengefu '|'

class FileTool;

// User 成员函数实现
User::User() :name(""), password(""), date(""), carbon_goal(default_carbon_goal) {}

User::User(string n, string p, string d, double g) :
	name(n), password(p), date(d), carbon_goal(g)
{}

string User::GetName()
{
	return name;
}
string User::GetPassword()
{
	return password;
}

string User::GetDate()
{
	return date;
}

double User::GetGoal()
{
	return carbon_goal;
}

void User::setgoal(double g)
{
	carbon_goal = g;
}

void User::setpassword(string p)
{
	password = p;
}
User User::load(string line)
{
	vector<string> parts = OtherFun::spilt(line, fengefu);
	return User(parts[0], OtherFun::pwK(parts[1]), parts[2], OtherFun::strtodb(parts[3]));
}

bool User::pwTF(string pw)
{
	return password == pw;
}

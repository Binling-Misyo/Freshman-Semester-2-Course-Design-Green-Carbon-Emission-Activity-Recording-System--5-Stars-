#ifndef USER_H
#define USER_H

#include<iostream>
using namespace std;

#define default_carbon_goal 5.0

class User {//用户类 
private:
	string name;
	string password;
	string date;
	double carbon_goal;
public:
	User();
	User(string n, string p, string d, double g = default_carbon_goal);
	string GetName();
	string GetPassword();
	string GetDate();
	double GetGoal();
	void setgoal(double g);
	void setpassword(string p);
	//账户字符串转换为账户对象 
	static User load(string line);
	//密码验证 
	bool pwTF(string pw);
}; 
#endif

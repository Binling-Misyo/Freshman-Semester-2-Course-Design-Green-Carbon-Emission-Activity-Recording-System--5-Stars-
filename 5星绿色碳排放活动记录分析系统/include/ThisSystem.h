#ifndef THISSYSTEM_H
#define THISSYSTEM_H

#include "ThisSystem.h"

#include<iostream>
using namespace std;

class User;

class ThisSystem {//系统模块函数类 
public:
	//维护开发中显示函数
	static void pass();
	//主界面函数 
	static bool GUI(User& user);
	//返回当前时间函数 
	static string getCurrentDate();
	//注册函数 
	static void login();
	//登录函数
	static void design(User& user);
	//新建用户个人碳排放活动记录函数
	static bool recordNewActivity(User& user);
	//周报告显示函数
	static void showWeeklyReport(User& user);
	//月报告显示函数
	static void showMonthlyReport(User& user);
	//修改个人密码函数
	static void changePassword(User& user);
};
#endif

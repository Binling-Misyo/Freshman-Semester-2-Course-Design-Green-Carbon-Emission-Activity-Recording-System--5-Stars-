#ifndef FILETOOL_H
#define FILETOOL_H
#include "CarbonActivity.h"

#include <iostream>
#include <vector>
#include <map>
using namespace std;

class CarbonActivity;
class User;

class FileTool {//文件管理类函数 
public:
	//加载全体用户信息
	static vector<User> LoadUserlist();
	//保存全体用户信息到程序中 
	static void SaveUserlist(vector<User> list);
	//按用户名查找并返回用户对象 
	static User FindUser(vector<User> list, string name);
	//读取个人碳活动列表
	static vector<CarbonActivity*> LoadCarbonActiveList(string name);
	//读取全班碳活动列表
	static map<string, vector<CarbonActivity*>> LoadAllCarbonActiveList();
	// 保存指定用户指定日期的碳排放总和
	static void saveDailyEmissionSum(const std::string& username, const std::string& date, double sum);
	// 加载指定用户指定日期的碳排放总和（返回-1表示未找到）
	static double loadDailyEmissionSum(const std::string& username, const std::string& date);
};
#endif

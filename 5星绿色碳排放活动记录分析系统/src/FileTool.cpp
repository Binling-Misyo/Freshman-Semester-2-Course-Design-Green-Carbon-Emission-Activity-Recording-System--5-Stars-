#include"../include/FileTool.h"
#include"../include/user.h"
#include"../include/otherfun.h"
#include"../include/CarbonActivity.h"
#include <vector>
#include<iostream>
#include <string>
#include <fstream>
#define userfile "user.txt"
#define pwkey 3
using namespace std;
// FileTool 成员函数实现
vector<User> FileTool::LoadUserlist()
{
	ifstream file(userfile);
	string line;
	vector<User> userlist;
	while (getline(file, line))
	{
		userlist.push_back(User::load(line));
	}
	file.close();
	return userlist;
}

void FileTool::SaveUserlist(vector<User> list)
{
	ofstream file(userfile);
	for (size_t i = 0; i < list.size(); i++)//修改int类型防止超出int最大值溢出变为负数
	{
		User temp = list[i];
		file << temp.GetName() << "|";
		file << OtherFun::pwX(temp.GetPassword(), pwkey) << "|";
		file << temp.GetDate() << "|";
		file << temp.GetGoal() << endl;
	}
	file.close();
}

User FileTool::FindUser(vector<User> list, string name)
{
	for (size_t i = 0; i < list.size(); i++)//修改int类型防止超出int最大值溢出变为负数
	{
		User use = list[i];
		if (use.GetName() == name)
		{
			return use;
		}
	}
	return User();
}

vector<CarbonActivity*> FileTool::LoadCarbonActiveList(string name)
{
	ifstream file(name + "_activities.txt");
	string line;
	vector<CarbonActivity*> activelist;
	while (getline(file, line))
	{
		vector<string> token = OtherFun::spilt(line, '|');
		if (token.size() != 5) continue;
		string type = token[0];
		if (type == "交通")
		{
			string t = token[1];
			double dk = OtherFun::strtodb(token[2]);
			double c = OtherFun::strtodb(token[3]);
			string d = token[4];
			TransportActivity* active = new TransportActivity("", d, dk,t);
			active->setcarbonEmisson(c);
			activelist.push_back(active);
		}
		else if (type == "饮食")
		{
			string t = token[1];
			double wk = OtherFun::strtodb(token[2]);
			double c = OtherFun::strtodb(token[3]);
			string d = token[4];
			DietActivity* active = new DietActivity("", d, wk,t);
			active->setcarbonEmisson(c);
			activelist.push_back(active);
		}
		else if (type == "能源")
		{
			string t = token[1];
			double con = OtherFun::strtodb(token[2]);
			double c = OtherFun::strtodb(token[3]);
			string d = token[4];
			EnergyActivity* active = new EnergyActivity("", d, con,t);
			active->setcarbonEmisson(c);
			activelist.push_back(active);
		}
	}
	file.close();
	return activelist;
}

map< string, vector<CarbonActivity*> >FileTool::LoadAllCarbonActiveList()
{
	vector<User> userlist = LoadUserlist();
	map<string, vector<CarbonActivity*>> allActivities;
	for (User& user : userlist)
	{
		string name = user.GetName();
		vector<CarbonActivity*> activities = LoadCarbonActiveList(name);
		allActivities[name] = activities;
	}
	return allActivities;
}

// 保存每日碳排放总和
void FileTool::saveDailyEmissionSum(const std::string& username, const std::string& date, double sum) 
{
	std::string filename = username + "_daily_sums.txt";
	std::vector<std::pair<std::string, double>> sums;

	// 读取已有数据
	std::ifstream infile(filename);
	std::string line;
	while (std::getline(infile, line)) 
	{
		std::vector<std::string> parts = OtherFun::spilt(line, '|');
		if (parts.size() == 2) 
		{
			sums.emplace_back(parts[0], OtherFun::strtodb(parts[1]));
		}
	}
	infile.close();

	// 更新或添加新记录
	bool updated = false;
	for (auto& p : sums) 
	{
		if (p.first == date) 
		{
			p.second = sum;
			updated = true;
			break;
		}
	}
	if (!updated) {
		sums.emplace_back(date, sum);
	}

	std::ofstream outfile(filename);
	for (const auto& p : sums) 
	{
		outfile << p.first << "|" << p.second << std::endl;
	}
	outfile.close();
}

// 加载每日碳排放总和
double FileTool::loadDailyEmissionSum(const std::string& username, const std::string& date) 
{
	std::string filename = username + "_daily_sums.txt";
	std::ifstream infile(filename);
	if (!infile.is_open()) 
	{
		return -1.0; // 文件不存在
	}

	std::string line;
	while (std::getline(infile, line)) 
	{
		std::vector<std::string> parts = OtherFun::spilt(line, '|');
		if (parts.size() == 2 && parts[0] == date) 
		{
			infile.close();
			return OtherFun::strtodb(parts[1]);
		}
	}
	infile.close();
	return -1.0; // 未找到对应日期
}
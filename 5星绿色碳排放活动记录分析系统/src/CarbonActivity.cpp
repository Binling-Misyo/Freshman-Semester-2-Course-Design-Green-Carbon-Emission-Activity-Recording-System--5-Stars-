#include"../include/CarbonActivity.h"

string CarbonActivity::getname() const
{
	return name;
}
string CarbonActivity::getdate() const
{
	return date;
}
double CarbonActivity::getcarbonEmisson() const
{
	return carbonEmisson;
}
void CarbonActivity::setname(string n)
{
	name=n;
}
void CarbonActivity::setdate(string d)
{
	date=d;
}
void CarbonActivity::setcarbonEmisson(double c)
{
	carbonEmisson=c;
}

const map<string,double> TransportActivity::CarbonActive_yingzi={
	{"公交",0.1},
	{"汽油车",0.2},
	{"新能源车",0.15 }
};
double TransportActivity::calculateCarbon()
{
	return distance_km * CarbonActive_yingzi.at(type);
	return 0.0;
}
string TransportActivity::getActivityType() const
{
	return "交通";
}

const map<string, double> DietActivity::CarbonActive_yingzi = {
	{"牛肉", 60.0},
	{"蔬菜", 2.0},
	{"猪肉",30.0}
};
double DietActivity::calculateCarbon()
{
	return weight_kg * CarbonActive_yingzi.at(type);
	return 0.0;
}
string DietActivity::getActivityType() const
{
	return "饮食";
}

const map<string, double> EnergyActivity::CarbonActive_yingzi = {
	{"电", 0.5},
	{"天然气", 2.0},
	{"煤炭", 5.0}
};
double EnergyActivity::calculateCarbon()
{
	return consumption * CarbonActive_yingzi.at(type);
	return 0.0;
}
string EnergyActivity::getActivityType() const
{
	return "能源";
}

//保存新的碳活动记录 
//格式：活动类型|子类型|数值|碳排放量|日期
void TransportActivity::saveActivity(string username)
{
	ofstream file(username + "_activities.txt", ios::app);
	if (!file.is_open()) {
		cerr << "无法打开文件进行写入: " << username + "_activities.txt" << endl;
		return;
	}
	file << getActivityType() << "|";
	file << type << "|";
	file << distance_km << "|";
	file << getcarbonEmisson() << "|";
	file << getdate() << endl;
	file.close();
}
void DietActivity::saveActivity(string username)
{
	ofstream file(username + "_activities.txt", ios::app);
	if (!file.is_open()) {
		cerr << "无法打开文件进行写入: " << username + "_activities.txt" << endl;
		return;
	}
	file << getActivityType() << "|";
	file << type << "|";
	file << weight_kg << "|";
	file << getcarbonEmisson() << "|";
	file << getdate() << endl;
	file.close();
}
void EnergyActivity::saveActivity(string username)
{
	ofstream file(username + "_activities.txt", ios::app);
	if (!file.is_open()) {
		cerr << "无法打开文件进行写入: " << username + "_activities.txt" << endl;
		return;
	}
	file << getActivityType() << "|";
	file << type << "|";
	file << consumption << "|";
	file << getcarbonEmisson() << "|";
	file << getdate() << endl;
	file.close();
}

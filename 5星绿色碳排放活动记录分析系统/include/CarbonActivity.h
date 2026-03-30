#ifndef CARBONACTIVE_H 
#define CARBONACTIVE_H

#include <iostream>
#include <map>
#include<fstream>
using namespace std;

class CarbonActivity { //碳活动基类
private:
	string name;
	string date;
	double carbonEmisson = 0.0;//该活动碳排放总量 
public:
	CarbonActivity(string n = "", string d = "", double c = 0) :name(n), date(d), carbonEmisson(c) {}
	virtual ~CarbonActivity() {}

	virtual double calculateCarbon() = 0;//计算碳排放量 
	virtual string getActivityType() const = 0;//获取活动类型 
	//数据成员访问函数 
	string getname() const;
	string getdate() const;
	double getcarbonEmisson() const;
	//数据成员修改函数
	void setname(string n);
	void setdate(string d);
	void setcarbonEmisson(double c);
};
class TransportActivity:public CarbonActivity{//交通类碳排放活动 
private:
	double distance_km=0.0;
	string type;
public:
 	TransportActivity(string n="", string d="",double dk=0.0,string t="") : CarbonActivity(n, d), distance_km(dk), type(t) {}
 	~TransportActivity() {}
 	
	static const map<string, double> CarbonActive_yingzi;//碳排放因子表
 	
	double getDistance() const { return distance_km; }
	string getType() const { return type; }

	void setDistance(double dk) { distance_km = dk; }
	void setType(string t) { type = t; }

 	double calculateCarbon();//计算碳排放量 
	string getActivityType() const override;//获取活动类型 
	void saveActivity(string username);//单文件写入
};

class DietActivity:public CarbonActivity{//食物类碳排放活动 
private:
	double	weight_kg=0.0;
	string type;
public:
	DietActivity(string n="", string d="",double wk=0.0,string t="") : CarbonActivity(n, d),weight_kg(wk),type(t) {}
 	~DietActivity() {}
 	
	static const map<string, double> CarbonActive_yingzi;

	double getWeight() const { return weight_kg; }
	string getType() const { return type; }

	void setWeight(double wk) { weight_kg = wk; }
	void setType(string t) { type = t; }

	double calculateCarbon();//计算碳排放量 
	string getActivityType() const override;//获取活动类型 
	void saveActivity(string username);//单文件写入
};

class EnergyActivity:public CarbonActivity{//能源类碳排放活动 
private:
	double consumption=0.0;
	string type;
public:
	EnergyActivity(string n="", string d="",double c=0.0,string t="") : CarbonActivity(n, d), consumption(c),type(t) {}
 	~EnergyActivity() {}
 	
	double getConsumption() const { return consumption; }
	string getType() const { return type; }

	void setConsumption(double c) { consumption = c; }
	void setType(string t) { type = t; }

	static const map<string, double> CarbonActive_yingzi;

	double calculateCarbon();//计算碳排放量 
	string getActivityType() const override;//获取活动类型 
	void saveActivity(string username);//单文件写入
};
#endif
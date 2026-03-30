#include"./ReportGenerator.h"
#include"include/FileTool.h"
#include"include/CarbonActivity.h"
#include"include/ThisSystem.h"
#include"include/otherfun.h"
#include"date.h"
#include <algorithm>

double ReportGenerator::getTotalCarbon(User& user, string period) {
	double totalEmission = 0.0;
	vector<CarbonActivity*> activities = FileTool::LoadCarbonActiveList(user.GetName());
	string today = ThisSystem::getCurrentDate();
	if(period=="day")
	{
		for (const auto* activity : activities) 
		{
			if (activity->getdate() == today) 
			{
				totalEmission += activity->getcarbonEmisson();
			}
		}
	}
	else if(period=="week")
	{
		Date todayDate(today);
		Date weekAgoDate = todayDate - 7;
		for (const auto* activity : activities) 
		{
			Date activityDate(activity->getdate());
			if (activityDate >= weekAgoDate && activityDate <= todayDate) 
			{
				totalEmission += activity->getcarbonEmisson();
			}
		}
	}
	else if (period == "month")
	{
		string todaymonth = today.substr(0, 7);
		for (const auto* activity : activities)
		{
			string activitymonth = activity->getdate().substr(0,7);
			if(activitymonth==todaymonth)
			{
				totalEmission += activity->getcarbonEmisson();
			}
		}
	}
	// 释放内存
	for (auto* activity : activities) {
		delete activity;
	}
	return totalEmission;
}
void ReportGenerator::showCategoryReport(User& user)//分类（交通 / 饮食 / 能源）占比统计。
{
	double totalEmission = 0.0;
	double TransportEmission = 0.0;
	double DietEmission = 0.0;
	double EnergyEmission = 0.0;
	vector<CarbonActivity*> activities = FileTool::LoadCarbonActiveList(user.GetName());
	string today = ThisSystem::getCurrentDate();
	Date todayDate(today);
	Date weekAgoDate = todayDate - 7;
	for (const auto* activity : activities)
	{
		Date activityDate(activity->getdate());
		if (activityDate >= weekAgoDate && activityDate <= todayDate)
		{
			totalEmission += activity->getcarbonEmisson();
			if (activity->getActivityType() == "交通")
			{
				TransportEmission += activity->getcarbonEmisson();
			}
			else if (activity->getActivityType() == "饮食")
			{
				DietEmission += activity->getcarbonEmisson();
			}
			else if (activity->getActivityType() == "能源")
			{
				EnergyEmission += activity->getcarbonEmisson();
			}
		}
	}
	if(totalEmission==0)
	{
		cout << "本周无碳排放记录，无法生成分类报告。\n";
		return;
	}
	double t, d, e;
	t = (TransportEmission / totalEmission) * 100;
	d = (DietEmission / totalEmission) * 100;
	e = (EnergyEmission / totalEmission) * 100;
	cout << "本周碳排放分类占比：\n";
	cout << "    交通：" << t << "%\n";
	cout << "    饮食：" << d << "%\n";
	cout << "    能源：" << e << "%\n";
	// 个性化建议
	OtherFun::setColor(10);
	if (totalEmission <= user.GetGoal() * 5)
	{
		cout << "本周碳排放情况良好\n";
		OtherFun::setColor(15);
		return;
	}
	if (t >= d && t >= e) cout << "交通排放较大，建议多使用公共交通出行\n";
	if (d >= t && d >= e) cout << "饮食排放较大，建议多食用绿色有机蔬菜，减少肉类摄入\n";
	if (e >= t && e >= d) cout << "能源排放较大，建议减少不必要的电器使用，选择绿色能源\n";
	OtherFun::setColor(15);
	return;
}
bool ReportGenerator::checkTarget(User& user, double target)// 检查是否超过预设碳排目标（目标值存于用户文件）。
{
	return getTotalCarbon(user, "day") > target;
}
void ReportGenerator::showClassRanking()
{
    // 读取所有用户的碳活动
    map<string, vector<CarbonActivity*>> allActivities = FileTool::LoadAllCarbonActiveList();
    map<string, double> userDailyEmissions;
    string today = ThisSystem::getCurrentDate();

    // 统计每个用户今日总碳排放
    for (const auto& pair : allActivities) {
        const string& username = pair.first;
        const vector<CarbonActivity*>& activities = pair.second;
        double totalEmission = 0.0;
        for (const auto* activity : activities) {
            if (activity->getdate() == today) {
                totalEmission += activity->getcarbonEmisson();
            }
        }
        userDailyEmissions[username] = totalEmission;
    }

    // 排序：按碳排放量从低到高
    vector<pair<string, double>> ranking(userDailyEmissions.begin(), userDailyEmissions.end());
    sort(ranking.begin(), ranking.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
        return a.second < b.second;
    });
	//输出人均日碳排放
    double totalEmission = 0.0;
    for (const auto& item : userDailyEmissions) {
        totalEmission += item.second;
    }
    double averageEmission = 0.0;
    if (!userDailyEmissions.empty()) {
        averageEmission = totalEmission / userDailyEmissions.size();
    }
    cout << "班级人均日碳排放量：" << averageEmission << " kg" << endl;

    // 输出排名
    cout << "班级人均日碳排放排名：" << endl;
	int i = 1;
    for (const auto& item : ranking) {
		if (totalEmission != 0)
		{
			int n = (item.second / totalEmission) * 50;
			for (int i = n; i < 50; i++) cout << " ";
			OtherFun::setColor(10);
			for (int i = 0; i < n; i++) cout << "|";
			OtherFun::setColor(15);
		}
		cout << i++ << ". ";
		cout << item.first << " : " << item.second << " kg";
		cout << endl;
    }
	system("pause");
    // 释放内存
    for (auto& pair : allActivities) {
        for (auto* activity : pair.second) {
            delete activity;
        }
    }
}
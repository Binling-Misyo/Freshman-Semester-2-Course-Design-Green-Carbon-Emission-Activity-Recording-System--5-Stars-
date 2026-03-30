#include"../include/ThisSystem.h"
#include"../include/FileTool.h"
#include"../include/user.h"
#include"../include/CarbonActivity.h"
#include"../ReportGenerator.h"
#include"../date.h"

#include<ctime>
#include<vector>
#include<string>
#include<windows.h>
// ThisSystem 成员函数实现
void ThisSystem::pass()
{
	cout << "功能开发中....\n";
	system("pause");
}

bool ThisSystem::GUI(User& user)
{
	system("cls");
	cout << "------------ 主 菜 单 ------------\n\n";
	cout << "  [1]登录\n\n";
	cout << "  [2]注册\n\n";
	cout << "  [0]退出\n\n";
	cout << "----------------------------------\n\n";
	string cho = "0";
	cout << "请输入操作>>>>> ";
	cin >> cho;
	system("cls");
	if (cho == "1")//登录 
	{
		design(user);
		return false;
	}
	else if (cho == "2") //注册 
	{
		login();
		return true;
	}
	else if (cho == "0")
	{
		return false;
	}
	else
	{
		cout << "输入错误，请重新输入！！！\n";
		system("pause");
		return true;
	}
	return true;
}

string ThisSystem::getCurrentDate() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[11]; // 足够存放 YYYY-MM-DD 和结束符

	// 使用localtime_s替代localtime_r，适用于Windows环境
	if (localtime_s(&tstruct, &now) != 0) {
		cerr << "获取当前时间失败！\n";
		return "";
	}

	// 格式化日期：YYYY-MM-DD
	strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
	return string(buf);
}

void ThisSystem::login()
{
	string n, p;
	vector<User> list = FileTool::LoadUserlist();
	cout << "**********注册**********\n\n";
	cout << "用户名>>>";
	cin >> n;
	cout << "密码>>>";
	cin >> p;
	User use = FileTool::FindUser(list, n);
	if (use.GetName() != "")
	{
		cout << "用户名已存在，注册无效！！！\n";
		system("pause");
		return;
	}
	else
	{
		User newuser(n, p, getCurrentDate());
		list.push_back(newuser);
		FileTool::SaveUserlist(list);
		cout << "注册成功!!!";
		system("pause");
		return;
	}
}

void ThisSystem::design(User& user)
{
	string n, p;
	vector<User> list = FileTool::LoadUserlist();
	int count = 3;
	while (count--)
	{
		cout << "---------- 登 录 ----------\n\n";
		cout << "用户名>>>";
		cin >> n;
		cout << "密码>>>";
		cin >> p;
		User use = FileTool::FindUser(list, n);
		if (use.pwTF(p))
		{
			user = use;
			cout << "登录成功！！！\n";

			Sleep(1000);
			system("cls");
			return;
		}
		else cout << "账号或密码错误，请重新登录\n";
		system("pause");
		system("cls");
	}
	cout << "尝试次数过多！！！";
	return;
}

bool ThisSystem::recordNewActivity(User& user)
{
	string type, andtype;
	double value;
	cout << "请输入活动类型(交通/饮食/能源)>>>";
	cin >> type;
	if (type == "交通")
	{
		cout << "请输入交通方式(公交/汽油车/新能源车)>>>";
		cin >> andtype;
		if (andtype == "公交" || andtype == "汽油车"||andtype=="新能源车")
		{
			cout << "请输入行驶距离(km)>>>";
			cin >> value;
			double distance = value;
			TransportActivity* active = new TransportActivity("", getCurrentDate(), value, andtype);
			active->setcarbonEmisson(active->calculateCarbon());

			active->saveActivity(user.GetName());
			delete active;
		}
		else
		{
			cout << "输入错误，请重新输入！！！\n";
			system("pause");
			return true;
		}
	}
	else if (type == "饮食")
	{
		cout << "请输入食物类型(牛肉/蔬菜/猪肉)>>>";
		cin >> andtype;
		if (andtype == "牛肉" || andtype == "蔬菜"|| andtype=="猪肉")
		{
			cout << "请输入食物重量(kg)>>>";
			cin >> value;
			double weight = value;
			DietActivity* active = new DietActivity("", getCurrentDate(), value, andtype);
			active->setcarbonEmisson(active->calculateCarbon());

			active->saveActivity(user.GetName());
			delete active;
		}
		else
		{
			cout << "输入错误，请重新输入！！！\n";
			system("pause");
			return true;
		}
	}
	else if (type == "能源")
	{
		cout << "请输入能源类型(电/天然气/煤炭)>>>";
		cin >> andtype;
		if (andtype == "电" || andtype == "天然气"||andtype=="煤炭")
		{
			cout << "请输入能源消耗量(kWh)>>>";
			cin >> value;
			double consumption = value;
			EnergyActivity* active = new EnergyActivity("", getCurrentDate(), value, andtype);
			active->setcarbonEmisson(active->calculateCarbon());

			active->saveActivity(user.GetName());
			delete active;
		}
		else
		{
			cout << "输入错误，请重新输入！！！\n";
			system("pause");
			return true;
		}
	}
	else
	{
		cout << "输入错误，请重新输入";
	}
	return false;
}
//周报告显示函数
void ThisSystem::showWeeklyReport(User& user)
{
	cout << "本周碳排放总量：" << ReportGenerator::getTotalCarbon(user, "week") << " kg CO2\n";
	string today = getCurrentDate();
	Date todayDate(today);
	Date weekAgoDate = todayDate - 7;
	string startDate = weekAgoDate.toString();
	cout << "统计时间为：" << startDate << "-----"<<today<<endl;
	system("pause");
}
//月报告显示函数
void ThisSystem::showMonthlyReport(User& user)
{
	string tomonth = getCurrentDate().substr(0, 7);
	cout << "本月（"<<tomonth<<"）碳排放总量：" << ReportGenerator::getTotalCarbon(user, "month") << " kg CO2\n";
	system("pause");
}

void ThisSystem::changePassword(User& user)
{
	string oldpw, newpw;
	cout << "请输入旧密码>>>";
	cin >> oldpw;
	if (user.pwTF(oldpw))
	{
		cout << "请输入新密码>>>";
		cin >> newpw;
		user.setpassword(newpw);
		vector<User> list = FileTool::LoadUserlist();
		for (auto& u : list)
		{
			if (u.GetName() == user.GetName())
			{
				u.setpassword(newpw);
				break;
			}
		}
		FileTool::SaveUserlist(list);
		cout << "修改成功！！！\n";
		system("pause");
		return;
	}
	else
	{
		cout << "旧密码错误，修改失败！！！\n";
		system("pause");
		return;
	}
}

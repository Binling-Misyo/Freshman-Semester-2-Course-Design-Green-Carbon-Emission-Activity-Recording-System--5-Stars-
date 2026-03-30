#include "../include/otherfun.h"
#include "../include/user.h"
#include "../include/ThisSystem.h"
#include "../include/FileTool.h"
#include "../ReportGenerator.h"

#include <iostream>
using namespace std;

int main()
{
    User user;
    while (ThisSystem::GUI(user));
    while (true)
    {
        if (user.GetName() != "")
    {
	    system("cls");
        cout << "-------------------------------------------\n";
        cout << "-----欢迎 " << user.GetName() << "! 今日碳排放量: ";
        OtherFun::setColor(14);
        cout<<ReportGenerator::getTotalCarbon(user,"day");
        OtherFun::setColor(15);
		cout << " kg CO2-----\n\n"<< "当前日期: " << ThisSystem::getCurrentDate() << "\n";
        cout << "当前减排目标: ";
        OtherFun::setColor(14);
        cout << user.GetGoal();
        OtherFun::setColor(15);
        cout<< " kg CO2\n";
        if(ReportGenerator::checkTarget(user, user.GetGoal()))
        {
            OtherFun::setColor(12);
            cout << "!!!已超过今日减排目标，请注意控制碳排放量!!!\n";
			OtherFun::setColor(15);
		}
        else
        {
            OtherFun::setColor(10);
            cout << "今日碳排放量未超过目标，请继续保持！！！\n";
			OtherFun::setColor(15);
        }
        //个性化建议
		ReportGenerator::showCategoryReport(user);
        cout << "-------------------------------------------\n\n";
        cout << "   [1]记录新活动\n\n";
        cout << "   [2]查看周报告\n\n";
        cout << "   [3]查看月报告\n\n";
        cout << "   [4]设置减排目标\n\n";
        cout << "   [5]班级低碳排行榜\n\n";
		cout << "   [6]修改密码\n\n";
        cout << "   [0]退出登录\n\n";
		cout << "-------------------------------------------\n";
		cout << "请输入操作>>>";
        string choice;
        cin >> choice;
		system("cls");
        if (choice == "1")
        {
            while (ThisSystem::recordNewActivity(user));
        }
        else if (choice == "2")
        {
			ThisSystem::showWeeklyReport(user);
        }
        else if (choice == "3")
        {
			ThisSystem::showMonthlyReport(user);
        }
        else if (choice == "4")
        {
            double goal;
            cout << "请输入新的减排目标(kg CO2)>>>";
            cin >> goal;
            if (goal < 0)
            {
                cout << "减排目标不能为负数，请重新输入！！！\n";
                system("pause");
                continue;
            }
            user.setgoal(goal);
            // 修正：同步更新到用户列表并保存
            vector<User> userlist = FileTool::LoadUserlist();
            for (auto& u : userlist) {
                if (u.GetName() == user.GetName()) {
                    u.setgoal(goal);
                    break;
                }
            }
            FileTool::SaveUserlist(userlist);
        }
        else if (choice == "5")
        {
			ReportGenerator::showClassRanking();
        }
        else if (choice == "0")
        {
            cout << "已退出登录，欢迎下次使用！！！\n";
            system("pause");
            break;
        }
        else if (choice == "6")
        {
            ThisSystem::changePassword(user);
        }
        else
        {
            cout << "输入错误，请重新输入！！！\n";
            system("pause");
		}
    }
    }
    return 0;
}

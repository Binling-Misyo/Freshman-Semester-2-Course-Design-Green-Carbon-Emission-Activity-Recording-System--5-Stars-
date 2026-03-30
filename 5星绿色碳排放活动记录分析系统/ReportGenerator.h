#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H
#include "include/user.h"
#include <iostream>

class ReportGenerator {
public:
	static double getTotalCarbon(User& user, string period);//按日 / 周 /月统计总碳排放。
	static void showCategoryReport(User& user);//分类一周的（交通 / 饮食 / 能源）占比统计。同时给出个性化建议。
	static bool checkTarget(User& user, double target);// 检查是否超过预设碳排目标（目标值存于用户文件）。
	static void showClassRanking();// 读取所有用户文件，计算人均日碳排放，输出班级排名（体现集体责任感）。
};
#endif
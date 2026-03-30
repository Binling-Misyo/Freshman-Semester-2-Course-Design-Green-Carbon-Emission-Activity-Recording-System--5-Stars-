#ifndef DATE_H
#define DATE_H
#include <cstdio>
#include<string>
class Date {
public:
	int year;//年
	int month;//月
	int day;//日
	// 构造函数
	Date(int y = 0, int m = 0, int d = 0) : year(y), month(m), day(d) {}
	// 从字符串解析日期，格式为 "YYYY-MM-DD"
	Date(const std::string& dateStr) {
		sscanf_s(dateStr.c_str(), "%d-%d-%d", &year, &month, &day);
	}
	// 将日期转换为字符串，格式为 "YYYY-MM-DD"
	std::string toString() const {
		char buffer[11];
		sprintf_s(buffer, sizeof(buffer), "%04d-%02d-%02d", year, month, day);
		return std::string(buffer);
	}
	//闰年判断
	bool isLeapYear(int year) const {
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}
	// 获取某年某月的天数
	int daysInMonth(int year, int month) const {
		static const int daysPerMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (month == 2 && isLeapYear(year)) return 29;
		return daysPerMonth[month - 1];
	}
	// 重载减法运算符，返回减去指定天数后的新日期
	Date operator-(int days) const {
		Date result = *this;
		result.day -= days;
		while (result.day <= 0) {
			result.month--;
			if (result.month <= 0) {
				result.month = 12;
				result.year--;
			}
			result.day += daysInMonth(result.year, result.month);
		}
		return result;
	}
	// 重载大于等于运算符
	bool operator>=(const Date& other) const {
		if (year != other.year) return year > other.year;
		if (month != other.month) return month > other.month;
		return day >= other.day;
	}
	// 重载小于等于运算符
	bool operator<=(const Date& other) const {
		if (year != other.year) return year < other.year;
		if (month != other.month) return month < other.month;
		return day <= other.day;
	}
};
#endif


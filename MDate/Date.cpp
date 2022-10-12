/**
* Hier ist der Quellcode für die eingebundene Headerdatei namens 
* "MDdate.h"
*/

#include <iostream>
#include <chrono>
#include "boost/lexical_cast.hpp"
#include "MDate.h"
#include <functional>

using namespace std::chrono;

using Clock = std::chrono::system_clock;
using Ms = std::chrono::milliseconds;
using Sec = std::chrono::seconds;

typedef std::numeric_limits<double> dbl;

Date* Date_Class;

Date::Date()
{
    time_point now = Clock::now();
    auto duration = now.time_since_epoch();
    auto now_ms = duration_cast<milliseconds>(duration);
    this->ms = now_ms.count();

    this->Evaluate_Units();
    this->German_GMT();
}
Date::Date(int y, int m, int d, int h, int min, int s) {
    this->Set_Year(y);
    this->Set_Month(m);
    this->Set_MonthDay(d);
    this->Set_Hour(h);
    this->Set_Minute(min);
    this->Set_Second(s);

    this->EvaluateStaticDate();
}
void Date::German_GMT() {
    int gmt = 0;
    int weekday = NULL;
    int d = this->month_days[2];
    while (weekday != 0) {
        weekday = this->Evaluate_weekday(d, 2, this->year);
        d--;
    }
    int day1_month = d;

    weekday = NULL;
    d = this->month_days[9];
    while (weekday != 0) {
        weekday = this->Evaluate_weekday(d, 9, this->year);
        d--;
    }
    int day2_month = d;


    if (this->month > 2 && this->month < 9) {
        gmt = 2;
    }
    if (this->month < 2 || this->month > 9) {
        gmt = 1;
    }
    if (this->month == 2) {
        if (this->day_month >= day1_month) gmt = 2;
        else gmt = 1;
    }
    if (this->month == 9) {
        if (this->day_month >= day2_month) gmt = 1;
        else gmt = 2;
    }

    this->Set_Hour(this->hour + gmt);
}
std::string Date::Ms_Str() {
    return boost::lexical_cast<std::string>(ms);
}
void Date::Print_Date() {
    std::string weekday_str = this->de_weekday_string[this->weekday];
    printf("%s, der %02d.%02d.%d und die Uhrzeit betraegt: %02d:%02d:%02d\n", weekday_str.c_str(), this->day_month, this->month + 1, this->year, this->hour, this->minute, this->second);
}

// Getter Section
std::string Date::Get_Date() {
    std::string n_str = std::format("{:0>2d}-{:0>2d}-{:0>2d}T{:0>2d}:{:0>2d}:{:0>2d}", this->year, this->month + 1, this->day_month, this->hour, this->minute, this->second);
    return n_str;
}
int Date::Get_Year() { return this->year; }
int Date::Get_Month() { return this->month; }
int Date::Get_MonthDay() { return this->day_month; }
int Date::Get_Hour() { return this->hour; }
int Date::Get_Minute() { return this->minute; }
int Date::Get_Second() { return this->second; }
int Date::Get_Week_of_year() { return this->week_of_year; }
int Date::Get_Weekday() { return this->weekday; }
uint64_t Date::Get_Milliseconds() { return this->ms; }

// Setter Section
void Date::Set_Year(int in_year) {
    this->year = in_year;
    if ((year % 4) == 0) this->leapyear = true;
    if (this->leapyear) this->month_days[1] = 29;

    this->EvaluateStaticDate();
}
void Date::Set_Month(int in_month) {
    if (in_month < 0) {
        this->Set_Year(this->year - 1);
        this->Set_Month(12 - std::fabs(in_month));
    }
    else if (in_month > 11) {
        this->Set_Year(this->year + 1);
        this->Set_Month(in_month - 12);
    }
    else {
        this->month = in_month;
        this->EvaluateStaticDate();
        if (this->day_month > this->month_days[this->month]) this->day_month = this->month_days[this->month];
    }
}

void Date::Set_MonthDay(int in_day_month) {
    if (in_day_month < 1) {
        this->Set_Month(this->month - 1);
        this->Set_MonthDay(this->month_days[this->month] - std::fabs(in_day_month));
    }
    else if (in_day_month > this->month_days[this->month]) {
        this->Set_MonthDay(in_day_month - this->month_days[this->month]);
        this->Set_Month(this->month + 1);
    }
    else {
        this->day_month = in_day_month;
        this->EvaluateStaticDate();
    }
}

void Forward_Set_MonthDay(void* context, int i0) { static_cast<Date*>(context)->Set_MonthDay(i0); }

void Date::Set_Hour(int in_hour) {
    this->Time_Deviation(in_hour, 0, 24, this->hour, this->day_month, &Forward_Set_MonthDay, this);
    this->Evaluate_Milliseconds();
}

void Forward_Set_Hour(void* context, int i0) { static_cast<Date*>(context)->Set_Hour(i0); }

void Date::Set_Minute(int in_minute) {
    this->Time_Deviation(in_minute, 0, 60, this->minute, this->hour, &Forward_Set_Hour, this);
    this->Evaluate_Milliseconds();
}

void Forward_Set_Minute(void* context, int i0) { static_cast<Date*>(context)->Set_Minute(i0); }

void Date::Set_Second(int in_second) {
    this->Time_Deviation(in_second, 0, 60, this->second, this->minute, &Forward_Set_Minute, this);
    this->Evaluate_Milliseconds();
}

void Date::Set_Milliseconds(uint64_t milliseconds) {
    this->ms = milliseconds;
    this->Evaluate_Units();
}

void Date::Time_Deviation(int input, int min_value, int max_value, int& time_attr, int& next_time_attr, void(*next_func)(void*, int), void* context) {
    if (input < min_value) {
        int tmp = time_attr - std::fabs(input);
        while (tmp < min_value) {
            next_func(context, next_time_attr - 1);
            tmp = max_value - std::fabs(tmp);
        }
        time_attr = tmp;
    }
    if (input >= max_value) {
        int tmp = input - max_value;
        next_func(context, next_time_attr + 1);
        while (tmp >= max_value) {
            next_func(context, next_time_attr + 1);
            tmp = tmp - max_value;
        }
        time_attr = tmp;
    }
    if (input < max_value && input >= min_value) {
        time_attr = input;
    }
}

int Date::Evaluate_weekday(int d, int m, int y) {
    // Change to julian calendar
    if (m == 0 || m == 1) {
        y -= 1;
    }
    if (m == 0) {
        m = 11;
    }
    else if (m == 1) {
        m = 12;
    }
    else {
        m -= 1;
    }

    // Use the formula to calculate the weekday, 0 = Sunday, 6 = Saturday
    int mod_y = y % 100;
    int mod_c = y - mod_y;
    mod_c = mod_c / 100;

    int formula1 = (d + std::floor(2.6 * m - 0.2) + mod_y + std::floor(mod_y / 4) + std::floor(mod_c / 4) - 2 * mod_c);
    int formula = formula1 % 7;
    return formula;
}

void Date::Month_Day_Increment() {
    this->Set_MonthDay(this->day_month + 1);
}

void Date::Month_Day_Decrement() {
    this->Set_MonthDay(this->day_month - 1);
}

int Date::Find_first_weekday() {
    int i = 1;
    int weekday = this->Evaluate_weekday(i, 0, this->year);
    while (weekday > 3 && weekday < 1) {
        weekday = this->Evaluate_weekday(i, 0, this->year);
        i++;
    }
    return i;
}

int Date::Evaluate_week_of_year() {
    int first_weekday = this->Find_first_weekday();
    int weekdays = this->day - (first_weekday - 1);
    this->week_of_year = (weekdays / 7) + 1;
    return this->week_of_year;
}

void Date::Evaluate_Units() {
    double ms_year = ((1000 * 3600 * 24) * 365.25);
    double year_day = (365.25);
    double day_hour = (24);
    double hour_minute = (60);
    double minute_sec = (60);


    double years = this->ms / ms_year;

    year = std::floor(years);
    double rem = years - year;
    year += TIMESTAMP_FROM;

    if ((year % 4) == 0) leapyear = true;
    else leapyear = false;

    if (leapyear) month_days[1] = 29;

    double days = rem * year_day;
    this->day = std::ceil(days);
    rem = days - std::floor(days);

    double hours = rem * day_hour;
    hour = std::floor(hours);
    rem = hours - hour;

    double minutes = rem * hour_minute;
    minute = std::floor(minutes);
    rem = minutes - minute;

    double seconds = rem * minute_sec;
    second = std::floor(seconds);
    rem = seconds - second;

    // Evaluate months and day in month
    int months = 0;
    int day_in_month = 0;
    int tmp = this->day;
    for (int i = 0; i < month_days.size(); i++) {
        if (tmp < this->month_days[i] + 1) {
            day_in_month = tmp;
            break;
        }
        else {
            tmp -= month_days[i];
            day_in_month = tmp;
            months++;
        }
    }
    this->day_month = day_in_month;
    this->month = months;

    this->weekday = this->Evaluate_weekday(this->day_month, this->month, this->year);
    this->Evaluate_week_of_year();
}

void Date::Evaluate_DayInYear() {
    int days = 0;
    for (int i = 0; i < this->month; i++) {
        days += this->month_days[i];
    }
    days += this->day_month;
    this->day = days;
}

void Date::Evaluate_Milliseconds() {
    uint64_t milliseconds = 0;
    int years = this->year - this->TIMESTAMP_FROM;
    milliseconds += static_cast<unsigned long long>(years) * 1000 * 3600 * 24 * 365.25;
    milliseconds += static_cast<unsigned long long>(this->day - 1) * 1000 * 3600 * 24;
    milliseconds += static_cast<unsigned long long>(this->hour) * 1000 * 3600;
    milliseconds += static_cast<unsigned long long>(this->minute) * 1000 * 60;
    milliseconds += static_cast<unsigned long long>(this->second) * 1000;
    this->ms = milliseconds;
}

void Date::EvaluateStaticDate() {
    this->Evaluate_DayInYear();
    this->weekday = this->Evaluate_weekday(this->day_month, this->month, this->year);
    this->Evaluate_week_of_year();
    this->Evaluate_Milliseconds();
}
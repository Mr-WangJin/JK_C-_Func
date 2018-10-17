/**
 * JKChineseDate.cpp
 * @Author   Tu Yongce <yongce@126.com>
 * @Created  2008-12-13 
 * @Modified 2008-12-13   
 * @Version  0.1
 */

#include "JKChineseDate.h"
#include "JKChineseCalendarDB.h"
#include "JKSolarDate.h"


// 判断是否为有效日期
bool JKChineseDate::IsValidDate() const
{
    if (m_year < 1901 || m_year > 2050)
        return false;
    
    if (m_month < 1 || m_month > JKChineseCalendarDB::GetYearMonths(m_year))
        return false;
    
    if (m_day < 1 || m_day > JKChineseCalendarDB::GetMonthDays(m_year, m_month))
        return false; 
    
    return true;
}

// 计算当前日期是该年的第几天
int JKChineseDate::YearDay() const
{
    int days = 0;
    
    for (int i = 1; i < m_month; ++i)
        days += JKChineseCalendarDB::GetMonthDays(m_year, i);
    days += m_day;
    
    return days;
}

// 计算*this和ref之间相差的天数，要求ref.IsPrior(*this)为真
int JKChineseDate::DoDiff(const JKChineseDate &ref) const
{
    assert(!IsPrior(ref));  // *this >= ref
    
    int days = 0;
    
    // 首先计算两个年份的1月1日相差的天数
    for (int year = ref.m_year; year < m_year; ++year) {
        days += JKChineseCalendarDB::GetYearDays(year);
    }
    
    // 处理月和日
    days += YearDay();
    days -= ref.YearDay();
    
    return days;
}

// 从该年的某天计算日期
// 如果无对应日期，则操作失败并返回false；否则返回true
bool JKChineseDate::FromYearDay(int days)
{
    if (days < 1 && days > JKChineseCalendarDB::GetYearDays(m_year))
        return false;
    
    m_month = 1;
    int monthDay = JKChineseCalendarDB::GetMonthDays(m_year, m_month);
    
    while (days > monthDay) {
        days -= monthDay;
        ++m_month;
        monthDay = JKChineseCalendarDB::GetMonthDays(m_year, m_month);
    }
    
    m_day = days;
    
    assert(IsValidDate());  // 当JKChineseDate对象内部数据变化时确保仍是正确的日期
    return true;
}


// 向前（未来）调整指定天数（注意：不能调整到农历2050年12月30日之后）
// 如果调整成功，则返回true；否则返回false（此时*this在调用前后不会发生改变）
bool JKChineseDate::DoAdjustForward(int days)
{
    assert(days > 0);
    if (JKChineseDate(2050, 12, 30).DoDiff(*this) < days)
        return false;  // 不能调整到农历2050年12月30日之后
    
    // 以每年最后一天为参考点进行计算
    days += YearDay();
    int yearDays = JKChineseCalendarDB::GetYearDays(m_year);
    
    while (days > yearDays) {
        days -= yearDays;
        ++m_year;
        yearDays = JKChineseCalendarDB::GetYearDays(m_year);
    }
    
    FromYearDay(days);
    
    return true;
}

// 向后（过去）调整指定天数（注意：不能调整到农历1901年1月1日之前）
// 如果调整成功，则返回true；否则返回false（此时*this在调用前后不会发生改变）
bool JKChineseDate::DoAdjustBackward(int days)
{
    assert(days > 0);
    if (this->DoDiff(JKChineseDate(1901, 1, 1)) < days)
        return false;  // 不能调整时间到农历1901年1月1日之前
    
    // 以每年第一天（1月1日）为参考点进行计算
    int yearDays = JKChineseCalendarDB::GetYearDays(m_year);
    days += yearDays - YearDay();
    
    while (days > yearDays) {
        days -= yearDays;
        --m_year;
        yearDays = JKChineseCalendarDB::GetYearDays(m_year);
    }
    
    FromYearDay(yearDays - days);
    
    return true;
}

// 转换为阳历
SolarDate JKChineseDate::ToSolarDate() const
{
    // 参考日期：农历2000年1月1日就是公元2000年2月5日
    JKChineseDate refDay(2000, 1, 1);
    
    // 计算出当前日期与参考日期之间的天数
    int days = this->Diff(refDay);
    
    SolarDate tmp(2000, 2, 5);
    tmp.AdjustDays(days);
    assert(tmp.Diff(SolarDate(2000, 2, 5)) == days);
    
    return tmp;
}

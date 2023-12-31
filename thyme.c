/*
MIT License

Copyright (c) 2023 ignurof

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <time.h>
#include "thyme.h"

//  2023
//  JANUARY = 31,
//	FEBRUARY = 28,
//	MARCH = 31,
//	APRIL = 30,
//	MAY = 31,
//	JUNE = 30,
//	JULY = 31,
//	AUGUST = 31,
//	SEPTEMBER = 30,
//	OCTOBER = 31,
//	NOVEMBER = 30,
//	DECEMBER = 31

enum {
	JANUARY = 0,
	FEBRUARY = 1,
	MARCH = 2,
	APRIL = 3,
	MAY = 4,
	JUNE = 5,
	JULY = 6,
	AUGUST = 7,
	SEPTEMBER = 8,
	OCTOBER = 9,
	NOVEMBER = 10,
	DECEMBER = 11
};

struct converted_time_t get_converted_time(void)
{
	// How to use time:
	// man mktime, man difftime
	time_t time_result = time(NULL);

	struct converted_time_t converted_time;
	converted_time.year = -1;
	converted_time.month = -1;
	converted_time.day_in_month = -1;
	converted_time.week_day = -1;
	converted_time.day_in_year = -1;
	converted_time.hour = -1;
	converted_time.min = -1;
	converted_time.sec = -1;

	if(time_result != (time_t)(-1))
	{
		struct tm time_struct = *localtime(&time_result);

		converted_time.year = 1900 + time_struct.tm_year;
		converted_time.month = 1 + time_struct.tm_mon;
		converted_time.day_in_month = time_struct.tm_mday;
		converted_time.week_day = time_struct.tm_wday;
		converted_time.day_in_year = time_struct.tm_yday;
		converted_time.hour = time_struct.tm_hour;
		converted_time.min = time_struct.tm_min;
		converted_time.sec = time_struct.tm_sec;
	}

	return converted_time;
}

// TODO: Rip out current day calculations into their own function
struct time_since_date_t get_time_since_date(struct date_time_input_t date_time_input)
{
	struct converted_time_t converted_time = get_converted_time();

	struct time_since_date_t time_since_date;
	time_since_date.years_since_date = 0;
	time_since_date.months_since_date = 0;
	time_since_date.weeks_since_date = 0;
	time_since_date.days_since_date = 0;
	time_since_date.hours_since_date = 0;
	time_since_date.minutes_since_date = 0;
	time_since_date.seconds_since_date = 0;
	time_since_date.current_month_date_count = 0;
	time_since_date.current_day_date_count = 0;
	time_since_date.current_hour_date_count = 0;
	time_since_date.current_minute_date_count = 0;
	time_since_date.current_second_date_count = 0;

	time_since_date.years_since_date = converted_time.year - date_time_input.year_start;

	// current_x_date_count details the current months of the year, or days of the month
	time_since_date.current_month_date_count = converted_time.month - date_time_input.month_start;
	// if age has not reached the birth month yet, convert year and month correctly
	// ie: 28 years -2 months -> 27 years 10 months
	if(time_since_date.current_month_date_count < 0)
	{
		int x = 12;
		x += time_since_date.current_month_date_count;
		time_since_date.current_month_date_count = x;
		time_since_date.years_since_date -= 1;
	}

	time_since_date.current_day_date_count = converted_time.day_in_month - date_time_input.day_start;
	int iterate_year_date = date_time_input.year_start;
	int i;
	for(i = 0; i < time_since_date.years_since_date; i++)
	{
		if(iterate_year_date % 4 == 0)
		{
			time_since_date.days_since_date += 366;
		}
		else
		{
			time_since_date.days_since_date += 365;
		}

		iterate_year_date += 1;
	}

	// avoid case where the day_date is not yet reached
	// so we need to adjust the month and days
	if(time_since_date.current_day_date_count < 0)
	{
		time_since_date.current_month_date_count -= 1;
		// here we need to make sure month index is back to 0
		// then account for the previous month not current month
		switch(converted_time.month - 1)
		{
			case JANUARY:
				// DECEMBER 
				time_since_date.current_day_date_count = 31 + time_since_date.current_day_date_count;
				break;
			case FEBRUARY:
				// JANUARY
				time_since_date.current_day_date_count = 31 + time_since_date.current_day_date_count;
				break;
			case MARCH:
				// FEBRUARY
				time_since_date.current_day_date_count = 28 + time_since_date.current_day_date_count;
				if(date_time_input.year_start % 4 == 0) // leap year
					time_since_date.current_day_date_count += 1;
				break;
			case APRIL:
				// MARCH
				time_since_date.current_day_date_count = 31 + time_since_date.current_day_date_count;
				break;
			case MAY:
				// APRIL
				time_since_date.current_day_date_count = 30 + time_since_date.current_day_date_count;
				break;
			case JUNE:
				// MAY
				time_since_date.current_day_date_count = 31 + time_since_date.current_day_date_count;
				break;
			case JULY:
				// JUNE
				time_since_date.current_day_date_count = 30 + time_since_date.current_day_date_count;
				break;
			case AUGUST:
				// JULY
				time_since_date.current_day_date_count = 31 + time_since_date.current_day_date_count;
				break;
			case SEPTEMBER:
				// AUGUST
				time_since_date.current_day_date_count = 31 + time_since_date.current_day_date_count;
				break;
			case OCTOBER:
				// SEPTEMBER
				time_since_date.current_day_date_count = 30 + time_since_date.current_day_date_count;
				break;
			case NOVEMBER:
				// OCTOBER
				time_since_date.current_day_date_count = 31 + time_since_date.current_day_date_count;
				break;
			case DECEMBER:
				// NOVEMBER
				time_since_date.current_day_date_count = 30 + time_since_date.current_day_date_count;
				break;
		}
	}

	time_since_date.current_hour_date_count = converted_time.hour - date_time_input.hour_start;
	if(time_since_date.current_hour_date_count < 0)
	{
		time_since_date.current_hour_date_count = 24 + time_since_date.current_hour_date_count;
		time_since_date.current_day_date_count -= 1;
	}

	time_since_date.current_minute_date_count = converted_time.min - date_time_input.minute_start;
	if(time_since_date.current_minute_date_count < 0)
	{
		time_since_date.current_minute_date_count = 60 + time_since_date.current_minute_date_count;
		time_since_date.current_hour_date_count -= 1;
	}

	time_since_date.current_second_date_count = converted_time.sec - date_time_input.second_start;
	if(time_since_date.current_second_date_count < 0)
	{
		time_since_date.current_second_date_count = 60 + time_since_date.current_second_date_count;
		time_since_date.current_minute_date_count -= 1;
	}

	time_since_date.months_since_date = time_since_date.years_since_date * 12 + time_since_date.current_month_date_count;

	time_since_date.days_since_date = time_since_date.current_day_date_count + time_since_date.days_since_date;

	// calculcate correct days since date
	if(time_since_date.years_since_date == 0)
	{
		time_since_date.days_since_date = 0;
		int j;
		for(j = 0; j < time_since_date.current_month_date_count; j++)
		{
			switch(j)
			{
				case JANUARY:
					time_since_date.days_since_date += 31;
					break;
				case FEBRUARY:
					time_since_date.days_since_date += 28;
					if(date_time_input.year_start % 4 == 0) // leap year
						time_since_date.days_since_date += 1;
					break;
				case MARCH:
					time_since_date.days_since_date += 31;
					break;
				case APRIL:
					time_since_date.days_since_date += 30;
					break;
				case MAY:
					time_since_date.days_since_date += 31;
					break;
				case JUNE:
					time_since_date.days_since_date += 30;
					break;
				case JULY:
					time_since_date.days_since_date += 31;
					break;
				case AUGUST:
					time_since_date.days_since_date += 31;
					break;
				case SEPTEMBER:
					time_since_date.days_since_date += 30;
					break;
				case OCTOBER:
					time_since_date.days_since_date += 31;
					break;
				case NOVEMBER:
					time_since_date.days_since_date += 30;
					break;
				case DECEMBER:
					time_since_date.days_since_date += 31;
					break;
			}
		}

		time_since_date.days_since_date += time_since_date.current_day_date_count;
	}

	time_since_date.weeks_since_date = time_since_date.days_since_date / 7;
	time_since_date.hours_since_date = time_since_date.days_since_date * 24 - 24 + converted_time.hour;
	// account for the hours on the day of the start date
	time_since_date.hours_since_date += 24 - date_time_input.hour_start;

	time_since_date.minutes_since_date = time_since_date.hours_since_date * 60;
	time_since_date.minutes_since_date += converted_time.min - date_time_input.minute_start;
	if(converted_time.min - date_time_input.minute_start < 0)
	{
		// if the hour is not reached yet make sure to account for that
		time_since_date.hours_since_date -= 1;
	}

	time_since_date.seconds_since_date = time_since_date.minutes_since_date * 60 + converted_time.sec;

	return time_since_date;
}

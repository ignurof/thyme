#include <stdio.h>
#include <time.h>

// DEBUG
int year_date = 2023;
int month_date = 1;
int day_date = 5;
int hour_date = 9;
int minute_date = 42;
int second_date = 0;
// DEBUG

// We need the struct definition here so it can be used wherever the header is #included
struct ct
{
	int year;
	int month;
	int day_in_month;
	int hour;
	int min;
	int sec;
	int week_day;
	int day_in_year;
};

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

struct ct get_converted_time(void)
{
	// How to use time:
	// man mktime, man difftime
	time_t time_result = time(NULL);

	struct ct converted_time;
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

struct tsd {
	int years_since_date;
	int months_since_date;
	int weeks_since_date;
	int days_since_date;
	int hours_since_date;
	int minutes_since_date;
	int seconds_since_date;
};

struct tsd get_time_since_date(void)
{
	struct ct converted_time = get_converted_time();
	
	struct tsd time_since_date;
	time_since_date.years_since_date = 0;
	time_since_date.months_since_date = 0;
	time_since_date.weeks_since_date = 0;
	time_since_date.days_since_date = 0;
	time_since_date.hours_since_date = 0;
	time_since_date.minutes_since_date = 0;
	time_since_date.seconds_since_date = 0;

	time_since_date.years_since_date = converted_time.year - year_date;

	// current_x_date_count details the current months of the year, or days of the month
	int current_month_date_count = converted_time.month - month_date;
	// if age has not reached the birth month yet, convert year and month correctly
	// ie: 28 years -2 months -> 27 years 10 months
	if(current_month_date_count < 0)
	{
		int x = 12;
		x += current_month_date_count;
		current_month_date_count = x;
		time_since_date.years_since_date -= 1;
	}

	int current_day_date_count = converted_time.day_in_month - day_date;
	int iterate_year_date = year_date;
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
	if(current_day_date_count < 0)
	{
		current_month_date_count -= 1;
		// here we need to make sure month index is back to 0
		// then account for the previous month not current month
		switch(converted_time.month - 1)
		{
			case JANUARY:
				// DECEMBER 
				current_day_date_count = 31 + current_day_date_count;
				break;
			case FEBRUARY:
				// JANUARY
				current_day_date_count = 31 + current_day_date_count;
				break;
			case MARCH:
				// FEBRUARY
				current_day_date_count = 28 + current_day_date_count;
				if(year_date % 4 == 0) // leap year
					current_day_date_count += 1;
				break;
			case APRIL:
				// MARCH
				current_day_date_count = 31 + current_day_date_count;
				break;
			case MAY:
				// APRIL
				current_day_date_count = 30 + current_day_date_count;
				break;
			case JUNE:
				// MAY
				current_day_date_count = 31 + current_day_date_count;
				break;
			case JULY:
				// JUNE
				current_day_date_count = 30 + current_day_date_count;
				break;
			case AUGUST:
				// JULY
				current_day_date_count = 31 + current_day_date_count;
				break;
			case SEPTEMBER:
				// AUGUST
				current_day_date_count = 31 + current_day_date_count;
				break;
			case OCTOBER:
				// SEPTEMBER
				current_day_date_count = 30 + current_day_date_count;
				break;
			case NOVEMBER:
				// OCTOBER
				current_day_date_count = 31 + current_day_date_count;
				break;
			case DECEMBER:
				// NOVEMBER
				current_day_date_count = 30 + current_day_date_count;
				break;
		}
	}

	int current_hour_date_count = converted_time.hour - hour_date;
	if(current_hour_date_count < 0)
	{
		current_hour_date_count = 24 + current_hour_date_count;
		current_day_date_count -= 1;
	}

	int current_minute_date_count = converted_time.min - minute_date;
	if(current_minute_date_count < 0)
	{
		current_minute_date_count = 60 + current_minute_date_count;
		current_hour_date_count -= 1;
	}

	int current_second_date_count = converted_time.sec - second_date;
	if(current_second_date_count < 0)
	{
		current_second_date_count = 60 + current_second_date_count;
		current_minute_date_count -= 1;
	}

	time_since_date.months_since_date = time_since_date.years_since_date * 12 + current_month_date_count;

	time_since_date.days_since_date = current_day_date_count + time_since_date.days_since_date;

	// calculcate correct days since date
	if(time_since_date.years_since_date == 0)
	{
		time_since_date.days_since_date = 0;
		int j;
		for(j = 0; j < current_month_date_count; j++)
		{
			switch(j)
			{
				case JANUARY:
					time_since_date.days_since_date += 31;
					break;
				case FEBRUARY:
					time_since_date.days_since_date += 28;
					if(year_date % 4 == 0) // leap year
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

		time_since_date.days_since_date += current_day_date_count;
	}

	time_since_date.weeks_since_date = time_since_date.days_since_date / 7;
	time_since_date.hours_since_date = time_since_date.days_since_date * 24 - 24 + converted_time.hour;
	// account for the hours on the day of the start date
	time_since_date.hours_since_date += 24 - hour_date;

	time_since_date.minutes_since_date = time_since_date.hours_since_date * 60;
	time_since_date.minutes_since_date += converted_time.min - minute_date;
	if(converted_time.min - minute_date < 0)
	{
		// if the hour is not reached yet make sure to account for that
		time_since_date.hours_since_date -= 1;
	}

	 time_since_date.seconds_since_date = time_since_date.minutes_since_date * 60 + converted_time.sec;

	 return time_since_date;
}

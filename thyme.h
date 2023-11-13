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

struct tsd {
	int years_since_date;
	int months_since_date;
	int weeks_since_date;
	int days_since_date;
	int hours_since_date;
	int minutes_since_date;
	int seconds_since_date;
	int current_month_date_count;
	int current_day_date_count;
	int current_hour_date_count;
	int current_minute_date_count;
	int current_second_date_count;
};

struct ct get_converted_time(void);
struct tsd get_time_since_date(void);

void example_debug(struct ct);
void example_print(struct tsd);

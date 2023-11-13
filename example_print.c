#include <stdio.h>
#include "thyme.h"

int main(void)
{
	struct dti date_time_input;
	date_time_input.year_start = 1990;
	date_time_input.month_start = 1;
	date_time_input.day_start = 3;
	date_time_input.hour_start = 23;
	date_time_input.minute_start = 59;
	date_time_input.second_start = 0;

	struct tsd date_time_output = get_time_since_date(date_time_input);

	printf("%i years since date.\n", date_time_output.years_since_date);

	return 0;
}

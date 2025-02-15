#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int isleap(int year)
{
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
	int i, leap;

	leap = isleap(year);
	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int* pmonth, int* pday)
{
	int i, leap;

	leap = isleap(year);
	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}

/* month_name: return name of n-th month */
char* month_name(int n)
{
	static char* names[] = {
		"Illegal",
		"January", "February", "March",
		"April", "May", "June",
		"July", "August", "September",
		"October", "November", "December"
	};

	return n < 1 || n > 12 ? names[0] : names[n];
}

main()
{
	int nmonth, nday;
	int day = day_of_year(2023, 5, 19);
	month_day(2023, day, &nmonth, &nday);
	printf("day_of_year: %d\n", day);
	printf("month_day: %d %d\n", nmonth, nday);
}

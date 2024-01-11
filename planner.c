/********************************************************
* Purpose: Provides functions to manage time and plan
*          events.
* Authors: Maria Duch
*          Marc Escote
*		   Claudia Lajara
* Creation date: 10/11/2023
* Last changed: 25/11/2023
********************************************************/
#include "planner.h"

/********************************************************
* Purpose: Checks whether the given date's time matches
*          the local time.
* Params: in: start_time = PLANNER_Date instance of the
*             date to check.
* Return: Returns TRUE if the time matches, otherwise
*         FALSE.
********************************************************/
char PLANNER_isCurrent(PLANNER_Date start_time) {
    time_t t;
	struct tm current_time;

	// get current time
	t = time(NULL);
	current_time = *localtime(&t);

	// check if same as given time
	if ((start_time.hour == current_time.tm_hour) || (start_time.minutes == current_time.tm_min)) {
	    return (TRUE);
	}

	return (FALSE);
}

/********************************************************
* Purpose: Represents the given date's time in seconds.
* Params: in: date = PLANNER_Date instance representing
*             the date from which to get the seconds.
* Return: Returns a long representing the time of the
*         date in seconds.
********************************************************/
long PLANNER_getSeconds(PLANNER_Date date) {
    long seconds = 0;

	// calculate timestamp in seconds
	seconds += date.minutes * 60;
	seconds += date.hour * 3600;

	return (seconds);
}

/********************************************************
* Purpose: Checks whether two times (in seconds) overlap.
* Params: in: start_time1 = long representing the time
*             in seconds to compare with start_time2.
*         in: duration1 = long representing the duration
*		      in seconds of the event that starts at
*			  start_time1.
*		  in: start_time2 = long representing the time
*		      in seconds to compare with start_time1.
*		  in: duration2 = long representing the duration
*		      in seconds of the event that starts at
*			  start_time2.
* Return: Returns TRUE if the events overlap, otherwise
*         FALSE.
********************************************************/
char PLANNER_isOverlapping(long start_time1, long duration1, long start_time2, long duration2) {
    long overlap = 0;
	if (start_time1 > start_time2) {
	    overlap = start_time2 + duration1;

		// check if event2 starts before event1 has finished
		if (overlap < start_time1) {
		    return (TRUE);
		}
	} else {
	    overlap = start_time1 + duration2;

		// check if event1 starts before event2 has finished
		if (overlap < start_time2) {
		    return (TRUE);
		}
	}

	return (FALSE);
}

/********************************************************
* Purpose: Checks whether a given time will happen in the
*          future.
* Params: in: start_time = PLANNER_Date instance that
*             represents the time to check.
* Return: Returns TRUE if it is a future or present time,
*         otherwise FALSE.
********************************************************/
char PLANNER_isFutureTime(PLANNER_Date start_time) {
	time_t t;
	struct tm current_time;

	// get current time
	t = time(NULL);
	current_time = *localtime(&t);

	// check whether a time is future or has already past
	if (start_time.hour >= current_time.tm_hour) {
	    return (TRUE);
	} else {
	    if ((start_time.hour == current_time.tm_hour) || (start_time.minutes >= current_time.tm_min)) {
	        return (TRUE);
		}
	}

	return (FALSE);
}

/********************************************************
* Purpose: Gets the date as a string in the format of
*          "day/month/year-hour:minutes".
* Params: in: date = PLANNER_Date instance representing
*             the date to turn into a string.
* Return: Returns a string with the information of the
*         date in the format "day/month/year-hour:min".
********************************************************/
char * PLANNER_stringifyDate(PLANNER_Date date) {
    char * str_date = NULL;
	int i = 0;

	// allocate memory for the string
	str_date = (char *) malloc (sizeof(char) * sizeof(date));
	// turn date data into string
	str_date[i++] = date.day + '0';
	str_date[i++] = DATE_SEPARATOR;
	str_date[i++] = date.month + '0';
	str_date[i++] = DATE_SEPARATOR;
	str_date[i++] = date.year + '0';
	str_date[i++] = DATE_TIME_SEPARATOR;
	str_date[i++] = date.hour + '0';
	str_date[i++] = TIME_SEPARATOR;
	str_date[i++] = date.minutes + '0';
	
	//return (&str_date);
	return str_date;
}

/********************************************************
* Purpose: Generates a random integer within a specified
*          range.
* Params: in: min_value = int representing the lower
*             limit of the range.
*         in: max_value = int representing the upper
*             limit of the range.
* Return: Returns a random integer between min_value and
*         max_value (both included).
********************************************************/
int PLANNER_generateRandomNumber(int min_value, int max_value) {
	int random_number;
	
	// generate number between the minimum value and the maximum one
	random_number = (rand() % (max_value - min_value)) + min_value;
	
	//return (&random_number);
	return random_number;
}

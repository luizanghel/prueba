/********************************************************
* Purpose: Provides functions to manage time and plan
*          events.
* Authors: Maria Duch
*          Marc Escote
*		   Claudia Lajara
* Creation date: 10/11/2023
* Last changed: 25/11/2023
********************************************************/
#ifndef _PLANNER_H_
#define _PLANNER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE 					0
#define FALSE 					1
#define DATE_SEPARATOR			'/'
#define DATE_TIME_SEPARATOR		'-'
#define TIME_SEPARATOR			':'

typedef struct {
    char day;
	char month;
	short year;
	char hour;
	char minutes;
} PLANNER_Date;

/********************************************************
* Purpose: Checks whether the given date's time matches
*          the local time.
* Params: in: start_time = PLANNER_Date instance of the
*             date to check.
* Return: Returns TRUE if the time matches, otherwise
*         FALSE.
********************************************************/
char PLANNER_isCurrent(PLANNER_Date start_time);

/********************************************************
* Purpose: Represents the given date's time in seconds.
* Params: in: date = PLANNER_Date instance representing
*             the date from which to get the seconds.
* Return: Returns a long representing the time of the
*         date in seconds.
********************************************************/
long PLANNER_getSeconds(PLANNER_Date date);

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
char PLANNER_isOverlapping(long start_time1, long duration1, long start_time2, long duration2);

/********************************************************
* Purpose: Checks whether a given time will happen in the
*          future.
* Params: in: start_time = PLANNER_Date instance that
*             represents the time to check.
* Return: Returns TRUE if it is a future or present time,
*         otherwise FALSE.
********************************************************/
char PLANNER_isFutureTime(PLANNER_Date start_time);

/********************************************************
* Purpose: Gets the date as a string in the format of
*          "day/month/year-hour:minutes".
* Params: in: date = PLANNER_Date instance representing
*             the date to turn into a string.
* Return: Returns a string with the information of the
*         date in the format "day/month/year-hour:min".
********************************************************/
char * PLANNER_stringifyDate(PLANNER_Date date);

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
int PLANNER_generateRandomNumber(int min_value, int max_value);

#endif

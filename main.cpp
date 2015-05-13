/* Stephen Tran
 * stephen.lance.tran@gmail.com
 * (214)799-6050
 * The University of Texas at Austin
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "String.h"

/* Given a specific date give me the current number of open and closed tasks.
 * The date is inclusive so if we ask for midnight Oct 12, a task opened or closed on midnight would count */
void opencloseTasksDate(String date) {
	int open = 0;
	int close = 0;
	String startComp = StringCreate("00000000000000"); // 14 long yyyy+mm+dd+hh+mm+ss
	String endComp = StringCreate("00000000000000");

	FILE *fp;
	fp = fopen("task.json", "r");
	char ch;

	while (1) {
		ch = getc(fp);
		if (ch == EOF) {
			break;
		}
		if (ch == 'c') { // closeDate found
			ch = getc(fp);
			if (ch == 'l') {
				ch = getc(fp);
				if (ch == 'o') {
					ch = getc(fp);
					if (ch == 's') {
						ch = getc(fp);
						if (ch == 'e') {
							ch = getc(fp);
							if (ch == 'D') {
								ch = getc(fp);
								if (ch == 'a') {
									ch = getc(fp);
									if (ch == 't') {
										ch = getc(fp);
										if (ch == 'e') {
											ch = getc(fp);
											ch = getc(fp);
											ch = getc(fp);
											ch = getc(fp);
											if (ch == 'n') { // make endDate infinite (99999...)
												endComp.ptr[0] = '9';
												endComp.ptr[1] = '9';
												endComp.ptr[2] = '9';
												endComp.ptr[3] = '9';
												endComp.ptr[4] = '9';
												endComp.ptr[5] = '9';
												endComp.ptr[6] = '9';
												endComp.ptr[7] = '9';
												endComp.ptr[8] = '9';
												endComp.ptr[9] = '9';
												endComp.ptr[10] = '9';
												endComp.ptr[11] = '9';
												endComp.ptr[12] = '9';
												endComp.ptr[13] = '9';
											}
											else { // make endComp equal to date in file, but in format used to analyze
												ch = getc(fp);
												endComp.ptr[0] = ch;
												ch = getc(fp);
												endComp.ptr[1] = ch;
												ch = getc(fp);
												endComp.ptr[2] = ch;
												ch = getc(fp);
												endComp.ptr[3] = ch;
												ch = getc(fp); ch = getc(fp);
												endComp.ptr[4] = ch;
												ch = getc(fp);
												endComp.ptr[5] = ch;
												ch = getc(fp); ch = getc(fp);
												endComp.ptr[6] = ch;
												ch = getc(fp);
												endComp.ptr[7] = ch;
												ch = getc(fp); ch = getc(fp);
												endComp.ptr[8] = ch;
												ch = getc(fp);
												endComp.ptr[9] = ch;
												ch = getc(fp); ch = getc(fp);
												endComp.ptr[10] = ch;
												ch = getc(fp);
												endComp.ptr[11] = ch;
												ch = getc(fp); ch = getc(fp);
												endComp.ptr[12] = ch;
												ch = getc(fp);
												endComp.ptr[13] = ch;												
											}
											ch = getc(fp);
											while (ch != ',') {
												ch = getc(fp);
											}
											ch = getc(fp);
											while (ch != ',') {
												ch = getc(fp);
											}
											ch = getc(fp);
											while (ch != ',') {
												ch = getc(fp);
											}
											ch = getc(fp);
											while (ch != ':') {
												ch = getc(fp);
											}
											ch = getc(fp); ch = getc(fp); ch = getc(fp); // reaches start of createDate
											startComp.ptr[0] = ch; // make startComp equal to createDate in used format
											ch = getc(fp);
											startComp.ptr[1] = ch;
											ch = getc(fp);
											startComp.ptr[2] = ch;
											ch = getc(fp);
											startComp.ptr[3] = ch;
											ch = getc(fp); ch = getc(fp);
											startComp.ptr[4] = ch;
											ch = getc(fp);
											startComp.ptr[5] = ch;
											ch = getc(fp); ch = getc(fp);
											startComp.ptr[6] = ch;
											ch = getc(fp);
											startComp.ptr[7] = ch;
											ch = getc(fp); ch = getc(fp);
											startComp.ptr[8] = ch;
											ch = getc(fp);
											startComp.ptr[9] = ch;
											ch = getc(fp); ch = getc(fp);
											startComp.ptr[10] = ch;
											ch = getc(fp);
											startComp.ptr[11] = ch;
											ch = getc(fp); ch = getc(fp);
											startComp.ptr[12] = ch;
											ch = getc(fp);
											startComp.ptr[13] = ch;
											if (StringCompare(endComp, date) == 0 || StringCompare(endComp, date) == 2) { // increment relevant counters
												close = close + 1;
											}
											else if (StringCompare(endComp, date) == 1) {
												if (StringCompare(startComp, date) == 0 || StringCompare(startComp, date) == 2) {
													open = open + 1;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		} // closeDate
	} // end while

	printf("Specific to %c%c%c%c-%c%c-%c%cT%c%c:%c%c:%c%cZ, %d tasks are currently open and %d tasks are currently closed.\n",
		date.ptr[0], date.ptr[1], date.ptr[2], date.ptr[3], date.ptr[4], date.ptr[5], date.ptr[6], date.ptr[7], date.ptr[8], date.ptr[9], date.ptr[10], 
		date.ptr[11], date.ptr[12], date.ptr[13], open, close); // print answer

	StringDestroy(startComp); // clear now unneeded memory
	StringDestroy(endComp);

	fclose(fp);
	return;
}


/* Given a specific start and end date, how many tasks were opened and how many were closed in that range.
 * The start date is inclusive, the end date is exclusive. */
void countTasksinRange(String startDate, String endDate) {
	int open = 0;
	int close = 0;
	String startComp = StringCreate("00000000000000"); // 14 long yyyy+mm+dd+hh+mm+ss
	String endComp = StringCreate("00000000000000");

	FILE *fp;
	fp = fopen("task.json", "r");
	char ch;

	while (1) {
		ch = getc(fp);
		if (ch == EOF) {
			break;
		}
		if (ch == 'c') { // closeDate found
			ch = getc(fp);
			if (ch == 'l') {
				ch = getc(fp);
				if (ch == 'o') {
					ch = getc(fp);
					if (ch == 's') {
						ch = getc(fp);
						if (ch == 'e') {
							ch = getc(fp);
							if (ch == 'D') {
								ch = getc(fp);
								if (ch == 'a') {
									ch = getc(fp);
									if (ch == 't') {
										ch = getc(fp);
										if (ch == 'e') {
											ch = getc(fp);
											ch = getc(fp);
											ch = getc(fp);
											ch = getc(fp);
											if (ch == 'n') {
												// if null skip to checking createDate
											}
											else {
												ch = getc(fp); // checking closeDate
												endComp.ptr[0] = ch;
												ch = getc(fp);
												endComp.ptr[1] = ch;
												ch = getc(fp);
												endComp.ptr[2] = ch;
												ch = getc(fp);
												endComp.ptr[3] = ch;
												ch = getc(fp); ch = getc(fp);
												endComp.ptr[4] = ch;
												ch = getc(fp);
												endComp.ptr[5] = ch;
												ch = getc(fp); ch = getc(fp);
												endComp.ptr[6] = ch;
												ch = getc(fp);
												endComp.ptr[7] = ch;
												ch = getc(fp); ch = getc(fp);
												endComp.ptr[8] = ch;
												ch = getc(fp);
												endComp.ptr[9] = ch;
												ch = getc(fp); ch = getc(fp);
												endComp.ptr[10] = ch;
												ch = getc(fp);
												endComp.ptr[11] = ch;
												ch = getc(fp); ch = getc(fp);
												endComp.ptr[12] = ch;
												ch = getc(fp);
												endComp.ptr[13] = ch;
												if (StringCompare(endComp, endDate) == 2) { // increment relevant counters
													if (StringCompare(endComp, startDate) == 0 || StringCompare(endComp, startDate) == 1) {
														close = close + 1;
													}
												}
											} // check open
											ch = getc(fp);
											while (ch != ',') {
												ch = getc(fp);
											}
											ch = getc(fp);
											while (ch != ',') {
												ch = getc(fp);
											}
											ch = getc(fp);
											while (ch != ',') {
												ch = getc(fp);
											}
											ch = getc(fp);
											while (ch != ':') {
												ch = getc(fp);
											}
											ch = getc(fp); ch = getc(fp); ch = getc(fp);
											startComp.ptr[0] = ch; // checking createDate
											ch = getc(fp);
											startComp.ptr[1] = ch;
											ch = getc(fp);
											startComp.ptr[2] = ch;
											ch = getc(fp);
											startComp.ptr[3] = ch;
											ch = getc(fp); ch = getc(fp);
											startComp.ptr[4] = ch;
											ch = getc(fp);
											startComp.ptr[5] = ch;
											ch = getc(fp); ch = getc(fp);
											startComp.ptr[6] = ch;
											ch = getc(fp);
											startComp.ptr[7] = ch;
											ch = getc(fp); ch = getc(fp);
											startComp.ptr[8] = ch;
											ch = getc(fp);
											startComp.ptr[9] = ch;
											ch = getc(fp); ch = getc(fp);
											startComp.ptr[10] = ch;
											ch = getc(fp);
											startComp.ptr[11] = ch;
											ch = getc(fp); ch = getc(fp);
											startComp.ptr[12] = ch;
											ch = getc(fp);
											startComp.ptr[13] = ch;
											if (StringCompare(startComp, endDate) == 2) { // increment relevant counters
												if (StringCompare(startComp, startDate) == 0 || StringCompare(startComp, startDate) == 1) {
													open = open + 1;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	//"dueDate": "2014-10-06T23:32:33Z",
	printf("Specific to the range %c%c%c%c-%c%c-%c%cT%c%c:%c%c:%c%cZ to %c%c%c%c-%c%c-%c%cT%c%c:%c%c:%c%cZ, %d tasks were opened and %d tasks were closed.\n",
		startDate.ptr[0], startDate.ptr[1], startDate.ptr[2], startDate.ptr[3], startDate.ptr[4], startDate.ptr[5], startDate.ptr[6], startDate.ptr[7], startDate.ptr[8],
		startDate.ptr[9], startDate.ptr[10], startDate.ptr[11], startDate.ptr[12], startDate.ptr[13], endDate.ptr[0], endDate.ptr[1], endDate.ptr[2], endDate.ptr[3],
		endDate.ptr[4], endDate.ptr[5], endDate.ptr[6], endDate.ptr[7], endDate.ptr[8], endDate.ptr[9], endDate.ptr[10], endDate.ptr[11], endDate.ptr[12],
		endDate.ptr[13], open, close); // print answer

	StringDestroy(startComp); // clear now unneeded memory
	StringDestroy(endComp);

	fclose(fp);
	return;
}


/* Given a particular instanceId, give me the name of the most recent task. */
void mostRecentTask(String instanceId) { // most recent = most recent createDate; assumes instanceIds are only 3 digits max
	String comp = StringCreate("00000000000000"); // 14 long yyyy+mm+dd+hh+mm+ss
	String comp1 = StringCreate("00000000000000");
	String name = StringCreate("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"); // long string for name to be filled; assumes names will not be longer than 50 chars
	StringClear(name);

	FILE *fp;
	fp = fopen("task.json", "r");
	char ch;

	while (1) {
		ch = getc(fp);
		if (ch == EOF) {
			break;
		}
		if (ch == ' ') { // beginning of finding occurrence of Id
			ch = getc(fp);
			if (ch == instanceId.ptr[0]) {
				ch = getc(fp);
				if (ch == instanceId.ptr[1]) {
					ch = getc(fp);
					if (ch == instanceId.ptr[2]) {
						ch = getc(fp);
						if (ch == '\"') {
							while (ch != ',') {
								ch = getc(fp);
							}
							ch = getc(fp);
							while (ch != ',') {
								ch = getc(fp);
							}
							ch = getc(fp);
							while (ch != ',') {
								ch = getc(fp);
							}
							ch = getc(fp);
							while (ch != ',') {
								ch = getc(fp);
							}
							ch = getc(fp);
							while (ch != ',') {
								ch = getc(fp);
							}
							ch = getc(fp);
							while (ch != ',') {
								ch = getc(fp);
							}
							ch = getc(fp); //printf("%c", ch); // will print start of createDate
							ch = getc(fp);
							ch = getc(fp);
							ch = getc(fp);
							ch = getc(fp);
							ch = getc(fp);
							ch = getc(fp);
							ch = getc(fp);
							ch = getc(fp);
							ch = getc(fp);
							ch = getc(fp);
							ch = getc(fp);
							ch = getc(fp);
							ch = getc(fp);
							ch = getc(fp);
							ch = getc(fp);
							ch = getc(fp);
							ch = getc(fp);
							ch = getc(fp);
							ch = getc(fp);
							ch = getc(fp); // points to start of date

							comp.ptr[0] = ch;
							ch = getc(fp);
							comp.ptr[1] = ch;
							ch = getc(fp);
							comp.ptr[2] = ch;
							ch = getc(fp);
							comp.ptr[3] = ch;
							ch = getc(fp); ch = getc(fp);
							comp.ptr[4] = ch;
							ch = getc(fp);
							comp.ptr[5] = ch;
							ch = getc(fp); ch = getc(fp);
							comp.ptr[6] = ch;
							ch = getc(fp);
							comp.ptr[7] = ch;
							ch = getc(fp); ch = getc(fp);
							comp.ptr[8] = ch;
							ch = getc(fp);
							comp.ptr[9] = ch;
							ch = getc(fp); ch = getc(fp);
							comp.ptr[10] = ch;
							ch = getc(fp);
							comp.ptr[11] = ch;
							ch = getc(fp); ch = getc(fp);
							comp.ptr[12] = ch;
							ch = getc(fp);
							comp.ptr[13] = ch;
							if (StringCompare(comp, comp1) == 1) { // replacing comp1 with comp as most recent date
								comp1.ptr[0] = comp.ptr[0];
								comp1.ptr[1] = comp.ptr[1];
								comp1.ptr[2] = comp.ptr[2];
								comp1.ptr[3] = comp.ptr[3];
								comp1.ptr[4] = comp.ptr[4];
								comp1.ptr[5] = comp.ptr[5];
								comp1.ptr[6] = comp.ptr[6];
								comp1.ptr[7] = comp.ptr[7];
								comp1.ptr[8] = comp.ptr[8];
								comp1.ptr[9] = comp.ptr[9];
								comp1.ptr[10] = comp.ptr[10];
								comp1.ptr[11] = comp.ptr[11];
								comp1.ptr[12] = comp.ptr[12];
								comp1.ptr[13] = comp.ptr[13];
								StringClear(name);
								int index = 0;
								while (ch != ':') {
									ch = getc(fp);
								}
								ch = getc(fp);
								ch = getc(fp);
								ch = getc(fp);
								while (ch != '\"') { // rewriting the recently cleared name
									name.ptr[index] = ch;
									ch = getc(fp);
									index = index + 1;
								}
							}
						}
					}
				}
			}
		}
	}

	printf("Particular to %s, the most recent task is: %s.\n", instanceId.ptr, name.ptr); // print answer

	StringDestroy(comp); // clear now unneeded memory
	StringDestroy(comp1);
	StringDestroy(name);

	fclose(fp);
	return;
}


/* Given a particular instanceId, give me the count of tasks. */
void countTasksId(String instanceId) { // assumes instanceIds are always 3 digits
	int taskCnt = 0;

	FILE *fp;
	fp = fopen("task.json", "r");
	char ch;

	while (1) {
		ch = getc(fp);
		if (ch == EOF) {
			break;
		}
		if (ch == ' ') { // beginning of finding occurrence of Id
			ch = getc(fp);
			if (ch == instanceId.ptr[0]) {
				ch = getc(fp);
				if (ch == instanceId.ptr[1]) {
					ch = getc(fp);
					if (ch == instanceId.ptr[2]) {
						ch = getc(fp);
						if (ch == '\"') { // increments every time this specific phrase is seen ( xxx")
							taskCnt = taskCnt + 1;
						}
					}
				}
			}
		}
	}

	printf("Particular to %s, there are %d associated tasks.\n", instanceId.ptr, taskCnt); // prints answer

	fclose(fp);
	return;
}


void main() {
//	FILE *fp;
//	fp = fopen("task.json", "r");
//	char ch = getc(fp);
//	printf("%c", ch);

	/* Implementation example for opencloseTasksDate */
	String date /* in "yyyymmddhhmmss" format; "xxxDate": "2015-02-22T22:24:56Z", */ = StringCreate("20150222222456");
	opencloseTasksDate(date); // will display an answer
	//StringDestroy(date); // up to the user to free the memory allocated for their created strings

	/* Implementation example for countTasksinRange */
	String startDate /* in "yyyymmddhhmmss" format; "xxxDate": "2014-10-06T23:32:31Z", */ = StringCreate("20141006233231");
	String endDate /* in "yyyymmddhhmmss" format; "xxxDate": "2015-02-22T22:24:56Z", */ = StringCreate("20150222222456");
	countTasksinRange(startDate, endDate); // will display an answer
	//StringDestroy(startDate); // up to the user to free the memory allocated for their created strings
	//StringDestroy(endDate);

	/* Implementation example for mostRecentTask */
	String instanceId = StringCreate("486");
	mostRecentTask(instanceId); // will display an answer
	//StringDestroy(instanceId); // up to the user to free the memory allocated for their created strings

	/* Implementation example for countTasksId */
	String instanceId2 = StringCreate("486");
	countTasksId(instanceId2); // will display an answer
	//StringDestroy(instanceId2); // up to the user to free the memory allocated for their created strings

}


#pragma once
#define _CRT_SECURE_NO_WARNINGS

typedef struct numberInfo {

	char kindOfNumber[30];
	char phoneNumber[30];

}NumberInfo;

typedef struct phoneInfo {

	char name[30];
	char address[128];
	char birthday[11];
	int countNumInfo;
	char memo[300];
	NumberInfo **numberInfoArr;

}PhoneInfo;



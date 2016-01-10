#pragma once

void insertInfo(int, PhoneInfo ***);
int deleteInfo(PhoneInfo**, int, int);
void searchInfo(PhoneInfo**, int);
void printAll(PhoneInfo**, int);


void viewPrintCommendNumber();
void viewPrintSuccessInsert(PhoneInfo**, int);
void viewPrintSuccessDelete(char[30]);
void viewPrintNextDoingText();

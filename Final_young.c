// final_young.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "Stdafx.h"
#include "InformationOfPhoneNumber.h"
#include "AllMethods.h"
#include <stdio.h>
#include <stdlib.h>



int main(){

	int i;
	int j;
	int k;
	int arrLen=50;//이중포인터 안의 총 배열의 길이
	int chooseNum = 0;//명령 선택할 변수
	char targetName[30];//찾거나 지울때, 이름 받음
	int arrCount;//지금 사용하고 있는 배열의 최종 인덱스
	PhoneInfo*** phoneInfoArr;
	char c = '0';//입력버퍼가 빠지지 않아서 생기는 문제를 해결하기 위한 임시변수
	FILE *inputConfigInfo, *outputConfigInfo;
	FILE *inputPhoneInfo, *outputPhoneinfo;
	char buffer[1000];
	char *pointerForBuffer;

	char *context = NULL;//strtok_s를 쓰기위한 세번째 변수
	char *token = NULL;//strtok_s의 토큰
	char criteria = '\t';

	system("mode con:cols=100 lines=40");
	system("title Final Project By WonYoung");

	//총 몇 개의 정보가 들어가 있는지에 대한 txt파일을 읽어서 arrCount에 저장 START
	fopen_s(&inputConfigInfo, "InformationOfPhoneBook.txt", "r");
	fscanf_s(inputConfigInfo, "%d", &arrCount);
	fclose(inputConfigInfo);
	//총 몇 개의 정보가 들어가 있는지에 대한 txt파일을 읽어서 arrCount에 저장 END

	//다른 메소드로 넘기기 위한 삼중 포인터 하나를 동적으로 할당 START
	phoneInfoArr = (PhoneInfo***)malloc(sizeof(PhoneInfo**));
	if (phoneInfoArr == NULL) {
		exit(-1);
	}
	//다른 메소드로 넘기기 위한 삼중 포인터 하나를 동적으로 할당 START

	//배열을 동적으로 할당(arrLen) START
	phoneInfoArr[0] = (PhoneInfo**)malloc(sizeof(PhoneInfo*) * arrLen);
	if (phoneInfoArr == NULL) {
		exit(-1);
	}
	//배열을 동적으로 할당(arrLen) END

	//개수(arrLen)만큼 돌면서 PhoneInfo가 들어갈 자리를 동적으로 할당 시작
	for (i = 0; i < arrLen; i++) {
		phoneInfoArr[0][i] = (PhoneInfo*)malloc(sizeof(PhoneInfo));
		memset(phoneInfoArr[0][i], 0, sizeof(PhoneInfo));
		
		if (phoneInfoArr[0][i] == NULL) {
			for (j = 0; j < i; j++) {
				free(phoneInfoArr[0][j]);
			}
			free(phoneInfoArr[0]);
			exit(-1);
		}

		phoneInfoArr[0][i]->numberInfoArr = (NumberInfo**)malloc(sizeof(NumberInfo*));//numberInfo들이 들어갈 NumberInfoArr 박스를 만듦
		if (phoneInfoArr[0][i]->numberInfoArr == NULL) {
			free(phoneInfoArr[0][i]->numberInfoArr);
			exit(-1);
		}
		//전화번호 들어갈 자리 하나 씩은 만들어주기 START
		phoneInfoArr[0][i]->countNumInfo = 1;
		phoneInfoArr[0][i]->numberInfoArr[0] = (NumberInfo*)malloc(sizeof(NumberInfo));
		memset(phoneInfoArr[0][i]->numberInfoArr[0], 0, sizeof(NumberInfo));
		//전화번호 들어갈 자리 하나 씩은 만들어주기 END
	}
	//개수(arrLen)만큼 돌면서 PhoneInfo가 들어갈 자리를 동적으로 할당 종료


	//파일을 읽어서 정보를 입력 START
	fopen_s(&inputPhoneInfo, "PhoneBook.txt", "r");

	i = 0;
	while (i<arrCount){
		fgets(buffer, 1000, inputPhoneInfo);
		buffer[strlen(buffer) - 1] = '\0';

		//tab 단위로 떼어내서 각 요소에 넣을 것 START
		strcpy(phoneInfoArr[0][i]->name, strtok_s(buffer, &criteria, &context));//첫 번째 자름. 이름
		strcpy(phoneInfoArr[0][i]->address, strtok_s(context, &criteria, &context));//두 번째 자름. 주소
		strcpy(phoneInfoArr[0][i]->birthday, strtok_s(context, &criteria, &context));//세 번째 자름. 생일
		strcpy(phoneInfoArr[0][i]->memo, strtok_s(context, &criteria, &context));//네 번째 자름. 메모
		
		phoneInfoArr[0][i]->countNumInfo = atoi(strtok_s(context, &criteria, &context));//다섯 번째 자름. 전화번호 몇 개?
		//tab 단위로 떼어내서 각 요소에 넣을 것 END

		//NumberInfoArr안의 NumberInfo를 countNumInfo만큼 말록 시작
		for (j = 0; j < phoneInfoArr[0][i]->countNumInfo; j++) {
			phoneInfoArr[0][i]->numberInfoArr[j] = (NumberInfo*)malloc(sizeof(NumberInfo));
			memset(phoneInfoArr[0][i]->numberInfoArr[j], 0, sizeof(NumberInfo));
		}
		//NumberInfoArr안의 NumberInfo를 countNumInfo만큼 말록 종료

		//countNumInfo 만큼 돌면서 kindOfnumber와 phoneNumber를 넣음 START
		for (j = 0; j < phoneInfoArr[0][i]->countNumInfo; j++) {
			strcpy(phoneInfoArr[0][i]->numberInfoArr[j]->kindOfNumber, strtok_s(context, &criteria, &context));//전화번호 이름 
			strcpy(phoneInfoArr[0][i]->numberInfoArr[j]->phoneNumber, strtok_s(context, &criteria, &context));//전화번호
		}
		//countNumInfo 만큼 돌면서 kindOfnumber와 phoneNumber를 넣음 END
		i++;
	}
	fclose(inputPhoneInfo);
	//파일을 읽어서 정보를 입력 END

	//do-while 시작
	do {
		
		viewPrintCommendNumber();//번호를 입력받는 텍스트를 출력하는 함수
		
		while (scanf_s("%d", &chooseNum) != 1) {
			c = getchar();
			system("cls");//이걸로 기존 문제 해결!!(반복 출력)
			printf("\n숫자가 아닙니다. 다시 입력해주세요.\n\n");
			viewPrintCommendNumber();
		}

		if (chooseNum == 1) {

			 //PhoneInfoArr이 가득차면, 더 늘리는 코드 시작
			if (arrCount == arrLen) {

				arrLen += 3;
				phoneInfoArr[0] = (PhoneInfo**)realloc(phoneInfoArr, sizeof(PhoneInfo*)*arrLen);//추가적으로 길이를 3늘려서 동적으로 재할당

				if (phoneInfoArr == NULL) {
					exit(-1);
				}

				//개수만큼 돌면서 추가된 자리에 PhoneInfo가 들어갈 자리를 동적으로 다시 할당 시작
				for (i = arrCount; i <= arrLen; i++) {
					phoneInfoArr[0][i] = (PhoneInfo*)malloc(sizeof(PhoneInfo));
					memset(phoneInfoArr[0][i], 0, sizeof(PhoneInfo));
					if (phoneInfoArr[0][i] == NULL) {
						for (j = 0; j < i; j++) {
							free(phoneInfoArr[0][j]);
						}
						free(phoneInfoArr[0]);
						exit(-1);
					}
				}
				//개수만큼 돌면서 추가된 자리에 PhoneInfo가 들어갈 자리를 동적으로 다시 할당 종료

			}
			//PhoneInfoArr이 가득차면, 더 늘리는 코드 종료

			insertInfo(arrCount, phoneInfoArr);
			viewPrintSuccessInsert(phoneInfoArr[0], arrCount);//insert가 성공했을때 출력
			arrCount++;

		}else if (chooseNum == 2) {
			
			arrCount = deleteInfo(phoneInfoArr[0], arrLen, arrCount);

		}else if (chooseNum == 3) {

			searchInfo(phoneInfoArr[0], arrCount);
			viewPrintNextDoingText();//searching을 마치고 다음 행동하라는 부분을 프린트하는 함수

		}else if (chooseNum == 4) {

			printAll(phoneInfoArr[0], arrCount);

		}else if (chooseNum == 5) {
		}else {
			system("cls");
			printf("\n\n잘못된 번호를 입력하셨습니다. 다시 입력해주세요.\n\n");

		}


	} while (chooseNum != 5);
	//do-while 종료

	//총 몇 개의 전화부 정보가 저장되어 있는지를 저장 START
	fopen_s(&outputConfigInfo, "InformationOfPhoneBook.txt", "wt");
	fprintf_s(outputConfigInfo, "%d", arrCount);
	fclose(outputConfigInfo);
	//총 몇 개의 전화부 정보가 저장되어 있는지를 저장 END

	//주소록 정보를 파일에 갱신해서 다시 담아줌 START
	fopen_s(&outputPhoneinfo, "PhoneBook.txt", "wt");
	i = 0;
	while (i < arrCount) {
		fputs(phoneInfoArr[0][i]->name, outputConfigInfo);
		fprintf_s(outputPhoneinfo, "\t");
		fputs(phoneInfoArr[0][i]->address, outputConfigInfo);
		fprintf_s(outputPhoneinfo, "\t");
		fputs(phoneInfoArr[0][i]->birthday, outputConfigInfo);
		fprintf_s(outputPhoneinfo, "\t");
		fputs(phoneInfoArr[0][i]->memo, outputConfigInfo);
		fprintf_s(outputPhoneinfo, "\t");
		fprintf_s(outputConfigInfo, "%d", phoneInfoArr[0][i]->countNumInfo);
		for (j = 0; j < phoneInfoArr[0][i]->countNumInfo; j++) {
			fprintf_s(outputPhoneinfo, "\t");
			fputs(phoneInfoArr[0][i]->numberInfoArr[j]->kindOfNumber, outputConfigInfo);
			fprintf_s(outputPhoneinfo, "\t");
			fputs(phoneInfoArr[0][i]->numberInfoArr[j]->phoneNumber, outputConfigInfo);
		}
		fprintf_s(outputPhoneinfo, "\n");
		i++;
	}
	fclose(outputPhoneinfo);
	//주소록 정보를 파일에 갱신해서 다시 담아줌 END

	//끝나서 모두 free 시작
	for (i = 0; i < arrLen; i++) {
		for (j = 0; j < phoneInfoArr[0][i]->countNumInfo; j++) {
			free(phoneInfoArr[0][i]->numberInfoArr[j]);
		}
		free(phoneInfoArr[0][i]);

	}

	free(phoneInfoArr[0]);
	free(phoneInfoArr);
	//끝나서 모두 free 종료

	return 0;

}//Main 함수 종료



void insertInfo(int takenArrCount, PhoneInfo ***phoneInfoArr) {

	int arrCount = takenArrCount;	
	int i;
	int j;
	int notNumFormat=0;
	int isNumFormatFlag = 0;//0은 false / 1은 true;
	int isBirthdayFormatFlag = 0; //0은 false / 1은 true;
	int isEndInputPhoneNumber = 0; //0은 끝 / 1은 계속;
	int commendNum;

	printf("\n");
	printf("[입력]\n");

	//이름 입력 부분(너무 길면 제한) START
	getchar();
	printf("이름을 입력하세요: ");
	while (scanf_s("%[^\n]s", phoneInfoArr[0][arrCount]->name, sizeof(phoneInfoArr[0][arrCount]->name)) != 1) {
		printf("너무 긴 이름을 입력하셨습니다. 영문 30자, 한글 15자 이내로 입력해주세요.\n");
		printf("이름음 입력하세요: ");
	}
	//이름 입력 부분(너무 길면 제한) END

	//주소 입력 부분(너무 길면 제한) START
	getchar();
	printf("주소를 입력하세요: ");
	while (scanf_s("%[^\n]s", phoneInfoArr[0][arrCount]->address, sizeof(phoneInfoArr[0][arrCount]->address)) != 1) {
		printf("너무 긴 주소를 입력하셨습니다. 영문 128자, 한글 64자 이내로 입력해주세요.\n");
		printf("주소를 입력하세요: ");
	}
	//주소 입력 부분(너무 길면 제한) END


	//생일 입력 및 양식 검사해주는 코드 START
	getchar();
	printf("생일을 입력하세요(0000-00-00 양식으로 입력하세요: ");
	while (isBirthdayFormatFlag != 1) {
		notNumFormat = 0;
		while (scanf_s("%s", phoneInfoArr[0][arrCount]->birthday, sizeof(phoneInfoArr[0][arrCount]->birthday)) != 1) {
			printf("너무 길게 입력하셨습니다. 다시 입력해주세요.\n");
			printf("생일을 입력하세요(0000-00-00 양식으로 입력하세요: ");
		}
		i = 0;
		while (phoneInfoArr[0][arrCount]->birthday[i] != '\0') {
			if ((phoneInfoArr[0][arrCount]->birthday[i]<48 || phoneInfoArr[0][arrCount]->birthday[i]>57)
				&& phoneInfoArr[0][arrCount]->birthday[i] != 45) {//아스키 48 ~ 57이 숫자
				notNumFormat++;
			}
			i++;
		}
		//'-'가 정확한 위치에 들어갔는지 확인하는 코드 START
		if (phoneInfoArr[0][arrCount]->birthday[4] != 45 || phoneInfoArr[0][arrCount]->birthday[7] != 45) {
			notNumFormat++;
		}
		//'-'가 정확한 위치에 들어갔는지 확인하는 코드 END

		if (notNumFormat > 0) {
			printf("정확한 양식이 아닙니다. 다시 입력하세요\n");
			printf("생일을 입력하세요(0000-00-00 양식으로 입력하세요: ");
		}else if (notNumFormat == 0) {
			isBirthdayFormatFlag = 1;
		}
	}
	//생일 입력 및 양식 검사해주는 코드 END

	//메모 입력 부분(너무 길면 제한) START
	getchar();
	printf("메모를 입력하세요: ");
	while (scanf_s("%[^\n]s", phoneInfoArr[0][arrCount]->memo, sizeof(phoneInfoArr[0][arrCount]->memo)) != 1) {
		printf("너무 길게 입력하셨습니다. 영문 300자, 한글 150자 이내로 입력해주세요.\n");
		printf("메모를 입력하세요: ");
		while (scanf_s("%[^\n]s", phoneInfoArr[0][arrCount]->memo, sizeof(phoneInfoArr[0][arrCount]->memo)) != 1) {//입력버퍼문제 해결
			getchar();
		}
	}
	//메모 입력 부분(너무 길면 제한) END


	phoneInfoArr[0][arrCount]->countNumInfo = 1;
	do {
		getchar();
		printf("\n%d번째 전화번호 정보를 입력합니다\n", (phoneInfoArr[0][arrCount]->countNumInfo));
		//전화번호 종류를 입력하는 부분(너무 길면 제한) START
		printf("어디 전화번호인가요?(집전화, 직장전화, 휴대전화, 팩스 등등): ");
		while (scanf_s("%[^\n]s", phoneInfoArr[0][arrCount]->numberInfoArr[(phoneInfoArr[0][arrCount]->countNumInfo)-1]->kindOfNumber,
			sizeof(phoneInfoArr[0][arrCount]->numberInfoArr[(phoneInfoArr[0][arrCount]->countNumInfo)-1]->kindOfNumber)) != 1) {
			printf("너무 길게 입력하셨습니다. 영문 30자, 한글 15자 이내로 입력해주세요.\n");
			printf("어디 전화번호인가요?(집전화, 직장전화, 휴대전화, 팩스 등등): ");
		}
		//전화번호 종류를 입력하는 부분(너무 길면 제한) END
		
		//전화번호 입력 및 양식을 검사해주는 코드 START
		isNumFormatFlag = 0;
		printf("전화번호를 입력하세요(숫자와 기호'-'만 입력 가능합니다): ");
		while (isNumFormatFlag != 1) {

			notNumFormat = 0;
			getchar();
			while (scanf_s("%[^\n]s", phoneInfoArr[0][arrCount]->numberInfoArr[(phoneInfoArr[0][arrCount]->countNumInfo)-1]->phoneNumber,
				sizeof(phoneInfoArr[0][arrCount]->numberInfoArr[(phoneInfoArr[0][arrCount]->countNumInfo)-1]->phoneNumber)) != 1) {
				printf("너무 긴 전화번호를 입력하셨습니다. 30자 이내로 입력해주세요.\n");
				printf("전화번호를 입력하세요(숫자와 기호'-'만 입력 가능합니다): ");
			}

			i = 0;
			while (phoneInfoArr[0][arrCount]->numberInfoArr[(phoneInfoArr[0][arrCount]->countNumInfo)-1]->phoneNumber[i] != '\0') {
				if ((phoneInfoArr[0][arrCount]->numberInfoArr[(phoneInfoArr[0][arrCount]->countNumInfo)-1]->phoneNumber[i] < 48
					|| phoneInfoArr[0][arrCount]->numberInfoArr[(phoneInfoArr[0][arrCount]->countNumInfo)-1]->phoneNumber[i]>57)
					&& phoneInfoArr[0][arrCount]->numberInfoArr[(phoneInfoArr[0][arrCount]->countNumInfo)-1]->phoneNumber[i] != 45) {//아스키 48 ~ 57이 숫자
					notNumFormat++;
				}
				i++;
			}

			if (notNumFormat > 0) {
				printf("숫자 혹은 '-'가 아닙니다. 다시 입력하세요\n");
				printf("전화번호를 입력하세요(숫자와 기호'-'만 입력 가능합니다): ");
			}
			else if (notNumFormat == 0) {
				isNumFormatFlag = 1;
			}
		}
		//전화번호 입력 및 양식을 검사해주는 코드 END

		//commendNum 입력 START
		printf("\n[ 전화번호 계속 입력  : 1 ]\n");
		printf("[ 그만 입력           : 2 ]\n 입력 : ");
		while (scanf_s("%d", &commendNum) != 1) {//입력버퍼문제 해결
			getchar();
		}

		while (commendNum != 1 && commendNum != 2) {
			printf("\n잘못 입력하셨습니다. 다시 입력하세요.");

			printf("\n[ 전화번호 계속 입력  : 1 ]\n");
			printf("[ 그만 입력           : 2 ]\n 입력 : ");

			while (scanf_s("%d", &commendNum) != 1) {//입력버퍼문제 해결
				getchar();
			}
		}
		printf("\n");
		//commendNum 입력 END

		//계속 입력이라면 realloc START
		if (commendNum == 1) {
			(phoneInfoArr[0][arrCount]->countNumInfo)++;
			//이전 것들을 임시 말록 받아서 넣고, 리얼록 받은 것에 복제하는 방법
			phoneInfoArr[0][arrCount]->numberInfoArr = (NumberInfo**)realloc(phoneInfoArr[0][arrCount]->numberInfoArr,
				sizeof(NumberInfo*)*((phoneInfoArr[0][arrCount]->countNumInfo)));//추가적으로 길이를 하나 늘려서 동적으로 재할당

			if (phoneInfoArr[0][arrCount]->numberInfoArr == NULL) {
				exit(-1);
			}

			//개수만큼 돌면서 추가된 자리에 PhoneInfo가 들어갈 자리를 동적으로 다시 할당 시작
			for (i = (phoneInfoArr[0][arrCount]->countNumInfo)-1; i < (phoneInfoArr[0][arrCount]->countNumInfo); i++) {
				phoneInfoArr[0][arrCount]->numberInfoArr[i] = (NumberInfo*)malloc(sizeof(NumberInfo));
				memset(phoneInfoArr[0][arrCount]->numberInfoArr[i], 0, sizeof(NumberInfo));
				if (phoneInfoArr[0][arrCount]->numberInfoArr[i] == NULL) {
					for (j = 0; j < i; j++) {
						free(phoneInfoArr[0][arrCount]->numberInfoArr[j]);
					}
					free(phoneInfoArr[0][arrCount]->numberInfoArr);
					exit(-1);
				}
			}
			//개수만큼 돌면서 추가된 자리에 PhoneInfo가 들어갈 자리를 동적으로 다시 할당 종료

			isEndInputPhoneNumber = 1;
		}
		//계속 입력이라면 realloc END
		else {//0이면 out!
			isEndInputPhoneNumber = 0;
		}

	} while (isEndInputPhoneNumber != 0);//0은 끝, 1은 계속

	printf("\n");

}



int deleteInfo(PhoneInfo **phoneInfoArr, int arrLen, int takenArrCount) {
	int compareNum = -1;
	int i;
	int j;
	int k;
	int arrCount = takenArrCount;
	char targetName[30];
	char targetNumber[30];
	int commendNum;
	int notNumFormat = 0;
	int isNumFormatFlag = 0;//0은 false / 1은 true;

	printf("\n[ 이름으로 삭제  : 1]\n[ 전화번호로 삭제: 2]\n 입력 : ");
	scanf_s("%d", &commendNum);

	while (commendNum != 1 && commendNum != 2) {
		printf("\n잘못 입력하셨습니다. 다시 입력하세요.");
		printf("\n[ 이름으로 삭제  : 1]\n[ 전화번호로 삭제: 2]\n 입력 : ");

		while (scanf_s("%d", &commendNum) != 1) {//입력버퍼문제 해결
			getchar();
		}
	}

	if (commendNum == 1) {
		printf("삭제할 사람의 이름을 입력하세요: ");

		//이름이 잘 입력되었는지 검사하는 부분 START
		while (scanf_s("%s", targetName, sizeof(targetName)) != 1) {

			printf("너무 긴 이름을 입력하셨습니다. 영문 30자, 한글 15자 이내로 입력해주세요.\n");
			printf("Input Name: ");

		}
		//이름이 잘 입력되었는지 검사하는 부분 END

		while (compareNum != 0) {
			for (i = 0; i < arrCount; i++) {
				compareNum = strcmp(phoneInfoArr[i]->name, targetName);

				if (compareNum == 0) {
					//해당 인덱스 이상의 것들을 불러다가, 해당 인덱스로 덮어씌우고 arrCount 하나 줄임 시작
					if (arrCount != 1) {//단 인덱스가 1이 아니면.. 왜냐면 인덱스가 1인데 phoneInfoArr 길이가 1이면 애러날 수도 있으니깐(지금 안나는 이유는 내가 기존에 만들어놨기 때문)_물론 애러 안나고 쓰레기 값이 그냥 들어갈 것 같긴함
						for (j = i; j < arrLen; j++) {
							phoneInfoArr[j] = phoneInfoArr[j + 1];
						}
					}
					arrCount--;
					//해당 인덱스 이상의 것들을 불러다가, 해당 인덱스로 덮어씌우고 arrCount 하나 줄임 종료
				}
			}

			//찾아서 성공적으로 지웠으면 함수에서 나감 시작
			if (compareNum == 0) {
				viewPrintSuccessDelete(targetName);//삭제가 성공했을때, 출력하는 함수
				return arrCount;
			}
			//찾아서 성공적으로 지웠으면 함수에서 나감 종료

			printf("해당하는 이름이 없습니다. 다시 입력해주세요.\n");
			printf("(기호'~'를 입력하시면 선택창으로 돌아갑니다)\n");
			printf("\n");
			printf("입력: ");
			scanf_s("%s", targetName, sizeof(targetName));

			if (strcmp(targetName, "~") == 0) {
				return;
			}

		}
	}
	else if (commendNum == 2) {
		printf("삭제할 사람의 전화번호를 입력하세요(숫자와 기호'-'만 입력 가능합니다): ");

		//숫자 혹은 '-'만 입력하도록 설정하는 코드 시작
		while (isNumFormatFlag != 1) {
			notNumFormat = 0;
			while (scanf_s("%s", targetNumber, sizeof(targetNumber)) != 1) {
				printf("너무 긴 전화번호를 입력하셨습니다. 30자 이내로 입력해주세요.\n");
				printf("전화번호를 입력하세요(숫자와 기호'-'만 입력 가능합니다): ");
			}
			i = 0;
			while (targetNumber[i] != '\0') {
				if ((targetNumber[i]<48 || targetNumber[i]>57) && targetNumber[i] != 45) {//아스키 48 ~ 57이 숫자
					notNumFormat++;
				}
				i++;
			}

			if (notNumFormat > 0) {
				printf("숫자 혹은 '-'가 아닙니다. 다시 입력하세요\n");
				printf("전화번호를 입력하세요(숫자와 기호'-'만 입력 가능합니다): ");
			}
			else if (notNumFormat == 0) {
				isNumFormatFlag = 1;
			}
		}
		//숫자 혹은 '-'만 입력하도록 설정하는 코드 종료

		while (compareNum != 0) {
			for (i = 0; i < arrCount; i++) {
				for (j = 0; j < (phoneInfoArr[i]->countNumInfo)+1; j++) {
					compareNum = strcmp(phoneInfoArr[i]->numberInfoArr[j]->phoneNumber, targetNumber);
					if (compareNum == 0) {
						viewPrintSuccessDelete(phoneInfoArr[i]->name);//삭제가 성공했을때, 출력하는 함수(삭제 완성하기 전에)
						//해당 인덱스 이상의 것들을 불러다가, 해당 인덱스로 덮어씌우고 arrCount 하나 줄임 시작
						if (arrCount != 1) {//단 인덱스가 1이 아니면.. 왜냐면 인덱스가 1인데 phoneInfoArr 길이가 1이면 애러날 수도 있으니깐(지금 안나는 이유는 내가 기존에 만들어놨기 때문)_물론 애러 안나고 쓰레기 값이 그냥 들어갈 것 같긴함
							for (k = i; k < arrLen; k++) {
								phoneInfoArr[k] = phoneInfoArr[k + 1];
							}
						}
						arrCount--;
						//해당 인덱스 이상의 것들을 불러다가, 해당 인덱스로 덮어씌우고 arrCount 하나 줄임 종료
					}
				}
			}

			//찾아서 성공적으로 지웠으면 함수에서 나감 시작
			if (compareNum == 0) {
				return arrCount;
			}
			//찾아서 성공적으로 지웠으면 함수에서 나감 종료

			printf("해당하는 전화번호가 없습니다. 다시 입력해주세요.\n");
			printf("(기호'~'를 입력하시면 선택창으로 돌아갑니다)\n");
			printf("\n");
			printf("입력: ");
			scanf_s("%s", targetNumber, sizeof(targetNumber));

			if (strcmp(targetName, "~") == 0) {
				return;
			}
		}
	}
}


void searchInfo(PhoneInfo **phoneInfoArr, int arrCount) {

	int compareNum = -1;
	int targetCount = 0;
	int i;
	int j;
	char targetName[30];
	char targetNumber[30];
	int commendNum;
	int notNumFormat = 0;
	int isNumFormatFlag = 0;//0은 false / 1은 true;


	printf("\n[ 이름으로 찾기  : 1]\n[ 전화번호로 찾기: 2]\n 입력 : ");
	getchar();
	scanf_s("%d", &commendNum);

	while (commendNum != 1 && commendNum != 2) {
		printf("\n잘못 입력하셨습니다. 다시 입력하세요.");
		printf("\n[ 이름으로 찾기  : 1]\n[ 전화번호로 찾기: 2]\n 입력 : ");

		while (scanf_s("%d", &commendNum) != 1) {//입력버퍼 문제 해결
			getchar();
		}
	}

	if (commendNum == 1) {

		printf("정보를 확인할 사람의 이름을 입력하세요: ");
		getchar();
		//이름이 잘 입력되었는지 검사하는 부분 START
		while (scanf_s("%[^\n]s", targetName, sizeof(targetName)) != 1) {
			printf("너무 긴 이름을 입력하셨습니다. 영문 30자, 한글 15자 이내로 입력해주세요.\n");
			printf("이름을 입력하세요: ");
		}
		//이름이 잘 입력되었는지 검사하는 부분 END

		//compareNum이 0이 아니면 계속 돌면서 값을 받아줘야 함. 그리고 중간에 빠져나가는 코드도 적어줘야함 시작
		while (compareNum != 0) {
			for (i = 0; i < arrCount; i++) {
				compareNum = strcmp(phoneInfoArr[i]->name, targetName);

				if (compareNum == 0) {
					//비교한 결과가 같으면, 그 인덱스(arrCount_여기선 i)를 리턴헤줌 시작
					system("cls");
					printf("\n");
					printf("*****************검색 결과*****************\n");
					printf("\n");
					printf("  이름: %s\n", targetName);
					printf("  주소: %s\n", phoneInfoArr[i]->address);
					printf("  생일: %s\n", phoneInfoArr[i]->birthday);
					printf("  메모: %s\n", phoneInfoArr[i]->memo);
					for (j = 0; j < (phoneInfoArr[i]->countNumInfo); j++) {
						printf("  %d번째 전화번호: %s [%s]\n", j+1, 
							phoneInfoArr[i]->numberInfoArr[j]->kindOfNumber, 
							phoneInfoArr[i]->numberInfoArr[j]->phoneNumber);
					}
					printf("\n");
					printf("*******************************************\n");
					return;
					//비교한 결과가 같으면, 그 인덱스(arrCount_여기선 i)를 리턴헤줌 종료
				}
			}
//(생각 시작) 생각해보니 이 코드가 반복됨. 하나의 함수로 빼놔도 좋을 것 같음
			//위에서 리턴이 일어나지 않으면, 못 찾은 것이므로 다시 받아주거나 빠져나갈 수 있게 해줘야 함 시작
			printf("\n");
			printf("해당하는 이름이 없습니다. 다시 입력해주세요.\n");
			printf("(기호'~'를 입력하시면 선택창으로 돌아갑니다)\n");
			printf("\n");
			printf("입력: ");
			scanf_s("%s", targetName, sizeof(targetName));

			if (strcmp(targetName, "~") == 0) {
				return;
			}
			//위에서 리턴이 일어나지 않으면, 못 찾은 것이므로 다시 받아주거나 빠져나갈 수 있게 해줘야 함 종료
//(생각 종료) 생각해보니 이 코드가 반복됨. 하나의 함수로 빼놔도 좋을 것 같음
		}
		//compareNum이 0이 아니면 계속 돌면서 값을 받아줘야 함. 그리고 중간에 빠져나가는 코드도 적어줘야함 종료

	}else if (commendNum == 2) {
		printf("찾을 사람의 전화번호를 입력하세요(Only Number or '-'): ");

		//숫자 혹은 '-'만 입력하도록 설정하는 코드 시작
		while (isNumFormatFlag != 1) {
			notNumFormat = 0;
			
			while (scanf_s("%s", targetNumber, sizeof(targetNumber)) != 1) {
				printf("너무 긴 전화번호를 입력하셨습니다. 30자 이내로 입력해주세요.\n");
				printf("찾을 사람의 전화번호를 입력하세요(Only Number or '-'): ");
			}
			i = 0;
			while (targetNumber[i] != '\0') {

				if ((targetNumber[i]<48 || targetNumber[i]>57) && targetNumber[i] != 45) {//아스키 48 ~ 57이 숫자
					notNumFormat++;
				}
				i++;
			}

			if (notNumFormat > 0) {

				printf("숫자 혹은 '-'가 아닙니다. 다시 입력하세요\n");
				printf("찾을 사람의 전화번호를 입력하세요(Only Number or '-'): ");

			}
			else if (notNumFormat == 0) {
				isNumFormatFlag = 1;
			}

		}
		//숫자 혹은 '-'만 입력하도록 설정하는 코드 종료


		//compareNum이 0이 아니면 계속 돌면서 값을 받아줘야 함. 그리고 중간에 빠져나가는 코드도 적어줘야함 시작
		while (compareNum != 0) {
			for (i = 0; i < arrCount; i++) {

				for (j = 0; j < (phoneInfoArr[i]->countNumInfo)+1; j++) {//해당 이름의 전화번호들을 돌면서 비교
					compareNum = strcmp(phoneInfoArr[i]->numberInfoArr[j]->phoneNumber, targetNumber);
				}

				if (compareNum == 0) {//비교해서 찾으면 정보를 출력해줌
					system("cls");
					printf("\n");
					printf("*****************검색 결과*****************\n");
					printf("\n");
					printf("  이름: %s\n", phoneInfoArr[i]->name);
					printf("  주소: %s\n", phoneInfoArr[i]->address);
					printf("  생일: %s\n", phoneInfoArr[i]->birthday);
					printf("  메모: %s\n", phoneInfoArr[i]->memo);
					for (j = 0; j < (phoneInfoArr[i]->countNumInfo); j++) {
						printf("  %d번째 전화번호: %s [%s]\n", j + 1,
							phoneInfoArr[i]->numberInfoArr[j]->kindOfNumber,
							phoneInfoArr[i]->numberInfoArr[j]->phoneNumber);
					}
					printf("\n");
					printf("*******************************************\n");
					return;
				}
			}
			//(생각 시작) 생각해보니 이 코드가 반복됨. 하나의 함수로 빼놔도 좋을 것 같음
			//위에서 리턴이 일어나지 않으면, 못 찾은 것이므로 다시 받아주거나 빠져나갈 수 있게 해줘야 함 시작
			printf("\n");
			printf("해당하는 전화번호가 없습니다. 다시 입력해주세요.\n");
			printf("(기호'~'를 입력하시면 선택창으로 돌아갑니다)\n");
			printf("\n");
			printf("입력: ");
			scanf_s("%s", targetNumber, sizeof(targetNumber));

			if (strcmp(targetNumber, "~") == 0) {
				return;
			}
			//위에서 리턴이 일어나지 않으면, 못 찾은 것이므로 다시 받아주거나 빠져나갈 수 있게 해줘야 함 종료
			//(생각 종료) 생각해보니 이 코드가 반복됨. 하나의 함수로 빼놔도 좋을 것 같음
		}
		//compareNum이 0이 아니면 계속 돌면서 값을 받아줘야 함. 그리고 중간에 빠져나가는 코드도 적어줘야함 종료
	}
}



void printAll(PhoneInfo **phoneInfoArr, int arrCount) {//모든 정보를 출력
	int i;
	int j;

	system("cls");//한번 지움
	printf("*****************출력결과******************\n");
	if (arrCount == 0) {
		printf("\n출력할 결과가 없습니다.\n");
	}else {
		for (i = 0; i < arrCount; i++) {
			printf("\n");
			printf("  이름: %s\n", phoneInfoArr[i]->name);
			printf("  주소: %s\n", phoneInfoArr[i]->address);
			printf("  생일: %s\n", phoneInfoArr[i]->birthday);
			printf("  메모: %s\n", phoneInfoArr[i]->memo);
			for (j = 0; j < (phoneInfoArr[i]->countNumInfo); j++) {
				printf("  %d번째 전화번호: %s [%s]\n", j + 1,
					phoneInfoArr[i]->numberInfoArr[j]->kindOfNumber,
					phoneInfoArr[i]->numberInfoArr[j]->phoneNumber);
			}
		}
	}
	printf("\n*******************************************\n");
	printf("\n");

}



void viewPrintCommendNumber() {

	printf("====================메뉴===================\n\n");
	printf("1. 전화번호 입력 \n");
	printf("2. 정보 삭제 \n");
	printf("3. 정보 찾기 \n");
	printf("4. 모든 정보 보기 \n");
	printf("5. 나가기\n\n");
	printf("===========================================\n\n");

	printf("번호를 입력해주세요: ");

}

void viewPrintSuccessInsert(PhoneInfo **phoneInfoArr, int arrCount) {

	int j;
	system("cls");
	printf("********************성공*******************\n\n");
	printf("  이름: %s\n", phoneInfoArr[arrCount]->name);
	printf("  주소: %s\n", phoneInfoArr[arrCount]->address);
	printf("  생일: %s\n", phoneInfoArr[arrCount]->birthday);
	printf("  메모: %s\n", phoneInfoArr[arrCount]->memo);
	for (j = 0; j < (phoneInfoArr[arrCount]->countNumInfo); j++) {
		printf("  %d번째 전화번호: %s [%s]\n", j + 1,
			phoneInfoArr[arrCount]->numberInfoArr[j]->kindOfNumber,
			phoneInfoArr[arrCount]->numberInfoArr[j]->phoneNumber);
	}
	printf(" 다음 할 일을 입력하세요.\n\n");
	printf("*******************************************\n\n");

}

void viewPrintSuccessDelete(char targetName[30]) {

	system("cls");
	printf("********************성공*******************\n\n");
	printf("   [%s]을(를) 성공적으로 삭제하였습니다.\n", targetName);
	printf("   다음 할 일을 입력하세요.\n\n");
	printf("*******************************************\n\n");

}


void viewPrintNextDoingText() {
	printf("\n*******************************************\n");
	printf("          다음 할 일을 입력하세요.\n");
	printf("*******************************************\n\n");
}


// final_young.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
	int arrLen=50;//���������� ���� �� �迭�� ����
	int chooseNum = 0;//��� ������ ����
	char targetName[30];//ã�ų� ���ﶧ, �̸� ����
	int arrCount;//���� ����ϰ� �ִ� �迭�� ���� �ε���
	PhoneInfo*** phoneInfoArr;
	char c = '0';//�Է¹��۰� ������ �ʾƼ� ����� ������ �ذ��ϱ� ���� �ӽú���
	FILE *inputConfigInfo, *outputConfigInfo;
	FILE *inputPhoneInfo, *outputPhoneinfo;
	char buffer[1000];
	char *pointerForBuffer;

	char *context = NULL;//strtok_s�� �������� ����° ����
	char *token = NULL;//strtok_s�� ��ū
	char criteria = '\t';

	system("mode con:cols=100 lines=40");
	system("title Final Project By WonYoung");

	//�� �� ���� ������ �� �ִ����� ���� txt������ �о arrCount�� ���� START
	fopen_s(&inputConfigInfo, "InformationOfPhoneBook.txt", "r");
	fscanf_s(inputConfigInfo, "%d", &arrCount);
	fclose(inputConfigInfo);
	//�� �� ���� ������ �� �ִ����� ���� txt������ �о arrCount�� ���� END

	//�ٸ� �޼ҵ�� �ѱ�� ���� ���� ������ �ϳ��� �������� �Ҵ� START
	phoneInfoArr = (PhoneInfo***)malloc(sizeof(PhoneInfo**));
	if (phoneInfoArr == NULL) {
		exit(-1);
	}
	//�ٸ� �޼ҵ�� �ѱ�� ���� ���� ������ �ϳ��� �������� �Ҵ� START

	//�迭�� �������� �Ҵ�(arrLen) START
	phoneInfoArr[0] = (PhoneInfo**)malloc(sizeof(PhoneInfo*) * arrLen);
	if (phoneInfoArr == NULL) {
		exit(-1);
	}
	//�迭�� �������� �Ҵ�(arrLen) END

	//����(arrLen)��ŭ ���鼭 PhoneInfo�� �� �ڸ��� �������� �Ҵ� ����
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

		phoneInfoArr[0][i]->numberInfoArr = (NumberInfo**)malloc(sizeof(NumberInfo*));//numberInfo���� �� NumberInfoArr �ڽ��� ����
		if (phoneInfoArr[0][i]->numberInfoArr == NULL) {
			free(phoneInfoArr[0][i]->numberInfoArr);
			exit(-1);
		}
		//��ȭ��ȣ �� �ڸ� �ϳ� ���� ������ֱ� START
		phoneInfoArr[0][i]->countNumInfo = 1;
		phoneInfoArr[0][i]->numberInfoArr[0] = (NumberInfo*)malloc(sizeof(NumberInfo));
		memset(phoneInfoArr[0][i]->numberInfoArr[0], 0, sizeof(NumberInfo));
		//��ȭ��ȣ �� �ڸ� �ϳ� ���� ������ֱ� END
	}
	//����(arrLen)��ŭ ���鼭 PhoneInfo�� �� �ڸ��� �������� �Ҵ� ����


	//������ �о ������ �Է� START
	fopen_s(&inputPhoneInfo, "PhoneBook.txt", "r");

	i = 0;
	while (i<arrCount){
		fgets(buffer, 1000, inputPhoneInfo);
		buffer[strlen(buffer) - 1] = '\0';

		//tab ������ ����� �� ��ҿ� ���� �� START
		strcpy(phoneInfoArr[0][i]->name, strtok_s(buffer, &criteria, &context));//ù ��° �ڸ�. �̸�
		strcpy(phoneInfoArr[0][i]->address, strtok_s(context, &criteria, &context));//�� ��° �ڸ�. �ּ�
		strcpy(phoneInfoArr[0][i]->birthday, strtok_s(context, &criteria, &context));//�� ��° �ڸ�. ����
		strcpy(phoneInfoArr[0][i]->memo, strtok_s(context, &criteria, &context));//�� ��° �ڸ�. �޸�
		
		phoneInfoArr[0][i]->countNumInfo = atoi(strtok_s(context, &criteria, &context));//�ټ� ��° �ڸ�. ��ȭ��ȣ �� ��?
		//tab ������ ����� �� ��ҿ� ���� �� END

		//NumberInfoArr���� NumberInfo�� countNumInfo��ŭ ���� ����
		for (j = 0; j < phoneInfoArr[0][i]->countNumInfo; j++) {
			phoneInfoArr[0][i]->numberInfoArr[j] = (NumberInfo*)malloc(sizeof(NumberInfo));
			memset(phoneInfoArr[0][i]->numberInfoArr[j], 0, sizeof(NumberInfo));
		}
		//NumberInfoArr���� NumberInfo�� countNumInfo��ŭ ���� ����

		//countNumInfo ��ŭ ���鼭 kindOfnumber�� phoneNumber�� ���� START
		for (j = 0; j < phoneInfoArr[0][i]->countNumInfo; j++) {
			strcpy(phoneInfoArr[0][i]->numberInfoArr[j]->kindOfNumber, strtok_s(context, &criteria, &context));//��ȭ��ȣ �̸� 
			strcpy(phoneInfoArr[0][i]->numberInfoArr[j]->phoneNumber, strtok_s(context, &criteria, &context));//��ȭ��ȣ
		}
		//countNumInfo ��ŭ ���鼭 kindOfnumber�� phoneNumber�� ���� END
		i++;
	}
	fclose(inputPhoneInfo);
	//������ �о ������ �Է� END

	//do-while ����
	do {
		
		viewPrintCommendNumber();//��ȣ�� �Է¹޴� �ؽ�Ʈ�� ����ϴ� �Լ�
		
		while (scanf_s("%d", &chooseNum) != 1) {
			c = getchar();
			system("cls");//�̰ɷ� ���� ���� �ذ�!!(�ݺ� ���)
			printf("\n���ڰ� �ƴմϴ�. �ٽ� �Է����ּ���.\n\n");
			viewPrintCommendNumber();
		}

		if (chooseNum == 1) {

			 //PhoneInfoArr�� ��������, �� �ø��� �ڵ� ����
			if (arrCount == arrLen) {

				arrLen += 3;
				phoneInfoArr[0] = (PhoneInfo**)realloc(phoneInfoArr, sizeof(PhoneInfo*)*arrLen);//�߰������� ���̸� 3�÷��� �������� ���Ҵ�

				if (phoneInfoArr == NULL) {
					exit(-1);
				}

				//������ŭ ���鼭 �߰��� �ڸ��� PhoneInfo�� �� �ڸ��� �������� �ٽ� �Ҵ� ����
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
				//������ŭ ���鼭 �߰��� �ڸ��� PhoneInfo�� �� �ڸ��� �������� �ٽ� �Ҵ� ����

			}
			//PhoneInfoArr�� ��������, �� �ø��� �ڵ� ����

			insertInfo(arrCount, phoneInfoArr);
			viewPrintSuccessInsert(phoneInfoArr[0], arrCount);//insert�� ���������� ���
			arrCount++;

		}else if (chooseNum == 2) {
			
			arrCount = deleteInfo(phoneInfoArr[0], arrLen, arrCount);

		}else if (chooseNum == 3) {

			searchInfo(phoneInfoArr[0], arrCount);
			viewPrintNextDoingText();//searching�� ��ġ�� ���� �ൿ�϶�� �κ��� ����Ʈ�ϴ� �Լ�

		}else if (chooseNum == 4) {

			printAll(phoneInfoArr[0], arrCount);

		}else if (chooseNum == 5) {
		}else {
			system("cls");
			printf("\n\n�߸��� ��ȣ�� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���.\n\n");

		}


	} while (chooseNum != 5);
	//do-while ����

	//�� �� ���� ��ȭ�� ������ ����Ǿ� �ִ����� ���� START
	fopen_s(&outputConfigInfo, "InformationOfPhoneBook.txt", "wt");
	fprintf_s(outputConfigInfo, "%d", arrCount);
	fclose(outputConfigInfo);
	//�� �� ���� ��ȭ�� ������ ����Ǿ� �ִ����� ���� END

	//�ּҷ� ������ ���Ͽ� �����ؼ� �ٽ� ����� START
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
	//�ּҷ� ������ ���Ͽ� �����ؼ� �ٽ� ����� END

	//������ ��� free ����
	for (i = 0; i < arrLen; i++) {
		for (j = 0; j < phoneInfoArr[0][i]->countNumInfo; j++) {
			free(phoneInfoArr[0][i]->numberInfoArr[j]);
		}
		free(phoneInfoArr[0][i]);

	}

	free(phoneInfoArr[0]);
	free(phoneInfoArr);
	//������ ��� free ����

	return 0;

}//Main �Լ� ����



void insertInfo(int takenArrCount, PhoneInfo ***phoneInfoArr) {

	int arrCount = takenArrCount;	
	int i;
	int j;
	int notNumFormat=0;
	int isNumFormatFlag = 0;//0�� false / 1�� true;
	int isBirthdayFormatFlag = 0; //0�� false / 1�� true;
	int isEndInputPhoneNumber = 0; //0�� �� / 1�� ���;
	int commendNum;

	printf("\n");
	printf("[�Է�]\n");

	//�̸� �Է� �κ�(�ʹ� ��� ����) START
	getchar();
	printf("�̸��� �Է��ϼ���: ");
	while (scanf_s("%[^\n]s", phoneInfoArr[0][arrCount]->name, sizeof(phoneInfoArr[0][arrCount]->name)) != 1) {
		printf("�ʹ� �� �̸��� �Է��ϼ̽��ϴ�. ���� 30��, �ѱ� 15�� �̳��� �Է����ּ���.\n");
		printf("�̸��� �Է��ϼ���: ");
	}
	//�̸� �Է� �κ�(�ʹ� ��� ����) END

	//�ּ� �Է� �κ�(�ʹ� ��� ����) START
	getchar();
	printf("�ּҸ� �Է��ϼ���: ");
	while (scanf_s("%[^\n]s", phoneInfoArr[0][arrCount]->address, sizeof(phoneInfoArr[0][arrCount]->address)) != 1) {
		printf("�ʹ� �� �ּҸ� �Է��ϼ̽��ϴ�. ���� 128��, �ѱ� 64�� �̳��� �Է����ּ���.\n");
		printf("�ּҸ� �Է��ϼ���: ");
	}
	//�ּ� �Է� �κ�(�ʹ� ��� ����) END


	//���� �Է� �� ��� �˻����ִ� �ڵ� START
	getchar();
	printf("������ �Է��ϼ���(0000-00-00 ������� �Է��ϼ���: ");
	while (isBirthdayFormatFlag != 1) {
		notNumFormat = 0;
		while (scanf_s("%s", phoneInfoArr[0][arrCount]->birthday, sizeof(phoneInfoArr[0][arrCount]->birthday)) != 1) {
			printf("�ʹ� ��� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���.\n");
			printf("������ �Է��ϼ���(0000-00-00 ������� �Է��ϼ���: ");
		}
		i = 0;
		while (phoneInfoArr[0][arrCount]->birthday[i] != '\0') {
			if ((phoneInfoArr[0][arrCount]->birthday[i]<48 || phoneInfoArr[0][arrCount]->birthday[i]>57)
				&& phoneInfoArr[0][arrCount]->birthday[i] != 45) {//�ƽ�Ű 48 ~ 57�� ����
				notNumFormat++;
			}
			i++;
		}
		//'-'�� ��Ȯ�� ��ġ�� ������ Ȯ���ϴ� �ڵ� START
		if (phoneInfoArr[0][arrCount]->birthday[4] != 45 || phoneInfoArr[0][arrCount]->birthday[7] != 45) {
			notNumFormat++;
		}
		//'-'�� ��Ȯ�� ��ġ�� ������ Ȯ���ϴ� �ڵ� END

		if (notNumFormat > 0) {
			printf("��Ȯ�� ����� �ƴմϴ�. �ٽ� �Է��ϼ���\n");
			printf("������ �Է��ϼ���(0000-00-00 ������� �Է��ϼ���: ");
		}else if (notNumFormat == 0) {
			isBirthdayFormatFlag = 1;
		}
	}
	//���� �Է� �� ��� �˻����ִ� �ڵ� END

	//�޸� �Է� �κ�(�ʹ� ��� ����) START
	getchar();
	printf("�޸� �Է��ϼ���: ");
	while (scanf_s("%[^\n]s", phoneInfoArr[0][arrCount]->memo, sizeof(phoneInfoArr[0][arrCount]->memo)) != 1) {
		printf("�ʹ� ��� �Է��ϼ̽��ϴ�. ���� 300��, �ѱ� 150�� �̳��� �Է����ּ���.\n");
		printf("�޸� �Է��ϼ���: ");
		while (scanf_s("%[^\n]s", phoneInfoArr[0][arrCount]->memo, sizeof(phoneInfoArr[0][arrCount]->memo)) != 1) {//�Է¹��۹��� �ذ�
			getchar();
		}
	}
	//�޸� �Է� �κ�(�ʹ� ��� ����) END


	phoneInfoArr[0][arrCount]->countNumInfo = 1;
	do {
		getchar();
		printf("\n%d��° ��ȭ��ȣ ������ �Է��մϴ�\n", (phoneInfoArr[0][arrCount]->countNumInfo));
		//��ȭ��ȣ ������ �Է��ϴ� �κ�(�ʹ� ��� ����) START
		printf("��� ��ȭ��ȣ�ΰ���?(����ȭ, ������ȭ, �޴���ȭ, �ѽ� ���): ");
		while (scanf_s("%[^\n]s", phoneInfoArr[0][arrCount]->numberInfoArr[(phoneInfoArr[0][arrCount]->countNumInfo)-1]->kindOfNumber,
			sizeof(phoneInfoArr[0][arrCount]->numberInfoArr[(phoneInfoArr[0][arrCount]->countNumInfo)-1]->kindOfNumber)) != 1) {
			printf("�ʹ� ��� �Է��ϼ̽��ϴ�. ���� 30��, �ѱ� 15�� �̳��� �Է����ּ���.\n");
			printf("��� ��ȭ��ȣ�ΰ���?(����ȭ, ������ȭ, �޴���ȭ, �ѽ� ���): ");
		}
		//��ȭ��ȣ ������ �Է��ϴ� �κ�(�ʹ� ��� ����) END
		
		//��ȭ��ȣ �Է� �� ����� �˻����ִ� �ڵ� START
		isNumFormatFlag = 0;
		printf("��ȭ��ȣ�� �Է��ϼ���(���ڿ� ��ȣ'-'�� �Է� �����մϴ�): ");
		while (isNumFormatFlag != 1) {

			notNumFormat = 0;
			getchar();
			while (scanf_s("%[^\n]s", phoneInfoArr[0][arrCount]->numberInfoArr[(phoneInfoArr[0][arrCount]->countNumInfo)-1]->phoneNumber,
				sizeof(phoneInfoArr[0][arrCount]->numberInfoArr[(phoneInfoArr[0][arrCount]->countNumInfo)-1]->phoneNumber)) != 1) {
				printf("�ʹ� �� ��ȭ��ȣ�� �Է��ϼ̽��ϴ�. 30�� �̳��� �Է����ּ���.\n");
				printf("��ȭ��ȣ�� �Է��ϼ���(���ڿ� ��ȣ'-'�� �Է� �����մϴ�): ");
			}

			i = 0;
			while (phoneInfoArr[0][arrCount]->numberInfoArr[(phoneInfoArr[0][arrCount]->countNumInfo)-1]->phoneNumber[i] != '\0') {
				if ((phoneInfoArr[0][arrCount]->numberInfoArr[(phoneInfoArr[0][arrCount]->countNumInfo)-1]->phoneNumber[i] < 48
					|| phoneInfoArr[0][arrCount]->numberInfoArr[(phoneInfoArr[0][arrCount]->countNumInfo)-1]->phoneNumber[i]>57)
					&& phoneInfoArr[0][arrCount]->numberInfoArr[(phoneInfoArr[0][arrCount]->countNumInfo)-1]->phoneNumber[i] != 45) {//�ƽ�Ű 48 ~ 57�� ����
					notNumFormat++;
				}
				i++;
			}

			if (notNumFormat > 0) {
				printf("���� Ȥ�� '-'�� �ƴմϴ�. �ٽ� �Է��ϼ���\n");
				printf("��ȭ��ȣ�� �Է��ϼ���(���ڿ� ��ȣ'-'�� �Է� �����մϴ�): ");
			}
			else if (notNumFormat == 0) {
				isNumFormatFlag = 1;
			}
		}
		//��ȭ��ȣ �Է� �� ����� �˻����ִ� �ڵ� END

		//commendNum �Է� START
		printf("\n[ ��ȭ��ȣ ��� �Է�  : 1 ]\n");
		printf("[ �׸� �Է�           : 2 ]\n �Է� : ");
		while (scanf_s("%d", &commendNum) != 1) {//�Է¹��۹��� �ذ�
			getchar();
		}

		while (commendNum != 1 && commendNum != 2) {
			printf("\n�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��ϼ���.");

			printf("\n[ ��ȭ��ȣ ��� �Է�  : 1 ]\n");
			printf("[ �׸� �Է�           : 2 ]\n �Է� : ");

			while (scanf_s("%d", &commendNum) != 1) {//�Է¹��۹��� �ذ�
				getchar();
			}
		}
		printf("\n");
		//commendNum �Է� END

		//��� �Է��̶�� realloc START
		if (commendNum == 1) {
			(phoneInfoArr[0][arrCount]->countNumInfo)++;
			//���� �͵��� �ӽ� ���� �޾Ƽ� �ְ�, ����� ���� �Ϳ� �����ϴ� ���
			phoneInfoArr[0][arrCount]->numberInfoArr = (NumberInfo**)realloc(phoneInfoArr[0][arrCount]->numberInfoArr,
				sizeof(NumberInfo*)*((phoneInfoArr[0][arrCount]->countNumInfo)));//�߰������� ���̸� �ϳ� �÷��� �������� ���Ҵ�

			if (phoneInfoArr[0][arrCount]->numberInfoArr == NULL) {
				exit(-1);
			}

			//������ŭ ���鼭 �߰��� �ڸ��� PhoneInfo�� �� �ڸ��� �������� �ٽ� �Ҵ� ����
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
			//������ŭ ���鼭 �߰��� �ڸ��� PhoneInfo�� �� �ڸ��� �������� �ٽ� �Ҵ� ����

			isEndInputPhoneNumber = 1;
		}
		//��� �Է��̶�� realloc END
		else {//0�̸� out!
			isEndInputPhoneNumber = 0;
		}

	} while (isEndInputPhoneNumber != 0);//0�� ��, 1�� ���

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
	int isNumFormatFlag = 0;//0�� false / 1�� true;

	printf("\n[ �̸����� ����  : 1]\n[ ��ȭ��ȣ�� ����: 2]\n �Է� : ");
	scanf_s("%d", &commendNum);

	while (commendNum != 1 && commendNum != 2) {
		printf("\n�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��ϼ���.");
		printf("\n[ �̸����� ����  : 1]\n[ ��ȭ��ȣ�� ����: 2]\n �Է� : ");

		while (scanf_s("%d", &commendNum) != 1) {//�Է¹��۹��� �ذ�
			getchar();
		}
	}

	if (commendNum == 1) {
		printf("������ ����� �̸��� �Է��ϼ���: ");

		//�̸��� �� �ԷµǾ����� �˻��ϴ� �κ� START
		while (scanf_s("%s", targetName, sizeof(targetName)) != 1) {

			printf("�ʹ� �� �̸��� �Է��ϼ̽��ϴ�. ���� 30��, �ѱ� 15�� �̳��� �Է����ּ���.\n");
			printf("Input Name: ");

		}
		//�̸��� �� �ԷµǾ����� �˻��ϴ� �κ� END

		while (compareNum != 0) {
			for (i = 0; i < arrCount; i++) {
				compareNum = strcmp(phoneInfoArr[i]->name, targetName);

				if (compareNum == 0) {
					//�ش� �ε��� �̻��� �͵��� �ҷ��ٰ�, �ش� �ε����� ������ arrCount �ϳ� ���� ����
					if (arrCount != 1) {//�� �ε����� 1�� �ƴϸ�.. �ֳĸ� �ε����� 1�ε� phoneInfoArr ���̰� 1�̸� �ַ��� ���� �����ϱ�(���� �ȳ��� ������ ���� ������ �������� ����)_���� �ַ� �ȳ��� ������ ���� �׳� �� �� ������
						for (j = i; j < arrLen; j++) {
							phoneInfoArr[j] = phoneInfoArr[j + 1];
						}
					}
					arrCount--;
					//�ش� �ε��� �̻��� �͵��� �ҷ��ٰ�, �ش� �ε����� ������ arrCount �ϳ� ���� ����
				}
			}

			//ã�Ƽ� ���������� �������� �Լ����� ���� ����
			if (compareNum == 0) {
				viewPrintSuccessDelete(targetName);//������ ����������, ����ϴ� �Լ�
				return arrCount;
			}
			//ã�Ƽ� ���������� �������� �Լ����� ���� ����

			printf("�ش��ϴ� �̸��� �����ϴ�. �ٽ� �Է����ּ���.\n");
			printf("(��ȣ'~'�� �Է��Ͻø� ����â���� ���ư��ϴ�)\n");
			printf("\n");
			printf("�Է�: ");
			scanf_s("%s", targetName, sizeof(targetName));

			if (strcmp(targetName, "~") == 0) {
				return;
			}

		}
	}
	else if (commendNum == 2) {
		printf("������ ����� ��ȭ��ȣ�� �Է��ϼ���(���ڿ� ��ȣ'-'�� �Է� �����մϴ�): ");

		//���� Ȥ�� '-'�� �Է��ϵ��� �����ϴ� �ڵ� ����
		while (isNumFormatFlag != 1) {
			notNumFormat = 0;
			while (scanf_s("%s", targetNumber, sizeof(targetNumber)) != 1) {
				printf("�ʹ� �� ��ȭ��ȣ�� �Է��ϼ̽��ϴ�. 30�� �̳��� �Է����ּ���.\n");
				printf("��ȭ��ȣ�� �Է��ϼ���(���ڿ� ��ȣ'-'�� �Է� �����մϴ�): ");
			}
			i = 0;
			while (targetNumber[i] != '\0') {
				if ((targetNumber[i]<48 || targetNumber[i]>57) && targetNumber[i] != 45) {//�ƽ�Ű 48 ~ 57�� ����
					notNumFormat++;
				}
				i++;
			}

			if (notNumFormat > 0) {
				printf("���� Ȥ�� '-'�� �ƴմϴ�. �ٽ� �Է��ϼ���\n");
				printf("��ȭ��ȣ�� �Է��ϼ���(���ڿ� ��ȣ'-'�� �Է� �����մϴ�): ");
			}
			else if (notNumFormat == 0) {
				isNumFormatFlag = 1;
			}
		}
		//���� Ȥ�� '-'�� �Է��ϵ��� �����ϴ� �ڵ� ����

		while (compareNum != 0) {
			for (i = 0; i < arrCount; i++) {
				for (j = 0; j < (phoneInfoArr[i]->countNumInfo)+1; j++) {
					compareNum = strcmp(phoneInfoArr[i]->numberInfoArr[j]->phoneNumber, targetNumber);
					if (compareNum == 0) {
						viewPrintSuccessDelete(phoneInfoArr[i]->name);//������ ����������, ����ϴ� �Լ�(���� �ϼ��ϱ� ����)
						//�ش� �ε��� �̻��� �͵��� �ҷ��ٰ�, �ش� �ε����� ������ arrCount �ϳ� ���� ����
						if (arrCount != 1) {//�� �ε����� 1�� �ƴϸ�.. �ֳĸ� �ε����� 1�ε� phoneInfoArr ���̰� 1�̸� �ַ��� ���� �����ϱ�(���� �ȳ��� ������ ���� ������ �������� ����)_���� �ַ� �ȳ��� ������ ���� �׳� �� �� ������
							for (k = i; k < arrLen; k++) {
								phoneInfoArr[k] = phoneInfoArr[k + 1];
							}
						}
						arrCount--;
						//�ش� �ε��� �̻��� �͵��� �ҷ��ٰ�, �ش� �ε����� ������ arrCount �ϳ� ���� ����
					}
				}
			}

			//ã�Ƽ� ���������� �������� �Լ����� ���� ����
			if (compareNum == 0) {
				return arrCount;
			}
			//ã�Ƽ� ���������� �������� �Լ����� ���� ����

			printf("�ش��ϴ� ��ȭ��ȣ�� �����ϴ�. �ٽ� �Է����ּ���.\n");
			printf("(��ȣ'~'�� �Է��Ͻø� ����â���� ���ư��ϴ�)\n");
			printf("\n");
			printf("�Է�: ");
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
	int isNumFormatFlag = 0;//0�� false / 1�� true;


	printf("\n[ �̸����� ã��  : 1]\n[ ��ȭ��ȣ�� ã��: 2]\n �Է� : ");
	getchar();
	scanf_s("%d", &commendNum);

	while (commendNum != 1 && commendNum != 2) {
		printf("\n�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��ϼ���.");
		printf("\n[ �̸����� ã��  : 1]\n[ ��ȭ��ȣ�� ã��: 2]\n �Է� : ");

		while (scanf_s("%d", &commendNum) != 1) {//�Է¹��� ���� �ذ�
			getchar();
		}
	}

	if (commendNum == 1) {

		printf("������ Ȯ���� ����� �̸��� �Է��ϼ���: ");
		getchar();
		//�̸��� �� �ԷµǾ����� �˻��ϴ� �κ� START
		while (scanf_s("%[^\n]s", targetName, sizeof(targetName)) != 1) {
			printf("�ʹ� �� �̸��� �Է��ϼ̽��ϴ�. ���� 30��, �ѱ� 15�� �̳��� �Է����ּ���.\n");
			printf("�̸��� �Է��ϼ���: ");
		}
		//�̸��� �� �ԷµǾ����� �˻��ϴ� �κ� END

		//compareNum�� 0�� �ƴϸ� ��� ���鼭 ���� �޾���� ��. �׸��� �߰��� ���������� �ڵ嵵 ��������� ����
		while (compareNum != 0) {
			for (i = 0; i < arrCount; i++) {
				compareNum = strcmp(phoneInfoArr[i]->name, targetName);

				if (compareNum == 0) {
					//���� ����� ������, �� �ε���(arrCount_���⼱ i)�� �������� ����
					system("cls");
					printf("\n");
					printf("*****************�˻� ���*****************\n");
					printf("\n");
					printf("  �̸�: %s\n", targetName);
					printf("  �ּ�: %s\n", phoneInfoArr[i]->address);
					printf("  ����: %s\n", phoneInfoArr[i]->birthday);
					printf("  �޸�: %s\n", phoneInfoArr[i]->memo);
					for (j = 0; j < (phoneInfoArr[i]->countNumInfo); j++) {
						printf("  %d��° ��ȭ��ȣ: %s [%s]\n", j+1, 
							phoneInfoArr[i]->numberInfoArr[j]->kindOfNumber, 
							phoneInfoArr[i]->numberInfoArr[j]->phoneNumber);
					}
					printf("\n");
					printf("*******************************************\n");
					return;
					//���� ����� ������, �� �ε���(arrCount_���⼱ i)�� �������� ����
				}
			}
//(���� ����) �����غ��� �� �ڵ尡 �ݺ���. �ϳ��� �Լ��� ������ ���� �� ����
			//������ ������ �Ͼ�� ������, �� ã�� ���̹Ƿ� �ٽ� �޾��ְų� �������� �� �ְ� ����� �� ����
			printf("\n");
			printf("�ش��ϴ� �̸��� �����ϴ�. �ٽ� �Է����ּ���.\n");
			printf("(��ȣ'~'�� �Է��Ͻø� ����â���� ���ư��ϴ�)\n");
			printf("\n");
			printf("�Է�: ");
			scanf_s("%s", targetName, sizeof(targetName));

			if (strcmp(targetName, "~") == 0) {
				return;
			}
			//������ ������ �Ͼ�� ������, �� ã�� ���̹Ƿ� �ٽ� �޾��ְų� �������� �� �ְ� ����� �� ����
//(���� ����) �����غ��� �� �ڵ尡 �ݺ���. �ϳ��� �Լ��� ������ ���� �� ����
		}
		//compareNum�� 0�� �ƴϸ� ��� ���鼭 ���� �޾���� ��. �׸��� �߰��� ���������� �ڵ嵵 ��������� ����

	}else if (commendNum == 2) {
		printf("ã�� ����� ��ȭ��ȣ�� �Է��ϼ���(Only Number or '-'): ");

		//���� Ȥ�� '-'�� �Է��ϵ��� �����ϴ� �ڵ� ����
		while (isNumFormatFlag != 1) {
			notNumFormat = 0;
			
			while (scanf_s("%s", targetNumber, sizeof(targetNumber)) != 1) {
				printf("�ʹ� �� ��ȭ��ȣ�� �Է��ϼ̽��ϴ�. 30�� �̳��� �Է����ּ���.\n");
				printf("ã�� ����� ��ȭ��ȣ�� �Է��ϼ���(Only Number or '-'): ");
			}
			i = 0;
			while (targetNumber[i] != '\0') {

				if ((targetNumber[i]<48 || targetNumber[i]>57) && targetNumber[i] != 45) {//�ƽ�Ű 48 ~ 57�� ����
					notNumFormat++;
				}
				i++;
			}

			if (notNumFormat > 0) {

				printf("���� Ȥ�� '-'�� �ƴմϴ�. �ٽ� �Է��ϼ���\n");
				printf("ã�� ����� ��ȭ��ȣ�� �Է��ϼ���(Only Number or '-'): ");

			}
			else if (notNumFormat == 0) {
				isNumFormatFlag = 1;
			}

		}
		//���� Ȥ�� '-'�� �Է��ϵ��� �����ϴ� �ڵ� ����


		//compareNum�� 0�� �ƴϸ� ��� ���鼭 ���� �޾���� ��. �׸��� �߰��� ���������� �ڵ嵵 ��������� ����
		while (compareNum != 0) {
			for (i = 0; i < arrCount; i++) {

				for (j = 0; j < (phoneInfoArr[i]->countNumInfo)+1; j++) {//�ش� �̸��� ��ȭ��ȣ���� ���鼭 ��
					compareNum = strcmp(phoneInfoArr[i]->numberInfoArr[j]->phoneNumber, targetNumber);
				}

				if (compareNum == 0) {//���ؼ� ã���� ������ �������
					system("cls");
					printf("\n");
					printf("*****************�˻� ���*****************\n");
					printf("\n");
					printf("  �̸�: %s\n", phoneInfoArr[i]->name);
					printf("  �ּ�: %s\n", phoneInfoArr[i]->address);
					printf("  ����: %s\n", phoneInfoArr[i]->birthday);
					printf("  �޸�: %s\n", phoneInfoArr[i]->memo);
					for (j = 0; j < (phoneInfoArr[i]->countNumInfo); j++) {
						printf("  %d��° ��ȭ��ȣ: %s [%s]\n", j + 1,
							phoneInfoArr[i]->numberInfoArr[j]->kindOfNumber,
							phoneInfoArr[i]->numberInfoArr[j]->phoneNumber);
					}
					printf("\n");
					printf("*******************************************\n");
					return;
				}
			}
			//(���� ����) �����غ��� �� �ڵ尡 �ݺ���. �ϳ��� �Լ��� ������ ���� �� ����
			//������ ������ �Ͼ�� ������, �� ã�� ���̹Ƿ� �ٽ� �޾��ְų� �������� �� �ְ� ����� �� ����
			printf("\n");
			printf("�ش��ϴ� ��ȭ��ȣ�� �����ϴ�. �ٽ� �Է����ּ���.\n");
			printf("(��ȣ'~'�� �Է��Ͻø� ����â���� ���ư��ϴ�)\n");
			printf("\n");
			printf("�Է�: ");
			scanf_s("%s", targetNumber, sizeof(targetNumber));

			if (strcmp(targetNumber, "~") == 0) {
				return;
			}
			//������ ������ �Ͼ�� ������, �� ã�� ���̹Ƿ� �ٽ� �޾��ְų� �������� �� �ְ� ����� �� ����
			//(���� ����) �����غ��� �� �ڵ尡 �ݺ���. �ϳ��� �Լ��� ������ ���� �� ����
		}
		//compareNum�� 0�� �ƴϸ� ��� ���鼭 ���� �޾���� ��. �׸��� �߰��� ���������� �ڵ嵵 ��������� ����
	}
}



void printAll(PhoneInfo **phoneInfoArr, int arrCount) {//��� ������ ���
	int i;
	int j;

	system("cls");//�ѹ� ����
	printf("*****************��°��******************\n");
	if (arrCount == 0) {
		printf("\n����� ����� �����ϴ�.\n");
	}else {
		for (i = 0; i < arrCount; i++) {
			printf("\n");
			printf("  �̸�: %s\n", phoneInfoArr[i]->name);
			printf("  �ּ�: %s\n", phoneInfoArr[i]->address);
			printf("  ����: %s\n", phoneInfoArr[i]->birthday);
			printf("  �޸�: %s\n", phoneInfoArr[i]->memo);
			for (j = 0; j < (phoneInfoArr[i]->countNumInfo); j++) {
				printf("  %d��° ��ȭ��ȣ: %s [%s]\n", j + 1,
					phoneInfoArr[i]->numberInfoArr[j]->kindOfNumber,
					phoneInfoArr[i]->numberInfoArr[j]->phoneNumber);
			}
		}
	}
	printf("\n*******************************************\n");
	printf("\n");

}



void viewPrintCommendNumber() {

	printf("====================�޴�===================\n\n");
	printf("1. ��ȭ��ȣ �Է� \n");
	printf("2. ���� ���� \n");
	printf("3. ���� ã�� \n");
	printf("4. ��� ���� ���� \n");
	printf("5. ������\n\n");
	printf("===========================================\n\n");

	printf("��ȣ�� �Է����ּ���: ");

}

void viewPrintSuccessInsert(PhoneInfo **phoneInfoArr, int arrCount) {

	int j;
	system("cls");
	printf("********************����*******************\n\n");
	printf("  �̸�: %s\n", phoneInfoArr[arrCount]->name);
	printf("  �ּ�: %s\n", phoneInfoArr[arrCount]->address);
	printf("  ����: %s\n", phoneInfoArr[arrCount]->birthday);
	printf("  �޸�: %s\n", phoneInfoArr[arrCount]->memo);
	for (j = 0; j < (phoneInfoArr[arrCount]->countNumInfo); j++) {
		printf("  %d��° ��ȭ��ȣ: %s [%s]\n", j + 1,
			phoneInfoArr[arrCount]->numberInfoArr[j]->kindOfNumber,
			phoneInfoArr[arrCount]->numberInfoArr[j]->phoneNumber);
	}
	printf(" ���� �� ���� �Է��ϼ���.\n\n");
	printf("*******************************************\n\n");

}

void viewPrintSuccessDelete(char targetName[30]) {

	system("cls");
	printf("********************����*******************\n\n");
	printf("   [%s]��(��) ���������� �����Ͽ����ϴ�.\n", targetName);
	printf("   ���� �� ���� �Է��ϼ���.\n\n");
	printf("*******************************************\n\n");

}


void viewPrintNextDoingText() {
	printf("\n*******************************************\n");
	printf("          ���� �� ���� �Է��ϼ���.\n");
	printf("*******************************************\n\n");
}


//�ɴ浵,�������bug[����ͣ�ù���],ԭ�����:1.�ļ��������� 2.�ַ����벻��
//����Ч��������,׼������ʵ��������[�漰��������򷽷�],�鲢�����


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

typedef struct Student {
	char m_name[20];         //����
	char m_number[20];       //ѧ��
	int m_ChineseScore;      //���ĳɼ�
	int m_MathScore;         //��ѧ�ɼ�
	int m_EnglishScore;      //Ӣ��ɼ�
	int m_programScore;      //������Ƴɼ�
	int m_totalScore;        //�ܷ�
	bool m_qualifiedScore;   //�����ϸ�(�������Ŀ����2�Ƽ�Ϊ���ϸ�)

	struct Student* next;    //ָ����
}S;

//��ҳ
void home_page()
{

	system("cls");

	printf("|---------------------------|\n");
	printf("|    DLNU�ɼ�����ϵͳ1.0    |\n");
	printf("|---------------------------|\n");
	printf("|       1.¼����Ϣ          |\n");
	printf("|       2.�޸���Ϣ          |\n");
	printf("|       3.ɾ��ѧ��          |\n");
	printf("|       4.��ѯ������Ϣ      |\n");
	printf("|       5.��ʾ������Ϣ      |\n");
	printf("|       6.�浵              |\n");
	printf("|---------------------------|\n");
	printf("  ��ǰϵͳ�ڹ���%d��ѧ�� \n");
	printf("------------------------------------\n");
	printf("| <����1-6 ѡ����,�����������˳�> |\n");
	printf("|    ע��: Ϊ��ֹ���ݶ�ʧ,          |\n");
	printf("|  ÿ���˳�ϵͳǰ����ش浵!        |\n");
	printf("------------------------------------\n");
}
//¼����Ϣ
S* Input_score();
//�жϷ����Ƿ�ϸ�
void Judge_score(S* student);
//β���ڵ�����
void Tail_add_node(S* head, S* new1);
//�ĳɼ�
void Change_score(S* student);
//�޸���Ϣ
void Change_information(S* head);
//�޸���Ϣѡ��
void Change_information_selection(S* student);
//ɾ��ѧ��
void Delete_student(S* head);
//��ѯ������Ϣ
void Search_student(S* head);
//��ѯ������Ϣѡ��[�ɼ�or����orѧ��]
void Search_student_option(S* head, S* student);
//��ѯ���˷���
void Search_score(S* student);
void Search_Chinese_rank(S* head, S* student);
void Search_Math_rank(S* head, S* student);
void Search_English_rank(S* head, S* student);
void Search_Program_rank(S* head, S* student);
void Search_totalscore_rank(S* head, S* student);
//��ѯ��������
void Search_score_rank(S* head, S* student);
//��ʾ������Ϣ(���ϸ�ѧ��orȫ��ѧ��)
void Show_all(S* head);
//��ʾ���в��ϸ��ѧ��
void Show_all_unqualified_student(S* head);
//��ʾȫ��ѧ��
void Show_all_student(S* head);
//��������
void Load_data(S* head);
//���ݴ浵
void Archive_data(S* head);

int main()
{
	S* head = (S*)malloc(sizeof(S));
	memset(head, 0, sizeof(S));
	head->next = NULL;

	//Load_data(head);

	int select = 0;
	while (1)
	{
		int N = 0;
		home_page();

		scanf("%d", &select);
		if (!(select >= 1 && select <= 6)) {
			break;
		}
		switch (select)
		{
		case 1://¼��ɼ���
			printf("�������㱾����¼��ɼ�������:\n");
			scanf("%d", &N);
			for (int i = 0; i < N; i++)
			{
				system("cls");
				Tail_add_node(head, Input_score());
				printf("¼��ɹ�!\n");
				getchar();
			}
			break;
		case 2://�޸���Ϣ
			Change_information(head);
			getchar();
			break;
		case 3://ɾ��ѧ����
			printf("����ɾ������ѧ��:");
			int deleteNumber;
			scanf("%d", &deleteNumber);
			for (int i = 0; i < deleteNumber; i++)
			{
				Delete_student(head);
			}
			getchar();
			break;
		case 4://��ѯ������Ϣ��
			Search_student(head);
			getchar();
			break;
		case 5://��ʾ������Ϣ
			Show_all(head);
			getchar();
			break;
		case 6:
			Archive_data(head);
			break;
		default:
			break;
		}
	}

	free(head);
	return 0;
}


//¼����Ϣ
S* Input_score()
{
	S* newStudent = (S*)malloc(sizeof(S));
	memset(newStudent, 0, sizeof(S));
	newStudent->next = NULL;
	printf("����:");
	scanf("%s", newStudent->m_name);
	printf("ѧ��:");
	scanf("%s", newStudent->m_number);
	printf("���ĳɼ�:");
	scanf("%d", &newStudent->m_ChineseScore);
	printf("��ѧ�ɼ�:");
	scanf("%d", &newStudent->m_MathScore);
	printf("Ӣ��ɼ�:");
	scanf("%d", &newStudent->m_EnglishScore);
	printf("����ɼ�:");
	scanf("%d", &newStudent->m_programScore);
	newStudent->m_totalScore = newStudent->m_ChineseScore + newStudent->m_MathScore + newStudent->m_EnglishScore + newStudent->m_programScore;
	Judge_score(newStudent);
	getchar();

	return newStudent;
}
//�жϷ����Ƿ�ϸ�
void Judge_score(S* student)
{
	int cnt = 0;
	cnt = (student->m_ChineseScore < 60) + (student->m_MathScore < 60)\
		+ (student->m_EnglishScore < 60) + (student->m_programScore < 60);
	if (cnt > 2)
		student->m_qualifiedScore = false;
	else
		student->m_qualifiedScore = true;
}
//β���ڵ�����
void Tail_add_node(S* head, S* new1)
{
	S* a = head;
	while (NULL != a->next)
	{
		a = a->next;
	}
	a->next = new1;
}
//�ĳɼ�
void Change_score(S* student)
{
	int ret;
	printf("%s", student->m_name);
	printf("���ĳɼ�:%d ,�Ƿ�Ҫ�޸�?\n[0-��;1-��]", student->m_ChineseScore);
	scanf("%d", &ret);
	while (ret)
	{
		printf("��Ϊ:");
		scanf("%d", &student->m_ChineseScore);
		ret = 0;
	}
	printf("��ѧ�ɼ�:%d ,�Ƿ�Ҫ�޸�?\n[0-��;1-��]", student->m_MathScore);
	scanf("%d", &ret);
	while (ret)
	{
		printf("��Ϊ:");
		scanf("%d", &student->m_MathScore);
		ret = 0;
	}
	printf("Ӣ��ɼ�:%d ,�Ƿ�Ҫ�޸�?\n[0-��;1-��]", student->m_EnglishScore);
	scanf("%d", &ret);
	while (ret)
	{
		printf("��Ϊ:");
		scanf("%d", &student->m_EnglishScore);
		ret = 0;
	}
	printf("����ɼ�:%d ,�Ƿ�Ҫ�޸�?\n[0-��;1-��]", student->m_programScore);
	scanf("%d", &ret);
	while (ret)
	{
		printf("��Ϊ:");
		scanf("%d", &student->m_programScore);
		ret = 0;
	}
	student->m_totalScore = student->m_ChineseScore + student->m_MathScore + student->m_EnglishScore + student->m_programScore;
	return;
}
//�޸���Ϣ
void Change_information(S* head) {
	int select;
	S* a = head;
	printf("����ͨ������/ѧ���޸�ѧ����Ϣ:[1--����/2--ѧ��]");
	scanf("%d", &select);
	getchar();
	switch (select)
	{
	case 1://ͨ��������
		char name[20];
		printf("����:");
		scanf("%s", name);
		while (NULL != a->next)
		{
			a = a->next;
			if (!strcmp(name, a->m_name))
			{
				Change_information_selection(a);
				return;
			}
		}
		break;
	case 2://ͨ��ѧ����
		char number[20];
		printf("ѧ��:");
		scanf("%s", number);
		while (NULL != a->next)
		{
			a = a->next;
			if (!strcmp(number, a->m_number))
			{
				Change_information_selection(a);
				return;
			}
		}
		break;

	default:
		break;
	}
	printf("δ�ҵ���ѧ��,�޸Ĳ�����Ч\n");
	getchar();
}
//�޸���Ϣѡ��
void Change_information_selection(S* student)
{
	printf("�����޸ĸ�ͬѧ����һ����Ϣ:\n");
	printf(" __________\n");
	printf("|1.����    |\n");
	printf("|2.ѧ��    |\n");
	printf("|3.�ɼ�    |\n");
	printf("|__________|\n");

	int select;
	scanf("%d", &select);
	switch (select)
	{
	case 1:
		printf("ԭ����%s,��Ϊ:", student->m_name);
		char newName[20];
		scanf("%s", newName);
		strcpy(student->m_name, newName);
		getchar();
		break;
	case 2:
		printf("ԭѧ��%s,��Ϊ:", student->m_number);
		char newNumber[20];
		scanf("%s", newNumber);
		strcpy(student->m_number, newNumber);
		getchar();
		break;
	case 3:
		Change_score(student);
		break;
	default:
		break;
	}
	printf("�޸ĳɹ�.\n");
	return;
}
//ɾ��ѧ��
void Delete_student(S* head)
{
	int select;
	S* a = head;
	S* prev = NULL;//�Ժ������ʱ��,���ڱ���ָ��a��ǰһλ
	printf("����ͨ������/ѧ��ɾ��ѧ��:[1--����/2--ѧ��]");
	scanf("%d", &select);
	switch (select)
	{
	case 1:
		char name[20];
		printf("����:");
		scanf("%s", name);
		while (NULL != a->next)
		{
			prev = a;
			a = a->next;
			if (!strcmp(name, a->m_name))
			{
				prev->next = a->next;
				printf("ɾ���ɹ�!");
				getchar();
				return;
			}
		}
		break;
	case 2:
		char number[20];
		printf("ѧ��:");
		scanf("%s", number);
		while (NULL != a->next)
		{
			a = a->next;
			if (!strcmp(number, a->m_number))
			{
				prev->next = a->next;
				printf("ɾ���ɹ�!");
				getchar();
				return;
			}
		}
		break;

	default:
		break;
	}
	printf("δ�ҵ���ѧ��,ɾ��������Ч\n");
	getchar();
}

//��ѯ������Ϣ(ѧ��/���ֲ���ѧ��)
void Search_student(S* head)
{
	int selectWay;//���ҷ�ʽ
	int selectWhat;//��ѯ������
	int ret = 1;//�ж�ѧ���Ƿ����
	S* a = head;
	printf("����ͨ������/ѧ�Ų���ѧ��:[1--����/2--ѧ��]");
	scanf("%d", &selectWay);
	getchar();
	switch (selectWay)
	{
	case 1:
		char name[20];
		printf("����:");
		scanf("%s", name);
		while (NULL != a->next)
		{
			a = a->next;
			if (!strcmp(name, a->m_name))
			{
				Search_student_option(head, a);
				ret = 0;
				break;
			}
		}
		break;
	case 2:
		char number[20];
		printf("ѧ��:");
		scanf("%s", number);
		while (NULL != a->next)
		{
			a = a->next;
			if (!strcmp(number, a->m_number))
			{
				Search_student_option(head, a);
				ret = 0;
				break;
			}
		}
		break;
	default:
		break;
	}
	if (ret)
	{
		printf("δ�ҵ���ѧ��\n");
		getchar();
	}

}
//��ѯ������Ϣѡ��[�ɼ�or����orѧ��]
void Search_student_option(S* head, S* student)
{
	int selectOption;
	int select = 1;
	while (select) {
		printf("�����ѯ%s��\n", student->m_name);
		printf("---------------\n");
		printf("|  1.�ɼ�      |\n");
		printf("|  2.����      |\n");
		printf("|  3.ѧ��      |\n");
		printf("---------------\n");
		scanf("%d", &selectOption);
		getchar();
		switch (selectOption)
		{
		case 1:
			Search_score(student);
			break;
		case 2:
			Search_score_rank(head, student);
			break;
		case 3:
			printf("%s��ѧ��Ϊ%s\n", student->m_name, student->m_number);
			break;
		default:
			printf("����!");
			getchar();
			break;
		}
		printf("���ʻ�Ҫ������ѯ��ͬѧ����Ϣ��?[1-��  0-��]\n");
		scanf("%d", &select);
	}
}
//��ѯ���˷���
void Search_score(S* student)
{
	system("cls");
	printf("����:%s\n", student->m_name);
	printf("ѧ��:%s\n", student->m_number);
	printf("����:%d\n", student->m_ChineseScore);
	printf("��ѧ:%d\n", student->m_MathScore);
	printf("Ӣ��:%d\n", student->m_EnglishScore);
	printf("����:%d\n", student->m_programScore);
	printf("�ܷ�:%d\n", student->m_totalScore);
}
void Search_Chinese_rank(S* head, S* student) {
	S* a = head;
	int rank = 1;
	while (NULL != a->next) {
		a = a->next;
		if (a->m_ChineseScore > student->m_ChineseScore)
			rank++;
	}
	printf("%s�����ķ���Ϊ:%d,����Ϊ:%d", student->m_name, student->m_ChineseScore, rank);
	getchar();
}
void Search_Math_rank(S* head, S* student) {
	S* a = head;
	int rank = 1;
	while (NULL != a->next) {
		a = a->next;
		if (a->m_MathScore > student->m_MathScore)
			rank++;
	}
	printf("%s����ѧ����Ϊ:%d,����Ϊ:%d", student->m_name, student->m_MathScore, rank);
	getchar();
}
void Search_English_rank(S* head, S* student) {
	S* a = head;
	int rank = 1;
	while (NULL != a->next) {
		a = a->next;
		if (a->m_EnglishScore > student->m_EnglishScore)
			rank++;
	}
	printf("%s��Ӣ�����Ϊ:%d,����Ϊ:%d", student->m_name, student->m_EnglishScore, rank);
	getchar();
}
void Search_Program_rank(S* head, S* student) {
	S* a = head;
	int rank = 1;
	while (NULL != a->next) {
		a = a->next;
		if (a->m_programScore > student->m_programScore)
			rank++;
	}
	printf("%s�ĳ������Ϊ:%d,����Ϊ:%d", student->m_name, student->m_programScore, rank);
	getchar();
}
void Search_totalscore_rank(S* head, S* student) {
	S* a = head;
	int rank = 1;
	while (NULL != a->next) {
		a = a->next;
		if (a->m_totalScore > student->m_totalScore)
			rank++;
	}
	printf("%s���ܷ�Ϊ:%d,����Ϊ:%d", student->m_name, student->m_totalScore, rank);
	getchar();
}

//��ѯ��������
void Search_score_rank(S* head, S* student)
{
	int select_subject;
	S* a = head;

	int select = 1;
	while (select) {
		printf("�����ѯ���ŵĳɼ�����:\n");
		printf("1.���� 2.��ѧ 3.Ӣ�� 4.���� 5.�ܷ� 6.�˳�\n");
		scanf("%d", &select_subject);
		getchar();
		switch (select_subject)
		{
		case 1:
			Search_Chinese_rank(head, student);
			break;
		case 2:
			Search_Math_rank(head, student);
			break;
		case 3:
			Search_English_rank(head, student);
			break;
		case 4:
			Search_Program_rank(head, student);
			break;
		case 5:
			Search_totalscore_rank(head, student);
			break;
		default:
			break;
		}
		printf("���ʻ�Ҫ������ѯ��ͬѧ�ĳɼ�������?[1-��  0-��]\n");
		scanf("%d", &select);
	}

}
//��ʾ������Ϣ(���ϸ�ѧ��orȫ��ѧ��)
void Show_all(S* head)
{
	printf(" _______________________________________\n");
	printf("| 1.���в��ϸ��ѧ��(�������Ŀ����2��)\t|\n");
	printf("| 2.ȫ��ѧ��\t\t\t\t|\n");
	printf("| 3.����\t\t\t\t|\n");
	printf(" ---------------------------------------\n");

	int select;
	scanf("%d", &select);

	switch (select)
	{
	case 1:
		Show_all_unqualified_student(head);
		break;
	case 2:
		Show_all_student(head);
		break;
	default:
		break;
	}
}
//��ʾ���в��ϸ��ѧ��
void Show_all_unqualified_student(S* head)
{
	system("cls");
	S* a = head;
	printf("--------------------------------------------------------------------------------------------\n");
	printf("    ѧ��    |    ����    |    ����    |    ��ѧ    |    Ӣ��    |    ����    |    �ܳɼ�    |\n");
	printf("------------+------------+------------+------------+------------+------------+--------------\n");
	while (NULL != a->next)
	{
		a = a->next;
		if (!a->m_qualifiedScore)
		{
			printf("------------+------------+------------+------------+------------+------------+--------------\n");
			printf("%11s |%11s |%11d |%11d |%11d |%11d |%11d   |\n", a->m_number, a->m_name, a->m_ChineseScore, a->m_MathScore, a->m_EnglishScore, a->m_programScore, a->m_totalScore);
		}
	}
	printf("--------------------------------------------------------------------------------------------\n");
	getchar();
}
//��ʾȫ��ѧ��
void Show_all_student(S* head)
{
	system("cls");
	S* a = head;
	printf("--------------------------------------------------------------------------------------------\n");
	printf("    ѧ��    |    ����    |    ����    |    ��ѧ    |    Ӣ��    |    ����    |    �ܳɼ�    |\n");
	printf("------------+------------+------------+------------+------------+------------+--------------\n");
	while (NULL != a->next)
	{
		a = a->next;
		printf("------------+------------+------------+------------+------------+------------+--------------\n");
		printf("%11s |%11s |%11d |%11d |%11d |%11d |%11d   |\n", a->m_number, a->m_name, a->m_ChineseScore, a->m_MathScore, a->m_EnglishScore, a->m_programScore, a->m_totalScore);
	}
	printf("--------------------------------------------------------------------------------------------\n");
	getchar();
}
//��������
void Load_data(S* head)
{
	FILE* fp = fopen("student.txt", "r");
	if (fp == NULL)
	{
		fp = fopen("student.txt", "w");
	}

	S* newStudent = (S*)malloc(sizeof(S));
	memset(newStudent, 0, sizeof(S));
	newStudent->next = NULL;
	while (fscanf(fp, "%s\t%s\t%d\t%d\t%d\t%d\t%d\n", \
		newStudent->m_name, newStudent->m_number, \
		& newStudent->m_ChineseScore, &newStudent->m_MathScore, \
		& newStudent->m_EnglishScore, &newStudent->m_programScore, \
		& newStudent->m_totalScore, &newStudent->m_totalScore) != EOF)
	{
		Tail_add_node(head, newStudent);
		memset(newStudent, 0, sizeof(newStudent));
	}
	free(newStudent);
	printf("�������!");
	getchar();

	fclose(fp);
}
//���ݴ浵
void Archive_data(S* head)
{
	FILE* fp;
	S* a = head;
	if ((fp = fopen("student.txt", "w+")) == NULL)
	{
		printf("�浵ʧ�ܣ�");
	}
	else
	{
		while (NULL != a->next)
		{
			a = a->next;
			fprintf(fp, "%s\t%s\t%d\t%d\t%d\t%d\t%d\n", a->m_name, a->m_number, a->m_ChineseScore, a->m_MathScore, a->m_EnglishScore, a->m_programScore, a->m_totalScore, a->m_totalScore);
		}
	}

	printf("�浵�ɹ�");
	getchar();
	getchar();
	fclose(fp);
}

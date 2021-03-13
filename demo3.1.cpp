//����3.0�汾������ʱ�Ĵ�ƪ�����ƴ��� 

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <windows.h>

typedef struct Student {
	char m_name[20];         //����
	char m_number[20];       //ѧ��
	int m_ChineseScore;      //���ĳɼ�
	int m_MathScore;         //��ѧ�ɼ�
	int m_EnglishScore;      //Ӣ��ɼ�
	int m_programScore;      //������Ƴɼ�
	int m_totalScore;        //�ܷ�
	int m_rankScore;         //�������������м���� 
	bool m_qualifiedScore;   //�����ϸ�(�������Ŀ����2�Ƽ�Ϊ���ϸ�)

	struct Student* next;    //ָ����
}S;

//��ҳ
void home_page()
{
	system("cls");

	printf("|---------------------------|\n");
	printf("|    DLNU�ɼ�����ϵͳ3.0    |\n");
	printf("|---------------------------|\n");
	printf("|       1.¼����Ϣ          |\n");
	printf("|       2.�޸���Ϣ          |\n");
	printf("|       3.ɾ��ѧ��          |\n");
	printf("|       4.��ѯ������Ϣ      |\n");
	printf("|       5.��ѯ��������      |\n");
	printf("|       6.��ʾ������Ϣ      |\n");
	printf("|       7.�˳�              |\n");
	printf(" ---------------------------\n");
	printf(" -----------------------------------\n");
	printf("|   ע��:  1.�ɼ���Ϊ����           |\n");
	printf("|         2.ѧ�Ų�����ʮλ          |\n");
	printf("|  3.�������˳�����������ݴ浵ʧ�� |\n");
	printf(" -----------------------------------\n");
}
//1.¼����Ϣ
S* Input_new_student();
//1...�жϷ����Ƿ�ϸ�
void Judge_score(S* student);
//1...�ڵ�����(β��)
void Tail_add_node(S* head, S* new1);//Ϊ��Ҫ��ͷָ�� 

//2.�޸���Ϣ[by:����/ѧ��]
void Change_information(S* head);
//2...�޸���Ϣѡ��
void Change_information_selection(S* student);
//2-3.�ĳɼ�
void Change_score(S* student);

//3.ɾ��ѧ��
void Delete_student(S* head);

//4.��ѯ������Ϣ[by:����/ѧ��]
void Search_student(S* head);
//4...��ѯ������Ϣѡ��
void Search_student_option(S* head, S* student);
//4...��ѯ���˷���
void Search_score(S* student);

//5.��������ѡ�� 
void Rank_kindSelect(S* head);
//5...����
void Rank_byScore(S* head);

//6.��ʾ������Ϣ(���ϸ�ѧ��orȫ��ѧ��)
void Show_all(S* head);
//6-1.���в��ϸ��ѧ��
void Show_all_unqualified_student(S* head);
//6-2.ȫ��ѧ��
void Show_all_student(S* head);

//��������
void Load_data(S* head);
//7.���ݴ浵
void Save_data(S* head);

int main()
{
	S* head = (S*)malloc(sizeof(S));
	memset(head, 0, sizeof(S));
	head->next = NULL;

	Load_data(head);//�������� 

	int select = 0;
	while (1)
	{
		int N = 0;
		home_page();

		scanf("%d", &select);
		if (!(select >= 1 && select <= 6)) {
			Save_data(head);//�浵 
			break;
		}
		switch (select)
		{
		case 1://¼����Ϣ
			printf("�������㱾����¼��ɼ�������:\n");
			scanf("%d", &N);
			for (int i = 0; i < N; i++)
			{
				system("cls");
				Tail_add_node(head, Input_new_student());
				printf("¼��ɹ�!\n");
				getchar();
			}
			break;
		case 2://�޸���Ϣ
			Change_information(head);
			getchar();
			break;
		case 3://ɾ��ѧ��
			printf("����ɾ������ѧ��:");
			int deleteNumber;
			scanf("%d", &deleteNumber);
			for (int i = 0; i < deleteNumber; i++)
			{
				Delete_student(head);
			}
			getchar();
			break;
		case 4://��ѯ������Ϣ
			Search_student(head);
			getchar();
			break;
		case 5://��ѯ��������
			Rank_kindSelect(head);
			getchar();
			break;
		case 6://��ʾ������Ϣ
			Show_all(head);
			getchar();
			break;
		default:
			break;
		}
	}

	free(head);
	return 0;
}


//1.¼����Ϣ
S* Input_new_student()
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
	newStudent->m_rankScore = 0;

	Judge_score(newStudent);//�жϺϸ���� 
	getchar();

	return newStudent;
}
//1...�жϷ����Ƿ�ϸ�
void Judge_score(S* student)
{
	int cnt = 0;//���ϸ��Ŀ������ 
	cnt = (student->m_ChineseScore < 60) + (student->m_MathScore < 60)\
		+ (student->m_EnglishScore < 60) + (student->m_programScore < 60);
	if (cnt > 2)
		student->m_qualifiedScore = false;
	else
		student->m_qualifiedScore = true;
}
//1...�ڵ�����(β��)
void Tail_add_node(S* head, S* new1)
{
	S* a = head;
	while (NULL != a->next)
	{
		a = a->next;
	}
	a->next = new1;
}

//2.�޸���Ϣ(�ҵ���Ӧ��ѧ��by:����/ѧ��)
void Change_information(S* head) {
	int selectWay;//���ҷ�ʽ 
	S* a = head;
	printf("����ͨ������/ѧ���޸�ѧ����Ϣ:[1--����/2--ѧ��]");
	scanf("%d", &selectWay);
	getchar();
	switch (selectWay)
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
//2...�޸���Ϣѡ��
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
	getchar();
	return;
}
//2-3.�ĳɼ�
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

//3.ɾ��ѧ��
void Delete_student(S* head)
{
	int selectWay;
	S* a = head;
	S* prev = NULL;//�Ժ������ʱ��,���ڱ���ָ��a��ǰһλ
	printf("����ͨ������/ѧ��ɾ��ѧ��:[1--����/2--ѧ��]");
	scanf("%d", &selectWay);
	switch (selectWay)
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

//4.��ѯ������Ϣ[by:����/ѧ��]
void Search_student(S* head)
{
	int selectWay;//���ҷ�ʽ
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
//4...��ѯ������Ϣѡ��
void Search_student_option(S* head, S* student)
{
	int selectOption;//��ѯ������ 
	int ifSelect = 1;//�Ƿ���� 

	while (ifSelect) {
		printf("�����ѯ%s��\n", student->m_name);
		printf("---------------\n");
		printf("|  1.�ɼ�      |\n");
		printf("|  2.ѧ��      |\n");
		printf("---------------\n");

		scanf("%d", &selectOption);
		getchar();
		switch (selectOption)
		{
		case 1:
			Search_score(student);
			break;
		case 2:
			printf("%s��ѧ��Ϊ%s\n", student->m_name, student->m_number);
			break;
		default:
			printf("����!");
			getchar();
			break;
		}
		printf("���ʻ�Ҫ������ѯ��ͬѧ����Ϣ��?[1-��  0-��]\n");
		scanf("%d", &ifSelect);
	}
}
//4...��ѯ���˷���
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

//5.��������ѡ�� 
void Rank_kindSelect(S* head)
{
	int select_subject = 0;
	int ifSelect = 1;

	while (ifSelect) {
		S* a = head;

		printf("���밴���ŵĳɼ�����:\n");
		printf("1.���� 2.��ѧ 3.Ӣ�� 4.���� 5.�ܷ� 6.�˳�\n");
		scanf("%d", &select_subject);
		getchar();
		switch (select_subject)
		{
		case 1://����������
			while (a->next)
			{
				a = a->next;
				a->m_rankScore = a->m_ChineseScore;
			}
			printf("----------------------------------------------------\n");
			printf("    ѧ��    |    ����    |  ���ĳɼ�  |  ��������  |\n");
			printf("------------+------------+------------+-------------\n");

			Rank_byScore(head);
			break;
		case 2://����ѧ����
			while (a->next)
			{
				a = a->next;
				a->m_rankScore = a->m_MathScore;
			}
			printf("----------------------------------------------------\n");
			printf("    ѧ��    |    ����    |  ��ѧ�ɼ�  |  ��ѧ����  |\n");
			printf("------------+------------+------------+-------------\n");

			Rank_byScore(head);
			break;
		case 3://��Ӣ������
			while (a->next)
			{
				a = a->next;
				a->m_rankScore = a->m_EnglishScore;
			}
			printf("----------------------------------------------------\n");
			printf("    ѧ��    |    ����    |  Ӣ��ɼ�  |  Ӣ������  |\n");
			printf("------------+------------+------------+-------------\n");

			Rank_byScore(head);
			break;
		case 4://����������
			while (a->next)
			{
				a = a->next;
				a->m_rankScore = a->m_programScore;
			}
			printf("----------------------------------------------------\n");
			printf("    ѧ��    |    ����    |  ����ɼ�  |  ��������  |\n");
			printf("------------+------------+------------+-------------\n");

			Rank_byScore(head);
			break;
		case 5://���ܷ�����
			while (a->next)
			{
				a = a->next;
				a->m_rankScore = a->m_totalScore;
			}
			printf("----------------------------------------------------\n");
			printf("    ѧ��    |    ����    |    �ܷ�    |  �ܷ�����  |\n");
			printf("------------+------------+------------+-------------\n");

			Rank_byScore(head);
			break;
		default:
			break;
		}
		printf("���ʻ�Ҫ��ѯ������Ŀ�ĳɼ�������?[1-��  0-��]\n");
		scanf("%d", &ifSelect);
	}
}
//5...����
void Rank_byScore(S* head)
{
	S* p = head->next->next;
	S* q = NULL;
	S* pre = NULL;
	head->next->next = NULL;
	//ֱ�巨����
	while (p)
	{
		q = p->next;
		pre = head;
		while (pre->next != NULL && pre->next->m_rankScore > p->m_rankScore)
		{
			pre = pre->next;
		}
		p->next = pre->next;
		pre->next = p;
		p = q;
	}
	//����
	S* a = head;
	int scoreRank = 1;
	while (NULL != a->next)
	{
		a = a->next;
		printf("------------+------------+------------+-------------\n");
		printf("%11s |%11s |%11d |%11d |\n", a->m_number, a->m_name, a->m_rankScore, scoreRank);
		scoreRank++;
	}
	printf("----------------------------------------------------\n");
	getchar();
}

//6.��ʾ������Ϣ(���ϸ�ѧ��orȫ��ѧ��)
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
//6-1.���в��ϸ��ѧ��
void Show_all_unqualified_student(S* head)
{
	system("cls");

	S* a = head;
	printf("-----------------------------------------------------------------------------------------------\n");
	printf("     ѧ��      |    ����    |    ����    |    ��ѧ    |    Ӣ��    |    ����    |    �ܳɼ�    |\n");
	printf("---------------+------------+------------+------------+------------+------------+--------------\n");
	while (NULL != a->next)
	{
		a = a->next;
		if (!a->m_qualifiedScore)
		{
			printf("---------------+------------+------------+------------+------------+------------+--------------\n");
			printf("%11s |%11s |%11d |%11d |%11d |%11d |%11d   |\n", a->m_number, a->m_name, a->m_ChineseScore, a->m_MathScore, a->m_EnglishScore, a->m_programScore, a->m_totalScore);
		}
	}
	printf("-----------------------------------------------------------------------------------------------\n");
	getchar();
}
//6-2.ȫ��ѧ��
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
	int loading = 4;
	while (loading--)//��װ�ڼ���
	{
		system("cls");
		for (int i = 0; i < loading; i++)
		{
			printf("o o o ");
		}
		Sleep(1000);
	}
	int number = 0;//��ǰϵͳ��¼���ѧ������
	S* a = head;
	FILE* fp = fopen("student.txt", "r");
	if (fp == NULL)
	{
		printf("\t��ǰ��ѧ��¼��.\n");
		printf("\t���س�����ϵͳ\n");
		getchar();
		return;
	}
	while (1)
	{
		S* newStudent = (S*)malloc(sizeof(S));
		if (fscanf(fp, "%s\t%s\t%d\t%d\t%d\t%d\t%d\n", \
			newStudent->m_name, newStudent->m_number, &newStudent->m_ChineseScore, \
			& newStudent->m_MathScore, &newStudent->m_EnglishScore, \
			& newStudent->m_programScore, &newStudent->m_totalScore, \
			& newStudent->m_totalScore) == EOF)
		{

			free(newStudent);
			break;
		}
		number++;
		Judge_score(newStudent);
		newStudent->next = NULL;
		a->next = newStudent;
		a = a->next;
	}
	printf("\t\t-�������-\n");
	printf("\t��ǰϵͳ����¼��%d��ѧ��\n", number);
	printf("\t\      ���س�����ϵͳ\n");
	getchar();
}
//7.�˳�ǰ�浵 
void Save_data(S* head)
{
	FILE* fp;
	S* a = head;
	if ((fp = fopen("student.txt", "w")) == NULL)
	{
		printf("�浵ʧ�ܣ�");
	}
	else
	{
		while (NULL != a->next)
		{
			a = a->next;
			fprintf(fp, "%s\t%s\t%d\t%d\t%d\t%d\t%d\n", a->m_name, a->m_number, a->m_ChineseScore, a->m_MathScore, a->m_EnglishScore, a->m_programScore, a->m_totalScore);
		}
	}

	printf("�浵�ɹ�");
	getchar();
	getchar();
	fclose(fp);
}

//4.0�汾�������˰༶���Լ���ز��� 

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <windows.h>

typedef struct Student {
	char m_name[20];         //����
	char m_number[20];       //ѧ��
	int m_class;             //�༶
	int m_ChineseScore;      //���ĳɼ�
	int m_MathScore;         //��ѧ�ɼ�
	int m_EnglishScore;      //Ӣ��ɼ�
	int m_programScore;      //������Ƴɼ�
	int m_totalScore;        //�ܷ�
	int m_rankScore;         //����������ʱ���м���� 
	bool m_qualifiedScore;   //�����ϸ�(�������Ŀ����2�Ƽ�Ϊ���ϸ�)

	struct Student* next;    //ָ����
}Stu;

//��ҳ
void home_page()
{
	system("cls");

	printf("     ___________________________\n");
	printf("    |                           |\n");
	printf("    |      SE�ɼ�����ϵͳ4.0    |\n");
	printf("    |___________________________|\n");
	printf("    |       1.¼����Ϣ          |\n");
	printf("    |       2.�޸���Ϣ          |\n");
	printf("    |       3.ɾ��ѧ��          |\n");
	printf("    |       4.��ѯ������Ϣ      |\n");
	printf("    |       5.��ѯ����          |\n");
	printf("    |       6.��ʾ������Ϣ      |\n");
	printf("    |       7.�˳�              |\n");
	printf("    |___________________________|\n");
	printf(" ------Made By:���202��١˧��------\n");
	printf("|                                   |\n");
	printf("|   ע��:  1.�ɼ���Ϊ����           |\n");
	printf("|         2.ѧ�Ų�����ʮλ          |\n");
	printf("|  3.�������˳�����������ݴ浵ʧ�� |\n");
	printf("|___________________________________|\n");
}
//1.¼����Ϣ
Stu* Input_new_student();
//1...�жϷ����Ƿ�ϸ�
void Judge_score(Stu* student);
//1...�ڵ�����(β��)
void Tail_add_node(Stu* pHead, Stu* new1);//Ϊ��Ҫ��ͷָ�� 

//2.�޸ĸ�����Ϣ�ķ�ʽ[ͨ������/ѧ����ѧ��]
void Change_information(Stu* pHead);
//2...�޸���Ϣѡ��
void Change_information_selection(Stu* student);
//2-4.�ĳɼ�
void Change_score(Stu* student);

//3.ɾ��ѧ��
void Delete_student(Stu* pHead);

//4.��ѯ������Ϣ[ͨ������/ѧ����ѧ��]
void Search_student(Stu* pHead);
//4.������Ϣ
void Show_studentInformation(Stu* student);

//5.��������ѡ��[�༶/ȫϵ]
void Rank_kindSelect(Stu* pHead);
//5...������Ҫ�����İ༶
Stu* Build_rankClass(Stu* pHead, int rankClass);
//5...����Ŀ����
void Rank_subjectSelect(Stu* pHead);
//5...����
void Rank_byScore(Stu* pHead, int subject);


//6.��ʾ������Ϣ(���ϸ�ѧ��orȫ��ѧ��)
void Show_all(Stu* pHead);
//6-1.���в��ϸ��ѧ��
void Show_all_unqualified_student(Stu* pHead);
//6-2.ȫ��ѧ��
void Show_all_student(Stu* pHead);

//��������
void Load_data(Stu* pHead);
//7.�˳�ǰ�浵 
void Save_data(Stu* pHead);

int main()
{
	Stu* pHead = (Stu*)malloc(sizeof(Stu));
	memset(pHead, 0, sizeof(Stu));
	pHead->next = NULL;

	Load_data(pHead);//�������� 

	int select = 0;
	while (1)
	{
		int N = 0;
		home_page();

		scanf("%d", &select);
		if (!(select >= 1 && select <= 6)) {
			Save_data(pHead);//�浵 
			break;
		}
		switch (select)
		{
		case 1://¼����Ϣ
			printf("�������㱾����¼��ɼ�������:\n");
			scanf("%d", &N);
			for (int i = 0; i < N; i++)
			{
				Tail_add_node(pHead, Input_new_student());
				printf("¼��ɹ�!\n");
				getchar();
			}
			break;
		case 2://�޸���Ϣ
			Change_information(pHead);
			getchar();
			break;
		case 3://ɾ��ѧ��
			printf("����ɾ������ѧ��:");
			int deleteNumber;
			scanf("%d", &deleteNumber);
			for (int i = 0; i < deleteNumber; i++)
			{
				Delete_student(pHead);
			}
			getchar();
			break;
		case 4://��ѯ������Ϣ
			Search_student(pHead);
			getchar();
			break;
		case 5://��ѯ����
			Rank_kindSelect(pHead);
			getchar();
			break;
		case 6://��ʾ������Ϣ
			Show_all(pHead);
			getchar();
			break;
		default:
			break;
		}
	}

	free(pHead);
	return 0;
}


//1.¼����Ϣ
Stu* Input_new_student()
{
	system("cls");

	Stu* newStudent = (Stu*)malloc(sizeof(Stu));
	memset(newStudent, 0, sizeof(Stu));
	newStudent->next = NULL;

	printf("����:");
	scanf("%s", newStudent->m_name);
	printf("ѧ��:");
	scanf("%s", newStudent->m_number);
	printf("�༶:");
	scanf("%d", &newStudent->m_class);
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
void Judge_score(Stu* student)
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
void Tail_add_node(Stu* pHead, Stu* new1)
{
	Stu* pMove = pHead;
	while (pMove->next)
	{
		pMove = pMove->next;
	}
	pMove->next = new1;
}

//2.�޸ĸ�����Ϣ�ķ�ʽ[ͨ������/ѧ����ѧ��]
void Change_information(Stu* pHead)
{
	system("cls");
	int selectWay;//���ҷ�ʽ 
	Stu* pMove = pHead;
	printf("����ͨ������/ѧ���޸�ѧ����Ϣ:[1--����/2--ѧ��]");
	scanf("%d", &selectWay);
	getchar();
	switch (selectWay)
	{
	case 1://ͨ��������
		char name[20];
		printf("����:");
		scanf("%s", name);
		while (pMove->next)
		{
			pMove = pMove->next;
			if (!strcmp(name, pMove->m_name))
			{
				Change_information_selection(pMove);
				return;
			}
		}
		break;
	case 2://ͨ��ѧ����
		char number[20];
		printf("ѧ��:");
		scanf("%s", number);
		while (pMove->next)
		{
			pMove = pMove->next;
			if (!strcmp(number, pMove->m_number))
			{
				Change_information_selection(pMove);
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
void Change_information_selection(Stu* student)
{
	system("cls");
	printf("�����޸�%s����һ����Ϣ:\n", student->m_name);
	printf(" __________\n");
	printf("|1.����    |\n");
	printf("|2.ѧ��    |\n");
	printf("|3.�༶    |\n");
	printf("|4.�ɼ�    |\n");
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
		break;
	case 2:
		printf("ԭѧ��%s,��Ϊ:", student->m_number);
		char newNumber[20];
		scanf("%s", newNumber);
		strcpy(student->m_number, newNumber);
		break;
	case 3:
		printf("ԭ�༶%d,��Ϊ:", student->m_class);
		scanf("%d", &student->m_class);
		break;
	case 4:
		Change_score(student);
		break;
	default:
		break;
	}
	printf("�޸ĳɹ�.\n");
	getchar();
	return;
}
//2-4.�ĳɼ�
void Change_score(Stu* student)
{
	system("cls");
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
void Delete_student(Stu* pHead)
{
	system("cls");
	int selectWay;
	Stu* pMove = pHead;
	Stu* prev = NULL;//�Ժ������ʱ��,���ڱ���ָ��pMove��ǰһλ
	printf("����ͨ������/ѧ��ɾ��ѧ��:[1--����/2--ѧ��]");
	scanf("%d", &selectWay);
	switch (selectWay)
	{
	case 1:
		char name[20];
		printf("����:");
		scanf("%s", name);
		while (pMove->next)
		{
			prev = pMove;
			pMove = pMove->next;
			if (!strcmp(name, pMove->m_name))
			{
				prev->next = pMove->next;
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
		while (pMove->next)
		{
			pMove = pMove->next;
			if (!strcmp(number, pMove->m_number))
			{
				prev->next = pMove->next;
				printf("ɾ���ɹ�!");
				getchar();
				return;
			}
		}
		break;

	default:
		break;
	}
	printf(" _____________________________\n");
	printf("|  δ�ҵ���ѧ��,ɾ��������Ч  |\n");
	printf("|_____________________________|\n");
	getchar();
}

//4.��ѯ������Ϣ[ͨ������/ѧ����ѧ��]
void Search_student(Stu* pHead)
{
	system("cls");
	int selectWay;//���ҷ�ʽ
	int ret = 1;//�ж�ѧ���Ƿ����
	Stu* pMove = pHead;

	printf("����ͨ������/ѧ�Ų���ѧ��:[1--����/2--ѧ��]");
	scanf("%d", &selectWay);
	getchar();
	switch (selectWay)
	{
	case 1:
		char name[20];
		printf("����:");
		scanf("%s", name);
		while (pMove->next)
		{
			pMove = pMove->next;
			if (!strcmp(name, pMove->m_name))
			{
				Show_studentInformation(pMove);
				ret = 0;
				break;
			}
		}
		break;
	case 2:
		char number[20];
		printf("ѧ��:");
		scanf("%s", number);
		while (pMove->next)
		{
			pMove = pMove->next;
			if (!strcmp(number, pMove->m_number))
			{
				Show_studentInformation(pMove);
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
		printf(" ________________\n");
		printf("|  δ�ҵ���ѧ��  |\n");
		printf("|________________|\n");
		getchar();
	}

}
//4.������Ϣ
void Show_studentInformation(Stu* student)
{
	system("cls");

	printf(" ____________________\n");
	printf("|  ����:%-12s|\n", student->m_name);
	printf("|  ѧ��:%-12s|\n", student->m_number);
	printf("|  �༶:%-12d|\n", student->m_class);
	printf("|  ����:%-12d|\n", student->m_ChineseScore);
	printf("|  ��ѧ:%-12d|\n", student->m_MathScore);
	printf("|  Ӣ��:%-12d|\n", student->m_EnglishScore);
	printf("|  ����:%-12d|\n", student->m_programScore);
	printf("|  �ܷ�:%-12d|\n", student->m_totalScore);
	printf("|___________________|\n");
	getchar();
}

//5.��������ѡ��[�༶/ȫϵ]
void Rank_kindSelect(Stu* pHead)
{
	int ifSelect = 1;//ѡ���Ƿ����
	int kindSelect = 0;
	printf("���հ༶/ȫϵ����[1-�༶ 2-ȫϵ]:");
	scanf("%d", &kindSelect);

	Stu* p_classHead = NULL;
	while (ifSelect)
	{
		switch (kindSelect)
		{
		case 1://�༶����
			int rankClass;
			printf("����������鿴�����İ༶:");
			scanf("%d", &rankClass);

			p_classHead = Build_rankClass(pHead, rankClass);
			if (NULL == p_classHead)
			{
				printf("  ___________________________________\n");
				printf(" |  ϵͳ����δ¼��ð༶ѧ������Ϣ.  |\n");
				printf(" |___________________________________|\n");
				getchar();
				break;
			}
			Rank_subjectSelect(p_classHead);
			getchar();
			break;
		case 2://ȫϵ����
			Rank_subjectSelect(pHead);
			getchar();
			break;
		default:
			break;
		}
		printf("�Ƿ�Ҫ�����鿴����?[1-�� 0-��]");
		scanf("%d", &ifSelect);
	}
}
//5...������Ҫ�����İ༶
Stu* Build_rankClass(Stu* pHead, int rankClass)
{
	Stu* pMoveGrade = pHead;//�������ͷָ�� 

	Stu* classHead = (Stu*)malloc(sizeof(Stu));//�ð༶��ͷ�ڵ�
	memset(classHead, 0, sizeof(Stu));
	classHead->next = NULL;
	Stu* pMoveClass = classHead;//�ð༶��ͷָ�� 

	int classmateNumber = 0;//�ð༶���� 
	while (pMoveGrade->next)
	{
		pMoveGrade = pMoveGrade->next;
		if (pMoveGrade->m_class == rankClass)//���ð༶��ѧ�����ϸ��Ƶ���Ҫ����������������
		{
			classmateNumber++;
			Stu* newStudent = (Stu*)malloc(sizeof(Stu));
			memset(newStudent, 0, sizeof(Stu));
			newStudent->next = NULL;

			strcpy(newStudent->m_name, pMoveGrade->m_name);
			strcpy(newStudent->m_number, pMoveGrade->m_number);
			newStudent->m_class = pMoveGrade->m_class;
			newStudent->m_qualifiedScore = pMoveGrade->m_qualifiedScore;
			newStudent->m_ChineseScore = pMoveGrade->m_ChineseScore;
			newStudent->m_MathScore = pMoveGrade->m_MathScore;
			newStudent->m_EnglishScore = pMoveGrade->m_EnglishScore;
			newStudent->m_programScore = pMoveGrade->m_programScore;
			newStudent->m_totalScore = pMoveGrade->m_totalScore;

			pMoveClass->next = newStudent;
			pMoveClass = pMoveClass->next;
		}
	}

	if (classmateNumber)
	{
		return classHead;
	}
	else {
		return NULL;
	}
}
//5...����Ŀ����
void Rank_subjectSelect(Stu* pHead)
{
	system("cls");

	if (NULL == pHead->next || NULL == pHead->next)
	{
		printf("�޸��������������¼��,����ʧ��.");
		getchar();
		return;
	}
	int select_subject = 0;
	int ifSelect = 1;
	Stu* pMove = pHead;

	printf("���밴���ŵĳɼ�����:\n");
	printf("1.���� 2.��ѧ 3.Ӣ�� 4.���� 5.�ܷ� 6.�˳�\n");
	scanf("%d", &select_subject);
	getchar();
	switch (select_subject)
	{
	case 1://����������
		while (pMove->next)
		{
			pMove = pMove->next;
			pMove->m_rankScore = pMove->m_ChineseScore;
		}
		printf("------------+------------+------------+-------------------------\n");
		printf("    ѧ��    |    ����    |    �༶    |  ���ĳɼ�  |  ��������  |\n");
		printf("------------+------------+------------+------------+------------\n");

		Rank_byScore(pHead, 1);
		break;
	case 2://����ѧ����
		while (pMove->next)
		{
			pMove = pMove->next;
			pMove->m_rankScore = pMove->m_MathScore;
		}
		printf("----------------------------------------------------------------\n");
		printf("    ѧ��    |    ����    |    �༶    |  ��ѧ�ɼ�  |  ��ѧ����  |\n");
		printf("------------+------------+------------+------------+------------\n");

		Rank_byScore(pHead, 2);
		break;
	case 3://��Ӣ������
		while (pMove->next)
		{
			pMove = pMove->next;
			pMove->m_rankScore = pMove->m_EnglishScore;
		}
		printf("------------+------------+------------+-------------------------\n");
		printf("    ѧ��    |    ����    |    �༶    |  Ӣ��ɼ�  |  Ӣ������  |\n");
		printf("------------+------------+------------+------------+------------\n");

		Rank_byScore(pHead, 3);
		break;
	case 4://����������
		while (pMove->next)
		{
			pMove = pMove->next;
			pMove->m_rankScore = pMove->m_programScore;
		}
		printf("------------+------------+------------+------------+------------\n");
		printf("    ѧ��    |    ����    |    �༶    |  ����ɼ�  |  ��������  |\n");
		printf("------------+------------+------------+------------+------------\n");

		Rank_byScore(pHead, 4);
		break;
	case 5://���ܷ�����
		while (pMove->next)
		{
			pMove = pMove->next;
			pMove->m_rankScore = pMove->m_totalScore;
		}
		printf("------------+------------+------------+------------+------------+------------+------------+------------+------------\n");
		printf("    ѧ��    |    ����    |    �༶    |  ���ĳɼ�  |  ��ѧ�ɼ�  |  Ӣ��ɼ�  |  ����ɼ�  |    �ܷ�    |  �ܷ�����  |\n");
		printf("------------+------------+------------+------------+------------+------------+------------+------------+------------\n");

		Rank_byScore(pHead, 5);
		break;
	default:
		break;
	}
}
//5...����
void Rank_byScore(Stu* pHead, int subject)
{
	Stu* p = pHead->next->next;
	Stu* q = NULL;
	Stu* pre = NULL;
	pHead->next->next = NULL;
	//ֱ�巨����
	while (p)
	{
		q = p->next;
		pre = pHead;
		while (pre->next != NULL && pre->next->m_rankScore > p->m_rankScore)
		{
			pre = pre->next;
		}
		p->next = pre->next;
		pre->next = p;
		p = q;
	}

	//����
	Stu* pMove = pHead;
	int scoreRank = 1;

	if (subject != 5)
	{
		while (pMove->next)
		{
			pMove = pMove->next;
			printf("------------+------------+------------+------------+-------------\n");
			printf("%11s |%11s |%11d |%11d |%11d |\n", pMove->m_number, \
				pMove->m_name, pMove->m_class, pMove->m_rankScore, scoreRank);
			scoreRank++;
		}
		printf("-----------------------------------------------------------------\n");
	}
	else {
		while (pMove->next)
		{
			pMove = pMove->next;
			printf("------------+------------+------------+------------+------------+------------+------------+------------+-------------\n");
			printf("%11s |%11s |%11d |%11d |%11d |%11d |%11d |%11d |%11d |\n", pMove->m_number, \
				pMove->m_name, pMove->m_class, pMove->m_ChineseScore, pMove->m_MathScore, \
				pMove->m_EnglishScore, pMove->m_programScore, pMove->m_rankScore, scoreRank);
			scoreRank++;
		}
		printf("---------------------------------------------------------------------------------------------------------------------\n");
	}
}

//6.��ʾ������Ϣ(���ϸ�ѧ��orȫ��ѧ��)
void Show_all(Stu* pHead)
{
	system("cls");

	printf(" _______________________________________\n");
	printf("| 1.���в��ϸ��ѧ��(�������Ŀ����2��)\t|\n");
	printf("| 2.ȫ��ѧ��\t\t\t\t|\n");
	printf("| 3.����\t\t\t\t|\n");
	printf(" ---------------------------------------\n");

	int select;
	scanf("%d", &select);

	switch (select)
	{
	case 1://���ϸ�ѧ�� 
		Show_all_unqualified_student(pHead);
		break;
	case 2://ȫ��ѧ��
		Show_all_student(pHead);
		break;
	default:
		break;
	}
}
//6-1.���в��ϸ��ѧ��
void Show_all_unqualified_student(Stu* pHead)
{
	system("cls");

	Stu* pMove = pHead;
	printf("------------------------------------------------------------------------------------------------------------\n");
	printf("     ѧ��      |    ����    |    �༶    |    ����    |    ��ѧ    |    Ӣ��    |    ����    |    �ܳɼ�    |\n");
	printf("---------------+------------+------------+------------+------------+------------+---------------------------\n");
	while (pMove->next)
	{
		pMove = pMove->next;
		if (!pMove->m_qualifiedScore)
		{
			printf("---------------+------------+------------+------------+------------+------------+------------+--------------\n");
			printf("%14s |%11s |%11d |%11d |%11d |%11d |%11d |%11d   |\n", pMove->m_number, pMove->m_name, pMove->m_class, pMove->m_ChineseScore, pMove->m_MathScore, pMove->m_EnglishScore, pMove->m_programScore, pMove->m_totalScore);
		}
	}
	printf("------------------------------------------------------------------------------------------------------------\n");
	getchar();
}
//6-2.ȫ��ѧ��
void Show_all_student(Stu* pHead)
{
	system("cls");
	Stu* pMove = pHead;

	printf("------------------------------------------------------------------------------------------------------------\n");
	printf("     ѧ��      |    ����    |    �༶    |    ����    |    ��ѧ    |    Ӣ��    |    ����    |    �ܳɼ�    |\n");
	printf("---------------+------------+------------+------------+------------+------------+------------+--------------\n");
	while (pMove->next)
	{
		pMove = pMove->next;
		printf("---------------+------------+------------+------------+------------+------------+------------+--------------\n");
		printf("%14s |%11s |%11d |%11d |%11d |%11d |%11d |%11d   |\n", pMove->m_number, pMove->m_name, \
			pMove->m_class, pMove->m_ChineseScore, pMove->m_MathScore, pMove->m_EnglishScore, \
			pMove->m_programScore, pMove->m_totalScore);
	}
	printf("------------------------------------------------------------------------------------------------------------\n");
	getchar();
}

//��������
void Load_data(Stu* pHead)
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
	Stu* pMove = pHead;
	FILE* fp = fopen("student.txt", "r");
	if (fp == NULL)
	{
		printf(" _______________________________\n");
		printf("|\t��ǰ��ѧ��¼��.  \t|\n");
		printf("|\t���س�����ϵͳ...\t|\n");
		printf("|_______________________________|\n");
		getchar();
		return;
	}
	while (1)
	{
		Stu* newStudent = (Stu*)malloc(sizeof(Stu));
		if (fscanf(fp, "%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", \
			newStudent->m_name, newStudent->m_number, \
			& newStudent->m_class, &newStudent->m_ChineseScore, \
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
		pMove->next = newStudent;
		pMove = pMove->next;
	}
	printf(" _______________________________________\n");
	printf("|\t\t-�������-\t\t|\n");
	printf("|\t��ǰϵͳ����¼��%3d��ѧ��\t|\n", number);
	printf("|\t      ���س�����ϵͳ       \t|\n");
	printf("|_______________________________________|\n");
	getchar();
}
//7.�˳�ǰ�浵 
void Save_data(Stu* pHead)
{
	FILE* fp;
	Stu* pMove = pHead;
	if ((fp = fopen("student.txt", "w")) == NULL)
	{
		printf("�浵ʧ�ܣ�");
	}
	else
	{
		while (pMove->next)
		{
			pMove = pMove->next;
			fprintf(fp, "%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", pMove->m_name, \
				pMove->m_number, pMove->m_class, pMove->m_ChineseScore, \
				pMove->m_MathScore, pMove->m_EnglishScore, pMove->m_programScore, \
				pMove->m_totalScore);
		}
	}

	printf("�浵�ɹ�");
	getchar();
	getchar();
	fclose(fp);
}

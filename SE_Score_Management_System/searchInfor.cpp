//4-1.��ѯ������Ϣ[ͨ������/ѧ����ѧ��]
void Search_student(Stu* pHead)
{
	system("cls");
	int ret = 1;//�ж�ѧ���Ƿ����
	Stu* pMove = pHead;

	printf("����ͨ������/ѧ�Ų���ѧ��:\n");
	printf(" ______________\n");
	printf("|   1.����     |\n");
	printf("|   2.ѧ��     |\n");
	printf("|______________|\n");
	printf("|   3.����     |\n");
	printf("|______________|\n");
	
	int searchWay;
	while(scanf("%d",&searchWay)==0 || searchWay==0 || searchWay>3)
	{
		getchar();
		printf("��������ȷ�Ĺ��ܴ���:");
	}

	switch (searchWay)
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
				return ;
			}
		}
		printf(" ________________\n");
		printf("|  δ�ҵ���ѧ��  |\n");
		printf("|________________|\n");
		getchar();
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
				return ;
			}
		}
		printf(" ________________\n");
		printf("|  δ�ҵ���ѧ��  |\n");
		printf("|________________|\n");
		getchar();
		break;
	default:
		break;
	}
}
//4-2.������Ϣ
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

//5-1.��������ѡ��[�༶/ȫϵ]
void Rank_kindSelect(Stu* pHead)
{
	system("cls");
	int ifSelect = 1;//ѡ���Ƿ����

	printf("���հ༶/ȫϵ����:\n");
	printf(" ______________\n");
	printf("|   1.�༶     |\n");
	printf("|   2.ȫϵ     |\n");
	printf("|______________|\n");
	printf("|   3.����     |\n");
	printf("|______________|\n");

	int kindSelect = 0;
	while(scanf("%d",&kindSelect)==0 || kindSelect==0 || kindSelect>3)
	{
		getchar();
		printf("��������ȷ�Ĺ��ܴ���:");
	}
	Stu* p_classHead = NULL;
	while (ifSelect)
	{
		switch (kindSelect)
		{
		case 1://�༶����
			system("cls");
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
			system("cls");
			Rank_subjectSelect(pHead);
			getchar();
			break;
		default:
			ifSelect = 0;
			break;
		}
		if(kindSelect != 3)
		{
			printf("�Ƿ�Ҫ�����鿴����?[1-�� 0-��]");
			scanf("%d", &ifSelect);
		}	
	}
}
//5-2.������Ҫ�����İ༶
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
//5-3.����Ŀ����
void Rank_subjectSelect(Stu* pHead)
{
	Stu* pMove = pHead;
	system("cls");

	if (NULL == pHead->next )
	{
		printf("�޸��������������¼��,����ʧ��.");
		getchar();
		return;
	}
	printf("���밴���ŵĳɼ�����:\n");
	printf("1.���� 2.��ѧ 3.Ӣ�� 4.���� 5.�ܷ� 6.�˳�\n");
	

	int select_subject = 0;
	while(scanf("%d",&select_subject)==0 || select_subject==0 || select_subject>6)
	{
		getchar();
		printf("��������ȷ�Ĵ���:");
	}
	
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
	case 6:
		return ;
		break; 
	default:
		break;
	}
}
//5-4.����
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
		while (pre->next != NULL && pre->next->m_rankScore > p->m_rankScore)//Ԥ�� 
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

//6-1.��ʾ������Ϣ(���ϸ�ѧ��orȫ��ѧ��)
void Show_all_selection(Stu* pHead)
{
	system("cls");

	printf(" _______________________________________\n");
	printf("| 1.���в��ϸ��ѧ��(�������Ŀ����2��)\t|\n");
	printf("| 2.ȫ��ѧ��\t\t\t\t|\n");
	printf("| 3.����\t\t\t\t|\n");
	printf(" ---------------------------------------\n");

	int select;
	while(scanf("%d",&select)==0 || select==0 || select>3)
	{
		printf("��������ȷ�Ĺ��ܴ���:");
	}
	//getchar();
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
//6-2.���в��ϸ��ѧ��
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
//6-3.ȫ��ѧ��
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

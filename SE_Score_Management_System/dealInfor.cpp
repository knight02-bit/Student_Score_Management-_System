//0-1.��������
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

//0-3ѡ���� 
void Select_fuction(Stu* pHead)
{
	int select = 0;
	while (1)
	{
		int N = 0;
		Home_page();

		while(scanf("%d",&select)==0 || select==0 || select>8)
		{
			getchar();
			printf("��������ȷ�Ĺ��ܴ���:");
		}

		switch (select)
		{
		case 1://¼����Ϣ
			Input_new_student(pHead);
			break;
		case 2://�޸���Ϣ
			Search_student_toChange(pHead);
			getchar();
			break;
		case 3://ɾ��ѧ��
			Delete_student(pHead);
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
			Show_all_selection(pHead);
			getchar();
			break;
		case 7://�浵 
			Save_data(pHead);//�浵 
			getchar(); 
			break;
		case 8://�˳� 
			Save_data(pHead);//�浵 
			exit(0); 
			break;
		default:		
			break;
		}
	}
}
//1-1.¼����Ϣ
void Input_new_student(Stu* pHead)
{
	int N;
	printf("�������㱾����¼��ɼ�������:\n");
	scanf("%d", &N);
	getchar();
	for (int i = 0; i < N; i++)
	{
		system("cls");
	
		Stu* newStudent = (Stu*)malloc(sizeof(Stu));
		memset(newStudent, 0, sizeof(Stu));
		newStudent->next = NULL;
	
		printf("����:");
		scanf("%s", newStudent->m_name);
		printf("ѧ��:");
		while(scanf("%s",&newStudent->m_number)==0 || strlen(newStudent->m_number)>10)
		{
			getchar();
			printf("ѧ���쳣 ,����������!\n");
			printf("ѧ��:");
		}
		printf("�༶:");
		scanf("%d", &newStudent->m_class);
		printf("���ĳɼ�:");
		while(scanf("%d",&newStudent->m_ChineseScore)==0 || newStudent->m_ChineseScore>100)
		{
			getchar();
			printf("�ɼ������쳣,����������!\n");
			printf("���ĳɼ�:");
		}
		printf("��ѧ�ɼ�:");
		while(scanf("%d",&newStudent->m_MathScore)==0 || newStudent->m_MathScore>100)
		{
			getchar();
			printf("�ɼ������쳣,����������!\n");
			printf("��ѧ�ɼ�:");
		}
		printf("Ӣ��ɼ�:");
		while(scanf("%d",&newStudent->m_EnglishScore)==0 || newStudent->m_EnglishScore>100)
		{
			getchar();
			printf("�ɼ������쳣,����������!\n");
			printf("Ӣ��ɼ�:");
		}
		printf("����ɼ�:");
		while(scanf("%d",&newStudent->m_programScore)==0 || newStudent->m_programScore>100)
		{
			getchar();
			printf("�ɼ������쳣,����������!\n");
			printf("����ɼ�:");
		}
		newStudent->m_totalScore = newStudent->m_ChineseScore + newStudent->m_MathScore + newStudent->m_EnglishScore + newStudent->m_programScore;
		newStudent->m_rankScore = 0;
		Judge_score(newStudent);//�жϺϸ���� 
		getchar();
		
		Tail_add_node(pHead, newStudent);
		printf("¼��ɹ�!\n");
		getchar();
	}
}
//1-2.�жϷ����Ƿ�ϸ�
void Judge_score(Stu* student)
{
	int cnt = 0;//���ϸ��Ŀ������ 
	cnt = (student->m_ChineseScore < 60) + (student->m_MathScore < 60)\
		+ (student->m_EnglishScore < 60) + (student->m_programScore < 60);
	if (cnt >= 2)
		student->m_qualifiedScore = false;
	else
		student->m_qualifiedScore = true;
}
//1-3.�ڵ�����(β��)
void Tail_add_node(Stu* pHead, Stu* new1)
{
	Stu* pMove = pHead;
	while (pMove->next)
	{
		pMove = pMove->next;
	}
	pMove->next = new1;
}

//2-1.�ҵ�Ҫ�޸ĵ�ѧ��[ͨ������/ѧ����ѧ��]
void Search_student_toChange(Stu* pHead)
{
	system("cls");
	
	int ifSelect=1;
	while(ifSelect)
	{
		system("cls");
		printf("����ͨ������/ѧ���޸�ѧ����Ϣ:\n");
		printf(" ______________\n");
		printf("|   1.����     |\n");
		printf("|   2.ѧ��     |\n");
		printf("|______________|\n");
		printf("|3.�鿴ȫ������|\n");
		printf("|   4.����     |\n");
		printf("|______________|\n");
		
		Stu* pMove = pHead;
		int selectWay;//���ҷ�ʽ 
		while(scanf("%d",&selectWay)==0 || selectWay==0 || selectWay>4)
		{
			getchar();
			printf("��������ȷ�Ĺ��ܴ���:");
		}

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
		case 3://ȫ����Ϣ 
			Show_all_student(pHead);
			break;	
		case 4:
			return ;
			break;
		default:
			break;
		}
		if(selectWay != 3)
		{
			getchar();
			printf("δ�ҵ���ѧ��,�޸Ĳ�����Ч\n");
			getchar();
		}
		printf("�Ƿ�Ҫ�����޸Ĳ���?[1-��  0-��]");
		scanf("%d",&ifSelect); 
	}
}
//2-2.�޸���Ϣѡ��
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
	printf("|5.����    |\n");
	printf("|__________|\n");
	
	int select;
	while(scanf("%d",&select)==0 || select==0 || select>5)
	{
		getchar();
		printf("��������ȷ�Ĺ��ܴ���:");
	}
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
		while(scanf("%s",newNumber)==0 || strlen(newNumber)>10)
		{
			getchar();
			printf("ѧ���쳣 ,����������!\n");
			printf("ѧ��:");
		}
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
	if(select != 5)
	{
		printf("�޸ĳɹ�.\n");
		getchar();
	}
}
//2-3.�ĳɼ�
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
		if(student->m_ChineseScore > 100)
		{
			ret=1;
			printf("�ɼ������쳣,����������!\n"); 
		}else{
			ret=0;
		}
	}
	printf("��ѧ�ɼ�:%d ,�Ƿ�Ҫ�޸�?\n[0-��;1-��]", student->m_MathScore);
	scanf("%d", &ret);
	while (ret)
	{
		printf("��Ϊ:");
		scanf("%d", &student->m_MathScore);
		if(student->m_MathScore > 100)
		{
			ret=1;
			printf("�ɼ������쳣,����������!\n"); 
		}else{
			ret=0;
		}
	}
	printf("Ӣ��ɼ�:%d ,�Ƿ�Ҫ�޸�?\n[0-��;1-��]", student->m_EnglishScore);
	scanf("%d", &ret);
	while (ret)
	{
		printf("��Ϊ:");
		scanf("%d", &student->m_EnglishScore);
		if(student->m_EnglishScore > 100)
		{
			ret=1;
			printf("�ɼ������쳣,����������!\n"); 
		}else{
			ret=0;
		}
	}
	printf("����ɼ�:%d ,�Ƿ�Ҫ�޸�?\n[0-��;1-��]", student->m_programScore);
	scanf("%d", &ret);
	while (ret)
	{
		printf("��Ϊ:");
		scanf("%d", &student->m_programScore);
		if(student->m_programScore > 100)
		{
			ret=1;
			printf("�ɼ������쳣,����������!\n"); 
		}else{
			ret=0;
		}
	}
	student->m_totalScore = student->m_ChineseScore + student->m_MathScore + student->m_EnglishScore + student->m_programScore;
	Judge_score(student);
	return;
}

//3.ɾ��ѧ��
void Delete_student(Stu* pHead)
{
	Stu* prev = NULL;//�Ժ������ʱ��,���ڱ���ָ��pMove��ǰһλ
	
	Stu* pMove = pHead;
	system("cls");
		
	printf("����ͨ������/ѧ��ɾ��ѧ��:\n");
	printf(" ______________\n");
	printf("|   1.����     |\n");
	printf("|   2.ѧ��     |\n");
	printf("|______________|\n");
	printf("|3.�鿴ȫ������|\n");
	printf("|   4.����     |\n");
	printf("|______________|\n");
	
	int searchWay;//���ҷ�ʽ 
	while(scanf("%d",&searchWay)==0 || searchWay==0 || searchWay>4)
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
	case 3: 
		Show_all_student(pHead);
		getchar();
		Delete_student(pHead);
		break;
	default:
		break;
	}
	if(searchWay==1 || searchWay==2)
	{
		getchar();
		printf(" _____________________________\n");
		printf("|  δ�ҵ���ѧ��,ɾ��������Ч  |\n");
		printf("|_____________________________|\n");
		getchar();
	}	
}
//7.�浵 
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
	fclose(fp);
}

//4-1.查询个人信息[通过名字/学号找学生]
void Search_student(Stu* pHead)
{
	system("cls");
	int ret = 1;//判断学生是否存在
	Stu* pMove = pHead;

	printf("你想通过名字/学号查找学生:\n");
	printf(" ______________\n");
	printf("|   1.名字     |\n");
	printf("|   2.学号     |\n");
	printf("|______________|\n");
	printf("|   3.返回     |\n");
	printf("|______________|\n");
	
	int searchWay;
	while(scanf("%d",&searchWay)==0 || searchWay==0 || searchWay>3)
	{
		getchar();
		printf("请输入正确的功能代号:");
	}

	switch (searchWay)
	{
	case 1:
		char name[20];
		printf("名字:");
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
		printf("|  未找到该学生  |\n");
		printf("|________________|\n");
		getchar();
		break;
	case 2:
		char number[20];
		printf("学号:");
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
		printf("|  未找到该学生  |\n");
		printf("|________________|\n");
		getchar();
		break;
	default:
		break;
	}
}
//4-2.个人信息
void Show_studentInformation(Stu* student)
{
	system("cls");

	printf(" ____________________\n");
	printf("|  名字:%-12s|\n", student->m_name);
	printf("|  学号:%-12s|\n", student->m_number);
	printf("|  班级:%-12d|\n", student->m_class);
	printf("|  语文:%-12d|\n", student->m_ChineseScore);
	printf("|  数学:%-12d|\n", student->m_MathScore);
	printf("|  英语:%-12d|\n", student->m_EnglishScore);
	printf("|  程序:%-12d|\n", student->m_programScore);
	printf("|  总分:%-12d|\n", student->m_totalScore);
	printf("|___________________|\n");
	getchar();
}

//5-1.排名种类选择[班级/全系]
void Rank_kindSelect(Stu* pHead)
{
	system("cls");
	int ifSelect = 1;//选择是否继续

	printf("按照班级/全系排名:\n");
	printf(" ______________\n");
	printf("|   1.班级     |\n");
	printf("|   2.全系     |\n");
	printf("|______________|\n");
	printf("|   3.返回     |\n");
	printf("|______________|\n");

	int kindSelect = 0;
	while(scanf("%d",&kindSelect)==0 || kindSelect==0 || kindSelect>3)
	{
		getchar();
		printf("请输入正确的功能代号:");
	}
	Stu* p_classHead = NULL;
	while (ifSelect)
	{
		switch (kindSelect)
		{
		case 1://班级排名
			system("cls");
			int rankClass;
			printf("请输入你想查看排名的班级:");
			scanf("%d", &rankClass);

			p_classHead = Build_rankClass(pHead, rankClass);
			if (NULL == p_classHead)
			{
				printf("  ___________________________________\n");
				printf(" |  系统内暂未录入该班级学生的信息.  |\n");
				printf(" |___________________________________|\n");
				getchar();
				break;
			}
			Rank_subjectSelect(p_classHead);
			getchar();
			break;
		case 2://全系排名
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
			printf("是否还要继续查看排名?[1-是 0-否]");
			scanf("%d", &ifSelect);
		}	
	}
}
//5-2.创建需要排名的班级
Stu* Build_rankClass(Stu* pHead, int rankClass)
{
	Stu* pMoveGrade = pHead;//主链表的头指针 

	Stu* classHead = (Stu*)malloc(sizeof(Stu));//该班级的头节点
	memset(classHead, 0, sizeof(Stu));
	classHead->next = NULL;
	Stu* pMoveClass = classHead;//该班级的头指针 

	int classmateNumber = 0;//该班级人数 
	while (pMoveGrade->next)
	{
		pMoveGrade = pMoveGrade->next;
		if (pMoveGrade->m_class == rankClass)//将该班级的学生资料复制到需要进行排名的链表中
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
//5-3.按科目排名
void Rank_subjectSelect(Stu* pHead)
{
	Stu* pMove = pHead;
	system("cls");

	if (NULL == pHead->next )
	{
		printf("无该排名的相关数据录入,排名失败.");
		getchar();
		return;
	}
	printf("你想按哪门的成绩排名:\n");
	printf("1.语文 2.数学 3.英语 4.程序 5.总分 6.退出\n");
	

	int select_subject = 0;
	while(scanf("%d",&select_subject)==0 || select_subject==0 || select_subject>6)
	{
		getchar();
		printf("请输入正确的代号:");
	}
	
	switch (select_subject)
	{
	case 1://按语文排名
		while (pMove->next)
		{
			pMove = pMove->next;
			pMove->m_rankScore = pMove->m_ChineseScore;
		}
		printf("------------+------------+------------+-------------------------\n");
		printf("    学号    |    姓名    |    班级    |  语文成绩  |  语文名次  |\n");
		printf("------------+------------+------------+------------+------------\n");

		Rank_byScore(pHead, 1);
		break;
	case 2://按数学排名
		while (pMove->next)
		{
			pMove = pMove->next;
			pMove->m_rankScore = pMove->m_MathScore;
		}
		printf("----------------------------------------------------------------\n");
		printf("    学号    |    姓名    |    班级    |  数学成绩  |  数学名次  |\n");
		printf("------------+------------+------------+------------+------------\n");

		Rank_byScore(pHead, 2);
		break;
	case 3://按英语排名
		while (pMove->next)
		{
			pMove = pMove->next;
			pMove->m_rankScore = pMove->m_EnglishScore;
		}
		printf("------------+------------+------------+-------------------------\n");
		printf("    学号    |    姓名    |    班级    |  英语成绩  |  英语名次  |\n");
		printf("------------+------------+------------+------------+------------\n");

		Rank_byScore(pHead, 3);
		break;
	case 4://按程序排名
		while (pMove->next)
		{
			pMove = pMove->next;
			pMove->m_rankScore = pMove->m_programScore;
		}
		printf("------------+------------+------------+------------+------------\n");
		printf("    学号    |    姓名    |    班级    |  程序成绩  |  程序名次  |\n");
		printf("------------+------------+------------+------------+------------\n");

		Rank_byScore(pHead, 4);
		break;
	case 5://按总分排名
		while (pMove->next)
		{
			pMove = pMove->next;
			pMove->m_rankScore = pMove->m_totalScore;
		}
		printf("------------+------------+------------+------------+------------+------------+------------+------------+------------\n");
		printf("    学号    |    姓名    |    班级    |  语文成绩  |  数学成绩  |  英语成绩  |  程序成绩  |    总分    |  总分名次  |\n");
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
//5-4.排名
void Rank_byScore(Stu* pHead, int subject)
{
	Stu* p = pHead->next->next;
	Stu* q = NULL;
	Stu* pre = NULL;
	pHead->next->next = NULL;
	//直插法排序
	while (p)
	{
		q = p->next;
		pre = pHead;
		while (pre->next != NULL && pre->next->m_rankScore > p->m_rankScore)//预判 
		{
			pre = pre->next;
		}
		p->next = pre->next;
		pre->next = p;
		p = q;
	}

	//遍历
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

//6-1.显示所有信息(不合格学生or全体学生)
void Show_all_selection(Stu* pHead)
{
	system("cls");

	printf(" _______________________________________\n");
	printf("| 1.所有不合格的学生(不及格科目超过2科)\t|\n");
	printf("| 2.全体学生\t\t\t\t|\n");
	printf("| 3.返回\t\t\t\t|\n");
	printf(" ---------------------------------------\n");

	int select;
	while(scanf("%d",&select)==0 || select==0 || select>3)
	{
		printf("请输入正确的功能代号:");
	}
	//getchar();
	switch (select)
	{
	case 1://不合格学生 
		Show_all_unqualified_student(pHead);
		break;
	case 2://全体学生
		Show_all_student(pHead);
		break;
	default:
		break;
	}
}
//6-2.所有不合格的学生
void Show_all_unqualified_student(Stu* pHead)
{
	system("cls");

	Stu* pMove = pHead;
	printf("------------------------------------------------------------------------------------------------------------\n");
	printf("     学号      |    姓名    |    班级    |    语文    |    数学    |    英语    |    程序    |    总成绩    |\n");
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
//6-3.全体学生
void Show_all_student(Stu* pHead)
{
	system("cls");
	Stu* pMove = pHead;

	printf("------------------------------------------------------------------------------------------------------------\n");
	printf("     学号      |    姓名    |    班级    |    语文    |    数学    |    英语    |    程序    |    总成绩    |\n");
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

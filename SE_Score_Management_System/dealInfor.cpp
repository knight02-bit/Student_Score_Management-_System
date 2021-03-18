//0-1.加载数据
void Load_data(Stu* pHead)
{
	int loading = 4;
	while (loading--)//假装在加载
	{
		system("cls");
		for (int i = 0; i < loading; i++)
		{
			printf("o o o ");
		}
		Sleep(1000);
	}
	int number = 0;//当前系统内录入的学生数量
	Stu* pMove = pHead;
	FILE* fp = fopen("student.txt", "r");
	if (fp == NULL)
	{
		printf(" _______________________________\n");
		printf("|\t当前无学生录入.  \t|\n");
		printf("|\t按回车进入系统...\t|\n");
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
	printf("|\t\t-加载完毕-\t\t|\n");
	printf("|\t当前系统内已录入%3d名学生\t|\n", number);
	printf("|\t      按回车进入系统       \t|\n");
	printf("|_______________________________________|\n");
	getchar();
}

//0-3选择功能 
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
			printf("请输入正确的功能代号:");
		}

		switch (select)
		{
		case 1://录入信息
			Input_new_student(pHead);
			break;
		case 2://修改信息
			Search_student_toChange(pHead);
			getchar();
			break;
		case 3://删除学生
			Delete_student(pHead);
			break;
		case 4://查询个人信息
			Search_student(pHead);
			getchar();
			break;
		case 5://查询排名
			Rank_kindSelect(pHead);
			getchar();
			break;
		case 6://显示所有信息
			Show_all_selection(pHead);
			getchar();
			break;
		case 7://存档 
			Save_data(pHead);//存档 
			getchar(); 
			break;
		case 8://退出 
			Save_data(pHead);//存档 
			exit(0); 
			break;
		default:		
			break;
		}
	}
}
//1-1.录入信息
void Input_new_student(Stu* pHead)
{
	int N;
	printf("请输入你本次想录入成绩的人数:\n");
	scanf("%d", &N);
	getchar();
	for (int i = 0; i < N; i++)
	{
		system("cls");
	
		Stu* newStudent = (Stu*)malloc(sizeof(Stu));
		memset(newStudent, 0, sizeof(Stu));
		newStudent->next = NULL;
	
		printf("姓名:");
		scanf("%s", newStudent->m_name);
		printf("学号:");
		while(scanf("%s",&newStudent->m_number)==0 || strlen(newStudent->m_number)>10)
		{
			getchar();
			printf("学号异常 ,请重新输入!\n");
			printf("学号:");
		}
		printf("班级:");
		scanf("%d", &newStudent->m_class);
		printf("语文成绩:");
		while(scanf("%d",&newStudent->m_ChineseScore)==0 || newStudent->m_ChineseScore>100)
		{
			getchar();
			printf("成绩数据异常,请重新输入!\n");
			printf("语文成绩:");
		}
		printf("数学成绩:");
		while(scanf("%d",&newStudent->m_MathScore)==0 || newStudent->m_MathScore>100)
		{
			getchar();
			printf("成绩数据异常,请重新输入!\n");
			printf("数学成绩:");
		}
		printf("英语成绩:");
		while(scanf("%d",&newStudent->m_EnglishScore)==0 || newStudent->m_EnglishScore>100)
		{
			getchar();
			printf("成绩数据异常,请重新输入!\n");
			printf("英语成绩:");
		}
		printf("程序成绩:");
		while(scanf("%d",&newStudent->m_programScore)==0 || newStudent->m_programScore>100)
		{
			getchar();
			printf("成绩数据异常,请重新输入!\n");
			printf("程序成绩:");
		}
		newStudent->m_totalScore = newStudent->m_ChineseScore + newStudent->m_MathScore + newStudent->m_EnglishScore + newStudent->m_programScore;
		newStudent->m_rankScore = 0;
		Judge_score(newStudent);//判断合格与否 
		getchar();
		
		Tail_add_node(pHead, newStudent);
		printf("录入成功!\n");
		getchar();
	}
}
//1-2.判断分数是否合格
void Judge_score(Stu* student)
{
	int cnt = 0;//不合格科目的数量 
	cnt = (student->m_ChineseScore < 60) + (student->m_MathScore < 60)\
		+ (student->m_EnglishScore < 60) + (student->m_programScore < 60);
	if (cnt >= 2)
		student->m_qualifiedScore = false;
	else
		student->m_qualifiedScore = true;
}
//1-3.节点连接(尾插)
void Tail_add_node(Stu* pHead, Stu* new1)
{
	Stu* pMove = pHead;
	while (pMove->next)
	{
		pMove = pMove->next;
	}
	pMove->next = new1;
}

//2-1.找到要修改的学生[通过名字/学号找学生]
void Search_student_toChange(Stu* pHead)
{
	system("cls");
	
	int ifSelect=1;
	while(ifSelect)
	{
		system("cls");
		printf("你想通过名字/学号修改学生信息:\n");
		printf(" ______________\n");
		printf("|   1.名字     |\n");
		printf("|   2.学号     |\n");
		printf("|______________|\n");
		printf("|3.查看全部资料|\n");
		printf("|   4.返回     |\n");
		printf("|______________|\n");
		
		Stu* pMove = pHead;
		int selectWay;//查找方式 
		while(scanf("%d",&selectWay)==0 || selectWay==0 || selectWay>4)
		{
			getchar();
			printf("请输入正确的功能代号:");
		}

		switch (selectWay)
		{
		case 1://通过名字找
			char name[20];
			printf("名字:");
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
		case 2://通过学号找
			char number[20];
			printf("学号:");
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
		case 3://全部信息 
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
			printf("未找到该学生,修改操作无效\n");
			getchar();
		}
		printf("是否还要继续修改操作?[1-是  0-否]");
		scanf("%d",&ifSelect); 
	}
}
//2-2.修改信息选项
void Change_information_selection(Stu* student)
{
	system("cls");
	printf("你想修改%s的哪一项信息:\n", student->m_name);
	printf(" __________\n");
	printf("|1.名字    |\n");
	printf("|2.学号    |\n");
	printf("|3.班级    |\n");
	printf("|4.成绩    |\n");
	printf("|__________|\n");
	printf("|5.返回    |\n");
	printf("|__________|\n");
	
	int select;
	while(scanf("%d",&select)==0 || select==0 || select>5)
	{
		getchar();
		printf("请输入正确的功能代号:");
	}
	switch (select)
	{
	case 1:
		printf("原名字%s,改为:", student->m_name);
		char newName[20];
		scanf("%s", newName);
		strcpy(student->m_name, newName);
		break;
	case 2:
		printf("原学号%s,改为:", student->m_number);
		char newNumber[20];
		while(scanf("%s",newNumber)==0 || strlen(newNumber)>10)
		{
			getchar();
			printf("学号异常 ,请重新输入!\n");
			printf("学号:");
		}
		strcpy(student->m_number, newNumber);
		break;
	case 3:
		printf("原班级%d,改为:", student->m_class);
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
		printf("修改成功.\n");
		getchar();
	}
}
//2-3.改成绩
void Change_score(Stu* student)
{
	system("cls");
	int ret;
	printf("%s", student->m_name);
	printf("语文成绩:%d ,是否要修改?\n[0-否;1-是]", student->m_ChineseScore);
	scanf("%d", &ret);
	while (ret)
	{
		printf("改为:");
		scanf("%d", &student->m_ChineseScore);
		if(student->m_ChineseScore > 100)
		{
			ret=1;
			printf("成绩数据异常,请重新输入!\n"); 
		}else{
			ret=0;
		}
	}
	printf("数学成绩:%d ,是否要修改?\n[0-否;1-是]", student->m_MathScore);
	scanf("%d", &ret);
	while (ret)
	{
		printf("改为:");
		scanf("%d", &student->m_MathScore);
		if(student->m_MathScore > 100)
		{
			ret=1;
			printf("成绩数据异常,请重新输入!\n"); 
		}else{
			ret=0;
		}
	}
	printf("英语成绩:%d ,是否要修改?\n[0-否;1-是]", student->m_EnglishScore);
	scanf("%d", &ret);
	while (ret)
	{
		printf("改为:");
		scanf("%d", &student->m_EnglishScore);
		if(student->m_EnglishScore > 100)
		{
			ret=1;
			printf("成绩数据异常,请重新输入!\n"); 
		}else{
			ret=0;
		}
	}
	printf("程序成绩:%d ,是否要修改?\n[0-否;1-是]", student->m_programScore);
	scanf("%d", &ret);
	while (ret)
	{
		printf("改为:");
		scanf("%d", &student->m_programScore);
		if(student->m_programScore > 100)
		{
			ret=1;
			printf("成绩数据异常,请重新输入!\n"); 
		}else{
			ret=0;
		}
	}
	student->m_totalScore = student->m_ChineseScore + student->m_MathScore + student->m_EnglishScore + student->m_programScore;
	Judge_score(student);
	return;
}

//3.删除学生
void Delete_student(Stu* pHead)
{
	Stu* prev = NULL;//稍后遍历的时候,用于保留指针pMove的前一位
	
	Stu* pMove = pHead;
	system("cls");
		
	printf("你想通过名字/学号删除学生:\n");
	printf(" ______________\n");
	printf("|   1.名字     |\n");
	printf("|   2.学号     |\n");
	printf("|______________|\n");
	printf("|3.查看全部资料|\n");
	printf("|   4.返回     |\n");
	printf("|______________|\n");
	
	int searchWay;//查找方式 
	while(scanf("%d",&searchWay)==0 || searchWay==0 || searchWay>4)
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
			prev = pMove;
			pMove = pMove->next;
			if (!strcmp(name, pMove->m_name))
			{
				prev->next = pMove->next;
				printf("删除成功!");
				getchar();
				return;
			}
		}
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
				prev->next = pMove->next;
				printf("删除成功!");
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
		printf("|  未找到该学生,删除操作无效  |\n");
		printf("|_____________________________|\n");
		getchar();
	}	
}
//7.存档 
void Save_data(Stu* pHead)
{
	FILE* fp;
	Stu* pMove = pHead;
	if ((fp = fopen("student.txt", "w")) == NULL)
	{
		printf("存档失败！");
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

	printf("存档成功");
	getchar();
	fclose(fp);
}

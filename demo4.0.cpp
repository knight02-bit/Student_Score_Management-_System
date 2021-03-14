//4.0版本新增加了班级属性及相关操作 

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <windows.h>

typedef struct Student {
	char m_name[20];         //姓名
	char m_number[20];       //学号
	int m_class;             //班级
	int m_ChineseScore;      //语文成绩
	int m_MathScore;         //数学成绩
	int m_EnglishScore;      //英语成绩
	int m_programScore;      //程序设计成绩
	int m_totalScore;        //总分
	int m_rankScore;         //按种类排名时的中间变量 
	bool m_qualifiedScore;   //分数合格(不及格科目超过2科即为不合格)

	struct Student* next;    //指针域
}Stu;

//主页
void home_page()
{
	system("cls");

	printf("     ___________________________\n");
	printf("    |                           |\n");
	printf("    |      SE成绩管理系统4.0    |\n");
	printf("    |___________________________|\n");
	printf("    |       1.录入信息          |\n");
	printf("    |       2.修改信息          |\n");
	printf("    |       3.删除学生          |\n");
	printf("    |       4.查询个人信息      |\n");
	printf("    |       5.查询排名          |\n");
	printf("    |       6.显示所有信息      |\n");
	printf("    |       7.退出              |\n");
	printf("    |___________________________|\n");
	printf(" ------Made By:软件202班佟帅杰------\n");
	printf("|                                   |\n");
	printf("|   注意:  1.成绩均为整数           |\n");
	printf("|         2.学号不超过十位          |\n");
	printf("|  3.非正常退出会造成新数据存档失败 |\n");
	printf("|___________________________________|\n");
}
//1.录入信息
Stu* Input_new_student();
//1...判断分数是否合格
void Judge_score(Stu* student);
//1...节点连接(尾插)
void Tail_add_node(Stu* pHead, Stu* new1);//为何要传头指针 

//2.修改个人信息的方式[通过名字/学号找学生]
void Change_information(Stu* pHead);
//2...修改信息选项
void Change_information_selection(Stu* student);
//2-4.改成绩
void Change_score(Stu* student);

//3.删除学生
void Delete_student(Stu* pHead);

//4.查询个人信息[通过名字/学号找学生]
void Search_student(Stu* pHead);
//4.个人信息
void Show_studentInformation(Stu* student);

//5.排名种类选择[班级/全系]
void Rank_kindSelect(Stu* pHead);
//5...创建需要排名的班级
Stu* Build_rankClass(Stu* pHead, int rankClass);
//5...按科目排名
void Rank_subjectSelect(Stu* pHead);
//5...排名
void Rank_byScore(Stu* pHead, int subject);


//6.显示所有信息(不合格学生or全体学生)
void Show_all(Stu* pHead);
//6-1.所有不合格的学生
void Show_all_unqualified_student(Stu* pHead);
//6-2.全体学生
void Show_all_student(Stu* pHead);

//加载数据
void Load_data(Stu* pHead);
//7.退出前存档 
void Save_data(Stu* pHead);

int main()
{
	Stu* pHead = (Stu*)malloc(sizeof(Stu));
	memset(pHead, 0, sizeof(Stu));
	pHead->next = NULL;

	Load_data(pHead);//加载数据 

	int select = 0;
	while (1)
	{
		int N = 0;
		home_page();

		scanf("%d", &select);
		if (!(select >= 1 && select <= 6)) {
			Save_data(pHead);//存档 
			break;
		}
		switch (select)
		{
		case 1://录入信息
			printf("请输入你本次想录入成绩的人数:\n");
			scanf("%d", &N);
			for (int i = 0; i < N; i++)
			{
				Tail_add_node(pHead, Input_new_student());
				printf("录入成功!\n");
				getchar();
			}
			break;
		case 2://修改信息
			Change_information(pHead);
			getchar();
			break;
		case 3://删除学生
			printf("你想删除几个学生:");
			int deleteNumber;
			scanf("%d", &deleteNumber);
			for (int i = 0; i < deleteNumber; i++)
			{
				Delete_student(pHead);
			}
			getchar();
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


//1.录入信息
Stu* Input_new_student()
{
	system("cls");

	Stu* newStudent = (Stu*)malloc(sizeof(Stu));
	memset(newStudent, 0, sizeof(Stu));
	newStudent->next = NULL;

	printf("姓名:");
	scanf("%s", newStudent->m_name);
	printf("学号:");
	scanf("%s", newStudent->m_number);
	printf("班级:");
	scanf("%d", &newStudent->m_class);
	printf("语文成绩:");
	scanf("%d", &newStudent->m_ChineseScore);
	printf("数学成绩:");
	scanf("%d", &newStudent->m_MathScore);
	printf("英语成绩:");
	scanf("%d", &newStudent->m_EnglishScore);
	printf("程序成绩:");
	scanf("%d", &newStudent->m_programScore);
	newStudent->m_totalScore = newStudent->m_ChineseScore + newStudent->m_MathScore + newStudent->m_EnglishScore + newStudent->m_programScore;
	newStudent->m_rankScore = 0;

	Judge_score(newStudent);//判断合格与否 
	getchar();

	return newStudent;
}
//1...判断分数是否合格
void Judge_score(Stu* student)
{
	int cnt = 0;//不合格科目的数量 
	cnt = (student->m_ChineseScore < 60) + (student->m_MathScore < 60)\
		+ (student->m_EnglishScore < 60) + (student->m_programScore < 60);
	if (cnt > 2)
		student->m_qualifiedScore = false;
	else
		student->m_qualifiedScore = true;
}
//1...节点连接(尾插)
void Tail_add_node(Stu* pHead, Stu* new1)
{
	Stu* pMove = pHead;
	while (pMove->next)
	{
		pMove = pMove->next;
	}
	pMove->next = new1;
}

//2.修改个人信息的方式[通过名字/学号找学生]
void Change_information(Stu* pHead)
{
	system("cls");
	int selectWay;//查找方式 
	Stu* pMove = pHead;
	printf("你想通过名字/学号修改学生信息:[1--名字/2--学号]");
	scanf("%d", &selectWay);
	getchar();
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

	default:
		break;
	}
	printf("未找到该学生,修改操作无效\n");
	getchar();
}
//2...修改信息选项
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

	int select;
	scanf("%d", &select);
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
		scanf("%s", newNumber);
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
	printf("修改成功.\n");
	getchar();
	return;
}
//2-4.改成绩
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
		ret = 0;
	}
	printf("数学成绩:%d ,是否要修改?\n[0-否;1-是]", student->m_MathScore);
	scanf("%d", &ret);
	while (ret)
	{
		printf("改为:");
		scanf("%d", &student->m_MathScore);
		ret = 0;
	}
	printf("英语成绩:%d ,是否要修改?\n[0-否;1-是]", student->m_EnglishScore);
	scanf("%d", &ret);
	while (ret)
	{
		printf("改为:");
		scanf("%d", &student->m_EnglishScore);
		ret = 0;
	}
	printf("程序成绩:%d ,是否要修改?\n[0-否;1-是]", student->m_programScore);
	scanf("%d", &ret);
	while (ret)
	{
		printf("改为:");
		scanf("%d", &student->m_programScore);
		ret = 0;
	}
	student->m_totalScore = student->m_ChineseScore + student->m_MathScore + student->m_EnglishScore + student->m_programScore;
	return;
}

//3.删除学生
void Delete_student(Stu* pHead)
{
	system("cls");
	int selectWay;
	Stu* pMove = pHead;
	Stu* prev = NULL;//稍后遍历的时候,用于保留指针pMove的前一位
	printf("你想通过名字/学号删除学生:[1--名字/2--学号]");
	scanf("%d", &selectWay);
	switch (selectWay)
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

	default:
		break;
	}
	printf(" _____________________________\n");
	printf("|  未找到该学生,删除操作无效  |\n");
	printf("|_____________________________|\n");
	getchar();
}

//4.查询个人信息[通过名字/学号找学生]
void Search_student(Stu* pHead)
{
	system("cls");
	int selectWay;//查找方式
	int ret = 1;//判断学生是否存在
	Stu* pMove = pHead;

	printf("你想通过名字/学号查找学生:[1--名字/2--学号]");
	scanf("%d", &selectWay);
	getchar();
	switch (selectWay)
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
				ret = 0;
				break;
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
		printf("|  未找到该学生  |\n");
		printf("|________________|\n");
		getchar();
	}

}
//4.个人信息
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

//5.排名种类选择[班级/全系]
void Rank_kindSelect(Stu* pHead)
{
	int ifSelect = 1;//选择是否继续
	int kindSelect = 0;
	printf("按照班级/全系排名[1-班级 2-全系]:");
	scanf("%d", &kindSelect);

	Stu* p_classHead = NULL;
	while (ifSelect)
	{
		switch (kindSelect)
		{
		case 1://班级排名
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
			Rank_subjectSelect(pHead);
			getchar();
			break;
		default:
			break;
		}
		printf("是否还要继续查看排名?[1-是 0-否]");
		scanf("%d", &ifSelect);
	}
}
//5...创建需要排名的班级
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
//5...按科目排名
void Rank_subjectSelect(Stu* pHead)
{
	system("cls");

	if (NULL == pHead->next || NULL == pHead->next)
	{
		printf("无该排名的相关数据录入,排名失败.");
		getchar();
		return;
	}
	int select_subject = 0;
	int ifSelect = 1;
	Stu* pMove = pHead;

	printf("你想按哪门的成绩排名:\n");
	printf("1.语文 2.数学 3.英语 4.程序 5.总分 6.退出\n");
	scanf("%d", &select_subject);
	getchar();
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
	default:
		break;
	}
}
//5...排名
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
		while (pre->next != NULL && pre->next->m_rankScore > p->m_rankScore)
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

//6.显示所有信息(不合格学生or全体学生)
void Show_all(Stu* pHead)
{
	system("cls");

	printf(" _______________________________________\n");
	printf("| 1.所有不合格的学生(不及格科目超过2科)\t|\n");
	printf("| 2.全体学生\t\t\t\t|\n");
	printf("| 3.返回\t\t\t\t|\n");
	printf(" ---------------------------------------\n");

	int select;
	scanf("%d", &select);

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
//6-1.所有不合格的学生
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
//6-2.全体学生
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

//加载数据
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
//7.退出前存档 
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
	getchar();
	fclose(fp);
}

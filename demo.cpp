//可存档,读档会出bug[已暂停该功能],原因可能:1.文件操作不当 2.字符编码不符
//排名效果不理想,准备快速实现排名表[涉及链表的排序方法],归并排序等


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

typedef struct Student {
	char m_name[20];         //姓名
	char m_number[20];       //学号
	int m_ChineseScore;      //语文成绩
	int m_MathScore;         //数学成绩
	int m_EnglishScore;      //英语成绩
	int m_programScore;      //程序设计成绩
	int m_totalScore;        //总分
	bool m_qualifiedScore;   //分数合格(不及格科目超过2科即为不合格)

	struct Student* next;    //指针域
}S;

//主页
void home_page()
{

	system("cls");

	printf("|---------------------------|\n");
	printf("|    DLNU成绩管理系统1.0    |\n");
	printf("|---------------------------|\n");
	printf("|       1.录入信息          |\n");
	printf("|       2.修改信息          |\n");
	printf("|       3.删除学生          |\n");
	printf("|       4.查询个人信息      |\n");
	printf("|       5.显示所有信息      |\n");
	printf("|       6.存档              |\n");
	printf("|---------------------------|\n");
	printf("  当前系统内共有%d名学生 \n");
	printf("------------------------------------\n");
	printf("| <输入1-6 选择功能,其他数字则退出> |\n");
	printf("|    注意: 为防止数据丢失,          |\n");
	printf("|  每次退出系统前请务必存档!        |\n");
	printf("------------------------------------\n");
}
//录入信息
S* Input_score();
//判断分数是否合格
void Judge_score(S* student);
//尾部节点连接
void Tail_add_node(S* head, S* new1);
//改成绩
void Change_score(S* student);
//修改信息
void Change_information(S* head);
//修改信息选项
void Change_information_selection(S* student);
//删除学生
void Delete_student(S* head);
//查询个人信息
void Search_student(S* head);
//查询个人信息选项[成绩or排名or学号]
void Search_student_option(S* head, S* student);
//查询个人分数
void Search_score(S* student);
void Search_Chinese_rank(S* head, S* student);
void Search_Math_rank(S* head, S* student);
void Search_English_rank(S* head, S* student);
void Search_Program_rank(S* head, S* student);
void Search_totalscore_rank(S* head, S* student);
//查询各门排名
void Search_score_rank(S* head, S* student);
//显示所有信息(不合格学生or全体学生)
void Show_all(S* head);
//显示所有不合格的学生
void Show_all_unqualified_student(S* head);
//显示全体学生
void Show_all_student(S* head);
//加载数据
void Load_data(S* head);
//数据存档
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
		case 1://录入成绩√
			printf("请输入你本次想录入成绩的人数:\n");
			scanf("%d", &N);
			for (int i = 0; i < N; i++)
			{
				system("cls");
				Tail_add_node(head, Input_score());
				printf("录入成功!\n");
				getchar();
			}
			break;
		case 2://修改信息
			Change_information(head);
			getchar();
			break;
		case 3://删除学生√
			printf("你想删除几个学生:");
			int deleteNumber;
			scanf("%d", &deleteNumber);
			for (int i = 0; i < deleteNumber; i++)
			{
				Delete_student(head);
			}
			getchar();
			break;
		case 4://查询个人信息√
			Search_student(head);
			getchar();
			break;
		case 5://显示所有信息
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


//录入信息
S* Input_score()
{
	S* newStudent = (S*)malloc(sizeof(S));
	memset(newStudent, 0, sizeof(S));
	newStudent->next = NULL;
	printf("姓名:");
	scanf("%s", newStudent->m_name);
	printf("学号:");
	scanf("%s", newStudent->m_number);
	printf("语文成绩:");
	scanf("%d", &newStudent->m_ChineseScore);
	printf("数学成绩:");
	scanf("%d", &newStudent->m_MathScore);
	printf("英语成绩:");
	scanf("%d", &newStudent->m_EnglishScore);
	printf("程序成绩:");
	scanf("%d", &newStudent->m_programScore);
	newStudent->m_totalScore = newStudent->m_ChineseScore + newStudent->m_MathScore + newStudent->m_EnglishScore + newStudent->m_programScore;
	Judge_score(newStudent);
	getchar();

	return newStudent;
}
//判断分数是否合格
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
//尾部节点连接
void Tail_add_node(S* head, S* new1)
{
	S* a = head;
	while (NULL != a->next)
	{
		a = a->next;
	}
	a->next = new1;
}
//改成绩
void Change_score(S* student)
{
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
//修改信息
void Change_information(S* head) {
	int select;
	S* a = head;
	printf("你想通过名字/学号修改学生信息:[1--名字/2--学号]");
	scanf("%d", &select);
	getchar();
	switch (select)
	{
	case 1://通过名字找
		char name[20];
		printf("名字:");
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
	case 2://通过学号找
		char number[20];
		printf("学号:");
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
	printf("未找到该学生,修改操作无效\n");
	getchar();
}
//修改信息选项
void Change_information_selection(S* student)
{
	printf("你想修改该同学的哪一项信息:\n");
	printf(" __________\n");
	printf("|1.名字    |\n");
	printf("|2.学号    |\n");
	printf("|3.成绩    |\n");
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
		getchar();
		break;
	case 2:
		printf("原学号%s,改为:", student->m_number);
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
	printf("修改成功.\n");
	return;
}
//删除学生
void Delete_student(S* head)
{
	int select;
	S* a = head;
	S* prev = NULL;//稍后遍历的时候,用于保留指针a的前一位
	printf("你想通过名字/学号删除学生:[1--名字/2--学号]");
	scanf("%d", &select);
	switch (select)
	{
	case 1:
		char name[20];
		printf("名字:");
		scanf("%s", name);
		while (NULL != a->next)
		{
			prev = a;
			a = a->next;
			if (!strcmp(name, a->m_name))
			{
				prev->next = a->next;
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
		while (NULL != a->next)
		{
			a = a->next;
			if (!strcmp(number, a->m_number))
			{
				prev->next = a->next;
				printf("删除成功!");
				getchar();
				return;
			}
		}
		break;

	default:
		break;
	}
	printf("未找到该学生,删除操作无效\n");
	getchar();
}

//查询个人信息(学号/名字查找学生)
void Search_student(S* head)
{
	int selectWay;//查找方式
	int selectWhat;//查询的内容
	int ret = 1;//判断学生是否存在
	S* a = head;
	printf("你想通过名字/学号查找学生:[1--名字/2--学号]");
	scanf("%d", &selectWay);
	getchar();
	switch (selectWay)
	{
	case 1:
		char name[20];
		printf("名字:");
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
		printf("学号:");
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
		printf("未找到该学生\n");
		getchar();
	}

}
//查询个人信息选项[成绩or排名or学号]
void Search_student_option(S* head, S* student)
{
	int selectOption;
	int select = 1;
	while (select) {
		printf("你想查询%s的\n", student->m_name);
		printf("---------------\n");
		printf("|  1.成绩      |\n");
		printf("|  2.排名      |\n");
		printf("|  3.学号      |\n");
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
			printf("%s的学号为%s\n", student->m_name, student->m_number);
			break;
		default:
			printf("错误!");
			getchar();
			break;
		}
		printf("请问还要继续查询该同学的信息吗?[1-是  0-否]\n");
		scanf("%d", &select);
	}
}
//查询个人分数
void Search_score(S* student)
{
	system("cls");
	printf("名字:%s\n", student->m_name);
	printf("学号:%s\n", student->m_number);
	printf("语文:%d\n", student->m_ChineseScore);
	printf("数学:%d\n", student->m_MathScore);
	printf("英语:%d\n", student->m_EnglishScore);
	printf("程序:%d\n", student->m_programScore);
	printf("总分:%d\n", student->m_totalScore);
}
void Search_Chinese_rank(S* head, S* student) {
	S* a = head;
	int rank = 1;
	while (NULL != a->next) {
		a = a->next;
		if (a->m_ChineseScore > student->m_ChineseScore)
			rank++;
	}
	printf("%s的语文分数为:%d,排名为:%d", student->m_name, student->m_ChineseScore, rank);
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
	printf("%s的数学分数为:%d,排名为:%d", student->m_name, student->m_MathScore, rank);
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
	printf("%s的英语分数为:%d,排名为:%d", student->m_name, student->m_EnglishScore, rank);
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
	printf("%s的程序分数为:%d,排名为:%d", student->m_name, student->m_programScore, rank);
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
	printf("%s的总分为:%d,排名为:%d", student->m_name, student->m_totalScore, rank);
	getchar();
}

//查询各门排名
void Search_score_rank(S* head, S* student)
{
	int select_subject;
	S* a = head;

	int select = 1;
	while (select) {
		printf("你想查询哪门的成绩排名:\n");
		printf("1.语文 2.数学 3.英语 4.程序 5.总分 6.退出\n");
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
		printf("请问还要继续查询该同学的成绩排名吗?[1-是  0-否]\n");
		scanf("%d", &select);
	}

}
//显示所有信息(不合格学生or全体学生)
void Show_all(S* head)
{
	printf(" _______________________________________\n");
	printf("| 1.所有不合格的学生(不及格科目超过2科)\t|\n");
	printf("| 2.全体学生\t\t\t\t|\n");
	printf("| 3.返回\t\t\t\t|\n");
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
//显示所有不合格的学生
void Show_all_unqualified_student(S* head)
{
	system("cls");
	S* a = head;
	printf("--------------------------------------------------------------------------------------------\n");
	printf("    学号    |    姓名    |    语文    |    数学    |    英语    |    程序    |    总成绩    |\n");
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
//显示全体学生
void Show_all_student(S* head)
{
	system("cls");
	S* a = head;
	printf("--------------------------------------------------------------------------------------------\n");
	printf("    学号    |    姓名    |    语文    |    数学    |    英语    |    程序    |    总成绩    |\n");
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
//加载数据
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
	printf("加载完毕!");
	getchar();

	fclose(fp);
}
//数据存档
void Archive_data(S* head)
{
	FILE* fp;
	S* a = head;
	if ((fp = fopen("student.txt", "w+")) == NULL)
	{
		printf("存档失败！");
	}
	else
	{
		while (NULL != a->next)
		{
			a = a->next;
			fprintf(fp, "%s\t%s\t%d\t%d\t%d\t%d\t%d\n", a->m_name, a->m_number, a->m_ChineseScore, a->m_MathScore, a->m_EnglishScore, a->m_programScore, a->m_totalScore, a->m_totalScore);
		}
	}

	printf("存档成功");
	getchar();
	getchar();
	fclose(fp);
}

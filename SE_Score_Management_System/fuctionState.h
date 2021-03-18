
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

//0-1加载数据
void Load_data(Stu* pHead);

//0-2.主页
void Home_page()
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
	printf("    |       7.存档              |\n");
	printf("    |       8.退出              |\n");
	printf("    |___________________________|\n");
	printf(" ------Made By:软件202班佟帅杰------\n");
	printf("|                                   |\n");
	printf("|   注意:                           |\n");
	printf("|  1.成绩均为整数,且满分为100       |\n");
	printf("|  2.学号不超过十位                 |\n");
	printf("|  3.若有重复名字,                  |\n");
	printf("|    请在其后加上\"(班级)\",          |\n");
	printf("|    例如:张三(2),张三(3)...        |\n");
	printf("|  4.非正常退出会造成新数据存档失败 |\n");
	printf("|___________________________________|\n");
}

//0-3选择功能 
void Select_fuction(Stu* pHead); 

//1-1.录入信息
void Input_new_student(Stu* pHead);
//1-2.判断分数是否合格
void Judge_score(Stu* student);
//1-3.节点连接(尾插)
void Tail_add_node(Stu* pHead, Stu* new1);

//2-1.找到要修改的学生[通过名字/学号找学生]
void Search_student_toChange(Stu* pHead);
//2-2.修改信息选项
void Change_information_selection(Stu* student);
//2-3.改成绩
void Change_score(Stu* student);

//3.删除学生
void Delete_student(Stu* pHead);

//4-1.查询个人信息[通过名字/学号找学生]
void Search_student(Stu* pHead);
//4-2.个人信息
void Show_studentInformation(Stu* student);

//5-1.排名种类选择[班级/全系]
void Rank_kindSelect(Stu* pHead);
//5-2.创建需要排名的班级
Stu* Build_rankClass(Stu* pHead, int rankClass);
//5-3.按科目排名
void Rank_subjectSelect(Stu* pHead);
//5-4.排名
void Rank_byScore(Stu* pHead, int subject);


//6-1.显示所有信息(不合格学生or全体学生)
void Show_all_selection(Stu* pHead);
//6-2.所有不合格的学生
void Show_all_unqualified_student(Stu* pHead);
//6-3.全体学生
void Show_all_student(Stu* pHead);

//7.存档 
void Save_data(Stu* pHead);


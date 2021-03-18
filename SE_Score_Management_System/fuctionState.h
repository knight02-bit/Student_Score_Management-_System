
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

//0-1��������
void Load_data(Stu* pHead);

//0-2.��ҳ
void Home_page()
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
	printf("    |       7.�浵              |\n");
	printf("    |       8.�˳�              |\n");
	printf("    |___________________________|\n");
	printf(" ------Made By:���202��١˧��------\n");
	printf("|                                   |\n");
	printf("|   ע��:                           |\n");
	printf("|  1.�ɼ���Ϊ����,������Ϊ100       |\n");
	printf("|  2.ѧ�Ų�����ʮλ                 |\n");
	printf("|  3.�����ظ�����,                  |\n");
	printf("|    ����������\"(�༶)\",          |\n");
	printf("|    ����:����(2),����(3)...        |\n");
	printf("|  4.�������˳�����������ݴ浵ʧ�� |\n");
	printf("|___________________________________|\n");
}

//0-3ѡ���� 
void Select_fuction(Stu* pHead); 

//1-1.¼����Ϣ
void Input_new_student(Stu* pHead);
//1-2.�жϷ����Ƿ�ϸ�
void Judge_score(Stu* student);
//1-3.�ڵ�����(β��)
void Tail_add_node(Stu* pHead, Stu* new1);

//2-1.�ҵ�Ҫ�޸ĵ�ѧ��[ͨ������/ѧ����ѧ��]
void Search_student_toChange(Stu* pHead);
//2-2.�޸���Ϣѡ��
void Change_information_selection(Stu* student);
//2-3.�ĳɼ�
void Change_score(Stu* student);

//3.ɾ��ѧ��
void Delete_student(Stu* pHead);

//4-1.��ѯ������Ϣ[ͨ������/ѧ����ѧ��]
void Search_student(Stu* pHead);
//4-2.������Ϣ
void Show_studentInformation(Stu* student);

//5-1.��������ѡ��[�༶/ȫϵ]
void Rank_kindSelect(Stu* pHead);
//5-2.������Ҫ�����İ༶
Stu* Build_rankClass(Stu* pHead, int rankClass);
//5-3.����Ŀ����
void Rank_subjectSelect(Stu* pHead);
//5-4.����
void Rank_byScore(Stu* pHead, int subject);


//6-1.��ʾ������Ϣ(���ϸ�ѧ��orȫ��ѧ��)
void Show_all_selection(Stu* pHead);
//6-2.���в��ϸ��ѧ��
void Show_all_unqualified_student(Stu* pHead);
//6-3.ȫ��ѧ��
void Show_all_student(Stu* pHead);

//7.�浵 
void Save_data(Stu* pHead);


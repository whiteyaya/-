#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<string>
#include <ctime>
#include <cstdlib>
#include<windows.h>
#define COURSE_NUM 20
#define STUDENT_NUM 90
using namespace std;

//��out�з���num��0~n-1�Ĳ��ظ������
void MyRand(int num,int n, vector<int> &out)
{
    for (int i = 0; i < num; i++)
    {
        int flag = 0;
        int t = rand() % n;
        for (int j = 0; j < i; j++)
        {
            if (out[j] == t)
            {
                i--;
                flag = 1;
                break;
            }
        }
        if(!flag) out.push_back(t);
    }
}

typedef class stu
{
public:
    stu() 
    {
        for (int i = 0; i < COURSE_NUM; i++)
        {
            absent[i] = true;//Ĭ��ȫ��ϯ
        }
    }
    //5~8������ȱ��80%
    void chasheng()
    {
        vector<int> abs;
        //ѡȡ�ò������ϿεĿ�--4��
        MyRand(4, 20, abs);
        for (int i = 0; i < 4; i++)
        {
            absent[abs[i]] = false;
        }
        for (int i = 0; i < COURSE_NUM; i++)
        {
            absent[i] = !absent[i];
        }
    }

    bool absent[COURSE_NUM];  //�������
}Student;

typedef class clas
{
public:
    clas()
    {
        //���ɲ�������--5~8
        int num_bad_stu = 5 + rand() % 4;
        //���ɲ�������--0~89
        vector<int> bad_stu;
        MyRand(num_bad_stu,90, bad_stu);
        for (auto& e : bad_stu)
        {
            cout << "��פ������" << e << endl;
        }
        
        //���ò���20�οε�ȱ�����
        for (int i = 0; i < num_bad_stu; i++)
        {
            size_t idx = bad_stu[i];
            stus[idx].chasheng();
        }
        //����20�οθ�0~3�����ȱ��ѧ��
        for (int i = 0; i < COURSE_NUM; i++)
        {
            //����0~3���ȱ��ѧ��
            int num_rand_bad = rand() % 4;
            for (int j = 0; j < num_rand_bad; j++)
            {
                //���ɳ�����������ȱ��ѧ������
                int s = rand() % 90;
                cout << "���ȱ��" << i << ':' << s << endl;
                if (stus[s].absent[i] == false)
                {
                    j--;
                }
                else
                {
                    stus[s].absent[i] = false;
                }
            }
            
        }
    }

    Student stus[STUDENT_NUM];
}Class;

void Save(const vector<Class> &class_list)
{
    FILE* fp;
    fp = fopen("data_class.txt", "w+");
    for (int i = 0; i < 5; i++)
    {
        fprintf(fp,"course %d:\n", i);
        for (int j = 0; j < 20; j++)
        {
            for (auto& e : class_list[i].stus)
            {
                fprintf(fp, "%d", e.absent[j]);
            }
            fprintf(fp, "\n");
        }
    }
    fclose(fp);

    fp = fopen("data_student.txt", "w+");
    for (int i = 0; i < 5; i++)
    {
        fprintf(fp, "course %d:\n", i);
            for (auto& e : class_list[i].stus)
            {
                for (auto& a : e.absent)
                {
                    fprintf(fp, "%d", a);
                }
                fprintf(fp, "\n");
            }
    }
    fclose(fp);
}

int main()
{
    //��ʼ�������������
    srand((unsigned)time(NULL));

    //����5~8
    int k = 5 + rand() % 4;
    vector<Class> class_list;
    for (int i = 0; i < 5; i++)
    {
        class_list.push_back(*new Class);
    }

    Save(class_list);

    return 0;
}
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

//在out中返回num个0~n-1的不重复随机数
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
            absent[i] = true;//默认全出席
        }
    }
    //5~8名差生缺课80%
    void chasheng()
    {
        vector<int> abs;
        //选取该差生来上课的课--4门
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

    bool absent[COURSE_NUM];  //到达情况
}Student;

typedef class clas
{
public:
    clas()
    {
        //生成差生个数--5~8
        int num_bad_stu = 5 + rand() % 4;
        //生成差生号码--0~89
        vector<int> bad_stu;
        MyRand(num_bad_stu,90, bad_stu);
        for (auto& e : bad_stu)
        {
            cout << "常驻差生：" << e << endl;
        }
        
        //设置差生20次课的缺课情况
        for (int i = 0; i < num_bad_stu; i++)
        {
            size_t idx = bad_stu[i];
            stus[idx].chasheng();
        }
        //生成20次课各0~3名随机缺课学生
        for (int i = 0; i < COURSE_NUM; i++)
        {
            //生成0~3随机缺课学生
            int num_rand_bad = rand() % 4;
            for (int j = 0; j < num_rand_bad; j++)
            {
                //生成除差生外的随机缺勤学生号码
                int s = rand() % 90;
                cout << "随机缺课" << i << ':' << s << endl;
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
    //初始化随机数发生器
    srand((unsigned)time(NULL));

    //生成5~8
    int k = 5 + rand() % 4;
    vector<Class> class_list;
    for (int i = 0; i < 5; i++)
    {
        class_list.push_back(*new Class);
    }

    Save(class_list);

    return 0;
}
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <ctime>
#include <cstdlib>
#include<windows.h>
#define COURSE_NUM 20
#define STUDENT_NUM 90
using namespace std;


void MyRand(int num,int n, int out[])
{
    for (int i = 0; i < num; i++)
    {
        out[i] = rand() % (n);
        for (int j = 0; j < i; j++)
        {
            if (out[j] == out[i])
            {
                i--;
                break;
            }
        }
    }
}

typedef class stu
{
public:
    stu() 
    {
        num = 0;
        for (int i = 0; i < COURSE_NUM; i++)
        {
            absent[i] = 1;
        }
    }
    void chasheng()
    {
        int abs[10];
        MyRand(4, 20, abs);
        for (int i = 0; i < 4; i++)
        {
            absent[abs[i]] = 0;
        }
        for (int i = 0; i < COURSE_NUM; i++)
        {
            absent[i] = !absent[i];
        }
    }

    int num;//学号
    bool absent[COURSE_NUM+1];  //到达情况
}Student;

typedef class clas
{
public:
    clas()
    {
        int k = 5 + rand() % 4;
        //cout << "差生有：" << k << endl;
        int queke [20] ={ 0 };
        MyRand(k,90, queke);
        
        for (int i = 0; i < k; i++)
        {
           cout << queke[i] << endl;
            stus[queke[i]].chasheng();
        }
        
        for (int i = 0; i < 20; i++)
        {
            int t = rand() % 4;
            for (int j = 0; j < t; j++)
            {
                int s = rand() % 90;
                if (stus[s].absent[i] == false)
                {
                    j--;
                    break;
                }
                else
                {
                    cout << "第" << i << "节课的 " << s << endl;
                    stus[s].absent[i] = false;
                }
            }
            
        }
    }
private:
    int num; //总学生数
    Student stus[STUDENT_NUM];
}Class;

int main()
{
    //初始化随机数发生器
    srand((unsigned)time(NULL));
    /*while (1){
        cout << 5 + rand() % 4 << endl;
        Sleep(100);
    }*/

    //生成5~8
    int k = 5 + rand() % 4;
    Class c[5];








    return 0;
}
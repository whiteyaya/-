#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<string>
#include <ctime>
#include <cstdlib>
#include<algorithm>

#define CLASS_NUM 20
#define COURSE_NUM 5
#define STUDENT_NUM 90

#define CLASSDATA_PATH "../data/data_class.txt"
#define GRADEDATA_PATH "../data/data_grade.txt"

using namespace std;

vector<double> bad;
vector<double> normal;

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
    stu():_gender(0),_bad_stu(false)
    {
        for (int i = 0; i < CLASS_NUM; i++)
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
        for (int i = 0; i < CLASS_NUM; i++)
        {
            absent[i] = !absent[i];
        }
    }

    void SetGender()
    {
        //是差生
        if (_bad_stu)
        {
            int t = rand() % 7;
            if (t == 0)//六分之一
            {
                //2~4
                _gender= 200+rand() % 201;
            }
            else
            {
                //2~2.7
                _gender = 200+rand() % 51;
            }
            bad.push_back(_gender/100);

        }
        //普通生
        else
        {
            int t = rand() % 6;
            if (t == 0)//四分之一
            {
                //2~4
                _gender = 210+rand() % 191;
            }
            else if (t == 1)
            {
                //3.5~4
                _gender = 350 + rand() % 51;
            }
            else
            {
                //3~3.8
                _gender = 300 + rand() % 81;
            }
            normal.push_back(_gender / 100);
        }
        _gender /= 100;
    }

    bool absent[CLASS_NUM];  //到达情况
    bool _bad_stu;    //是否差生
    double _gender;  //绩点

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
            //cout << "常驻差生：" << e << endl;
            stus[e]._bad_stu = true;
        }
        
        //设置差生20次课的缺课情况
        for (int i = 0; i < num_bad_stu; i++)
        {
            size_t idx = bad_stu[i];
            stus[idx].chasheng();
        }
        //生成20次课各0~3名随机缺课学生
        for (int i = 0; i < CLASS_NUM; i++)
        {
            //生成0~3随机缺课学生
            int num_rand_bad = rand() % 4;
            for (int j = 0; j < num_rand_bad; j++)
            {
                //生成除差生外的随机缺勤学生号码
                int s = rand() % 90;
               // cout << "随机缺课" << i << ':' << s << endl;
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

        for (int i = 0; i < STUDENT_NUM; i++)
        {
            stus[i].SetGender();
        }
    }


    
    Student stus[STUDENT_NUM];
}Class;

void Save(const vector<Class> &class_list)
{
    FILE* fp;
    fp = fopen(CLASSDATA_PATH, "w+");
    for (int i = 0; i < COURSE_NUM; i++)
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

    
    fp = fopen(GRADEDATA_PATH, "w+");
    for (int i = 0; i < COURSE_NUM; i++)
    {
        for (auto& e : class_list[i].stus)
        {
                fprintf(fp, "%.2lf ", e._gender);
        }
        fprintf(fp, "\n");
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
    for (int i = 0; i < COURSE_NUM; i++)
    {
        class_list.push_back(*new Class);
    }

    Save(class_list);
    sort(bad.begin(), bad.end());

    ////cout << "差生绩点" << endl;
    //for (auto& e : bad)
    //{
    //    cout << e << endl;
    //}
    //sort(normal.begin(), normal.end());
    ////cout << "普通绩点" << endl;
    //for (auto& e : normal)
    //{
    //    cout << e << endl;
    //}
    return 0;
}
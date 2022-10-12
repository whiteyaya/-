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
    stu():_gender(0),_bad_stu(false)
    {
        for (int i = 0; i < CLASS_NUM; i++)
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
        for (int i = 0; i < CLASS_NUM; i++)
        {
            absent[i] = !absent[i];
        }
    }

    void SetGender()
    {
        //�ǲ���
        if (_bad_stu)
        {
            int t = rand() % 7;
            if (t == 0)//����֮һ
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
        //��ͨ��
        else
        {
            int t = rand() % 6;
            if (t == 0)//�ķ�֮һ
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

    bool absent[CLASS_NUM];  //�������
    bool _bad_stu;    //�Ƿ����
    double _gender;  //����

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
            //cout << "��פ������" << e << endl;
            stus[e]._bad_stu = true;
        }
        
        //���ò���20�οε�ȱ�����
        for (int i = 0; i < num_bad_stu; i++)
        {
            size_t idx = bad_stu[i];
            stus[idx].chasheng();
        }
        //����20�οθ�0~3�����ȱ��ѧ��
        for (int i = 0; i < CLASS_NUM; i++)
        {
            //����0~3���ȱ��ѧ��
            int num_rand_bad = rand() % 4;
            for (int j = 0; j < num_rand_bad; j++)
            {
                //���ɳ�����������ȱ��ѧ������
                int s = rand() % 90;
               // cout << "���ȱ��" << i << ':' << s << endl;
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
    //��ʼ�������������
    srand((unsigned)time(NULL));

    //����5~8
    int k = 5 + rand() % 4;
    vector<Class> class_list;
    for (int i = 0; i < COURSE_NUM; i++)
    {
        class_list.push_back(*new Class);
    }

    Save(class_list);
    sort(bad.begin(), bad.end());

    ////cout << "��������" << endl;
    //for (auto& e : bad)
    //{
    //    cout << e << endl;
    //}
    //sort(normal.begin(), normal.end());
    ////cout << "��ͨ����" << endl;
    //for (auto& e : normal)
    //{
    //    cout << e << endl;
    //}
    return 0;
}
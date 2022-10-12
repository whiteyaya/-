#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<string>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include<windows.h>
#include<fstream>
#define _CRT_SECURE_NO_WARNINGS
#define CLASS_NUM 5
#define COURSE_NUM 20
#define STUDENT_NUM 90
#define CLASSDATA_PATH "../data/data_class.txt"
#define GRADEDATA_PATH "../data/data_grade.txt"

using namespace std;

double YE = 0;
double E = 0;
FILE* fq;
double jidian[CLASS_NUM][STUDENT_NUM];
void maopao(int a[], int b) {
	int i, j, t, n = STUDENT_NUM * 2 / 3;
	for (i = 1; i <= n; i++)
	{
		t = 1;
		for (j = n; j > i; j--)
			if (jidian[b][a[j]] < jidian[b][a[j - 1]]) {
				swap(a[j], a[j - 1]);
				t = 0;
			}
		if (t)
			break;
	}
}
class clas {
public:
	string poi[COURSE_NUM];
};
int main() {
	int u;
	clas myclass[CLASS_NUM]{};
	string rbq;
	ifstream fp;
	fp.open(CLASSDATA_PATH, ios::in);
	for (int i = 0; i < CLASS_NUM; i++) {
		getline(fp, rbq);
		for (int j = 0; j < COURSE_NUM; j++) {
			getline(fp, myclass[i].poi[j]);
		}
	}
	fp.close();

	fopen_s(&fq, GRADEDATA_PATH, "r");
	for (int i = 0; i < CLASS_NUM; i++) {
		for (int j = 0; j < STUDENT_NUM - 1; j++) {
			fscanf_s(fq, "%lf ", &jidian[i][j]);
			u = j + 1;
		}

		fscanf_s(fq, "%lf\n", &jidian[i][u]);
	}
	fclose(fq);
	for (int i = 0; i < CLASS_NUM; i++) {
		int mpoi[11] = { 0 };
		int npoi[11] = { 0 };
		int spoi[STUDENT_NUM] = { 0 };
		int u = 0, k;
		int temp[STUDENT_NUM] = { 0 };
		cout << "course:" << i << endl;
		for (int j = 0; j < COURSE_NUM; j++) {
			cout << "class:" << j<<":";
			int t = 0;
			int g = 0;
			if (j < 3) {
				for (u = 0, k = j * STUDENT_NUM * 2 / 3; k < (j + 1) * STUDENT_NUM * 2 / 3; k++) {
					if (k >= STUDENT_NUM) u = k % STUDENT_NUM;
					else u = k;
					temp[g++] = u;
				}
				maopao(temp, i);
				for (k = 0; k < STUDENT_NUM * 1 / 10; k++) {
					u = temp[k];
					cout << u << " ";
					if (myclass[i].poi[j][u] == '0') {
						t++;
						if (spoi[u] != 1)
							for (int l = 0; l < 11; l++) {
								if (mpoi[l] == 0) {
									mpoi[l] = u + 1;
									spoi[u] = 1;
									break;
								}
							}
						YE++;
					}
					E++;
					//if (t == 2)break;
				}

			}
			else {

				for (int l = 0; l < 11; l++) {
					if (mpoi[l] == 0)continue;
					int m = mpoi[l] - 1;
					cout << m << " ";
					if (myclass[i].poi[j][m] == '0') {
						YE++;
						npoi[l]--;
					}
					else npoi[l]++;
					if (npoi[l] == 2) mpoi[l] = 0;
					E++;
				}
			}
			cout << endl;
		}
		cout << endl;
	}
	E = YE / E;
	FILE* fpp;
	fpp = fopen("E_data.txt", "a+");
	cout << E;
	fprintf(fpp, "%.3lf\n", E);
	fclose(fpp);
}
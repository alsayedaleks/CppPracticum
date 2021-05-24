#include "Random-2.h"
#include <stdlib.h>
#include <time.h>

int errors_counter;

Parameters _params(int a, int c, int m, int s0) {
	Parameters ret;
	ret.a = a;
	ret.c = c;
	ret.m = m;
	ret.s0 = 0;
	return ret;
}

void reportError(char* msg) {
	printf("������� �����: %s\n", msg);
	errors_counter++;
}

void test_checkParametersConds() {
	// m - ���������� � �������� ����������� �������
	if (checkParametersConds(_params(1, 1, 1, 1)) || checkParametersConds(_params(2, 1, 1, 1))
		|| checkParametersConds(_params(1, 2, 1, 1)) || checkParametersConds(_params(1, 1, 1, 2))) {
		reportError("checkParametersConds(): �������� m, �� �� � ������������ ���������");
	}
	if (checkParametersConds(_params(1, 1, -1, 1))) {
		reportError("checkParametersConds(): �������� ��'���� m");
	}

	// a) m = 2^k, �� k -- ���������� �����
	if (checkParametersConds(_params(1, 1, 56, 1))) {
		reportError("checkParametersConds(): �������� m, �� �� � �������� 2");
	}

	// b) c ��  m - ������ ����� �����
	//    (����������� ��, �� m = 2^k)
	if (checkParametersConds(_params(1, 2, 256, 1))) {
		reportError("checkParametersConds(): �������� � �� ������ ������ � m");
	}

	// c) (a-1) ������� �� �� ����� �����, �� � ��������� m
	//    (������������� ��, �� m = 2^k)
	if (checkParametersConds(_params(4, 1, 256, 1))) {
		reportError("checkParametersConds(): �������� �, �� �� �������� ��� �����");
	}

	// d) c*(a-1) ������� �� 4:
	if (checkParametersConds(_params(4, 7, 256, 1))) {
		reportError("checkParametersConds(): ��������(�,c), �� �� �������� ��� �����");
	}
}


void test_task1_genParameters(int n) {
	for (int i = 0; i < n; i++) {
		if (!checkParametersConds(task1_genParameters())) {
			reportError("task1_genParameters(): wrong parameters generated");
			return;
		}
	}
}


void test_task3_hash_params() {
	Parameters p0 = task1_genParameters();
	Parameters p1;
	p1.a = p0.a;
	p1.c = p0.c;
	p1.m = p0.m;
	p1.s0 = p0.s0;
	task3_hash_params(&p1);
	Parameters p2;
	p2.a = p1.a;
	p2.c = p1.c;
	p2.m = p1.m;
	p2.s0 = p1.s0;
	task3_hash_params(&p2);
	if (p1.s0 == p0.s0 && p2.s0 == p1.s0) {
		reportError("task3_hash_params(): ������������� s0 �� ���������� �� ��������� �������");
	}
}


void test_task2_int_rnd() {
	Parameters params = task1_genParameters();
	if (checkParametersConds(params)) {
		task3_hash_params(&params);
		int num = 1000;
		int pval = -1;
		for (int i = 0; i < num; i++) {
			int val = task2_int_rnd(&params);
			if (val == pval) {
				reportError("task2_int_rnd(): ��������� ����� �������� ��������");
				return;
			}
			if (val < 0 || val >= params.m) {
				reportError("task2_int_rnd(): ��������� ����� �������� �� ������ ��������");
				return;
			}
			pval = val;
		}
	}
	else {
		reportError("task2_int_rnd(): ������� ��������� ��������� ��� �����");
	}
}

void test_task2_double_rnd() {
	Parameters params = task1_genParameters();
	if (checkParametersConds(params)) {
		task3_hash_params(&params);
		int num = 1000;
		double pval = -1;
		for (int i = 0; i < num; i++) {
			double val = task2_double_rnd(&params);
			if (val == pval) {
				reportError("task2_double_rnd(): ������� ����� ����।�� ���祭��");
				return;
			}
			if (val < 0.0 || val >= 1.0) {
				reportError("task2_double_rnd(): ������� ����� ���祭�� �� ������ �?�������");
				return;
			}
			pval = val;
		}
	}
	else {
		reportError("task2_double_rnd(): ������� �⢮७�� ��ࠬ���?� ��� ����");
	}
}


int main(char** args) {
	errors_counter = 0;
	srand(time(NULL));

	printf("test_checkParametersConds()...\n");
	test_checkParametersConds();

	printf("test_task1_genParameters()...\n");
	test_task1_genParameters(100);

	printf("test_task2_int_rnd()...\n");
	test_task2_int_rnd();

	printf("test_task2_double_rnd()...\n");
	test_task2_double_rnd();

	printf("test_task3_hash_params()...\n");
	test_task3_hash_params();

	if (errors_counter > 0) {
		printf("�������? ������� � ஡��? � �����: %d", errors_counter);
	}
	else {
		printf("Tests ok");
	}
	scanf_s("%d", &errors_counter);
	return 0;
}

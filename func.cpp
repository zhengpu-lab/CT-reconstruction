#include "func.h"
#include <iostream>
//�����Զ���ͷ�ļ�

// ����ʵ��
int sum(int a, int b) {
	return a + b;
}

int min(int a, int b) {
	if (a >= b) {
		return b;
	}
	else {
		return a;
	}
}
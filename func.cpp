#include "func.h"
#include <iostream>
//引入自定义头文件

// 函数实现
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
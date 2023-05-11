#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
int xA, yA, xB, yB, L;
int x1, yy1, x2, y2, x3, y3;
double f (double x) {
	double C1 = L*L + (x-xB)*(x-xB) - 
				(x-xA)*(x-xA) + yB*yB - yA*yA;
	double C2 = 4*L*L*((x-xB)*(x-xB) + yB*yB);
	double k1 = 2*(yA - yB);
	double a = 4*L*L - k1*k1;
	double b = -8*L*L*yB - 2*k1*C1;
	double c = C2 - C1*C1;
	double delta = b*b - 4*a*c;
	if(delta < 0)		return 0;
	double Y1 = (-b + sqrt(delta)) / (2*a), 
		   Y2 = (-b - sqrt(delta)) / (2*a);
	if(Y1 > Y2)		swap(Y1, Y2);
	double Y3 = 0, Y4 = 0, 
		   Y5 = 2000, Y6 = 2000, Y7 = 2000;
	bool haveans = 0;
	if(x1 <= x && x <= x2) {
		if(x1 == x2)
			Y3 = (double)min(yy1, y2), 
			Y4 = (double)max(yy1, y2),
			haveans = 1;
		else 
			Y5 = (double)(y2-yy1) / 
				 (x2-x1) * (x-x1) + yy1;
	}
	if(x2 <= x && x <= x3) {
		if(x2 == x3)
			Y3 = (double)min(y2, y3), 
			Y4 = (double)max(y2, y3),
			haveans = 1;
		else 
			Y6 = (double)(y3-y2) / 
				 (x3-x2) * (x-x2) + y2;
	}
	if(x1 <= x && x <= x3) {
		if(x1 == x3)
			Y3 = (double)min(yy1, y3),
			Y4 = (double)max(yy1, y3),
			haveans = 1;
		else 
			Y7 = (double)(y3-yy1) / 
				 (x3-x1) * (x-x1) + yy1;
	}
	if(haveans == 0) {
		Y3 = 2000;
		Y3 = min(Y3, Y5);
		Y3 = min(Y3, Y6);
		Y3 = min(Y3, Y7);
	} 
	if(haveans == 0) {
		Y4 = -2000;
		if(Y5 != 2000) 	Y4 = max(Y4, Y5);
		if(Y6 != 2000) 	Y4 = max(Y4, Y6);
		if(Y7 != 2000) 	Y4 = max(Y4, Y7);
	} 
	if(Y3 > Y4)			return 0;
	double Yy = max(Y1, Y3);
	double Yx = min(Y2, Y4);
	return Yx - Yy > 0? Yx - Yy:0;
}

//ţ�١����ƴĹ�ʽ�����ϵ��
double C[8][9] = { {}, {2, 1,1}, {6, 1, 4,1}, {8, 1, 3,3,1}, {90, 7, 32, 12,32,7}, {288, 19, 75, 50,50,75,19}, {840, 41, 216, 27, 272,27,216,41},
{17280, 751, 3577,1323, 2989,2989,1323,3577,751} };
double Newton_Cotes(double a, double b) {
	for(int N = 1; N <= 7; N++) {
		double h = (b - a) / N;
		double sum = 0;
		for (int n = 0; n <= N+1; n++) 
			sum += C[N][n] * f(a + h*n);
		sum = sum / C[N][0] * (b - a);
		printf("%d: %0.6lf\n", N, sum);
	}
}
int main () {
	scanf("%d%d%d%d%d", &xA, &yA, &xB, &yB, &L);
	scanf("%d%d%d%d%d%d", &x1, &yy1, &x2, &y2, &x3, &y3);
	if(xA > xB)		swap(xA, xB), swap(yA, yB);
	if(x1 > x2)		swap(x1, x2), swap(yy1, y2);
	if(x2 > x3)		swap(x2, x3), swap(y2, y3);
	if(x1 > x2)		swap(x1, x2), swap(yy1, y2);
	Newton_Cotes(x1, x3);
	system("pause"); 
	return 0;
}

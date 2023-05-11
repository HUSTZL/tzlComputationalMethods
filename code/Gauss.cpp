#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include<string>
#include<iomanip>
using namespace std;
long double X[9];
long double A[9];
void init(int n) {
	long double x1, x2, x3, x4, x5, x6, x7, x8, x9; //插值点
	long double A1, A2, A3, A4, A5, A6, A7, A8, A9; // 求积系数
	n = n+1;
	if (n == 1) {
		x1 = 0;
		x2 = 0;
		x3 = 0;
		x4 = 0;
		x5 = 0;
		x6 = 0;
		x7 = 0;
		x8 = 0;
		A1 = 2;
		A2 = 0;
		A3 = 0;
		A4 = 0;
		A5 = 0;
		A6 = 0;
		A7 = 0;
		A8 = 0;
	}
	if (n == 2)	{
		x1 = -0.5773502692;
		x2 = +0.5773502692;
		x3 =  0;
		x4 =  0;
		x5 =  0;
		x6 =  0;
		x7 =  0;
		x8 =  0;
		A1 =  1;
		A2 =  1;
		A3 =  0;
		A4 =  0;
		A5 =  0;
		A6 =  0;
		A7 =  0;
		A8 =  0;
	}
	if (n == 3)	{
		x1 = -0.7745966692;
		x2 =  0;
		x3 = +0.7745966692;
		x4 =  0;
		x5 =  0;
		x6 =  0;
		x7 =  0;
		x8 =  0;
		A1 =  0.5555555556;
		A2 =  0.8888888889;
		A3 =  0.5555555556;
		A4 =  0;
		A5 =  0;
		A6 =  0;
		A7 =  0;
		A8 =  0;
	}
	if (n == 4)	{
		x1 = -0.8611363116;
		x2 = -0.3399810436;
		x3 = +0.3399810436;
		x4 = +0.8611363116;
		x5 =  0;
		x6 =  0;
		x7 =  0;
		x8 =  0;
		A1 =  0.3478548451;
		A2 =  0.6521451549;
		A3 =  0.6521451549;
		A4 =  0.3478548451;
		A5 =  0;
		A6 =  0;
		A7 =  0;
		A8 =  0;
	}
	if (n == 5)	{
		x1 = -0.9061798459;
		x2 = -0.5384693101;
		x3 =  0;
		x4 = +0.5384693101;
		x5 = +0.9061798459;
		x6 =  0;
		x7 =  0;
		x8 =  0;
		A1 =  0.2369268851;
		A2 =  0.4786286705;
		A3 =  0.5688888889;
		A4 =  0.4786286705;
		A5 =  0.2369268851;
		A6 =  0;
		A7 =  0;
		A8 =  0;
	}
	if (n == 6)	{
		x1 = -0.9324695142;
		x2 = -0.6612093865;
		x3 = -0.2386191861;
		x4 = +0.2386191861;
		x5 = +0.6612093865;
		x6 = +0.9324695142;
		x7 =  0;
		x8 =  0;
		A1 =  0.1713244924;
		A2 =  0.3607615730;
		A3 =  0.4679139346;
		A4 =  0.4679139346;
		A5 =  0.3607615730;
		A6 =  0.1713244924;
		A7 =  0;
		A8 =  0;
	}
	if (n == 7)	{
		x1 = -0.9491079123;
		x2 = -0.7415311856;
		x3 = -0.4058451514;
		x4 =  0;
		x5 = +0.4058451514;
		x6 = +0.7415311856;
		x7 = +0.9491079123;
		x8 =  0;
		A1 =  0.1294849662;
		A2 =  0.2797053915;
		A3 =  0.3818300505;
		A4 =  0.4179591837;
		A5 =  0.3818300505;
		A6 =  0.2797053915;
		A7 =  0.1294849662;
		A8 =  0;
	}
	if (n == 8)	{
		x1 = -0.9602898565;
		x2 = -0.7966664774;
		x3 = -0.5255324099;   
		x4 = -0.1834346425;
		x5 = +0.1834346425;
		x6 = +0.5255324099;   
		x7 = +0.7966664774;
		x8 = +0.9602898565;
		A1 =  0.1012285363;
		A2 =  0.2223810345;
		A3 =  0.3137066459;
		A4 =  0.3626837834;
		A5 =  0.3626837834;
		A6 =  0.3137066459;
		A7 =  0.2223810345;
		A8 =  0.1012285363;
	}
	X[1] = x1, X[2] = x2, X[3] = x3, X[4] = x4, X[5] = x5, X[6] = x6, X[7] = x7, X[8] = x8;
	for(int i = 0; i <= 7; i++)
		X[i] = X[i+1];
	A[1] = A1, A[2] = A2, A[3] = A3, A[4] = A4, A[5] = A5, A[6] = A6, A[7] = A7, A[8] = A8;
	for(int i = 0; i <= 7; i++)
		A[i] = A[i+1];
}
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
void Gauss(double a, double b) {
	double k = (b-a)/2, v = (a+b)/2;
	for(int N = 1; N <= 7; N++) {
		init(N);
		double sum = 0;
		for(int n = 0; n <= N+1; n++)
			sum += A[n] * f(k * X[n] + v);
		sum = sum * (b-a)/2;
		printf("%d: %0.6lf\n", N, sum);
	}
}
int main()
{
	scanf("%d%d%d%d%d", &xA, &yA, &xB, &yB, &L);
	scanf("%d%d%d%d%d%d", &x1, &yy1, &x2, &y2, &x3, &y3);
	if(xA > xB)		swap(xA, xB), swap(yA, yB);
	if(x1 > x2)		swap(x1, x2), swap(yy1, y2);
	if(x2 > x3)		swap(x2, x3), swap(y2, y3);
	if(x1 > x2)		swap(x1, x2), swap(yy1, y2);
	Gauss(x1, x3); 
	system("pause");
}


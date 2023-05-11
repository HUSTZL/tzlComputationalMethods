#include <cstdio>
#include <algorithm>
#include <cmath>
#include <ctime>
using namespace std;
double eps = 1e-7; 
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
void Romberg(double a, double b, int l) {
	clock_t startTime, endTime;
	//startTime = clock();
	double T[6][2000];
	T[0][0] = (b - a) / 2 * (f(a) + f(b));
	for(int m = 0; m <= l; m++)
		for(int i = 0; i <= l-m; i++) {
			if(m == 0) {
				if(i == 0)	continue; 
				T[0][i] = T[0][i-1]/2;
				for(int j = 1; j <= (1<<(i - 1)); j++) 
					T[0][i] += ((b - a) / (double)(1 << i)) * 
					f(a + (((double)(2*j-1) / (1 << i)) * (b - a)));			
			}
			else 
				T[m][i] = ((1 << (2*m)) * T[m-1][i+1] - T[m-1][i])/
						((1 << (2*m)) - 1);
		}
	for(int i = 1; ; i++) {
		T[0][i+l] = T[0][i+l-1]/2;
		for(int j = 1; j <= (1<<(i+l - 1)); j++) 
			T[0][i+l] += (b - a) / (double)(1 << (i+l)) * 
			f(a + ((double)(2*j-1) / (1 << (i+l)) * (b - a)));
		for(int m = 1; m <= l; m++)
			T[m][i+l-m] = ((1 << (2*m)) * T[m-1][i+l-m+1] - 
					T[m-1][i+l-m])/((1 << (2*m)) - 1);
		if(abs(T[l][i] - T[l][i-1]) < eps) {
			//endTime = clock();
			printf("%d: %0.6lf\n", l, T[l][i]);
			return ;
		}
	}	
} 
int main () {
	scanf("%d%d%d%d%d", &xA, &yA, &xB, &yB, &L);
	scanf("%d%d%d%d%d%d", &x1, &yy1, &x2, &y2, &x3, &y3);
	if(xA > xB)		swap(xA, xB), swap(yA, yB);
	if(x1 > x2)		swap(x1, x2), swap(yy1, y2);
	if(x2 > x3)		swap(x2, x3), swap(y2, y3);
	if(x1 > x2)		swap(x1, x2), swap(yy1, y2);
	for(int i = 0; i <= 5; i++)
		Romberg(x1, x3, i);
	system("pause");
	return 0;
}

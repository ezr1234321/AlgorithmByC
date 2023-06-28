#include<iostream>
#include<math.h>
#include<time.h>
#define BIG 200000
using namespace std;
int max[BIG] = { 0 };
int base[BIG] = { 0 };
int temp[BIG] = { 0 };
int max_size;
bool MillerRabin_Primality(int n,int k);
int test(int n, int i);
int n_n(int i, int n[]);
void reset();
void division(int x);
int main() {
	int n=1233, k=5;
	srand(time(NULL));
	clock_t startTime, endTime;
	cout << "n= " << n << " k= " << k << endl;
	startTime = clock();
	if (MillerRabin_Primality(n,k)) cout << "prime" << endl;
	else cout << "composite" << endl;
	endTime = clock();
	cout << "Totle Time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	system("pause");
	return 0;
}
bool MillerRabin_Primality(int n,int k) {
	int D = 0, A, R = 0;
	int X,temp,i=0,flag=0;
	if (n % 2 == 0)	return false;
	int N = n - 1;
	while (N % 2 == 0) {
		R++;
		N /= 2;
	}D = N;
	while (k > 1) {
		A = rand() % 10 + 2;
		
		temp = A;
		while (temp > 0) {//A -> max[]
			max[i] = temp % 10;
			base[i] = max[i];
			temp /= 10;
			i++;
		}
		test(D, i);
		division(n);
		X = max[0];reset();
		if (X == 1 || X == N) continue;
		for (int j = 0; j < R; j++) {
			X = (X*X)%n;
			if (X == 1) flag=1;
			if (X == N) flag=1;
		}
		k--;
	}
	if (flag == 0) return false;
	return true;
}
int test(int D, int i) {//ex: D=25
	int count = 0, odd = 0;
	if (D % 2 != 0) { odd = 1; D--; }
	int max_size = 2 * i;
	while (D % 2 == 0) {// D => (2*2*2)*3  
		D /= 2;
		count++;
	}
	while (D > 1) {// 1+1+1=3
		max_size = n_n(max_size, base);
		max_size += i;
		D--;
	}
	while (count > 0) {// 3+3=6 -> 6+6=12 -> 12+12=24
		max_size = n_n(max_size, max);
		max_size += i;
		count--;
	}
	if (odd == 1) { max_size = n_n(max_size, base); }//24+1 補上之前扣掉的值
	return 0;
}
int n_n(int i, int n[]) {
	cout << ".";
	max_size += i;
	if (max_size > BIG) { cout << "error"; return 0; }
	for (int j = 0; j < i; j++) {//陣列相乘
		if (n[j] == 0) continue;
		for (int k = 0; k + j < max_size; k++) {
			temp[j + k] += (n[j] * max[k]);
		}
	}
	int carry = 0;
	int h_b = 0, temp_i = 0;
	for (int j = max_size; j >= 0; j--) { max[j] = temp[j]; temp[j] = 0; }
	for (int j = max_size; j >= 0; j--) {
		for (int j = 0; j <= max_size; j++) {//進位處理
			max[j] += carry;
			carry = max[j] / 10;
			max[j] %= 10;
		}
		if (max[j] != 0) h_b = 1;
		if (h_b == 0) max_size--;
	}

	return max_size;
}
void reset() {
	for (int i = 0; i < BIG; i++) {
		max[i] = 0;
		base[i] = 0;
		temp[i] = 0;
	}
}
void division(int x) {//餘數
	for (int i = max_size; i > 0; i--) {
		int j = i - 1;
		max[j] += max[i] * 10;
		max[i] = 0;
		max[j] %= x;
	}
}
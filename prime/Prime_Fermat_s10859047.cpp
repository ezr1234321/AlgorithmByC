#include<iostream>
#include<math.h>
#include<vector>
#include<time.h>
#define BIG 200000
using namespace std;
void Fermat_Primality(int n, int k);
int test(int n, int i, int k);
int n_n(int i, int n[]);
void division(int x);
void print_max();
void reset();
int max[BIG] = { 0 };
int base[BIG] = { 0 };
int temp[BIG] = { 0 };
int max_size;
int main() {
	clock_t startTime, endTime;
	startTime = clock();
	
	int k = 2,n=101;
	cout << "n= " << n << " k= " << k << endl;
	srand(time(NULL));
	Fermat_Primality(n, k);
	endTime = clock();
	cout << "Totle Time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	system("pause");
	return 0;
}
int test(int n, int i, int k) {//x^n-1
	int count = 0;
	int c = n / 2, odd = 0;
	if (n % 2 != 0) { odd = 1; n--; }
	int max_size = 2 * i;
	while (n % 2 == 0) {
		n /= 2;
		count++;
	}
	while (n > 1) {
		max_size = n_n(max_size, base);
		max_size += i;
		n--;
	}
	for (int j = max_size; j >= 0; j--) cout << max[j]; cout << endl << endl;
	while (count > 0) {
		max_size = n_n(max_size, max);
		max_size += i;
		count--;
	}
	if (odd == 1) { max_size = n_n(max_size, base); }
	return 0;
}
int n_n(int i, int n[]) {
	max_size += i;
	if (max_size > BIG) { cout << "error"; return 0; }
	for (int j = 0; j < i; j++) {
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
	//	for (int j = max_size; j >= 0; j--) cout << max[j]; cout << endl << endl;
	return max_size;
}
void print_max() {
	int h_b = 0;
	for (int j = max_size; j >= 0; j--) {
		if (max[j] != 0) h_b = 1;
		if (h_b == 1) cout << max[j];
		else  max_size--;
	}
	cout << endl;
}
void division(int x) {
	for (int i = max_size; i > 0; i--) {
		int j = i - 1;
		max[j] += max[i] * 10;
		max[i] = 0;
		max[j] %= x;
	}
	cout << "max[0]= " << max[0] << endl;
	if (max[0] != 1) cout << "composite !" << endl;
	else cout << "Prime" << endl;
}
void reset() {
	for (int i = 0; i < BIG; i++) {
		max[i] = 0;
		base[i] = 0;
		temp[i] = 0;
	}
}
void Fermat_Primality(int n, int k) {
	while (k > 1) {
		int i = 0;
		int x = rand() % (n - 2) + 1; cout << "x= " << x << endl;
		while (x > 0) {
			max[i] = x % 10;
			base[i] = max[i];
			x /= 10;
			i++;
		}
		test(n - 1, i, k);
		print_max();
		division(n);
		reset();
		k--;
	}
}
#include<iostream>
#include<math.h>
#include<time.h>
using namespace std;
bool Basic_prime(int n);
int main() {
	clock_t startTime, endTime;
	startTime = clock();
	int n=123456;
	cout << "n=" << n << endl;
	if (Basic_prime(n)) cout << "prime" << endl;
	else cout << "composite" << endl;
	endTime = clock();
	cout << "Totle Time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	system("pause");
	return 0;
}
bool Basic_prime(int n) {
	for (int i = 2; i * i <= n; ++i)
	{
		if (n % i == 0) return false;
	}
	return true;
}
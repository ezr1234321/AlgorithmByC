#include<iostream>
#include<math.h>
#include<vector>
#include<time.h>
using namespace std;
bool Sieve_of_Eratosthenes(int n);

int main() {
	clock_t startTime, endTime;
	startTime = clock();
	int n = 1234567;
	cout << "n= " << n << endl;
	if (Sieve_of_Eratosthenes(n)) cout << "Prime" << endl;
	else cout << "composite" << endl;
	endTime = clock();
	cout << "Totle Time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	system("pause");
	return 0;
}
bool Sieve_of_Eratosthenes(int n) {
	vector<int> a(n + 1, 1);
	a[0] = a[1] = 0;
	for (int i = 2; i * i <= n; i++) {
		if (a[i])
			for (int j = i * i; j <= n; j += i)
				a[j] = 0;
	}
	//	for (int i = 2; i < a.size(); i++)//印出 1~n 所有質數
	//		if (a[i] == 1) cout << i << " ";

	if (a[a.size() - 1] == true) return true;
	
	return false;
}
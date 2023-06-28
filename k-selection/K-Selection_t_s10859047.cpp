#include "selection.h"
int main() {
	selection s;
	srand(time(NULL));
	clock_t starttime, endtime;
	int key, ctrl;
	cout << "Input smallest kth (range:1~500):";
	cin >> key;
	cout << endl 
		<<"Menu:"<<endl
		<< "(1).Insertion Sort+Select" << endl
		<< "(2).Merge Sort+Select" << endl
		<< "(3).Quick Sort+Select" << endl
		<< "(4).QuickSelction" << endl
		<< "(5).Median of Medians Select(gap=3)" << endl
		<< "(6).Median of Medians Select(gap=5)" << endl
		<< "(7).Median of Medians Select(gap=7)" << endl;
	cin >> ctrl;
	cout << endl << "====================================================" << endl;
	cout << "Unsort data:" << endl;
	s.Print_array();
	cout << endl << "====================================================" << endl;
	starttime = clock();
	switch (ctrl)
	{
	case 1:
		s.Insertion_sort();// endtime = clock();
		s.Print_array();
		cout << endl << "Answer :" << n[key - 1] << endl;
		break;
	case 2:
		s.Merge_sort(v, 0, Size - 1); //endtime = clock();
		s.Print_v();
		cout << endl << "Answer :" << v[key - 1] << endl;
		break;
	case 3:
		s.QuickSort(0, Size - 1, key); //endtime = clock();
		cout << endl;
		cout << endl << "Answer :" << n[key - 1] << endl;
		s.Print_array();
		break;
	case 4:
		cout <<"Answer :" <<s.qs_kth_smallest(n, 0, Size - 1, key); endtime = clock();
		s.Print_array();
		break;
	case 5:
		s.Median_of_Medians(v, key, 3);// endtime = clock();
		break;
	case 6:
		s.Median_of_Medians(v, key, 5);// endtime = clock();
		break;
	case 7:
		s.Median_of_Medians(v, key, 7);// endtime = clock();
		break;
	default:
		break;
	}
	endtime = clock();
	cout << "Total time " << (double)(endtime - starttime) / CLOCKS_PER_SEC << "s" << endl;
	system("pause");
	return 0;
}

#include"Header.h"

int main() {
	srand((unsigned)time(NULL) * 5000);
	BST T;
	TH th;
	Hash2 hash2;
	string a = "30";
	int ctrl;

	cout << endl << endl << "Menu ---------------------------------------------------------" << endl << endl;
	cout << 
		" 1 : BST" << endl <<
		" 2 : Treap" << endl <<
		" 3 : Hash(hashfunction : A mod B)" << endl <<
		" 4 : Hash(hashfunction : A * p^n mod B )" << endl <<
		" 5 : Compare All Text"
		<< endl << endl << "----------------------------------------------------------------" << endl << endl<<
		"Please choose function :";
	cin >> ctrl;
	srand(time(NULL));
	clock_t starttime, endtime;
	starttime=clock();
	switch (ctrl)
	{
	case 1:
		T.CreatDiction();
		T.Print();
		T.search(a);
		T.useremove(a);
		T.search(a);
		cout << endl << endl;
		T.Search_Diction();
		endtime = clock();
		break;
	case 2:

		th.CreatDiction();
		th.PrintTH();
		th.use_search(a);
		th.use_delete(a);
		th.use_search(a);
		cout << endl << endl;
		th.Search_Diction();
		endtime = clock();
		break;
	case 3:
		hash2.setarray();
		hash2.CreatDiction();
		hash2.PrintHash();
		hash2.SearchHash(a);
		hash2.DeleteHash(a);
		hash2.SearchHash(a);
		cout << endl << endl;
		hash2.Search_Dictionary();
		endtime = clock();
		break; 
	case 4:

		hash2.setarray();
		hash2.CreatDiction2();
		hash2.PrintHash();
		hash2.SearchHash2(a);
		hash2.DeleteHash2(a);
		hash2.SearchHash2(a);
		cout << endl << endl;
		hash2.Search_Dictionary2();
		endtime = clock();
		break;
	case 5:
		T.AlltextCompare();
		endtime = clock();
		break;
	default:
		break;
	}
	cout << "Total time " << (double)(endtime - starttime) / CLOCKS_PER_SEC << "s" << endl;
	system("pause");
	return 0;
}
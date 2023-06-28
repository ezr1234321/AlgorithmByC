#include"travel_map.h"
#include<time.h>
int main() {
	travel_map T;
	srand(time(NULL));
	clock_t starttime, endtime;

	T.ReadMapNode();
	T.graphZero();
	cout << "=======================(1)========================" << endl;
	
	starttime = clock();
	for (int i = 0; i < tempNode.size(); i++)
		cout << tempNode[i].name << " (x,y) " << tempNode[i].x << " " << tempNode[i].y << endl;
	cout << endl;
	T.ClosestorFarthest(tempNode, 1,true);
	T.graphPrint(tempNode);
	endtime = clock();
	cout << "Total time " << (double)(endtime - starttime) / CLOCKS_PER_SEC << "s" << endl;

	cout << endl<<"=======================(2)========================" << endl<<endl;
	starttime = clock();
	T.Graph_Area();
	cout << endl;
	T.graphPrint(tempNode);
	endtime = clock();
	cout << "Total time " << (double)(endtime - starttime) / CLOCKS_PER_SEC << "s" << endl;

	cout << endl << "=======================(3)========================" << endl << endl;

	starttime = clock();
	T.Convex_Hull_TSP();
	T.graphPrint(tempNode);
	endtime = clock();
	cout << "Total time " << (double)(endtime - starttime) / CLOCKS_PER_SEC << "s" << endl;

	starttime = clock();
	T.ClosestorFarthest(tempNode, 2, true);//初始graph
	endtime = clock();
	cout << "Total time " << (double)(endtime - starttime) / CLOCKS_PER_SEC << "s" << endl;

	starttime = clock();
 	T.TSP();
	endtime = clock();
	cout << "Total time " << (double)(endtime - starttime) / CLOCKS_PER_SEC << "s" << endl;
	cout << endl<<"d_convex: "<<Convex_Hull_MIN<<endl<<"d_TSP"<<TSP_MIN<<endl<<"d_convex/d_TSP: " << TSP_MIN / Convex_Hull_MIN;

	cout << endl << "=======================(4)========================" << endl << endl;
	//T.Hungarian_mrthod();//未完成
	system("pause");
	return 0;
}
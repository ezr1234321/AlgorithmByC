#pragma once
#include<iostream>
#include<iterator>
#include<string>
#include<fstream>
#include<math.h>
#include<iomanip>
#include<vector>
#define Max_size 50
using namespace std;
double**graph;
struct node {
	double x, y;
	char name;
};
struct node newnode(double a,double b,char name) {
	node n;
	n.x = a;
	n.y = b;
	n.name = name;
	return n;
};
vector<node> tempNode;
vector <node> N;//裝外圈的點
vector<node> NotInN;//內圈的點
vector<int> ng_order;
double TSP_MIN = INTMAX_MAX;
double Convex_Hull_MIN = 0;
class travel_map {
private:
	vector <double> row;
	vector<vector<double>> graph;
public:
	double computer(node a, node b, node c);
	void ReadMapNode();
	void graphRange(vector<node>& N);
	void ClosestorFarthest(vector<node> t, int ctrl,bool add);// ctrl :1.印最短2點 ,0.印最長2點  add:1 加進graph
	void Graph_Area();
	void graphZero() {
		row.assign(tempNode.size(), 0);
		graph.assign(tempNode.size(), row);
	}
	void graphPrint(vector<node> Node) {
		for (int i = 0; i < Node.size(); i++) cout << "    [" << Node[i].name << "]   ";
			cout << endl;
		for (int i = 0; i < Node.size(); i++) {
			cout << "[" << Node[i].name << "] ";
			for (int j = 0; j < Node.size(); j++)
				cout << graph[i][j] << " ";
			cout << endl;
		}
	}
	void addEdge(int i, int j, double edge) {
		graph[i][j] = edge;
		graph[j][i] = edge;
	}
	void sort_x(vector<node>& n);
	void TSP();
	void next(int size, int pivot, int perm[],int preNode);
	void Convex_Hull_TSP();
	void Convex_Hull_Add(node t, int order);
	void Hungarian_mrthod();
	bool step3(vector<int>&zero_i, vector<int>&zero_j, vector<int>&r, vector<int>&col, vector<int>&ri, vector<int>&coli);
	int find(vector<int> v);
};
void travel_map::ReadMapNode() {
	cout << fixed << setprecision(7);
	ifstream in("11.txt");
	string line;
	char buffer[20];
	char name = 'a';
	if (in) {
		while (getline(in, line)) {
			if (line == "          <coordinates>") {//找座標
				getline(in, line);
				int ctrl = 0;  int k = 0; double x = 0, y = 0;//char 轉 double 
				for (int i = 0; i < line.size(); i++) 
				{
					if (line[i] == ' ') continue;
					if (line[i] == '.') {
						if (ctrl == 0) 	x = (double)atoi(buffer);
						else if (ctrl == 1) y = (double)atoi(buffer);
						k = 0; continue;
					}
					if (line[i] == ',') {
						double temp = 0;
						temp = atoi(buffer);
						temp *= pow(10, -(k));
						for (int i = k - 1; i > -1; i--) {
							temp = temp + buffer[i] - 48;
							buffer[i] = 0;
							temp *= 0.1;
						}
						if (ctrl == 0) x += temp * 1.0;
						else if (ctrl == 1) y += temp * 1.0;
						ctrl++; k = 0; continue;
					}
					buffer[k] = line[i]; k++;
				}
				tempNode.push_back(newnode(x, y,name));
				name += 1;
			}
		}
	}
	else cout << "no such file" << endl;
	in.close();
}
void travel_map::ClosestorFarthest(vector<node> t, int ctrl,bool add) {
	int  min1 = 0, min2 = 0, max1=0, max2=0;
	if (t.empty()) return;
	cout << fixed << setprecision(7);
	double MIN = INTMAX_MAX,temp=0,Max=0;
	for (int i = 0; i < t.size() - 1; i++) {
		for (int j = i + 1; j < t.size(); j++) {
			temp = abs(t[i].x - t[j].x) + abs(t[i].y - t[j].y);
			if (add == 1)addEdge(i, j, temp);
			if (MIN > temp) {
				MIN = temp;
				min1 = i; min2 = j;
			}
			if (Max < temp) {
				Max = temp;
				max1 = i; max2 = j;
			}
		}
	}
	if (ctrl==1) {
		cout << "Closest_Node: " << endl <<
			t[min1].name  << "( " << t[min1].x << " , " << t[min1].y << " )" << endl <<
			t[min2].name  << "( " << t[min2].x << " , " << t[min2].y << " )" << endl <<
			"Distance: " << MIN << endl << endl;
	}
	if(ctrl==0){
		cout << "farthest_Node: " << endl <<
			t[max1].name << "( " << t[max1].x << " , " << t[max1].y << " )" << endl <<
			t[max2].name << "( " << t[max2].x << " , " << t[max2].y << " )" << endl <<
			"Distance: " << Max << endl << endl;
	}
}
void travel_map::Graph_Area() {
	graphRange(N);
	sort_x(N);
	double total = 0;
	int a = 0, b = 1, c = 2;
	while (1) {
		total += computer(N[a], N[b], N[c]);
		a++; b++; c++;
		if (c == N.size()) break;
	}
	cout << "Area : " << total << endl;
	ClosestorFarthest(N, 0,false);
}
void travel_map::sort_x( vector<node>& n) {
	for (int i = 0; i < n.size()-1; i++) {
		for (int j = i+1; j < n.size(); j++) {
			if (n[i].x > n[j].x) {
				node temp = n[i];
				n[i] = n[j];
				n[j] = temp;
			}
		}
	}
	cout << "Sort Graph_outer_node(small to big): ";
	for (int i = 0; i < n.size(); i++)
		cout << n[i].name << " ";
	cout << endl;
}
double travel_map::computer(node a,node b,node c) {
	double ans;
	ans=a.x* b.y + c.x * a.y + b.x + c.y - c.x * b.y - b.x * a.y - a.x * c.y;
	ans = abs(ans) / 2;
	return ans;
}
void travel_map::graphRange(vector<node>& N) {
	vector<bool>n;
	int i, j;
	for (i = 0; i < tempNode.size(); i++)
		n.push_back(false);
	for (i = 0; i < tempNode.size() - 1; i++) {
		for (j = i + 1; j < tempNode.size(); j++) {
			double a = 0, b = 0, c = 0;
			bool pass = true;
			a = tempNode[j].y - tempNode[i].y;//a=y2-y1
			b = tempNode[i].x - tempNode[j].x;//b=x1-x2
			c = tempNode[i].x * tempNode[j].y - tempNode[i].y * tempNode[j].x;//c=x1y2-y1x2
			bool big = false, small = false;
			for (int k = 0; k < tempNode.size(); k++) {
				if (k == i || k == j)continue;
				double test = 0;
				test = a * tempNode[k].x + b * tempNode[k].y - c;
				if (test > 0) big = true;
				else if (test < 0)small = true;
				if (!big ^ small) {//相同 1 , 1
					pass = false;
					break;
				}
			}
			if (pass) {
				if (n[i] == false) {
					N.push_back(tempNode[i]);
					n[i] = true;
				}
				if (n[j] == false) {
					N.push_back(tempNode[j]);
					n[j] = true;
				}
			}
			else addEdge(i, j, 0);
		}
	}
	for (i = 0; i < tempNode.size(); i++)
		if (n[i]) cout << " 1 ";
		else { 
			cout << " 0 ";
			NotInN.push_back(tempNode[i]);
			ng_order.push_back(i);
		}
	cout << endl;

}
void travel_map::TSP() {
	int n = 7;
	int perm[Max_size];
	for (int i = 0; i < n; i++) {
		perm[i] = 1;
	}
	next(n, 0, perm,0);
	cout << "Shortest distence : " << TSP_MIN;
}
void travel_map::Convex_Hull_TSP() {
	cout << "Convex_Hull_TSP " << endl<<endl;
	for (int i = 0; i < NotInN.size(); i++)
		Convex_Hull_Add(NotInN[i], ng_order[i]);
	for (int i = 0; i < tempNode.size() - 1; i++) {
		for (int j = i + 1; j < tempNode.size(); j++) {
			if (graph[i][j] != 0)Convex_Hull_MIN += graph[i][j];

		}
	}
	cout << "Convex_Hull_MIN : " << Convex_Hull_MIN << endl;
	
	
}
void travel_map::Convex_Hull_Add(node t, int order) {
	double MIN = INTMAX_MAX;
	int i_i=0, j_i=0;
	for (int i = 0; i < tempNode.size(); i++) {
		for (int j = 0; j < tempNode.size(); j++) {
			if (i < j) continue;
			if (graph[i][j] != 0) {
				double a, b, c;
				a = tempNode[j].y - tempNode[i].y;//a=y2-y1
				b = tempNode[i].x - tempNode[j].x;//b=x1-x2
				c = tempNode[i].x * tempNode[j].y - tempNode[i].y * tempNode[j].x;
				double temp = t.x * t.x + t.y * t.y;
				double d = abs(a * t.x + b * t.y - c) /sqrt(temp);
				if (MIN > d) {
					MIN = d;
					j_i = j;
					i_i = i;
				}
			}
			else continue;
		}
	}
	MIN = abs(tempNode[i_i].x - tempNode[j_i].x) + abs(tempNode[i_i].y - tempNode[j_i].y);
	addEdge(i_i, j_i, 0);
	addEdge(i_i, order, MIN);
	addEdge(j_i, order, MIN);

}
void travel_map::Hungarian_mrthod(){
	double temp, MIN = INTMAX_MAX;
	graphPrint(tempNode);
	int i, j;
	vector <int> r;
	vector<int>ri;
	vector<int>col;
	vector<int>coli;
	vector<int>zero_i;
	vector<int>zero_j;
	for (i = 0; i < tempNode.size(); i++) {
		r.push_back(0);
		col.push_back(0);
		zero_i.push_back(0);
		zero_j.push_back(0);
	}
	for (i = 0; i < tempNode.size(); i++) {// 每個row減去row裡最小值
		double MIN = INTMAX_MAX;
		for (j = 0; j < tempNode.size(); j++) {
			if (i == j) continue;
			if (MIN > graph[i][j])
				MIN = graph[i][j];
		}
		for (j = 0; j < tempNode.size(); j++) {
			if (i == j) continue;
			graph[i][j] -= MIN;
		}
	}
	graphPrint(tempNode);
	cout << endl;
	for (j = 0; j < tempNode.size(); j++) {// 每個colume減去colume裡最小值
		double MIN = INTMAX_MAX;
		for (i = 0; i < tempNode.size(); i++) {
			if (i == j) continue;
			if (MIN > graph[i][j])
				MIN = graph[i][j];
		}
		for (i = 0; i < tempNode.size(); i++) {
			if (i == j) continue;
			graph[i][j] -= MIN;
		}
	}
	graphPrint(tempNode);
	step3(zero_i, zero_j, r, col, ri, coli);
	cout << "r ";
	for (i = 0; i < tempNode.size(); i++) {
		cout << r[i] << " ";
	}cout << endl;
	cout << "col ";
	for (i = 0; i < tempNode.size(); i++) {
		cout << col[i] << " ";
	}cout << endl;
	cout << "zero_i ";
	for (int i = 0; i < zero_i.size(); i++) 	cout << zero_i[i] << " ";
	cout << endl;
	cout << "zero_j ";
	for (int i = 0; i < zero_j.size(); i++)	cout << zero_j[i] << " ";
	cout << endl;
	cout << "ri ";
	for (int i = 0; i < ri.size(); i++) cout << ri[i]<<" ";
	cout << endl;
	cout << "coli ";
	for (int i = 0; i < coli.size(); i++)	cout << coli[i]<<" ";
	cout << endl;

	int m=find(zero_i); cout << "m= " << m << endl;
	for (i = 0; i < zero_i.size(); i++) zero_i[i] -= m;
	cout << "zero_i ";
	for (int i = 0; i < zero_i.size(); i++)
		cout << zero_i[i] << " ";
	cout << endl;

	m = find(zero_j);
	cout << "m= " << m << endl;
	for (i = 0; i < zero_j.size(); i++) zero_j[i] -= m;
	cout << "zero_j ";
	for (int i = 0; i < zero_j.size(); i++)
		cout << zero_j[i] << " ";
	cout << endl;


	double  K = INTMAX_MAX;
	int ii = 0, ji = 0;
	for (i = 0; i < tempNode.size(); i++) {
		if (zero_i[i] != 0)continue;
		for (j = 0; j < tempNode.size(); j++) {
			if (zero_j[j] != 0)continue;
			if (i == j) continue;
			if (K > graph[i][j]) { K = graph[i][j]; ii = i; ji = j; }
		}
	}
	cout << "ii,ji " << ii << " " << ji << endl;

	
	for (i = 0; i < tempNode.size(); i++) {
		if (zero_i[i] != 0)continue;
		for (j = 0; j < tempNode.size(); j++) {
			if (i == j) continue;
			if (zero_j[j] != 0)continue;
			graph[i][j] -= K;
			if (graph[i][j] == 0) {
				r[i] = 1;
				col[j] = 1;

			}
		}
	}
	graphPrint(tempNode);

}
bool travel_map::step3(vector<int>&zero_i, vector<int>&zero_j, vector<int>&r, vector<int>&col, vector<int>&ri, vector<int>&coli) {
	int i, j;
	for (i = 0; i < tempNode.size(); i++) {
		for (j = 0; j < tempNode.size(); j++) {
			if (i == j)continue;
			if (graph[i][j] == 0) {
				zero_i[i]++;
				zero_j[j]++;
				if (r[i] != 0) break;
				if (col[j] != 0)continue;
				r[i] += 1;
				col[j] += 1;
				cout << "(i,j)  " << i << " , " << j << endl << endl;
				ri.push_back(i);
				coli.push_back(j);
			}
		}
	}
	int OK = 0;
	for (i = 0; i < r.size(); i++) {
		if (r[i] == 0) {
			OK = 0;
			return 0;
		}
	}
	return 1;
}
int travel_map::find(vector<int> v) {
	int i; int min = v[0];

	for (i = 0; i < v.size(); i++)
		if (min > v[i])min = v[i];
	return min;
}
void travel_map::next(int size, int pivot, int perm[],int preNode)
{
	int i, collision;
	static int count = 0;
	static double TSP_TEMP = 0;
	perm[pivot] = 0;
	while (perm[pivot]++ < size)
	{
		if (perm[0] != 1) return;
		collision = 0;
		for (i = 0; i < pivot; i++)
			if (perm[pivot] == perm[i])
			{
				collision = 1;
				break;
			}
		if (!collision)
		{
			if (pivot + 1 < size) next(size, pivot + 1, perm,0);
			else
			{
				TSP_TEMP = 0;
				for (i = 0; i < size - 1; i++) {
					TSP_TEMP += graph[perm[i]][perm[i+1]];
				}
				TSP_TEMP += graph[0][perm[size-1]];
				if (TSP_MIN > TSP_TEMP) TSP_MIN = TSP_TEMP;
					cout << ++count << " ";
					for (i = 0; i < size; i++)
						cout << perm[i]-1 << " ";
					cout << "0 :d=" << TSP_TEMP << endl;
			}
		}
	}
}
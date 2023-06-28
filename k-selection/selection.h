#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
using namespace std;
#define Size 500
int n[Size] = {
162, 91, 155, 23, 76, 116, 191, 38, 94, 189, 166, 138, 9, 196, 157, 153, 50, 142, 149, 170,
87, 89, 178, 97, 59, 0, 66, 40, 167, 26, 52, 154, 58, 163, 21, 31, 128, 43, 96, 145,
125, 179, 188, 53, 42, 140, 27, 88, 98, 171, 168, 137, 14, 158, 114, 46, 133, 107, 4,
5, 164, 64, 110, 75, 24, 2, 161, 198, 124, 181, 165, 139, 81, 79, 65, 195, 85, 152, 200, 67,
19, 49, 69, 173, 199, 13, 123, 174, 95, 68, 82, 28, 47, 56, 12, 103, 70, 187, 6, 6,

431, 423, 334, 434, 217, 368, 461, 313, 337, 236, 294, 302, 459, 443, 242, 383, 372, 323, 404, 276,
440, 470, 299, 341, 480, 419, 345, 476, 410, 374, 292, 220, 393, 420, 275, 473, 265, 376, 474, 317,
224, 442, 252, 288, 295, 398, 450, 258, 260, 379, 211, 396, 453, 497, 381, 282, 214, 209, 290, 439,
487, 489, 277, 321, 241, 308, 227, 322, 235, 483, 204, 336, 367, 354, 259, 479, 271, 428, 249, 426,
365, 463, 206, 366, 406, 390, 315, 318, 632, 471, 329, 422, 445, 457, 405, 273, 250, 430, 469, 296,

385, 344, 225, 397, 486, 495, 293, 205, 403, 333, 369, 407, 342, 222, 263, 408, 316, 399, 449, 485,
285, 412, 327, 415, 234, 297, 401, 251, 482, 267, 284, 221, 432, 391, 245, 274, 458, 281, 228, 477,
238, 231, 363, 349, 216, 286, 460, 213, 384, 352, 414, 347, 484, 388, 291, 215, 253, 361, 395, 268,
325, 208, 375, 226, 254, 357, 326, 309, 492, 264, 283, 356, 218, 455, 735, 451, 257, 481, 201, 311,
348, 300, 424, 402, 230, 418, 212, 493, 364, 340, 491, 416, 261, 350, 314, 498, 270, 468, 202, 346,

320, 248, 425, 338, 500, 203, 287, 298, 324, 452, 377, 467, 328, 289, 380, 394, 279, 310, 370, 301,
409, 332, 331, 444, 362, 446, 387, 435, 278, 272, 371, 488, 447, 240, 306, 382, 247, 389, 437, 436,
454, 210, 355, 243, 456, 378, 237, 438, 475, 255, 490, 433, 219, 307, 411, 496, 417, 266, 312, 339,
358, 466, 494, 465, 421, 244, 429, 400, 386, 319, 499, 262, 373, 359, 269, 353, 472, 223, 330, 413,
441, 392, 239, 305, 448, 464, 360, 303, 351, 462, 343, 229, 246, 280, 427, 304, 256, 478, 233, 207,

707, 584, 513, 609, 528, 743, 711, 547, 658, 697, 776, 592, 674, 683, 673, 503, 514, 530, 654, 732,
774, 796, 677, 629, 625, 588, 730, 696, 733, 695, 773, 712, 761, 562, 689, 636, 570, 769, 608, 703,
520, 601, 704, 688, 670, 751, 783, 617, 680, 525, 529, 557, 635, 799, 700, 591, 660, 671, 504, 508,
639, 767, 640, 620, 532, 526, 772, 633, 792, 661, 515, 587, 624, 746, 571, 713, 612, 516, 717, 642,
744, 701, 793, 748, 579, 590, 788, 785, 756, 623, 699, 542, 659, 603, 560, 720, 614, 510, 583, 665 };
vector<int> v(n, n + sizeof(n) / sizeof(int));//(¶}ÀY,µ²§À)
class selection
{
public:
	void Print_array() {
		for (int i = 0; i < Size; i++) {
			if (i %20 == 0) cout << endl;
			cout << n[i] << " ";
		}
	}
	void Print_v() {
		for (int i = 0; i < Size; i++) {
			if (i % 20 == 0) cout << endl;
			cout <<v[i] << " ";
		}
	
	}
	void swap(int* a, int* b) {
		int temp = *a;
		*a = *b;
		*b = temp;
	}
	//========== Insertion Sort ==============================================================
	void Insertion_sort() {
		for (int i = 1; i < Size; i++) {
			int temp = n[i];
			int j = i - 1;
			while (j>=0 && n[j] > temp) {
				
				n[j+1] = n[j];
				j = j - 1;
			}
			n[j+1] = temp;
		}
	}
	//=========== Merge Sort =============================================================
	void merge(vector<int> &array, int left, int mid, int right) {
		vector<int>leftsub(array.begin() + left, v.begin() + mid+1);
		vector<int>	rightsub(array.begin() + mid + 1, v.begin() +right + 1);
		leftsub.insert(leftsub.end(), numeric_limits<int>::max());
		rightsub.insert(rightsub.end(),numeric_limits<int>::max());
		int l_index = 0, r_index = 0;
		for (int i = left; i <= right; i++) {
			if (leftsub[l_index] < rightsub[r_index]) {
				array[i] = leftsub[l_index];
				l_index++;
			}
			else {
				array[i] = rightsub[r_index];
				r_index++;
			}
		}
	}
	void Merge_sort(vector<int> &array,int left,int right) {
		if (left < right) {
			int mid = (left + right)/2;
			Merge_sort(array, left, mid);
			Merge_sort(array, mid + 1, right);
			merge(array, left, mid, right);
		}
	}
	//============ Quick Sort ============================================================
	int sort_pivot(int front, int end) {
		int pivot = n[end];
		int i = front - 1;
		for (int j = front; j < end; j++) {
			if (n[j] < pivot) {
				i++;
				swap(&n[i], &n[j]);
			}
		}
		i++;
		swap(&n[i], &n[end]);
		return i;
	}
	void QuickSort(int front, int end,int key) {
		if (front < end) {
			int pivot = sort_pivot(front, end);
			QuickSort(front, pivot - 1,key);
			QuickSort(pivot + 1, end,key);
		}
	}
	//============ Quick Selction ==========================================================
	int partition(int arr[], int l, int r)
	{
		int x = arr[r], i = l;
		for (int j = l; j <= r - 1; ++j)
		{
			if (arr[j] <= x)
			{
				swap(&arr[i],&arr[j]);
				i++;
			}
		}
		swap(&arr[i], &arr[r]);
		return i;
	}
	int qs_kth_smallest(int arr[], int l, int r, int k)
	{
		if (k < 0 || k > r - l + 1) { return -1; }
		int index = partition(arr, l, r); 
		if (index - l == k - 1)
			return arr[index];
		if (index - l > k - 1)
			return qs_kth_smallest(arr, l, index - 1, k);
		else 
			return qs_kth_smallest(arr, index + 1, r, k - index + l - 1);
	}
	//============ Median of Medians Selection ============================================================
	int findMedian(vector<int> vec) {
		int median;
		int size = vec.size();
		median = vec[(size / 2)];
		return median;
	}
	int findMedianOfMedians(vector<vector<int> > values) {
		vector<int> medians;
		for (int i = 0; i < values.size(); i++) {
			int m = findMedian(values[i]);
			medians.push_back(m);
		}
		return findMedian(medians);
	}
	void Median_of_Medians(vector<int> value ,int key,int gap) {
		vector<vector<int>> v2d;
		int total = 0;
//		cout <<endl<< "Order = " << key << endl<<endl;
		while (total != value.size()) {
			int rowcount = 0;
			vector<int>row;
			while ((rowcount < gap) && (total < value.size())) {
				row.push_back(value[total]);
				total++;rowcount++;
			}
			v2d.push_back(row);
		}
		int m = findMedianOfMedians(v2d);
	//	cout << "median is : " << m<< endl;
		vector<int>L1, L2;
		for (int r = 0; r < v2d.size(); r++) {
			for (int c = 0; c < v2d[r].size(); c++) {
				if (v2d[r][c] > m) L1.push_back(v2d[r][c]);
				else if (v2d[r][c] < m) L2.push_back(v2d[r][c]);
			}
		}
		/*
		cout << endl<<"L1 biger ";
		for (int r = 0; r < L1.size(); r++) cout << L1[r] << " "; cout << endl;
		cout << "L2 smaller ";
		for (int r = 0; r < L2.size(); r++) cout << L2[r] << " "; cout << endl;
		*/
		if ((key-1 ) == L2.size()) {
			cout << endl << "Answer :" << m<<endl;
		}
		else if (key <= L2.size()) {
			return Median_of_Medians(L2, key,gap);
		}
		else if (key > (L2.size() + 1)) {
			return Median_of_Medians(L1, key - ((int)L2.size())-1,gap);
		}
	}
};
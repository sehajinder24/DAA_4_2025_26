#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
//24BCS11459
//Sehaj Inder Singh

int operations = 0; 
int Depth = 0;
//global variable to ensure changes in function reflected in main

void complexRec(int n, int dep) {
    Depth = max(Depth, dep);
    //check in which recursion the depth is maximum
    
    if (n <= 2) {       //base Case
        operations++;
        return;
    }

    int p = n;
    while (p > 0) {
        operations++;
        vector<int> temp(n);
        for (int i = 0; i < n; i++) {
            temp[i] = i ^ p;
            operations++;
        }
        p >>= 1;
    }

    vector<int> small(n);
    for (int i = 0; i < n; i++) {
        small[i] = i * i;
        operations++;
    }

    // Check was not needed
    reverse(small.begin(), small.end());
    operations += n;
    
    //recursion calls
    complexRec(n / 2, dep + 1);
    complexRec(n / 2, dep + 1);
    complexRec(n / 2, dep + 1);
}

int main() {
	int a = 25;

	auto start = high_resolution_clock::now();
	    for (int n=0;n<=a;n++) {
	        operations = 0;
	        Depth = 0;
	        complexRec(n, 1);
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start);

        cout << "n = " << n << endl;
        cout << "Operations: " << operations << endl;
        cout << "Depth: " << Depth << endl;
        cout << "Time taken: " << duration.count() << " ms\n\n";
    }

	//Recurrance Relation = 3(T/2)+N
	// A=3 , B=2 , K=1 
	// Case 1 A>B^K
	//Time Complexity T(N)=O(N^Log3) 	Log 3 = Log2(3) base is 2 

    return 0;
}

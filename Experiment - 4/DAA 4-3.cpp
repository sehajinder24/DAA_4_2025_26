#include <bits/stdc++.h>
using namespace std;

#define MAX 100

int heap[MAX];
int heapSize = 0;
int K;

void heapifyDown(int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heapSize && heap[left] < heap[smallest])
        smallest = left;
    if (right < heapSize && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        heapifyDown(smallest);
    }
}

void heapifyUp(int i) {
    while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
        swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void insert(int val) {
    heap[heapSize] = val;
    heapSize++;
    heapifyUp(heapSize - 1);
}

int main() {
    int n;
    cin >> K >> n;

	int arr[n];
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if (heapSize < K) insert(x);
        else if (x > heap[0]) {
            heap[0] = x;
            heapifyDown(0);
        }

        if (heapSize < K){
        arr[i]=-1;	
        cout << -1 << endl;
		
		}
        else{
        int z = heap[0];
        arr[i]=z;
		cout << z << endl;
			
		}
		cout << endl;
        
    }
	cout << endl << "Final Output for ease of Viewing\n";
	for(int i=0;i<n;i++) cout << arr[i] << endl;
	
    return 0;
}


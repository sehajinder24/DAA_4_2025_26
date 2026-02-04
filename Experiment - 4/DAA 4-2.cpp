#include <bits/stdc++.h>
using namespace std;

#define MAX 100

int heap[MAX];
int heapSize = 0;

void heapifyDown(int i) {
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

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
    while (i > 0 && heap[(i-1)/2] > heap[i]) {
        swap(heap[i], heap[(i-1)/2]);
        i = (i-1)/2;
    }
}

void insert(int val) {
    if (heapSize == MAX) {
        cout << "Heap is Full\n";
        return;
    }
    heap[heapSize] = val;
    heapSize++;
    heapifyUp(heapSize - 1);
}

void deleteMin() {
    if (heapSize == 0) {
        cout << "Empty Heap\n";
        return;
    }
    heap[0] = heap[heapSize - 1];
    heapSize--;
    heapifyDown(0);
}

void display() {
    for (int i = 0; i < heapSize; i++)
        cout << heap[i] << " ";
    cout << endl;
}

void deleteAtIndex(int i) {
    if (i < 0 || i >= heapSize)
        return;

    heap[i] = heap[heapSize - 1];
    heapSize--;

    if (i > 0 && heap[i] < heap[(i - 1) / 2])
        heapifyUp(i);
    else
        heapifyDown(i);
}

int main() {
    insert(2);
    insert(4);
    insert(6);
    insert(1);

    deleteMin();
    deleteAtIndex(2);
    display();

    return 0;
}


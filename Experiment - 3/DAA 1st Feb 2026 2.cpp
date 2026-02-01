#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    int n;
    cin >> n;
    char arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    unordered_map<int, int> mp;
    mp[0] = -1; 
    int current = 0;      
    int maximum = 0;  

    for (int i = 0; i < n; i++) {
        if (arr[i] == 'P' || arr[i] == 'p') current = current + 1;
        else current = current - 1;

        if (mp.find(current) != mp.end())  maximum = max(maximum, i - mp[current]);
    	else mp[current] = i;
    }

    cout << "\n\nThe stable window length is : " << maximum << endl;
    return 0;
}

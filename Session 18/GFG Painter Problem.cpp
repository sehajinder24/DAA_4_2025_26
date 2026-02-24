




class Solution {
  public:
    int minTime(vector<int>& arr, int k) {
        long low = 0, high = 0;
    
        for (int length : arr) {
            high += length;
            low = max(low, (long)length);
        }
        
        long ans = high;
        
        while (low <= high) {
            long mid = low + (high - low) / 2;
            
            if (isPossible(arr, k, mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        
        return (int)ans;
    }
    
    bool isPossible(vector<int>& arr, int k, long maxTime) {
        long currSum = 0;
        int painters = 1;
        
        for (int length : arr) {
            if (currSum + length <= maxTime) {
                currSum += length;
            } else {
                painters++;
                currSum = length;
                
                if (painters > k)
                    return false;
            }
        }
        return true;
    }
};



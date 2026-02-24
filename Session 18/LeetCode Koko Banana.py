class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        left = 1
        right = max(piles)
        hours = 0

        while left < right:
            hours = 0
            mid = (left + right) // 2    
            for pile in piles:
                hours += (pile + mid - 1) // mid   
            if hours > h:
                left = mid + 1
            else:
                right = mid                
        return left
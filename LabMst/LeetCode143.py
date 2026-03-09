# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reorderList(self, head: Optional[ListNode]) -> None:
        slow, fast = head, head
        while fast.next and fast.next.next:
            slow = slow.next
            fast = fast.next.next
        prev,curr = None,slow.next

        while(curr):
            temp = curr.next
            curr.next = prev
            prev = curr
            curr = temp
        slow.next = None
        
        first,second = head,prev
        while second:
            t1 = first.next
            t2 = second.next

            first.next = second
            second.next = t1
            first = t1
            second = t2
        
        """
        Do not return anything, modify head in-place instead.
        """
        
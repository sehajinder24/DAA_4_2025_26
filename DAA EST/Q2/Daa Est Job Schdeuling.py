deadline = list(map(int, input().split()))
profit = list(map(int, input().split()))

n = len(deadline)
jobs = list(zip(deadline, profit))
jobs.sort(key=lambda x: x[1], reverse=True)

max_deadline = max(deadline)
slots = [-1] * (max_deadline + 1)

count,total_profit = 0,0

for d, p in jobs:
    for j in range(d, 0, -1):
        if slots[j] == -1:
            slots[j] = p
            count += 1
            total_profit += p
            break

print([count, total_profit])

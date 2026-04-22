from flask import Flask, jsonify, request
from flask_cors import CORS
import random
import time
from collections import deque

app = Flask(__name__)
CORS(app)

TOP    = 1
RIGHT  = 2
BOTTOM = 4
LEFT   = 8

DIRECTIONS = [
    (-1,  0, TOP,    BOTTOM),
    ( 0,  1, RIGHT,  LEFT),
    ( 1,  0, BOTTOM, TOP),
    ( 0, -1, LEFT,   RIGHT),
]


def generate_maze(n: int) -> list[list[int]]:
    walls = [[TOP | RIGHT | BOTTOM | LEFT for _ in range(n)] for _ in range(n)]
    visited = [[False] * n for _ in range(n)]

    stack = [(0, 0)]
    visited[0][0] = True

    while stack:
        r, c = stack[-1]
        dirs = DIRECTIONS[:]
        random.shuffle(dirs)
        moved = False
        for dr, dc, wall_cur, wall_next in dirs:
            nr, nc = r + dr, c + dc
            if 0 <= nr < n and 0 <= nc < n and not visited[nr][nc]:
                # Remove walls between current and neighbour
                walls[r][c]  &= ~wall_cur
                walls[nr][nc] &= ~wall_next
                visited[nr][nc] = True
                stack.append((nr, nc))
                moved = True
                break

        if not moved:
            stack.pop()

    return walls

def solve_bfs(walls: list[list[int]], n: int) -> dict:
    start, end = (0, 0), (n - 1, n - 1)
    visited  = [[False] * n for _ in range(n)]
    parent   = [[None]  * n for _ in range(n)]
    visited_order = []

    queue = deque([start])
    visited[0][0] = True

    t_start = time.perf_counter()
    steps = 0
    found = False

    while queue:
        r, c = queue.popleft()
        steps += 1
        visited_order.append((r, c))

        if (r, c) == end:
            found = True
            break

        for dr, dc, wall, _ in DIRECTIONS:
            if walls[r][c] & wall:
                continue         
            nr, nc = r + dr, c + dc
            if 0 <= nr < n and 0 <= nc < n and not visited[nr][nc]:
                visited[nr][nc] = True
                parent[nr][nc]  = (r, c)
                queue.append((nr, nc))

    elapsed = time.perf_counter() - t_start

    path = []
    if found:
        cur = end
        while cur:
            path.append(cur)
            cur = parent[cur[0]][cur[1]]
        path.reverse()

    return {
        "algorithm": "BFS",
        "steps": steps,
        "path_length": len(path),
        "time_ms": round(elapsed * 1000, 4),
        "visited_order": visited_order,
        "path": path,
        "found": found,
    }

def solve_dfs(walls: list[list[int]], n: int) -> dict:
    start, end = (0, 0), (n - 1, n - 1)
    visited  = [[False] * n for _ in range(n)]
    parent   = [[None]  * n for _ in range(n)]
    visited_order = []

    stack = [start]
    steps = 0
    found = False

    t_start = time.perf_counter()

    while stack:
        r, c = stack.pop()
        if visited[r][c]:
            continue
        visited[r][c] = True
        steps += 1
        visited_order.append((r, c))

        if (r, c) == end:
            found = True
            break

        for dr, dc, wall, _ in DIRECTIONS:
            if walls[r][c] & wall:
                continue
            nr, nc = r + dr, c + dc
            if 0 <= nr < n and 0 <= nc < n and not visited[nr][nc]:
                parent[nr][nc] = (r, c)
                stack.append((nr, nc))

    elapsed = time.perf_counter() - t_start

    path = []
    if found:
        cur = end
        while cur:
            path.append(cur)
            cur = parent[cur[0]][cur[1]]
        path.reverse()

    return {
        "algorithm": "DFS",
        "steps": steps,
        "path_length": len(path),
        "time_ms": round(elapsed * 1000, 4),
        "visited_order": visited_order,
        "path": path,
        "found": found,
    }

def solve_backtracking(walls: list[list[int]], n: int) -> dict:
    start, end = (0, 0), (n - 1, n - 1)
    visited = [[False] * n for _ in range(n)]

    frames = []
    steps  = [0]
    result = {"path": [], "found": False}

    t_start = time.perf_counter()

    def dfs(r, c, path):
        if result["found"]:
            return
        visited[r][c] = True
        path.append((r, c))
        steps[0] += 1
        frames.append({"pos": (r, c), "action": "enter"})

        if (r, c) == end:
            result["found"] = True
            result["path"]  = list(path)
            for pos in path:
                frames.append({"pos": pos, "action": "solution"})
            return

        for dr, dc, wall, _ in DIRECTIONS:
            if result["found"]:
                return
            if walls[r][c] & wall:
                continue
            nr, nc = r + dr, c + dc
            if 0 <= nr < n and 0 <= nc < n and not visited[nr][nc]:
                dfs(nr, nc, path)

        if not result["found"]:
            frames.append({"pos": (r, c), "action": "backtrack"})
            path.pop()

    import sys
    sys.setrecursionlimit(10000)
    dfs(0, 0, [])

    elapsed = time.perf_counter() - t_start

    return {
        "algorithm": "Backtracking",
        "steps": steps[0],
        "path_length": len(result["path"]),
        "time_ms": round(elapsed * 1000, 4),
        "frames": frames,
        "path": result["path"],
        "found": result["found"],
    }


@app.route("/generate", methods=["POST"])
def generate():
    data = request.get_json()
    n    = max(3, min(41, int(data.get("size", 15))))
    if n % 2 == 0:
        n += 1
    seed = data.get("seed")
    if seed is not None:
        random.seed(seed)
    walls = generate_maze(n)
    return jsonify({"size": n, "walls": walls})


@app.route("/solve", methods=["POST"])
def solve():
    data  = request.get_json()
    n     = int(data.get("size", 15))
    walls = data.get("walls")
    algos = data.get("algorithms", ["bfs", "dfs", "backtracking"])

    results = {}
    if "bfs" in algos:
        results["bfs"] = solve_bfs(walls, n)
    if "dfs" in algos:
        results["dfs"] = solve_dfs(walls, n)
    if "backtracking" in algos:
        results["backtracking"] = solve_backtracking(walls, n)

    return jsonify(results)


@app.route("/")
def index():
    return "Maze Solver API is running. Open index.html in your browser."


if __name__ == "__main__":
    print("=" * 50)
    print("  Maze Solver API")
    print("  Running at http://localhost:5000")
    print("  Open index.html in your browser")
    print("=" * 50)
    app.run(debug=True, port=5000)

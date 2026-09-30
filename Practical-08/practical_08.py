def bfs(graph, startnode):
    visited = set()
    queue = [startnode]
    traversal_order = []

    visited.add(startnode)

    while queue:
        current_node = queue.pop(0)
        traversal_order.append(current_node)

        for neighbor in graph[current_node]:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)

    return traversal_order


def dfs(graph, startnode):
    visited = set()
    stack = [startnode]
    traversal_order = []

    while stack:
        current_node = stack.pop()

        if current_node not in visited:
            visited.add(current_node)
            traversal_order.append(current_node)

            for neighbor in reversed(graph[current_node]):
                if neighbor not in visited:
                    stack.append(neighbor)

    return traversal_order


graph = {
    'A': ['B', 'C'],
    'B': ['A', 'D', 'E'],
    'C': ['A', 'F'],
    'D': ['B'],
    'E': ['B', 'F'],
    'F': ['C', 'E']
}

print("BFS:", bfs(graph, 'A'))
print("DFS:", dfs(graph, 'A'))
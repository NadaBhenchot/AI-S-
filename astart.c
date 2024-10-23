#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define N 8 // Number of nodes

// A utility function to return the minimum f(n) value
int findMinFNode(int f[], bool visited[]) {
    int min = INT_MAX;
    int min_index = -1;

    for (int v = 0; v < N; v++) {
        if (!visited[v] && f[v] < min) {
            min = f[v];
            min_index = v;
        }
    }
    return min_index;
}

// A utility function to print the path
void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d ", j);
        return;
    }
    printPath(parent, parent[j]);
    printf("%d ", j);
}

// A* algorithm implementation
void aStar(int graph[N][N], int h[N], int start, int goal) {
    int g[N]; // Cost from start to node n
    int f[N]; // f(n) = g(n) + h(n)
    bool visited[N]; // To keep track of visited nodes
    int parent[N]; // To store the path

    // Initialize g, f, and visited arrays
    for (int i = 0; i < N; i++) {
        g[i] = INT_MAX;
        f[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    g[start] = 0;
    f[start] = h[start];

    for (int i = 0; i < N - 1; i++) {
        int current = findMinFNode(f, visited);

        if (current == -1) break;
        visited[current] = true;

        if (current == goal) {
            printf("Shortest path: ");
            printPath(parent, goal);
            printf("\nTotal cost: %d\n", g[goal]);
            return;
        }

        for (int neighbor = 0; neighbor < N; neighbor++) {
            if (graph[current][neighbor] && !visited[neighbor]) {
                int tempG = g[current] + graph[current][neighbor];

                if (tempG < g[neighbor]) {
                    g[neighbor] = tempG;
                    f[neighbor] = g[neighbor] + h[neighbor];
                    parent[neighbor] = current;
                }
            }
        }
    }

    printf("No path found\n");
}

int main() {
    int graph[N][N];
    int h[N];
    int start, goal;

    // Input the adjacency matrix in a single line per row
    printf("Enter the adjacency matrix (%dx%d) for the graph (space-separated rows):\n", N, N);
    for (int i = 0; i < N; i++) {
        printf("Row %d: ", i);
        for (int j = 0; j < N; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Input the heuristic values using a loop
    printf("Enter the heuristic values for each node:\n");
    for (int i = 0; i < N; i++) {
        printf("Heuristic for node %d: ", i);
        scanf("%d", &h[i]);
    }

    // Input start and goal nodes
    printf("Enter the start node (0-%d): ", N - 1);
    scanf("%d", &start);
    printf("Enter the goal node (0-%d): ", N - 1);
    scanf("%d", &goal);

    // Run A* algorithm
    aStar(graph, h, start, goal);

    return 0;
}

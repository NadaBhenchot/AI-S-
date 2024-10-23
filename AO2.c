#include <stdio.h>
#include <limits.h>

#define MAX 10
#define INF 9999

int cost[MAX][MAX], n, goal[MAX], heuristic[MAX], solution[MAX], path[MAX], pathIndex = 0;

int minCost(int parent) {
    int min = INF;
    for (int i = 0; i < n; i++) {
        if (cost[parent][i] != INF && heuristic[i] < min) {
            min = heuristic[i];
        }
    }
    return min;
}

void AOStar(int node) {
    if (goal[node]) {
        solution[node] = 1;
        path[pathIndex++] = node;  // Add to path
        return;
    }

    int minSubCost = minCost(node);
    printf("Expanding node: %d with cost %d\n", node, minSubCost);
    path[pathIndex++] = node;  // Add to path

    for (int i = 0; i < n; i++) {
        if (cost[node][i] != INF && heuristic[i] == minSubCost) {
            AOStar(i);
            // Update heuristic of the node based on the sub-tree's solution
            heuristic[node] = minSubCost + cost[node][i];
            if (solution[i]) {
                solution[node] = 1;
                break;
            }
        }
    }
}

int main() {
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    // Initialize the solution array to 0 (unsolved)
    for (int i = 0; i < n; i++) {
        solution[i] = 0;
    }

    printf("Enter cost matrix (use %d for infinity):\n", INF);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    printf("Enter heuristic values for each node:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &heuristic[i]);
    }

    printf("Enter goal nodes (1 if goal, 0 if not):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &goal[i]);
    }

    int start;
    printf("Enter start node: ");
    scanf("%d", &start);

    AOStar(start);

    if (solution[start]) {
        printf("Solution found. Path: ");
        for (int i = 0; i < pathIndex; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        printf("No solution found.\n");
    }

    return 0;
}

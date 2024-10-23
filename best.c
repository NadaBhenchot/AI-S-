#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 100

// Structure for the elements in the priority queue
struct item {
    int node;
    int priority;  // This can be the heuristic value (distance or cost)
};

// Priority Queue structure and size
struct item pr[MAX];
int size = -1;

// Graph representation
int graph[MAX][MAX];
int n; // Number of nodes

// Function to insert an element into the priority queue
void enqueue(int node, int priority) {
    size++;
    pr[size].node = node;
    pr[size].priority = priority;
}

// Function to find the element with the lowest heuristic value
int peek() {
    int lowestPriority = INT_MAX;
    int ind = -1;

    for (int i = 0; i <= size; i++) {
        if (pr[i].priority < lowestPriority) {
            lowestPriority = pr[i].priority;
            ind = i;
        }
    }
    return ind;
}

// Function to remove the node with the highest priority (lowest heuristic)
int dequeue() {
    int ind = peek();
    int node = pr[ind].node;

    // Shift elements to remove the dequeued node
    for (int i = ind; i < size; i++) {
        pr[i] = pr[i + 1];
    }
    size--;
    return node;
}

// Best First Search function
void bestFirstSearch(int start, int goal, int heuristic[]) {
    bool visited[MAX] = { false };  // Keep track of visited nodes
    enqueue(start, heuristic[start]);  // Enqueue the start node with its heuristic value
    visited[start] = true;

    printf("Best First Search Path: ");
    while (size != -1) {
        int current = dequeue();  // Get the node with the lowest heuristic
        printf("%d ", current);  // Print the current node as part of the path

        // Goal found
        if (current == goal) {
            printf("\nGoal Node %d found!\n", goal);
            return;
        }

        // Explore neighbors
        for (int i = 0; i < n; i++) {
            if (graph[current][i] != 0 && !visited[i]) {  // If there is an edge and it's unvisited
                enqueue(i, heuristic[i]);  // Enqueue the neighbor node with its heuristic value
                visited[i] = true;  // Mark as visited
            }
        }
    }
    printf("\nGoal Node %d not reachable!\n", goal);  // If the goal node is not reachable
}

// Main function to demonstrate Best First Search with user inputs
int main() {
    int startNode, goalNode;

    // Input number of nodes
    printf("Enter the number of nodes in the graph: ");
    scanf("%d", &n);

    // Input the adjacency matrix
    printf("Enter the adjacency matrix (0 for no edge, 1 for edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Input heuristic values
    int heuristic[MAX];
    printf("Enter the heuristic values for each node:\n");
    for (int i = 0; i < n; i++) {
        printf("Heuristic for node %d: ", i);
        scanf("%d", &heuristic[i]);
    }

    // Input start and goal nodes
    printf("Enter the start node: ");
    scanf("%d", &startNode);
    printf("Enter the goal node: ");
    scanf("%d", &goalNode);

    // Run Best First Search
    bestFirstSearch(startNode, goalNode, heuristic);

    return 0;
}
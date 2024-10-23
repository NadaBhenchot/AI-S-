#include <stdio.h>

#define MAX 10 // Max number of vertices

int adjMatrix[MAX][MAX];  
int visited[MAX]; 
int queue[MAX];  
int front = -1, rear = -1;  


void enqueue(int vertex) {
    if (rear == MAX - 1)
        printf("Queue is full\n");
    else {
        if (front == -1)  
            front = 0;
        rear++;
        queue[rear] = vertex;
    }
}


int dequeue() {
    int vertex;
    if (front == -1 || front > rear) {
        printf("Queue is empty\n");
        return -1;
    } else {
        vertex = queue[front];
        front++;
        return vertex;
    }
}

// Function to perform BFS
void bfs(int startVertex, int n) {
    int i;
    
    enqueue(startVertex);
    visited[startVertex] = 1;  // Mark the start vertex as visited

    while (front <= rear) {
        int currentVertex = dequeue();
        printf("%d ", currentVertex);

        // Visit adjacent vertices
        for (i = 0; i < n; i++) {
            if (adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
}

int main() {
    int n, i, j, startVertex;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    // Initialize adjacency matrix and visited array
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            adjMatrix[i][j] = 0;
        }
        visited[i] = 0;
    }

    printf("Enter the adjacency matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &adjMatrix[i][j]);
        }
    }

    printf("Enter the starting vertex (0 to %d): ", n-1);
    scanf("%d", &startVertex);

    printf("BFS traversal starting from vertex %d:\n", startVertex);
    bfs(startVertex, n);

    return 0;
}

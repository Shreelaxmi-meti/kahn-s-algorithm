/* ============================================================
 * Mini Project: Implementation of Kahn’s Algorithm for Topological Sorting in DAG
 * Algorithm   : Kahn’s Algorithm (Topological Sorting using BFS)
 * Author      : [shreelaxmi]  |  USN: [R24EJ125]
 * Date        : [19-09-2025]
 * Description : Program to find topological order of a DAG using queue
 * ============================================================ */

/* --- Include necessary header files --- */
#include <stdio.h>
#include <stdlib.h>

/* --- Constants and Macro Definitions --- */
#define MAX_SIZE 100   /* Maximum number of vertices */

/* --- Queue implementation --- */
int queue[MAX_SIZE], front = -1, rear = -1;

/* Function to insert element into queue */
void enqueue(int value) {
    if (rear == MAX_SIZE - 1)
        return;  /* Queue overflow (ignored for simplicity) */

    if (front == -1)
        front = 0;

    queue[++rear] = value;  /* Add element at rear */
}

/* Function to remove element from queue */
int dequeue() {
    if (front == -1)
        return -1;  /* Queue underflow */

    int value = queue[front];

    if (front == rear)
        front = rear = -1;  /* Reset queue */
    else
        front++;

    return value;
}

/* Function to check if queue is empty */
int isEmpty() {
    return (front == -1);
}

/* ============================================================
 * Module / Function 1: KahnTopologicalSort
 * Purpose : Perform topological sorting using Kahn’s Algorithm
 * Input   : graph[MAX_SIZE][MAX_SIZE] - adjacency matrix
 *           V - number of vertices
 * Output  : Prints topological order or cycle detection message
 * ============================================================ */
void KahnTopologicalSort(int graph[MAX_SIZE][MAX_SIZE], int V) {

    int indegree[MAX_SIZE] = {0};  /* Store indegree of each vertex */
    int i, j, count = 0;

    /* Step 1: Calculate indegree of each vertex */
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            if (graph[i][j] == 1) {
                indegree[j]++;  /* Increase indegree */
            }
        }
    }

    /* Step 2: Add vertices with indegree 0 to queue */
    for (i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            enqueue(i);
        }
    }

    printf("Topological Order: ");

    /* Step 3: Process vertices in queue */
    while (!isEmpty()) {

        int u = dequeue();  /* Remove vertex */
        printf("%d ", u);
        count++;

        /* Step 4: Reduce indegree of adjacent vertices */
        for (j = 0; j < V; j++) {
            if (graph[u][j] == 1) {
                indegree[j]--;

                /* If indegree becomes 0, add to queue */
                if (indegree[j] == 0) {
                    enqueue(j);
                }
            }
        }
    }

    /* Step 5: Check for cycle */
    if (count != V) {
        printf("\nCycle detected! Topological sorting not possible.\n");
    }
}

/* ============================================================
 * Function: main
 * Purpose : Entry point of the program
 * ============================================================ */
int main() {

    int V, i, j;
    int graph[MAX_SIZE][MAX_SIZE];

    /* Step 1: Input number of vertices */
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    /* Step 2: Input adjacency matrix */
    printf("Enter adjacency matrix:\n");
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    /* Step 3: Call Kahn’s Algorithm */
    KahnTopologicalSort(graph, V);

    return 0;
}
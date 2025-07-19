#include <stdio.h>
#define MAX 100

// Function to print the path using parent array
void printPath(int parent[MAX][MAX], int u, int v) {
    if(u == v){
        printf("%d ",u);
        return;

    }
    /*
    if (parent[u][v] == u) {
        printf("%d ", u);
        return;
    }
    */
    printPath(parent, u, parent[u][v]);
    printf("%d ", v);
}

// Floyd-Warshall-like function to update adjacency matrix and track path
void findPath(int adjMatrix[MAX][MAX], int vertices, int source, int dest) {
    int parent[MAX][MAX];

    // Initialize parent matrix
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (adjMatrix[i][j] != 0) {
                parent[i][j] = i; // Direct edge, parent is the source
            } else {
                parent[i][j] = -1; // No edge
            }
        }
    }

    // Floyd-Warshall logic to check for paths
    for (int k = 0; k < vertices; k++) {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (adjMatrix[i][k] && adjMatrix[k][j]) {
                    if (!adjMatrix[i][j]) {
                        adjMatrix[i][j] = 1; // Path found through vertex k
                        parent[i][j] = k;
                    }
                }
            }
        }
    }

    for(int  i = 0;i<vertices;i++){
        for(int  j = 0;j<vertices;j++){
        printf("%d ",parent[i][j]);}
        printf("\n");
    }

    // Check if a path exists
    if (adjMatrix[source][dest]) {
        printf("Path from %d to %d: ", source, dest);
        printPath(parent, source, dest);
        //printf("%d\n", dest);
    } else {
        printf("No path exists between %d and %d\n", source, dest);
    }
}

int main() {
    int vertices;
    int adjMatrix[MAX][MAX];
    int source, dest;

    // Input the number of vertices
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    // Input the adjacency matrix
    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            scanf("%d", &adjMatrix[i][j]);
        }
    }

    // Input the source and destination vertices
    printf("Enter the source vertex: ");
    scanf("%d", &source);
    printf("Enter the destination vertex: ");
    scanf("%d", &dest);

    // Find and print the path
    findPath(adjMatrix, vertices, source, dest);

    return 0;
}
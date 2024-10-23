#include <stdio.h>
#include <stdbool.h>

// Function to find the minimum color that can be assigned to a vertex
void greedyGraphColoring(int graph[][4], int numVertices) {
    int color[numVertices];  // Array to store the color assigned to each vertex

    // Assign the first color to the first vertex
    color[0] = 0;

    // Initialize all other vertices as unassigned
    for (int i = 1; i < numVertices; i++) {
        color[i] = -1;  // -1 indicates that no color is assigned yet
    }

    // Array to keep track of the colors that are unavailable for a vertex
    bool available[numVertices];
    for (int i = 0; i < numVertices; i++) {
        available[i] = true;  // Initially, all colors are available
    }

    // Assign colors to the remaining vertices
    for (int u = 1; u < numVertices; u++) {
        // Mark the colors of adjacent vertices as unavailable
        for (int i = 0; i < numVertices; i++) {
            if (graph[u][i] == 1 && color[i] != -1) {
                available[color[i]] = false;
            }
        }

        // Find the first available color
        int cr;
        for (cr = 0; cr < numVertices; cr++) {
            if (available[cr]) {
                break;
            }
        }

        color[u] = cr;  // Assign the found color to vertex u

        // Reset the values back to true for the next iteration
        for (int i = 0; i < numVertices; i++) {
            if (graph[u][i] == 1 && color[i] != -1) {
                available[color[i]] = true;
            }
        }
    }

    // Find the maximum color index used
    int maxColor = 0;
    for (int i = 0; i < numVertices; i++) {
        if (color[i] > maxColor) {
            maxColor = color[i];
        }
    }

    // Print the result
    printf("The color assigned to each vertex is as follows:\n");
    for (int i = 0; i < numVertices; i++) {
        printf("Vertex %d ---> Color %d\n", i, color[i]);
    }

    // Print the total number of colors used
    printf("Total number of colors used: %d\n", maxColor + 1);
}

// Driver code
int main() {
    // Adjacency matrix representation of the graph
    int graph[4][4] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };

    int numVertices = 4;

    // Solve the graph coloring problem using the Greedy algorithm
    greedyGraphColoring(graph, numVertices);

    return 0;
}

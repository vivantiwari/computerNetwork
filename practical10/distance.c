#include <stdio.h>

#define MAX_NODES 10
#define INF 9999

// Structure to define a routing table entry
struct RoutingTable {
    int distance[MAX_NODES];
    int next_hop[MAX_NODES];
};

int main() {
    int cost_matrix[MAX_NODES][MAX_NODES];
    struct RoutingTable nodes[MAX_NODES];
    int total_nodes;

    printf("Enter the number of nodes (Max %d): ", MAX_NODES);
    scanf("%d", &total_nodes);

    // 1. Read the network cost adjacency matrix
    printf("Enter the cost adjacency matrix (Use %d for infinity/no direct link):\n", INF);
    for (int i = 0; i < total_nodes; i++) {
        for (int j = 0; j < total_nodes; j++) {
            scanf("%d", &cost_matrix[i][j]);
            
            // Set basic values for zero path length to self
            if (i == j) {
                cost_matrix[i][j] = 0;
            }
            
            // Initialize local routing tables with direct neighbor values
            nodes[i].distance[j] = cost_matrix[i][j];
            nodes[i].next_hop[j] = (cost_matrix[i][j] != INF) ? j : -1;
        }
    }

    // 2. Compute vectors iteratively (Bellman-Ford equation)
    int count = 0;
    do {
        count = 0; // Tracks if any changes happened in this iteration
        
        for (int i = 0; i < total_nodes; i++) {         // From Source Router 'i'
            for (int j = 0; j < total_nodes; j++) {     // To Destination Router 'j'
                for (int k = 0; k < total_nodes; k++) { // Via Intermediate Neighbor 'k'
                    
                    // Check if path through neighbor 'k' is shorter than current path
                    if (nodes[i].distance[j] > cost_matrix[i][k] + nodes[k].distance[j]) {
                        nodes[i].distance[j] = cost_matrix[i][k] + nodes[k].distance[j];
                        nodes[i].next_hop[j] = k;
                        count++; // Flag that a structural optimization occurred
                    }
                }
            }
        }
    } while (count != 0); // Keep iterating until routing tables stabilize completely

    // 3. Print the final stable routing tables
    printf("\n--- Final Stable Routing Tables --- \n");
    for (int i = 0; i < total_nodes; i++) {
        printf("\nRouting Table for Router %c:\n", 'A' + i);
        printf("%-15s %-10s %-10s\n", "Destination", "Distance", "Next Hop");
        printf("-----------------------------------\n");
        for (int j = 0; j < total_nodes; j++) {
            if (nodes[i].distance[j] == INF) {
                printf("%-15c %-10s %-10s\n", 'A' + j, "INF", "-");
            } else {
                printf("%-15c %-10d %-10c\n", 'A' + j, nodes[i].distance[j], 'A' + nodes[i].next_hop[j]);
            }
        }
    }
printf("Vivan Tiwari 24070521133 B2");
    return 0;
}

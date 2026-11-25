#include <stdio.h>
#include <unistd.h>

#define BUCKET_CAPACITY 30  // Max tokens the bucket can hold
#define TOKEN_GEN_RATE 5    // Tokens added to the bucket per second

void simulateTokenBucket(int requested_bytes[], int total_intervals) {
    int current_tokens = 0;

    printf("\n--- Starting Token Bucket Simulation ---\n");
    printf("Max Token Capacity: %d | Token Regeneration Rate: %d/sec\n\n", BUCKET_CAPACITY, TOKEN_GEN_RATE);
    printf("%-10s %-18s %-18s %-18s %-18s\n", "Second", "Tokens Regenerated", "Current Balance", "Requested Output", "Transmission Action");
    printf("-----------------------------------------------------------------------------------------\n");

    for (int t = 0; t < total_intervals; t++) {
        // 1. Add new tokens generated during this time step
        current_tokens += TOKEN_GEN_RATE;
        if (current_tokens > BUCKET_CAPACITY) {
            current_tokens = BUCKET_CAPACITY; // Cap at max bucket threshold
        }

        int requested = requested_bytes[t];

        // 2. Evaluate if enough tokens exist to satisfy the requested packet transmission size
        if (requested <= current_tokens) {
            current_tokens -= requested;
            printf("%-10d %-18d %-18d %-18d %-18s\n", t + 1, TOKEN_GEN_RATE, current_tokens, requested, "PASSED (Burst OK)");
        } else {
            printf("%-10d %-18d %-18d %-18d %-18s\n", t + 1, TOKEN_GEN_RATE, current_tokens, requested, "FAILED (Dropped)");
        }

        sleep(1); // One-second delay for simulation pacing
    }
}

int main() {
    // Array where each element represents required packet transmission sizing per second
    int requested_bytes[] = {10, 25, 5, 40, 15};
    int total_intervals = sizeof(requested_bytes) / sizeof(requested_bytes[0]);

    simulateTokenBucket(requested_bytes, total_intervals);
	printf("Vivan Tiwari 24070521133 B2");
    return 0;
}

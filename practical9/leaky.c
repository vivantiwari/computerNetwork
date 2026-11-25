#include <stdio.h>
#include <unistd.h>

#define BUCKET_CAPACITY 50  // Maximum storage size of the bucket
#define LEAK_RATE 10        // Packets processed out of the bucket per second

void simulateLeakyBucket(int incoming_packets[], int total_intervals) {
    int current_buffer = 0;

    printf("\n--- Starting Leaky Bucket Simulation ---\n");
    printf("Bucket Capacity: %d packets | Leak Rate: %d packets/sec\n\n", BUCKET_CAPACITY, LEAK_RATE);
    printf("%-10s %-18s %-16s %-16s %-16s\n", "Second", "Incoming Packets", "Accepted Buffer", "Leaked/Sent", "Dropped Packets");
    printf("-----------------------------------------------------------------------------------------\n");

    for (int t = 0; t < total_intervals || current_buffer > 0; t++) {
        int incoming = (t < total_intervals) ? incoming_packets[t] : 0;
        int dropped = 0;

        // 1. Add incoming packets to the buffer if capacity permits
        if (incoming + current_buffer <= BUCKET_CAPACITY) {
            current_buffer += incoming;
        } else {
            dropped = (incoming + current_buffer) - BUCKET_CAPACITY;
            current_buffer = BUCKET_CAPACITY; // Fill bucket completely
        }

        // 2. Transmit packets at a constant leak rate
        int leaked = (current_buffer < LEAK_RATE) ? current_buffer : LEAK_RATE;
        current_buffer -= leaked;

        // 3. Print status for the current second interval
        printf("%-10d %-18d %-16d %-16d %-16d\n", t + 1, incoming, current_buffer + leaked, leaked, dropped);
        
        sleep(1); // One-second delay for simulation pacing
    }
}

int main() {
    // Array where each element represents incoming packet counts per second
    int incoming_packets[] = {15, 30, 5, 45, 0}; 
    int total_intervals = sizeof(incoming_packets) / sizeof(incoming_packets[0]);

    simulateLeakyBucket(incoming_packets, total_intervals);
	printf("Vivan Tiwari 24070521133 B2");
    return 0;
}

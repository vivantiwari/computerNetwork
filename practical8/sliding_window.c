#include <stdio.h>

int main() {
    int window_size, total_frames;
    int frames[100];

    // Input configuration
    printf("Enter window size: ");
    scanf("%d", &window_size);

    printf("Enter total number of frames to transmit: ");
    scanf("%d", &total_frames);

    printf("Enter the frame values (integers):\n");
    for (int i = 1; i <= total_frames; i++) {
        scanf("%d", &frames[i]);
    }

    printf("\n--- Starting Sliding Window Transmission ---\n");
    printf("Sender will send up to %d frames before waiting for an ACK.\n\n", window_size);

    int i = 1;
    while (i <= total_frames) {
        int window_limit = i + window_size - 1;
        if (window_limit > total_frames) {
            window_limit = total_frames;
        }

        // Send all frames inside the current window capacity
        printf("Current Window status: [Sent frames ");
        for (int j = i; j <= window_limit; j++) {
            printf("%d ", frames[j]);
        }
        printf("]\n");

        // Simulate receiving ACK for the oldest unacknowledged frame
        printf(">>> Acknowledgment for Frame %d received by sender.\n", frames[i]);
        printf("Sliding window forward...\n\n");
        
        i++; // Slide the window frame-by-frame
    }

    printf("All %d frames transmitted and acknowledged successfully!\n", total_frames);
    printf("Vivan Tiwari 24070521133 B2");
    return 0;
}



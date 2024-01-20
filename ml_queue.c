// These are standard C library header files. stdio.h is included for input/output operations,
// and stdlib.h is included for memory allocation and other standard functions
#include<stdio.h>
#include<stdlib.h>

// Defines a structure named Process with three members: id, priority, and burst_time.
// This structure represents a process in a multi-level queue scheduling system.
struct Process {
    int id;
    int priority;
    int burst_time;
};

// This function swaps two processes.
// It takes pointers to two Process structures as parameters and exchanges their values.
void swap(struct Process *xp, struct Process *yp) {
    struct Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// This function performs a simple bubble sort on an array of processes based on their priority.
// It uses the swap function to swap elements when necessary.
void sortByPriority(struct Process processes[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (processes[j].priority > processes[j+1].priority)
                swap(&processes[j], &processes[j+1]);
}

// This function performs multi-level queue scheduling.
// It separates processes into high and low priority queues,
// sorts them based on burst order, and prints the scheduling order.
void multiLevelQueueScheduling(struct Process processes[], int n) {
    int highPriorityQueueSize = 0;
    int lowPriorityQueueSize = 0;

    // This part counts the number of processes in each priority queue (0 for high priority, 1 for low priority).
    for (int i = 0; i < n; i++) {
        if (processes[i].priority == 0) {
            highPriorityQueueSize++;
        } else {
            lowPriorityQueueSize++;
        }
    }

    // Allocates memory for the high and low priority queues based on the counts obtained above.
    struct Process *highPriorityQueue = (struct Process*)malloc(highPriorityQueueSize * sizeof(struct Process));
    struct Process *lowPriorityQueue = (struct Process*)malloc(lowPriorityQueueSize * sizeof(struct Process));

    // Initialize indices for each queue
    int highPriorityIndex = 0;
    int lowPriorityIndex = 0;

    // This loop separates the processes into high and low priority queues based on their priority.
    for (int i = 0; i < n; i++) {
        if (processes[i].priority == 0) {
            highPriorityQueue[highPriorityIndex++] = processes[i];
        } else {
            lowPriorityQueue[lowPriorityIndex++] = processes[i];
        }
    }

    // Calls the sortByPriority function to sort both queues based on burst time priority(for simplicity)
    sortByPriority(highPriorityQueue, highPriorityQueueSize);
    sortByPriority(lowPriorityQueue, lowPriorityQueueSize);

    // Prints the scheduling order of processes from both high and low priority queues.
    printf("Scheduling Order:\n");

    for (int i = 0; i < highPriorityQueueSize; i++) {
        printf("Process %d (Priority %d) -> ", highPriorityQueue[i].id, highPriorityQueue[i].priority);
    }

    for (int i = 0; i < lowPriorityQueueSize; i++) {
        printf("Process %d (Priority %d) -> ", lowPriorityQueue[i].id, lowPriorityQueue[i].priority);
    }

    printf("\n");
}

// This is the main function where the program starts its execution.
// It prompts the user for the number of processes, gathers information about each process,
// performs multi-level queue scheduling, and frees the allocated memory.
int main() {
    int n;

    // Get the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Create an array of processes
    struct Process *processes = (struct Process*)malloc(n * sizeof(struct Process));

    // Get process details from the user
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter priority for Process %d (0 for high priority, 1 for low priority): ", i + 1);
        scanf("%d", &processes[i].priority);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    // Perform multi-level queue scheduling
    multiLevelQueueScheduling(processes, n);

    // Free allocated memory
    free(processes);

    return 0;
}

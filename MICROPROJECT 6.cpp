#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char name[50];
    int burst;
    int priority;   
} Job;

Job heap[MAX];
int size = 0;

int comparisons = 0;
int heapifyOps = 0;

void swap(int i, int j) {
    Job temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void insert(Job job) {
    if (size >= MAX) {
        printf("Heap full\n");
        return;
    }

    heap[size] = job;
    int i = size;
    size++;

    while (i > 0) {
        int parent = (i - 1) / 2;
        comparisons++;
        if (heap[parent].priority > heap[i].priority) {
            swap(parent, i);
            heapifyOps++;
            i = parent;
        } else break;
    }
}

void minHeapify(int i) {
    int smallest = i;
    int left = 2*i + 2;
    int right = 2*i + 2;

    if (left < size) {
        comparisons++;
        if (heap[left].priority < heap[smallest].priority)
            smallest = left;
    }

    if (right < size) {
        comparisons++;
        if (heap[right].priority < heap[smallest].priority)
            smallest = right;
    }

    if (smallest != i) {
        swap(i, smallest);
        heapifyOps++;
        minHeapify(smallest);
    }
}

Job extractMin() {
    Job min = heap[0];
    heap[0] = heap[size - 1];
    size--;
    minHeapify(0);
    return min;
}

void displayHeap() {
    printf("\nHeap (Level Order):\n");
    for (int i = 0; i < size; i++) {
        printf("ID:%d Name:%s Burst:%d Priority:%d\n",
               heap[i].id, heap[i].name,
               heap[i].burst, heap[i].priority);
    }
}

void simulateCPU() {
    if (size == 0) {
        printf("No jobs in heap\n");
        return;
    }

    printf("\nExecution Order:\n");

    while (size > 0) {
        Job job = extractMin();
        printf("Executing Job %d (%s), Burst:%d\n",
               job.id, job.name, job.burst);
    }

    printf("\nPerformance Report:\n");
    printf("Heapify Operations: %d\n", heapifyOps);
    printf("Total Comparisons: %d\n", comparisons);
}

int main() {
    int choice;
    Job job;

    while (1) {
        printf("\n1.Insert Job");
        printf("\n2.Extract Highest Priority Job");
        printf("\n3.Display Heap");
        printf("\n4.Simulate CPU Execution");
        printf("\n5.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter ID Name BurstTime Priority(1=High):\n");
                scanf("%d %s %d %d",
                      &job.id, job.name,
                      &job.burst, &job.priority);
                insert(job);
                break;

            case 2:
                if (size == 0)
                    printf("Heap empty\n");
                else {
                    Job j = extractMin();
                    printf("Extracted Job %d (%s)\n",
                           j.id, j.name);
                }
                break;

            case 3:
                displayHeap();
                break;

            case 4:
                simulateCPU();
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}

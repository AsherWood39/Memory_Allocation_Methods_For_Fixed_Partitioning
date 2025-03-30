#include <stdio.h>

#define MAX 100
#define INF 9999

typedef struct {
    int id;
    int size;
    int remaining;
    int block;
} Process;

typedef struct {
    int id;
    int size;
    int remaining;
} Memory;

Memory memory[MAX];
Process process[MAX];
int n, p;

void initializeMemory() {
    for (int i = 0; i < n; i++) {
        memory[i].remaining = memory[i].size; 
    }
}

void display() {
    printf("---------------------------------------------------------------------------------\n");
    printf("|    Process    |  Process Size |  Block Alloc. |   Block Size  |  Rem. Memory  |\n");
    printf("---------------------------------------------------------------------------------\n");

    for (int i = 0; i < p; i++) {
        if (process[i].block == -1) {
            printf("|\tP%d\t|\t%d\t|\tNA\t|\t---\t|\t---\t|\n", process[i].id, process[i].size);
            continue;
        }
        printf("|\tP%d\t|\t%d\t|\tB%d\t|\t%d\t|\t%d\t|\n", process[i].id, process[i].size, process[i].block + 1, memory[process[i].block].size, process[i].remaining);
    }

    printf("---------------------------------------------------------------------------------\n\n");

    printf("Memory Allocation Chart : \n");

    for (int i = 0; i < n; i++) { printf("----------------"); } printf("\n|");
    for (int i = 0; i < n; i++) {
        printf("Block %d : %d\t|", i + 1, memory[i].remaining);
    }
    printf("\n");
    for (int i = 0; i < n; i++) { printf("----------------"); } printf("\n\n");
}

void allocateMemory(int (*fitStrategy)(int, int)) {
    initializeMemory();

    for (int i = 0; i < p; i++) {
        process[i].remaining = 0;
        process[i].block = -1;
        fitStrategy(i, p);
    }
    display();
}

int firstFit(int i, int p) {
    for (int j = 0; j < n; j++) {
        if (memory[j].remaining >= process[i].size && memory[j].remaining > 0) {
            memory[j].remaining -= process[i].size;
            process[i].block = j;
            process[i].remaining = memory[j].remaining;
            break;
        }
    }
    return 0;
}

int bestFit(int i, int p) {
    int min = INF, index = -1;
    for (int j = 0; j < n; j++) {
        if (memory[j].remaining >= process[i].size && memory[j].remaining > 0) {
            if (memory[j].remaining - process[i].size < min) {
                min = memory[j].remaining - process[i].size;
                index = j;
            }
        }
    }
    if (index != -1) {
        memory[index].remaining -= process[i].size;
        process[i].block = index;
        process[i].remaining = memory[index].remaining;
    }
    return 0;
}

int worstFit(int i, int p) {
    int max = -1, index = -1;
    for (int j = 0; j < n; j++) {
        if (memory[j].remaining >= process[i].size && memory[j].remaining > 0) {
            if (memory[j].remaining - process[i].size > max) {
                max = memory[j].remaining - process[i].size;
                index = j;
            }
        }
    }
    if (index != -1) {
        memory[index].remaining -= process[i].size;
        process[i].block = index;
        process[i].remaining = memory[index].remaining;
    }
    return 0;
}

void main() {
    printf("Enter the no: of blocks in the memory : ");
    scanf("%d", &n);

    printf("\nEnter the size of the blocks : \n");
    for (int i = 0; i < n; i++) {
        printf("Block %d : ", i + 1);
        scanf("%d", &memory[i].size);
        memory[i].id = i;
    }

    printf("\nEnter the no: of processes : ");
    scanf("%d", &p);

    printf("\nEnter the size of the processes : \n");
    for (int i = 0; i < p; i++) {
        printf("Process %d : ", i + 1);
        scanf("%d", &process[i].size);
        process[i].id = i + 1;
    }

    int ch;
    printf("\n---- . M . E . N . U . ----\n     1. First Fit\n     2. Best Fit\n     3. Worst Fit\n     4. Exit\n");

    while (ch != 4) {
        printf("Enter your choice : ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("\nFirst Fit : \n"); allocateMemory(firstFit); break;
            case 2: printf("\nBest Fit : \n"); allocateMemory(bestFit); break;
            case 3: printf("\nWorst Fit : \n"); allocateMemory(worstFit); break;
            case 4: printf("\nExiting . . . \n\n"); break;
            default: printf("Invalid Choice !\n");
        }
    }
}


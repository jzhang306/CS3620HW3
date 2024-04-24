#include <stdio.h>

#define FRAME_SIZE 20


int frames[FRAME_SIZE];
int front = 0;
int pageFaults = 0;

void initialize() {
    for(int i = 0; i < FRAME_SIZE; i++) {
        frames[i] = -1; // Initialize frames with -1 to indicate they're empty
    }
}

int isPageInFrames(int page) {
    for(int i = 0; i < FRAME_SIZE; i++) {
        if(frames[i] == page) return 1; // Page found
    }
    return 0; // Page not found
}

void insertPage(int page) {
    if(!isPageInFrames(page)) {
        frames[front] = page;
        front = (front + 1) % FRAME_SIZE; // Move front in a circular manner
        pageFaults++;
    }
}

void printPageFaultRate(int totalReferences) {
    printf("FIFO Page Fault Rate: %.2f%%\n", (float)pageFaults / totalReferences * 100);
}

int main() {
    FILE *file;
    int page;
    char accessType;
    int totalReferences = 0;

    initialize();

    file = fopen("../page_references.txt", "r");
    if(file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while(fscanf(file, "%d %c\n", &page, &accessType) != EOF) {
        insertPage(page);
        totalReferences++;
    }

    fclose(file);
    printf("There are %d page fault numbers in total.\n",pageFaults);
    printPageFaultRate(totalReferences);
    return 0;
}

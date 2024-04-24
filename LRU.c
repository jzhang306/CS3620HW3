#include <stdio.h>

#define FRAME_SIZE 20
#define MAX_PAGES 2000

int frames[FRAME_SIZE];
int recency[MAX_PAGES];
int pageFaults = 0;
int time = 0;

void initialize() {
    for(int i = 0; i < FRAME_SIZE; i++) {
        frames[i] = -1; // Initialize frames as empty
    }
    for(int i = 0; i < MAX_PAGES; i++) {
        recency[i] = -1; // Initialize recency for each page as -1
    }
}

int findLRU() {
    int minTime = time, lruIndex = 0;
    for(int i = 0; i < FRAME_SIZE; i++) {
        if(recency[frames[i]] < minTime && frames[i] != -1) {
            minTime = recency[frames[i]];
            lruIndex = i;
        }
    }
    return lruIndex;
}

void insertPage(int page) {
    int i;
    for(i = 0; i < FRAME_SIZE; i++) {
        if(frames[i] == page) {
            recency[page] = time++; // Update recency
            return; // Page is already in a frame
        }
    }

    for(i = 0; i < FRAME_SIZE; i++) {
        if(frames[i] == -1) { // Empty frame found
            frames[i] = page;
            recency[page] = time++;
            pageFaults++;
            return;
        }
    }

    // No empty frame found, replace the LRU page
    int lruIndex = findLRU();
    frames[lruIndex] = page;
    recency[page] = time++;
    pageFaults++;
}

void printPageFaultRate(int totalReferences) {
    printf("LRU Page Fault Rate: %.2f%%\n", (float)pageFaults / totalReferences * 100);
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
    printf("Page fault number is %d\n",pageFaults);
    printPageFaultRate(totalReferences);
    return 0;
}
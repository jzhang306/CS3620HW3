#include <stdio.h>

#define FRAME_SIZE 20


int frames[FRAME_SIZE];
int referenceBits[FRAME_SIZE];
int front = 0;
int pageFaults = 0;

void initialize() {
    for(int i = 0; i < FRAME_SIZE; i++) {
        frames[i] = -1; // Initialize frames as empty
        referenceBits[i] = 0; // Initialize all reference bits to 0
    }
}

int isPageInFrames(int page, int *pagePosition) {
    for(int i = 0; i < FRAME_SIZE; i++) {
        if(frames[i] == page) {
            *pagePosition = i; // Pass back the position of the page in the frames
            return 1; // Page found
        }
    }
    return 0; // Page not found
}

void insertPage(int page) {
    int pagePosition;
    if(isPageInFrames(page, &pagePosition)) {
        referenceBits[pagePosition] = 1; // Set reference bit if page is found
        return;
    }

    // Iterate to find a page to replace
    while(referenceBits[front] == 1) {
        referenceBits[front] = 0; // Give a second chance and clear the reference bit
        front = (front + 1) % FRAME_SIZE; // Move to the next frame
    }

    // Replace the page without a second chance
    frames[front] = page;
    referenceBits[front] = 0; // Clear reference bit for the new page
    front = (front + 1) % FRAME_SIZE;
    pageFaults++;
}

void printPageFaultRate(int totalReferences) {
    printf("Second Chance Page Fault Rate: %.2f%%\n", (float)pageFaults / totalReferences * 100);
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
    printf("The page fault number is: %d\n",pageFaults);
    printPageFaultRate(totalReferences);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FRAME_SIZE 20
#define PAGE_REFERENCE_FILE "../page_references.txt"

typedef struct {
    int pageNumber;
    bool referenceBit;
    bool modifiedBit;
} Frame;

// Function Prototypes
void initializeFrames(Frame frames[]);
int findReplacementIndex(Frame frames[], bool *diskWrite);
void printResults(int totalReferences, int pageFaults, int diskWrites);

int main() {
    Frame frames[FRAME_SIZE];
    initializeFrames(frames);
    
    FILE* file = fopen(PAGE_REFERENCE_FILE, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    int totalReferences = 0, pageFaults = 0, diskWrites = 0;
    int pageNumber;
    char accessType;
    
    while (fscanf(file, "%d %c", &pageNumber, &accessType) != EOF) {
        totalReferences++;
        bool pageFound = false;
        
        for (int i = 0; i < FRAME_SIZE; i++) {
            if (frames[i].pageNumber == pageNumber) {
                frames[i].referenceBit = true;
                if (accessType == 'w') frames[i].modifiedBit = true;
                pageFound = true;
                break;
            }
        }
        
        if (!pageFound) {
            bool diskWrite = false;
            int indexToReplace = findReplacementIndex(frames, &diskWrite);
            if (diskWrite) diskWrites++;
            
            frames[indexToReplace].pageNumber = pageNumber;
            frames[indexToReplace].referenceBit = true;
            frames[indexToReplace].modifiedBit = (accessType == 'w');
            pageFaults++;
        }
    }
    
    fclose(file);
    printResults(totalReferences, pageFaults, diskWrites);
    
    return EXIT_SUCCESS;
}

void initializeFrames(Frame frames[]) {
    for (int i = 0; i < FRAME_SIZE; i++) {
        frames[i].pageNumber = -1; // Indicates frame is empty
        frames[i].referenceBit = false;
        frames[i].modifiedBit = false;
    }
}

int findReplacementIndex(Frame frames[], bool *diskWrite) {
    int pass, index = 0;
    
    // Four passes represent four categories (0,0), (0,1), (1,0), and (1,1)
    for (pass = 0; pass < 4; pass++) {
        for (int i = 0; i < FRAME_SIZE; i++) {
            bool ref = frames[i].referenceBit;
            bool mod = frames[i].modifiedBit;
            if (ref == ((pass / 2) % 2) && mod == (pass % 2)) {
                *diskWrite = mod;
                frames[i].referenceBit = false; // Reset reference bit before replacement
                return i; // Found the page to replace
            }
        }
    }
    
    // This point should never be reached if the algorithm is correct
    *diskWrite = frames[0].modifiedBit;
    return 0; // Fallback to the first frame if all else fails
}

void printResults(int totalReferences, int pageFaults, int diskWrites) {
    printf("Total Page References: %d\n", totalReferences);
    printf("Page Faults: %d\n", pageFaults);
    printf("Disk Writes: %d\n", diskWrites);
    printf("Page Fault Rate: %.2f%%\n", (double)pageFaults / totalReferences * 100);
}

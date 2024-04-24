# Page Replacement Algorithms

This assignment contains implementations of four classic page replacement algorithms: FIFO (First-In, First-Out), LRU (Least Recently Used), Second Chance, and Enhanced Second Chance. These algorithms are fundamental to understanding how operating systems manage memory, especially in handling page faults and optimizing memory access.

## Algorithms Overview

- **FIFO**: Replaces the oldest page in memory. Simple and intuitive, but not always optimal as it doesn't consider page access patterns.
- **LRU**: Evicts the least recently used page. More effective than FIFO in many scenarios as it considers recent page access history.
- **Second Chance**: A variation of FIFO that gives pages a "second chance" if they have been accessed recently.
- **Enhanced Second Chance**: Extends Second Chance by also considering if a page has been modified, prioritizing the eviction of pages that are not recently used and not modified.

## Compilation and Execution

The source code for each algorithm is provided in separate C files. To compile any of the algorithms, use a C compiler such as `gcc`. For example:

```bash
gcc FIFO.c -o FIFO
```

Replace `fifo.c` with the name of the source file for the algorithm you wish to compile. To execute the compiled program:

```bash
./FIFO
```

Ensure the input file `page_references.txt` is formatted correctly and located in the expected directory.

## Input Format

The input file `page_references.txt` should contain page references and access types (read/write), one per line, formatted like so:

```
45 w
82 r
9 w
...
```

## Expected Outcomes

- The programs report the page fault rate after processing all page references.
- The Enhanced Second Chance algorithm additionally reports the number of disk writes due to page replacements.

## Note

- Modify the `FRAME_SIZE` macro in each source file to experiment with different numbers of physical frames.

## Credits

- https://www.youtube.com/watch?v=C26qsPwf-Js&t=313s&ab_channel=Dr.RobertDimpsey
- https://www.geeksforgeeks.org/program-for-least-recently-used-lru-page-replacement-algorithm/
- https://www.geeksforgeeks.org/page-replacement-algorithms-in-operating-systems/
- https://stackoverflow.com/questions/58496569/how-does-the-enhanced-second-chance-algorithm-has-a-preference-to-the-changes-th


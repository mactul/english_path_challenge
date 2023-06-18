# English path challenge

This code was written quickly for a dev challenge, it's not realy optimized, but it works fine.

Here are the instructions:  
> Write a program that takes a starting word and an ending word as input and finds the shortest chain of words, changing one letter at a time, from the starting word to the ending word. All intermediate words must be valid English words.

Unfortunately, this doesn't work with a lot of english words, there is not enough words to always find a path.

This words works great:
- airth -> scags
- scalar -> footer
- abaci -> septa

## Installation:

Download the entire content of this repository, then, you can build the file with gcc like that:

On Windows:
```bash
gcc main.c a_star.c graph.c priority_queue.c -o path_challenge.exe -Wall -pedantic
```

On linux:
```bash
gcc main.c a_star.c graph.c priority_queue.c -o path_challenge -Wall -pedantic
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "a_star.h"


unsigned int get_distance(char* str1, char* str2)
{
    int i = 0;
    unsigned int distance = 0;
    while(str1[i] != '\0' && str2[i] != '\0')
    {
        if(str1[i] != str2[i])
        {
            distance += 1;
        }
        i++;
    }

    return distance;
}


int main()
{
    char word[MAX_WORD_SIZE];
    Graph* graph = graph_init();
    GraphNode* start;
    GraphNode* end;
    FILE* file;
    int word_len;

    printf("Enter the starting word: ");  // the a_star algorithm find the reversed path
    fgets(word, MAX_WORD_SIZE, stdin);
    end = graph_add_node(graph, word, 0);
    word_len = strlen(word);

    printf("Enter the ending word: ");
    fgets(word, MAX_WORD_SIZE, stdin);
    if(strlen(word) != word_len)
    {
        printf("error: the starting and the ending word must have the same size\n");
        exit(1);
    }
    start = graph_add_node(graph, word, get_distance(word, end->word));

    file = fopen("words_alpha.txt", "r");
    while(fgets(word, MAX_WORD_SIZE, file) != NULL)
    {
        if(strlen(word) == word_len)
        {
            graph_add_node(graph, word, get_distance(word, end->word));
        }
    }
    fclose(file);

    if(!a_star(start, end))
    {
        graph_free(&graph);
        printf("There is no path between the starting word and the ending word\n");
        exit(0);
    }

    printf("BEST PATH:\n");
    while(end != NULL)
    {
        printf("%s", end->word);
        end = end->came_from;
    }

    graph_free(&graph);
}
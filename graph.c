#include <stdlib.h>
#include <string.h>
#include "graph.h"

#define NODE_NUMBER_BASE 2048
#define NEIGHBORS_NUMBER_BASE 256

struct _graph {
    int node_number;
    int node_allocated;
    GraphNode** node_list;
};

char is_compatible_neighbor(GraphNode* node1, GraphNode* node2)
{
    int i = 0;
    char diff = 0;
    while(node1->word[i] != '\0' && node2->word[i] != '\0' && diff <= 1)
    {
        if(node1->word[i] != node2->word[i])
        {
            diff++;
        }
        i++;
    }
    if(diff == 1 && node1->word[i] == '\0' && node2->word[i] == '\0')
    {
        return 1;
    }

    return 0;
}

char add_one_way_neighbor(GraphNode* node1, GraphNode* node2)
{
    if(node1->neighbors_number == node1->_neighbors_allocated)
    {
        node1->_neighbors_allocated += NEIGHBORS_NUMBER_BASE;
        node1->neighbors = (GraphNode**) realloc(node1->neighbors, node1->_neighbors_allocated * sizeof(GraphNode*));
        if(node1->neighbors == NULL)
        {
            return 0;
        }
    }
    node1->neighbors[node1->neighbors_number] = node2;
    node1->neighbors_number++;

    return 1;
}

char add_neighbors(Graph* graph, GraphNode* node)
{
    for(int i = 0; i < graph->node_number; i++)
    {
        if(is_compatible_neighbor(graph->node_list[i], node))
        {
            if(!add_one_way_neighbor(node, graph->node_list[i]))
            {
                return 0;
            }
            if(!add_one_way_neighbor(graph->node_list[i], node))
            {
                return 0;
            }
        }
    }
    return 1;
}

Graph* graph_init(void)
{
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    if(graph == NULL)
    {
        return NULL;
    }
    graph->node_number = 0;
    graph->node_allocated = NODE_NUMBER_BASE;
    graph->node_list = (GraphNode**) malloc(graph->node_allocated * sizeof(GraphNode*));
    if(graph->node_list == NULL)
    {
        free(graph);
        return NULL;
    }

    return graph;
}

GraphNode* graph_add_node(Graph* graph, char* word, unsigned int heuristic)
{
    GraphNode* new_node = (GraphNode*) malloc(sizeof(GraphNode));
    if(new_node == NULL)
    {
        return NULL;
    }

    if(graph->node_number == graph->node_allocated)
    {
        graph->node_allocated += NODE_NUMBER_BASE;
        graph->node_list = (GraphNode**) realloc(graph->node_list, graph->node_allocated * sizeof(GraphNode*));
        if(graph->node_list == NULL)
        {
            free(new_node);
            return NULL;
        }
    }
    strncpy(new_node->word, word, MAX_WORD_SIZE);
    new_node->word[MAX_WORD_SIZE-1] = '\0';
    
    new_node->heuristic = heuristic;
    new_node->gscore = (unsigned int)(-1);
    new_node->fscore = (unsigned int)(-1);

    new_node->came_from = NULL;

    new_node->neighbors_number = 0;
    new_node->_neighbors_allocated = NODE_NUMBER_BASE;
    new_node->neighbors = (GraphNode**) malloc(sizeof(GraphNode*) * new_node->_neighbors_allocated);
    if(new_node->neighbors == NULL)
    {
        free(new_node);
        return NULL;
    }
    if(!add_neighbors(graph, new_node))
    {
        free(new_node->neighbors);
        free(new_node);
        return NULL;
    }

    graph->node_list[graph->node_number] = new_node;
    graph->node_number++;

    return new_node;
}

void graph_free(Graph** graph)
{
    if(*graph == NULL)
    {
        return;
    }

    for(int i = 0; i < (*graph)->node_number; i++)
    {
        GraphNode* node = (*graph)->node_list[i];
        free(node->neighbors);
        free(node);
    }
    free((*graph)->node_list);
    free(*graph);
    *graph = NULL;
}
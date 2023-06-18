#include <stdlib.h>
#include "graph.h"
#include "priority_queue.h"
#include "a_star.h"

char a_star(GraphNode* start, GraphNode* end)
{
    GraphNode* current;
    QueueEl* open_set = NULL;

    start->gscore = 0;
    start->fscore = start->heuristic;

    pqueue_add_el(&open_set, start, start->fscore);

    while((current = pqueue_next_el(&open_set)) != NULL)
    {
        if(current == end)
        {
            pqueue_free_all(&open_set);
            return 1;
        }

        for(int i = 0; i < current->neighbors_number; i++)
        {
            GraphNode* neighbor = current->neighbors[i];
            unsigned int tentative_gscore = current->gscore + 1;
            if(tentative_gscore < neighbor->gscore)
            {
                neighbor->came_from = current;
                neighbor->gscore = tentative_gscore;
                neighbor->fscore = tentative_gscore + neighbor->heuristic;
                pqueue_remove_node(&open_set, neighbor);
                pqueue_add_el(&open_set, neighbor, neighbor->fscore);
            }
        }
    }

    return 0;
}
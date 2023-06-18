// strlen("Pneumonoultramicroscopicsilicovolcanoconiosis") == 45
#define MAX_WORD_SIZE 64

typedef struct _graph_node {
    char word[MAX_WORD_SIZE];
    unsigned int heuristic;
    unsigned int gscore;
    unsigned int fscore;
    int neighbors_number;
    int _neighbors_allocated;
    struct _graph_node** neighbors;
    struct _graph_node* came_from;
} GraphNode;
typedef struct _graph Graph;

Graph* graph_init(void);
GraphNode* graph_add_node(Graph* graph, char* word, unsigned int heuristic);
void graph_free(Graph** graph);
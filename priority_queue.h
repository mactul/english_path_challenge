typedef struct _queue_el QueueEl;

void pqueue_add_el(QueueEl** root, GraphNode* node, unsigned int priority);
GraphNode* pqueue_next_el(QueueEl** root);
void pqueue_remove_node(QueueEl** root, GraphNode* node);
void pqueue_free_all(QueueEl** root);
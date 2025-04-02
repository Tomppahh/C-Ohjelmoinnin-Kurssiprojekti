// graph.h

#ifndef GRAPH_H
#define GRAPH_H

#define LENGTH 30


typedef struct edge {
    char *aDestination;
    int iDistance;
    struct EDGE *next;
} EDGE;

typedef struct nodeGraph {
    char *aSource;
    EDGE *edges;
} NODE_G


int GraphMenu(void);
void graphMenuLogic(void);

#endif
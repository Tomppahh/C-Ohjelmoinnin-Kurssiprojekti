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
    struct NODE_G *next;
} NODE_G;


int GraphMenu(void);
void graphMenuLogic(void);
void fileName(char *pFileName, char *pSentence);
NODE_G* buildGraphFromFile (NODE_G *nodeList, const char *aFile);
NODE_G* createGraphNode(NODE_G *nodeList, const char *name);
void addEdge(NODE_G *node, const char *aDest, int iDist);

#endif
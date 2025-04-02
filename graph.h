// graph.h

#ifndef GRAPH_H
#define GRAPH_H

#define LENGTH 30
#define ROW 60


typedef struct edge {
    const char *aDestination;
    int iDistance;
    struct edge *next;
} EDGE;

typedef struct nodeGraph {
    const char *aSource;
    EDGE *edges;
    struct nodeGraph *next;
} NODE_G;


int GraphMenu(void);
void graphMenuLogic(void);
void fileName(char *pFileName, char *pSentence);
NODE_G* buildGraphFromFile (NODE_G *nodeList, const char *aFile);
NODE_G* createGraphNode(NODE_G *nodeList, const char *name);
void addEdge(NODE_G *node, const char *aDest, int iDist);
void printGraph(const NODE_G *nodeList);

#endif
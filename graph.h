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
void fileName(char *pFileName, char *pSentence);
NODE_G* buildGraphFromFile (NODE *nodeList, const char *aFile);
NODE* createNode(NODE *nodeList, const char *name);
void addEdge(NODE_g *node, const char *aDest, int iDist);
void printGraph(nodeList);

#endif
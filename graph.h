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
} NODE_G;


int GraphMenu(void);
void graphMenuLogic(void);
void fileName(char *pFileName, char *pSentence);
<<<<<<< HEAD
NODE_G* buildGraphFromFile (NODE *nodeList, const char *aFile);
NODE* createGraphNode(NODE *nodeList, const char *name);
void addEdge(NODE_g *node, const char *aDest, int iDist);
=======
NODE_G* buildGraphFromFile (NODE_G *nodeList, const char *aFile);
NODE_G* createNode(NODE_G *nodeList, const char *name);
void addEdge(NODE_G *node, const char *aDest, int iDist);
void printGraph(nodeList);

#endif
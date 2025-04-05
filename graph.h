// graph.h

#ifndef GRAPH_H
#define GRAPH_H

#define LENGTH 30
#define ROW 60

// nopein matka algoritmille
typedef struct DjikstraList  {
    char *aCurrent;
    int *iDistanceBetween;
    char *aPreviousNode;
    struct DjikstraList *next;
} DLIST;

typedef struct edge {
    char *aDestination;
    int iDistance;
    struct edge *next;
} EDGE;

typedef struct nodeGraph {
    char *aSource;
    EDGE *edges;
    struct nodeGraph *next;
} NODE_G;


int GraphMenu(void);
void graphMenuLogic(void);
void fileName(char *pFileName, char *pSentence);
NODE_G* buildGraphFromFile (NODE_G *nodeList, const char *aFile);
NODE_G* createGraphNode(NODE_G **nodeList, const char *name);
NODE_G shortestPath(NODE_G *graph, const char *startNode, const char *goalNode, const char *outputFile);
void freeGraph(NODE_G *graph);
void addEdge(NODE_G *node, const char *aDest, int iDist);
void printGraph(const NODE_G *nodeList);
void removeGraphNode(NODE_G **nodeList, const char *aName);
char *firstTimeAskName(const char *aFileName);
void addOrUpdateArc(NODE_G **nodeList);

#endif
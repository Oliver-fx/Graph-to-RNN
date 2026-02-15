#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    NONE = 0,
    T433 = 1,
    T4231 = 2,
    T343 = 3,
    T442 = 4,
    T42121 = 5,
    T424 = 6,
} Position;

typedef enum {
    GOAL = 0,
    FORWARD = 1,
    MID = 2,
    DEFENSE = 3,
} PlayerField;

struct graph {
    int playerNum;
    Position tacticPosition;
    char teamName[100];
    struct PlayerFeature players[11];
    struct adjNode **edges;
}; 

struct PlayerFeature {
    int player_id;
    PlayerField playerPosition;
    float success_pass_rate;
};

struct adjNode {
    int player_id;
    Position reciever_position;
    struct edgeInfo eInfo;
    struct adjNode *next;
};

struct edgeInfo {
    int total_pass_with_passer;
    float success_rate;

    int count_D_M;              // Passes from Defense to Midfield on this edge
    int count_M_F;              // Passes from Midfield to Forward on this edge
    int count_D_F;              // Passes from Defense to Forward on this edge
    int count_other;
};

typedef struct graph *Graph;

Graph graphNew(int playerNum, Position tacticPosition, char teamName[100], struct PlayerFeature initialPlayerFeatures[]);

Graph graphNew(int playerNum, Position tacticPosition, char teamName[100], struct PlayerFeature initialPlayerFeatures[]) {
    Graph newGraph = malloc(sizeof(*newGraph));

    newGraph->playerNum = playerNum;
    newGraph->tacticPosition = tacticPosition;
    strncpy(newGraph->teamName, teamName, sizeof(newGraph->teamName) - 1);
    newGraph->teamName[sizeof(newGraph->teamName) - 1] = '\0';
    newGraph->edges = calloc(playerNum, sizeof(struct adjNode *));

    for (int i = 0; i < playerNum; i++) {
        newGraph->players[i] = initialPlayerFeatures[i];
    }

    return newGraph;
}


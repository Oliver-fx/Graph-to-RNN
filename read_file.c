#include <stdio.h>
#include <stdlib.h>

#include "graph_env.h"


Graph readStation(char *fileName) {
    FILE *fp = fopen(fileName, "r");

    if (fp == NULL) {
        fprintf(stderr, "error: failed to open '%s' for reading\n", fileName);
		exit(EXIT_FAILURE);
    }

    char area_name[100];
    if (fgets(area_name, sizeof(area_name), fp) == NULL) {
        fprintf(stderr, "error: failed to read area name\n");
		exit(EXIT_FAILURE);
    }

    Graph newGraph = graphNew(area_name);

    //float latitude, float longitude, char name[100], int wind_dir, float wind_speed, float p_level, float temp, float humidity
    float latitude = 0.0;
    float longitude = 0.0;
    char S_name[100];
    float wind_dir = 0.0;
    float wind_speed = 0.0;
    float p_level = 0.0;
    float temp = 0.0;
    float humidity = 0.0;
    
    int check = 0;

    while ((check = fscanf(fp, "%f %f %s %f %f %f %f %f", &latitude, &longitude, S_name, &wind_dir, &wind_speed, &p_level, &temp, &humidity)) != EOF) {
        //printf("READ: %f %f %s %f %f %f %f %f\n", latitude, longitude, S_name, wind_dir, wind_speed, p_level, temp, humidity);
        if (check != 8) {
            fprintf(stderr, "error: missing data");
            exit(EXIT_FAILURE);
        } else {
            add_station(newGraph, latitude, longitude, S_name, wind_dir, wind_speed, p_level, temp, humidity);
        }

    }
    
    fclose(fp);

    return newGraph;

}
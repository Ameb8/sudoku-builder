#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <stdbool.h>
#include <math.h>
#include <cjson/cJSON.h>
#include <stdint.h>
#include "../include/upload_puzzle.h"

typedef struct {
    char puzzle_vals[82];
    char solution_vals[82];
    uint8_t num_clues;
} puzzle_model;

static puzzle_model* init_puzzle_model(int puzzle[9][9]) {
    puzzle_model* model = (puzzle_model*)malloc(sizeof(puzzle_model));
    if((model) == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    model->num_clues = 0;

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            model->solution_vals[9 * i + j] = '0' + abs(puzzle[i][j]);
            
            if(puzzle[i][j] < 1) {
                model->puzzle_vals[9 * i + j] = '0' + 0;
            } else {
                model->puzzle_vals[9 * i + j] = '0' + puzzle[i][j];
                model->num_clues++;
            }
        }
    }

    model->puzzle_vals[81] = '\0';
    model->solution_vals[81] = '\0';

    return model;
}

static char* get_json(int puzzle[9][9]) {
    puzzle_model* model = init_puzzle_model(puzzle);
    cJSON *puzzle_json = cJSON_CreateObject();

    // Add the fields to the JSON object
    cJSON_AddStringToObject(puzzle_json, "puzzle_vals", model->puzzle_vals);
    cJSON_AddStringToObject(puzzle_json, "solution_vals", model->solution_vals);
    cJSON_AddNumberToObject(puzzle_json, "num_clues", model->num_clues);

    // Convert to string
    char *json_string = cJSON_PrintUnformatted(puzzle_json);
    cJSON_Delete(puzzle_json);
    return json_string;
}

bool upload_puzzle(int puzzle[9][9]) {
    /*
    CURL *curl;
    CURLcode result;

    const char *api_key = getenv("ADMIN_KEY");

    if(!api_key) {
        fprintf(stderr, "Environment variable PUZZLE_API_KEY not set.\n");
        return false;
    }*/

    char* puzzle_json = get_json(puzzle);
    printf("\nPuzzle JSON:\n%s\n", puzzle_json);

    // Get auth header string
    //char auth_header[256];
    //snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", api_key);

    free(puzzle_json);

    return true;
}
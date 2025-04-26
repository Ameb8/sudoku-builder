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
    cJSON_AddStringToObject(puzzle_json, "puzzleVals", model->puzzle_vals);
    cJSON_AddStringToObject(puzzle_json, "solutionVals", model->solution_vals);
    cJSON_AddNumberToObject(puzzle_json, "numClues", model->num_clues);

    // Convert to string
    char *json_string = cJSON_PrintUnformatted(puzzle_json);
    cJSON_Delete(puzzle_json);
    return json_string;
}

bool upload_puzzle(int puzzle[9][9]) {
    CURL *curl;
    CURLcode result;
    bool success = false;

    char *api_key = getenv("ADMIN_KEY");
    const char *api_url = getenv("API_URL");

    // Strip trailing newline from ADMIN_KEY
    if (api_key) {
        size_t len = strlen(api_key);
        if (len > 0 && (api_key[len - 1] == '\n' || api_key[len - 1] == '\r')) {
            api_key[len - 1] = '\0';  // Remove trailing newline or carriage return
        }
    }

    if (!api_key || !api_url) {
        fprintf(stderr, "Missing environment variables: ADMIN_KEY or API_URL not set.\n");
        return false;
    }

    char* puzzle_json = get_json(puzzle);
    if (!puzzle_json) {
        fprintf(stderr, "Failed to create JSON payload.\n");
        return false;
    }

    curl = curl_easy_init();
    if (curl) {
        struct curl_slist *headers = NULL;

        // Set headers
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "X-API-KEY: %s", api_key);

        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, auth_header);

        curl_easy_setopt(curl, CURLOPT_URL, api_url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, puzzle_json);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        result = curl_easy_perform(curl);
        if (result != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
        } else {
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            printf("Upload response code: %ld\n", http_code);
            success = (http_code >= 200 && http_code < 300);
        }

        // Cleanup
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    free(puzzle_json);

    return success;
}
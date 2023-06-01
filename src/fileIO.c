#include <fileIO.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

cJSON *cJSON_Read(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "cJSON Read Error: Unable to open the file: %s.\n", filename);
        exit(1);
    }
    char buffer[MAX_BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    int len = fread(buffer, 1, sizeof(buffer), fp);
    fclose(fp);

    cJSON *json = cJSON_Parse(buffer);
    if (json == NULL)
    {
        const char *err_ptr = cJSON_GetErrorPtr();
        if (err_ptr != NULL)
        {
            fprintf(stderr, "cJSON Read Error: %s.\n", err_ptr);
            exit(1);
        }
    }

    char *out = cJSON_Print(json);
    fprintf(stdout, "%s", out);

    return json;
}
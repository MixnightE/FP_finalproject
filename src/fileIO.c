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
    char buffer[8192];
    memset(buffer, 0, sizeof(buffer));
    int len = fread(buffer, 1, sizeof(buffer), fp);
    fclose(fp);

    cJSON *json = cJSON_Parse(buffer);
    if (json == NULL)
    {
        const char *err_ptr = cJSON_GetErrorPtr();
        if (err_ptr != NULL)
        {
            fprintf(stderr, "%s", buffer);
            fprintf(stderr, "cJSON Read Error on %s: %s.\n", filename, err_ptr);
            exit(1);
        }
    }

    char *out = cJSON_Print(json);
    // fprintf(stdout, "%s", out);

    return json;
}

void cJSON_Write(const char *filename, const cJSON *object)
{
    char *tmp = cJSON_Print(object);
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "cJSON Write Error: Unable to open the file: %s.\n", filename);
        exit(1);
    }
    // fprintf(stdout, "%s\n", tmp);
    fputs(tmp, fp);
    fclose(fp);
    cJSON_free(tmp);
}
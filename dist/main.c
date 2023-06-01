#include <cJSON.h>
#include <fileIO.h>
#include <stdio.h>

signed main(int argc, char *argv[])
{
    cJSON *json = cJSON_Read("./data/card.json");

    cJSON_Delete(json);
    return 0;
}
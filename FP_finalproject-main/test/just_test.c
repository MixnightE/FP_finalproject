

if (root != NULL && cJSON_IsObject(root)) {
        cJSON* cultist = cJSON_GetObjectItem(root, "Cultist");
        if (cultist != NULL && cJSON_IsObject(cultist)) {
            cJSON* buff = cJSON_GetObjectItem(cultist, "buff");
            if (buff != NULL && cJSON_IsObject(buff)) {
                cJSON* item = buff->child;
                while (item != NULL) {
                    if (cJSON_IsNumber(item)) {
                        const char* key = item->string;
                        int value = item->valueint;
                        printf("%s: %d\n", key, value);
                    }
                    item = item->next;
                }
            }
        }
    }
    
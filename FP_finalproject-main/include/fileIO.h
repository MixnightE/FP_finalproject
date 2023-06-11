#ifndef _FILE_IO_H_
#define _FILE_IO_H_

#define MAX_BUFFER_SIZE 1024

#include <cJSON.h>

/**
 * @brief 將json檔讀出來
 * @return 讀出來的json檔
 */
cJSON *cJSON_Read(const char *filename);

/**
 * @brief 將object寫入filename檔案中，並刪除object的資料
 */
void cJSON_Write(const char *filename, const cJSON *object);

#endif // _FILE_IO_H_
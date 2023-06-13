#ifndef _JSON_DEF_H_
#define _JSON_DEF_H_

#define DEBUG printf("Running At %s, %d line.\n", __FILE__, __LINE__);

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum JsonType
{
    Type_Null,
    Type_Bool,
    Type_Int,
    Type_Double,
    Type_String,
    Type_Array,
    Type_Object
} json_t;

typedef union JsonDatatype
{
    struct Json *data_obj;   // 指向Json物件
    struct Json *data_array; // 指向數組
    int data_int;            // 儲存int
    double data_double;      // 儲存double
    bool data_boolean;       // 儲存布林值
    char *data_string;       // 儲存字串
} json_dt;

typedef struct Json
{
    json_t type; // 標示json_dt現在是什麼型態的
    json_dt data;
    char *name;
    struct Json *next, *prev;
} json;

/**
 * 此Json結構可視為
 * {
 *     "$obj1$" : [],
 *     "$obj2$" : {
 *         ...
 *     },
 *     "$obj3$" : 123
 *     ...
 * }
 */

/**
 * @brief 新增並初始化一個新的Json物件
 */
json *NewJson();

/**
 * @brief 開啟Json檔案並讀取其內容至obj中，如果檔案不存在則創建新檔案並回傳
 * @param obj 開啟檔案之後儲存json檔案內容的buffer
 * @param filename 檔案名稱
 * @return (json *)obj
 */
json *JsonOpen(json *obj, char *filename);

/**
 * @brief 讀取json結構中的內容，並將其全部印出
 */
void JsonPrint(json *obj);
void JsonPrintWithIdt(json *obj, int indent);

/**
 * @brief Free掉obj的記憶體，如果obj為動態分配的記憶體則需自行free(obj)
 */
void JsonFree(json *obj);

/**
 * @brief 在$obj中找到name成員為$name的物件
 * @param name 要找的name
 * @return 找到的成員指針，沒找到則回傳NULL
 */
json *JsonAt(json *obj, char *name);

/**
 * @brief 將obj中的內容寫入filename中
 * @param filename 欲寫入之檔案名稱
 */
void JsonWrite(json *obj, char *filename);
void JsonWriteRecur(json *obj, FILE *file, int indent);

/**
 * @brief 在此層key後方寫入新的json物件，若key不存在則插入至最後
 * @param obj json主結構
 * @param key 要插入的key
 */
json *JsonAdd(json *obj, char *key, json *new_obj);

/**
 * @brief 刪除obj子結構中名為name的物件，如果要遞迴查找，請呼叫JsonDeleteRecur
 */
void JsonDelete(json *obj, char *name);

/**
 * @brief 遞迴查找並刪除子結構中名為name的物件
 */
void JsonDeleteRecur(json *obj, char *name);

/**
 * @brief 在此層key後方寫入新的值，若key不存在則插入至最後
 * @param obj 主結構
 * @param type 要插入的型態
 * @param data 數據
 */
json *JsonAddValue(json *obj, char *key, json_t type, void *data);

/* Json Sort Function */
json *JsonSortRoot(json *obj);
json *JsonSort(json *obj);
json *merge(json *first, json *second);
json *split(json *head);
json *mergeSort(json *head);
void updatePrevLinks(json *head);

/* Json Parse Function */
json *parseJson(const char *text);
json *parseValue(const char **text);
json *parseObject(const char **text);
json *parseArray(const char **text);
json *parseString(const char **text);
json *parseNumber(const char **text);
json *parseTrue(const char **text);
json *parseFalse(const char **text);
json *parseNull(const char **text);
void skipWhitespace(const char **text);

#endif // _JSON_DEF_H_
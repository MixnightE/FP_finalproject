#include "json_def.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

json *NewJson()
{
    json *obj = (json *)malloc(sizeof(json));
    return obj;
}

json *JsonOpen(json *obj, char *filename)
{
    // JsonClear(obj);
    FILE *f = fopen(filename, "r");
    obj->name = filename;
    if (f == NULL)
    {
        f = fopen(filename, "w");
        if (f == NULL)
        {
            fprintf(stderr, "Error: Unable to create file %s\n", filename);
            exit(1);
        }
        fprintf(f, "{\n}\n");
        fclose(f);
        obj->type = Type_Object;
        obj->data.data_obj = NULL;
        obj->name = filename;
        obj->next = NULL;
        obj->prev = NULL;
        return obj;
    }

    // 獲取檔案大小

    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);

    // 讀取檔案內容到一個字符串中

    char *fileContent = (char *)malloc(fileSize + 1);
    if (!fileContent)
    {
        fprintf(stderr, "Error: Unable to allocate memory for file content\n");
        exit(1);
    }
    fread(fileContent, 1, fileSize, f);
    fileContent[fileSize] = '\0';
    fclose(f);

    // 解析 JSON 字符串並存儲到 obj 中

    json *parsedJson = parseJson(fileContent);
    memcpy(obj, parsedJson, sizeof(json));

    // 釋放臨時分配的內存

    free(fileContent);

    // 假設 parseJson 返回的 json 結構體是動態分配的，所以需要釋放 parsedJson

    free(parsedJson);

    return obj;
}

void JsonPrint(json *obj)
{
    JsonPrintWithIdt(obj, 0);
}

void JsonPrintWithIdt(json *obj, int indent)
{
    if (!obj)
    {
        return;
    }

    for (int i = 0; i < indent; i++)
    {
        printf("    ");
    }

    if (obj->name)
    {
        printf("\"%s\": ", obj->name);
    }

    switch (obj->type)
    {
    case Type_Null:
        printf("null");
        break;
    case Type_Bool:
        printf(obj->data.data_boolean ? "true" : "false");
        break;
    case Type_Int:
        printf("%d", obj->data.data_int);
        break;
    case Type_Double:
        printf("%f", obj->data.data_double);
        break;
    case Type_String:
        printf("\"%s\"", obj->data.data_string);
        break;
    case Type_Object:
        printf("{\n");
        json *child = obj->data.data_obj;
        while (child)
        {
            JsonPrintWithIdt(child, indent + 1);
            if (child->next)
            {
                printf(",");
            }
            printf("\n");
            child = child->next;
        }
        for (int i = 0; i < indent; i++)
        {
            printf("    ");
        }
        printf("}");
        break;
    case Type_Array:
        printf("[\n");
        json *item = obj->data.data_array;
        while (item)
        {
            JsonPrintWithIdt(item, indent + 1);
            if (item->next)
            {
                printf(",");
            }
            printf("\n");
            item = item->next;
        }
        for (int i = 0; i < indent; i++)
        {
            printf("    ");
        }
        printf("]");
        break;
    default:
        fprintf(stderr, "Error: Invalid JSON type\n");
        exit(1);
    }
}

void JsonWrite(json *obj, char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Unable to create file %s\n", filename);
        exit(1);
    }

    JsonWriteRecur(obj, file, 0);

    fclose(file);
}

void JsonWriteRecur(json *obj, FILE *file, int indent)
{
    if (!obj)
    {
        return;
    }

    for (int i = 0; i < indent; i++)
    {
        fprintf(file, "    ");
    }

    if (obj->name)
    {
        fprintf(file, "\"%s\": ", obj->name);
    }

    switch (obj->type)
    {
    case Type_Null:
        fprintf(file, "null");
        break;
    case Type_Bool:
        fprintf(file, obj->data.data_boolean ? "true" : "false");
        break;
    case Type_Int:
        fprintf(file, "%d", obj->data.data_int);
        break;
    case Type_Double:
        fprintf(file, "%f", obj->data.data_double);
        break;
    case Type_String:
        fprintf(file, "\"%s\"", obj->data.data_string);
        break;
    case Type_Object:
        fprintf(file, "{\n");
        json *child = obj->data.data_obj;
        while (child)
        {
            JsonWriteRecur(child, file, indent + 1);
            if (child->next)
            {
                fprintf(file, ",");
            }
            fprintf(file, "\n");
            child = child->next;
        }
        for (int i = 0; i < indent; i++)
        {
            fprintf(file, "    ");
        }
        fprintf(file, "}");
        break;
    case Type_Array:
        fprintf(file, "[\n");
        json *item = obj->data.data_array;
        while (item)
        {
            JsonWriteRecur(item, file, indent + 1);
            if (item->next)
            {
                fprintf(file, ",");
            }
            fprintf(file, "\n");
            item = item->next;
        }
        for (int i = 0; i < indent; i++)
        {
            fprintf(file, "    ");
        }
        fprintf(file, "]");
        break;
    default:
        fprintf(stderr, "Error: Invalid JSON type\n");
        exit(1);
    }
}

void JsonFree(json *obj)
{
    if (!obj)
        return;

    if (obj->type == Type_String && obj->data.data_string)
    {
        free(obj->data.data_string);
    }
    else if (obj->type == Type_Object || obj->type == Type_Array)
    {
        json *child = obj->data.data_obj;
        while (child)
        {
            json *nextChild = child->next;
            JsonFree(child);
            free(child);
            child = nextChild;
        }
    }

    if (obj->name)
    {
        free(obj->name);
    }
}

json *JsonAt(json *obj, char *name)
{
    if (obj == NULL)
    {
        return NULL;
    }

    if (obj->name && strcmp(obj->name, name) == 0)
    {
        return obj;
    }

    switch (obj->type)
    {
    case Type_Null:
    case Type_Bool:
    case Type_Int:
    case Type_Double:
    case Type_String:
        return NULL;
        break;
    case Type_Array:
    {
        json *item = obj->data.data_array;
        while (item)
        {
            json *found = JsonAt(item, name);
            if (found)
            {
                return found;
            }
            item = item->next;
        }
    }
    break;
    case Type_Object:
    {
        json *child = obj->data.data_obj;
        while (child)
        {
            json *found = JsonAt(child, name);
            if (found)
            {
                return found;
            }
            child = child->next;
        }
    }
    break;
    }

    return NULL;
}

// json *JsonAdd(json *obj, json *new_obj, char *key)
// {
//     if (!obj || !new_obj)
//         return NULL;

//     if (!key)
//     {
//         // 將 new 插入到 obj 的末尾
//         json *last = obj;
//         while (last->next)
//         {
//             last = last->next;
//         }
//         last->next = new;
//         new->prev = last;
//         new->next = NULL;
//         return obj;
//     }

//     json *current = obj;
//     while (current)
//     {
//         if (current->name && strcmp(current->name, position) == 0)
//         {
//             // 將 new 插入到 current 的後面
//             new->prev = current;
//             new->next = current->next;
//             if (current->next)
//             {
//                 current->next->prev = new;
//             }
//             current->next = new;
//             return obj;
//         }
//         current = current->next;
//     }

//     // 未找到匹配的節點，將 new 插入到 obj 的末尾
//     json *last = obj;
//     while (last->next)
//     {
//         last = last->next;
//     }
//     last->next = new;
//     new->prev = last;
//     new->next = NULL;
//     return obj;
// }

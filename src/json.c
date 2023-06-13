#include "json.h"

json *NewJson()
{
    json *obj = (json *)malloc(sizeof(json));
    obj->type = Type_Object;
    obj->next = NULL;
    obj->prev = NULL;
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
    // 判斷型態
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
            // 遞迴，tab增加一個
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
                fprintf(file, "\n");
            }
            child = child->next;
        }
        if (obj->data.data_obj)
        {
            fprintf(file, "\n");
            for (int i = 0; i < indent; i++)
            {
                fprintf(file, "    ");
            }
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
                fprintf(file, "\n");
            }
            item = item->next;
        }
        if (obj->data.data_array)
        {
            fprintf(file, "\n");
            for (int i = 0; i < indent; i++)
            {
                fprintf(file, "    ");
            }
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

void JsonDelete(json *obj, char *name)
{
    if (!obj || !name)
        return;

    if (obj->type == Type_Object || obj->type == Type_Array)
    {
        json *prevChild = NULL;
        json *child = obj->data.data_obj;
        while (child)
        {
            if (child->name && strcmp(child->name, name) == 0)
            {
                // 若child有next，就設定next的prev為child的prev
                if (child->next)
                    child->next->prev = prevChild;

                // 若child有prev，就設定prev的next為child的next
                if (prevChild)
                    prevChild->next = child->next;
                // 若obj的data_obj為child，就設定obj的data_obj為child的next
                else
                    obj->data.data_obj = child->next;

                // 刪除找到的物件
                JsonFree(child);
                free(child);
                return;
            }
            prevChild = child;
            child = child->next;
        }
    }
}

void JsonDeleteRecur(json *obj, char *name)
{
    if (!obj || !name)
        return;

    json *prevChild = NULL;
    json *child = obj->data.data_obj;

    while (child)
    {
        if (child->name && strcmp(child->name, name) == 0)
        {
            // 若child有next，就設定next的prev為child的prev
            if (child->next)
                child->next->prev = prevChild;

            // 若child有prev，就設定prev的next為child的next
            if (prevChild)
                prevChild->next = child->next;
            // 若obj的data_obj為child，就設定obj的data_obj為child的next
            else
                obj->data.data_obj = child->next;

            // 刪除找到的物件
            JsonFree(child);
            free(child);
            return;
        }

        // 如果當前的 child 是一個物件或數組，則進入該物件或數組並進行刪除操作
        if (child->type == Type_Object || child->type == Type_Array)
            JsonDeleteRecur(child, name);

        prevChild = child;
        child = child->next;
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
    // 判斷條件
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
            // 遞迴下去找子結構
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
    // 找不到回傳NULL
    return NULL;
}

json *JsonAdd(json *obj, char *key, json *add_obj)
{
    if (obj == NULL)
        return add_obj;

    json *current = obj;
    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = add_obj;
    add_obj->prev = current;
    add_obj->name = strdup(key); // 確保 key 是分配的新記憶體區塊

    return obj;
}

json *JsonAddValue(json *obj, char *key, json_t type, void *data)
{
    if (obj->type != Type_Object)
    {
        fprintf(stderr, "Error: The given JSON object is not of Type_Object\n");
        exit(1);
    }
    // 如果type是object或array這種可以遞迴下去的，且它的name等於NULL，代表它是根物件
    if ((type == Type_Object || type == Type_Array) && data && ((json *)data)->name == NULL)
    {
        ((json *)data)->name = strdup(key);
        if (obj->data.data_obj == NULL)
        {
            obj->data.data_obj = (json *)data;
        }
        else
        {
            json *current = obj->data.data_obj;
            while (current->next != NULL)
            {
                current = current->next;
            }

            current->next = (json *)data;
            ((json *)data)->prev = current;
        }
    }
    else
    {
        // 新配置空間作為加進去的東西的位置
        json *add_obj = (json *)malloc(sizeof(json));
        if (!add_obj)
        {
            fprintf(stderr, "Error: Out of memory\n");
            exit(1);
        }

        add_obj->type = type;
        add_obj->name = strdup(key); // 確保 key 是分配的新記憶體區塊
        add_obj->next = NULL;
        add_obj->prev = NULL;
        // 判斷型態
        switch (type)
        {
        case Type_Null:
            break;
        case Type_Bool:
            add_obj->data.data_boolean = *(bool *)data;
            break;
        case Type_Int:
            add_obj->data.data_int = *(int *)data;
            break;
        case Type_Double:
            add_obj->data.data_double = *(double *)data;
            break;
        case Type_String:
            add_obj->data.data_string = strdup((char *)data);
            break;
        case Type_Array:
        case Type_Object:
            add_obj->data.data_obj = (json *)data;
            break;
        default:
            fprintf(stderr, "Error: Invalid JSON type\n");
            exit(1);
        }
        // 找到當前鏈表的尾端並加進去
        if (obj->data.data_obj == NULL)
        {
            obj->data.data_obj = add_obj;
        }
        else
        {
            json *current = obj->data.data_obj;
            while (current->next != NULL)
            {
                current = current->next;
            }

            current->next = add_obj;
            add_obj->prev = current;
        }
    }

    return obj;
}

json *JsonSort(json *obj)
{
    // 判斷當前節點是否為空
    if (obj == NULL)
        return NULL;

    if (obj->name == NULL)
    {
        obj->name = "";
    }
    // 如果當前節點是物件或者是陣列
    if (obj->type == Type_Object || obj->type == Type_Array)
    {
        json *child = obj->data.data_obj;
        while (child != NULL)
        {
            // 對每個子物件進行排序
            JsonSort(child);
            child = child->next;
        }
        // 然後對本身的子物件鏈表進行排序
        if (obj->type == Type_Object)
            obj->data.data_obj = mergeSort(obj->data.data_obj);
    }
    if (obj->name == "")
        obj->name = NULL;
    return obj;
}

json *JsonSortRoot(json *obj)
{
    // 創建假的父物件
    json *fakeParent = (json *)malloc(sizeof(json));
    fakeParent->type = Type_Object;
    fakeParent->data.data_obj = obj;
    fakeParent->name = NULL;
    fakeParent->next = NULL;
    fakeParent->prev = NULL;

    // 對假的父物件進行排序
    fakeParent = JsonSort(fakeParent);

    // 返回排序後的子物件
    return fakeParent->data.data_obj;
}

void updatePrevLinks(json *head)
{
    // 將prev指針連上去
    json *temp = head;
    json *prev = NULL;
    while (temp)
    {
        temp->prev = prev;
        prev = temp;
        temp = temp->next;
    }
}

json *merge(json *first, json *second)
{
    if (!first)
    {
        return second;
    }

    if (!second)
    {
        return first;
    }
    // 合併，決定誰要排前面
    if (strcmp(first->name, second->name) < 0)
    {
        first->next = merge(first->next, second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        second->next = merge(first, second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

json *mergeSort(json *head)
{
    if (!head || !head->next)
    {
        return head;
    }
    json *second = split(head);
    // Recur for left and right halves
    head = mergeSort(head);
    second = mergeSort(second);

    // Merge the two sorted halves
    json *sorted_list = merge(head, second);

    // Update previous links
    updatePrevLinks(sorted_list);
    return sorted_list;
}

json *split(json *head)
{
    // 快慢指針
    json *fast = head;
    json *slow = head;
    while (fast->next != NULL && fast->next->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    json *temp = slow->next;
    slow->next = NULL;
    return temp;
}

json *parseJson(const char *text)
{
    skipWhitespace(&text);
    return parseValue(&text);
}

json *parseValue(const char **text)
{
    skipWhitespace(text);

    if (**text == '{')
        return parseObject(text);
    else if (**text == '[')
        return parseArray(text);
    else if (**text == '\"')
        return parseString(text);
    else if (isdigit(**text) || **text == '-')
        return parseNumber(text);
    else if (strncmp(*text, "true", 4) == 0)
        return parseTrue(text);
    else if (strncmp(*text, "false", 5) == 0)
        return parseFalse(text);
    else if (strncmp(*text, "null", 4) == 0)
        return parseNull(text);
    else
    {
        fprintf(stderr, "Error: Invalid JSON value\n");
        exit(1);
    }
}

json *parseObject(const char **text)
{
    json *object = NewJson();
    object->type = Type_Object;
    object->data.data_obj = NULL;
    object->name = NULL;
    object->next = NULL;
    object->prev = NULL;

    json *current = NULL;

    (*text)++; // Skip '{'
    skipWhitespace(text);

    while (**text != '}' && **text != '\0')
    {
        json *key = parseString(text);
        skipWhitespace(text);

        if (**text != ':')
        {
            fprintf(stderr, "Error: Missing colon in object\n");
            exit(1);
        }

        (*text)++; // Skip ':'
        json *value = parseValue(text);

        value->name = key->data.data_string;
        free(key);

        if (current == NULL)
        {
            object->data.data_obj = value;
            current = value;
        }
        else
        {
            current->next = value;
            value->prev = current;
            current = value;
        }

        skipWhitespace(text);

        if (**text == ',')
        {
            (*text)++; // Skip ','
            skipWhitespace(text);
        }
        else if (**text != '}')
        {
            fprintf(stderr, "Error: Missing comma in object\n");
            exit(1);
        }
    }

    if (**text != '}')
    {
        fprintf(stderr, "Error: Missing closing brace in object\n");
        exit(1);
    }

    (*text)++; // Skip '}'
    return object;
}

json *parseArray(const char **text)
{
    json *array = NewJson();
    array->type = Type_Array;
    array->data.data_array = NULL;
    array->name = NULL;
    array->next = NULL;
    array->prev = NULL;
    json *current = NULL;

    (*text)++; // Skip '['
    skipWhitespace(text);

    while (**text != ']' && **text != '\0')
    {
        json *item = parseValue(text);

        if (current == NULL)
        {
            array->data.data_array = item;
            current = item;
        }
        else
        {
            current->next = item;
            item->prev = current;
            current = item;
        }

        skipWhitespace(text);

        if (**text == ',')
        {
            (*text)++; // Skip ','
            skipWhitespace(text);
        }
        else if (**text != ']')
        {
            fprintf(stderr, "Error: Missing comma in array\n");
            exit(1);
        }
    }

    if (**text != ']')
    {
        fprintf(stderr, "Error: Missing closing bracket in array\n");
        exit(1);
    }

    (*text)++; // Skip ']'
    return array;
}

json *parseString(const char **text)
{
    json *str = NewJson();
    str->type = Type_String;
    str->next = NULL;
    str->prev = NULL;

    const char *start = ++(*text); // Skip '\"'

    while (**text != '\"' && **text != '\0')
    {
        (*text)++;
    }

    if (**text != '\"')
    {
        fprintf(stderr, "Error: Missing closing quote in string\n");
        exit(1);
    }

    size_t length = *text - start;
    str->data.data_string = (char *)malloc(length + 1);
    strncpy(str->data.data_string, start, length);
    str->data.data_string[length] = '\0';

    (*text)++; // Skip '\"'
    return str;
}

json *parseNumber(const char **text)
{
    json *number = NewJson();
    number->next = NULL;
    number->prev = NULL;
    char *end;
    double value = strtod(*text, &end);

    if (value == (int)value)
    {
        number->type = Type_Int;
        number->data.data_int = (int)value;
    }
    else
    {
        number->type = Type_Double;
        number->data.data_double = value;
    }

    *text = end;
    return number;
}

json *parseTrue(const char **text)
{
    json *result = NewJson();
    result->type = Type_Bool;
    result->data.data_boolean = true;
    result->next = NULL;
    result->prev = NULL;
    *text += 4; // Skip "true"
    return result;
}

json *parseFalse(const char **text)
{
    json *result = NewJson();
    result->type = Type_Bool;
    result->data.data_boolean = false;
    result->next = NULL;
    result->prev = NULL;
    *text += 5; // Skip "false"
    return result;
}

json *parseNull(const char **text)
{
    json *result = NewJson();
    result->type = Type_Null;
    result->next = NULL;
    result->prev = NULL;
    *text += 4; // Skip "null"
    return result;
}

void skipWhitespace(const char **text)
{
    while (isspace(**text))
    {
        (*text)++;
    }
}
#include "json_def.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

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
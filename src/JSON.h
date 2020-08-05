#ifndef JSON_H
#define JSON_H
#include"LinkedList.h"
#include"Tokenizer.h"
#include"Memalloc.h"


typedef struct JsonType{
  JSON_NULL;
  JSON_OBJECT;
  JSON_ARRAY;
  JSON_BOOLEAN;
  JSON_NUMBER;
  JSON_STRING;
  JSON_ELEMENT;
} JsonType;

typedef struct JSON{
  double double_val;
  char   *string;
  int    int_val;
}

typedef struct JsonGeneric JsonGeneric, JsonNull;
struct JsonGeneric {
  JsonType type;
};

typedef struct JsonObject JsonObject,JsonArray;
struct JsonObject {
  JsonType type;
  LinkedList list;
};

typedef struct JsonBoolean JsonBoolean;
struct JsonBoolean {
  JsonType type;
  int value;
};

typedef struct JsonNumber JsonNumber;
struct JsonNumber {
  JsonType type;
  double value;
};

typedef struct JsonString JsonString;
struct JsonString {
  JsonType type;
  char *name;
};

typedef struct JsonElement JsonElement;
struct JsonElement {
  JsonType type;
  char *name;
  JsonGeneric *value;
};

JsonGeneric *createJsonObject();
JsonGeneric *createJsonArray();
JsonGeneric *createJsonBoolean(int value);
JsonGeneric *createJsonNumber(double value);
JsonGeneric *createJsonString(char *str);
JsonGeneric *createJsonElement(char *str, JsonGeneric *value);
JsonObject  *JsonParse(char *strToParse);




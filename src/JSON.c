#include "JSON.h"
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Memalloc.h"
#include "LinkedList.h"
#include "CException.h"
#include "Exception.h"


Token *getnewToken(Tokenizer *tokenizer, Token *token){
 freeToken(token);
 return token = getToken(tokenizer);
}

/*
JsonGeneric *createJsonArray(){
  JsonArray* jsonArr;
  
}
*/

//createJsonNumber is a pointer to a funtion taking in int value and returning to JsonGeneric
JsonGeneric* createJsonBoolean(int value){
  JsonBoolean* jsonBool;
  jsonBool = memAlloc(sizeof(JsonBoolean));
  jsonBool->type = JSON_BOOLEAN;
  jsonBool->value = value;
  return (JsonGeneric*)jsonBool;
}

//createJsonNumber is pointer to function takinng in double value and returning to JsonGeneric
JsonGeneric* createJsonNumber(double value){
  JsonNumber* jsonNum;
  jsonNum = memAlloc(sizeof(JsonNumber));
  jsonNum->type  = JSON_NUMBER;
  jsonNum->value = value; 
  return (JsonGeneric*)jsonNum;
}

//createJsonString is a pointer to a funtion taking in str and returning to JsonGeneric
JsonGeneric *createJsonString(char *str){
  JsonString* jsonStr;
  jsonStr = memAlloc(sizeof(JsonString));
  jsonStr->type = JSON_STRING;
  jsonStr->name = str;
  return (JsonGeneric*)jsonStr;
}

//createJsonElement is a pointer to a funtion taking in char str and int value and returning to JsonGeneric
JsonGeneric *createJsonElement(char *str, JsonGeneric *value){
  JsonElement* jsonElem;
  jsonElem = memAlloc(sizeof(JsonElement));
  jsonElem->type = JSON_ELEMENT;
  jsonElem->key = str;
  jsonElem->type = JSON_ELEMENT;
  jsonElem->value= value;
  return (JsonGeneric*)jsonElem;
}

JsonObject  *parserJsonElement(Tokenizer *tokenizer){
  token = getToken(tokenizer);
  JsonElement* jsonElem;
  jsonElem = memAlloc(sizeof(JsonElement));
  jsonElem->type = JSON_ELEMENT;
  jsonElem->key = tokenizer;
  jsonElem->type = JSON_ELEMENT;
  jsonElem->value= tokenizer;
  return (JsonObject*)jsonElem;
}
  
  
  
  
































































/*
static int json_parse_value(const char ** cursor, json_value * parent);

static void skip_whitespace(const char** cursor)
{
	if (**cursor == '\0') return;
	while (iscntrl(**cursor) || isspace(**cursor)) ++(*cursor);
}

static int has_char(const char** cursor, char character)
{
	skip_whitespace(cursor);
	int success = **cursor == character;
	if (success) ++(*cursor);
	return success;
}

static int json_parse_object(const char** cursor, json_value* parent)
{
	json_value result = { .type = TYPE_OBJECT };
	vector_init(&result.value.object, sizeof(json_value));

	int success = 1;
	while (success && !has_char(cursor, '}')) {
		json_value key = { .type = TYPE_NULL };
		json_value value = { .type = TYPE_NULL };
		success = json_parse_value(cursor, &key);
		success = success && has_char(cursor, ':');
		success = success && json_parse_value(cursor, &value);

		if (success) {
			vector_push_back(&result.value.object, &key);
			vector_push_back(&result.value.object, &value);
		}
		else {
			json_free_value(&key);
			break;
		}
		skip_whitespace(cursor);
		if (has_char(cursor, '}')) break;
		else if (has_char(cursor, ',')) continue;
		else success = 0;
	}

	if (success) {
		*parent = result;
	}
	else {
		json_free_value(&result);
	}

	return success;
	return 1;
}

static int json_parse_array(const char** cursor, json_value* parent)
{
	int success = 1;
	if (**cursor == ']') {
		++(*cursor);
		return success;
	}
	while (success) {
		json_value new_value = { .type = TYPE_NULL };
		success = json_parse_value(cursor, &new_value);
		if (!success) break;
		skip_whitespace(cursor);
		vector_push_back(&parent->value.array, &new_value);
		skip_whitespace(cursor);
		if (has_char(cursor, ']')) break;
		else if (has_char(cursor, ',')) continue;
		else success = 0;
	}
	return success;
}


void json_free_value(json_value* val)
{
	if (!val) return;

	switch (val->type) {
		case TYPE_STRING:
			free(val->value.string);
			val->value.string = NULL;
			break;
		case TYPE_ARRAY:
		case TYPE_OBJECT:
			vector_foreach(&(val->value.array), (void(*)(void*))json_free_value);
			vector_free(&(val->value.array));
			break;
	}

	val->type = TYPE_NULL;
}

int json_is_literal(const char** cursor, const char* literal) {
	size_t cnt = strlen(literal);
	if (strncmp(*cursor, literal, cnt) == 0) {
		*cursor += cnt;
		return 1;
	}
	return 0;
}

static int json_parse_value(const char** cursor, json_value* parent)
{
	// Eat whitespace
	int success = 0;
	skip_whitespace(cursor);
	switch (**cursor) {
		case '\0':
			// If parse_value is called with the cursor at the end of the string
			// that's a failure
			success = 0;
			break;
		case '"':
			++*cursor;
			const char* start = *cursor;
			char* end = strchr(*cursor, '"');
			if (end) {
				size_t len = end - start;
				char* new_string = malloc((len + 1) * sizeof(char));
				memcpy(new_string, start, len);
				new_string[len] = '\0';

				assert(len == strlen(new_string));

				parent->type = TYPE_STRING;
				parent->value.string = new_string;

				*cursor = end + 1;
				success = 1;
			}
			break;
		case '{':
			++(*cursor);
			skip_whitespace(cursor);
			success = json_parse_object(cursor, parent);
			break;
		case '[':
			parent->type = TYPE_ARRAY;
			vector_init(&parent->value.array, sizeof(json_value));
			++(*cursor);
			skip_whitespace(cursor);
			success = json_parse_array(cursor, parent);
			if (!success) {
				vector_free(&parent->value.array);
			}
			break;
		case 't': {
			success = json_is_literal(cursor, "true");
			if (success) {
				parent->type = TYPE_BOOL;
				parent->value.boolean = 1;
			}
			break;
		}
		case 'f': {
			success = json_is_literal(cursor, "false");
			if (success) {
				parent->type = TYPE_BOOL;
				parent->value.boolean = 0;
			}
			break;
		}
		case 'n':
			success = json_is_literal(cursor, "null");
			break;
		default: {
			char* end;
			double number = strtod(*cursor, &end);
			if (*cursor != end) {
				parent->type = TYPE_NUMBER;
				parent->value.number = number;
				*cursor = end;
				success = 1;
			}
		}
	}

	return success;
}


int json_parse(const char* input, json_value* result)
{
	return json_parse_value(&input, result);
}

char* json_value_to_string(json_value* value)
{
	assert(value->type == TYPE_STRING);
	return (char *)value->value.string;
}

double json_value_to_double(json_value* value)
{
	assert(value->type == TYPE_NUMBER);
	return value->value.number;
}

int json_value_to_bool(json_value* value)
{
	assert(value->type == TYPE_BOOL);
	return value->value.boolean;
}

vector* json_value_to_array(json_value* value)
{
	assert(value->type == TYPE_ARRAY);
	return &value->value.array;
}

vector* json_value_to_object(json_value* value)
{
	assert(value->type == TYPE_OBJECT);
	return &value->value.object;
}

json_value* json_value_at(const json_value* root, size_t index)
{
	assert(root->type == TYPE_ARRAY);
	if (root->value.array.size < index) {
		return vector_get_checked(&root->value.array,index);
	}
	else {
		return NULL;
	}
}

json_value* json_value_with_key(const json_value* root, const char* key)
{
	assert(root->type == TYPE_OBJECT);
	json_value* data = (json_value*)root->value.object.data;
	size_t size = root->value.object.size;
	for (size_t i = 0; i < size; i += 2)
	{
		if (strcmp(data[i].value.string, key) == 0)
		{
			return &data[i + 1];
		}
	}
	return NULL;
}
*/


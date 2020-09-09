#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "JSON.h"
#include "Error.h"
#include "Memalloc.h"
#include "LinkedList.h"
#include "Exception.h"
#include "CException.h"

Token *getnewToken(Tokenizer *tokenizer, Token *token){
 freeToken(token);
 return token = getToken(tokenizer);
}

JsonGeneric *createJsonNull(){
  JsonNull* jsonNull;
  jsonNull = memAlloc(sizeof(JsonNull));
  jsonNull->type = JSON_NULL;
  return (JsonGeneric*)jsonNull;
}

JsonGeneric *createJsonArray(){
  JsonArray* jsonArr;
  jsonArr = memAlloc(sizeof(JsonArray));
  jsonArr->type = JSON_ARRAY;
  return (JsonGeneric*)jsonArr;
}

JsonGeneric *createJsonObject(){
  JsonObject* jsonObj;
  jsonObj = memAlloc(sizeof(JsonObject));
  jsonObj->type = JSON_OBJECT;
}

//createJsonBoolean is a pointer to a funtion taking in int value and returning to JsonGeneric
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
JsonGeneric *createJsonElement(char *key, JsonGeneric *value){
  JsonElement* jsonElem;
  jsonElem = memAlloc(sizeof(JsonElement));
  jsonElem->type = JSON_ELEMENT;
  jsonElem->key = key;
  jsonElem->value= value;
  return (JsonGeneric*)jsonElem;
}


void verifyAndConsumeToken(Tokenizer *tokenizer,char* str){
  Token *token;
  token = getToken(tokenizer);
  if(strcmp(token->str,str)==0){
    freeToken(token);
    return;
  }
  throwException(ERR_MALFORMED_JSON_ELEMENT,token,"expect %s, but encountered %s", str ,token->str );
}
    

JsonElement *parseJsonElement(Tokenizer *tokenizer){
  Token *token0, *token1,*token2;
  JsonGeneric *jsonNull;
  JsonNumber  *jsonNum;
  JsonBoolean *jsonBool;
  JsonString  *jsonStr;
  JsonElement *jsonElem;
  
  token0 = getToken(tokenizer);
  if(token0->type != TOKEN_STRING_TYPE) 
    throwException(ERR_MALFORMED_JSON_ELEMENT,token0,"This is not a string"); 
  
  verifyAndConsumeToken(tokenizer, ":");
  
  token1 = (Token*)getToken(tokenizer);
  token2 = (Token*)getToken(tokenizer); 
  
  if(token2->type != TOKEN_NULL_TYPE){
    freeToken(token0);
    freeToken(token1);
    throwException(ERR_INVALID_CONSTANT,token2,"There should not be any character here");
  }
  
  if(token1->type == TOKEN_INTEGER_TYPE){
    jsonNum = (JsonNumber*)createJsonNumber(((IntegerToken*)token1)->value);
    jsonElem = (JsonElement*)createJsonElement(strdup(token0->str),(JsonGeneric*)jsonNum);
  } else if (token1->type == TOKEN_FLOAT_TYPE){
    jsonNum = (JsonNumber*)createJsonNumber(((FloatToken*)token1)->value);
    jsonElem = (JsonElement*)createJsonElement(strdup(token0->str),(JsonGeneric*)jsonNum);
  } else if (token1->type == TOKEN_STRING_TYPE){
      jsonStr = (JsonString*)createJsonString(((StringToken*)token1)->str);
      jsonElem = (JsonElement*)createJsonElement(strdup(token0->str),(JsonGeneric*)jsonStr);
  } else if (token1->type == TOKEN_IDENTIFIER_TYPE ){
    if(strcmp(token1->str,"null") == 0){
      jsonNull = (JsonNull*)createJsonNull();
      jsonElem = (JsonElement*)createJsonElement(strdup(token0->str),(JsonGeneric*)jsonNull);
    } else{
      if(strcmp(token1->str,"false") == 0){
        jsonBool = (JsonBoolean*)createJsonBoolean(0);
        jsonElem = (JsonElement*)createJsonElement(strdup(token0->str),(JsonGeneric*)jsonBool);
      } else if(strcmp(token1->str,"true") == 0){
        jsonBool = (JsonBoolean*)createJsonBoolean(1);
        jsonElem = (JsonElement*)createJsonElement(strdup(token0->str),(JsonGeneric*)jsonBool);  
      } else {
        throwException(ERR_INVALID_CONSTANT,token1,"This is not null, true or false");
      }        
    }
  } else{
    throwException(ERR_MALFORMED_JSON_ELEMENT,token1,"This is an unknown type"); 
  } 
    
  freeToken(token0);
  freeToken(token1);
  return jsonElem;
}


JsonObject *parseJsonObject(Tokenizer *tokenizer){
  Token *token0, *token1;
  JsonObject *jsonObj;
  
  verifyAndConsumeToken(tokenizer, "{");
  
  token0 = getToken(tokenizer);
  if(token0->type != TOKEN_STRING_TYPE) 
    throwException(ERR_MALFORMED_JSON_ELEMENT,token0,"This is not a string"); 
  
  verifyAndConsumeToken(tokenizer, ":");
  
  token1 = (Token*)getToken(tokenizer);
  if(token1->type != TOKEN_INTEGER_TYPE || token1->type != TOKEN_FLOAT_TYPE || token1->type != TOKEN_STRING_TYPE || token1->type != TOKEN_IDENTIFIER_TYPE)
    throwException(ERR_MALFORMED_JSON_ELEMENT,token1,"This is an unknown type");
  else{
  jsonObj = (JsonObject*)createJsonObject();
  }
  
  verifyAndConsumeToken(tokenizer, "}");
}



































































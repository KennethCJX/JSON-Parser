#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "unity.h"
#include "Memalloc.h"
#include "LinkedList.h"
#include "JSON.h"
#include "Tokenizer.h"
#include "Token.h"
#include "Common.h"
#include "Exception.h"
#include "Error.h"
#include "CException.h"

CEXCEPTION_T ex;

void setUp(void)
{
}

void tearDown(void)
{

}
void test_createJsonNull_given_NULL_expect_JsonNull_with_NULL(void){
  JsonGeneric *jsonNull;
  jsonNull = (JsonGeneric*)createJsonNull();
  TEST_ASSERT_EQUAL(JSON_NULL,jsonNull->type); 
}


void test_createJsonBoolean_given_1_is_true_expect_JsonBoolean_with_1(void)
{
  JsonBoolean *jsonBool;
  jsonBool = (JsonBoolean*)createJsonBoolean(1);
  TEST_ASSERT_EQUAL(JSON_BOOLEAN,jsonBool->type);
  TEST_ASSERT_EQUAL(1,jsonBool->value);
}

void test_createJsonBoolean_given_0_is_false_expect_JsonBoolean_with_0(void)
{
  JsonBoolean *jsonBool;
  jsonBool = (JsonBoolean*)createJsonBoolean(0);
  TEST_ASSERT_EQUAL(JSON_BOOLEAN,jsonBool->type);
  TEST_ASSERT_EQUAL(0,jsonBool->value);
}

void test_createJsonNumber_given_45678_expect_JsonNumber_with_45678(void)
{
  JsonNumber *json;
  json = (JsonNumber*)createJsonNumber(45678);
  TEST_ASSERT_EQUAL(JSON_NUMBER,json->type);
  TEST_ASSERT_EQUAL(45678,json->value);
}

void test_createJsonString_given_the_name_Ali_expect_JsonString_with_Ali(void)
{
  JsonString *json;
  json = (JsonString*)createJsonString("Ali");
  TEST_ASSERT_EQUAL(JSON_STRING,json->type);
  TEST_ASSERT_EQUAL_STRING("Ali",json->name);
}


void test_createJsonElement_given_name_Abu_and_value_21_expect_JsonElement_with_Abu_and_21(void)
{
  JsonElement *elem;
  elem = (JsonElement*)createJsonElement("Abu",createJsonNumber(21.123));
  TEST_ASSERT_EQUAL(JSON_ELEMENT,elem->type);
  TEST_ASSERT_EQUAL_STRING("Abu",elem->key);
  TEST_ASSERT_EQUAL(JSON_ELEMENT,elem->type);
  JsonNumber* jsonNum = (JsonNumber*)elem->value;
  TEST_ASSERT_EQUAL(JSON_NUMBER,jsonNum->type);
  TEST_ASSERT_FLOAT_WITHIN(1.0e-7,21.123,jsonNum->value);
}



void test_parseJsonElement_given_age_with_number_34(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;
  
  tokenizer = createTokenizer(" \"age\" : 34 ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_ASSERT_EQUAL(JSON_ELEMENT, elem->type);
    TEST_ASSERT_EQUAL_STRING("age", elem->key);
    TEST_ASSERT_EQUAL(JSON_NUMBER, elem->value->type);
    TEST_ASSERT_EQUAL(34,((JsonNumber*)elem->value)->value);
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
  }
  freeTokenizer(tokenizer);
}

void test_parseJsonElement_given_silly_plus_2_expect_ERR_MALFORMED_JSON_ELEMENT_to_be_thrown(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;
  
  tokenizer = createTokenizer(" silly+2 ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_FAIL_MESSAGE("Expect ERR_MALFORMED_JSON_ELEMENT to be thrown");
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_ASSERT_EQUAL(ERR_MALFORMED_JSON_ELEMENT,ex->errorCode);
  } 
  freeTokenizer(tokenizer);
}

void test_parseJsonElement_given_dummy_here_and_there_expect_ERR_MALFORMED_JSON_ELEMENT_to_be_thrown(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;
  
  tokenizer = createTokenizer(" dummy here and there ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_FAIL_MESSAGE("Expect ERR_MALFORMED_JSON_ELEMENT to be thrown");
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_ASSERT_EQUAL(ERR_MALFORMED_JSON_ELEMENT,ex->errorCode);
  } 
  freeTokenizer(tokenizer);
}

void test_parseJsonElement_given_string_with_name_questionMark_ali_expect_ERR_MALFORMED_JSON_ELEMENT_to_be_thrown(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;
  
  tokenizer = createTokenizer(" \"name\" ? \"ali\" ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_FAIL_MESSAGE("Expect ERR_MALFORMED_JSON_ELEMENT to be thrown");
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_ASSERT_EQUAL(ERR_MALFORMED_JSON_ELEMENT,ex->errorCode);
  } 
  freeTokenizer(tokenizer);
}

void test_parseJsonElement_given_string_with_name_colon_AT_symbol_expect_ERR_MALFORMED_JSON_ELEMENT_to_be_thrown(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;
  
  tokenizer = createTokenizer(" \"Abu\" : @ ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_FAIL_MESSAGE("Expect ERR_MALFORMED_JSON_ELEMENT to be thrown");
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_ASSERT_EQUAL(ERR_MALFORMED_JSON_ELEMENT,ex->errorCode);
  } 
  freeTokenizer(tokenizer);
}

void test_parseJsonElement_given_dollar_sign_and_false_expect_ERR_MALFORMED_JSON_ELEMENT_to_be_thrown(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;
  
  tokenizer = createTokenizer(" $ : false ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_FAIL_MESSAGE("Expect ERR_MALFORMED_JSON_ELEMENT to be thrown");
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_ASSERT_EQUAL(ERR_MALFORMED_JSON_ELEMENT,ex->errorCode);
  } 
  freeTokenizer(tokenizer);
}

void test_parseJsonElement_given_married_and_false(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;
  
  tokenizer = createTokenizer(" \"married\" : false ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_ASSERT_EQUAL(JSON_ELEMENT, elem->type);
    TEST_ASSERT_EQUAL_STRING("married", elem->key);
    TEST_ASSERT_EQUAL(JSON_BOOLEAN, elem->value->type);
    TEST_ASSERT_EQUAL(false,((JsonBoolean*)elem->value)->value);
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
  }
  freeTokenizer(tokenizer);
}

void test_parseJsonElement_given_married_and_true(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;
  
  tokenizer = createTokenizer(" \"married\" : true ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_ASSERT_EQUAL(JSON_ELEMENT, elem->type);
    TEST_ASSERT_EQUAL_STRING("married", elem->key);
    TEST_ASSERT_EQUAL(JSON_BOOLEAN, elem->value->type);
    TEST_ASSERT_EQUAL(true,((JsonBoolean*)elem->value)->value);
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
  }
  freeTokenizer(tokenizer);
}

 //check prob
void test_parseJsonElement_given_string_with_swim_and_true_plus_one_expect_ERR_INVALID_CONSTANT_to_be_thrown(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;
  
  tokenizer = createTokenizer(" \"swim\" : true+1 ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_FAIL_MESSAGE("Expect ERR_INVALID_CONSTANT to be thrown");
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_ASSERT_EQUAL(ERR_INVALID_CONSTANT,ex->errorCode);
  } 
  freeTokenizer(tokenizer);
}

void test_parseJsonElement_given_string_with_cake_and_good_expect_ERR_INVALID_CONSTANT_to_be_thrown(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;
  
  tokenizer = createTokenizer(" \"cake\" : good ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_FAIL_MESSAGE("Expect ERR_INVALID_CONSTANT to be thrown");
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_ASSERT_EQUAL(ERR_INVALID_CONSTANT,ex->errorCode);
  } 
  freeTokenizer(tokenizer);
}

void test_parseJsonElement_given_string_with_jump_there_and_false_expect_ERR_MALFORMED_JSON_ELEMENT_to_be_thrown(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;
  
  tokenizer = createTokenizer(" \"jump\" \"there\" : false ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_FAIL_MESSAGE("Expect ERR_MALFORMED_JSON_ELEMENT to be thrown");
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_ASSERT_EQUAL(ERR_MALFORMED_JSON_ELEMENT,ex->errorCode);
  } 
  freeTokenizer(tokenizer);
}

void test_parseJsonElement_given_food_and_null(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;
  
  tokenizer = createTokenizer(" \"food\" : null ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_ASSERT_EQUAL(JSON_ELEMENT, elem->type);
    TEST_ASSERT_EQUAL_STRING("food", elem->key);
    TEST_ASSERT_EQUAL(JSON_NULL, elem->value->type);

  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
  }
  freeTokenizer(tokenizer);
}

void test_parseJsonElement_given_string_with_swim_and_reyna_expect_ERR_INVALID_CONSTANT_to_be_thrown(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;
  
  tokenizer = createTokenizer(" \"swim\" : reyna ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_FAIL_MESSAGE("Expect ERR_INVALID_CONSTANT to be thrown");
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_ASSERT_EQUAL(ERR_INVALID_CONSTANT,ex->errorCode);
  } 
  freeTokenizer(tokenizer);
}


void test_parseJsonElement_given_height_and_1_dot_75(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;
  
  tokenizer = createTokenizer(" \"height\" : 1.75 ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_ASSERT_EQUAL(JSON_ELEMENT, elem->type);
    TEST_ASSERT_EQUAL_STRING("height", elem->key);
    TEST_ASSERT_EQUAL(JSON_NUMBER, elem->value->type);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-7,1.75,((JsonNumber*)elem->value)->value);
    
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
  }
  freeTokenizer(tokenizer);
}


void test_parseJsonElement_given_height_and_8_dot_e_expect_ERR_INVALID_FLOAT_exception_to_be_thrown(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;
  
  tokenizer = createTokenizer(" \"height\" : 8.e ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_FAIL_MESSAGE("Expect ERR_INVALID_FLOAT to be thrown");
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_ASSERT_EQUAL(ERR_INVALID_FLOAT,ex->errorCode);
  } 
  freeTokenizer(tokenizer);
}

void test_parseJsonElement_given_height_and_2dot3456e_plus_plus_8_expect_ERR_INVALID_FLOAT_exception_to_be_thrown(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;
  
  tokenizer = createTokenizer(" \"height\" : 1.98765e++8 ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_FAIL_MESSAGE("Expect ERR_INVALID_FLOAT to be thrown");
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_ASSERT_EQUAL(ERR_INVALID_FLOAT,ex->errorCode);
  } 
  freeTokenizer(tokenizer);
}

void test_parseJsonElement_given_height_and_8dot43210e_minus_minus_60_ERR_INVALID_FLOAT_exception_to_be_thrown(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;
  
  tokenizer = createTokenizer(" \"height\" : 8.43210e--60 ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_FAIL_MESSAGE("Expect ERR_INVALID_FLOAT to be thrown");
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_ASSERT_EQUAL(ERR_INVALID_FLOAT,ex->errorCode);
  } 
  freeTokenizer(tokenizer);
}
     

void test_parseJsonElement_given_string_John_and_David(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;
  
  tokenizer = createTokenizer(" \"John\" : \"David\" ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_ASSERT_EQUAL(JSON_ELEMENT, elem->type);
    TEST_ASSERT_EQUAL_STRING("John", elem->key);
    TEST_ASSERT_EQUAL(JSON_STRING, elem->value->type);
    TEST_ASSERT_EQUAL_STRING("David",((JsonString*)elem->value)->name);
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
  }
  freeTokenizer(tokenizer);
}

void test_parseJsonElement_given_string_Jackson_and_hello_minus_1_expeect_ERR_INVALID_STRING_to_be_thrown(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;

  tokenizer = createTokenizer(" \"Jackson\" : \"hello-1 ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_FAIL_MESSAGE("Expect ERR_INVALID_STRING to be thrown");
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_ASSERT_EQUAL(ERR_INVALID_STRING,ex->errorCode);
  } 
  freeTokenizer(tokenizer);
}


void test_parseJsonElement_given_string_Jackson_and_bye_plus_3_expeect_ERR_INVALID_CONSTANT_to_be_thrown(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonElement *elem;

  tokenizer = createTokenizer(" \"Jackson\" : bye+3 ");
  Try{
    elem = (JsonElement *)parseJsonElement(tokenizer);
    TEST_FAIL_MESSAGE("Expect ERR_INVALID_CONSTANT to be thrown");
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_ASSERT_EQUAL(ERR_INVALID_CONSTANT,ex->errorCode);
  } 
  freeTokenizer(tokenizer);
}


void test_parseJsonObject_given_json_object(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonObject *jsonObj;
  JsonElement *elem;
  DoubleLinkedList  *listPtr;
  
  tokenizer = createTokenizer(" { " 
                              " \"boolean\" : true " 
                              " } ");
  Try{
    jsonObj = (JsonObject *)parseJsonObject(tokenizer);
    elem = (JsonElement*)listPtr->head->data;
    jsonObj = (JsonObject*)elem->key;
    TEST_ASSERT_EQUAL(JSON_OBJECT, jsonObj->type);
    TEST_ASSERT_EQUAL_PTR("boolean",jsonObj);
    //TEST_ASSERT_EQUAL(JSON_BOOLEAN, (((json->data->)elem)->value)->type);
    //TEST_ASSERT_EQUAL(true,((((JsonBoolean*)json->data)->elem)->value)->value);
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
  }
   freeTokenizer(tokenizer);
}   



/*    
void test_parseJsonObject_given_json_object_and_array(void){
  Tokenizer *tokenizer;
  Token *token;
  JsonGeneric *json;
  
  tokenizer = createTokenizer(" { " 
                              " \"array\" : [2, 2.33, true, false, null, \"hello\"] " 
                              "}  ");
  Try{
    json = (JsonGeneric *)parseJsonObject(tokenizer); 
    //dumpJsonEntityString(json,0);
  }Catch(ex){
    dumpTokenErrorMessage(ex,1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
  } 
  freeTokenizer(tokenizer);
}
*/







  








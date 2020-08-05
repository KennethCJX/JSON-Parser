#include <stdio.h>
#include <stdlib.h>
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

/*pass JSON_STRING inside JsonElement and check name
     (type)|JsonElement| 
     (key) | name      |
     (value|           |  --> |JsonString|
                              | name     |
*/
void test_parse_JsonElement_given_name_with_string_John(void)
{
Tokenizer *tokenizer;
Token *token;
JsonElement *elem

tokenizer = createTokenizer("\"name\":\John\" ");
Try{
    elem = (JsonElement *)parserJsonElement(tokenizer);
    TEST_ASSERT_EQUAL (JSON_ELEMENT, elem->type);
    TEST_ASSERT_EQUAL_STRING ("name", elem->name);
    TEST_ASSERT_EQUAL (JSON_STRING, elem->value->type);
    TEST_ASSERT_EQUAL_STRING ("ali",((JsonString *)elem->value)->name);
    freeTokenizer(tokenizer);
}catch(ex){
  dempTokenErrorMessage(ex,1);
  TEST_FAIL_MESSAGE("Do not expect exception to be thrown.");
 }
}

/*pass JSON_Number inside JsonElement and check age
elem--->  JsonElement       JSON_NUMBER
          age         -->    12345678

*/
void test_parse_JsonElement_given_age_with_number_12345678(void)
{
Tokenizer *tokenizer;
Token *token;
JsonElement *elem

tokenizer = createTokenizer("\"age\":\12345678\" ");
Try{
    elem = (JsonElement *)parserJsonElement(tokenizer);
    TEST_ASSERT_EQUAL (JSON_ELEMENT, elem->type);
    TEST_ASSERT_EQUAL_STRING ("age", elem->name);
    TEST_ASSERT_EQUAL (JSON_NUMBER, elem->->value->type);
    TEST_ASSERT_EQUAL_STRING (12345678,((JsonString *)elem->value)->value);
    freeTokenizer(tokenizer);
}catch(ex){
  dempTokenErrorMessage(ex,1);
  TEST_FAIL_MESSAGE("Do not expect exception to be thrown.");
 }
}

/*pass Json object and array inside JsonGeneric
JsonGeneric --> JsonObject --> JsonArray -->JsonBoolean
                                         -->JsonNumber


*/

void test_parse_JsonElement_given_json_object_and_array(void)
{
Tokenizer *tokenizer;
Token *token;
JsonGeneric *json;

tokenizer = createTokenizer("{"
  "\"array\" : [True,false,2,null,\"hello\"] "
"}    ");

Try{
    json = (JsonGeneric *)parserJsonObject(tokenizer);
    freeTokenizer(tokenizer);
    dumpJsonString(json,0);
}catch(ex){
  dempTokenErrorMessage(ex,1);
  TEST_FAIL_MESSAGE("Do not expect exception to be thrown.");
 }
}


/* pass age,array,boolean that are point by JsonGeneric
json --> JsonArray --> JsonBoolean
                   --> JsonNumber
                   --> JsonString
*/
void test_parseJsonObject_given_json_object_array_age_and_boolean(void)
{
Tokenizer *tokenizer;
Token *token;
JsonGeneric *json;

tokenizer = createTokenizer(
"{"
"  \"age\" : 20,"
"  \"boolean\" : true,"
"  \"my object\" : {"
"                    \"value\" : 0.23405e-1,"
"                     \"date\" : \"29/7/2020\" "
"     \"array\" : [true,flase,2,  "
"                 {"
"                  \"json\":\"naisuuu!\", "
"                  \"start now\":false , "
"                  \"data\": [0x12C,2C,null]  "
"                  },"
"                  null, \"hello\"}  "
"}  ");

Try{
    json = (JsonGeneric *)parserJsonObject(tokenizer);
    freeTokenizer(tokenizer);
    dumpJsonString(json,0);
}catch(ex){
  dempTokenErrorMessage(ex,1);
  TEST_FAIL_MESSAGE("Do not expect exception to be thrown.");
 }
}
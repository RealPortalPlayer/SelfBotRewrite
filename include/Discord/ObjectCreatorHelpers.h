// Purpose: Helper macros to help with creating Discord objects
// Created on: 4/27/24 @ 1:17 AM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#define SBR_OBJECTCREATORHELPERS_HEADER(type, assertMessage) \
type* object = malloc(sizeof(type));                         \
BA_ASSERT(object != NULL, "Failed to allocate memory for " assertMessage "\n")

#define SBR_OBJECTCREATORHELPERS_CHECK_REQUIRED(name) \
if (name == NULL) {                                   \
    free(object);                                     \
    return NULL;                                      \
} (void) NULL

#define SBR_OBJECTCREATORHELPERS_GET_KEY_STRING_NOT_SAME(key, keyString) keyString
#define SBR_OBJECTCREATORHELPERS_GET_KEY_STRING_SAME(key, keyString) #key

#define SBR_OBJECTCREATORHELPERS_CHECK_OPTIONAL(name) (void) NULL

#define SBR_OBJECTCREATORHELPERS_GET(key, keyString, required, sameKey) \
json_object* key = json_object_object_get(unparsedJsonData, SBR_OBJECTCREATORHELPERS_GET_KEY_STRING_ ## sameKey(key, keyString)); \
SBR_OBJECTCREATORHELPERS_CHECK_ ## required(key)

#define SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(key, keyString, type, sameKey) \
SBR_OBJECTCREATORHELPERS_GET(key, keyString, type, sameKey);                  \
object->key = SBR_Snowflake_ConvertFromNumber(json_object_get_int(key))

#define SBR_OBJECTCREATORHELPERS_GET_STRING(key, keyString, type, sameKey) \
SBR_OBJECTCREATORHELPERS_GET(key, keyString, type, sameKey);               \
object->key = json_object_get_string(key)

#define SBR_OBJECTCREATORHELPERS_GET_BOOLEAN(key, keyString, type, sameKey) \
SBR_OBJECTCREATORHELPERS_GET(key, keyString, type, sameKey);                \
object->key = json_object_get_boolean(key)

#define SBR_OBJECTCREATORHELPERS_GET_INTEGER(key, keyString, type, sameKey) \
SBR_OBJECTCREATORHELPERS_GET(key, keyString, type, sameKey);                \
object->key = json_object_get_int(key)

#define SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(key, keyString, type, sameKey, flags, bit) \
SBR_OBJECTCREATORHELPERS_GET(key, keyString, type, sameKey);                                   \
if (json_object_get_boolean(key))                                                              \
    BA_BITWISE_SET_BIT(object->flags, bit)

#define SBR_OBJECTCREATORHELPERS_FOOTER() return object

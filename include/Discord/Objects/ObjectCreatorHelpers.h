// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

// Purpose: Helper macros to help with creating Discord objects
// Created on: 4/27/24 @ 1:17 AM

#pragma once

#include <BaconAPI/Debugging/Assert.h>
#include <BaconAPI/Math/Bitwise.h>
#include <string.h>

#include "Snowflake.h"
#include "User.h"
#include "../Locale.h"
#include "../Permissions.h"
#include "Time.h"
#include "Memory.h"

#define SBR_OBJECTCREATORHELPERS_HEADER(type, memoryType, assertMessage) \
if (unparsedJsonData == NULL)                                \
    return NULL;                                             \
BA_LOGGER_TRACE("Creating object: %s\n", json_object_to_json_string(unparsedJsonData)); \
type* object = BA_Memory_Allocate(sizeof(type), memoryType); \
memset(object, 0, sizeof(type))

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

#define SBR_OBJECTCREATORHELPERS_SET(key, keyString, required, sameKey) \
do {                                                                    \
    SBR_OBJECTCREATORHELPERS_GET(key, keyString, required, sameKey);    \
    object->key

#define SBR_OBJECTCREATORHELPERS_GRAB(key, required, caller) \
do {                                                         \
    object->key = caller(object->key ## Id);                 \
    SBR_OBJECTCREATORHELPERS_CHECK_ ## required(object->key); \
} while (BA_BOOLEAN_FALSE)


#define SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(key, keyString, required, sameKey) SBR_OBJECTCREATORHELPERS_SET(key, keyString, required, sameKey) = SBR_Snowflake_ConvertFromNumber(json_object_get_uint64(key)); } while (BA_BOOLEAN_FALSE)
#define SBR_OBJECTCREATORHELPERS_GET_STRING(key, keyString, required, sameKey) SBR_OBJECTCREATORHELPERS_SET(key, keyString, required, sameKey) = json_object_get_string(key); } while (BA_BOOLEAN_FALSE)
#define SBR_OBJECTCREATORHELPERS_GET_BOOLEAN(key, keyString, required, sameKey) SBR_OBJECTCREATORHELPERS_SET(key, keyString, required, sameKey) = json_object_get_boolean(key); } while (BA_BOOLEAN_FALSE)
#define SBR_OBJECTCREATORHELPERS_GET_INTEGER(key, keyString, required, sameKey) SBR_OBJECTCREATORHELPERS_SET(key, keyString, required, sameKey) = json_object_get_int(key); } while (BA_BOOLEAN_FALSE)

#define SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(key, keyString, required, sameKey, flags, bit) \
do {                                                                                               \
    SBR_OBJECTCREATORHELPERS_GET(key, keyString, required, sameKey);                               \
    if (json_object_get_boolean(key))                                                              \
        BA_BITWISE_SET_BIT(object->flags, bit);                                                    \
} while (BA_BOOLEAN_FALSE)

#define SBR_OBJECTCREATORHELPERS_GET_JSON_OBJECT(key, keyString, required, sameKey) SBR_OBJECTCREATORHELPERS_SET(key, keyString, required, sameKey) = key; } while (BA_BOOLEAN_FALSE)
#define SBR_OBJECTCREATORHELPERS_GET_USER(key, keyString, required, sameKey) SBR_OBJECTCREATORHELPERS_SET(key, keyString, required, sameKey) = SBR_DiscordUser_Create(key); } while (BA_BOOLEAN_FALSE)
#define SBR_OBJECTCREATORHELPERS_GET_LOCALE(key, keyString, required, sameKey) SBR_OBJECTCREATORHELPERS_SET(key, keyString, required, sameKey) = SBR_DiscordLocales_FromLanguageCode(json_object_get_string(key)); } while (BA_BOOLEAN_FALSE)
#define SBR_OBJECTCREATORHELPERS_GET_PERMISSIONS(key, keyString, required, sameKey) SBR_OBJECTCREATORHELPERS_SET(key, keyString, required, sameKey) = SBR_DiscordPermissions_ConvertFromString(json_object_get_string(key)); } while (BA_BOOLEAN_FALSE)

#define SBR_OBJECTCREATORHELPERS_GRAB_GUILD(key, required) SBR_OBJECTCREATORHELPERS_GRAB(key, required, SBR_DiscordGuild_Get)

#define SBR_OBJECTCREATORHELPERS_GET_TIME(key, keyString, required, sameKey) SBR_OBJECTCREATORHELPERS_SET(key, keyString, required, sameKey) = SBR_Time_Parse(json_object_get_string(key)); } while (BA_BOOLEAN_FALSE)

#define SBR_OBJECTCREATORHELPERS_FOOTER() return object

#define SBR_OBJECTCREATORHELPERS_DEALLOCATE_CHECK_REQUIRED(variable) (void) variable;
#define SBR_OBJECTCREATORHELPERS_DEALLOCATE_CHECK_OPTIONAL(variable) if (variable != NULL) 

#define SBR_OBJECTCREATORHELPERS_CHECK(variable, required) SBR_OBJECTCREATORHELPERS_DEALLOCATE_CHECK_ ## required(variable)

#define SBR_OBJECTCREATORHELPERS_DEALLOCATE_MANUAL(variable, size, type, required) \
SBR_OBJECTCREATORHELPERS_CHECK(variable, required)                                 \
BA_Memory_Deallocate(variable, size, type)

#define SBR_OBJECTCREATORHELPERS_DEALLOCATE_SNOWFLAKE(variable, required) \
SBR_OBJECTCREATORHELPERS_CHECK(variable, required)                        \
SBR_Snowflake_Deallocate(variable)

#define SBR_OBJECTCREATORHELPERS_DEALLOCATE_USER(variable, required) \
SBR_OBJECTCREATORHELPERS_CHECK(variable, required)                   \
SBR_DiscordUser_Deallocate(variable)

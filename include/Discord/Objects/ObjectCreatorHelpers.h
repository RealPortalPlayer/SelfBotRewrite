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

#define SBR_OBJECTCREATORHELPERS_HEADER(type, assertMessage) \
if (unparsedJsonData == NULL)                                \
    return NULL;                                             \
BA_LOGGER_TRACE("Creating object: %s\n", json_object_to_json_string(unparsedJsonData)); \
type* object = malloc(sizeof(type));                         \
BA_ASSERT(object != NULL, "Failed to allocate memory for " assertMessage "\n"); \
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
SBR_OBJECTCREATORHELPERS_GET(key, keyString, required, sameKey);        \
object->key

#define SBR_OBJECTCREATORHELPERS_GET_SNOWFLAKE(key, keyString, required, sameKey) SBR_OBJECTCREATORHELPERS_SET(key, keyString, required, sameKey) = SBR_Snowflake_ConvertFromNumber(json_object_get_uint64(key))
#define SBR_OBJECTCREATORHELPERS_GET_STRING(key, keyString, required, sameKey) SBR_OBJECTCREATORHELPERS_SET(key, keyString, required, sameKey) = json_object_get_string(key)
#define SBR_OBJECTCREATORHELPERS_GET_BOOLEAN(key, keyString, required, sameKey) SBR_OBJECTCREATORHELPERS_SET(key, keyString, required, sameKey) = json_object_get_boolean(key)
#define SBR_OBJECTCREATORHELPERS_GET_INTEGER(key, keyString, required, sameKey) SBR_OBJECTCREATORHELPERS_SET(key, keyString, required, sameKey) = json_object_get_int(key)

#define SBR_OBJECTCREATORHELPERS_SET_BIT_ON_BOOLEAN(key, keyString, required, sameKey, flags, bit) \
SBR_OBJECTCREATORHELPERS_GET(key, keyString, required, sameKey);                                   \
if (json_object_get_boolean(key))                                                                  \
    BA_BITWISE_SET_BIT(object->flags, bit)

#define SBR_OBJECTCREATORHELPERS_GET_JSON_OBJECT(key, keyString, required, sameKey) SBR_OBJECTCREATORHELPERS_SET(key, keyString, required, sameKey) = key
#define SBR_OBJECTCREATORHELPERS_GET_USER(key, keyString, required, sameKey) SBR_OBJECTCREATORHELPERS_SET(key, keyString, required, sameKey) = SBR_DiscordUser_Create(key)
#define SBR_OBJECTCREATORHELPERS_GET_LOCALE(key, keyString, required, sameKey) SBR_OBJECTCREATORHELPERS_SET(key, keyString, required, sameKey) = SBR_DiscordLocales_FromLanguageCode(json_object_get_string(key))

#define SBR_OBJECTCREATORHELPERS_GET_PERMISSIONS(key, keyString, required, sameKey) SBR_OBJECTCREATORHELPERS_SET(key, keyString, required, sameKey) = SBR_DiscordPermissions_ConvertFromString(json_object_get_string(key))

#define SBR_OBJECTCREATORHELPERS_FOOTER() return object

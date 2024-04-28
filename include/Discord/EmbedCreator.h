// Purpose: Help make embeds
// Created on: 4/28/24 @ 12:20 PM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <BaconAPI/Internal/Boolean.h>
#include <BaconAPI/Storage/DynamicArray.h>

#include "Discord/Objects/User.h"

typedef struct {
    BA_Boolean inlined;
    char* name;
    char* value;
} SBR_EmbedCreator_Field;

typedef struct {
    char* url;
    char* proxyUrl;
    int height;
    int width;
} SBR_EmbedCreator_Media;

typedef struct {
    char* title;
    char* description;
    // TODO: timestamp
    int color;
    struct {
        char* text;
        char* iconUrl;
        char* proxyIconUrl;
    } footer;
    SBR_EmbedCreator_Media image;
    SBR_EmbedCreator_Media thumbnail;
    SBR_EmbedCreator_Media video;
    struct {
        char* name;
        char* url;
    } provider;
    struct {
        char* name;
        char* url;
        char* iconUrl;
        char* proxyIconUrl;
    } author;
    BA_DynamicArray fields;

    /**
     * This is internal. Do not edit this
     */
    size_t characterCount;
} SBR_EmbedCreator_Embed;

#define SBR_EMBEDCREATOR_CREATE_SETTER(name, ...) SBR_EmbedCreator_Embed* SBR_EmbedCreator_Set ## name(SBR_EmbedCreator_Embed* embed, __VA_ARGS__)

#define SBR_EMBEDCREATOR_CREATE_MEDIA_SETTER(name) SBR_EMBEDCREATOR_CREATE_SETTER(name, const char* url, const char* proxyUrl, int height, int width)

SBR_EmbedCreator_Embed* SBR_EmbedCreator_Create(void);
SBR_EMBEDCREATOR_CREATE_SETTER(Title, const char* title);
SBR_EMBEDCREATOR_CREATE_SETTER(Description, const char* description);
SBR_EMBEDCREATOR_CREATE_SETTER(Footer, const char* text, const char* iconUrl, const char* proxyIconUrl);
SBR_EMBEDCREATOR_CREATE_MEDIA_SETTER(Image);
SBR_EMBEDCREATOR_CREATE_MEDIA_SETTER(Thumbnail);
SBR_EMBEDCREATOR_CREATE_MEDIA_SETTER(Video);
SBR_EMBEDCREATOR_CREATE_SETTER(Provider, const char* name, const char* url);
SBR_EMBEDCREATOR_CREATE_SETTER(Author, SBR_DiscordUser* user);

SBR_EmbedCreator_Embed* SBR_EmbedCreator_AddField(SBR_EmbedCreator_Embed* embed, const char* name, const char* value, BA_Boolean inlined);

/**
 * You usually shouldn't need to call this directly 
 */
json_object* SBR_EmbedCreator_Build(SBR_EmbedCreator_Embed* embed);

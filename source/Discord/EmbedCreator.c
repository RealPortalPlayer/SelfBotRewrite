// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <stdlib.h>
#include <BaconAPI/Logger.h>
#include <BaconAPI/Debugging/Assert.h>
#include <BaconAPI/String.h>
#include <BaconAPI/Internal/Boolean.h>
#include <string.h>

#include "Discord/EmbedCreator.h"

#define SBR_EMBEDCREATOR_SET_STRING(root, variable, value) \
if (root->variable != NULL) {                              \
    embed->characterCount -= strlen(root->variable);       \
    free(root->variable);                                  \
}                                                          \
if (value != NULL) {                                       \
    embed->characterCount += strlen(value);                \
    root->variable = BA_String_Copy(value);                \
} else                                                     \
    root->variable = NULL


#define SBR_EMBEDCREATOR_SET_EMBED_STRING(variable, value) SBR_EMBEDCREATOR_SET_STRING(embed, variable, value)
    
#define SMB_EMBEDCREATOR_CREATE_MEDIA_SETTER_FUNCTION(name) \
SBR_EMBEDCREATOR_CREATE_MEDIA_SETTER(name) {                \
    SBR_EMBEDCREATOR_SET_EMBED_STRING(image.url, url);      \
    SBR_EMBEDCREATOR_SET_EMBED_STRING(image.proxyUrl, proxyUrl); \
    embed->image.height = height;                           \
    embed->image.width = width;                             \
    return embed;                                           \
}

SBR_EmbedCreator_Embed* SBR_EmbedCreator_Create(void) {
    SBR_EmbedCreator_Embed* embed = calloc(1, sizeof(SBR_EmbedCreator_Embed));

    BA_ASSERT(embed != NULL, "Failed to allocate memory for embed creator\n");
    BA_DynamicArray_Create(&embed->fields, 5);
    return embed;
}

SBR_EMBEDCREATOR_CREATE_SETTER(Title, const char* title) {
    SBR_EMBEDCREATOR_SET_EMBED_STRING(title, title);
    return embed;
}

SBR_EMBEDCREATOR_CREATE_SETTER(Description, const char* description) {
    SBR_EMBEDCREATOR_SET_EMBED_STRING(description, description);
    return embed;
}

SBR_EMBEDCREATOR_CREATE_SETTER(Footer, const char* text, const char* iconUrl, const char* proxyIconUrl) {
    SBR_EMBEDCREATOR_SET_EMBED_STRING(footer.text, text);
    SBR_EMBEDCREATOR_SET_EMBED_STRING(footer.iconUrl, iconUrl);
    SBR_EMBEDCREATOR_SET_EMBED_STRING(footer.proxyIconUrl, proxyIconUrl);
    return embed;
}

SMB_EMBEDCREATOR_CREATE_MEDIA_SETTER_FUNCTION(Image)
SMB_EMBEDCREATOR_CREATE_MEDIA_SETTER_FUNCTION(Thumbnail)
SMB_EMBEDCREATOR_CREATE_MEDIA_SETTER_FUNCTION(Video)
SBR_EMBEDCREATOR_CREATE_SETTER(Provider, const char* name, const char* url) {
    SBR_EMBEDCREATOR_SET_EMBED_STRING(provider.name, name);
    SBR_EMBEDCREATOR_SET_EMBED_STRING(provider.url, url);
    return embed;
}

SBR_EMBEDCREATOR_CREATE_SETTER(Author, SBR_DiscordUser* user) {
    SBR_EMBEDCREATOR_SET_EMBED_STRING(author.name, user->username);
    // TODO: URLs
    return embed;
}

SBR_EmbedCreator_Embed* SBR_EmbedCreator_AddField(SBR_EmbedCreator_Embed* embed, const char* name, const char* value, BA_Boolean inlined) {
    // TODO: Limits
    
    SBR_EmbedCreator_Field* field = calloc(1, sizeof(SBR_EmbedCreator_Field));
    
    BA_ASSERT(field != NULL, "Failed to allocate memory for embed field\n");
    SBR_EMBEDCREATOR_SET_STRING(field, name, name);
    SBR_EMBEDCREATOR_SET_STRING(field, value, value);

    field->inlined = inlined;

    BA_DynamicArray_AddElementToLast(&embed->fields, field);
    return embed;
}

#define SBR_EMBEDCREATOR_ADD_EMBED_FIELD(type, name) json_object_object_add(object, #name, json_object_new_ ## type(embed->name))

#define SBR_EMBEDCREATOR_ADD_EMBED_FIELD_NULL_CHECK(type, name) \
if (embed->name != NULL) \
    SBR_EMBEDCREATOR_ADD_EMBED_FIELD(type, name)

json_object* SBR_EmbedCreator_Build(SBR_EmbedCreator_Embed* embed) {
    // TODO: Limits

    json_object* object = json_object_new_object();
    json_object* fieldsArray = json_object_new_array();

    if (object == NULL || fieldsArray == NULL) {
        BA_LOGGER_ERROR("Failed to create embed json\n");
        return NULL;
    }

    SBR_EMBEDCREATOR_ADD_EMBED_FIELD_NULL_CHECK(string, title);
    json_object_object_add(object, "type", json_object_new_string("rich"));
    SBR_EMBEDCREATOR_ADD_EMBED_FIELD_NULL_CHECK(string, description);
    SBR_EMBEDCREATOR_ADD_EMBED_FIELD(int, color);
    json_object_object_add(object, "fields", fieldsArray);

    for (int i = 0; i < embed->fields.used; i++) {
        json_object* fieldData = json_object_new_object();
        SBR_EmbedCreator_Field* field = BA_DYNAMICARRAY_GET_ELEMENT(SBR_EmbedCreator_Field, embed->fields, i);

        json_object_object_add(fieldData, "name", json_object_new_string(field->name));
        json_object_object_add(fieldData, "value", json_object_new_string(field->value));
        json_object_object_add(fieldData, "inline", json_object_new_boolean(field->inlined));
        json_object_array_add(fieldsArray, fieldData);
    }

    return object;
}

#define SBR_EMBEDCREATOR_EASY_FREE(variable) \
if (embed->variable != NULL) {               \
    free(embed->variable);                   \
    embed->variable = NULL;                  \
} (void) NULL

#define SBR_EMBEDCREATOR_EASY_FREE_MEDIA(media) \
SBR_EMBEDCREATOR_EASY_FREE(media.url);          \
SBR_EMBEDCREATOR_EASY_FREE(media.proxyUrl)

void SBR_EmbedCreator_Free(SBR_EmbedCreator_Embed* embed) {
    SBR_EMBEDCREATOR_EASY_FREE(title);
    SBR_EMBEDCREATOR_EASY_FREE(description);
    SBR_EMBEDCREATOR_EASY_FREE(footer.text);
    SBR_EMBEDCREATOR_EASY_FREE(footer.iconUrl);
    SBR_EMBEDCREATOR_EASY_FREE(footer.proxyIconUrl);
    SBR_EMBEDCREATOR_EASY_FREE_MEDIA(image);
    SBR_EMBEDCREATOR_EASY_FREE_MEDIA(thumbnail);
    SBR_EMBEDCREATOR_EASY_FREE_MEDIA(video);
    SBR_EMBEDCREATOR_EASY_FREE(provider.name);
    SBR_EMBEDCREATOR_EASY_FREE(provider.url);
    SBR_EMBEDCREATOR_EASY_FREE(author.name);
    SBR_EMBEDCREATOR_EASY_FREE(author.url);
    SBR_EMBEDCREATOR_EASY_FREE(author.iconUrl);
    SBR_EMBEDCREATOR_EASY_FREE(author.proxyIconUrl);

    if (embed->fields.internalArray != NULL) {
        for (int i = 0; i < embed->fields.used; i++) {
            SBR_EmbedCreator_Field* field = BA_DYNAMICARRAY_GET_ELEMENT(SBR_EmbedCreator_Field, embed->fields, i);

            free(field->name);
            free(field->value);
            free(field);
        }
    }

    SBR_EMBEDCREATOR_EASY_FREE(fields.internalArray);

    embed->characterCount = 0;
}

// Purpose: Discord locale
// Created on: 4/27/24 @ 11:38 AM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <BaconAPI/Internal/Boolean.h>

typedef enum {
    SBR_DISCORD_LOCALE_INDONESIAN,
    SBR_DISCORD_LOCALE_DANISH,
    SBR_DISCORD_LOCALE_GERMAN,
    SBR_DISCORD_LOCALE_BRITISH_ENGLISH,
    SBR_DISCORD_LOCALE_AMERICAN_ENGLISH,
    SBR_DISCORD_LOCALE_SPANISH,
    SBR_DISCORD_LOCALE_LATIN_AMERICAN_SPANISH,
    SBR_DISCORD_LOCALE_FRENCH,
    SBR_DISCORD_LOCALE_CROATIAN,
    SBR_DISCORD_LOCALE_ITALIAN,
    SBR_DISCORD_LOCALE_LITHUANIAN,
    SBR_DISCORD_LOCALE_HUNGARIAN,
    SBR_DISCORD_LOCALE_DUTCH,
    SBR_DISCORD_LOCALE_NORWEIGAN,
    SBR_DISCORD_LOCALE_POLISH,
    SBR_DISCORD_LOCALE_PORTUGUESE,
    SBR_DISCORD_LOCALE_ROMANIAN,
    SBR_DISCORD_LOCALE_FINNISH,
    SBR_DISCORD_LOCALE_SWEDISH,
    SBR_DISCORD_LOCALE_VIETNAMESE,
    SBR_DISCORD_LOCALE_TURKISH,
    SBR_DISCORD_LOCALE_CZECH,
    SBR_DISCORD_LOCALE_GREEK,
    SBR_DISCORD_LOCALE_BULGARIAN,
    SBR_DISCORD_LOCALE_RUSSIAN,
    SBR_DISCORD_LOCALE_UKRAINIAN,
    SBR_DISCORD_LOCALE_HINDI,
    SBR_DISCORD_LOCALE_THAI,
    SBR_DISCORD_LOCALE_CHINESE,
    SBR_DISCORD_LOCALE_JAPANENSE,
    SBR_DISCORD_LOCALE_TAIWAN,
    SBR_DISCORD_LOCALE_KOREAN,

    /**
     * Not a real code
     */
    SBR_DISCORD_LOCALE_SIZE
} SBR_DiscordLocales;

const char* SBR_DiscordLocales_ToLanguageCode(SBR_DiscordLocales locale);


/**
 * @return SBR_DISCORD_LOCALE_AMERICAN_ENGLISH if it's invalid
 */
SBR_DiscordLocales SBR_DiscordLocales_FromLanguageCode(const char* code);
BA_Boolean SBR_DiscordLocales_IsValid(SBR_DiscordLocales locale);

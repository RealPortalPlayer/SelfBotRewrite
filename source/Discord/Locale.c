// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#include <BaconAPI/Debugging/StaticAssert.h>
#include <BaconAPI/String.h>

#include "Discord/Locale.h"

static const char* sbrDiscordLocaleLookup[] = {
    "id", "da", "de",
    "en-GB", "en-US", "es-ES",
    "es-419", "fr", "hr",
    "it", "lt", "hu",
    "nl", "no", "pl",
    "pt-BR", "ro", "fi",
    "sv-SE", "vi", "tr",
    "cs", "el", "bg",
    "ru", "uk", "hi",
    "th", "zh-CN", "ja",
    "zh-TW", "ko"
};

BA_STATIC_ASSERT_LOOKUP_TABLE_CHECK(sbrDiscordLocaleLookup, SBR_DISCORD_LOCALE_SIZE);

const char* SBR_DiscordLocales_ToLanguageCode(SBR_DiscordLocales locale) {
    return SBR_DiscordLocales_IsValid(locale) ? sbrDiscordLocaleLookup[locale] : NULL;
}

SBR_DiscordLocales SBR_DiscordLocales_FromLanguageCode(const char* code) {
    for (int i = 0; i < SBR_DISCORD_LOCALE_SIZE; i++) {
        if (!BA_String_Equals(sbrDiscordLocaleLookup[i], code, BA_BOOLEAN_TRUE))
            continue;

        return i;
    }

    return SBR_DISCORD_LOCALE_AMERICAN_ENGLISH;
}

BA_Boolean SBR_DiscordLocales_IsValid(SBR_DiscordLocales locale) {
    return locale < SBR_DISCORD_LOCALE_SIZE;
}

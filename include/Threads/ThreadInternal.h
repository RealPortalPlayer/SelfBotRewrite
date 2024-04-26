// Purpose: Make it easier to create threads
// Created on: 4/26/24 @ 11:31 AM

// Copyright (c) 2024, PortalPlayer <email@portalplayer.xyz>
// Licensed under MIT <https://opensource.org/licenses/MIT>

#pragma once

#include <BaconAPI/Thread.h>
#include <BaconAPI/Debugging/Assert.h>
#include <BaconAPI/Logger.h>

#define SBR_THREADINTERNAL_HEADER(name) \
void SBR_ ## name ## Thread_Create(void); \
void SBR_ ## name ## Thread_Destroy(void)

#define SBR_THREADINTERNAL_JOIN(name) BA_Thread_Join(sbr ## name ## Thread, NULL)
#define SBR_THREADINTERNAL_KILL(name) BA_Thread_Kill(sbr ## name ## Thread)

#define SBR_THREADINTERNAL_CODE(name, stylizedName, destroyType) \
static BA_Thread sbr ## name ## Thread;             \
static volatile BA_Boolean sbr ## name ## Initialized; \
static BA_THREAD_RETURN_VALUE BA_THREAD_ATTRIBUTE SBR_ ## name ## Thread_Function(void* argument); \
void SBR_ ## name ## Thread_Create(void) {          \
    BA_ASSERT(!sbr ## name ## Initialized, "Already created " stylizedName " thread\n"); \
    sbr ## name ## Initialized = BA_BOOLEAN_TRUE;   \
    BA_LOGGER_TRACE("Creating " stylizedName " thread\n"); \
    BA_ASSERT(BA_Thread_Create(&sbr ## name ## Thread, &SBR_ ## name ## Thread_Function, NULL), "Failed to create " stylizedName " thread\n"); \
}                                                   \
void SBR_ ## name ## Thread_Destroy(void) {         \
    BA_ASSERT(sbr ## name ## Initialized, stylizedName " thread not created\n"); \
    BA_LOGGER_TRACE("Destroying " stylizedName " thread\n"); \
    sbr ## name ## Initialized = BA_BOOLEAN_FALSE;  \
    BA_ASSERT(SBR_THREADINTERNAL_ ## destroyType(name), "Failed to destroy " stylizedName " thread\n"); \
}                                                   \
static BA_THREAD_RETURN_VALUE BA_THREAD_ATTRIBUTE SBR_ ## name ## Thread_Function(void* argument)

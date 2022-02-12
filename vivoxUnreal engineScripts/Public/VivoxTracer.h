// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

/// Do NOT log anything by default, only when intentionally raised to Verbose or VeryVerbose
DECLARE_LOG_CATEGORY_EXTERN(LogShooterGameTracer, Log, All);

#if defined(_MSC_VER)
#define FUNC_NAME    TEXT(__FUNCTION__)
#elif defined(__PRETTY_FUNCTION__)
#define FUNC_NAME __PRETTY_FUNCTION__
#else
#define FUNC_NAME    __func__
#endif

#define LogVerboseFormat(Format, ...) \
    _LogVerbose(FUNC_NAME, FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define LogVeryVerboseFormat(Format, ...) \
    _LogVeryVerbose(FUNC_NAME, FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define MinorMethodPrologue() \
    _MethodPrologue(FUNC_NAME, "")
#define MajorMethodPrologue(Format, ...) \
    _MethodPrologue(FUNC_NAME, FString::Printf(TEXT(Format), ##__VA_ARGS__))

class Tracer {
public:
    static void _LogVerbose(const FString Name, const FString Message);
    static void _LogVeryVerbose(const FString Name, const FString Message);
    static void _MethodPrologue(const FString Name, const FString Message = "");

private:
    /// Disallow creating an instance of this object
    Tracer() {}
};

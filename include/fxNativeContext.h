// https://github.com/citizenfx/fivem/blob/master/code/components/citizen-scripting-core/include/fxNativeContext.h

#pragma once

struct fxNativeContext
{
    uintptr_t arguments[32];
    int numArguments;
    int numResults;
    uint64_t nativeIdentifier;
};

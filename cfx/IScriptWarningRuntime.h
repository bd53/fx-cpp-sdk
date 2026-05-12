#pragma once

#include "core.h"

FX_DEFINE_GUID(IID_IScriptWarningRuntime, 0xD72BE411, 0x5152, 0x4474, 0x91, 0x7C, 0x53, 0x61, 0xAC, 0x05, 0x11, 0x81);

class IScriptWarningRuntime : public fxIBase
{
public:
    NS_DECLARE_STATIC_IID_ACCESSOR(IID_IScriptWarningRuntime)
    NS_IMETHOD EmitWarning(char* channel, char* message) = 0;
};

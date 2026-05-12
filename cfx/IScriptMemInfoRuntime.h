#pragma once

#include "core.h"

FX_DEFINE_GUID(IID_IScriptMemInfoRuntime, 0xD98A35CF, 0xD6EE, 0x4B51, 0xA1, 0xC3, 0x99, 0xB7, 0x0F, 0x4E, 0xC1, 0xE6);

class IScriptMemInfoRuntime : public fxIBase
{
public:
    NS_DECLARE_STATIC_IID_ACCESSOR(IID_IScriptMemInfoRuntime)
    NS_IMETHOD RequestMemoryUsage() = 0;
    NS_IMETHOD GetMemoryUsage(int64_t* memUsage) = 0;
};

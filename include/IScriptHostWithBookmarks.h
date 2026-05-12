#pragma once

#include "core.h"

class IScriptTickRuntimeWithBookmarks;

FX_DEFINE_GUID(IID_IScriptHostWithBookmarks, 0x2A7E092D, 0x6CE9, 0x4B9D, 0xAC, 0x4F, 0x8D, 0xA8, 0x18, 0xBD, 0x0D, 0xA4);

class IScriptHostWithBookmarks : public fxIBase
{
public:
    NS_DECLARE_STATIC_IID_ACCESSOR(IID_IScriptHostWithBookmarks)
    NS_IMETHOD ScheduleBookmark(IScriptTickRuntimeWithBookmarks* runtime, uint64_t bookmark, int64_t deadline) = 0;
    NS_IMETHOD RemoveBookmarks(IScriptTickRuntimeWithBookmarks* runtime) = 0;
    NS_IMETHOD CreateBookmarks(IScriptTickRuntimeWithBookmarks* runtime) = 0;
};

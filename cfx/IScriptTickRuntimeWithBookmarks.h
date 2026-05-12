#pragma once

#include "core.h"

FX_DEFINE_GUID(IID_IScriptTickRuntimeWithBookmarks, 0x195FB3BD, 0x1A64, 0x4EBD, 0xA1, 0xCC, 0x80, 0x52, 0xED, 0x7E, 0xB0, 0xBD);

class IScriptTickRuntimeWithBookmarks : public fxIBase
{
public:
    NS_DECLARE_STATIC_IID_ACCESSOR(IID_IScriptTickRuntimeWithBookmarks)
    NS_IMETHOD TickBookmarks(uint64_t* bookmarks, int32_t numBookmarks) = 0;
};

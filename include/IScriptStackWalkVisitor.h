#pragma once

#include "core.h"

FX_DEFINE_GUID(IID_IScriptStackWalkVisitor, 0x182CAAF3, 0xE33D, 0x474B, 0xA6, 0xAF, 0x33, 0xD5, 0x9F, 0xF0, 0xE9, 0xED);

class IScriptStackWalkVisitor : public fxIBase
{
public:
    NS_DECLARE_STATIC_IID_ACCESSOR(IID_IScriptStackWalkVisitor)
    NS_IMETHOD SubmitStackFrame(char* frameBlob, uint32_t frameBlobSize) = 0;
};

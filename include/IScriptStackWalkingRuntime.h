#pragma once

#include "core.h"
#include "IScriptStackWalkVisitor.h"

FX_DEFINE_GUID(IID_IScriptStackWalkingRuntime, 0x567D2FDA, 0x610C, 0x4FA0, 0xAE, 0x3E, 0x4F, 0x70, 0x0A, 0xE5, 0xCE, 0x56);

class IScriptStackWalkingRuntime : public fxIBase
{
public:
    NS_DECLARE_STATIC_IID_ACCESSOR(IID_IScriptStackWalkingRuntime)
    NS_IMETHOD WalkStack(char* boundaryStart, uint32_t boundaryStartLength, char* boundaryEnd, uint32_t boundaryEndLength, IScriptStackWalkVisitor* visitor) = 0;
};

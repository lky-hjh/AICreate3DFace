#pragma once

#include "Modules/ModuleManager.h"

class FFaceToonPlugin : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
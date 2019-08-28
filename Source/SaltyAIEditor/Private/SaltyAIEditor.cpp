// Copyright 2019 - Now Salty Panda Studios. All Rights reserved.

#include "SaltyAIEditor.h"
#include <PropertyEditorModule.h>
#include "FunctionContextCustomization.h"
#include "BlackboardKeyChangerCustomization.h"

#define LOCTEXT_NAMESPACE "FSaltyAIEditorModule"

void FSaltyAIEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	//Custom properties
	PropertyModule.RegisterCustomPropertyTypeLayout("FunctionContext", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FFunctionContextCustomization::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout("BlackboardKeyChanger", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FBlackboardKeyChangerCustomization::MakeInstance));
}

void FSaltyAIEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSaltyAIEditorModule, SaltyAIEditor)
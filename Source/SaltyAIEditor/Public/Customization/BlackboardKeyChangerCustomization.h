// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Editor/PropertyEditor/Public/IPropertyTypeCustomization.h"
#include "Editor/PropertyEditor/Public/IDetailCustomization.h"

class UBTT_SetBlackboardProperty;

class FBlackboardKeyChangerCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	void OnBlackboardKeyChange();

	void UpdatePropertyVisibilty();

	TSharedPtr<SWidget> StringWidget;
	TSharedPtr<SWidget> IntWidget;
	TSharedPtr<SWidget> FloatWidget;
	TSharedPtr<SWidget> BoolWidget;
	TSharedPtr<SWidget> NameWidget;
	TSharedPtr<SWidget> EnumWidget;
	TSharedPtr<SWidget> ClassWidget;

	TSharedPtr<IPropertyHandle> StructPropHandle;
};
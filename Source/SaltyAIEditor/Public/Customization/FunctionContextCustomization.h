// Copyright 2019 - Now Salty Panda Studios. All Rights reserved.

#pragma once

#include "Editor/PropertyEditor/Public/IPropertyTypeCustomization.h"
#include "Editor/PropertyEditor/Public/IDetailCustomization.h"
#include "InputCoreTypes.h"
#include "SComboBox.h"

class FFunctionContextCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	typedef TSharedPtr<FString> FComboItemType;

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	void OnClassChange();
	void OnSelectionChanged(FComboItemType NewValue, ESelectInfo::Type);
	TSharedRef<SWidget> MakeWidgetForOption(FComboItemType InOption);

	void UpdateActiveSelectedClass();
	FText GetActiveFunction() const;

	TArray<FComboItemType> Functions;
	FString FormattedClass;

	TSharedPtr<SComboBox<FComboItemType>> ComboBox;
	TSharedPtr<IPropertyHandle> ClassProperty;
	TSharedPtr<IPropertyHandle> FunctionProperty;
};
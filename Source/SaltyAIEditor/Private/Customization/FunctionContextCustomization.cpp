// Copyright 2019 - Now Salty Panda Studios. All Rights reserved.

#include "FunctionContextCustomization.h"
#include <PropertyHandle.h>
#include <SubclassOf.h>
#include "Editor/PropertyEditor/Public/DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "FFunctionContextCustomization"

TSharedRef<IPropertyTypeCustomization> FFunctionContextCustomization::MakeInstance()
{
	return MakeShareable(new FFunctionContextCustomization());
}

void FFunctionContextCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	uint32 NumChildren;
	StructPropertyHandle->GetNumChildren(NumChildren);

	ClassProperty = StructPropertyHandle->GetChildHandle("ContextClass");
	FunctionProperty = StructPropertyHandle->GetChildHandle("FunctionToExecute");

	FSimpleDelegate OnChange;
	OnChange.BindRaw(this, &FFunctionContextCustomization::OnClassChange);
	ClassProperty->SetOnPropertyValueChanged(OnChange);

	OnClassChange();

	HeaderRow.NameContent()
	[
		StructPropertyHandle->CreatePropertyNameWidget(FText::FromString("Function Context"))
	]
	.ValueContent()
	.MinDesiredWidth(500)
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		[
			ClassProperty->CreatePropertyValueWidget()
		]
		+ SVerticalBox::Slot()
		[
			SAssignNew(ComboBox, SComboBox<FComboItemType>)
			.OptionsSource(&Functions)
			.OnSelectionChanged(this, &FFunctionContextCustomization::OnSelectionChanged)
			.OnGenerateWidget(this, &FFunctionContextCustomization::MakeWidgetForOption)
			[
				SNew(STextBlock)
				.Text(this, &FFunctionContextCustomization::GetActiveFunction)
			]
		]
	];

	UpdateActiveSelectedClass();
}

void FFunctionContextCustomization::OnSelectionChanged(FComboItemType NewValue, ESelectInfo::Type)
{
	if (!NewValue.IsValid())
	{
		FunctionProperty->SetValue(FString(""));
		return;
	}

	FunctionProperty->SetValue(*NewValue);
	ComboBox->SetSelectedItem(NewValue);
}

TSharedRef<SWidget> FFunctionContextCustomization::MakeWidgetForOption(FComboItemType InOption)
{
	return SNew(STextBlock).Text(FText::FromString(*InOption));
}

void FFunctionContextCustomization::UpdateActiveSelectedClass()
{
	if (!ComboBox.IsValid())
	{
		return;
	}

	ComboBox->RefreshOptions();

	FString FuncName = "";
	FunctionProperty->GetValue(FuncName);

	for (int i = 0; i < Functions.Num(); i++)
	{
		if (*Functions[i] == FuncName)
		{
			FunctionProperty->SetValue(*FuncName);
			return;
		}
	}

	//If we didn't find the same we can safely set the function to first available function
	if (Functions.Num() >= 1)
	{
		FunctionProperty->SetValue(*Functions[0]);
		return;
	}
}

FText FFunctionContextCustomization::GetActiveFunction() const
{
	FString FuncName = "";
	FunctionProperty->GetValue(FuncName);

	return FText::FromString(FuncName);
}

void FFunctionContextCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{

}

void FFunctionContextCustomization::OnClassChange()
{
	FormattedClass = "";

	if (ClassProperty.IsValid())
	{
		ClassProperty->GetValueAsFormattedString(FormattedClass);
	}

	Functions.Empty();

	UClass* ContextClass = FindObject<UClass>(ANY_PACKAGE, *FormattedClass);

	if (!ContextClass)
	{
		if (ComboBox)
		{
			ComboBox->RefreshOptions();
		}

		FunctionProperty->SetValue(FString(""));

		return;
	}

	//Add empty
	Functions.Add(MakeShareable(new FString("")));

	for (TFieldIterator<UFunction> FuncIt(ContextClass); FuncIt; ++FuncIt)
	{
		UFunction* Function = *FuncIt;

		//Only blueprint callable
		if (!Function->HasAnyFunctionFlags(FUNC_BlueprintCallable))
		{
			continue;
		}

		//Ignore return val function
		if (Function->GetReturnProperty())
		{
			continue;
		}

		//Ignore native functions
		if (Function->HasAnyFunctionFlags(FUNC_Native))
		{
			continue;
		}

		//If function has params ignore the function
		if (Function->NumParms > 0)
		{
			continue;
		}

		Functions.Add(MakeShareable(new FString(Function->GetName())));
	}

	UpdateActiveSelectedClass();
}

#undef LOCTEXT_NAMESPACE
// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BlackboardKeyChangerCustomization.h"
#include <PropertyHandle.h>
#include <SubclassOf.h>
#include "Editor/PropertyEditor/Public/DetailWidgetRow.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Name.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Rotator.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Class.h"
#include "Tasks/BTT_SetBlackboardProperty.h"



#define LOCTEXT_NAMESPACE "FBlackboardKeyChangerCustomization"

TSharedRef<IPropertyTypeCustomization> FBlackboardKeyChangerCustomization::MakeInstance()
{
	return MakeShareable(new FBlackboardKeyChangerCustomization());
}

void FBlackboardKeyChangerCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructPropHandle = StructPropertyHandle;

	TSharedPtr<IPropertyHandle> StringProperty = StructPropertyHandle->GetChildHandle("StringValue");
	TSharedPtr<IPropertyHandle> IntProperty = StructPropertyHandle->GetChildHandle("IntValue");
	TSharedPtr<IPropertyHandle> FloatProperty = StructPropertyHandle->GetChildHandle("FloatValue");
	TSharedPtr<IPropertyHandle> BoolProperty = StructPropertyHandle->GetChildHandle("BoolValue");
	TSharedPtr<IPropertyHandle> NameProperty = StructPropertyHandle->GetChildHandle("NameValue");
	TSharedPtr<IPropertyHandle> EnumProperty = StructPropertyHandle->GetChildHandle("EnumValue");
	TSharedPtr<IPropertyHandle> ClassProperty = StructPropertyHandle->GetChildHandle("ClassValue");

	TArray<UObject*> Outers;
	StructPropertyHandle->GetOuterObjects(Outers);
	for (int i = 0; i < Outers.Num(); i++)
	{
		if (UBTT_SetBlackboardProperty* Task = Cast<UBTT_SetBlackboardProperty>(Outers[i]))
		{
			Task->OnChanged.BindRaw(this, &FBlackboardKeyChangerCustomization::OnBlackboardKeyChange);
			break;
		}
	}

	StringWidget = StringProperty->CreatePropertyValueWidget();
	IntWidget = IntProperty->CreatePropertyValueWidget();
	FloatWidget = FloatProperty->CreatePropertyValueWidget();
	BoolWidget = BoolProperty->CreatePropertyValueWidget();
	NameWidget = NameProperty->CreatePropertyValueWidget();
	EnumWidget = EnumProperty->CreatePropertyValueWidget();
	ClassWidget = ClassProperty->CreatePropertyValueWidget();

	HeaderRow.NameContent()
	[
		StructPropertyHandle->CreatePropertyNameWidget(FText::FromString("Blackboard Key Changer"))
	]
	.ValueContent()
	.MinDesiredWidth(500)
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		[
			StringWidget.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		[
			IntWidget.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		[
			FloatWidget.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		[
			BoolWidget.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		[
			NameWidget.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		[
			EnumWidget.ToSharedRef()
		]
		+ SVerticalBox::Slot()
		[
			ClassWidget.ToSharedRef()
		]
	];

	UpdatePropertyVisibilty();
}

void FBlackboardKeyChangerCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{

}

void FBlackboardKeyChangerCustomization::OnBlackboardKeyChange()
{
	UpdatePropertyVisibilty();
}

void FBlackboardKeyChangerCustomization::UpdatePropertyVisibilty()
{
	UBTT_SetBlackboardProperty* Task = nullptr;

	TArray<UObject*> Outers;
	StructPropHandle->GetOuterObjects(Outers);
	for (int i = 0; i < Outers.Num(); i++)
	{
		if (UBTT_SetBlackboardProperty* testTask = Cast<UBTT_SetBlackboardProperty>(Outers[i]))
		{
			Task = testTask;
			break;
		}
	}

	if (!Task)
	{
		return;
	}

	TSharedPtr<SWidget> VisibleWidget = nullptr;

	if (Task->Key.SelectedKeyType)
	{
		UObject* ClassObject = nullptr;

		FString FormattedClassString = "";

		ClassObject = Task->Key.SelectedKeyType->GetDefaultObject();

		if (UBlackboardKeyType_String* StringType = Cast<UBlackboardKeyType_String>(ClassObject))
		{
			VisibleWidget = StringWidget;
		}

		else if (UBlackboardKeyType_Int* IntType = Cast<UBlackboardKeyType_Int>(ClassObject))
		{
			VisibleWidget = IntWidget;
		}

		else if (UBlackboardKeyType_Float* FloatType = Cast<UBlackboardKeyType_Float>(ClassObject))
		{
			VisibleWidget = FloatWidget;
		}

		else if (UBlackboardKeyType_Bool* BoolType = Cast<UBlackboardKeyType_Bool>(ClassObject))
		{
			VisibleWidget = BoolWidget;
		}

		else if (UBlackboardKeyType_Name* NameType = Cast<UBlackboardKeyType_Name>(ClassObject))
		{
			VisibleWidget = NameWidget;
		}

		else if (UBlackboardKeyType_Enum* EnumType = Cast<UBlackboardKeyType_Enum>(ClassObject))
		{
			VisibleWidget = EnumWidget;
		}

		else if (UBlackboardKeyType_Class* ClassType = Cast<UBlackboardKeyType_Class>(ClassObject))
		{
			VisibleWidget = ClassWidget;
		}
	}

	StringWidget->SetVisibility(StringWidget == VisibleWidget ? EVisibility::SelfHitTestInvisible : EVisibility::Collapsed);
	IntWidget->SetVisibility(IntWidget == VisibleWidget ? EVisibility::SelfHitTestInvisible : EVisibility::Collapsed);
	FloatWidget->SetVisibility(FloatWidget == VisibleWidget ? EVisibility::SelfHitTestInvisible : EVisibility::Collapsed);
	BoolWidget->SetVisibility(BoolWidget == VisibleWidget ? EVisibility::SelfHitTestInvisible : EVisibility::Collapsed);
	NameWidget->SetVisibility(NameWidget == VisibleWidget ? EVisibility::SelfHitTestInvisible : EVisibility::Collapsed);
	EnumWidget->SetVisibility(EnumWidget == VisibleWidget ? EVisibility::SelfHitTestInvisible : EVisibility::Collapsed);
	ClassWidget->SetVisibility(ClassWidget == VisibleWidget ? EVisibility::SelfHitTestInvisible : EVisibility::Collapsed);
}

#undef LOCTEXT_NAMESPACE
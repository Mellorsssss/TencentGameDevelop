// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HOMEWORK3/Public/TargetGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTargetGameModeBase() {}
// Cross Module References
	HOMEWORK3_API UClass* Z_Construct_UClass_ATargetGameModeBase_NoRegister();
	HOMEWORK3_API UClass* Z_Construct_UClass_ATargetGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_HOMEWORK3();
// End Cross Module References
	void ATargetGameModeBase::StaticRegisterNativesATargetGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_ATargetGameModeBase_NoRegister()
	{
		return ATargetGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ATargetGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATargetGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_HOMEWORK3,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATargetGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "TargetGameModeBase.h" },
		{ "ModuleRelativePath", "Public/TargetGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATargetGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATargetGameModeBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ATargetGameModeBase_Statics::ClassParams = {
		&ATargetGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ATargetGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATargetGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATargetGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ATargetGameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ATargetGameModeBase, 3426032760);
	template<> HOMEWORK3_API UClass* StaticClass<ATargetGameModeBase>()
	{
		return ATargetGameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ATargetGameModeBase(Z_Construct_UClass_ATargetGameModeBase, &ATargetGameModeBase::StaticClass, TEXT("/Script/HOMEWORK3"), TEXT("ATargetGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATargetGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif

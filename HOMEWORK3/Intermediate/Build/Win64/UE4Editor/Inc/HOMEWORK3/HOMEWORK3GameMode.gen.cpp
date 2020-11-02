// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HOMEWORK3/HOMEWORK3GameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHOMEWORK3GameMode() {}
// Cross Module References
	HOMEWORK3_API UClass* Z_Construct_UClass_AHOMEWORK3GameMode_NoRegister();
	HOMEWORK3_API UClass* Z_Construct_UClass_AHOMEWORK3GameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_HOMEWORK3();
// End Cross Module References
	void AHOMEWORK3GameMode::StaticRegisterNativesAHOMEWORK3GameMode()
	{
	}
	UClass* Z_Construct_UClass_AHOMEWORK3GameMode_NoRegister()
	{
		return AHOMEWORK3GameMode::StaticClass();
	}
	struct Z_Construct_UClass_AHOMEWORK3GameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AHOMEWORK3GameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_HOMEWORK3,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AHOMEWORK3GameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "HOMEWORK3GameMode.h" },
		{ "ModuleRelativePath", "HOMEWORK3GameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AHOMEWORK3GameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AHOMEWORK3GameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AHOMEWORK3GameMode_Statics::ClassParams = {
		&AHOMEWORK3GameMode::StaticClass,
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
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_AHOMEWORK3GameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AHOMEWORK3GameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AHOMEWORK3GameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AHOMEWORK3GameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AHOMEWORK3GameMode, 2789261955);
	template<> HOMEWORK3_API UClass* StaticClass<AHOMEWORK3GameMode>()
	{
		return AHOMEWORK3GameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AHOMEWORK3GameMode(Z_Construct_UClass_AHOMEWORK3GameMode, &AHOMEWORK3GameMode::StaticClass, TEXT("/Script/HOMEWORK3"), TEXT("AHOMEWORK3GameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AHOMEWORK3GameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif

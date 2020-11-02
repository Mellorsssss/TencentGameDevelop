// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HOMEWORK3/Public/TPSPlayerController.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTPSPlayerController() {}
// Cross Module References
	HOMEWORK3_API UClass* Z_Construct_UClass_ATPSPlayerController_NoRegister();
	HOMEWORK3_API UClass* Z_Construct_UClass_ATPSPlayerController();
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	UPackage* Z_Construct_UPackage__Script_HOMEWORK3();
// End Cross Module References
	void ATPSPlayerController::StaticRegisterNativesATPSPlayerController()
	{
	}
	UClass* Z_Construct_UClass_ATPSPlayerController_NoRegister()
	{
		return ATPSPlayerController::StaticClass();
	}
	struct Z_Construct_UClass_ATPSPlayerController_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATPSPlayerController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_HOMEWORK3,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATPSPlayerController_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "TPSPlayerController.h" },
		{ "ModuleRelativePath", "Public/TPSPlayerController.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATPSPlayerController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATPSPlayerController>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ATPSPlayerController_Statics::ClassParams = {
		&ATPSPlayerController::StaticClass,
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
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_ATPSPlayerController_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATPSPlayerController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATPSPlayerController()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ATPSPlayerController_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ATPSPlayerController, 179630355);
	template<> HOMEWORK3_API UClass* StaticClass<ATPSPlayerController>()
	{
		return ATPSPlayerController::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ATPSPlayerController(Z_Construct_UClass_ATPSPlayerController, &ATPSPlayerController::StaticClass, TEXT("/Script/HOMEWORK3"), TEXT("ATPSPlayerController"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATPSPlayerController);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif

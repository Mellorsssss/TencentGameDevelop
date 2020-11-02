// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HOMEWORK3/Public/TPSPlayerState.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTPSPlayerState() {}
// Cross Module References
	HOMEWORK3_API UClass* Z_Construct_UClass_ATPSPlayerState_NoRegister();
	HOMEWORK3_API UClass* Z_Construct_UClass_ATPSPlayerState();
	ENGINE_API UClass* Z_Construct_UClass_APlayerState();
	UPackage* Z_Construct_UPackage__Script_HOMEWORK3();
// End Cross Module References
	DEFINE_FUNCTION(ATPSPlayerState::execAddScore)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_ScoreDelta);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->AddScore(Z_Param_ScoreDelta);
		P_NATIVE_END;
	}
	void ATPSPlayerState::StaticRegisterNativesATPSPlayerState()
	{
		UClass* Class = ATPSPlayerState::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AddScore", &ATPSPlayerState::execAddScore },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ATPSPlayerState_AddScore_Statics
	{
		struct TPSPlayerState_eventAddScore_Parms
		{
			float ScoreDelta;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ScoreDelta;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ATPSPlayerState_AddScore_Statics::NewProp_ScoreDelta = { "ScoreDelta", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(TPSPlayerState_eventAddScore_Parms, ScoreDelta), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATPSPlayerState_AddScore_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATPSPlayerState_AddScore_Statics::NewProp_ScoreDelta,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATPSPlayerState_AddScore_Statics::Function_MetaDataParams[] = {
		{ "Category", "PlayerState" },
		{ "ModuleRelativePath", "Public/TPSPlayerState.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATPSPlayerState_AddScore_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATPSPlayerState, nullptr, "AddScore", nullptr, nullptr, sizeof(TPSPlayerState_eventAddScore_Parms), Z_Construct_UFunction_ATPSPlayerState_AddScore_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATPSPlayerState_AddScore_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATPSPlayerState_AddScore_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATPSPlayerState_AddScore_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATPSPlayerState_AddScore()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATPSPlayerState_AddScore_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ATPSPlayerState_NoRegister()
	{
		return ATPSPlayerState::StaticClass();
	}
	struct Z_Construct_UClass_ATPSPlayerState_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATPSPlayerState_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerState,
		(UObject* (*)())Z_Construct_UPackage__Script_HOMEWORK3,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ATPSPlayerState_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ATPSPlayerState_AddScore, "AddScore" }, // 3232671906
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATPSPlayerState_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "TPSPlayerState.h" },
		{ "ModuleRelativePath", "Public/TPSPlayerState.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATPSPlayerState_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATPSPlayerState>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ATPSPlayerState_Statics::ClassParams = {
		&ATPSPlayerState::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_ATPSPlayerState_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATPSPlayerState_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATPSPlayerState()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ATPSPlayerState_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ATPSPlayerState, 3277617569);
	template<> HOMEWORK3_API UClass* StaticClass<ATPSPlayerState>()
	{
		return ATPSPlayerState::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ATPSPlayerState(Z_Construct_UClass_ATPSPlayerState, &ATPSPlayerState::StaticClass, TEXT("/Script/HOMEWORK3"), TEXT("ATPSPlayerState"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATPSPlayerState);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif

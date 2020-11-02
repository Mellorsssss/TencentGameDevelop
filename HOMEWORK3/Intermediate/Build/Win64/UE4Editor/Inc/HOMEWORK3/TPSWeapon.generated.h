// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef HOMEWORK3_TPSWeapon_generated_h
#error "TPSWeapon.generated.h already included, missing '#pragma once' in TPSWeapon.h"
#endif
#define HOMEWORK3_TPSWeapon_generated_h

#define HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_SPARSE_DATA
#define HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execFire);


#define HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execFire);


#define HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATPSWeapon(); \
	friend struct Z_Construct_UClass_ATPSWeapon_Statics; \
public: \
	DECLARE_CLASS(ATPSWeapon, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/HOMEWORK3"), NO_API) \
	DECLARE_SERIALIZER(ATPSWeapon)


#define HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_INCLASS \
private: \
	static void StaticRegisterNativesATPSWeapon(); \
	friend struct Z_Construct_UClass_ATPSWeapon_Statics; \
public: \
	DECLARE_CLASS(ATPSWeapon, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/HOMEWORK3"), NO_API) \
	DECLARE_SERIALIZER(ATPSWeapon)


#define HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ATPSWeapon(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATPSWeapon) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATPSWeapon); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATPSWeapon); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATPSWeapon(ATPSWeapon&&); \
	NO_API ATPSWeapon(const ATPSWeapon&); \
public:


#define HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATPSWeapon(ATPSWeapon&&); \
	NO_API ATPSWeapon(const ATPSWeapon&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATPSWeapon); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATPSWeapon); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ATPSWeapon)


#define HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__MeshComp() { return STRUCT_OFFSET(ATPSWeapon, MeshComp); } \
	FORCEINLINE static uint32 __PPO__ShootRange() { return STRUCT_OFFSET(ATPSWeapon, ShootRange); } \
	FORCEINLINE static uint32 __PPO__DamageType() { return STRUCT_OFFSET(ATPSWeapon, DamageType); }


#define HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_10_PROLOG
#define HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_PRIVATE_PROPERTY_OFFSET \
	HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_SPARSE_DATA \
	HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_RPC_WRAPPERS \
	HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_INCLASS \
	HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_PRIVATE_PROPERTY_OFFSET \
	HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_SPARSE_DATA \
	HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_INCLASS_NO_PURE_DECLS \
	HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> HOMEWORK3_API UClass* StaticClass<class ATPSWeapon>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID HOMEWORK3_Source_HOMEWORK3_Public_TPSWeapon_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS

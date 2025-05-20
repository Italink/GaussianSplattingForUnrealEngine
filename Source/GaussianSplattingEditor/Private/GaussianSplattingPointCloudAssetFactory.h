#pragma once

#include "Factories/Factory.h"
#include "AssetTypeActions_Base.h"
#include "AssetDefinitionDefault.h"
#include "ActorFactories/ActorFactory.h"
#include "GaussianSplattingPointCloudAssetFactory.generated.h"

UCLASS(hidecategories = Object)
class UGaussianSplattingPointCloudAssetFactory: public UFactory{
	GENERATED_UCLASS_BODY()
public:
	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
};

UCLASS()
class UAssetDefinition_GaussianSplattingPointCloud: public UAssetDefinitionDefault
{
	GENERATED_BODY()
public:
	virtual FText GetAssetDisplayName() const override final;
	TSoftClassPtr<UObject> GetAssetClass() const override final;
	virtual FLinearColor GetAssetColor() const override final;
	TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override final;
	EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override final;
};

UCLASS(MinimalAPI)
class UActorFactory_GaussianSplattingPointCloud : public UActorFactory
{
	GENERATED_UCLASS_BODY()

	//~ Begin UActorFactory Interface
	virtual bool CanCreateActorFrom( const FAssetData& AssetData, FText& OutErrorMsg ) override;
	virtual void PostSpawnActor( UObject* Asset, AActor* NewActor) override;
	virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;
	virtual FQuat AlignObjectToSurfaceNormal(const FVector& InSurfaceNormal, const FQuat& ActorRotation) const override;
	//~ End UActorFactory Interface
};


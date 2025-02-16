


#include "CharacterLogic/OnaCharacter.h"

#include "Structs/OnaMovementSettings_State.h"

// Sets default values
AOnaCharacter::AOnaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOnaCharacter::BeginPlay()
{
	Super::BeginPlay();
	USkeletalMeshComponent* mesh = GetMesh();
	/**
	 * Make sure the mesh and animbp update after the CharacterBP to ensure it gets the most recent values.
	 */
	mesh->AddTickPrerequisiteActor(this);
	
	/**
	 * Set Reference to the Main Anim Instance.
	 */
	if (IsValid(mesh->GetAnimInstance()))
	{
		MainAnimInstance = mesh->GetAnimInstance();
	}

	SetMovementModel();
}

// Called every frame
void AOnaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOnaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AOnaCharacter::SetMovementModel()
{
	FName rowName = MovementModel.RowName;
	const UDataTable* dataTable = MovementModel.DataTable;
	const FString ContextString = FString::Printf(TEXT("Find Row: %s"), *rowName.ToString());
	if (auto outRow = dataTable->FindRow<FOnaMovementSettings_State>(rowName, ContextString))
	{
		MovementSettingsState = *outRow;
	}
}


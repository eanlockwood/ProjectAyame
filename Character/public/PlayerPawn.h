
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

//I typically forward declare classes in the header file to avoid circular includes but if you must include header files in the .h, put them in between coreminimal and the generated.h

#include "PlayerPawn.generated.h"

//forward declares
class USkeletalMeshComponent; //a rigged mesh, component form for actors
class UCameraComponent; //A camera you can attach to actors. This is helpful not only for players but for regular actors because you can call a function that sets your "view target" which will essentially set the player view to the first camera component of an actor
class USpringArmComponent; //a "raycast" (LineTrace in unreal terms) that extends from (0,0,0) of the actor with rotation properties. Used for making things follow the player while keeping clipping in mind (clipping checks can be disabled). Many uses, best use case however is the camera 

//The way to add things to actors is through components, there are many that you will come to learn, but the basics are:
//USceneComponent: is a component that has world positioning (think meshes and cameras) 
//UActorComponent: is a component that contains logic only (So for example: maybe a component that holds an array of items in an NPCs hand and spawns them in on death?)

//Pawn is an Actor that utilizing the possession system and has access to the basic movement component  
UCLASS()
class ROUGELIKE_API APlayerPawn : public APawn 
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties (boiler plate comment but true) 
	APlayerPawn(); 


	//Declare components as variables in header and initialize them in the constructor (the method listed above)  
	//Rule of thumb: every object is a pointer. Values and structs are typically just written out. Structs are usually denoted with F. For example FString or FTransform
	UPROPERTY(BlueprintReadWrite)
	USkeletalMeshComponent* mesh;

	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* cam;

	UPROPERTY(BlueprintReadWrite)
	USpringArmComponent* springarm;

protected:
	// Called when the game starts or when spawned (AKA Unreal's equivelent to Start(), also boiler plate comment)
	virtual void BeginPlay() override;

	int32 Lives = 5; // its a good rule of thumb to make important variables private and edit them through getter and setter functions to prevent unexpected modifications 
	int32 Armor = 10;

public:	
	// Update function
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input - I typically dont use this anymore because the enhanced input system took over and its much easier to implement in BP
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Declare functions that you want to call from BP with UFUNCTION(BlueprintCallable). This is vital because you wont be able to call it in blueprints otherwise
	UFUNCTION(BlueprintCallable)
	void TakeDamage(int32 dmg); // Side note: in visual studio, to quickly add functions to the .cpp, put your cursor withinin the function name, click Ctrl and Period and hit "create definition" Then click the little square thats in between your file name and the x in the window that popped up

	//seperate function for giving lives for visual purposes unique to gaining lives btw 
	UFUNCTION(BlueprintCallable)
	void GainLives(int32 Lives);

	UFUNCTION(BlueprintCallable)
	void Die();

	UFUNCTION(BlueprintPure)
	void GetLivesAndArmor(int32& PlayerLives, int32& PlayerArmor) { PlayerLives = Lives; PlayerArmor = Armor; } //You can add smaller logic to your header files to save space. In blueprint pure functions you return using references

};

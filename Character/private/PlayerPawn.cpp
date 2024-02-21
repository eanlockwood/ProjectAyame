// Read the bottom for other tid bits

//All of your real includes go under the headers include
//I found out these includes through the Docs on the unreal engine site. You will eventually know the component names by heart. 
#include "PlayerPawn.h"

//The components from earlier 
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

//I like to organize by putting includes from my own files underneath the game engine includes 

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh")); //To initialize components call create default sub object and attach it to another component using setup attachment
	mesh->SetupAttachment(RootComponent); //For calling functions on pointers use ->, else use your standard .

	springarm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm")); // the <Component Type> acts like a cast of sorts. So in the function you're creating a component casted as a USpringArmComponent
	springarm->SetupAttachment(mesh);
	springarm->TargetArmLength = 500;

	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")); //I honestly have no idea what TEXT(name) does but always use it and make sure each name is unique and doesnt have spaces
	cam->SetupAttachment(springarm);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	//You can make calls to parent functions using Super in c++ and by right clicking event nodes in BP and clicking "Add call to parent function"
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


//Make use of pragma region! makes things way cleaner 

#pragma region HealthStuff

void APlayerPawn::TakeDamage(int32 dmg)
{
	//Hating on elif statements is for stupid hipsters. On leetcode my solutions with "if gating" techniques typically run faster than 60% of solutions. Suck it youtube nerds. Hate harder <3
	//But really dont be that guy. Its not like we're calling this every frame

	if (Armor <= 0)
	{
		Lives -= dmg; 

		if (Lives <= 0)
			Die();
	}
	else {
		Armor -= dmg; 

		if (Armor < 0)
			Armor = 0;

		//Im too lazy to do the math for figuring out remaining dmg rn so ackchually the player gets a free hit on armor break, its not a bug, its a feature!
	}
}

void APlayerPawn::GainLives(int32 MoreLives)
{
	Lives += MoreLives;

	//when im not feeling lazy I will implement a formatted string that says something like "The player has gained x lives! :D" 
}

void APlayerPawn::Die()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 15, FColor::Red, "You have died!"); //on screen print function. For structs like color you can call predefined structures like red for example here
}

#pragma endregion


//various tips and tricks below! :D

#pragma region CharacterInformation

//pawns are basically plain actors with a movement component and the ability to make use of the possession system
//The possession system basically automates handling input priority
//The possession system makes use of PlayerController's and AIController's respectfully 
//Along with controlling possesion for the player, playercontroller also serves as a function hub for camera switching among other goodies 
//Characters are a subclass of pawn with preset like movement
//You can grab a reference to a player controller from anywhere using the function GetPlayerController from the UGameplayStatics library (a very good include to know)
//Using the player controller you can get the pawn that the controller is currently using (IE this very script)
//You can make subclasses of player controller for custom logic purposes, although I typically keep everything in subsystems or on the pawn itself (preference)

//in order to make use of pawns you made you either have to 
//A) create a gamemode, set the pawn you made as the default pawn, and set the levels gamemode as the one you just created 
//B) there is an option in the inspector for pawns called something along the lines of "automatically possess" - switch this from off to On placed in world and set it to recieve from player 0 

//You might have to add a floating pawn movement component within the bp childclass you create. Not sure, been a while. Do that if you pawn isnt moving

#pragma endregion

#pragma region CPPandBP
//This is why bp is awesome now. Once you successfully add c++ to your project, right click and click "create blueprint child" and now you can move the components around and do things like setting the mesh!
//Technically you can grab a reference to file location of the mesh to set in c++ but why should you do that? Doing movement is 10x easier in BP anyways
//Why not just make the entire class in BP? Because now you can reference the playerpawn type in c++, its always a good idea to start in c++ and derrive into something like BP_PlayerPawn
#pragma endregion

#pragma region Compiling
//Compiling in unreal sucks ass. 
//You have to close out of the entire engine when you want to compile c++ or else you run the risk of getting fucked by hot reloads or live coding.
//So just save yourself the hassel and close out of the engine when you're ready to compile c++. wait like 10 seconds after you close the engine though because sometimes live coding takes a minute to shut down
//To quickly compile in visual studio press ctrl + b
//sometimes when you open the engine you wont see your c++ files. Simply press the compile button in the bottom right hand corner of the editor
#pragma endregion

#pragma region DebuggingTips
//sometimes right clicking solution and hitting "rebuild all" fixes issues. Remember this is all boiler plate so sometimes the problem does lie in the engine itself
//Otherwise go to your project folder-> Delete the solution file and the folders: Saved, Intermediate and Binaries (WARNING: this will set some things to engine defaults) -> Right click the Uproject file and hit "generate visual studio files" -> Finally open the solution and rebuild all. If this doesnt work your code is the problem  
//The errors that show up can be weird but typically errors that are more gibberish mean you're missing an include somewhere or you made an event wrong
#pragma endregion
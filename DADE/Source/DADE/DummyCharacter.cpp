// Fill out your copyright notice in the Description page of Project Settings.

#include "DADE.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "DummyCharacter.h"
#include "Puzzle_Object.h"
#include "Puzzle_Trigger.h"
#include "PuzzleObject_Vehicle.h"
// Sets default values
ADummyCharacter::ADummyCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

												// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm



	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);

	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	m_FSM_Status = eFSM_Hero::FSM_Normal;

	

	m_Box_TriggerCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	m_Box_TriggerCollision->SetupAttachment(RootComponent);

	m_Box_TriggerCollision->OnComponentBeginOverlap.AddDynamic(this, &ADummyCharacter::OnOverlapBegin);
	m_Box_TriggerCollision->OnComponentEndOverlap.AddDynamic(this, &ADummyCharacter::OnOverlapEnd);


	_SM_MagicArea = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MagicArea"));
	_SM_MagicArea->SetupAttachment(RootComponent);
	
	_SM_MagicArea->OnComponentBeginOverlap.AddDynamic(this, &ADummyCharacter::OnOverlapBegin_MagicArea);
	_SM_MagicArea->OnComponentEndOverlap.AddDynamic(this, &ADummyCharacter::OnOverlapEnd_MagicArea);
	_SM_MagicArea->SetVisibility(false);
	MagicActive = false;
}
void ADummyCharacter::Tick(float DeltaTime)
{
	float tmp_AreaScale;
	Super::Tick(DeltaTime);
	TestCursorSymbol();

	if (MagicActive) {
		
		tmp_AreaScale = FMath::FInterpTo(_SM_MagicArea->GetComponentTransform().GetScale3D().X, _MagicArea, DeltaTime, 0.4f);
		if (tmp_AreaScale <= _MagicArea - 0.1f || tmp_AreaScale >= _MagicArea + 0.1f) {
			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Grow in %f %f %f"),_SM_MagicArea->GetComponentTransform().GetScale3D().X, tmp_AreaScale, _MagicArea));
			//_SM_MagicArea->GetComponentTransform().SetScale3D(FVector(tmp_AreaScale, tmp_AreaScale, tmp_AreaScale));
			_SM_MagicArea->SetWorldScale3D(FVector(tmp_AreaScale, tmp_AreaScale, tmp_AreaScale));
		}
	}
	
	
}
void ADummyCharacter::TestCursorSymbol()
{
	if (CursorToWorld != nullptr)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}
//////////////////////////////////////////////////////////////////////////
// Input

void ADummyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Move_Foward", this, &ADummyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move_Right", this, &ADummyCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Move_Mouse_X", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADummyCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Move_Mouse_Y", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADummyCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADummyCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADummyCharacter::TouchStopped);


	PlayerInputComponent->BindAction("MouseClick", IE_Pressed, this, &ADummyCharacter::TestMousePicking);
	PlayerInputComponent->BindAction("ActionActive", IE_Pressed, this, &ADummyCharacter::Action);
	//PlayerInputComponent->BindAction("MouseClick", IE_Released, this, &ADummyCharacter::TestMousePicking);
	
	PlayerInputComponent->BindAction("MagicActive", IE_Pressed, this, &ADummyCharacter::Magic);
	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ADummyCharacter::OnResetVR);

}
void ADummyCharacter::Magic()
{
	if (MagicActive)
	{
		
		MagicActive = false;
		_SM_MagicArea->SetWorldScale3D(FVector(1, 1, 1));
		_SM_MagicArea->SetVisibility(false);
		
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("magic on")));
		MagicActive = true;
		_SM_MagicArea->SetVisibility(true);
	}
}
void ADummyCharacter::TestMousePicking()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("MagicClicked!!")));

	if (MagicActive) {
		APlayerController* tmpcontroller = UGameplayStatics::GetPlayerController(this, 0);
		FHitResult Hit;
		tmpcontroller->GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{

			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("MagicClicked!!")));

			APuzzle_Object*Temp = Cast<APuzzle_Object>(Hit.Actor.Get());
			if (Temp != NULL &&	Temp->_bInside_MagicArea==true)
			{
				Temp->OnMagickActive();

			}
		}
	}
}
void ADummyCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ADummyCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
}

void ADummyCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
	TestMousePicking();
}
void ADummyCharacter::Action()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Touch")));
	APlayerController *tempController;
	APuzzleObject_Vehicle* Temp;
	switch (m_FSM_Status)
	{
	case eFSM_Hero::FSM_Normal:
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Normal!!")));
		break;
	case eFSM_Hero::FSM_EnableJump:
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Jump!!")));
		Jump();
		break;
	case eFSM_Hero::FSM_EnableRiding:
		tempController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("rrrr")));
		Temp = Cast<APuzzleObject_Vehicle>(Changer);
		if (Temp != NULL) {
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("ssarrrrr")));
			Temp->_ARidingTarget = this;
			tempController->Possess(Changer);
			tempController = NULL;
			Temp = NULL;
			m_FSM_Status = FSM_Riding;
		}

		break;
	case eFSM_Hero::FSM_Riding:
		break;
	case eFSM_Hero::FSM_EnableCliming:
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("clim go")));
		GetCharacterMovement()->GravityScale = 0;
		m_FSM_Status = eFSM_Hero::FSM_Climing;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
		break;
	case eFSM_Hero::FSM_Climing:
		GetCharacterMovement()->GravityScale = 1;
		m_FSM_Status = eFSM_Hero::FSM_Normal;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);

		break;
	}

}
void ADummyCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADummyCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADummyCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		if (m_FSM_Status != eFSM_Hero::FSM_Climing) {
			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("moveFowr")));
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("clclclc %f "), Value));
			AddActorWorldOffset(FVector(0, 0, 1)*Value, true);
		}
		//setgravity


		//AddMovementInput(FVector(0, 0, 1), Value);
	}

}

void ADummyCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		if (m_FSM_Status != eFSM_Hero::FSM_Climing)
		{
			
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
		}
	}
}

void ADummyCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Over!!")));
	APuzzle_Trigger* tmp_PT = Cast<APuzzle_Trigger>(OtherActor);
	if (tmp_PT != NULL&&m_FSM_Status == eFSM_Hero::FSM_Normal)
	{
		switch (tmp_PT->m_TriggerID)
		{
		case eID_Trigger::TriggerID_JumpZone:
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Change Jumpzon")));
			m_FSM_Status = eFSM_Hero::FSM_EnableJump;
			break;
		case eID_Trigger::TriggerID_ClimingZone:
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Change climzone")));
			m_FSM_Status = eFSM_Hero::FSM_EnableCliming;
			break;
		default:
			break;
		}

	}
}
void ADummyCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("OverOut!!")));
	APuzzle_Trigger* tmp_PT = Cast<APuzzle_Trigger>(OtherActor);
	if (tmp_PT != NULL)
	{
		switch (tmp_PT->m_TriggerID)
		{
		case eID_Trigger::TriggerID_JumpZone:
			if (m_FSM_Status == eFSM_Hero::FSM_EnableJump) {
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Out Jump zone")));
				m_FSM_Status = eFSM_Hero::FSM_Normal;
			}
			break;
		case eID_Trigger::TriggerID_ClimingZone:
			if (m_FSM_Status == eFSM_Hero::FSM_Climing) {
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Out clim zone")));
				GetCharacterMovement()->GravityScale = 1;
				m_FSM_Status = eFSM_Hero::FSM_Normal;
				GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);

				m_FSM_Status = eFSM_Hero::FSM_Normal;
			}
			else if (m_FSM_Status == eFSM_Hero::FSM_EnableCliming)
				m_FSM_Status = eFSM_Hero::FSM_Normal;
			break;
		default:
			break;
		}

	}
}


void ADummyCharacter::OnOverlapBegin_MagicArea(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis)
{
	APuzzle_Object*Temp = Cast<APuzzle_Object>(OtherActor);
	if (Temp != NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Area overlap")));
		//Temp->OnMagickActive();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_MagicAreaEffect, Temp->GetActorTransform(), true);
		Temp->_bInside_MagicArea = true;
	}
	
}
void ADummyCharacter::OnOverlapEnd_MagicArea(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APuzzle_Object*Temp = Cast<APuzzle_Object>(OtherActor);
	if (Temp != NULL)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Area overlap")));
		//Temp->OnMagickActive();
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_MagicAreaEffect, Temp->GetActorTransform(), true);
		Temp->_bInside_MagicArea = false;
	}
}
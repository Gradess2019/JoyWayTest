// Copyright Epic Games, Inc. All Rights Reserved.

#include "StandaloneServerCommands.h"

#define LOCTEXT_NAMESPACE "FStandaloneServerModule"

void FStandaloneServerCommands::RegisterCommands()
{
	UI_COMMAND(ButtonAction, "Start server", "Launch dedicated server", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE

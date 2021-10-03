// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "StandaloneServerStyle.h"

class FStandaloneServerCommands : public TCommands<FStandaloneServerCommands>
{
public:

	FStandaloneServerCommands()
		: TCommands<FStandaloneServerCommands>(TEXT("StandaloneServer"), NSLOCTEXT("Contexts", "StandaloneServer", "StandaloneServer Plugin"), NAME_None, FStandaloneServerStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > ButtonAction;
};

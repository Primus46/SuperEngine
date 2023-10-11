#pragma once
#include "CoreMinimal.h"
#include "Game.h"

int main(int argc, char* argv[]) {
	Game::GetGameInstance()->Run();
	Game::DestroyGameInstance();

	return 0;
}
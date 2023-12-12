#pragma once
#include "SDL2/SDL_mixer.h"

struct SESFXStack {
	SEString Path;
	Mix_Chunk* Chunk;
};
struct SEMUSStack {
	SEString Path;
	Mix_Music* Music;
};

class SEAudioPlayer
{
public:
	SEAudioPlayer() = default;
	~SEAudioPlayer();

	// load the sfx to the array and mixer
	Mix_Chunk* LoadSFX(SEString Path);

	// load music to the array and mixer
	Mix_Music* LoadMusic(SEString Path);

	// play a sound effect
	void PlaySFX(Mix_Chunk* Chunk, int Volume = 50, int Loops = 0, int Channel = -1);

	// play background music
	void PlayMusic(Mix_Music* Music, float Volume = 50, int Loops = -1);

	// pause the current playing music
	void PauseMusic();

	//resume the currently paused music
	void ResumeMusic();

private:
	// stack to store all game sounds added to the game
	TArray<SESFXStack> m_SFXStack;
	// stack to store all of the music added to the game
	TArray<SEMUSStack> m_MusicStack;
};


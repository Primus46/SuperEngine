#include "CoreMinimal.h"
#include "SEAudioPlayer.h"

SEAudioPlayer::~SEAudioPlayer()
{
	// deload all the sound effects from memory
	for (auto SFX : m_SFXStack) {
		if (SFX.Chunk != nullptr) {
			Mix_FreeChunk(SFX.Chunk);
		}
	}

	m_SFXStack.clear();

	// delete all of the music from memory
	for (auto Music : m_MusicStack) {
		if (Music.Music != nullptr) {
			Mix_FreeMusic(Music.Music);
		}
	}

	m_MusicStack.clear();

}

Mix_Chunk* SEAudioPlayer::LoadSFX(SEString Path)
{
	// check if the sound file has already been imported
	for (auto SFX : m_SFXStack) {
		if (strcmp(SFX.Path.c_str(), Path.c_str()) == 0) {
			// return the chunk if it was found
			return SFX.Chunk;
		}
	}

	// create a new sfx if we didn't find one
	Mix_Chunk* NewSFX = Mix_LoadWAV(Path.c_str());

	SESFXStack NewStackItem{
		Path,
		NewSFX
	};

	return NewStackItem.Chunk;
}

Mix_Music* SEAudioPlayer::LoadMusic(SEString Path)
{
	// check if the Music file has already been imported
	for (auto Music : m_MusicStack) {
		if (strcmp(Music.Path.c_str(), Path.c_str()) == 0) {
			// return the Music if it was found
			return Music.Music;
		}
	}

	// create a new Music if we didn't find one
	Mix_Music* NewMusic = Mix_LoadMUS(Path.c_str());

	SEMUSStack NewStackItem{
		Path,
		NewMusic
	};

	return NewStackItem.Music;
}

void SEAudioPlayer::PlaySFX(Mix_Chunk* Chunk, int Volume, int Loops, int Channel)
{
	if (Chunk == nullptr) {
		return;
	}

	// set the volume of the chunk
	Mix_VolumeChunk(Chunk, Volume);
	// play the sound effect
	Mix_PlayChannel(Channel, Chunk, Loops);
}

void SEAudioPlayer::PlayMusic(Mix_Music* Music, float Volume, int Loops)
{
	if (Music == nullptr) {
		return;
	}
	
	// play the music track
	Mix_PlayMusic(Music, Loops);
	// update volume
	Mix_VolumeMusic(Volume);
}

void SEAudioPlayer::PauseMusic()
{
	Mix_PauseMusic();
}

void SEAudioPlayer::ResumeMusic()
{
	Mix_ResumeMusic();
}

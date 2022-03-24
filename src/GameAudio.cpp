#include "GameAudio.h"
#include <stdlib.h>
#include <stdio.h>
#include <AL/al.h>
#include <AL/alut.h>

#define NUM_BUFFERS 1
#define NUM_SOURCES 1
#define NUM_ENVIRONMENTS 1

ALfloat listenerPos[] = { 0.0, 0.0, 4.0 };
ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
ALfloat listenerOri[] = { 0.0, 0.0, 1.0, 0.0, 1.0, 0.0 };

ALfloat source0Pos[] = { -2.0, 0.0, 0.0 };
ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };

ALfloat source1Pos[] = { 2.0, 0.0, 0.0 };
ALfloat source1Vel[] = { 0.0, 0.0, 0.0 };

ALfloat source2Pos[] = { 0.0, 0.0, -4.0 };
ALfloat source2Vel[] = { 0.0, 0.0, 0.0 };
ALCdevice *dev;

ALuint buffer[NUM_BUFFERS];
ALuint source[NUM_SOURCES];
ALuint environment[NUM_ENVIRONMENTS];

int GLwin;

ALsizei size, freq;
ALenum format;
ALvoid *data;
int ch;
namespace game
{
	static int started_resources = 0;

	GameAudio::GameAudio(int argc, char** argv)
	{
		this->playing = 0;
		//initialize openAL
		alutInit(&argc, argv);
		/*
		dev = alcOpenDevice(NULL);
		if(!dev)
		{
			fprintf(stderr, "Oops\n");
			exit(1);
		}*/
		char al_bool;

		// alutInit(0, NULL) ;

		alListenerfv(AL_POSITION, listenerPos);
		alListenerfv(AL_VELOCITY, listenerVel);
		alListenerfv(AL_ORIENTATION, listenerOri);

		alGetError(); /* clear error */

		// Generate buffers, or no sound will be produced
		alGenBuffers(NUM_BUFFERS, buffer);
		if (alGetError() != AL_NO_ERROR)
		{
			printf("- Error creating buffers !!\n");
			exit(1);
		}
		else
		{
			printf("Created buffers\n");
		}

		//Music: https://www.bensound.com
        ALbyte file_name[] = "Audio/bensound-epic.wav";
		alutLoadWAVFile(&file_name[0], &format, &data, &size, &freq, &al_bool);
		alBufferData(buffer[0], format, data, size, freq);
		alutUnloadWAV(format, data, size, freq);

		printf("%s\n", &file_name[0]);
		/*
		 alutLoadWAVFile("29 Trailer Theme - Part 1.wav",&format,&data,&size,&freq, &al_bool);
		 alBufferData(buffer[1],format,data,size,freq);
		 alutUnloadWAV(format,data,size,freq);

		 alutLoadWAVFile("29 Trailer Theme - Part 1.wav",&format,&data,&size,&freq, &al_bool);
		 alBufferData(buffer[2],format,data,size,freq);
		 alutUnloadWAV(format,data,size,freq);
		 */
		alGetError(); /* clear error */
		alGenSources(NUM_SOURCES, source);

		if (alGetError() != AL_NO_ERROR)
		{
			printf("- Error creating sources !!\n");
			exit(2);
		}

		alSourcef(source[0], AL_PITCH, 1.0f);
		alSourcef(source[0], AL_GAIN, 1.0f);
		alSourcefv(source[0], AL_POSITION, source0Pos);
		alSourcefv(source[0], AL_VELOCITY, source0Vel);
		alSourcei(source[0], AL_BUFFER, buffer[0]);
		alSourcei(source[0], AL_LOOPING, AL_TRUE);

		alSourcef(source[1], AL_PITCH, 1.0f);
		alSourcef(source[1], AL_GAIN, 1.0f);
		alSourcefv(source[1], AL_POSITION, source1Pos);
		alSourcefv(source[1], AL_VELOCITY, source1Vel);
		alSourcei(source[1], AL_BUFFER, buffer[1]);
		alSourcei(source[1], AL_LOOPING, AL_TRUE);

		alSourcef(source[2], AL_PITCH, 1.0f);
		alSourcef(source[2], AL_GAIN, 1.0f);
		alSourcefv(source[2], AL_POSITION, source2Pos);
		alSourcefv(source[2], AL_VELOCITY, source2Vel);
		alSourcei(source[2], AL_BUFFER, buffer[2]);
		alSourcei(source[2], AL_LOOPING, AL_TRUE);

		started_resources++;
	}

	void GameAudio::play()
	{
		alSourcePlay(source[0]);
		this->playing = 1;
	}
	void GameAudio::stop()
	{
		alSourceStop(source[0]);
		this->playing = 0;
	}
	void GameAudio::pause()
	{
		alSourcePause(source[0]);
		this->playing = 0;
	}
	bool GameAudio::isPlaying()
	{
		return this->playing;
	}
	GameAudio::~GameAudio()
	{
		alSourceStop(source[0]);
		alDeleteSources(NUM_SOURCES, source);
		started_resources--;
		printf("destroy count %i\n", started_resources);
		if(started_resources == 0)
		{
			printf("calling exit %i\n", started_resources);
		}
	}

} /* namespace game */

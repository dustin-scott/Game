#include "GameAudio.h"
#include <stdlib.h>
#include <stdio.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AudioFile.h>

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
ALCdevice *device;

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
		//reset error stack.
		alGetError();

		this->playing = 0;
		//initialize openAL
		//alutInit(&argc, argv);
		device = alcOpenDevice(NULL);
		if (!device)
		{
			fprintf(stderr, "Oops\n");
			exit(1);
		}
		this->initializeContext();
		this->initializeDevices();
		this->initializeListeners();
		this->initializeBuffers();
		this->initializeSources();
		this->loadDataIntoBuffers();

		char al_bool;

		// alutInit(0, NULL) ;

		
		//Uncomment when another audio library is found to load raw data.
		//alBufferData(buffer[0], format, data, size, freq);
		
		
		
		//alutUnloadWAV(format, data, size, freq);

		/*
		 alutLoadWAVFile("29 Trailer Theme - Part 1.wav",&format,&data,&size,&freq, &al_bool);
		 alBufferData(buffer[1],format,data,size,freq);
		 alutUnloadWAV(format,data,size,freq);

		 alutLoadWAVFile("29 Trailer Theme - Part 1.wav",&format,&data,&size,&freq, &al_bool);
		 alBufferData(buffer[2],format,data,size,freq);
		 alutUnloadWAV(format,data,size,freq);
		 */
		alGetError(); /* clear error */

		started_resources++;
	}

	void GameAudio::initializeDevices()
	{	
		alGetError();
		ALCenum error;
		const ALCchar *devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
        	fprintf(stdout, "AL error found on alcGetString! %d\n", error);
			if(error == AL_INVALID_OPERATION)
			{
				printf("Operation was invalid.\n");
			}
			exit(1);
		}

        const ALCchar *device = devices, *next = devices + 1;
        size_t len = 0;

        fprintf(stdout, "Devices list:\n");
        fprintf(stdout, "----------\n");
        while (device && *device != '\0' && next && *next != '\0') {
                fprintf(stdout, "%s\n", device);
                len = strlen(device);
                device += (len + 1);
                next += (len + 2);
        }
        fprintf(stdout, "----------\n");

		error = alGetError();
		if (error != AL_NO_ERROR)
		{
        	fprintf(stdout, "AL error found! %d\n", error);
			exit(1);
		}
	}

	void GameAudio::initializeContext()
	{
		ALCcontext *context;

		context = alcCreateContext(device, NULL);
		if (!alcMakeContextCurrent(context))
		{
			fprintf(stderr, "Oops\n");
			exit(1);
		}
	}

	void GameAudio::initializeListeners()
	{
		alListenerfv(AL_POSITION, listenerPos);
		alListenerfv(AL_VELOCITY, listenerVel);
		alListenerfv(AL_ORIENTATION, listenerOri);

		ALCenum error;
		error = alGetError();

		if (error != AL_NO_ERROR)
		{
        	fprintf(stdout, "AL error found!\n");
			exit(1);
		}
	}

	void GameAudio::initializeSources()
	{
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
	}

	void GameAudio::initializeBuffers()
	{
		alGetError();
		ALCenum error;
		// Generate buffers, or no sound will be produced
		alGenBuffers(NUM_BUFFERS, buffer);
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			printf("- Error creating buffers %d!!\n", error);
			exit(1);
		}
		else
		{
			printf("Created buffers\n");
		}
	}

	void GameAudio::loadDataIntoBuffers()
	{
		//Music: https://www.bensound.com
        std::string file_name = "Audio/bensound-epic.wav";
		//alutLoadWAVFile(&file_name[0], &format, &data, &size, &freq, &al_bool);
		AudioFile<double> file;
		if(!file.load(file_name))
		{
			printf("Error loading file %s \n", file_name.c_str());
			exit(1);
		}
		else
		{
			//TODO: Finish fixing this per https://github.com/adamstark/AudioFile/issues/9#issuecomment-670521283
			data = reinterpret_cast<ALvoid*>(file.samples[0].data());
			size = file.samples[0].size();
			freq = file.getSampleRate();
			alBufferData(buffer[0], format, data, size, freq);
		}
		printf("%s\n", &file_name[0]);
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

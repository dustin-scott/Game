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

	template <typename T> T clip(const T& n, const T& lower, const T& upper) 
	{
		return std::max(lower, std::min(n, upper));
	}

	static inline uint8_t sampleToSingleByte (double sample)
	{
		sample = clip (sample, -1., 1.);
		sample = (sample + 1.) / 2.;
		return static_cast<uint8_t> (sample * 255.);
	}

	static inline int16_t sampleToSixteenBitInt (double sample)
	{
		sample = clip (sample, -1., 1.);
		return static_cast<int16_t> (sample * 32767.);
	}

	static inline void addInt16ToFileData (std::vector<uint8_t>& fileData, int16_t i, bool isLittleEndian = true)
	{
		uint8_t bytes[2];
		
		if (isLittleEndian)
		{
			bytes[1] = (i >> 8) & 0xFF;
			bytes[0] = i & 0xFF;
		}
		else
		{
			bytes[0] = (i >> 8) & 0xFF;
			bytes[1] = i & 0xFF;
		}
		
		fileData.push_back (bytes[0]);
		fileData.push_back (bytes[1]);
	}

	static inline void addInt32ToFileData (std::vector<uint8_t>& fileData, int32_t i, bool isLittleEndian)
	{
		uint8_t bytes[4];
		
		if (isLittleEndian)
		{
			bytes[3] = (i >> 24) & 0xFF;
			bytes[2] = (i >> 16) & 0xFF;
			bytes[1] = (i >> 8) & 0xFF;
			bytes[0] = i & 0xFF;
		}
		else
		{
			bytes[0] = (i >> 24) & 0xFF;
			bytes[1] = (i >> 16) & 0xFF;
			bytes[2] = (i >> 8) & 0xFF;
			bytes[3] = i & 0xFF;
		}
		
		for (int i = 0; i < 4; i++)
			fileData.push_back (bytes[i]);
	}

	static inline ALenum toOpenAlFormat(short channels, short samples)
	{
		bool stereo = (channels > 1);

		switch (samples) {
		case 16:
			if (stereo)
				return AL_FORMAT_STEREO16;
			else
				return AL_FORMAT_MONO16;
		case 8:
			if (stereo)
				return AL_FORMAT_STEREO8;
			else
				return AL_FORMAT_MONO8;
		default:
			return -1;
		}
	}

	static inline bool savePCMToBuffer(AudioFile<double> file, std::vector<uint8_t>& fileData)
	{
		auto bitDepth = file.getBitDepth();
		fileData.clear();

		int16_t audioFormat = bitDepth == 32 ? WavAudioFormat::IEEEFloat : WavAudioFormat::PCM;

		for (int i = 0; i < file.getNumSamplesPerChannel(); i++)
		{
			for (int channel = 0; channel < file.getNumChannels(); channel++)
			{
				if (bitDepth == 8)
				{
					uint8_t byte = sampleToSingleByte(file.samples[channel][i]);
					fileData.push_back(byte);
				}
				else if (bitDepth == 16)
				{
					int16_t sampleAsInt = sampleToSixteenBitInt(file.samples[channel][i]);
					addInt16ToFileData(fileData, sampleAsInt, true);
				}
				else if (bitDepth == 24)
				{
					int32_t sampleAsIntAgain = (int32_t)(file.samples[channel][i] * (double)8388608.);

					uint8_t bytes[3];
					bytes[2] = (uint8_t)(sampleAsIntAgain >> 16) & 0xFF;
					bytes[1] = (uint8_t)(sampleAsIntAgain >> 8) & 0xFF;
					bytes[0] = (uint8_t)sampleAsIntAgain & 0xFF;

					fileData.push_back(bytes[0]);
					fileData.push_back(bytes[1]);
					fileData.push_back(bytes[2]);
				}
				else if (bitDepth == 32)
				{
					int32_t sampleAsInt;

					if (audioFormat == WavAudioFormat::IEEEFloat)
						sampleAsInt = (int32_t) reinterpret_cast<int32_t&> (file.samples[channel][i]);
					else // assume PCM
						sampleAsInt = (int32_t)(file.samples[channel][i] * std::numeric_limits<int32_t>::max());

					addInt32ToFileData(fileData, sampleAsInt, true);
				}
				else
				{
					assert(false && "Trying to write a file with unsupported bit depth");
					return false;
				}
			}
		}

		return true;
	}

	void GameAudio::loadDataIntoBuffers()
	{
		//Music: https://www.bensound.com
        std::string file_name = "Audio/bensound-epic.wav";
		//alutLoadWAVFile(&file_name[0], &format, &data, &size, &freq, &al_bool);
		AudioFile<double> audioFile;
		if(!audioFile.load(file_name))
		{
			printf("Error loading file %s \n", file_name.c_str());
			exit(1);
		}
		else
		{
			//TODO: Finish fixing this per https://github.com/adamstark/AudioFile/issues/9#issuecomment-670521283
			std::vector<uint8_t> audioData;
			savePCMToBuffer(audioFile, audioData);

			data = reinterpret_cast<ALvoid*>(audioData.data());
			size = audioData.size();
			freq = audioFile.getSampleRate();
			format = toOpenAlFormat(audioFile.getNumChannels(),  audioFile.getBitDepth());
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

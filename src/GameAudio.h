#ifndef GAMEAUDIO_H_
#define GAMEAUDIO_H_

#include <AL/alc.h>
namespace game {

class GameAudio {
private:
	bool playing;
	void initializeDevices();
	void initializeContext();
	void initializeListeners();
	void initializeSources();
	void initializeBuffers();
	void loadDataIntoBuffers();
public:
	bool isPlaying();
	void play();
	void stop();
	void pause();
	void delete_sources();
	GameAudio(int argc, char** argv);
	virtual ~GameAudio();
};

} /* namespace game */
#endif /* GAMEAUDIO_H_ */

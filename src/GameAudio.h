/*
 * GameAudio.h
 *
 *  Created on: Dec 1, 2012
 *      Author: Dustin Scott
 */

#ifndef GAMEAUDIO_H_
#define GAMEAUDIO_H_

namespace game {

class GameAudio {
private:
	bool playing;
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

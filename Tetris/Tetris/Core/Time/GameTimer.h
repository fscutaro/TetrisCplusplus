#pragma once
#include "../Processing/IUpdateable.h"
class GameTimer
{
public:
	GameTimer(void);
	~GameTimer(void);
	void Start();
	void Pause();
	void Resume();
	void Update();
	void Stop();
	float getElapesedTime();
	float getPreviousElapsedTime();
	float getDeltaTime();
private:
	void _Reset();
	float _elapsedTime;
	float _previousElapsedTime;
	float _deltaTime;
	bool _paused;
};


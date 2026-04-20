#pragma once
const int TARGET_FPS = 180;
const float TARGET_DELTA = 1.5f;

class Ticker
{
public:
	void Tick();
	inline float GetDeltaTime() { return DeltaTime; }
	static Ticker& GetInstance()
	{
		static Ticker TickerInstance;
		return TickerInstance;
	}
private:
	Ticker();
	float DeltaTime = 0.0f, LastDelta;
};


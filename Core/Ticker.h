#pragma once
const int TARGET_FPS = 150;
const float TARGET_DELTA = 1.5f;

class Ticker
{
public:
	void Tick();
	inline float GetDeltaTime() { return DeltaTime; }
	static Ticker* GetInstance()
	{
		if (TickerInstance != nullptr) return TickerInstance;
		else return TickerInstance = new Ticker();
	}
private:
	Ticker();
	static Ticker* TickerInstance;
	float DeltaTime = 0.0f, LastDelta;
};


#pragma once
class IGameplayRules
{
public:
	inline void Update() { };
};

enum GameState { Initializing, Running, LifeLost, GameOver };

class TemplateGameplayRules : public IGameplayRules
{

public:
	TemplateGameplayRules(int healthLossLimit, int initialHealth = 3, GameState gameState = Initializing)
	{
		HealthLossLimit = healthLossLimit;
		CurrentGameState = gameState;
		CurrentHealth = initialHealth;
	};
	inline int GetHealth() { return CurrentHealth; }
	inline void SetHealth(int number) { CurrentHealth = number; CurrentGameState = LifeLost; }
	inline void DecreaseHealth(int times) { CurrentHealth -= times; ; CurrentGameState = LifeLost; }

	inline GameState GetCurrentGameState() { return CurrentGameState; }
	inline void SetCurrentGameState(GameState gameState) { CurrentGameState = gameState; }
	
	inline int GetHealthLossLimit() { return HealthLossLimit; }

private:
	GameState CurrentGameState;
	int CurrentHealth;
	int HealthLossLimit;
};
#pragma once

#include <SDL.h>
#include <string>

class ScoreManager
{
public:

	ScoreManager() : currentScore(0) {}
	~ScoreManager();

	void AddScore(int points);

	void SetScore(int points);

	void UpdateHighScore();

	int GetScore();

	int GetHighScore();

	void SaveHighScoreToFile(const std::string& filename);

	int LoadHighScoreFromFile(const std::string& filename);

private:

	int currentScore = 0;

	int highScore = 0;

	const char KEY = 0xA784aa8A84;
};
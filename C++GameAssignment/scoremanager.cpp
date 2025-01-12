#include "scoremanager.h"

#include<SDL_ttf.h>
#include<sstream>
#include<fstream>
#include<iostream>

void ScoreManager::AddScore(int points)
{
	currentScore += points;

    UpdateHighScore();
}

void ScoreManager::SetScore(int points)
{
	currentScore == points;
}

void ScoreManager::UpdateHighScore() 
{
	if (currentScore >= highScore)
	{
		highScore = currentScore;
	}
}

int ScoreManager::GetScore()
{
	return currentScore;
}

int ScoreManager::GetHighScore() 
{
	return LoadHighScoreFromFile("./Assets/Player/HighScore.txt");
}

void ScoreManager::SaveHighScoreToFile(const std::string& filename)
{
    // Encrypt high score before saving, using XOR operation, can only be decrypted with the key
    int encryptedHighScore = highScore ^ KEY;

    // Open the file to save the encrypted high score
    std::ofstream scoreStream(filename, std::ios::binary);
    if (scoreStream.is_open())
    {
        scoreStream.write(reinterpret_cast<char*>(&encryptedHighScore), sizeof(encryptedHighScore));
        scoreStream.close();
    }
    else
    {
        std::cerr << "Error opening file for writing!" << std::endl;
    }
}

int ScoreManager::LoadHighScoreFromFile(const std::string& filename)
{
    // Open the encrypted file high score
    std::ifstream scoreStream(filename, std::ios::binary);
    if (scoreStream.is_open())
    {
        int encryptedHighScore = 0;
        scoreStream.read(reinterpret_cast<char*>(&encryptedHighScore), sizeof(encryptedHighScore));
        scoreStream.close();

        // Decrypt using key
        return highScore = encryptedHighScore ^ KEY;
    }
    else
    {
        std::cerr << "Error opening file for reading!" << std::endl;
        return 0;
    }
}
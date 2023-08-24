#include "Extension.h"
std::string GetHighScoreFromFile(std::string pathFile)
{
	std::ifstream HighScoreFile(pathFile);
	std::string highscore;
	HighScoreFile >> highscore;
	return highscore;
}
void updateHighScore(std::string pathFile,
	const int& score,
	const std::string& old_high_score)
{
	int oldHighScore = 0;
	std::ofstream HighScoreFile(pathFile);
	std::string newHighScore;
	std::stringstream ConvertStringToInt(old_high_score);
	ConvertStringToInt >> oldHighScore;
	if (score > oldHighScore)
	{
		oldHighScore = score;
	}
	newHighScore = std::to_string(oldHighScore);

	HighScoreFile << newHighScore;
}
void resetHighScore(std::string pathFile)
{
	int oldHighScore = 0;
	std::ofstream HighScoreFile(pathFile);
	HighScoreFile << 0;
}
std::vector<int> readNumberListFromFile(const std::string& filePath)
{
	std::vector<int> numberList;
	int num;
	std::ifstream wordFile(filePath);
	if (wordFile.is_open()) {
		while (wordFile >> num) {
			numberList.push_back(num);
		}
		wordFile.close();
		return numberList;
	}
	
}
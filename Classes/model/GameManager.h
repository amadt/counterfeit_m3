#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "Types.h"
#include "ArtManager.h"

const int difficultyCount = 3;

class Level
{
public:
	int id;
	int blobRows;
	int blobCols;
	int artSizeBig;
	int artSizeSmall;
	int gameSeconds;
	std::string name;
};

class GameManager
{

public:
	static GameManager* getInstance();
	
	void		selectGallary(Gallary* gallary);
	void		selectArt(Art* art, Level level);
	void		resetArt();
	Gallary*	getSelectedGallary()		 { return _selectedGallary; }
	Art*		getSelectedArt()			 { return _selectedArt;  }
	Level		getSelectedLevel()			 { return _selectedLevel; }
	Level		getLevel(int index)			 { return _levels[index]; }
	void		setArtDimensions(int cols, int rows) { _artCols = cols; _artRows = rows; }
	int			getArtRows() { return _artRows; }
	int			getArtCols() { return _artCols; }

	int         getTokens() { return _tokens; }
	int         getLives() { return _lives; }
	void		setTokens(int value);
	void		setLives(int value);
	void		useLive() { setLives(_lives - 1); }
	void		useToken() { setTokens(_tokens - 1); }
	bool        checkLevelStatus(Art* art, Level level);
	void		setLevelComplete(Art* art, Level level);

private:
	GameManager();

	Gallary* _selectedGallary;
	Art* _selectedArt;
	Level _selectedLevel;

	Level _levels[difficultyCount];

	int _tokens;
	int _lives;

	int _artCols;
	int _artRows;
};


#endif
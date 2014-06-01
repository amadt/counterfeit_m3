#ifndef __ART_MANAGER_H__
#define __ART_MANAGER_H__

#include "Types.h"

const int LEVELS = 3;

class Art
{
public:
	Art(int id);
	int id;
	std::string name;
	std::string artist;
	std::string image;
	int year;
	int croppedOffset;
};

class Gallary
{
public:
	Gallary(int id);
	int id;
	std::string name;
	std::string romanNumber;
	std::vector<int> artIds;
	std::string image;
};



class ArtManager
{

public:
	static ArtManager* getInstance();
	
	int getGallaryCount() { return _gallaries.size(); }

	Gallary* getGallary(int id);
	Art*     getArt(int id);

private:
	ArtManager();

	std::vector<Gallary*> _gallaries;
	std::vector<Art*> _art;
};


#endif
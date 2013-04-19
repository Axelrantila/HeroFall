#include <fstream>
#include <sstream>
#include "SpriteSheet.h"


SpriteSheet::SpriteSheet()
{
	m_wSheet = 0;
	m_hSheet = 0;
	m_wSprite = 0;
	m_hSprite = 0;
	m_spriteSheet = nullptr;
}

SpriteSheet::~SpriteSheet()
{
	if(m_spriteSheet != nullptr)
	{
		delete m_spriteSheet;
	}
}

bool SpriteSheet::loadSpriteSheet(std::string spriteSheetName)
{
	//Load the spritesheet
	std::string folderPath = "assets\\sprites\\";
	folderPath += spriteSheetName;

	std::string imagePath = folderPath;
	imagePath += ".png";

	m_spriteSheet = new sf::Texture();

	if(m_spriteSheet->loadFromFile(imagePath))
	{
		std::string infoPath = folderPath;
		infoPath += ".txt";

		//Read the information file
		std::ifstream in;
		in.open(infoPath);
	
		if(!in.is_open())
		{
			return false;
		}

		bool infoLoaded[4] = {false, false, false, false};

		while(!in.eof())
		{
			std::string inString = "";
			getline(in, inString);

			if(inString.find("wSheet=") != std::string::npos)
			{
				std::stringstream sstream(inString.substr(7, inString.size() - 7));
				sstream >> m_wSheet;
				infoLoaded[0] = true;
			}

			else if(inString.find("hSheet=") != std::string::npos)
			{
				std::stringstream sstream(inString.substr(7, inString.size() - 7));
				sstream >> m_hSheet;
				infoLoaded[1] = true;
			}

			else if(inString.find("wSprite=") != std::string::npos)
			{
				std::stringstream sstream(inString.substr(8, inString.size() - 8));
				sstream >> m_wSprite;
				infoLoaded[2] = true;
			}

			else if(inString.find("hSprite=") != std::string::npos)
			{
				std::stringstream sstream(inString.substr(8, inString.size() - 8));
				sstream >> m_hSprite;
				infoLoaded[3] = true;
			}

			else
			{
				m_spriteList.push_back(inString);
			}
		}

		for(int a = 0; a < 4; a++)
		{
			if(!infoLoaded[a])
			{
				return false;
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}

sf::Sprite* SpriteSheet::getSprite(std::string spriteName)
{
	return getSprite(nullptr, spriteName);
}

sf::Sprite* SpriteSheet::getSprite(sf::Sprite* sprite, std::string spriteName)
{
	/*
	Check if the sprite in question exists and at what position
	in the array it is at if it does
	Returns nullptr if it doesn't exist
	*/
	int spritePosition = -1;
	for(unsigned int a = 0; a < m_spriteList.size(); a++)
	{
		if(spriteName == m_spriteList[a])
		{
			spritePosition = a;
			break;
		}
	}

	if(spritePosition == -1)
	{
		return nullptr;
	}

	/*
	Calculate at what position in the spritesheet
	the sprite is
	*/
	int rows = m_hSheet / m_hSprite;
	int collumns = m_wSheet / m_wSprite;

	int targetXPos = 0;
	int targetYPos = 0;

	while(spritePosition > 0)
	{
		spritePosition--;
		targetXPos++;

		if(targetXPos >= collumns)
		{
			targetXPos = 0;
			targetYPos++;
		}
	}
	
	if(sprite == nullptr)
	{
		sprite = new sf::Sprite(*m_spriteSheet);
	}
	else
	{
		if (sprite->getTexture() != m_spriteSheet)
		{
			sprite->setTexture(*m_spriteSheet);
		}
	}

	sprite->setTextureRect(sf::IntRect(targetXPos * m_wSprite,
		targetYPos * m_hSprite,
		m_wSprite,
		m_hSprite));

	return sprite;
}
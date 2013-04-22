#include "LevelObjectPlattform.h"


LevelObjectPlattform::LevelObjectPlattform(float xPos, float yPos)
	:LevelObject(PT_UPPER_LEFT, LO_PLATTFORM, xPos, yPos)
{
}


LevelObjectPlattform::~LevelObjectPlattform()
{
}

bool LevelObjectPlattform::collidesWith(LevelObject* anotherLevelObject)
{
	return false;
}

void LevelObjectPlattform::draw(sf::RenderWindow* window)
{
}
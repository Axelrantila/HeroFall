#ifndef POPUPIMAGEMANAGER_H
#define POPUPIMAGEMANAGER_H

#include <SFML\System\Vector2.hpp>
#include <vector>

//Forward declarations
namespace sf
{
	class Sprite;
	class RenderWindow;
}

struct PopupImage
{
	sf::Sprite* sprite;
	sf::Vector2f speed;
	float maxTime;
	float currentTime;
	bool markedForDelete;
};

class PopupImageManager
{
public:
	PopupImageManager();
	~PopupImageManager();

	void addImage(std::string sheetName, std::string spriteName, sf::Vector2f position, sf::Vector2f speed, float maxTime);
	void update(float delta);
	void draw(sf::RenderWindow* window);

private:
	std::vector<PopupImage> m_images;
};

#endif
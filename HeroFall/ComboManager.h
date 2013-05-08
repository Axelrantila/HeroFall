#ifndef COMBOMANAGER_H
#define COMBOMANAGER_H

class ComboManager
{
public:
	static ComboManager* getInstance();

private:
	ComboManager();
	~ComboManager();

	void increaseComboMeter();
	void update(float delta);

	float m_comboMeter;
};

#endif
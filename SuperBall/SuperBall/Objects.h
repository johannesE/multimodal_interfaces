#pragma once
class Objects
{
public:
	Objects(void);
	~Objects(void);
	void setNewPos(int x, int y);
	int getposX();
	int getposY();

protected:
	int x, y; //the position of the objects
	int width, height; //the size of the objets
};


#pragma once
class Diamond
{

public:
	Diamond::Diamond();
	Diamond(int x, int y);
	~Diamond(void);
	int posX();
	int posY();
	void setNewPos(int x, int y);
	void Diamond::drawIt();  //called from the main loop

private:
	int x,y;
	
};


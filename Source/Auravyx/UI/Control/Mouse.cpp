#include "Auravyx/UI/Control/Mouse.h"
#include "Auravyx/Core/GameManager.h"
//#include "Server/ClientManager.h"
Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}
float tX, tY;

bool nnx, nny;

int prevX =9999999, prevY = 9999999;
void send(int x, int y, int id)
{
	
	nnx = false;
	nny = false;

	int cX = x / 16;
	int cY = y / 16;

	if (x < 0)
		nnx = true;
	if (y < 0)
		nny = true;
	if (nnx)
	{
		cX = (x + 1) / 16;
		cX -= 1;
	}
	if (nny)
	{
		cY = (y + 1) / 16;
		cY -= 1;
	}
	Chunk* c = GameManager::world.getChunk(cX, cY, 0);
	if (c != nullptr)
	{
		//PacketTileChange p;
		//p.write(cX, cY, 0, (x - cX * 16) * 16 + (y - cY * 16), id);
		//ClientManager::send(Packet::Type::TILE_CHANGE, p.pData);
	}
	prevX = x;
	prevY = y;
}

void Mouse::update(const World& world)
{
	/*if (tX < 0)
	{
		tX -= 1;
		tX = ceil(tX);
	}
	if (tY < 0)
	{
		tY -= 1;
		tY = ceil(tY);
	}
	int x = tX;
	int y = tY;
	if (WindowManager::getWindow()->getController()->isMouseDown(GLFW_MOUSE_BUTTON_LEFT))
	{
		if (x != prevX || y != prevY)
		{
			send(x, y, 5);
		}
	}
	if (WindowManager::getWindow()->getController()->isMouseDown(GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (x != prevX || y != prevY)
		{
			send(x, y,0);
		}
	}*/
}
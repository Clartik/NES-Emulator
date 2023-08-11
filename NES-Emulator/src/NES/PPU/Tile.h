#pragma once

#include <stdint.h>

const unsigned int PLANE_SIZE = 8;

class Tile
{
public:
	Tile(uint8_t* data);
	~Tile();

	//uint8_t* GetTile();
private:
	uint8_t m_Plane1[PLANE_SIZE], m_Plane2[PLANE_SIZE];
};
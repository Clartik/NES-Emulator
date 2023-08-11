#include "Tile.h"

#include <cstring>

Tile::Tile(uint8_t* data)
{
	memcpy(m_Plane1, data, PLANE_SIZE);
	data += PLANE_SIZE;
	memcpy(m_Plane2, data, PLANE_SIZE);
}

Tile::~Tile()
{
}

//uint8_t* Tile::GetTile()
//{
//	uint8_t tile[PLANE_SIZE];
//
//	for (int i = 0; i < PLANE_SIZE; i++)
//	{
//
//	}
//}

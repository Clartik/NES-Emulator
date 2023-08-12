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

uint8_t* Tile::GetTile()
{
	uint8_t tile[PLANE_SIZE * PLANE_SIZE];

	for (int row = 0; row < PLANE_SIZE; row++)
	{
		const uint8_t byte1 = m_Plane1[row];
		const uint8_t byte2 = m_Plane2[row];
		for (int column = 0; column < PLANE_SIZE; column++)
		{
			bool value1 = byte1 & (0x01 << column);
			bool value2 = byte2 & (0x01 << column);

			if (value1 && value2)
			{
				tile[row * PLANE_SIZE + column] = 3;
				continue;
			}

			if (value1 && !value2)
			{
				tile[row * PLANE_SIZE + column] = 1;
				continue;
			}

			if (!value1 && value2)
			{
				tile[row * PLANE_SIZE + column] = 2;
				continue;
			}

			tile[row * PLANE_SIZE + column] = 0;
		}
	}

	return tile;
}

#pragma once

#include <stdint.h>

#include "Tile.h"

const unsigned int PATTERN_TABLE_TILE_AMOUNT = 256;
const unsigned int PATTERN_TABLE_SIZE = TILE_SIZE * PATTERN_TABLE_TILE_AMOUNT;

class PatternTable
{
public:
	PatternTable(uint8_t* data);
	~PatternTable();
private:
	Tile m_Tiles[PATTERN_TABLE_TILE_AMOUNT];
};
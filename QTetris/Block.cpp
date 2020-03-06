#include "Block.h"

//**************
//**BLOCK*******
//**************

Block::Block(char block[4][4], BlockColor color)
{
	this->block = new char*[4];
	for (int i = 0; i < 4; i++)
		this->block[i] = new char[4];
	
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			this->block[i][j] = block[i][j];

	this->color = color;
}

Block::Block(const Block& ob)
{
	block = new char*[4];
	for (int i = 0; i < 4; i++)
		block[i] = new char[4];

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			block[i][j] = ob.block[i][j];

	color = ob.color;
}

Block& Block::operator= (const Block& ob)
{
	block = new char*[4];
	for (int i = 0; i < 4; i++)
		block[i] = new char[4];

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			block[i][j] = ob.block[i][j];

	color = ob.color;

	return *this;
}

Block::~Block()
{
	for (int i = 0; i < 4; i++)
		delete[] block[i];

	delete[] block;
}

void Block::rotateBy90()
{
	char temp[4][4];

	for (int i = 0; i < 4; i++)
		for (int j = 3, k = 0; j >= 0; j--, k++)
			temp[i][k] = block[j][i];

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			block[i][j] = temp[i][j];
	alignMatrix();
}

void Block::alignMatrix()
{
	//Vertical align
	bool vAlign = false;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[0][j])
			{
				vAlign = true;
				break;
			}
		}
		if (vAlign) break;
		else upMatrix();
	}

	//Horizontal align
	bool hAlign = false;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[j][0])
			{
				hAlign = true;
				break;
			}
		}
		if (hAlign) break;
		else leftMatrix();
	}
}

void Block::upMatrix()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			block[i][j] = block[i + 1][j];
			if (i == 2) block[3][j] = 0;
		}
	}
}

void Block::leftMatrix()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			block[j][i] = block[j][i + 1];
			if (i == 2) block[j][3] = 0;
		}
	}
}

//GETTERS SETTERS
char** Block::getBlock()
{
	return block;
}

BlockColor Block::getColor()
{
	return color;
}

//**************
//**REGISTRY****
//**************

vector<Block> Registry::registry;

vector<Block>& Registry::getRegistry()
{
	if (registry.empty())
	{
		char matrI[4][4] = { {1, 0, 0, 0},
							 {1, 0, 0, 0},
							 {1, 0, 0, 0},
							 {1, 0, 0, 0}, };
		registry.emplace_back(matrI, cyan);

		char matrO[4][4] = { {1, 1, 0, 0},
							 {1, 1, 0, 0},
							 {0, 0, 0, 0},
							 {0, 0, 0, 0}, };
		registry.emplace_back(matrO, yellow);

		char matrT[4][4] = { {0, 1, 0, 0},
							 {1, 1, 1, 0},
							 {0, 0, 0, 0},
							 {0, 0, 0, 0}, };
		registry.emplace_back(matrT, purple);

		char matrS[4][4] = { {0, 1, 1, 0},
							 {1, 1, 0, 0},
							 {0, 0, 0, 0},
							 {0, 0, 0, 0}, };
		registry.emplace_back(matrS, green);

		char matrZ[4][4] = { {1, 1, 0, 0},
							 {0, 1, 1, 0},
							 {0, 0, 0, 0},
							 {0, 0, 0, 0}, };
		registry.emplace_back(matrZ, red);

		char matrJ[4][4] = { {1, 1, 0, 0},
							 {0, 1, 0, 0},
							 {0, 1, 0, 0},
							 {0, 0, 0, 0}, };
		registry.emplace_back(matrJ, blue);

		char matrL[4][4] = { {1, 1, 0, 0},
							 {1, 0, 0, 0},
							 {1, 0, 0, 0},
							 {0, 0, 0, 0}, };
		registry.emplace_back(matrL, orange);
	}

	return registry;
}
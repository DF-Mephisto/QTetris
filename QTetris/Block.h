#pragma once

#include <vector>

#include "BlockColor.h"

using namespace std;

class Block;

class Registry
{
public:
	static vector<Block>& getRegistry();
	Registry() = delete;

private:
	static vector<Block> registry;
};


class Block
{
public:
	Block(char block[4][4], BlockColor color);
	Block(const Block& ob);
	Block& operator= (const Block& ob);
	~Block();

	void rotateBy90();

	char** getBlock();
	BlockColor getColor();

private:
	void alignMatrix();
	void upMatrix();
	void leftMatrix();
	
private:
	char** block;
	BlockColor color;
};
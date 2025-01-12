#pragma once

#include <algorithm>
#include <vector>
#include <array>
#include <stack>

#include "tilemap.h"

struct Node
{
	int x, y;
	int parentX, parentY;
	float gCost;
	float hCost;
	float fCost;
};

bool IsValid(Tilemap &map, int x, int y);

bool IsDestination(int x, int y, Node destination);

float CalculateH(int x, int y, Node destination);

std::vector<Node> MakePath(std::array<std::array<Node, 25>, 21> &map, Node dest);

std::vector<Node> aStar(const Tilemap& theMap, const Node& enemy, const Node& dest);
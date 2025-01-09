#include "enemiesastarsearch.h"

#include <queue>
#include <iostream>
#include <fstream>

// Checks if the enemy can move to the position
// Basically finds out if it is a wall or outside the array bounds
bool IsValid(const Tilemap& theMap, int x, int y)
{
	if (x < 0 || x >= 25) {
		return false;
	}

	if (y < 0 || y >= 21) {
		return false;
	}

	if (theMap.MAP_DATA[y][x] == 1) {
		return false;
	}

	return true;
}

// Indicated if the position corresponds to the destination
bool IsDestination(int x, int y, Node destination)
{
	if (x == destination.x && y == destination.y) {
		return true;
	}

	return false;
}

// Works out the cost based on the location and destination
// The calculation is called the Manhattan distance
// It is one of the distance measures used in AI algorithms
float CalculateH(int x, int y, Node destination)
{
	int xDist = std::max(x, destination.x) - std::min(x, destination.x);
	int yDist = std::max(y, destination.y) - std::min(y, destination.y);

	return xDist + yDist;
}

// Work out a path to the destination
// It does this in reverse because the map is represented by a Node
// Node has a parent X and Y to know where the previous Node is for a given Node
// Starting from the destination it will work out a path to the enemy starting point
// Need a path from the start to the destination though so reverse the path
std::vector<Node> MakePath(std::array<std::array<Node, 25>, 21>& map, Node dest)
{
	// Stores the current path used
	std::vector<Node> usablePath;

	// Start at the destination
	int x = dest.x;
	int y = dest.y;

	// Find the nodes that make up the path
	// From the destination to the starting point
	// Starting point will be based on the location of the enemy
	while (!(map[y][x].parentX == x && map[y][x].parentY == y)
		&& map[y][x].x != -1 && map[y][x].y != -1)
	{
		// Puts the node into the list
		usablePath.push_back(map[y][x]);

		int tempX = map[y][x].parentX;
		int tempY = map[y][x].parentY;

		// Move to the parent for next pretition
		x = tempX;
		y = tempY;
	}

	// Push the starting node into the list
	usablePath.push_back(map[y][x]);

	// Reverse the list so path starts from the enemy
	std::reverse(usablePath.begin(), usablePath.end());

	// Return the correct path
	return usablePath;
}

// nodeDetails & closedList are helper data structures
// nodeDetails corresponds to the tilemap
// it stores the details about the search for each tile
// they are currently hardcoded to the tilemap of 25 x 21
std::array<std::array<Node, 25>, 21> nodeDetails;

// Indicates if a tile has been visited
// So the same node isn't visited
std::array< std::array<bool, 25>, 21> closedList;

// Used to represent no path
// Basically if the location can't be reached
std::vector<Node> emptyPath;

// Main algorithm
// Different types of pathfinding could find a path quicker
std::vector<Node> aStar(const Tilemap& theMap, const Node& enemy, const Node& dest)
{
	// Checks if the location selected is able to be accessed
	if (!IsValid(theMap, dest.x, dest.y))
	{
		return emptyPath;
	}

	// Check if the selected destination is the enemy
	if (IsDestination(enemy.x, enemy.y, dest))
	{
		return emptyPath;
	}

	// Initialise the helper arrays
	for (int y = 0; y < 21; y++)
	{
		for (int x = 0; x < 25; x++)
		{
			// Position
			nodeDetails[y][x].x = x;
			nodeDetails[y][x].y = y;

			// Max cost
			nodeDetails[y][x].fCost = FLT_MAX;
			nodeDetails[y][x].gCost = FLT_MAX;
			nodeDetails[y][x].hCost = FLT_MAX;

			// No parent yet
			nodeDetails[y][x].parentX = -1;
			nodeDetails[y][x].parentY = -1;

			// Not visited
			closedList[y][x] = false;
		}
	}
	

	// Open list is the list of nodes
	// That will be visited after moving to new location

	struct CompareF
	{
		bool operator()(const Node& a, const Node& b)
		{
			return a.fCost > b.fCost; // Min-heap
		}
	};

	using PriorityQueue = std::priority_queue<Node, std::vector<Node>, CompareF>;

	PriorityQueue openList;

	//std::vector<Node> openList;

	Node& startNode = nodeDetails[enemy.y][enemy.x];
	// Initialise the starting point the player pos
	startNode.x = enemy.x;
	startNode.y = enemy.y;

	// Initialise the starting point the player pos
	startNode.fCost = 0.0f;
	startNode.gCost = 0.0f;
	startNode.hCost = 0.0f;

	// Initialise the starting point the player pos
	startNode.parentX = enemy.x;
	startNode.parentY = enemy.y;

	// Put the start node into the open list to start the algorithm
	openList.push(nodeDetails[enemy.y][enemy.x]);
	//openList.push_back(nodeDetails[enemy.y][enemy.x]);

	// Indicates if the destination was found
	// Will be false until destination is reached
	bool found = false;

	// While there are nodes to process
	while (!openList.empty())
	{
		// Get a node from the list
		Node current = openList.top();
		//Node current = openList.front();

		// Remove the node so it isn't used again
		openList.pop();
		//openList.erase(openList.begin());

		// Indicate visited
		int X = current.x; // IsValidIndex(1, current.x, closedList.size()) - 1;
		int Y = current.y; // IsValidIndex(1, current.y, closedList[current.x].size()) - 1;

		closedList[Y][X] = true;

		// Is the current node the destination
		if (IsDestination(X, Y, dest))
		{
			// If it is found
			found = true;

			// Exit the loop
			break;
		}

		// Check four directions, Each code direction is mostly the same
		// Except for determining the next node to visit based on x,y and the direction of travel
		//
		// UP
		// Is the tile above accessible and hasn't been visited
		// Note, if your game allows player to move diagonally, e.g. Up and Right, then you'll have
		// to add code to check and move in that direction
		if (IsValid(theMap, current.x, current.y - 1) && !closedList[current.y - 1][current.x])
		{
			// Calculate the cost in terms of the distance from the node to the destination
			float gNew = nodeDetails[current.y][current.x].gCost + 1.0f;
			float hNew = CalculateH(current.x, current.y - 1, dest);
			float fNew = gNew + hNew;

			// Update the node with the cost if the current cost of the node is FLT_MAX (No Cost)
			// or this node is on a path that is better for reaching the destination
			if (nodeDetails[current.y - 1][current.x].fCost == FLT_MAX || nodeDetails[current.y - 1][current.x].fCost > fNew)
			{
				// Update the details of this neighbour node
				nodeDetails[current.y - 1][current.x].fCost = fNew;
				nodeDetails[current.y - 1][current.x].gCost = gNew;
				nodeDetails[current.y - 1][current.x].hCost = hNew;
				nodeDetails[current.y - 1][current.x].parentX = current.x;
				nodeDetails[current.y - 1][current.x].parentY = current.y;

				// Put it in the list for nect time
				openList.push(nodeDetails[current.y - 1][current.x]);
				//openList.push_back(nodeDetails[current.y - 1][current.x]);
			}
		}

		// RIGHT
		if (IsValid(theMap, current.x + 1, current.y) && !closedList[current.y][current.x + 1]) {
			float gNew = nodeDetails[current.y][current.x].gCost + 1.0f;
			float hNew = CalculateH(current.x + 1, current.y, dest);
			float fNew = gNew + hNew;

			if (nodeDetails[current.y][current.x + 1].fCost == FLT_MAX || nodeDetails[current.y][current.x + 1].fCost > fNew) {
				// Update the details of this neighbour node
				nodeDetails[current.y][current.x + 1].fCost = fNew;
				nodeDetails[current.y][current.x + 1].gCost = gNew;
				nodeDetails[current.y][current.x + 1].hCost = hNew;
				nodeDetails[current.y][current.x + 1].parentX = current.x;
				nodeDetails[current.y][current.x + 1].parentY = current.y;

				openList.push(nodeDetails[current.y][current.x + 1]);
				//openList.push_back(nodeDetails[current.y][current.x + 1]);
			}
		}

		// DOWN
		if (IsValid(theMap, current.x, current.y + 1) && !closedList[current.y + 1][current.x]) {
			float gNew = nodeDetails[current.y][current.x].gCost + 1.0f;
			float hNew = CalculateH(current.x, current.y + 1, dest);
			float fNew = gNew + hNew;

			if (nodeDetails[current.y + 1][current.x].fCost == FLT_MAX || nodeDetails[current.y + 1][current.x].fCost > fNew) {
				// Update the details of this neighbour node
				nodeDetails[current.y + 1][current.x].fCost = fNew;
				nodeDetails[current.y + 1][current.x].gCost = gNew;
				nodeDetails[current.y + 1][current.x].hCost = hNew;
				nodeDetails[current.y + 1][current.x].parentX = current.x;
				nodeDetails[current.y + 1][current.x].parentY = current.y;

				openList.push(nodeDetails[current.y + 1][current.x]);
				//openList.push_back(nodeDetails[current.y + 1][current.x]);
			}
		}

		// LEFT
		if (IsValid(theMap, current.x - 1, current.y) && !closedList[current.y][current.x - 1]) {
			float gNew = nodeDetails[current.y][current.x].gCost + 1.0f;
			float hNew = CalculateH(current.x - 1, current.y, dest);
			float fNew = gNew + hNew;

			if (nodeDetails[current.y][current.x - 1].fCost == FLT_MAX || nodeDetails[current.y][current.x - 1].fCost > fNew) {
				// Update the details of this neighbour node
				nodeDetails[current.y][current.x - 1].fCost = fNew;
				nodeDetails[current.y][current.x - 1].gCost = gNew;
				nodeDetails[current.y][current.x - 1].hCost = hNew;
				nodeDetails[current.y][current.x - 1].parentX = current.x;
				nodeDetails[current.y][current.x - 1].parentY = current.y;

				openList.push(nodeDetails[current.y][current.x - 1]);
				//openList.push_back(nodeDetails[current.y][current.x - 1]);
			}
		}
	}

	// Out of loop.  Was the destination found?
	if (found) {
		// Yes, then create the path for the current node state
		return MakePath(nodeDetails, dest);
	}
	else {
		// No, return no path
		return emptyPath;
	}
}
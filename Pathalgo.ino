const int totalNodes = 12;
const int totalPaths = 18;

struct Node {
  int id;
  int heuristic;
  int gScore;
};

struct Edge {
  int from;
  int to;
  int cost;
  bool isWaterBlocked;
};

Edge paths[18] = {
  {12, 23, 1, false}, {23, 34, 1, false}, {34, 45, 1, false},
  {45, 16, 1, false}, {16, 36, 1, false}, {36, 73, 1, false},
  {73, 74, 1, false}, {74, 84, 1, false}, {84, 85, 1, false},
  {85, 9, 1, false}, {9, 10, 1, false}, {10, 11, 1, false},
  {11, 12, 1, false}, {7, 10, 1, false}, {8, 11, 1, false},
  {5, 12, 1, false}, {6, 10, 1, false}, {7, 8, 1, false}
};

int calculateHeuristic(int currentNode, int goalNode) {
  // Replace this with your own heuristic calculation based on the goal node
  return 0;
}

void aStar(int startNode, int goalNode) {
  Node openSet[totalNodes];
  int openSetSize = 0;
  Node closedSet[totalNodes];
  int closedSetSize = 0;

  openSet[openSetSize++] = {startNode, calculateHeuristic(startNode, goalNode), 0};

  while (openSetSize > 0) {
    int currentIdx = 0;
    for (int i = 1; i < openSetSize; ++i) {
      if (openSet[i].gScore + openSet[i].heuristic < openSet[currentIdx].gScore + openSet[currentIdx].heuristic) {
        currentIdx = i;
      }
    }

    Node current = openSet[currentIdx];
    if (current.id == goalNode) {
      // Goal reached, implement your desired actions here
      break;
    }

    // Move current node from open set to closed set
    for (int i = currentIdx; i < openSetSize - 1; ++i) {
      openSet[i] = openSet[i + 1];
    }
    openSetSize--;

    // Loop through neighbors
    for (int i = 0; i < totalPaths; ++i) {
      if (paths[i].from == current.id && !paths[i].isWaterBlocked) {
        int neighbor = paths[i].to;
        int tentativeGScore = current.gScore + paths[i].cost;

        // Check if neighbor is in closed set
        bool inClosedSet = false;
        for (int j = 0; j < closedSetSize; ++j) {
          if (closedSet[j].id == neighbor) {
            inClosedSet = true;
            break;
          }
        }

        // Check if neighbor is in open set or not
        int neighborIdx = -1;
        for (int j = 0; j < openSetSize; ++j) {
          if (openSet[j].id == neighbor) {
            neighborIdx = j;
            break;
          }
        }

        if (!inClosedSet || (inClosedSet && tentativeGScore < closedSet[neighborIdx].gScore)) {
          if (!inClosedSet) {
            openSet[openSetSize++] = {neighbor, calculateHeuristic(neighbor, goalNode), 0};
          }
          openSet[openSetSize - 1].gScore = tentativeGScore;
        }
      }
    }

    // Move current node to closed set
    closedSet[closedSetSize++] = current;
  }
}

void modifyWaterBlockage(int pathIndex, bool isBlocked) {
  paths[pathIndex].isWaterBlocked = isBlocked;
}

void setup() {
  // Initialize your setup code here
}

void loop() {
  // Call your A* star function with appropriate start and goal nodes
  aStar(12, 48);

  // Modify water blockage if needed
  modifyWaterBlockage(6, true);  // Example: block the path from 73 to 74

  // Add your loop code here
}

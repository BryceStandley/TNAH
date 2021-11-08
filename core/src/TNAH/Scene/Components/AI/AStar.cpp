#include "tnahpch.h"
#include "AStar.h"

namespace tnah
{
        //Just checking it is in bounds atm not for any obstacles
         bool AStar::IsValid(Int2 point)
        {
            if(usedPositions[point.x][point.y])
                return false;
            
            if (point.x < startingPos.x || point.y < startingPos.y || point.x > startingPos.x + size.x || point.y > startingPos.y + size.y)
            {
                return false;
            }
            else
                return true;
        }

         void AStar::Update()
        {
            for(Int2 values : usedPositionsHolder)
            {
                usedPositions[values.x][values.y] = false;
            }

             usedPositionsHolder.clear();
        }
        
         bool AStar::Reached(Int2 point, Node destination)
        {
            if (point.CheckSame(destination.position))
            {

                return true;
            }

            return false;
        }

         double AStar::heuristic(Int2 point, Node destination)
        {
            double H = (sqrt((point.x - destination.position.x)*(point.x - destination.position.x)
                + (point.y - destination.position.y)*(point.y - destination.position.y)));
            return H;
        }
        
         void AStar::Init(Int2 startingPosition, Int2 xySize)
        {
            startingPos = startingPosition;
            size = xySize;
            initilised = true;
            for (int x = startingPos.x; x < startingPos.x + size.x; x++) {
                for (int y = startingPos.y; y < startingPos.y + size.y; y++) {
                    astarMap[x][y].f= FLT_MAX;
                    astarMap[x][y].g = FLT_MAX;
                    astarMap[x][y].h = FLT_MAX;
                    astarMap[x][y].parent =  {-1, -1};
                    astarMap[x][y].position = {x, y};
                }
            }
        }
        
         std::deque<Node> AStar::Algorithm(Node point, Node destination)
        {
            if(!initilised)
            {
                return {};    
            }
            
            if(!IsValid(destination.position))
            {
                return {};
            }
            if(!IsValid(point.position))
            {
                return {};
            }
            if(Reached(point.position, destination))
            {
                return {};
            }

            for (int x = startingPos.x; x < startingPos.x + size.x; x++) {
                for (int y = startingPos.y; y < startingPos.y + size.y; y++) {
                    astarMap[x][y].f= FLT_MAX;
                    astarMap[x][y].g = FLT_MAX;
                    astarMap[x][y].h = FLT_MAX;
                    astarMap[x][y].parent =  {-1, -1};
                    astarMap[x][y].position = {x, y};
                    closedList[x][y] = false;
                }
            }
            
            Int2 position = point.position;
            astarMap[position.x][position.y].f = 0.0;
            astarMap[position.x][position.y].g = 0.0;
            astarMap[position.x][position.y].h = 0.0;
            astarMap[position.x][position.y].parent = position;

            std::vector<Node> searchList;  
            searchList.emplace_back(astarMap[position.x][position.y]);

            while (!searchList.empty()) {
                Node node;
                do {
                    float t = FLT_MAX;
                    std::vector<Node>::iterator iteratorNode;
                    for (std::vector<Node>::iterator it = searchList.begin();
                        it != searchList.end(); it = next(it)) {
                        Node n = *it;
                        if (n.f < t) {
                            t = n.f;
                            iteratorNode = it;
                        }
                        }
                    node = *iteratorNode;
                    searchList.erase(iteratorNode);
                } while (IsValid(node.position) == false);

                position = node.position;
                
                closedList[position.x][position.y] = true;
                
                for (int x = -1; x <= 1; x++) {
                    for (int y = -1; y <= 1; y++) {
                        if (IsValid(Int2(position.x + x, position.y + y))) {
                            if (Reached(Int2(position.x + x, position.y + y), destination))
                            {
                                astarMap[position.x + x][position.y + y].parent = {position.x, position.y};
                                return makePath(astarMap, destination);
                            }
                            else if (closedList[position.x + x][position.y + y] == false)
                            {
                                float gNew;

                                if(x == y){
                                    gNew = node.g + 1.5f;
                                }
                                else {
                                    gNew = node.g + 1.0f;
                                }

                                const float heuristicNew = (float)heuristic(Int2((int)position.x + x, (int)position.y + y), destination);
                                const float fNew = gNew + heuristicNew;
                                if (astarMap[position.x + x][position.y + y].f == FLT_MAX || astarMap[position.x + x][position.y + y].f > fNew)
                                {
                                    astarMap[position.x + x][position.y + y].f = fNew;
                                    astarMap[position.x + x][position.y + y].g = gNew;
                                    astarMap[position.x + x][position.y + y].h = heuristicNew;
                                    astarMap[position.x + x][position.y + y].parent = {position.x, position.y};
                                    searchList.emplace_back(astarMap[position.x + x][position.y + y]);
                                }
                            }
                        }
                    }
                }
            }
            
                return {};
        }

         std::deque<Node> AStar::makePath(std::unordered_map<int, std::unordered_map<int, Node>> map, Node destination) 
         {
            int x = destination.position.x;
            int y = destination.position.y;
            std::stack<Node> path;
            std::deque<Node> usablePath;

            while (!(map[x][y].parent.x == x && map[x][y].parent.y == y))
            {
                if(x == 0 && y == 0)
                {
                    return {};
                }
                path.push(map[x][y]);
                int tempX = map[x][y].parent.x;
                int tempY = map[x][y].parent.y;
                x = tempX;
                y = tempY;

            }
            path.push(map[x][y]);

            while (!path.empty()) {
                Node top = path.top();
                path.pop();
                usablePath.push_back(top);
            }
            return usablePath;
  
        }

         Node AStar::GenerateRandomPosition(Int2 currentPosition)
        {
             bool notFound = false;
            while(!notFound)
            {
                std::random_device d;
                std::mt19937 gen(d());
                std::uniform_int_distribution<int> xRand(startingPos.x,  startingPos.x + size.x-1);
                std::uniform_int_distribution<int> yRand(startingPos.y,  startingPos.y + size.y-1);
                Int2 newPos(xRand(gen), yRand(gen));
                
                if(!newPos.CheckSame(currentPosition) && IsValid(newPos))
                {
                    return newPos;
                    notFound = true;   
                }
            }
            return Int2(0, 0);
        }
         std::unordered_map<int, std::unordered_map<int, Node>> AStar::GetMapPoints()
        {
            if(!generated)
            {
                for (int x = startingPos.x; x < startingPos.x + size.x; x++) {
                    for (int y = startingPos.y; y < startingPos.y + size.y; y++) {
                        astarMap[x][y].parent =  {-1, -1};
                        astarMap[x][y].position = {x, y};
                    }
                }
                generated = true;
            }

            return astarMap;
        }

         std::unordered_map<int, std::unordered_map<int, bool>> AStar::GetUsedPoints()
        {
            return usedPositions;
        }

         void AStar::AddUsedPosition(Int2 position, bool dynamic)
        {
            usedPositions[position.x][position.y] = true;

            if(dynamic)
                usedPositionsHolder.push_back(position);
            
            /*usedPositions[position.x-1][position.y] = true;
            usedPositions[position.x+1][position.y] = true;
            usedPositions[position.x][position.y-1] = true;
            usedPositions[position.x][position.y+1] = true;*/
        }
        
     Int2 AStar::GetStartingPos()
        {
            return startingPos;
        }

     Int2 AStar::GetEndPosition()
        {
            return Int2(startingPos.x + size.x, startingPos.y + size.y);
        }
}
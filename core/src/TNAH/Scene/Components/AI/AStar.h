/*****************************************************************//**
 * @file   AStar.h
 * @brief  Astar algorithm
 * 
 * @author chris
 * @date   November 2021
 *********************************************************************/
#pragma once
#include <stack>

namespace tnah
{
    /** Int2 struct */
    struct Int2
    {
        int x;
        int y;
        
        Int2(int o = 0, int t = 0) : x(o), y(t) {}
        bool CheckSame(Int2 other)
        {
            if(x == other.x && y == other.y)
                return true;

            return false;
        }
    };

    /** Astar obstacle component */
    struct AStarObstacleComponent
    {
        AStarObstacleComponent() = default;
        AStarObstacleComponent(bool b) : dynamic(b) {}
        /** If the object is dynamic or not */
        bool dynamic = false;
    private:
        inline static std::string s_SearchString = "AStar Obstacle Component";
        /** @brief	Type identifiers for the component */
        inline static ComponentTypes s_Types = {
            {ComponentVariations::AStarObstacle},
{{ComponentCategory::Objects}}
        };
        friend class EditorUI;
    };
    
    /** The node for the object */
    struct Node
    {
        Int2 position;
        Int2 parent;

        float f;
        float g;
        float h;

        Node(Int2 p = {0, 0}) : position(p), parent(-1, -1), f(-1), g(-1), h(-1)
        {}
    };

    inline bool operator < (const Node& left, const Node & right)
    {
        return left.f < right.f;
    }
    
    class AStar
    {
    public:
        AStar() {}
        ~AStar() = default;
        
        /**
         *
         * @fn IsValid
         * @brief Checks if the given point is valid
         * 
         * @param point
         * @return bool
         * @author chris
         */
        static bool IsValid(Int2 point);

        /**
         *
         * @fn Update
         * @brief Updates the dynamic positions
         * 
         * @author chris
         */
        static void Update();
        
        /**
         *
         * @fn Reached
         * @brief Checks if the position is reached
         * 
         * @param point
         * @param destination
         * @return 
         * @author chris
         */
        static bool Reached(Int2 point, Node destination);

        /**
         *
         * @fn heuristic
         * @brief Gets the H value using square root
         * 
         * @param point
         * @param destination
         * @return 
         * @author chris
         */
        static double heuristic(Int2 point, Node destination);
        
        /**
         *
         * @fn Init
         * @brief Initilises the astar map
         * 
         * @param startingPosition
         * @param xySize
         * @author chris
         */
        static void Init(Int2 startingPosition, Int2 xySize);
        
        /**
         *
         * @fn Algorithm
         * @brief DOes the algorithm calling make path
         * 
         * @param point
         * @param destination
         * @return 
         * @author chris
         */
        static std::deque<Node> Algorithm(Node point, Node destination);

        /**
         *
         * @fn GenerateRandomPosition
         * @brief Generates a random position on the map
         * 
         * @param currentPosition
         * @return 
         * @author chris
         */
        static Node GenerateRandomPosition(Int2 currentPosition);
        
        /**
         *
         * @fn GetMapPoints
         * @brief Gets the map points
         * 
         * @return 
         * @author chris
         */
        static std::unordered_map<int, std::unordered_map<int, Node>> GetMapPoints();

        /**
         *
         * @fn GetUsedPoints
         * @brief Gets the map points taht are obstacles
         * 
         * @return 
         * @author chris
         */
        static std::unordered_map<int, std::unordered_map<int, bool>> GetUsedPoints();

        /**
         *
         * @fn AddUsedPosition
         * @brief Adds the given position to the used map, and adds it to the dynamic one if dynamic
         * 
         * @param position
         * @param dynamic
         * @author chris
         */
        static void AddUsedPosition(Int2 position, bool dynamic);
        
        /**
         *
         * @fn GetStartingPos
         * @brief Gets the starting position
         * 
         * @return 
         * @author chris
         */
        static Int2 GetStartingPos();

        /**
         *
         * @fn GetEndPosition
         * @brief Gets the end position
         * 
         * @return 
         * @author chris
         */
        static Int2 GetEndPosition();
    
    private:
        /**
         *
         * @fn makePath
         * @brief Creates the path used in the algorithm
         *
         * @param map
         * @param destination
         * @return
         * @author chris
         */
        static std::deque<Node> makePath(std::unordered_map<int, std::unordered_map<int, Node>> map, Node destination);
        /**  If it is initilised*/
        inline static bool initilised = false;
        /**  The starting position*/
        inline static Int2 startingPos = {0, 0};
        /** The overall size */
        inline static Int2 size = {10, 10};
        /** If it has been generated  */
        inline static bool generated = false;
        /**  The map holding the closed list*/
        inline static std::unordered_map<int, std::unordered_map<int, bool>> closedList = std::unordered_map<int, std::unordered_map<int, bool>>();
        /**  The map holding the used position*/
        inline static std::unordered_map<int, std::unordered_map<int, bool>> usedPositions = std::unordered_map<int, std::unordered_map<int, bool>>();
        /** The map holding the overall map */
        inline static std::unordered_map<int, std::unordered_map<int, Node>> astarMap = std::unordered_map<int, std::unordered_map<int, Node>>();
        /**  The vector holding the dynamic positions*/
        inline static std::vector<Int2> usedPositionsHolder = std::vector<Int2>();
    };

    struct AStarComponent
    {
        AStarComponent() = default;
        AStarComponent(Int2 pos, Int2 s) : StartingPos(pos), Size(s) {}
        AStarComponent(const AStarComponent &copy)
        {
            StartingPos = copy.StartingPos;
            Size = copy.Size;
        }
        /**  */
        Int2 StartingPos = {0, 0};
        /**  */
        Int2 Size = {5, 5};
        /**  */
        bool DisplayMap = false;
        /**  */
        bool reset = true;
    private:
        inline static std::string s_SearchString = "AStar Component";
        /** @brief	Type identifiers for the component */
        inline static ComponentTypes s_Types = {
            {ComponentVariations::AStar},
{{ComponentCategory::Objects}}
        };
        friend class EditorUI;
    };
}

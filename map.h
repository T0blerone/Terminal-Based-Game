#ifndef MAP_H
#define MAP_H

#include <iostream>

using namespace std;

class Map{
private:
    const char UNEXPLORED = '-'; // marker for unexplored spaces
    const char EXPLORED = ' ';   // marker for explored spaces
    const char ROOM = 'R';       // marker for room locations
    const char NPC = 'N';        // marker for NPC locations
    const char PARTY = 'X';      // marker for party position
    const char EXIT = 'E';       // marker for dungeon exit

    static const int num_rows_ = 12; // number of rows in map
    static const int num_cols_ = 12; // number of columns in map
    static const int max_npcs_ = 5;  // max non-player characters
    static const int max_rooms_ = 5; // max number of rooms

    char current_space;

    int player_position_[2];              // player position (row,col)
    int dungeon_exit_[2];                 // exit location of the dungeon
    int npc_positions_[max_npcs_][3];     // stores the (row,col) positions of NPCs present on map and if they have been found
    int room_positions_[max_rooms_][2];   // stores the (row,col) positions of rooms present on map
    char map_data_[num_rows_][num_cols_]; // stores the character that will be shown at a given (row,col)

    int npc_count_;  // stores number of misfortunes currently on map
    int room_count_; // stores number of sites currently on map
    int rooms_explored_;
public:
    Map();

    void resetMap();

    // getters
    int getPlayerRow(); //Returns players row
    int getPlayerCol(); //Returns players col
    int getDungeonExitRow(); //Returns exits location row
    int getDungeonExitCol();//Returns exits location col
    int getRoomCount(); //How many rooms are left
    int getNPCCount();//How many NPCS have been found
    int getNumRows(); 
    int getNumCols();
    bool isOnMap(int row, int col);
    bool isNPCLocation(int row, int col); //Checks if a location is a NPC
    bool isRoomLocation(int row, int col);//Checks if a location is a room
    bool isExplored(int row, int col); //Checks if a space is explored.
    bool isFreeSpace(int row, int col); 
    bool isDungeonExit(int row, int col); //Checks if a space is the exit.
    int getRoomsExplored(); //The number of rooms explored.

    // setters
    void setPlayerPosition(int row, int col); //Sets the players location
    void setDungeonExit(int row, int col); //Sets the dungeon exit space

    // other
    void displayMap(); //Outputs the map
    bool move(char); //Moves the player in the direction they chose
    bool addNPC(int row, int col);//Adds an npc at a locatino
    void seeNPC(int row, int col); //Makes the nPC visible
    bool addRoom(int row, int col); //Adds a room at location
    bool removeNPC(int row, int col); //Removes an NPC
    bool removeRoom(int row, int col); //Removes a room
    void exploreSpace(int row, int col); //Explores the space
};

#endif
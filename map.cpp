#include "map.h"
#include <cstdlib>
#include <time.h>

//Constructors
    Map::Map(){
        //Sets characters starting position in the top left
        player_position_[0] = 0;
        player_position_[1] = 0;
        
        //Sets the dungeon exit square, randomly on the bottom row.
        dungeon_exit_[0] = 11;
        srand(time(NULL));
        dungeon_exit_[1] = rand() % 12;

        for(int i = 0; i < 12; i++){
            for(int j = 0; j < 12; j++){
                map_data_[i][j] = '-';
            }
        }

        map_data_[dungeon_exit_[0]][dungeon_exit_[1]] = 'E';

        npc_count_ = 0;
        room_count_ = 0;
        rooms_explored_ = 0;
        
    }

    //Getters
    int Map::getPlayerRow(){
        return player_position_[0];
    }

    int Map::getPlayerCol(){
        return player_position_[1];
    }

    int Map::getDungeonExitRow(){
        return dungeon_exit_[0];
    }

    int Map::getDungeonExitCol(){
        return dungeon_exit_[1];
    }

    int Map::getRoomCount(){
        return room_count_;
    }

    int Map::getNPCCount(){
        return npc_count_;
    }

    int Map::getNumRows(){
        return num_rows_;
    }

    int Map::getNumCols(){
        return num_cols_;
    }

    bool Map::isOnMap(int row, int col){
        return true;
    }

    bool Map::isNPCLocation(int row, int col){
        for(int i = 0; i < 5; i++){
            if(npc_positions_[i][0] == row && npc_positions_[i][1] == col){
                return true;
            }
        }
    return false;
    }

    bool Map::isRoomLocation(int row, int col){
         for(int i = 0; i < 5; i++){
            if(room_positions_[i][0] == row && room_positions_[i][1] == col){
                return true;
            }
        }
    return false;
    }

    bool Map::isExplored(int row, int col){
        if(map_data_[row][col] == ' '){
            return true;
        }
        else {
            return false;
        }
    }

    bool Map::isFreeSpace(int row, int col){
return true;
    }

    bool Map::isDungeonExit(int row, int col){
        if(dungeon_exit_[0] == row && dungeon_exit_[1] == col){
            return true;
        }
        else {
            return false;
        }
    }

    int Map::getRoomsExplored(){
        return rooms_explored_;
    }

    //Setters

    void Map::setPlayerPosition(int row, int col){
        player_position_[0] = row;
        player_position_[1] = col;
    }

    void Map::setDungeonExit(int row, int col){
        dungeon_exit_[0] = row;
        dungeon_exit_[1] = col;
    }

    

    //Other
    void Map::displayMap(){
        for(int i = 0; i < num_rows_; i++){
            for(int j = 0; j < num_cols_; j++){
                if(i == getPlayerRow() && j == getPlayerCol()){
                    cout << "X";
                }
                else {
                    cout << map_data_[i][j];
                }
                
            }
            cout << endl;
        }
    }

    bool Map::move(char direction){
        switch(direction){ //Moves the character based on the direction specified, returns false if invalid.
            case 'w':   
                if(player_position_[0] == 0){
                    cout << "You cannot move this way!" << endl;
                    return false;
                }
                else {
                    player_position_[0]--;
                    return true;
                }                
            break;

            case 'a':
                if(player_position_[1] == 0){
                    cout << "You cannot move this way!" << endl;
                    return false;
                }
                else {
                    player_position_[1]--;
                    return true;
                }
            break;

            case 's':
                if(player_position_[0] == 11){
                    cout << "You cannot move this way!" << endl;
                    return false;
                }
                else {
                    player_position_[0]++;                
                    return true;    
                }                
            break;

            case 'd':
                if(player_position_[1] == 11){
                    cout << "You cannot move this way!" << endl;
                    return false;
                }
                else {
                    player_position_[1]++;
                return true;
                }                
            break;

            default:
                return false;
            break;
        }
    }

    bool Map::addNPC(int row, int col){
        if(isNPCLocation(row,col) == true){
            return false;
        }
        npc_positions_[npc_count_][0] = row;
        npc_positions_[npc_count_][1] = col;
        npc_positions_[npc_count_][2] = 0;
        npc_count_++;
        return true;
    }

    void Map::seeNPC(int row, int col){
        map_data_[row][col] = 'N';
    }

    bool Map::addRoom(int row, int col){
        if(isRoomLocation(row,col) == true){
            return false;
        }
        room_positions_[room_count_][0] = row;
        room_positions_[room_count_][1] = col;
        room_count_++;
        map_data_[row][col] = 'R';
        return true;
    }

    bool Map::removeNPC(int row, int col){
        if(isNPCLocation(row, col) == false){
            return false;
        }
        npc_count_--;
        map_data_[row][col] = ' ';
        return true;
    }

    bool Map::removeRoom(int row, int col){
        if(isRoomLocation(row, col) == false){
            return false;
        }
        room_count_--;
        map_data_[row][col] = ' ';
        return true;
    }

    void Map::exploreSpace(int row, int col){
        map_data_[row][col] = ' ';
        rooms_explored_++;
    }




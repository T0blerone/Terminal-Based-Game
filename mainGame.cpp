#include <iostream>
#include <string>
#include "party.h"
#include "map.h"
#include <fstream>
using namespace std;

void gameStart(Party &my_party){
    string playername; //Initializes variables to take input for player names.
    string member1;
    string member2;
    string member3;
    string member4;

    cout << "Please enter the players name: " << endl; //Takes players name
    cin >> playername;

    cout << "Please enter the four members of your parties names (seperated by a space)" << endl; //Takes members names
    cin >> member1 >> member2 >> member3 >> member4;

    my_party.setPlayerName(playername); //Sets player and members names.
    my_party.setMemberName(0, member1);
    my_party.setMemberName(1, member2);
    my_party.setMemberName(2, member3);
    my_party.setMemberName(3, member4);
    
}

void gameOver(Party &my_party, Map &game_map){
    //Outputs Party Info
    cout <<"+-------------+\n" << "| PARTY       |\n" << "+-------------+\n";
    cout << "| " << my_party.getPlayerName() << " | Fullness: " << my_party.getPlayerFullness() << endl;
    for(int i = 0; i < my_party.getLivingMembers(); i++){
        cout << "| " << my_party.getMemberName(i) << " | Fullness: " << my_party.getMemberFullness(i) << endl;
    }
    cout << "+-------------+" << endl << endl;

    cout <<"+-------------+\n" << "| STATS       |\n" << "+-------------+\n";
    cout << "| Gold: " << my_party.getGoldBalance() << endl;
    cout << "| Rooms Cleared: " << my_party.getRoomsCleared() << endl;
    cout << "| Treasures | " << "R: " << my_party.getTreasures(0) << " | N: " << my_party.getTreasures(1) << " | B: " << my_party.getTreasures(2) 
        << " | C: " << my_party.getTreasures(3) << " | G: " << my_party.getTreasures(4) << endl;
    cout << "Rooms Explored: " << game_map.getRoomsExplored() << endl;
    cout << "Monsters Defeated: " << my_party.getMonstersDefeated() << endl;
    cout << "Turns Taken: " << endl;

}

void generateMap(Map &game_map){

    //Sets npc positions and position on map
        srand(time(NULL));
        rand();

        int row = 0;
        int col = 0;

        for(int i = 0; i < 5;){ //Adds all five NPC's
            row = rand() % 12;
            col = rand() % 12;
            if(!game_map.isNPCLocation(row, col) && !game_map.isDungeonExit(row, col)){ //Checks that it isn't already an NPC space or the exit space
                game_map.addNPC(row, col);
                i++;
            }
        }

        //Sets room positions and position on map
        for(int i = 0; i < 5;){
            row = rand() % 12;
            col = rand() % 12;
            if(!game_map.isRoomLocation(row, col) && !game_map.isNPCLocation(row, col) && !game_map.isDungeonExit(row, col)){ //Cehcks the space isn't an NPC, room, or exit already
                game_map.addRoom(row, col);
                i++;
            }
        }
}

void statusUpdate(Party &my_party){
    //Outputs Rooms Cleared:
    cout << "+-------------+\n" << "| STATUS      |\n" << "+-------------+\n";
    cout << "| Rooms Cleared: " << my_party.getRoomsCleared() << " | Keys: " << my_party.getKeys() << " | Anger Level: " << my_party.getAngerLevel() << endl;

    //Outputs Inventory
    cout << "+-------------+\n" << "| INVENTORY   |\n" << "+-------------+\n";
    cout << "| Gold        | " << my_party.getGoldBalance() << endl;
    cout << "| Ingredients | " << my_party.getIngredientsBalance() << endl;
    cout << "| Cookware    | " << "P: " << my_party.getCookware(0) << " | F: " << my_party.getCookware(1) << " | C: " << my_party.getCookware(2) << endl;
    cout << "| Weapons     | " << "C: " << my_party.getWeapons(0) << " | S: " << my_party.getWeapons(1) << " | R: " << my_party.getWeapons(2) 
        << " | B: " << my_party.getWeapons(3) << " | L: " << my_party.getWeapons(4) << endl;
    cout << "| Armor       | " << my_party.getArmor() << endl;
    cout << "| Treasures   | " << "R: " << my_party.getTreasures(0) << " | N: " << my_party.getTreasures(1) << " | B: " << my_party.getTreasures(2) 
        << " | C: " << my_party.getTreasures(3) << " | G: " << my_party.getTreasures(4) << endl;
    cout << "+-------------+" << endl;

    //Outputs Party Info
    cout <<"+-------------+\n" << "| PARTY       |\n" << "+-------------+\n";
    cout << "| " << my_party.getPlayerName() << " | Fullness: " << my_party.getPlayerFullness() << endl;
    for(int i = 0; i < my_party.getLivingMembers(); i++){
        cout << "| " << my_party.getMemberName(i) << " | Fullness: " << my_party.getMemberFullness(i) << endl;
    }
    cout << "+-------------+" << endl << endl;
}

void getMisfortune(Party &my_party){
    int misfortuneid = rand() % 7 + 1; //Randomizes the misfortune you get.
    switch(misfortuneid){
        case 1:
        case 2:
        case 3:
        {
            cout << "Oh no! You've been robbed!" << endl;
            int lostid = rand() % 3; //Randomizes what item you lose
            if(lostid == 0){
                cout << "You lost 10 ingredients. " << endl;
                if(my_party.getIngredientsBalance() < 10){ //Checks how many ingredients you have for how many you will lose.
                    my_party.spendIngredients(my_party.getIngredientsBalance());
                }
                else {
                    my_party.spendIngredients(10);
                }
            }
            else if(lostid == 1){
                cout << "You lost a cookware item!" << endl;
                if(my_party.getCookware(0) > 0){ //Removes the cookware item that you have.
                    my_party.useCookware(0);
                }
                else if(my_party.getCookware(1) > 0){
                    my_party.useCookware(1);
                }
                else if(my_party.getCookware(2) > 0){
                    my_party.useCookware(2);
                }
            }
            else if(lostid == 2){
                cout << "You have lost 1 armor piece." << endl; //Removes an armor piece, if you have one.
                if(!my_party.getArmor() == 0){
                    my_party.losearmor();
                }
            }
        }
        break;

        case 4:
        {
            cout << "Oh no! Your";
            int lostid = rand() % 2; //Randomizes which item breaks.
            if(lostid == 0){
                cout << " armor broke!" << endl;
                my_party.losearmor();
            }
            else {
                cout << "Weapon broke!" << endl;
                if(my_party.getWeapons(0) > 0){ //Breaks the weapon you have.
                    my_party.breakweapon(0);
                }
                else if(my_party.getWeapons(1) > 0){
                    my_party.breakweapon(1);
                }
                else if(my_party.getWeapons(2) > 0){
                    my_party.breakweapon(2);
                }
                else if(my_party.getWeapons(3) > 0){
                    my_party.breakweapon(3);
                }
                else if(my_party.getWeapons(4) > 0){
                    my_party.breakweapon(4);
                }
            }
        }
        break;

        case 5:
        case 6:
        case 7:
        {
            int member = rand() % my_party.getLivingMembers(); //Randomizes the member that gets food poisoning. 
            cout << "Oh no! Party member " << my_party.getMemberName(member) << " has gotten food poisoning!" << endl;
            for(int i = 0; i < 10; i++){
                my_party.loseMemberFullness(member); //Removes 10 fullness.
            }
        }
        break;
    }

}


bool battle(int challengelevel, Party &my_party){
/*
RETURNS TRUE IF ENEMY IS DEFEATED, FALSE IF PLAYER FAILS
Starts a battle with a random enemy
runs through the battle
10% chance the monster will drop a key
50% to drop party fullness
*/
    int selection = 0;
    ifstream fin; //File stream for the monsters names and power levels.
    fin.open("monsters.txt");
    int enemy_id = rand() % 4 + (4 * challengelevel); //Randomizes which monster you fight, within the challenge level.
    string enemy_name; //Strings to take input from the file.
    string junk;
    for(int i = 0; i < enemy_id + 1; i++){
        getline(fin, enemy_name, ',');
        getline(fin, junk);
    }

    fin.close(); //Closes the files stream.

    cout << "You are engaged in a battle with " << enemy_name << endl;

    int weapons = my_party.getWeapons(0) + my_party.getWeapons(1) + my_party.getWeapons(2) + my_party.getWeapons(3) + my_party.getWeapons(4); //Total weapons owned.

    if (weapons > 0){ //Can only fight if you have weapons.
        bool fighting = true; //Allows the fight to loop on invalid inputs.
        cout << "Would you like to \n" << "1. Attack the monster\n2. Surrender" << endl;
        do {
            cin >> selection;
            if(selection == 1){
                double strength = weapons + (1 * my_party.getWeapons(2)) + (2 * my_party.getWeapons(3)) + (3 * my_party.getWeapons(4)); //Strength calculation based on weapons owned.
                double d = 0; //Bonus if everyone has different weapon.
                if(my_party.getWeapons(0) > 0 && my_party.getWeapons(1) > 0 && my_party.getWeapons(2) > 0 && my_party.getWeapons(3) > 0 && my_party.getWeapons(4) > 0 && my_party.getWeapons(5) > 0){
                    d = 4;
                }
                double a = my_party.getArmor();
                double c = challengelevel;
                double r1 = rand() % 6 + 1;
                double r2 = rand() % 6 + 1;
                double battle = (r1 * strength + d) - ((r2 * c) / a); //Calculates the winnder of the battle.
                if(battle > 0){
                    cout << "Congratulations, you have won the battle!" << endl;
                    int gold = 10 * (challengelevel + 1); //Gives rewards based on challenge level.
                    int ingredients = 5 * (challengelevel + 1);
                    cout << "You have earned " << gold << " gold and " << ingredients << " kg ingredients from the monster." << endl;
                    my_party.gainGold(gold);
                    my_party.gainIngredients(ingredients);
                    if(rand() % 10 == 7){ //10% chance to find a key.
                        cout << "You have also found a key!" << endl;
                        my_party.foundKey();
                    }
                    fighting = false; //Allows you to exit the fighting loop.
                    return true;
                }
                else {
                    int gold = my_party.getGoldBalance() * .25; //Amount of gold you lose.
                    cout << "You have lost the battle. You have lost " <<  gold << " gold." << endl; 
                    my_party.spendGold(gold);
                    //10% chance for each member to be slain by the monster.
                    int member1 = rand() % 10;
                    int member2 = rand() % 10;
                    int member3 = rand() % 10;
                    int member4 = rand() % 10;
                    if(member1 == 3){
                        cout << "Oh no! " << my_party.getMemberName(0) << " has been slain by the monster! You will have to continue without them. " << endl;
                        my_party.loseMember(0);
                    }
                    else if(member2 == 3){
                        cout << "Oh no! " << my_party.getMemberName(1) << " has been slain by the monster! You will have to continue without them. " << endl;
                        my_party.loseMember(1);
                    }
                    else if(member3 == 3){
                        cout << "Oh no! " << my_party.getMemberName(2) << " has been slain by the monster! You will have to continue without them. " << endl;
                        my_party.loseMember(2);
                    }
                    else if(member4 == 3){
                        cout << "Oh no! " << my_party.getMemberName(3) << " has been slain by the monster! You will have to continue without them. " << endl;
                        my_party.loseMember(3);
                    }
                    fighting = false;
                }
            }
            else if(selection == 2){ //On surrender
                int memberLost = rand() % my_party.getLivingMembers(); //Chooses which member will be stuck behind randomly.
                cout << "Oh no!" << my_party.getMemberName(memberLost) << " is trapped in the room! You will have to continue without them." << endl;
                my_party.loseMember(memberLost);
                fighting = false;
                return false;
            }
        } while(fighting);
        
    }
    else { //With no weapons, must surrender. 
        cout << "You have no weapons to fight the monster! You must surrender by pressing 1." << endl;
        bool fighting = true;
        do {
            cin >> selection;
            if(selection == 1){
                int memberLost = rand() % my_party.getLivingMembers(); //Randomizes which member will be stuck behind.
                cout << "Oh no!" << my_party.getMemberName(memberLost) << " is trapped in the room! You will have to continue without them." << endl;
                my_party.loseMember(memberLost);
                fighting = false;
                return false;
            }
            else {
                cout << "Please enter a valid input." << endl;
            }
        } while(fighting);
        
    }
    return false;
}

void investigate(Party &my_party, Map &game_map){
    /*
    Changes map data to " "
    10% chance to find a key
    20% chance to find treasure
    20% chance to fight random monster
    50% to drop party fullness.
    */

    game_map.exploreSpace(game_map.getPlayerRow(), game_map.getPlayerCol()); //Explores the space.

    srand(time(NULL));
    rand();

    int key_chance = (rand() % 10) + 1; //10% chance to find a key.
    if(key_chance == 1){
        cout << "You found a key!" << endl;
        my_party.foundKey();
    }

    int treasure_chance = (rand() % 10) + 1; //20% chance to find treasure, gives treasure depending on how many rooms have been cleared.
    if(treasure_chance == 3 || treasure_chance == 5){
        cout << "You found treasure!" << endl;
        if(my_party.getRoomsCleared() == 1){
            my_party.gainTreasures(0, 1);
        }
        else if(my_party.getRoomsCleared() == 2){
            my_party.gainTreasures(1, 1);
        }
        else if(my_party.getRoomsCleared() == 3){
            my_party.gainTreasures(2, 1);
        }
        else if(my_party.getRoomsCleared() == 4){
            my_party.gainTreasures(3, 1);
        }
        else if(my_party.getRoomsCleared() == 5){
            my_party.gainTreasures(4, 1);
        }
    }
    
    int monster_chance = (rand() % 10) + 1; //20% chance to encounter a monster.
    if(monster_chance == 3 || monster_chance == 7){
        cout << "You have encountered a monster!" << endl;
        battle(my_party.getRoomsCleared(), my_party);
    }

    int player_fullness_chance = (rand() % 10) + 1; //50% chance for each member to lose a fullness point.
    if(player_fullness_chance <= 5){
        my_party.losePlayerFullness();
    }

    int member1_fullness_chance = (rand() % 10) + 1;
    if(member1_fullness_chance <= 5){
        my_party.loseMemberFullness(0);
    }

    int member2_fullness_chance = (rand() % 10) + 1;
    if(member2_fullness_chance <= 5){
        my_party.loseMemberFullness(1);
    }

    int member3_fullness_chance = (rand() % 10) + 1;
    if(member3_fullness_chance <= 5){
        my_party.loseMemberFullness(2);
    }

    int member4_fullness_chance = (rand() % 10) + 1;
    if(member4_fullness_chance <= 5){
        my_party.loseMemberFullness(3);
    }

}

void cook(Party &my_party){
    /*
    Give the option to cook food
    select from ingredients
    every 5kg of food is 1 fullness
    */
    bool cooking = true;
    char confirm;
    int amount = 0; //The amount of food to be cooked.
    cout << "Remaining ingredients: " << my_party.getIngredientsBalance() << endl; //Outputs how many ingredients you have.
    do {    
        cout << "How many kg's of food would you like to cook? (in increments of 5kg)" << endl;
        cin >> amount;
        if(!cin.fail()){
            if(amount % 5 != 0 || amount < 5){
                cout << "Please enter a valid input." << endl;
            }
            else {
                cout << "You have chosen to cook " << amount << " kg of food. Confirm? (y/n)" << endl;
                cin >> confirm;
                if(confirm == 'y' || confirm == 'Y'){
                    cout << "You have cooked " << amount << "kg's of food. Your hunger stats have been updated." << endl;
                    for(int i = 0; i < amount; i++){
                        if(i % (my_party.getLivingMembers() + 1) == 0){ //Feeds all players, looping from top to bottom until all food has been given out.
                            my_party.feedPlayer(1);
                        }
                        else {
                            my_party.feedMember(i % my_party.getLivingMembers(), 1);
                        }
                    }
                    cooking = false;
                }
                else if(confirm == 'n' || confirm == 'N'){
                    cout << "No food was cooked." << endl;
                }
                else {
                    cout << "Please enter a valid input." << endl;
                }
            }
            
        }
        else {
            cin.clear();
            cin.ignore(10, '\n');
            cout << "Please enter a valid input. " << endl;
        }
            
    } while(cooking);
    

}

void actions(Map &game_map, Party &my_party){

    int misfortune;

    cout << "Which action would you like to do?" << endl; //Outputs action options.
    cout << "1. Move" << endl;
    cout << "2. Investigate" << endl;
    cout << "3. Pick a Fight!" << endl;
    cout << "4. Cook and Eat" << endl;
    cout << "5. Give up" << endl;

    //Take user input for what action to take
    int actioninput = 0;
    cin >> actioninput;


    if(!cin.fail()){ 
        
        switch(actioninput){
        case 1:
        {
            //if 1 - Move
            actioninput = 0;
            char direction;
            cout << "Which direction would you like to move?" << endl;
            cin >> direction;
            game_map.move(direction); 
            if(!game_map.isExplored(game_map.getPlayerRow(), game_map.getPlayerCol()) && !my_party.isSorcererDefeated()){ //Adds an anger level if the space moved onto is not explored and the sorcerer is still alive.
                my_party.addAngerLevel(1);
            }
        } 
        break;

        case 2:
            //if 2 - Investiage
            actioninput = 0;
            if(game_map.isExplored(game_map.getPlayerRow(), game_map.getPlayerCol())){ //Checks if space is already explored.
                cout << "You have already explored this space!" << endl;
            }
            else {
                investigate(my_party, game_map); //Explore the space.
            }

            misfortune = rand() % 10; //40% chance for a misfortune.
            if(misfortune < 4){
                getMisfortune(my_party);
            }
        break;

        case 3:
            //if 3 - Pick a fight
            actioninput = 0;
            battle(my_party.getRoomsCleared(), my_party); //Starts a battle with a challenge level dependent on the rooms cleared.
            misfortune = rand() % 10; //40% chance for a misfortune.
            if(misfortune < 4){
                getMisfortune(my_party);
            }
        break;

        case 4:
            //if 4 - cook and eat
            actioninput = 0;
            cook(my_party); //Calls cooking function
            misfortune = rand() % 10; //40% chance for a misfortune
            if(misfortune < 4){
                getMisfortune(my_party);
            }
        break;

        case 5:
            //Give up
            cout << "Game Over..." << endl;
            my_party.gameOver(); //Ends the game.
        break;

        default:
            cout << "enter valid input" << endl;
            actioninput = 0;
        break;
        }
    }

    else {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Please enter a valid input. " << endl;
    }
    
}



bool doorPuzzle(Party &my_party){
    bool win = false; //True is won, false is lost.
    bool gameOver = false;
    int attemps = 0; //Attempts at winning, up to 3.
    cout << "I, the door, hereby challenge you to a game of Boulder... Parchment... Shears..." << endl;
    int playerchoice = 0;
    do {
        cout << "Do you choose: \n" << "1. Boulder \n" << "2. Parchment \n" << "3. Shears" << endl;
        cin >> playerchoice;
        int doorchoice = rand() % 3 + 1; //Randomizes the computers choice for the game.

        if(!cin.fail()){
            switch(playerchoice){

                case 1: //Cases where player chose Boulder
                    attemps++;
                    if(doorchoice == 1){
                        cout << "Doors choice is Boulder." << endl;
                        cout << "It's a tie... Again!" << endl;
                    }
                    else if(doorchoice == 2){
                        cout << "Doors choice is Parchment. Door wins!" << endl;
                        win = false;
                        gameOver = true;
                    }
                    else if(doorchoice == 3){
                        cout << "Doors choice is Shears. You win!" << endl;
                        win = true;
                        gameOver = true;
                    }
                break;

                case 2://Cases where player chose Parchment
                    attemps++;
                    if(doorchoice == 1){
                        cout << "Doors choice is Boulder. You win!" << endl;
                        win = true;
                        gameOver = true;
                    }
                    else if(doorchoice == 2){
                        cout << "Doors choice is Parchment." << endl;
                        cout << "It's a tie... Again!" << endl;
                        
                    }
                    else if(doorchoice == 3){
                        cout << "Doors choice is Shears. Door wins!" << endl;
                        win = false;
                        gameOver = true;
                    }
                break;

                case 3://Cases where player chose Shears
                    attemps++;
                    if(doorchoice == 1){
                        cout << "Doors choice is Boulder. Door wins!" << endl;
                        win = false;
                        gameOver = true; 
                    }
                    else if(doorchoice == 2){
                        cout << "Doors choice is Parchment. You win!" << endl;
                        win = true;
                        gameOver = true;
                    }
                    else if(doorchoice == 3){
                        cout << "Doors choice is Shears." << endl;
                        cout << "It's a tie... Again!" << endl;                                       
                    }
                break;

                default:
                    playerchoice = 0;
                    cout << "Please enter a valid selection. " << endl;
                break;
            }
        }

        else {
            cin.clear();
            cin.ignore(10, '\n');
            cout << "Please enter a valid input. " << endl;
        }

    } while(gameOver == false && attemps < 3);

    if(win == true){
        cout << "Congratulations, you won and are able to enter the room!" << endl;
        return true;
    }
    else {
        cout << "You have failed to beat the challenge. " << endl;
        return false;
    }
    
}

void roomActions(Map &game_map, Party &my_party){


    cout << "Which action would you like to do?" << endl; //Outputs action options.
    cout << "1. Move" << endl;
    cout << "2. Open the Door" << endl;
    cout << "3. Give up" << endl;

    //Take user input for what action to take
    int actioninput = 0;
    cin >> actioninput;


    if(!cin.fail()){ 

        switch(actioninput){
        case 1:
        {
            //if 1 - Move
            actioninput = 0;
            char direction;
            cout << "Which direction would you like to move?" << endl;
            cin >> direction;
            game_map.move(direction); 
        } 
        break;

        case 2:
            //if 2 - Open The Door
            actioninput = 0;
            if(my_party.getKeys() == 0){ //Can't open the door without keys. Redirects to the puzzle.
                cout << "You have fallen into a trap!" << endl;
                bool puzzle = doorPuzzle(my_party);
                if(puzzle == true){ //Continue if you won the puzzle.
                    int success = battle(my_party.getRoomsCleared() + 1, my_party); //Starts a battle with an enemy of challenge level +1 of rooms cleared.
                    if(success == true){ //If you win the battle.
                        cout << "Congratulations on defeating the monster!" << endl;
                        my_party.roomCleared(); //Clears the room and removes the R from the map.
                        if(my_party.getRoomsCleared() == 5){ //If you were fighting the sorcerer.
                            my_party.defeatSorcerer();
                        }
                        game_map.removeRoom(game_map.getPlayerRow(), game_map.getPlayerCol()); 
                        int misfortune = rand() % 10 + 1; //60% chance for a misfortune.
                            if(misfortune <= 6){
                                getMisfortune(my_party);
                            }
                    }
                    else { //If battle is lost.
                        cout <<"Unfortunate. You have failed to defeat this monster." << endl;
                        int misfortune = rand() % 10 + 1; ///40% chance of misfortune.
                            if(misfortune <= 4){
                                getMisfortune(my_party);
                            }
                    }
                }
                if(puzzle == false){ //If you fail the puzzle, traps one random member behind.
                    int memberLost = rand() % my_party.getLivingMembers();
                    cout << "Oh no!" << my_party.getMemberName(memberLost) << " is trapped in the room! You will have to continue without them." << endl;
                    my_party.loseMember(memberLost);
                }
            }
            else { //If you have a key. Same as above. 
                cout << "You have encountered a monster!" << endl;
                my_party.useKey();
                int success = battle(my_party.getRoomsCleared() + 1, my_party);
                if(success == true){
                    cout << "Congratulations on defeating the monster!" << endl;
                    my_party.roomCleared();
                    if(my_party.getRoomsCleared() == 5){
                        my_party.defeatSorcerer();
                    }
                    game_map.removeRoom(game_map.getPlayerRow(), game_map.getPlayerCol());
                    int misfortune = rand() % 10 + 1;
                    if(misfortune <= 6){
                        getMisfortune(my_party);
                    }
                }
                else {
                    cout <<"Unfortunate. You have failed to defeat this monster." << endl;
                    int misfortune = rand() % 10 + 1;
                    if(misfortune <= 4){
                        getMisfortune(my_party);
                    }
                }
            }
            
        break;

        case 3:
            //Game Over
            cout << "Game Over..." << endl;
            my_party.gameOver(); //Ends game.
        break;

        default:
            cout << "enter valid input" << endl;
            actioninput = 0;
        break;
        }
    }

    else {
            cin.clear();
            cin.ignore(10, '\n');
            cout << "Please enter a valid input. " << endl;
    }
}

void exitActions(Map &game_map, Party &my_party){ //Actions available when on an exit space. 
    cout << "Which action would you like to do?" << endl; //Outputs action options.
    cout << "1. Move" << endl;
    cout << "2. Exit the Dungeon" << endl;
    cout << "3. Give up" << endl;

    //Take user input for what action to take
    int actioninput = 0;
    cin >> actioninput;


    if(!cin.fail()){ 

        switch(actioninput){
        case 1:
        {
            //if 1 - Move
            actioninput = 0;
            char direction;
            cout << "Which direction would you like to move?" << endl;
            cin >> direction;
            game_map.move(direction); 
        } 
        break;

        case 2:
            if(my_party.isSorcererDefeated() == false){ //Only allows you to exit if the sorcerer is dead.
                cout << "The sorcerer is still alive! Defeat him and come back to exit." << endl;
            }
            else {
                cout << "Congratulations, you have escaped the dungeon!" << endl;
                my_party.gameOver(); //Ends the game.
            }
        break;

        case 3:
            //Game Over
            cout << "Game Over..." << endl;
            my_party.gameOver(); //Ends the game.
        break;

        default:
            cout << "enter valid input" << endl;
            actioninput = 0;
        break;
        }
    }

    else {
            cin.clear();
            cin.ignore(10, '\n');
            cout << "Please enter a valid input. " << endl;
    }
}

int merchantMenu(Party &my_party){
    char selection; //Creates a variable for input
    //Outputs inventory stats
    cout << "+-------------+\n" << "| INVENTORY   |\n" << "+-------------+\n"; 
    cout << "| Gold        | " << my_party.getGoldBalance() << endl;
    cout << "| Ingredients | " << my_party.getIngredientsBalance() << endl;
    cout << "| Cookware    | " << "P: " << my_party.getCookware(0) << " | F: " << my_party.getCookware(1) << " | C: " << my_party.getCookware(2) << endl;
    cout << "| Weapons     | " << "C: " << my_party.getWeapons(0) << " | S: " << my_party.getWeapons(1) << " | R: " << my_party.getWeapons(2) 
        << " | B: " << my_party.getWeapons(3) << " | L: " << my_party.getWeapons(4) << endl;
    cout << "| Armor       | " << my_party.getArmor() << endl;
    cout << "| Treasures   | " << "R: " << my_party.getTreasures(0) << " | N: " << my_party.getTreasures(1) << " | B: " << my_party.getTreasures(2) 
        << " | C: " << my_party.getTreasures(3) << " | G: " << my_party.getTreasures(4) << endl;
    cout << "+-------------+" << endl;

    //Outputs merchant options
    cout << "Choose one of the following: " << endl;
    cout << "1. Ingredients: To make food, you have to cook raw ingredients." << endl;
    cout << "2. Cookware: You will need something to cook those ingredients." << endl;
    cout << "3. Weapons: It's dangerous to go alone, take this!" << endl;
    cout << "4. Armor: If you want to survive monster attacks, you will need some armor." << endl;
    cout << "5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands." << endl;
    cout << "6. Leave: Make sure you get everything you need, I'm leaving after this sale!" << endl;

    cin >> selection; //Takes input on the seleciton

    int int_selection = (int)selection; //Turns it into an integer

    if(int_selection < 48 || int_selection > 54){ //Checks it is in the proper range, if it isn't it resets the selection.
        cin.clear();
        int_selection = 0;
    }
    else{ //If it is in the proper range, bring it down to 1-6 option.
        int_selection -= 48; 
    }

    return int_selection; //Returns that selection.
}

void merchantIngredients(Party &my_party){
    int amount = 0;
    char confirm;
    bool purchased = false;
    do {
        cout << "How many kg of ingredients do you need [1 Gold/kg]? (Enter a positive multiple of 5, or 0 to cancel)" << endl;
        cin >> amount;
        if(!cin.fail()){
            if(amount == 0){
                cout << "Exiting... " << endl;
                purchased = true;
            }
            else if(amount < 0){
                cout << "You cannot buy a negative amount!" << endl;
            }
            else if(amount % 5 == 0){
                int price = amount + my_party.getRoomsCleared() * (amount * .25); //Increases price by floors cleared.
                cout << "You want to buy " << amount << " kg of ingredients for " << price << " Gold? (y/n)" << endl;
                cin >> confirm;
                if(my_party.getGoldBalance() < price){
                    cout << "You can't afford this!" << endl;
                }
                else if(confirm == 'y' || confirm == 'Y'){
                    my_party.gainIngredients(amount);
                    my_party.spendGold(price);
                    cout << "Thank you for your patronage. What else can I get for you?" << endl;
                    purchased = true;
                }
                else if (confirm == 'n' || confirm == 'N'){
                    cout << "Alright then." << endl;
                }

                else {
                    cout << "Please enter a valid input. " << endl;
                }
            }
        }
            
        else {
            cin.clear();
            cin.ignore(10, '\n');
            cout << "Please enter a valid input. " << endl;
        }

    } while(purchased == false);
}

void merchantCookware(Party &my_party){
    int selection = 0;
    char confirm;
    int quantity = 0;
    bool purchased = false;
    bool inCookware = true;
    do {
        cout << "I have several different types of cookware, which one would you like?" << endl;
        cout << "Each type has a different probability of breaking when used, marked by %." << endl;
        cout << "Choose one of the following: " << endl;
        cout << "1. (25%) Ceramic Pot [2 Gold]" << endl;
        cout << "2. (10%) Frying Pan [10 Gold]" << endl;
        cout << "3. ( 2%) Cauldron [20 Gold]" << endl;
        cout << "4. Cancel. " << endl;

        cin >> selection;

        if(!cin.fail()){
            switch(selection){

                case 1:
                    selection = 0;
                    do {
                        cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                        cin >> quantity;
                        if(quantity == 0){
                            cout << "Exiting..." << endl;
                            purchased = true;
                        }
                        else if(quantity > 0){
                            int price = quantity * 2 + (my_party.getRoomsCleared() * ((quantity * 2) * .25));//Increases price by floors cleared.
                            cout << "You want to buy " << quantity << " Ceramic pot(s) for " << price << " Gold? (y/n)" << endl;
                            cin >> confirm;
                            if(my_party.getGoldBalance() < price){
                                cout << "You can't afford this!" << endl;
                            }
                            else if(confirm == 'y' || confirm == 'Y'){
                                my_party.buyCookware(0, quantity);
                                cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                my_party.spendGold(price);
                                purchased = true;
                            }
                            else if (confirm == 'n' || confirm == 'N'){
                                cout << "Alright then. What else can I get for you?" << endl;
                            }
                            else {
                                cout << "Please enter a valid input. " << endl;
                            }
                        }
                        else if(quantity < 0){
                            cout << "Please enter a valid input." << endl;
                        }
                    } while (purchased == false);
                break;

                case 2:
                    selection = 0;
                    do {
                        cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                        cin >> quantity;
                        if(quantity == 0){
                            cout << "Exiting..." << endl;
                            purchased = true;
                        }
                        else if(quantity > 0){
                            int price = quantity * 10 + (my_party.getRoomsCleared() * ((quantity * 10) * .25));//Increases price by floors cleared.
                            cout << "You want to buy " << quantity << " Frying pan(s) for " << price << " Gold? (y/n)" << endl;
                            cin >> confirm;
                            if(my_party.getGoldBalance() < price){
                                cout << "You can't afford this!" << endl;
                            }
                            else if(confirm == 'y' || confirm == 'Y'){
                                my_party.buyCookware(1, quantity);
                                cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                my_party.spendGold(price);
                                purchased = true;
                            }
                            else if (confirm == 'n' || confirm == 'N'){
                                cout << "Alright then. What else can I get for you?" << endl;
                            }
                            else {
                                cout << "Please enter a valid input. " << endl;
                            }
                        }
                        else if(quantity < 0){
                            cout << "Please enter a valid input." << endl;
                        }
                    } while (purchased == false);
                break;
                    
                case 3:
                    selection = 0;
                    do {
                        cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                        cin >> quantity;
                        if(quantity == 0){
                            cout << "Exiting..." << endl;
                            purchased = true;
                        }
                        else if(quantity > 0){
                            int price = quantity * 20 + (my_party.getRoomsCleared() * ((quantity * 20) * .25));//Increases price by floors cleared.
                            cout << "You want to buy " << quantity << " Cauldron(s) for " << price << " Gold? (y/n)" << endl;
                            cin >> confirm;
                            if(my_party.getGoldBalance() < price){
                                cout << "You can't afford this!" << endl;
                            }
                            else if(confirm == 'y' || confirm == 'Y'){
                                my_party.buyCookware(2, quantity);
                                cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                my_party.spendGold(price);
                                purchased = true;
                            }
                            else if (confirm == 'n' || confirm == 'N'){
                                cout << "Alright then. What else can I get for you?" << endl;
                            }
                            else {
                                cout << "Please enter a valid input. " << endl;
                            }
                        }
                        else if(quantity < 0){
                            cout << "Please enter a valid input." << endl;
                        }
                    } while (purchased == false);
                break;

                case 4:
                    selection = 0;
                    inCookware = false;
                    cout << "Exiting..." << endl;
                break;

                default:
                    selection = 0;
                    cout << "Please enter a valid input." << endl;
                break;
            }
        }

        else {
            cin.clear();
            cin.ignore(10, '\n');
            cout << "Please enter a valid input. " << endl;
        }

        } while(inCookware == true);

}

void merchantWeapons(Party &my_party){
    int selection = 0;
    char confirm;
    int quantity = 0;
    bool purchased = false;
    bool inWeapons = true;
    do {
        cout << "I have a plentiful collection of weapons to choose from, what would you like?" << endl;
        cout << "Note that some of them provide you a special bonus in combat, marked by a (+X)." << endl;
        cout << "Choose one of the following: " << endl;
        cout << "1. Stone Club [2 Gold]" << endl;
        cout << "2. Iron Spear [2 Gold]" << endl;
        cout << "3. (+1) Mythril Rapier [5 Gold]" << endl;
        cout << "4. (+2) Flaming Battle-Axe [15 Gold]" << endl;
        cout << "5. (+3) Vorpal Longsword [50 Gold]" << endl;
        cout << "6. Cancel. " << endl;

        cin >> selection;

        if(!cin.fail()){
            
            switch(selection){

                case 1:
                    selection = 0;
                    do {
                        cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                        cin >> quantity;
                        if(quantity == 0){
                            cout << "Exiting..." << endl;
                            purchased = true;
                        }
                        else if(quantity > 0){
                            int price = quantity * 2 + (my_party.getRoomsCleared() * ((quantity * 2) * .25));//Increases price by floors cleared.
                            cout << "You want to buy " << quantity << " Stone Club(s) for " << price << " Gold? (y/n)" << endl;
                            cin >> confirm;
                            if(my_party.getGoldBalance() < price){
                                cout << "You can't afford this!" << endl;
                            }
                            else if(confirm == 'y' || confirm == 'Y'){
                                my_party.buyWeapons(0, quantity);
                                cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                my_party.spendGold(price);
                                purchased = true;
                            }
                            else if (confirm == 'n' || confirm == 'N'){
                                cout << "Alright then. What else can I get for you?" << endl;
                            }
                            else {
                                cout << "Please enter a valid input. " << endl;
                            }
                        }
                        else if(quantity < 0){
                            cout << "Please enter a valid input." << endl;
                        }
                    } while (purchased == false);
                break;

                case 2:
                    selection = 0;
                    do {
                        cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                        cin >> quantity;
                        if(quantity == 0){
                            cout << "Exiting..." << endl;
                            purchased = true;
                        }
                        else if(quantity > 0){
                            int price = quantity * 2 + (my_party.getRoomsCleared() * ((quantity * 2) * .25));//Increases price by floors cleared.
                            cout << "You want to buy " << quantity << " Iron Spear(s) for " << price << " Gold? (y/n)" << endl;
                            cin >> confirm;
                            if(my_party.getGoldBalance() < price){
                                cout << "You can't afford this!" << endl;
                            }
                            else if(confirm == 'y' || confirm == 'Y'){
                                my_party.buyWeapons(1, quantity);
                                cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                my_party.spendGold(price);
                                purchased = true;
                            }
                            else if (confirm == 'n' || confirm == 'N'){
                                cout << "Alright then. What else can I get for you?" << endl;
                            }
                            else {
                                cout << "Please enter a valid input. " << endl;
                            }
                        }
                        else if(quantity < 0){
                            cout << "Please enter a valid input." << endl;
                        }
                    } while (purchased == false);
                break;
                    
                case 3:
                    selection = 0;
                    do {
                        cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                        cin >> quantity;
                        if(quantity == 0){
                            cout << "Exiting..." << endl;
                            purchased = true;
                        }
                        else if(quantity > 0){
                            int price = quantity * 5 + (my_party.getRoomsCleared() * ((quantity * 5) * .25));//Increases price by floors cleared.
                            cout << "You want to buy " << quantity << " (+1) Mythril Rapier(s) for " << price << " Gold? (y/n)" << endl;
                            cin >> confirm;
                            if(my_party.getGoldBalance() < price){
                                cout << "You can't afford this!" << endl;
                            }
                            else if(confirm == 'y' || confirm == 'Y'){
                                my_party.buyWeapons(2, quantity);
                                cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                my_party.spendGold(price);
                                purchased = true;
                            }
                            else if (confirm == 'n' || confirm == 'N'){
                                cout << "Alright then. What else can I get for you?" << endl;
                            }
                            else {
                                cout << "Please enter a valid input. " << endl;
                            }
                        }
                        else if(quantity < 0){
                            cout << "Please enter a valid input." << endl;
                        }
                    } while (purchased == false);
                break;

                case 4:
                    selection = 0;
                    do {
                        cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                        cin >> quantity;
                        if(quantity == 0){
                            cout << "Exiting..." << endl;
                            purchased = true;
                        }
                        else if(quantity > 0){
                            int price = quantity * 15 + (my_party.getRoomsCleared() * ((quantity * 15) * .25));//Increases price by floors cleared.
                            cout << "You want to buy " << quantity << " (+2) Flaming Battle-axe(s) for " << price << " Gold? (y/n)" << endl;
                            cin >> confirm;
                            if(my_party.getGoldBalance() < price){
                                cout << "You can't afford this!" << endl;
                            }
                            else if(confirm == 'y' || confirm == 'Y'){
                                my_party.buyWeapons(3, quantity);
                                cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                my_party.spendGold(price);
                                purchased = true;
                            }
                            else if (confirm == 'n' || confirm == 'N'){
                                cout << "Alright then. What else can I get for you?" << endl;
                            }
                            else {
                                cout << "Please enter a valid input. " << endl;
                            }
                        }
                        else if(quantity < 0){
                            cout << "Please enter a valid input." << endl;
                        }
                    } while (purchased == false);
                break;

                case 5:
                    selection = 0;
                    do {
                        cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                        cin >> quantity;
                        if(quantity == 0){
                            cout << "Exiting..." << endl;
                            purchased = true;
                        }
                        else if(quantity > 0){
                            int price = quantity * 50 + (my_party.getRoomsCleared() * ((quantity * 50) * .25));//Increases price by floors cleared.
                            cout << "You want to buy " << quantity << " (+3) Vorpal Longsword(s) for " << price << " Gold? (y/n)" << endl;
                            cin >> confirm;
                            if(my_party.getGoldBalance() < price){
                                cout << "You can't afford this!" << endl;
                            }
                            else if(confirm == 'y' || confirm == 'Y'){
                                my_party.buyWeapons(4, quantity);
                                cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                my_party.spendGold(price);
                                purchased = true;
                            }
                            else if (confirm == 'n' || confirm == 'N'){
                                cout << "Alright then. What else can I get for you?" << endl;
                            }
                            else {
                                cout << "Please enter a valid input. " << endl;
                            }
                        }
                        else if(quantity < 0){
                            cout << "Please enter a valid input." << endl;
                        }
                    } while (purchased == false);
                break;


                case 6:
                    selection = 0;
                    inWeapons = false;
                    cout << "Exiting..." << endl;
                break;

                default:
                    selection = 0;
                    cout << "Please enter a valid input." << endl;
                break;
            }
        }

        else {
            cin.clear();
            cin.ignore(10, '\n');
            cout << "Please enter a valid input. " << endl;
        }

    } while(inWeapons == true);

}

void merchantArmor(Party &my_party){
    int amount = 0;
    char confirm;
    bool purchased = false;
    do {
        cout << "How many suits of armor can I get you? (Enter a positive integer, or 0 to cancel)" << endl;
        cin >> amount;

        if(!cin.fail()){
            if(amount == 0){
                cout << "Exiting... " << endl;
                purchased = true;
            }
            else if(amount > 0){
                int price = amount * 5 + (my_party.getRoomsCleared() * ((amount * 5) * .25));//Increases price by floors cleared.
                cout << "You want to buy " << amount << " suit(s) of armor for " << price << " Gold? (y/n)" << endl;
                cin >> confirm;
                if(my_party.getGoldBalance() < price){
                    cout << "You can't afford this!" << endl;
                }
                else if(confirm == 'y' || confirm == 'Y'){
                    my_party.buyArmor(amount);
                    my_party.spendGold(price);
                    cout << "Thank you for your patronage. What else can I get for you?" << endl;
                    purchased = true;
                }
                else if (confirm == 'n' || confirm == 'N'){
                    cout << "Alright then." << endl;
                }

                else {
                    cout << "Please enter a valid input. " << endl;
                }
            }
        }
        
        else {
            cin.clear();
            cin.ignore(10, '\n');
            cout << "Please enter a valid input. " << endl;
        }
    } while(purchased == false);
}

void merchantSell(Party &my_party){

    int selection = 0;
    int amount = 0;
    char confirm;
    bool sold = false;
    bool inTreasures = true;
    do {
        //Outputs what treasures you have and how much they are worth.
        cout << "Ah, you'd like to sell your treasures!" << endl;
        cout << "Which would you like to sell?" << endl;
        cout << "1. Silver ring (R)          | Amount: " << my_party.getTreasures(0) << " | Value: 10 Gold" << endl;
        cout << "2. Ruby Necklace (N)        | Amount: " << my_party.getTreasures(1) << " | Value: 20 Gold" << endl;
        cout << "3. Emerald Bracelet (B)     | Amount: " << my_party.getTreasures(2) << " | Value: 30 Gold" << endl;
        cout << "4. Diamond Cirlcet (C)      | Amount: " << my_party.getTreasures(3) << " | Value: 40 Gold" << endl;
        cout << "5. Gem-encursted Goblet (G) | Amount: " << my_party.getTreasures(4) << " | Value: 50 Gold" << endl;
        cout << "6. Cancel" << endl;

        cin >> selection;

        if(!cin.fail()){
                switch(selection){

                case 1:
                    selection = 0;
                    do {
                        if (my_party.getTreasures(0) > 0){
                            cout << "How many silver rings would you like to sell? (0 to cancel)" << endl;
                            cin >> amount;
                            
                            if(amount == 0){
                                cout << "Exiting... " << endl;
                                sold = true;
                            }
                            else if(amount < 0){
                                cout << "You cannot sell a negative number!" << endl;
                            }
                            else if(amount > my_party.getTreasures(0)){
                                cout << "You do not have that many silver rings!" << endl;
                            }
                            else {
                                cout << "You would like to sell " << amount << " Silver ring(s) for " << amount * 10 << " Gold? (y/n)" << endl;
                                cin >> confirm;

                                if(confirm == 'y' || confirm == 'Y'){
                                    my_party.sellTreaures(0, amount);
                                    my_party.gainGold(amount * 10);
                                    cout << "Thank you for your selling! What else can I do for you?" << endl;
                                    sold = true;
                                }
                                else if (confirm == 'n' || confirm == 'N'){
                                    cout << "Alright then." << endl;
                                }

                                else {
                                    cout << "Please enter a valid input. " << endl;
                                }
                            }
                        }
                        else {
                            cout << "You do not have any of this treasure!" << endl;
                            sold = true;
                        }
                    } while(sold == false);
                break;

                case 2:
                    selection = 0;
                    do {
                        if (my_party.getTreasures(1) > 0){
                            cout << "How many Ruby Necklaces would you like to sell? (0 to cancel)" << endl;
                            cin >> amount;
                            
                            if(amount == 0){
                                cout << "Exiting... " << endl;
                                sold = true;
                            }
                            else if(amount < 0){
                                cout << "You cannot sell a negative number!" << endl;
                            }
                            else if(amount > my_party.getTreasures(1)){
                                cout << "You do not have that many Ruby Necklaces!" << endl;
                            }
                            else {
                                cout << "You would like to sell " << amount << " Ruby Necklace(s) for " << amount * 20 << " Gold? (y/n)" << endl;
                                cin >> confirm;

                                if(confirm == 'y' || confirm == 'Y'){
                                    my_party.sellTreaures(1, amount);
                                    my_party.gainGold(amount * 20);
                                    cout << "Thank you for your selling! What else can I do for you?" << endl;
                                    sold = true;
                                }
                                else if (confirm == 'n' || confirm == 'N'){
                                    cout << "Alright then." << endl;
                                }

                                else {
                                    cout << "Please enter a valid input. " << endl;
                                }
                            }
                        }
                        else {
                            cout << "You do not have any of this treasure!" << endl;
                            sold = true;
                        }
                    } while(sold == false);
                break;

                case 3:
                    selection = 0;
                    do {
                        if (my_party.getTreasures(2) > 0){
                            cout << "How many Emerald Braclets would you like to sell? (0 to cancel)" << endl;
                            cin >> amount;
                            
                            if(amount == 0){
                                cout << "Exiting... " << endl;
                                sold = true;
                            }
                            else if(amount < 0){
                                cout << "You cannot sell a negative number!" << endl;
                            }
                            else if(amount > my_party.getTreasures(2)){
                                cout << "You do not have that many Emerald Bracelets!" << endl;
                            }
                            else {
                                cout << "You would like to sell " << amount << " Emerald Bracelet(s) for " << amount * 30 << " Gold? (y/n)" << endl;
                                cin >> confirm;

                                if(confirm == 'y' || confirm == 'Y'){
                                    my_party.sellTreaures(2, amount);
                                    my_party.gainGold(amount * 30);
                                    cout << "Thank you for your selling! What else can I do for you?" << endl;
                                    sold = true;
                                }
                                else if (confirm == 'n' || confirm == 'N'){
                                    cout << "Alright then." << endl;
                                }

                                else {
                                    cout << "Please enter a valid input. " << endl;
                                }
                            }
                        }
                        else {
                            cout << "You do not have any of this treasure!" << endl;
                            sold = true;
                        }
                    } while(sold == false);
                break;

                case 4:
                    selection = 0;
                    do {
                        if (my_party.getTreasures(3) > 0){
                            cout << "How many Diamond Circlets would you like to sell? (0 to cancel)" << endl;
                            cin >> amount;
                            
                            if(amount == 0){
                                cout << "Exiting... " << endl;
                                sold = true;
                            }
                            else if(amount < 0){
                                cout << "You cannot sell a negative number!" << endl;
                            }
                            else if(amount > my_party.getTreasures(3)){
                                cout << "You do not have that many Diamond Circlets!" << endl;
                            }
                            else {
                                cout << "You would like to sell " << amount << " Diamond Circlet(s) for " << amount * 40 << " Gold? (y/n)" << endl;
                                cin >> confirm;

                                if(confirm == 'y' || confirm == 'Y'){
                                    my_party.sellTreaures(3, amount);
                                    my_party.gainGold(amount * 40);
                                    cout << "Thank you for your selling! What else can I do for you?" << endl;
                                    sold = true;
                                }
                                else if (confirm == 'n' || confirm == 'N'){
                                    cout << "Alright then." << endl;
                                }

                                else {
                                    cout << "Please enter a valid input. " << endl;
                                }
                            }
                        }
                        else {
                            cout << "You do not have any of this treasure!" << endl;
                            sold = true;
                        }
                    } while(sold == false);
                break;

                case 5:
                    selection = 0;
                    do {
                        if (my_party.getTreasures(4) > 0){
                            cout << "How many Gem-Encrusted Goblets would you like to sell? (0 to cancel)" << endl;
                            cin >> amount;
                            
                            if(amount == 0){
                                cout << "Exiting... " << endl;
                                sold = true;
                            }
                            else if(amount < 0){
                                cout << "You cannot sell a negative number!" << endl;
                            }
                            else if(amount > my_party.getTreasures(4)){
                                cout << "You do not have that many Gem-Encrusted Goblets!" << endl;
                            }
                            else {
                                cout << "You would like to sell " << amount << " Gem-Encrusted Goblet(s) for " << amount * 50 << " Gold? (y/n)" << endl;
                                cin >> confirm;

                                if(confirm == 'y' || confirm == 'Y'){
                                    my_party.sellTreaures(4, amount);
                                    my_party.gainGold(amount * 50);
                                    cout << "Thank you for your selling! What else can I do for you?" << endl;
                                    sold = true;
                                }
                                else if (confirm == 'n' || confirm == 'N'){
                                    cout << "Alright then." << endl;
                                }

                                else {
                                    cout << "Please enter a valid input. " << endl;
                                }
                            }
                        }
                        else {
                            cout << "You do not have any of this treasure!" << endl;
                            sold = true;
                        }
                    } while(sold == false);
                break;

                case 6:
                    selection = 0;
                    inTreasures = false;
                    cout << "Exiting..." << endl;
                break;

                default:
                    selection = 0;
                    cout << "Please enter a valid input." << endl;
                break;
            }
        }

        else {
            cin.clear();
            cin.ignore(10, '\n');
            cout << "Please enter a valid input. " << endl;
        }

    } while(inTreasures == true);

}

void merchantVisit(Party &my_party){
    int selection = 0;
    bool shopping = true; //To loop until the player chooses to exit the shop.

    cout << "Welcome to the merchants den. Here is the place to stock up before your journey. " << endl;

    do {
        selection = merchantMenu(my_party);

        switch(selection){ //Redirects to each individual section of the shop.
            case 1: 
                selection = 0;
                merchantIngredients(my_party);
            break;

            case 2:
                selection = 0;
                merchantCookware(my_party);
            break;

            case 3:
                selection = 0;
                merchantWeapons(my_party);
            break;
            
            case 4:
                selection = 0;
                merchantArmor(my_party);
            break;

            case 5:
                selection = 0;
                merchantSell(my_party);
            break;

            case 6: 
                selection = 0;
                cout << "Goodbye!" << endl;
                shopping = false; //Exits the loop.
            break;

            default:
                selection = 0;
                cout << "Please enter a valid selection. " << endl;
            break;
        }

    } while(shopping == true);

}

void npcActions(Map &game_map, Party &my_party){
    game_map.seeNPC(game_map.getPlayerRow(), game_map.getPlayerCol()); //Makes the NPC space visible.
            
    cout << "Which action would you like to do?" << endl; //Outputs action options.
    cout << "1. Move" << endl;
    cout << "2. Speak to NPC" << endl;
    cout << "3. Give up" << endl;

    //Take user input for what action to take
    int actioninput = 0;
    cin >> actioninput;

    if(!cin.fail()){ 

    switch(actioninput){
        case 1:
        {
            //if 1 - Move
            actioninput = 0;
            char direction;
            cout << "Which direction would you like to move?" << endl;
            cin >> direction;
            game_map.move(direction); 
        } 
        break;

        case 2:
        {
            //if 2 - Speak to NPC
            actioninput = 0;
            cout << "You have encountered an NPC! You must now solve my riddle..." << endl;
            int riddlenumber = rand() % 20 + 1; //Randomly chooses a riddle 
            string riddle;
            string answer;
            string player_answer;
            ifstream fin; //Filestream for the list of riddles.
            fin.open("riddles.txt.");

            for(int i = 0; i < riddlenumber; i++){ //Loops to choose the selected riddle.
                getline(fin, riddle, '~');
                getline(fin, answer);
            }
            cout << riddle << endl; //Outputs the riddle, takes in an answer.
            cin >> player_answer;
            if(answer == player_answer){ //If correct, takes you to the shop.
                cout << "Correct! Welcome to my shop." << endl;
                merchantVisit(my_party);
            }
            else { //If fails, starts a battle.
                cout << "Wrong! The correct answer was " << answer << endl;
                cout << "You will now have to face the wrath of my friend!" << endl;
                battle(my_party.getRoomsCleared(), my_party);
            }
        }
        break;

        case 3:
            //Game Over
            cout << "Game Over..." << endl;
            my_party.gameOver(); //Ends game.
        break;

        default:
            cout << "enter valid input" << endl;
            actioninput = 0;
        break;
        }
    }

    else {
            cin.clear();
            cin.ignore(10, '\n');
            cout << "Please enter a valid input. " << endl;
    }

}

int main(){
    //Start the game and initialize the party and map.
    Map game_map;
    Party my_party("Jeff");

    generateMap(game_map); //Generates locations of NPC's and Rooms.

    gameStart(my_party); //Sets player and members names.
    
    merchantVisit(my_party);//Visit the merchant, and stock up on supplies.
    //Game loop:
    while(my_party.isAlive() == true){ //Runs every single turn to allow actions, and check if the game should continue.

        statusUpdate(my_party); //Outputs a status update.
        game_map.displayMap(); //Display map at the start of each turn.
        
        if(game_map.isNPCLocation(game_map.getPlayerRow(), game_map.getPlayerCol())){
            npcActions(game_map, my_party); //Actions if you're on an NPC space. 
        }
        else if(game_map.isRoomLocation(game_map.getPlayerRow(), game_map.getPlayerCol())){
            roomActions(game_map, my_party); //Actions if you're on a room space.
        }
        else if(game_map.isDungeonExit(game_map.getPlayerRow(), game_map.getPlayerCol())){
            exitActions(game_map, my_party); //Actions if you're on the exit space.
        }
        else {
            actions(game_map, my_party); //Calls for each turn to decide what to do.
        }
        

        if(my_party.isAlive() == false){ //Checsk if you are dead.
            cout << "The game is over." << endl;
            gameOver(my_party, game_map);
        }

        if(my_party.getPlayerFullness() <= 0){ //Checks if the player has starved.
            cout << "You have died from hunger! Game over." << endl;
            my_party.gameOver();
            gameOver(my_party, game_map);
        }
        for(int i = 0; i < my_party.getLivingMembers(); i++){ //Checks if a member has starved.
            if(my_party.getMemberFullness(i) <= 0){
                cout << "Oh no! Party member " << my_party.getMemberName(i) << " has starved to death! You will have to continue wihtout them." << endl;
                my_party.loseMember(i);
            }
        }
        if(my_party.getAngerLevel() == 100){ //Checks if the sorcerer has reached 100 anger
            cout << "Oh no! The sorcrer has become enraged and destroyed the dungeon. Game over. " << endl;
            my_party.gameOver();
            gameOver(my_party, game_map);
        }
        if(my_party.getLivingMembers() == 1){ //Checks if enough members are alive to continue.
            cout << "To much of your party has been lost. You are unable to continue with this many people. Game over." << endl;
            my_party.gameOver();
            gameOver(my_party, game_map);
        }

    }

    return 0;
}
#include "party.h"

//Constructors
    Party::Party(string playername){
        player.setMemberName(playername);
        gold = 100;
        alive = true;
        ingredients = 0;
        cookware[0] = 0;
        cookware[1] = 0;
        cookware[2] = 0;
        weapons[0] = 0;
        weapons[1] = 0;
        weapons[2] = 0;
        weapons[3] = 0;
        weapons[4] = 0;
        armor = 0;
        treasures[0] = 0;
        treasures[1] = 0;
        treasures[2] = 0;
        treasures[3] = 0;
        treasures[4] = 0;
        rooms_cleared = 0;
        keys = 0;
        anger_level = 0;
        livingMembers = 4;
        montsers_defeated = 0;
        sorcerer_defeated = false;
    }

//Getters

    string Party::getPlayerName(){
        return player.getMemberName();
    }

    int Party::getPlayerFullness(){
        return player.getMemberFullness();
    }

    string Party::getMemberName(int member_id){
        return party[member_id].getMemberName();
    }

    int Party:: getMemberFullness(int member_id){
        return party[member_id].getMemberFullness();
    }

    int Party::getGoldBalance(){
        return gold;
    }

    int Party::getIngredientsBalance(){
        return ingredients;
    }

    int Party::getCookware(int cookware_id){
        return cookware[cookware_id];
    }

    int Party::getWeapons(int weapon_id){
        return weapons[weapon_id];
    }

    int Party::getArmor(){
        return armor;
    }

    int Party::getTreasures(int treasure_id){
        return treasures[treasure_id];
    }

    bool Party::isAlive(){
        return alive;
    }

    int Party::getRoomsCleared(){
        return rooms_cleared;
    }

    int Party::getKeys(){
        return keys;
    }

    int Party::getAngerLevel(){
        return anger_level;
    }

    int Party::getLivingMembers(){
        return livingMembers;
    }

    int Party::getMonstersDefeated(){
        return montsers_defeated;
    }

    bool Party::isSorcererDefeated(){
        return sorcerer_defeated;
    }

//Setters

    void Party::setPlayerName(string player_name){
        player.setMemberName(player_name);
    }

    void Party::addAngerLevel(int amount){
        anger_level += amount;
    }

    void Party::roomCleared(){
        rooms_cleared++;
    }

    void Party::foundKey(){
        keys++;
    }

    void Party::useKey(){
        if( keys != 0){
            keys--;
        }        
    }

    void Party::setMemberName(int member_id, string name){
        party[member_id].setMemberName(name);
    }

    void Party::spendGold(int gold_spent){
        gold -= gold_spent;
    }

    void Party::gainGold(int gold_gained){
        gold += gold_gained;
    }

    void Party::gainIngredients(int ingredients_gained){
        ingredients += ingredients_gained;
    }

    void Party::spendIngredients(int ingredients_spent){
        ingredients -= ingredients_spent;
    }

    void Party::buyCookware(int cookware_id, int amount){
        cookware[cookware_id] += amount;
    }

    void Party::useCookware(int cookware_id){
        cookware[cookware_id]--;
    }

    void Party::buyWeapons(int weapon_id, int amount){
        weapons[weapon_id] += amount;
    }

    void Party::buyArmor(int amount_of_armor){
        armor += amount_of_armor;
    }

    void Party::gainTreasures(int treasure_id, int amount){
        treasures[treasure_id] += amount;
    }

    void Party::sellTreaures(int treasure_id, int amount){
        treasures[treasure_id] -= amount;
    }

    void Party::losePlayerFullness(){
        player.removeMemberFullness();
    }
    
    void Party::loseMemberFullness(int member_id){
        party[member_id].removeMemberFullness();
    }

    void Party::loseMember(int member_id){
        for(int i = member_id; i < livingMembers; i++){ //Moves living members up one in the array
            party[i] = party[i + 1];
        }
        livingMembers--;
    }

    void Party::gameOver(){
        alive = false;
    }

    void Party::defeatSorcerer(){
        sorcerer_defeated = true;
    }

    void Party::feedPlayer(int amount){
        player.addMemberFullness(amount);
    }

    void Party::feedMember(int member_id, int amount){
        party[member_id].addMemberFullness(amount);
    }

    void Party::losearmor(){
        armor--;
    }

    void Party::breakweapon(int weapon_id){
        weapons[weapon_id]--;
    }
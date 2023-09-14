#include <iostream>
#include "members.h"

class Party{
    private:
        Members player;
        Members party[4];
        int gold; //Gold stored
        int ingredients; //Ingredients stored
        int cookware[3]; //Cookware owned
        int weapons[5]; //Weapons owned
        int armor; //Armor you have
        int treasures[5]; //Treasured stored
        bool alive; //If you're alive
        int rooms_cleared; //Rooms cleared
        int keys; //Keys had
        int anger_level; //Anger level of sorcerer
        int livingMembers; //How many members are alive
        int montsers_defeated; //How many monsters have been defeated.
        bool sorcerer_defeated; //If the sorcerer is defeated.

    public:
        //Constructors
        Party(string playername);

        //Getters
        string getPlayerName();
        int getPlayerFullness();
        string getMemberName(int member_id);
        int getMemberFullness(int member_id);
        int getGoldBalance();
        int getIngredientsBalance();
        int getCookware(int cookware_id);
        int getWeapons(int weapon_id);
        int getArmor();
        int getTreasures(int treasure_id);
        bool isAlive();
        int getRoomsCleared();
        int getKeys();
        int getAngerLevel();
        int getLivingMembers();
        int getMonstersDefeated();
        bool isSorcererDefeated();

        //Setters
        void setPlayerName(string player_name);
        void addAngerLevel(int amount);
        void roomCleared();
        void foundKey();
        void useKey();
        void setMemberName(int member_id, string name);
        void spendGold(int gold_spent);
        void gainGold(int gold_gained);
        void gainIngredients(int ingredients_gained);
        void spendIngredients(int ingredients_spent);
        void buyCookware(int cookware_id, int amount);
        void useCookware(int cookware_id);
        void buyWeapons(int weapon_id, int amount);
        void buyArmor(int amount_of_armor);
        void gainTreasures(int treasure_id, int amount);
        void sellTreaures(int treasure_id, int amount);
        void losePlayerFullness();
        void loseMemberFullness(int member_id);
        void loseMember(int member_id);
        void gameOver();
        void defeatSorcerer();
        void feedPlayer(int amount);
        void feedMember(int member_id, int amount);
        void losearmor();
        void breakweapon(int weapon_id);




};
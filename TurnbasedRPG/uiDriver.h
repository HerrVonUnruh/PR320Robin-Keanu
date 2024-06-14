﻿#pragma once
#include <iostream>
#include <string>
#include <map>

class uiDriver
{
public:
    void displayMonster(int monsterIDs[], int monsterAmount);
    void displayBoss(int bossID);

    void displayMonsterStats(std::map<std::string, int> fighterStats[], int fighterStatsAmount);

    std::string* generatePlayerStatsLines(std::map<std::string, int> fighterStats, int& lineAmount);

    std::string drawMenu(std::string* playerStatLines, int lineAmount, std::string tagLine, std::string menuItems[], int menuItemCount);


    void drawTopLine();
    void drawCenterLine();
    void drawBottomLine();


    std::string topLine = "/=======================================================================================================\\";
    std::string centerLine = "|=======================================================================================================|";
    std::string bottomLine = "\\=======================================================================================================/";

    std::string playerGrafix[7] = {
        "You              ",
        "________         ",
        ") .  . (         ",
        "\\______/         ",
        "    |            ",
        "                 ",
        "                 "
    };

    std::string bossGrafix[3][13] = {
       { "|Infant Panda                                                                                           ",
         "|                                                            **%@@@@@@@@@&&                             ",
         "|                               (#%%%&&&&&&@@@@&%(,...(*..,%&&&&@@&&&&&&&&&&%                           ",
         "|                     (%%&&&&&&@@@@@@@@@@@@@@&%,....,#*../#&&&&&&&&&&&&&&&&&&%#                         ",
         "|                   #%%##(((##%&&&&&&&&@@@&&&/....../%%(/%&&&&&&&&&&&&&&&&&%%%%#                        ",
         "|                  ##/*,.....,,/#%%&&&&&&&&(,.......%&&&&&&&&&&&%%%&&&&&&%%%%%%#                        ",
         "|                 *,,...    .  .*##%%%&%&(,.....    *#%%%%%&&%%,..%%&&&%%,.#######                      ",
         "|                ,...         ..,(##%%%%(,...        (((##%%%*.,./*%%%%%%,..#%###                       ",
         "|               ,...           .*/(####/,......,....../##%%#(..,&&&&&%%&&&#.,####                       ",
         "|               .             .,,/((((/,,,,,.....    ..,#%%%##%&&&&&&&%%%%%#./###                       ",
         "|               ,.. .          ,,*/////,,,..,.... .   ...,#((/(%&%%##%#%#%%#(#                          ",
         "|               *....         ...,,*****..........     . ..,,.,*/#((*..,((#                             ",
         "|_______________________________________________________________________________________________________"
       },

       { "|Skellington                                                                                            ",
         "|                           **,*,%#*(###%%%#%###%&%&%%&&&&%(%&&&@&&&%%%%#%#/                            ",
         "|                           /**,,**%%/////*/**,,/#%&%%&%/#(#((((((/&%#%%%%#                             ",
         "|                            ****(%*,**,,..,,,,,*((#%%&((//** ***//*/@&#%#/                             ",
         "|                             ****&*/**,,,,.   ./// *&&& .  *///***/*&&%%/                              ",
         "|                              /,*/#*/*,,,,...((//* .,&&&%*****//*/*%&&%*                               ",
         "|                            .**,*(##%((#%%###(/*.****.(&@&@@&&&%&&&&&&%#                               ",
         "|                             #***######%%#(((/,*//**(/.,&@&&&&&&&&&%&&%%,                              ",
         "|                               /,(%%######/(((*#/(*/(*(*&&&&&&&&&&&&#&/                                ",
         "|                              */*(((@%#((*(*%%####&&&&&%&&%&&&%(*%#%%                                  ",
         "|                                 ,*// ,(/(*/#&##(#&#&&%&%&&%%&#, (#((                                  ",
         "|                                 *,/*. ***/,#(/###&#&%##(&#&%#& /((#                                   ",
         "|_______________________________________________________________________________________________________"
        },

        { "|The Kraken                                                                                             ",
          "|                            //***/*#%%#%%%(##%######(///*                               #&@&&&%&#(     ",
          "|                           (*,*,**/(###(#(####((###%%%%###*                         &&&&&###(/(/*      ",
          "|                           (,***   %*//(/((//#(##/((((##((*,                      *%@@&#(#(,,,/        ",
          "|                           (,  ,%@@%..,****//#//#*/###(/,(                       *%&%#/*(##/,          ",
          "|       (((((###(            \\ *.,,,,.....*,#**((*,,,,,..#%(/                     %%%%%%%&((*,.         ",
          "|          //#####(           ..,       .,*#(,/#**//,....,,,/*                   **#%(/**               ",
          "|           ////(#((          ((,      ,,*(*,,,****/(*.    .,/#(/               (%%#/,,,*               ",
          "|            //*/(#(((((#(##%#/,,. .../*/**(/,,,*./,*,*.   .,((#(#####%%      %%*(/////                 ",
          "|%&&##%        ((##%%%%###(/**,,..,,(*/,/*,..,,.,.**,*,....,,,**//////(%%#######%#/*,.                  ",
          "|##%%#%%%####%#%##(/(/////**//*,,##(//***./*..*./...,#*(,,,*/##(**///*/((#/###%#(#*,                    ",
          "|,%%*/###*%#%%%%###%%%(/(/((,,,/(((((/*,*.,,.    ,,*,***(//..%&,.#*(*/*%,,#(((////#,                    ",
          "|_______________________________________________________________________________________________________"
       }
    };

    std::string monsterGrafix[11][7] = {
        { "|                         ",
          "|                         ",
          "|                         ",
          "|                         ",
          "|                         ",
          "|                         ",
          "|_________________________" },

        // Monster 1
        { "|Big Bad Enemy            ",
          "|                         ",
          "|           O             ",
          "|          /|\\            ",
          "|          / \\            ",
          "|                         ",
          "|_________________________" },

          // Monster 2
          { "|Ugly Foe                 ",
            "|                         ",
            "|         (..)            ",
            "|         |  |            ",
            "|         W  W            ",
            "|                         ",
            "|_________________________" },

            // Monster 3
            { "|Ork                      ",
              "|                         ",
              "|       ^----^            ",
              "|       \\o  o/            ",
              "|        )__(             ",
              "|                         ",
              "|_________________________" },

              // Monster 4
              { "|Quandale                 ",
                "|      ___                ",
                "|     / ..\\               ",
                "|     \\___/               ",
                "|      | |                ",
                "|                         ",
                "|_________________________" },

                // Monster 5
                { "|Trigonous Terror         ",
                  "|                         ",
                  "|        (..)             ",
                  "|        /   \\            ",
                  "|       /_____\\           ",
                  "|                         ",
                  "|_________________________" },

                  // Monster 6
                  { "|Bubblenose               ",
                    "|                         ",
                    "|      (0)~~~(0)          ",
                    "|      /       \\          ",
                    "|     /___/ \\___\\         ",
                    "|                         ",
                    "|_________________________" },

                    // Monster 7
                    { "|Shadow Wraith            ",
                      "|                         ",
                      "|         //  \\\\          ",
                      "|        //    \\\\         ",
                      "|        \\ o  O /         ",
                      "|       _/      \\_        ",
                      "|_________________________" },

                      // Monster 8
                      { "|Eye Guy                  ",
                        "|                         ",
                        "|        ( O O O )        ",
                        "|       (   O O   )       ",
                        "|      (   (uuu)   )      ",
                        "|         v      v        ",
                        "|_________________________" },

                        // Monster 9
                        { "|Ponytail                 ",
                          "|                         ",
                          "|         (\\(\\            ",
                          "|         ( -.-)          ",
                          "|       o_(\")(\")          ",
                          "|                         ",
                          "|_________________________" },

                          // Monster 10
                          { "|Menancing-Spinning Top   ",
                            "|                         ",
                            "|         \\    /          ",
                            "|       --(o\\/o)--        ",
                            "|         /    \\          ",
                            "|                         ",
                            "|_________________________" }
    };

private:
    int charactersPerStatField = 26;
    int characterAmountForPlayerStats = 52;
};

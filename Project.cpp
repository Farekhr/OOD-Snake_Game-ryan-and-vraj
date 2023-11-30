#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"
#include "objPosArrayList.h"


using namespace std;



#define DELAY_CONST 100000


//OOD benefit, very limited globa variable declaration
//In Advanced OOD, there won't be any global variables
GameMechs* myGM;
Player*  myPlayer; // both are references
Food* tempFood;

//bool exitFlag; //ask to comment or not

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    

    myGM = new GameMechs(30,15); // makes the board size 30x15
    myPlayer = new Player(myGM);
    //exitFlag = false;

    //temporary position of the player
    // objPos tempPos; 
    // myPlayer-> getPlayerPos(tempPos);
    objPos tempPos{-1,-1,'%'}; // for testing only
    tempFood = new Food(tempPos); //doublwe check if we need this
    tempFood->generateFood(tempPos); //how to tunr this into arrayList operation
    
}

void GetInput(void)
{
   myGM->getInput(); //ask about this section
}


void RunLogic(void)
{
    
    //myGM->getInput();
    myPlayer-> updatePlayerDir();
    myPlayer->movePlayer();
    //myPlayer->checkFoodConsumption();
    myGM->clearInput(); //dont repeadtedly process same input
    
    
    // objPos tempPos; 
    // myPlayer-> getPlayerPos(tempPos);

    // objPos tempPosFood;
    // tempFood->getFoodPos(tempPosFood);

    // if((tempPos.x == tempPosFood.x) && (tempPos.y == tempPosFood.y)){
        
    // }
    // if(myPlayer->checkSelfCollision()){
    //     myGM->setExitTrue();
    // }
    
}

void DrawScreen(void)
{
   MacUILib_clearScreen(); 
    
    // objPos tempPos;
    // myPlayer->getPlayerPos(tempPos); // get player pos

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;
    bool drawn;
    //user to get coordinates of tempFood
    objPos tempPosFood;
    tempFood->getFoodPos(tempPosFood);
    //objPos myPlayer->7, 12, 'W');

        for (int i = 0; i < myGM->getBoardSizeY(); i++)
        {
            for (int j = 0; j < myGM->getBoardSizeX(); j++)
            {
                
                drawn = false;
                //iterate thorugh palyerbody and check if the copy matches i and j
                for(int k =0; k < playerBody->getSize(); k++){

                    playerBody->getElement(tempBody, k);

                    if(tempBody.x == j && tempBody.y == i){
                        MacUILib_printf("%c", tempBody.symbol);
                        drawn = true;
                    }

                }
                if(drawn) continue;
                objPos currentPos(j, i, ' ');
                


                if (i == 0 || i == myGM->getBoardSizeY() -1 || j == 0 || j == myGM->getBoardSizeX()-1)
                {
                    objPos borderPos(i, j, '#');
                    MacUILib_printf("%c", borderPos.getSymbol());
                }

                
                // Print food symbol randomly
                else if (i == tempPosFood.y && j == tempPosFood.x)
                {

                    MacUILib_printf("%c", tempPosFood.symbol);
                }

               
                else 
                {
                    MacUILib_printf("%c", currentPos.getSymbol());
                }
                //MacUILib_printf("i: %d j:%d\n", i, j);
            }

            MacUILib_printf("\n");

            
        }

        
        //MacUILib_printf("Input: %c\n", myGM->getInput());
        MacUILib_printf("BoardSize: %dx%d\n", 
                        myGM->getBoardSizeX(), 
                        myGM->getBoardSizeY() 
                        );

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    //ask about deleting off of the heap    
    
    MacUILib_uninit();

    //remove heap instances
    delete[] myGM;
    delete[] myPlayer;
}

/*

Food foodIntance = Food(player_pos); // objPo, 0, 0, o




\*/
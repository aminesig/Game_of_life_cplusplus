/*-----------------------------------------------------------------------------------
Author: Benziane M.Mohammed El Amine
Company: Bluefruit

Date :20/06/2015
Version:1.0.0.0

Processor: x86/x64/arm/mips
Compiler: gnu gcc compiler

Titolo/Title: Conway's Game of life

Description:
Evaluation for making a program in c++ to simulate Conway's game of life
------------------------------------------------------------------------------------*/
#include <QCoreApplication>
#include <iostream>

/********************************************* Global variables declaration *********************************/
#define height 8 //Define grid's height
#define width 8  //Define grid's width
bool grid[height][width]; //grid matrix
bool updated_grid[height][width]; //grid matrix of the updated generation
int generation_counter;
using namespace std;

/******************************************** Show Grid ******************************************************/
/* show grid function displays the current Conways universe based
on the height and width defined by the user */

void show_grid(bool buffer[width][height]){

 //Nested loop to display every cell on the grid
 for(int j=0;j<height;j++){
   for(int i=0;i<width;i++) {
      if(buffer[i][j] == 0)
            cout <<"." ; //print points if the current cell is not set alive by the user
      else
            cout <<"*";  //print asterisks if the current cell set alive by the user

    }
    cout<<""<<endl;  // when the point is equal to the grid max width the program jumps to draw the next line
  }
}
/***********************************************Update Grid*****************************************************/
/* show grid function displays the current Conways universe based
on the height and width defined by the user */
void update_grid(){

    int neighbours ;  // neighbours count to determin the rules to apply to the cells
    generation_counter++;    //generation counting

    //Nested loop to scan every single cell's neighbour in the grid
    for (int k=1;k<=height;k++)
    {
        for (int l=1; l<=width;l++)
        {
            neighbours=0;           //neighbours counter clear for every cout cycle

            //every single cell have the possibility to have up to 8 neighbours, so i scan
            //the cell's neighborhood to eventually determine the rules to apply to the cell
            if (grid[k-1][l-1] == 1) neighbours++;
            if (grid[k-1][l] == 1) neighbours++;
            if (grid[k-1][l+1] == 1) neighbours++;
            if (grid[k][l-1] == 1) neighbours++;
            if (grid[k][l+1] == 1) neighbours++;
            if (grid[k+1][l-1] == 1) neighbours++;
            if (grid[k+1][l] == 1) neighbours++;
            if (grid[k+1][l+1] == 1) neighbours++;

            //Applying the rules to the cell based on the previous count of the cell's neighbours

            if (grid[k][l] == 1 && neighbours < 2)
               updated_grid[k][l] = 0;  //first rule: Any live cell with fewer than two live neighbours dies

            else if (grid[k][l] == 1 && neighbours  > 3)
               updated_grid[k][l] = 0; //second rule: Any live cell with more than three live neighbours dies
            else if (grid[k][l] == 1 && (neighbours  == 2 || neighbours  == 3))
               updated_grid[k][l] = 1; //third rule : Any live cell with two or three live neighbours lives on to the next generation
            else if (grid[k][l] == 0 && neighbours  == 3)
               updated_grid[k][l] = 1; //forth rule : Any dead cell with exactly three live neighbours becomes a live cell
        }
    }
  show_grid(updated_grid);      //show the next updated generation grid

  //display the generation count
  cout << "Generation : " << generation_counter<< endl;

  //reassign the updated grid values to the initial grid for the next cycle
  for (int m=0;m<height;m++)
  {  for (int n=0; n<=width;n++)
      {
         grid[n][m]=updated_grid[n][m];
      }
  }

}

/*********************************************Main program ***********************************************************/
int main(int argc, char *argv[])
{
     int x, y; //coordinates variables used for user input
     int live_cells_number;

     /****************console input *******************/
     cout << left << "Conway's Game of Life." << endl;
     cout << "Press any key to start the game." << endl;
     cin.get(); //wait untill key is pressed

     //input how many live cells are needed
     cout <<"Input the number of the live cells you would like to start with:";
     cin >> live_cells_number ;

     //loop untill the chosen number of live cells coordinates are entered
     for(int j=0;j<live_cells_number;j++){
         //input how many live cells are needed
         cout <<"Input the X coordinate for the "<< j+1 << " live cell : ";
         cin >> x;
         cout <<"Input the Y coordinate for the "<< j+1 << " live cell : ";
         cin >> y;
         grid[x][y]=1;
     }

     //call function to show the initial grid with the first live cells set buy the user
     show_grid(grid);


     while(true){
         //input how many live cells are needed
         cout <<"Press anykey to proceed to the next generation";
         cin.get(); //wait untill key is pressed

         update_grid();
     }


     QCoreApplication a(argc, argv);
     return a.exec();
}

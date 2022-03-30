#include "./drawapp-2/graphics.c"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

const int width = 600;
const int height = 600;
const int gridSize = 60;
int numberOfRows = height / gridSize;
int numberOfColumns = width / gridSize;
int currentX = 0, currentY = 0, currentDir = 1;
int numberOfObsticles;
const int maxObsticles = 7 + 1;
int obsticlePositions[2][maxObsticles+1];
int targetX;
int targetY;

//For reference
#define North 0
#define East 1
#define South 2
#define West 3

int getNextX(int _x, int dir);
int getNextY(int _y, int dir);

void generateObsticles();
void drawObsticles();
void generateTarget();
void drawTarget();
void generateDefaultPos();
void generateDefaultDir();

bool isObsticle(int _x, int _y);

void drawBackground(){
  background();
  //Draw the background grid
  setColour(black);
  for (int row = 0; row <= numberOfRows; row++)
  {
    drawLine(0, row * gridSize, width, row * gridSize);
  }
  for (int col = 0; col < numberOfColumns; col++)
  {
    drawLine(col * gridSize, 0, col * gridSize, height);
  }
}

// Update the foreground layer to display the robot in a new position
void update(int x, int y, int dir)
{
  //x, y is TOP LEFT corner of grid square
  int xs[3];  
  int ys[3];
  switch (dir)
  {
  case 0:
    xs[0] = x; xs[1] = x + gridSize/2; xs[2] = x + gridSize;
    ys[0] = y + gridSize; ys[1] = y; ys[2] = y + gridSize;
    break;
  case 1:
    xs[0] = x; xs[1] = x; xs[2] = x + gridSize;
    ys[0] = y; ys[1] = y + gridSize; ys[2] = y + gridSize/2;
    break;
  case 2:
    xs[0] = x; xs[1] = x + gridSize/2; xs[2] = x + gridSize;
    ys[0] = y; ys[1] = y + gridSize; ys[2] = y;
    break;
  case 3:
    xs[0] = x + gridSize; xs[1] = x + gridSize; xs[2] = x;
    ys[0] = y; ys[1] = y + gridSize; ys[2] = y + gridSize/2;
    break;
  default:
    break;
  }
  // Clear the existing content, otherwise squares will just be added
  // and to what is already there.
  clear();
  setColour(green);
  fillPolygon(3, xs, ys);
  drawObsticles();
  drawTarget();
}

// Control the animation step-by-step
void move()
{
  // The animated shape is on the foreground (top) layer, which must be
  // selected.
  foreground();
  while (!(currentX == targetX * gridSize && currentY == targetY * gridSize))
  {
    //Check for obsticle, wall or target
    
    //Check if wall
    if (getNextX(currentX, currentDir) >= numberOfColumns * gridSize|| getNextX(currentX, currentDir) < 0)
    {
      if (targetY < currentY){//Target is 'north'
        //Face north
        currentDir = 0;
      }else if(targetY > currentY){//Target is 'south'
        //Face south
        currentDir = 2;
      } else { // target is in same row
        //Turn around
        currentDir = (currentDir + 2) % 4;
      }
    }
  
    //Check if ceiling or floor
    else if (getNextY(currentY, currentDir) >= numberOfRows * gridSize|| getNextY(currentY, currentDir) < 0 )
    {
      if (targetX < currentX){//Target is 'east'
        //Face east
        currentDir = 3;
      }else if (targetX > currentX){//Target is 'west'
        //Face west
        currentDir = 1;
      } else{ // target is in same column
        //tunr around
        currentDir = (currentDir + 2) % 4;
      }
    }

    //Check if target
    else if (getNextX(currentX, currentDir) == targetX * gridSize && getNextY(currentY, currentDir) == targetY * gridSize)
    {
      currentX = targetX * gridSize;
      currentY = targetY * gridSize;
    }

    //Check if obsticle
    else if (isObsticle(getNextX(currentX, currentDir), getNextY(currentY, currentDir)))
    {
      if (currentDir == 0 || currentDir == 2)
      {//Can only turn west or east
        if (targetX < currentX){//Target is 'west'
          //Face west
          currentDir = 3;
        }else if (targetX > currentX){//Target is 'west'
          //Face west
          currentDir = 1;
        } else{ // target is in same column
          //turn around
          currentDir = (currentDir + 2) % 4;
        }
      } else {//Can only turn north or south
        if (targetY < currentY){//Target is 'north'
          //Face north
          currentDir = 0;
        }else if(targetY > currentY){//Target is 'south'
          //Face south
          currentDir = 2;
        } else { // target is in same row
          //Turn around
          currentDir = (currentDir + 2) % 4;
        }
      }
    }

    //Can move forward
    else
    {
      currentX = getNextX(currentX, currentDir);
      currentY = getNextY(currentY, currentDir);
    }
    update(currentX, currentY, currentDir);
    sleep(500);  
  }
}

int getNextX(int _x, int dir)
{
  switch (dir)
  {
  case 1://East
    return _x + gridSize;
    break;
  case 3: //West
    return _x - gridSize;
  default: //North or South
    return _x;    
    break;
  }
}

int getNextY(int _y, int dir)
{
  switch (dir)
  {
  case 0: //North
    return _y - gridSize;
    break;
  case 2: //South
    return _y + gridSize;
    break;
  default: //East or West
    return _y;
    break;
  }
}

void generateObsticles()
{
  for (int i = 0; i < numberOfObsticles; i++)
  {
    int x = rand() % (numberOfColumns);
    int y = rand() % (numberOfRows);
    obsticlePositions[0][i]=x;
    obsticlePositions[1][i]=y;
  }
}

void drawObsticles()
{
  setColour(red);
  for (int i = 0; i < numberOfObsticles; i++)
  {
    fillRect(obsticlePositions[0][i] * gridSize, obsticlePositions[1][i] * gridSize, gridSize, gridSize);
  }
}

void generateTarget()
{
  targetX = rand() % numberOfColumns;
  targetY = rand() % numberOfRows;
}

void drawTarget(){
  setColour(gray);
  fillRect(targetX * gridSize, targetY * gridSize, gridSize, gridSize);
}

void generateDefaultPos(){
  currentX = rand() % numberOfColumns * gridSize;
  currentY = rand() % numberOfRows * gridSize;
}

void generateDefaultDir(){
  currentDir = rand() % 4;
}

bool isObsticle(int _x, int _y){
  for (int i = 0; i < numberOfObsticles; i++)
  {
    if (obsticlePositions[0][i] * gridSize == _x && obsticlePositions[1][i] * gridSize== _y)
    {
      return true;
      break;
    }
  }
  return false;
}

int main(void)
{
  srand(time(NULL)); //Actual random
  numberOfObsticles = rand() % (maxObsticles) + 1;

  setWindowSize(width, height);
  drawBackground();
  foreground();

  generateDefaultPos();
  generateDefaultDir();

  generateObsticles();
  generateTarget();

  move();
}
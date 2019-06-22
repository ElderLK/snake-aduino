#include <LiquidCrystal.h> 

//########DISPLAY LCD 16x2#############
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);    //Informamos a biblioteca quais serão os 
                                         // pinos do Arduíno que serão ligados aos
                                         // pinos do display, observe que a ordem
                                         // é a mesma da lista acima. Aqui também 
                                         // dou um nome do display, que neste caso
                                         // vai se chamar "lcd"

//##################JOYSTICK########################
int axis_X= A0; //PINO REFERENTE A LIGAÇÃO DO EIXO X
int axis_Y = A1; //PINO REFERENTE A LIGAÇÃO DO EIXO Y
int button = 8; //PINO REFERENTE A LIGAÇÃO NO PINO KEY (EIXO Z)
//##################################################


//##################SNAKE GAME########################
typedef struct snakeStruct
{
  int row,column;
  struct snakeStruct *next;
} SnakeBody;

boolean displayGame[16][80];
SnakeBody *head, *tail;

boolean gameOver, gameStarted;
int pc,pr;
int key, oldkey; 
int dir, olddir; // 1 - Down, 2 - Up, 3 - Left, 4 - Right
int selectedLevel = 1, levels = 3;
int gameSpeed, collected;
unsigned long timer, timeNow;


boolean levelz[3][2][16] = {
{{true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true},
{true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true}},
 
{{true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true},
{true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true}},
 
{{true,false,false,false,true,false,false,false,false,false,false,true,false,false,false,true},
{true,false,false,false,false,false,false,false,true,false,false,false,false,false,false,true}}
};


void createSnake(int n) // n = size of snake
{
  int i, j;
  for (i=0;i<16;i++)
    for (j=0;j<80;j++)
      displayGame[i][j] = false;
         
  SnakeBody *p, *q;
  tail = (SnakeBody*) malloc(sizeof(SnakeBody));
  tail->row = 8;
  tail->column = 39 + n/2;
  q = tail;
  displayGame[tail->row][tail->column] = true;
  for (i = 0; i < n-1; i++) // build snake from tail to head
  {
    p = (SnakeBody*) malloc(sizeof(SnakeBody));
    p->row = q->row;
    p->column = q->column - 1; //initial snake id placed horizoltally
    displayGame[p->row][p->column] = true;
    q->next = p;
    q = p;
  }
  if (n > 1)
  {
    q->next = NULL;
    head  = q;
  }
  else
  {
    tail->next = NULL;
    head = tail;
  }
}

void startMenu()
{
  int i;
  byte mySnake[8][8] = { { B00000, B00000, B00011, B00110, B01100, B11000, B00000, },
                         { B00000, B11000, B11110, B00011, B00001, B00000, B00000, },
                         { B00000, B00000, B00000, B00000, B00000, B11111, B01110, },
                         { B00000, B00000, B00011, B01111, B11000, B00000, B00000, },
                         { B00000, B11100, B11111, B00001, B00000, B00000, B00000, },
                         { B00000, B00000, B00000, B11000, B01101, B00111, B00000, },
                         { B00000, B00000, B01110, B11011, B11111, B01110, B00000, },
                         { B00000, B00000, B00000, B01000, B10000, B01000, B00000, } };
                         
  gameOver = gameStarted = false;
  key = oldkey = 0;
  olddir = 0;
  dir = 3;
  selectedLevel = 1;
 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Select level: 1");
  for( i = 0; i < 8; i++)
  {
    lcd.createChar(i,mySnake[i]);
    lcd.setCursor(i+4,1);
    lcd.write(byte(i));
  }
  collected = 0;
  gameSpeed = 8;
  createSnake(3);
  timer = 0;
}

void setup() {
 lcd.begin(16, 2); //
 pinMode (button, INPUT_PULLUP); // "_PULLUP" Active internal resistor
 startMenu();
 Serial.begin (9600); //INICIALIZA O MONITOR SERIAL
}

void loop() {

   key = get_key_moviment();
   delay(50);  //wait for debounce time
   if (key != oldkey){ //Is the direction unlike the previous one
      oldkey = key;
    
      // The game NOT started
      if (!gameOver && !gameStarted){
        oldkey = key;
          if (key > 0){
            switch(key){
              case 3:
                  if(selectedLevel > 1) selectedLevel--;
                break;
              case 4:
                  if(selectedLevel < levels) selectedLevel++;
                break;
              case 5:
                  lcd.clear();
                  newPoint();
                  gameStarted = true;
                break;
            }
            lcd.setCursor(14,0);
            lcd.print(selectedLevel);
          } 
      }
  
      // The game started
      if (!gameOver && gameStarted){
       delay(1000/gameSpeed);
        if (key > 0 && key < 5){
          // 1 - Down, 2 - Up, 3 - Left, 4 - Right
          if((dir == 1 || dir == 2) && (key == 3 || key == 4)){
            dir = key;
          }else if ((dir == 3 || dir == 4) && (key == 1 || key == 2)){
             dir = key;
          }
        }
      }
    
   }
   if (!gameOver && gameStarted){
      drawMoviment();
   }

  if(gameOver && key == 5)
  {
     startMenu();
     delay(100);
  }
    
}

void drawMatrix()
{
  int cc=0;
  byte myChar[8];
  boolean special;
  if (!gameOver)
  {
   displayGame[pr][pc] = true;
  for(int r=0;r<2;r++)
  {
    for(int c=0;c<16;c++)
    {
      special = false;
      for(int i=0;i<8;i++)
      {
        byte b=B00000;
        if (displayGame[r*8+i][c*5+0]) {b+=B10000; special = true;}
        if (displayGame[r*8+i][c*5+1]) {b+=B01000; special = true;}
        if (displayGame[r*8+i][c*5+2]) {b+=B00100; special = true;}
        if (displayGame[r*8+i][c*5+3]) {b+=B00010; special = true;}
        if (displayGame[r*8+i][c*5+4]) {b+=B00001; special = true;}
        myChar[i] = b;
      }
      if (special)
      {
        lcd.createChar(cc, myChar);
        lcd.setCursor(c,r);
        lcd.write(byte(cc));
        cc++;
      }
      else
      {
        lcd.setCursor(c,r);
        if (levelz[selectedLevel][r][c]) lcd.write(255);
        else lcd.write(254);
      }
    }
  }
  }
}

void drawMoviment(){
     timeNow = millis();
     if (timeNow - timer > 1000 / gameSpeed)
     {
       moveSnake();
       drawMatrix();
       timer = millis();
     }
}

void moveHead(){

  switch(dir) // 1 - Down, 2 - Up, 3 - Left, 4 - Right
  {
    case 1: head->row--; break;
    case 2: head->row++; break;
    case 3: head->column--; break;
    case 4: head->column++; break;
    default : break;
  }
if (head->column >= 80) head->column = 0;
else if (head->column < 0) head->column = 79;
else if (head->row >= 16) head->row = 0;
else if (head->row < 0) head->row = 15;

 if (levelz[selectedLevel][head->row / 8][head->column / 5]) gameOver = true; // wall collision check

// ######### Verify if has a snake collision ###########
  SnakeBody *p;
  p = tail;
  while (p != head) // self collision
  {
    if (p->row == head->row && p->column == head->column){
      gameOver = true;
      break;
    }
    p = p->next;
  }
// #####################################################

  if (gameOver) {
    gameOverFunction();
  }else {
    displayGame[head->row][head->column] = true;
    if (head->row == pr && head->column == pc) // point pickup check
    {
      collected++;
      if (gameSpeed < 25) gameSpeed += 3;
      newPoint();
    }
  }
}

void moveTail(){
  SnakeBody *p, *q;
  q = p = tail;
  displayGame[p->row][p->column] = false;
  tail = p->next;
  while (p->next != head){
    p = p->next;
  }
  // Preparation to Make New Head
  SnakeBody * oldHead = (SnakeBody *) malloc(sizeof(SnakeBody));
  oldHead->row = head->row;
  oldHead->column = head->column;
  oldHead->next = head;
  p->next = oldHead;
  free(q);
}

void moveSnake()
{
  moveTail();
  moveHead();
}

void newPoint()
{
 
  SnakeBody *p;
  p = tail;
  boolean newp = true;
  while (newp)
  {
    pr = random(16);
    pc = random(80);
    newp = false;
    if (levelz[selectedLevel][pr / 8][pc / 5]) newp=true;
    while (p->next != NULL)
    {
      if (p->row == pr && p->column == pc){
        newp = true;
        break;
      }
      p = p->next;
    }
  }
 
 if (collected < 20 && gameStarted) growSnake();
}

void growSnake()
{
  SnakeBody *p = (SnakeBody*)malloc(sizeof(SnakeBody));
  p->row = tail->row;
  p->column = tail->column;
  p->next = tail;
  tail = p;
}

void gameOverFunction()
{
  delay(1000);
  lcd.clear();
  freeList();
  lcd.setCursor(3,0);
  lcd.print("Game Over!");
  lcd.setCursor(4,1);
  lcd.print("Score: ");
  lcd.print(collected);
  delay(1000);
}

void freeList()
{
  SnakeBody *p,*q;
  p = tail;
  while (p!=NULL)
  {
    q = p;
    p = p->next;
    free(q);
  }
  head = tail = NULL;
}

// 1 - Up, 2 - Down, 3 - Left, 4 - Right
int get_key_moviment(){
    int k = -1;
    if((analogRead(axis_X)) < 100){ // BECAUSE JOYSTICK IS NOT GOOD :(
        k = 2;
    }else{
      if((analogRead(axis_X)) > 900){ //SE LEITURA FOR MAIOR 900
          k = 1;
      }else{
              if((analogRead(axis_Y)) < 100){ //SE LEITURA FOR MENOR 18
                k = 3;
              }else{
                    if((analogRead(axis_Y)) > 900){  //SE LEITURA FOR MAIOR 900
                         k = 4;
                    }else{
                          if(digitalRead(button) == LOW){ //SE LEITURA FOR IGUAL A HIGH, FAZ
                             k = 5;
                          }  
                    }
              }
      }
    }
    return k;
}

void printMatrix()
{
  Serial.println();
  Serial.println();
  Serial.println();
  for (int i=0;i<16;i++)
  {
    for (int j=0;j<80;j++)
    {
      Serial.print(displayGame[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }
}

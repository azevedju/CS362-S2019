#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    char randChar ;
    char testChar [9];
    int randInt;
   
    //Populate character array with characters from target statements
    testChar[0] = '[' ;
    testChar[1] = '(' ;
    testChar[2] = '{' ;
    testChar[3] = ' ' ;
    testChar[4] = 'a' ;
    testChar[5] = 'x' ;
    testChar[6] = '}' ;
    testChar[7] = ')' ;
    testChar[8] = ']' ;

    //Generate a random number between 0 and 8
    randInt = rand() % 9 ;

    //Copy the character at the location of the randInt into the return value.
    randChar = testChar[randInt] ;
	
    return randChar;
}

char *inputString()
{
   
    int i;
    int randInt;
    char testChar[5];
    char randString [6];	
    
    //Populate character array with characters from target statements
    testChar[0] = 'r';
    testChar[1] = 'e';
    testChar[2] = 's';
    testChar[3] = 't';
    testChar[4] = '\0';

    //Loop through the return char array and randomly populate it with characters
    //from the testChar array. 
    for(i=0 ; i < 6 ; i++){

    	randInt = rand() % 5 ;
    	randString[i] = testChar[randInt];
    }
	

    return randString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}

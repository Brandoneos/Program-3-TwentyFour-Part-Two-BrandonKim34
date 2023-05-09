
/*----------------------------------------
Program 3: TwentyFour Part 2
Course: CS 211, Spring 2023, UIC
System: Replit
Author: Brandon Kim 
-----------------------------------------*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//Node structure
typedef struct Node *NodePtr; // Make NodePtr to be a synonym for: struct Node *
struct Node {
  char *c;       // The word stored at the node
  NodePtr pNext; // Pointer to the next node
};
//Function to display the linked list
void displayList(NodePtr pHead) {
  printf("Displaying:\n");
  while (pHead != NULL) {
    printf("%s ", pHead->c);
    pHead = pHead->pNext;
  }

  printf("\n");
} // end displayList()
//function to pop last element of the linked list, return string as the returnstring
void pop(NodePtr *pHead, char *returnstring) {
  // char ca[3];
  NodePtr prev = NULL;
  if (*pHead == NULL) {
    // list is empty so just return;
    strcpy(returnstring, "#");
    return;
  }
  NodePtr pTemp = *pHead;
  while (pTemp->pNext != NULL) {
    prev = pTemp;
    pTemp = pTemp->pNext;
  }
  // printf("Test pop\n");
  // printf("c:%s\n", pTemp->c);
  int i;

  strcpy(returnstring, pTemp->c);
  // ca = pTemp->c;
  // printf("Test pop2\n");
  if (pTemp == *pHead) {
    free(pTemp->c);
    free(pTemp);
    *pHead = NULL;
  } else {

    prev->pNext = NULL;
    free(pTemp->c);
    free(pTemp);
  }
  // printf("ca:%s\n",ca);
  // return ca;
}
void appendNode(NodePtr *pHead, char *c1) {
  NodePtr pNewNode;
  pNewNode = malloc(sizeof(struct Node));
  pNewNode->c = malloc(sizeof(char) * 5);

  strcpy(pNewNode->c, c1);
  pNewNode->pNext = NULL;
  if (*pHead == NULL) {
    // list is empty so make the new node the first one
    *pHead = pNewNode;
    return;
  }
  NodePtr pTemp = *pHead;
  // Iterate until end
  while (pTemp->pNext != NULL) {
    pTemp = pTemp->pNext;
  }
  pTemp->pNext = pNewNode;

} // end appendNode()

// Function to display the greeting message when starting the program
void displayGreeting() {
  printf("Welcome to the game of TwentyFour Part Two!\n");
  printf("Use each of the four numbers shown exactly once, \n");
  printf("combining them somehow with the basic mathematical operators "
         "(+,-,*,/) \n");
  printf("to yield the value twenty-four.\n");
}
//function to clear the allocated array with the numbers from the file
void clearArray(char **array, int *size) {
  int x;
  for (x = 0; x < *size; x++) {
    free(array[x]); // free each string of array
  }
  free(array); // free array
  array = malloc(1 * sizeof(char *));
  *size = 0;
}
//function to display the array of numbers from the file, used for testing
void displayArray(char **array, int arraySize) {

  int i;
  for (i = 0; i < arraySize; i++) {
    printf("Line: %s\n", array[i]);
  }
}

// Function to display the ending message when exiting the program
void displayEnding() {
  printf("\nThanks for playing!\n");
  printf("Exiting...\n");
}
//function for the user to choose a difficulty at the beginning of program
void chooseDifficulty(char input1) {
  printf("Choose your difficulty level: E for easy, M for medium, and H for "
         "hard (default is easy).\n");
  printf("Your choice --> ");
  scanf("%c", &input1);
}
//function to randomly generate the 4 numbers from the file
void generateNumbers(char input, int *n1, int *n2, int *n3, int *n4,
                     char **array, int *numberOfElements) {
  int randomNumber;
  char *string1;

  int index = 0;
  index = input - 'A';
  FILE *filePtr;
  char inputString[81];
  switch (index) {
  case 4: // Easy
    filePtr = fopen("easy.txt", "r");
    break;
  case 12: // Medium
    filePtr = fopen("medium.txt", "r");
    break;
  case 7:
    filePtr = fopen("hard.txt", "r");
    break;
  default:
    filePtr = fopen("easy.txt", "r");
    break;
  }
  if (filePtr == NULL) {
    printf("Error: could not open %s for reading\n", "easy.txt");
    exit(-1);
  }
  char *modifiedString;
  int isFirstWord = 1;
  while (fgets(inputString, 81, filePtr) != NULL) {
    modifiedString = inputString;
    if (modifiedString[strlen(inputString) - 1] == '\n') {
      modifiedString[strlen(inputString) - 1] = 0;
    }
    // printf("MS: %s",modifiedString);
    // printf("test:%lu\n",strlen(modifiedString));
    if (isFirstWord) {
      // first word, allocate memory for string and store value with strcpy
      array[(*numberOfElements)] =
          malloc(sizeof(char) * (strlen(inputString) + 1));
      strcpy(array[(*numberOfElements)], inputString);
      *numberOfElements = 1;
      isFirstWord = 0;
    } else {
      array = (char **)realloc(
          array, ((*numberOfElements) + 1) *
                     sizeof(char *)); // make space for new word in array1
      if (!array) {
        printf("Error in reallocating new array\n");
      }
      array[(*numberOfElements)] =
          malloc(sizeof(char) * (strlen(inputString) + 1));
      strcpy(array[(*numberOfElements)], inputString);
      (*numberOfElements)++;
      // allocate and store the new word read from file into array1
    }
    // add to dynamically allocated array after removing the newline char from
    // fgets
  }
  fclose(filePtr);
  // printf("Displaying:%d:\n",*numberOfElements);
  // displayArray(array, *numberOfElements);
  randomNumber = rand() % (*numberOfElements);
  string1 = array[randomNumber];
  // printf("String1: %c\n", (*string1));
  *n1 = (*string1) - '0';
  *n2 = (*(string1 + 2)) - '0';
  *n3 = (*(string1 + 4)) - '0';
  *n4 = (*(string1 + 6)) - '0';
  clearArray(array, numberOfElements);
  *numberOfElements = 0;
  return;
}
//function to calculations, only returns the number given
int evaluate6(char *string, int foundInd) {
  int value = -1;
  int i = foundInd;
  int j = 0;
  char ch[7] = "      ";
  while (isdigit(string[i])) {
    ch[j] = string[i];
    i++;
    j++;
  }
  ch[j] = '\0';
  value = atoi(ch);
  return value;
}
//function to do a calculation with 2 numbers and an operator
int evaluate2(int v1, char op, int v2) {
  int answer = -1000;

  if (op == '*') {
    answer = v1 * v2;
    printf("%d %c %d = %d.\n", v1, '*', v2, answer);
  } else if (op == '/') {
    answer = v1 / v2;
    printf("%d %c %d = %d.\n", v1, '/', v2, answer);
  } else if (op == '+') {
    answer = v1 + v2;
    printf("%d %c %d = %d.\n", v1, '+', v2, answer);
  } else if (op == '-') {
    answer = v1 - v2;
    printf("%d %c %d = %d.\n", v1, '-', v2, answer);
  } else {
  }
  return answer;
}
//function to evaluate an entire string of numbers and operators
int evaluate5(char *string) {
  char string2[8] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
  int total = 0;
  int count = 7;
  int v1 = -1;
  int v2 = -1;
  int v3 = -1;
  int v4 = -1;
  int foundNum = -1;
  int string2size = 0;
  char o1 = '#';
  char o2 = '#';
  char o3 = '#';
  int op1 = -1;
  int op2 = -1;
  int op3 = -1;
  int evalu1 = -1000;
  int evalu2 = -1000;
  int evalu3 = -1000;
  int i;
  for (i = 0; i <= 6; i++) {
    if (isdigit(string[i])) {
      foundNum = i;
      break;
    }
  }

  for (i = 0; i < (strlen(string) - foundNum); i++) {
    string2[i] = string[foundNum + i];
  }
  for (i = 0; string2[i] != ' '; i++) {
    string2size++;
    if (string2[i] == '+' || string2[i] == '-' || string2[i] == '*' ||
        string2[i] == '/') {
      // printf("Stringi:%c\n",string[i]);
      if (o1 == '#') {
        o1 = string2[i];
        op1 = i;
      } else if (o2 == '#') {
        o2 = string2[i];
        op2 = i;
      } else if (o3 == '#') {
        o3 = string2[i];
        op3 = i;
      }
    }
  }
  // printf("string2:%s\n",string2);
  // printf("op1:%d\n",op1);
  // printf("op2:%d\n",op2);
  // printf("op3:%d\n",op3);

  char numb1[5] = {' ', ' ', ' ', ' ', '\0'};
  char numb2[5] = {' ', ' ', ' ', ' ', '\0'};
  char numb3[5] = {' ', ' ', ' ', ' ', '\0'};
  int u;
  // 12+3+4+4
  if (o1 != '#') {
    for (u = 0; u < (op1); u++) {
      numb1[u] = string2[u];
    }
    numb1[u] = '\0';
    if (op2 == -1) {
      op2 = string2size;
    }
    for (u = 0; u < (op2 - op1 - 1); u++) {
      numb2[u] = string2[u + op1 + 1];
    }
    numb2[u] = '\0';
    // printf("numb1:%s\n",numb1);
    // printf("numb2:%s\n",numb2);
    v1 = atoi(numb1);
    v2 = atoi(numb2);
    if (o2 != '#') {
      if (op3 == -1) {
        op3 = string2size;
      }
      for (u = 0; u < (op3 - op2 - 1); u++) {
        numb3[u] = string2[u + op2 + 1];
      }
      numb3[u] = '\0';
      v3 = atoi(numb3);
    }
  }
  // printf("v1:%d\n",v1);
  // printf("v2:%d\n",v2);
  // printf("o1:%c\n",o1);

  if (o2 == '#') {
    count = 3;
  } else if (o3 == '#') {
    count = 5;
  } else {
    count = 7;
  }
  if (count == 3) {
    evalu1 = evaluate2(v1, o1, v2);
    total = evalu1;
  } else if (count == 5) {
    if (o1 == '*' || o1 == '/') {
      evalu1 = evaluate2(v1, o1, v2);
      evalu2 = evaluate2(evalu1, o2, v3);
      total = evalu2;
    } else if (o2 == '*' || o2 == '/') {
      evalu2 = evaluate2(v2, o2, v3);
      evalu1 = evaluate2(v1, o1, evalu2);
      total = evalu1;
    } else {
      evalu1 = evaluate2(v1, o1, v2);
      evalu2 = evaluate2(evalu1, o2, v3);
      total = evalu2;
    }
  } else if (count == 7) {
    // printf("Should print\n");
    if (o1 == '*' || o1 == '/') {
      evalu1 = evaluate2(v1, o1, v2);
      if (o2 == '*' || o2 == '/') {
        evalu2 = evaluate2(evalu1, o2, v3);
        evalu3 = evaluate2(evalu2, o3, v4);
        total = evalu3;
      } else if (o3 == '*' || o3 == '/') {
        evalu3 = evaluate2(v3, o3, v4);
        evalu2 = evaluate2(evalu1, o2, evalu3);
        total = evalu2;
      } else {
        evalu2 = evaluate2(evalu1, o2, v3);
        evalu3 = evaluate2(evalu2, o3, v4);
        total = evalu3;
      }

    } else if (o2 == '*' || o2 == '/') {
      evalu2 = evaluate2(v2, o2, v3);
      if (o3 == '*' || o3 == '/') {
        evalu3 = evaluate2(evalu2, o3, v4);
        evalu1 = evaluate2(v1, o1, evalu3);
        total = evalu1;
      } else {
        evalu1 = evaluate2(v1, o1, evalu2);
        evalu3 = evaluate2(evalu1, o3, v4);
        total = evalu3;
      }
    } else if (o3 == '*' || o3 == '/') {
      evalu3 = evaluate2(v3, o3, v4);
      evalu1 = evaluate2(v1, o1, v2);
      evalu2 = evaluate2(evalu1, o2, evalu3);
      total = evalu2;
    } else {
      evalu1 = evaluate2(v1, o1, v2);
      evalu2 = evaluate2(evalu1, o2, v3);
      evalu3 = evaluate2(evalu2, o3, v4);
      total = evalu3;
    }
  }
  // 123,12,1 to string

  return total;
}
//another function to calculate the string given with different numbers and operators, returns the calculated value
int evaluate3(char *string) {
  int total = 0;
  int count = 7;
  int v1 = -1;
  int v2 = -1;
  int v3 = -1;
  int v4 = -1;
  char o1 = '#';
  char o2 = '#';
  char o3 = '#';
  int opInd = -1;
  int beginN = -1;
  int beginNSize = 0;
  int beginN2 = -1;
  int beginN2Size = 0;
  int evalu1 = -1000;
  int evalu2 = -1000;
  int evalu3 = -1000;
  int i;
  int eval = 0;
  for (i = 0; i <= 6; i++) {

    if (string[i] == '+' || string[i] == '-' || string[i] == '*' ||
        string[i] == '/') {
      opInd = i;
      o1 = string[i];
    } else if (isdigit(string[i])) {
      if (opInd == -1) {
        // still first number
        if (beginN == -1) {
          beginN = i;
        }
        beginNSize++;
      } else {
        // second number
        if (beginN2 == -1) {
          beginN2 = i;
        }
        beginN2Size++;
      }
    }
  }
  char numb1[5] = {' ', ' ', ' ', ' ', '\0'};
  char numb2[5] = {' ', ' ', ' ', ' ', '\0'};
  int u;
  for (u = 0; u < beginNSize; u++) {
    numb1[u] = string[u + beginN];
  }
  numb1[beginNSize] = '\0';
  for (u = 0; u < beginN2Size; u++) {
    numb2[u] = string[u + beginN2];
  }
  numb2[beginN2Size] = '\0';
  v1 = atoi(numb1);
  v2 = atoi(numb2);

  if (o2 == '#') {
    count = 3;
  } else if (o3 == '#') {
    count = 5;
  } else {
    count = 7;
  }
  if (count == 3) {
    evalu1 = evaluate2(v1, o1, v2);
    total = evalu1;
  } else if (count == 5) {
    if (o1 == '*' || o1 == '/') {
      evalu1 = evaluate2(v1, o1, v2);
      evalu2 = evaluate2(evalu1, o2, v3);
      total = evalu2;
    } else if (o2 == '*' || o2 == '/') {
      evalu2 = evaluate2(v2, o2, v3);
      evalu1 = evaluate2(v1, o1, evalu2);
      total = evalu1;
    } else {
      evalu1 = evaluate2(v1, o1, v2);
      evalu2 = evaluate2(evalu1, o2, v3);
      total = evalu2;
    }
  } else if (count == 7) {
    // printf("Should print\n");
    if (o1 == '*' || o1 == '/') {
      evalu1 = evaluate2(v1, o1, v2);
      if (o2 == '*' || o2 == '/') {
        evalu2 = evaluate2(evalu1, o2, v3);
        evalu3 = evaluate2(evalu2, o3, v4);
        total = evalu3;
      } else if (o3 == '*' || o3 == '/') {
        evalu3 = evaluate2(v3, o3, v4);
        evalu2 = evaluate2(evalu1, o2, evalu3);
        total = evalu2;
      } else {
        evalu2 = evaluate2(evalu1, o2, v3);
        evalu3 = evaluate2(evalu2, o3, v4);
        total = evalu3;
      }

    } else if (o2 == '*' || o2 == '/') {
      evalu2 = evaluate2(v2, o2, v3);
      if (o3 == '*' || o3 == '/') {
        evalu3 = evaluate2(evalu2, o3, v4);
        evalu1 = evaluate2(v1, o1, evalu3);
        total = evalu1;
      } else {
        evalu1 = evaluate2(v1, o1, evalu2);
        evalu3 = evaluate2(evalu1, o3, v4);
        total = evalu3;
      }
    } else if (o3 == '*' || o3 == '/') {
      evalu3 = evaluate2(v3, o3, v4);
      evalu1 = evaluate2(v1, o1, v2);
      evalu2 = evaluate2(evalu1, o2, evalu3);
      total = evalu2;
    } else {
      evalu1 = evaluate2(v1, o1, v2);
      evalu2 = evaluate2(evalu1, o2, v3);
      evalu3 = evaluate2(evalu2, o3, v4);
      total = evalu3;
    }
  }
  // 123,12,1 to string
  // char return1[10] = "          ";
  // int digits = log10(total) + 1; // number of digits
  // int k;
  // int ret;
  // int d = digits;
  // for (k = 0; k < digits; k++) {
  //   ret = total / pow(10, d - 1);
  //   return1[k] = ret + '0';
  //   total = total - (ret * pow(10, d - 1));
  //   d--;
  // }
  // return1[k] = '\0';
  // printf("Return1:%s\n", return1);
  return total;
}
//another function to calculate the string given with different numbers and operators, returns the calculated value
int evaluate(char *string) {
  int total = 0;
  int count = 7;
  int v1 = -1;
  int v2 = -1;
  int v3 = -1;
  int v4 = -1;
  char o1 = '#';
  char o2 = '#';
  char o3 = '#';
  int evalu1 = -1000;
  int evalu2 = -1000;
  int evalu3 = -1000;
  int i;
  int eval = 0;
  for (i = 0; i <= 6; i++) {
    if (isdigit(string[i])) {
      if (v1 < 0) {
        v1 = string[i] - '0';
      } else if (v2 < 0) {
        v2 = string[i] - '0';
      } else if (v3 < 0) {
        v3 = string[i] - '0';
      } else if (v4 < 0) {
        v4 = string[i] - '0';
      } else {
        // error
      }

    } else if (string[i] == '+' || string[i] == '-' || string[i] == '*' ||
               string[i] == '/') {
      if (o1 == '#') {
        o1 = string[i];
      } else if (o2 == '#') {
        o2 = string[i];
      } else if (o3 == '#') {
        o3 = string[i];
      } else {
        // error
      }
    }
  }

  if (o2 == '#') {
    count = 3;
  } else if (o3 == '#') {
    count = 5;
  } else {
    count = 7;
  }
  if (count == 3) {
    evalu1 = evaluate2(v1, o1, v2);
    total = evalu1;
  } else if (count == 5) {
    if (o1 == '*' || o1 == '/') {
      evalu1 = evaluate2(v1, o1, v2);
      evalu2 = evaluate2(evalu1, o2, v3);
      total = evalu2;
    } else if (o2 == '*' || o2 == '/') {
      evalu2 = evaluate2(v2, o2, v3);
      evalu1 = evaluate2(v1, o1, evalu2);
      total = evalu1;
    } else {
      evalu1 = evaluate2(v1, o1, v2);
      evalu2 = evaluate2(evalu1, o2, v3);
      total = evalu2;
    }
  } else if (count == 7) {
    if (o1 == '*' || o1 == '/') {
      evalu1 = evaluate2(v1, o1, v2);
      if (o2 == '*' || o2 == '/') {
        evalu2 = evaluate2(evalu1, o2, v3);
        evalu3 = evaluate2(evalu2, o3, v4);
        total = evalu3;
      } else if (o3 == '*' || o3 == '/') {
        evalu3 = evaluate2(v3, o3, v4);
        evalu2 = evaluate2(evalu1, o2, evalu3);
        total = evalu2;
      } else {
        evalu2 = evaluate2(evalu1, o2, v3);
        evalu3 = evaluate2(evalu2, o3, v4);
        total = evalu3;
      }

    } else if (o2 == '*' || o2 == '/') {
      evalu2 = evaluate2(v2, o2, v3);
      if (o3 == '*' || o3 == '/') {
        evalu3 = evaluate2(evalu2, o3, v4);
        evalu1 = evaluate2(v1, o1, evalu3);
        total = evalu1;
      } else {
        evalu1 = evaluate2(v1, o1, evalu2);
        evalu3 = evaluate2(evalu1, o3, v4);
        total = evalu3;
      }
    } else if (o3 == '*' || o3 == '/') {
      evalu3 = evaluate2(v3, o3, v4);
      evalu1 = evaluate2(v1, o1, v2);
      evalu2 = evaluate2(evalu1, o2, evalu3);
      total = evalu2;
    } else {
      evalu1 = evaluate2(v1, o1, v2);
      evalu2 = evaluate2(evalu1, o2, v3);
      evalu3 = evaluate2(evalu2, o3, v4);
      total = evalu3;
    }
  }
  return total;
}

void checkInput(char *input2, int n1, int n2, int n3, int n4,
                int *checkInput1) {
  *checkInput1 = 0;
  input2[strlen(input2) - 1] = '\0';
  int opC = 0;
  int n1u = 0;
  int n2u = 0;
  int n3u = 0;
  int n4u = 0;
  int par = 0;
  int valid1 = 0;
  int i = 0;
  int inp = 0;
  while (input2[i] != '\0') {
    if (input2[i] != '+' && input2[i] != '-' && input2[i] != '*' &&
        input2[i] != '/' && input2[i] != '(' && input2[i] != ')' &&
        input2[i] != ' ' && !(isdigit(input2[i]))) {
      valid1 = 1;
      // if any of the arguments were not the correct operators, then it cause
      // an error, 4,4,3,6
    }
    inp = input2[i] - '0';
    if (inp == n1 && n1u == 0) {
      n1u = 1;
    } else if (inp == n2 && n2u == 0) {
      n2u = 1;
    } else if (inp == n3 && n3u == 0) {
      n3u = 1;
    } else if (inp == n4 && n4u == 0) {
      n4u = 1;
    }
    if (input2[i] == '(') {
      par--;
    } else if (input2[i] == ')') {
      par++;
    }
    if (input2[i] == '+' || input2[i] == '-' || input2[i] == '*' ||
        input2[i] == '/') {
      opC++;
    }

    i++;
  }
  // Need to account for right characters***
  if (valid1 == 1) { // this is wrong
    printf("Error! Invalid symbol entered. Please try again.\n\n");
    // firstTimeThrough = 1;
    // break;
    // generate different numbers
    *checkInput1 = 1;
    return;
  }
  if ((n1u + n2u + n3u + n4u) != 4) {
    printf("Error! You must use all four numbers, and use each one only once. "
           "Please try again.\n\n");

    *checkInput1 = 1;
    return;
  }
  if (par > 0) {
    printf("Error! Too many closing parentheses in the expression.\n\n");
    *checkInput1 = 1;
    return;
  }
  if (opC != 3) {
    printf("Error! Too many values in the expression.\n\n");
    *checkInput1 = 1;
    return;
  }
}
//function to calculate based on the user input and the linked list, returns whether the calculations worked or not.
void calculate(char *string, NodePtr *pHead, int *listSize, int *worked) {
  int leftPar = 0;
  int rightPar = 0;
  char evalString[7] = "       ";
  char operator1;
  int eval;
  int val1 = -1;
  int val2 = -1;
  int i;
  char str2[2] = {'#', '\0'};
  for (i = 0; i < strlen(string); i++) {
    if (string[i] != '\n' && string[i] != '\0') {
      if (string[i] == '(') {
        leftPar++;
        str2[0] = string[i];
        appendNode(pHead, str2);


      } else if (isdigit(string[i])) {
        // val1 = string[i] - '0';
        str2[0] = string[i];
        // printf("digit:%s\n",str2);
        appendNode(pHead, str2);
        // displayList(*pHead);
      } else if (string[i] == '+' || string[i] == '-' || string[i] == '*' ||
                 string[i] == '/') {
        // operator1 = string[i];
        str2[0] = string[i];
        appendNode(pHead, str2);
        // displayList(*pHead);
      } else if (isdigit(string[i])) {
        // val2 = string[i] - '0';
        str2[0] = string[i];
        appendNode(pHead, str2);
        // displayList(*pHead);
      } else if (string[i] == ')') {
        rightPar++;
        if (leftPar > 0) {
          // evaluate what's in parentheses
          int x = 6;
          int j = 0;
          char popped[10] = "         ";

          pop(pHead, popped);
          // displayList(*pHead);
          int b;
          for (b = 0; b < 7; b++) {
            evalString[b] = ' ';
          }
          // printf("EvalStringBefore:%s\n", evalString);
          // displayList(*pHead);
          while (popped[0] != '(' && popped[0] != '#') {
            // printf("EvalStringInloop:%s\n", evalString);
            // printf("Popped:%s\n", popped);
            if (popped[0] != '(' && popped[0] != ')') {
              for (j = strlen(popped) - 1; j >= 0; j--) {
                if (isdigit(popped[j]) || popped[j] == '+' ||
                    popped[j] == '-' || popped[j] == '*' || popped[j] == '/') {
                  evalString[x] = popped[j]; // pop 16-> 1,6
                  x--;
                }
              }
            }
            pop(pHead, popped); // pop left par
            // displayList(*pHead);
          }
          // displayList(*pHead);
          // printf("EvalString:%s\n", evalString);
          int p;
          int foundOp = 0;
          int foundDigit = -1;
          for (p = 0; p < 7; p++) {
            if (evalString[p] == '+' || evalString[p] == '-' ||
                evalString[p] == '*' || evalString[p] == '/') {
              foundOp = 1;
              break;
            }
            if (isdigit(evalString[p])) {
              if (foundDigit == -1) {
                foundDigit = p;
              }
            }
          }
          if (foundOp == 1) {
            eval = evaluate5(evalString);
          } else {
            eval = evaluate6(evalString, foundDigit);
          }

          // printf("Eval1: %d\n", eval);
          if (eval == -1000) {
            *worked = 1;
            // printf("Error\n");
            return;
          } else {
            int x = 0;
            char str[5];
            // fflush(stdin);
            // printf("Test\n");
            sprintf(str, "%d", eval);
            appendNode(pHead, str);
      
            leftPar--;
          }
        } else {
          // error, closing par before opening
        }
      }
    }
  }
  // displayList(*pHead);

  if ((*pHead)->pNext == NULL) {
    // done
    // printf("done calculating\n");
  } else {
    // printf("last calculation, no par\n");
    int p;
    int ev = 0;
    if ((*pHead)->pNext->pNext->pNext != NULL) {
      ev = 0;
    } else {
      ev = 3;
    }
    for (p = 0; p < 7; p++) {
      evalString[p] = ' ';
    }
    int x = 6;
    int j = 0;
    char popped[10];

    pop(pHead, popped);
    // printf("Popped:%s\n", popped);
    // displayList(*pHead);
    while (popped[0] != '(' && popped[0] != '#') {
      // printf("Popped:%s\n", popped);
      if (popped[0] != '(' && popped[0] != ')') {
        for (j = strlen(popped) - 1; j >= 0; j--) {
          if (isdigit(popped[j]) || popped[j] == '+' || popped[j] == '-' ||
              popped[j] == '*' || popped[j] == '/') {
            evalString[x] = popped[j]; // pop 16-> 1,6
            x--;
          }
        }
      }
      pop(pHead, popped); // pop left par
      // displayList(*pHead);
    }
    int foundOp = 0;
    int foundDigit = -1;
    for (p = 0; p < 7; p++) {
      if (evalString[p] == '+' || evalString[p] == '-' ||
          evalString[p] == '*' || evalString[p] == '/') {
        foundOp = 1;
        break;
      }
      if (isdigit(evalString[p])) {
        if (foundDigit == -1) {
          foundDigit = p;
        }
      }
    }
    // displayList(*pHead);
    // printf("EvalString:%s\n",evalString);
    if (foundOp == 1) {
      if (ev == 0) {
        // 3 number calc
        eval = evaluate(evalString);
      } else {
        eval = evaluate3(evalString);
      }
    } else {
      eval = evaluate6(evalString, foundDigit);
    }

    // printf("Eval: %d\n", eval);
    if (eval == -1000) {
      *worked = 1;
      // printf("Error\n");
      return;
    } else {
      int x = 0;
      char str[5];
      // printf("Test1\n");
      sprintf(str, "%d", eval);
      // printf("Test3\n");

      // printf("EvalM: %d\n", eval);
      appendNode(pHead, str);
      // printf("Testing Eval:\n");
      // displayList(*pHead);
      leftPar--;
    }
  }
  // displayList(*pHead);
}

int main() {
  srand(1);
  displayGreeting();
  int isFirstTime = 1;
  int checkInputV = 0;
  int mode = 4;
  int continue1 = 0;
  int arraySize = 0;
  char **array1;
  array1 = malloc(1 * sizeof(char *));//alocate array for the file numbers
  while (continue1 == 0) {
    while (mode != 3) {

      int num1, num2, num3, num4;

      char input1 = 'E';
      if (mode > 1) {
        // generate numbers using a cleared array
        chooseDifficulty(input1);
        getchar();
        if (isFirstTime) {
          // don't clear array, already clear, generate numbers
          generateNumbers(input1, &num1, &num2, &num3, &num4, array1,
                          &arraySize);
          // once it gets out of function, array is empty
          //  printf("Displaying:%d:\n",arraySize);
          //  displayArray(array1, arraySize);
          isFirstTime = 0;
        } else {
          // clear the array, then generate numbers
          // clear
          array1 = malloc(1 * sizeof(char *));
          generateNumbers(input1, &num1, &num2, &num3, &num4, array1,
                          &arraySize);
        }
      } else {
        // generate numbers using same array, dont clear array

        array1 = malloc(1 * sizeof(char *));
        generateNumbers(input1, &num1, &num2, &num3, &num4, array1, &arraySize);
      }

      // 1

      printf("The numbers to use are: %d, %d, %d, %d.\n", num1, num2, num3,
             num4);

      printf("Enter your solution: ");
      char input2[40];
      fgets(input2, 40, stdin);
      // scanf for solution input
      checkInput(input2, num1, num2, num3, num4, &checkInputV);
      // returns 1 for failed, 0 for works
      if (checkInputV == 1) {
        mode = 1;
        break;
      }
      // Now to enter into stack(linked list)
      NodePtr pHead = NULL;
      int listSize = 0;
      int worked = 0;
      // printf("Test\n");
      calculate(input2, &pHead, &listSize, &worked);
      // printf("Test1\n");
      char res[10];
      pop(&pHead, res);//should pop the remaining number which is the final result
      // displayList(pHead);
      
      // printf("res:%s\n",res);
      if (strcmp(res, "24") == 0) {
        printf("Well done! You are a math genius.\n\n");
      } else {
        printf("Sorry. Your solution did not evaluate to 24.\n\n");
      }
      printf("Enter: \t1 to play again,\n");
      printf("\t2 to change the difficulty level and then play again, or\n");
      printf("\t3 to exit the program.\n");

      mode = 4;
      int choice = 0;
      while (mode != 1 && mode != 2 && mode != 3) {//loop for the user's choice
        printf("Your choice --> ");
        scanf("%d", &mode);
        getchar();
      }
      if (mode == 3) {
        continue1 = 1;
        break;
      }
      // mode = choice;
    }

    // end of continue1 while loop
  }

  displayEnding();
  return 0;
}
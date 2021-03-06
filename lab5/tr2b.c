#include<stdio.h>
#include<stdlib.h>


void checkLengths(char* from, char* to)
{
  int length=0;
  while(from[length] != '\0' && to[length] != '\0')
  {
    length++;
  }

  if(from[length] != to[length])
  {
    fprintf(stderr, "Error, the arguments are not of the same length");
    exit(1);
  }
}

void checkArg(int argc)
{
  if(argc!=3)
  {
    fprintf(stderr, "Error, incorrect number of arguments\n");
    exit(1);
  }
}

void checkRepeat(char* from)
{
  int current, next;
  for (current = 0; from[current] != '\0'; current=current+1)
  {
    for (next = current+1; from[next] != '\0'; next=next+1)
    {
      if (from[current] == from[next]) 
      {
        fprintf(stderr,"Error, repeating characters in first operand\n");
        exit(1);
      }
    }
  }
}

void checkIn()
{
  if(ferror(stdin))
  {
    fprintf(stderr, "Error in input\n");
    exit(1);
  }
}

void checkOut()
{
  if(ferror(stdout))
  {
    fprintf(stderr, "Error in output\n");
    exit(1);
  }
}

int main (int argc, char* argv[])
{
  checkArg(argc);
  char * from = argv[1];
  char* to = argv[2];
  checkLengths(from, to);
  checkRepeat(from);

  char current = getchar();
  checkIn();

  while(current != EOF)
  {
      for(int i = 0; from[i] != '\0' ; i++)
      {
        if(current == from[i])
        {
          current = to[i];
          break;
        }
      }
      putchar(current);
      checkOut();
      current = getchar();
      checkIn();
  }

}
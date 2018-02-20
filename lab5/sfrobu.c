#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<limits.h>
#include<ctype.h>
#include<string.h>

int flag = 0;
int comparisons =0;

int frobcmp(char const *a, char const *b)
{
  comparisons++;
  while(1) 
  {
    if (flag)
    {
        if((*a^42) <= UCHAR_MAX && (*b^42) <= UCHAR_MAX && (*a^42) > 0 && (*b^42) > 0) 
        {
          if(*a == ' ' && *b == ' ') 
            { return 0; }
          else if(*a == ' ' || (toupper(*a^42) < toupper(*b^42))) 
            { return -1; }
          else if(*b == ' ' || (toupper(*a^42) > toupper(*b^42))) 
            { return 1; }
        } 
        else if((*a^42) <= UCHAR_MAX && (*a^42) > 0 && ((*b^42) > UCHAR_MAX || (*b^42) < 0)) 
        {
          if(*a == ' ' && *b == ' ') 
            { return 0; }
          else if(*a == ' ' || (toupper(*a^42) < (*b^42))) 
            { return -1; }
          else if(*b == ' ' || (toupper(*a^42) > (*b^42))) 
            { return 1; }
        }  
        else if(((*a^42) > UCHAR_MAX || (*a^42) < 0) && (*b^42) <= UCHAR_MAX && (*b^42) > 0) 
        {
          if(*a == ' ' && *b == ' ') 
            { return 0; }
          else if(*a == ' ' || ((*a^42) < toupper(*b^42))) 
            { return -1; }
          else if(*b == ' ' || ((*a^42) > toupper(*b^42))) 
            { return 1; }
        }
        else 
        {
          if(*a == ' ' && *b == ' ') 
            { return 0; }
          else if (*a == ' ') 
            { return -1; }
          else if ((*a^42) < (*b^42))
            { return -1; }
          else if (*b == ' ') 
            { return 1; }
          else if ((*a^42) > (*b^42))
            { return 1; }
        }
    }
    else 
    {
      if(*a == ' ' && *b == ' ') 
          { return 0; }
      else if (*a == ' ') 
          { return -1; }
      else if ((*a^42) < (*b^42))
          { return -1; }
      else if (*b == ' ') 
          { return 1; }
      else if ((*a^42) > (*b^42))
          { return 1; }
    }
    a++;
    b++;
  }
}
int cmp(const void* a, const void* b)
{
  const char* temp1 = *(const char**)a;
  const char* temp2 = *(const char**)b;
  return frobcmp(temp1,temp2);
}

void checkError()
{
  if(ferror(stdin))
  {
    fprintf(stderr, "Error reading in value");
    exit(1);
  }
}

int main (int argc, char* argv[])
{
  if(argc == 2 && strcmp(argv[1], "-f") == 0) 
  {
      flag= 1;
  }
  struct stat fileDescriptor;
  if(fstat(0,&fileDescriptor) < 0) 
  {
    fprintf(stderr, "Error while reading in the file");
  }

  char **words; 
  char *allText;
  
  int letter_count=0, word_count=0;

  if(S_ISREG(fileDescriptor.st_mode))
  {
    allText = (char *)(malloc(fileDescriptor.st_size * sizeof(char)));
    int numPointers = 0;
    int skip =1;
    if(read(0, allText, fileDescriptor.st_size)==-1)
    {
      fprintf(stderr, "Error reading in value");
      exit(1);
    }
    else
    {
      for(int i = 0; i < fileDescriptor.st_size; i+=skip)
      {
        skip = 1;
        if(allText[i] == ' ')
        {
          for(int j = i; allText[i] != ' '; j++)
          {
            skip++;
          }
          numPointers++;
        }
        if(i == fileDescriptor.st_size - 1) 
        {
            allText[i] = ' ';
        }
      }
    }
    words = (char**)malloc(numPointers * sizeof(char*));
    int endword = 0;
    for(int i = 0; i < fileDescriptor.st_size; i++)
    {
      if(endword == 0 && allText[i] != ' ')
      {
        words[word_count] = &allText[i];
        endword=1;
        word_count++;
      }
      else if (endword == 1 && allText[i] == ' ')
      {
        endword = 0;
      }
    }
  }
  else
  {
    words = (char**)malloc(sizeof(char*));
  }
  char* newWord = (char*)(malloc(sizeof(char)));
  char *currentChar;
  int current = read(0, currentChar, 1);
  char *nextChar;
  int next = read(0, nextChar, 1);
  if(current < 0|| next < 0)
  {
    fprintf(stderr, "Error reading in value");
    exit(1);
  }

  while(current > 0)
    {
      newWord[letter_count] = *currentChar;
      char * temp1 = (char *)(realloc(newWord, (letter_count+2)*(sizeof(char))));
      letter_count++;
      if(temp1 != NULL)
      {
        newWord = temp1;
      }
      else
      {
        free(newWord);
        fprintf(stderr, "Error Allocation Memory");
        exit(1);
      }
      if(*nextChar == ' ')
      {
        
        newWord[letter_count] = ' ';
        
        words[word_count] = newWord;

        char ** temp2 = realloc(words,(word_count+2)*(sizeof(char**)));
        if(temp2 != NULL)
        {
          words = temp2;
        }
        else
        {
          free(words);
          fprintf(stderr, "Error Allocation Memory");
          exit(1);
        }
        word_count++;
        letter_count = 0;
        newWord =  (char *)(malloc(sizeof(char)));
        *currentChar = *nextChar;
        next = read(0, nextChar, 1);
        if(next < 0)
        {
          fprintf(stderr, "Error Allocation Memory");
          exit(1);
        }
      }
      if(next == 0)
      {
        if(*currentChar != ' ')
        {
          newWord[letter_count] = ' ';
          words[word_count] = newWord;
          char ** temp2 = realloc(words,(word_count+2)*(sizeof(char**)));
          if(temp2 != NULL)
          {
            words = temp2;
          }
          else
          {
            free(words);
            fprintf(stderr, "Error Allocation Memory");
            exit(1);
          }
          word_count++;
          letter_count = 0;
        }
        break;
      }
      if(*currentChar == ' ' && *nextChar == ' ')
      {
        while(*currentChar == ' ')
        {
          current = read(0,currentChar,1);
          if(current < 0)
          {
            fprintf(stderr, "Error Allocation Memory");
            exit(1);
          }
        }
        next = read(0,nextChar,1);
        if(next < 0)
        {
            fprintf(stderr, "Error Allocation Memory");
            exit(1);
        }
      }
      *currentChar = *nextChar;
      next = read(0,nextChar,1);
      checkError();
    }

    qsort(words,word_count,sizeof(char*),cmp);

    for(size_t i = 0; i < word_count ; i++)
    {
      for(size_t j = 0; ;j++)
      {
        if(write(1, &words[i][j], 1) == -1)
        {
          fprintf(stderr, "Error on writing to output");
          exit(1);  
        }
        if(words[i][j] == ' ')
          { break; }
      }
    }

   
    free(words);
    free(newWord);
    printf("%d\n", comparisons);
    exit(0);
}

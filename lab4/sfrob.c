#include<stdlib.h>
#include<stdio.h>
int frobcmp(const char * a, const char *b)
{
  for(;;a++, b++)
  {
    if(*a == ' ' && *b == ' ')
    {
      return 0;
    }
    else if(*a == ' ' || ((*a^42) < (*b^42)))
    {
      return -1;
    }
    else if(*b == ' ' || ((*a^42) >(*b^42))) 
    {
      return 1;
    }
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

int main(void)
{
  char *word; 
  char **dict;
  word = (char *)(malloc(sizeof(char)));
  dict = (char **)(malloc(sizeof(char*)));
  
  int letter_count=0, word_count=0;

  char current;
  current = getchar();
  checkError();
  char next;
  next = getchar();
  checkError();

  while(current !=  EOF)
    {
      word[letter_count] = current;
      char * temp1 = (char *)(realloc(word, (letter_count+2)*(sizeof(char))));
      letter_count++;
      if(temp1 != NULL)
      {
        word = temp1;
      }
      else
      {
        free(word);
        fprintf(stderr, "Error Allocation Memory");
        exit(1);
      }
      if(next == ' ')
      {
        
        word[letter_count] = ' ';
        
        dict[word_count] = word;

        char ** temp2 = realloc(dict,(word_count+2)*(sizeof(char**)));
        if(temp2 != NULL)
        {
          dict = temp2;
        }
        else
        {
          free(dict);
          fprintf(stderr, "Error Allocation Memory");
          exit(1);
        }
        word_count++;
        letter_count = 0;
        word =  (char *)(malloc(sizeof(char)));
        current = next;
        next = getchar();
      }
      if(next == EOF)
      {
        if(current != ' ')
        {
          word[letter_count] = ' ';
          dict[word_count] = word;
          char ** temp2 = realloc(dict,(word_count+2)*(sizeof(char**)));
          if(temp2 != NULL)
          {
            dict = temp2;
          }
          else
          {
            free(dict);
            fprintf(stderr, "Error Allocation Memory");
            exit(1);
          }
          word_count++;
          letter_count = 0;
        }
        break;
      }
      if(current == ' ' && next == ' ')
      {
        while(current == ' ')
        {
          current =getchar();
          checkError();
        }
        next = getchar();
        checkError();

      }
      current = next;
      next = getchar();
      checkError();
    }

    qsort(dict,word_count,sizeof(char*),cmp);

    for(size_t i = 0; i < word_count ; i++)
    {
      for(size_t j = 0; ;j++)
      {
        putchar(dict[i][j]);
        if(dict[i][j] == ' ')
        {
          break;
        }
      }
    }

    for(size_t i=0; i<word_count ; i++)
    {
      free(dict[i]);
    }
    free(dict);

    exit(0);
}

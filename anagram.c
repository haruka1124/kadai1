#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 26        //English alphabet: 26 letters
#define LENGTH 30   //Maximum length of 235886 words
#define SIZE 235886 //Total number of words

char *words[SIZE];
int freq[N],freq_wrd[N];

int comp1(const void *c1, const void *c2);
int comp2(char *wrd);
void read_file(char *filename);


/* to compare the length of two strings */
int comp1(const void *c1, const void *c2){
  return (strlen(*(char **)c2) - strlen(*(char **)c1));
}

/* whether argument is a word that has been rearranged some letters of input string */
int comp2(char *wrd){
  int j,length=strlen(wrd);
  for(j=0;j<N;j++) freq_wrd[j] = 0; // Initialize an array
  for(j=0;j<length;j++){
    char c = tolower(wrd[j]);
    if(122 <c || c<97) continue;    // Hyphen is ignored
    freq_wrd[c - 97]++;
    if( freq[c-97] < freq_wrd[c -97] ) return 0;
  }
  return 1;
}

/* to read the file and store the data in an array words */
void read_file(char *filename){
  FILE *file;
  char a[LENGTH];
  int j=0;
  
  if((file = fopen (filename, "r")) == NULL) { 
    printf ("Failure to open file : %s\n",filename);
    exit (1);
  }
  while (fgets(a,LENGTH-1,file)!=NULL){
    words[j] = (char *) malloc (LENGTH);
    a[strlen(a) - 1] = '\0';
    strcpy(words[j],a);
    j++;
  }
  fclose(file);
}

int main(int argc,char *argv[]){  
  int length,i;	
  char *target, *word;

  /* Argument count has to be two */
  if(argc !=2){ 
    printf ("Usage: ./anagram <Alphabetic string> \n");
    exit (1);
  }

  /* Initialize an arrey freq */
  for(i=0;i<N;i++) freq[i] = 0;
  length = strlen(argv[1]);

  /* Count frequencies of each of the alphabet */
  for(i=0;i<length;i++){ 
    char c = tolower (argv[1][i]); 
    if(122<c || c<97) continue;      // non-alphabet is ignored
    freq[c-97]++;
  }
 
  /* store the data of file in an arrary words */
  read_file("words");
  /* sort the array words by length */
  qsort(words, SIZE, sizeof(char *),comp1);

  /* find the array subscript of the answer */
  i=0;
  while(!(comp2(words[i]))) i++;

  printf("%s\n",words[i]);
  return 0;
}

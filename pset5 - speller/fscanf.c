#include <stdio.h>
#include <stdlib.h>


int main()
{
   //char str1[10], str2[10], str3[10];
   //int year;
   FILE * fp;

   char word[45];

   fp = fopen ("file.txt", "w+");
   fputs("We are in 2017, and that´s great!", fp);

   // cursor back to start of file
   rewind(fp);

   while( fscanf(fp, "%s", word) != EOF )
   {
      printf("word is: %s \n", word);
   }

   printf("\n");

   // cursor back to start of file
   rewind(fp);

   for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
   {
      printf("%c", c);
   }

   printf("\n");

   fclose(fp);

   return(0);
}
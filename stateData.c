/** 
 * This program processes a CSV file containing data on US
 * States and produces an XML-formatted file with the same data.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * This function takes an array of states (names as strings) and
 * an array of each one's population and outputs them to an XML-formatted
 * file.
 */
void toXMLFile(char **states, int *populations, int numStates);

/**
 * This function trims trailing whitespace from the given string.
 */
void rtrim(char *str);

int main(int argc, char **argv) {
  int const size = 200;
  int const numStates = 50;
  char filePath[] = "data/stateData.txt";
  char tempBuffer[size];
  char tmp[size];

  // setup arrays
  int i;
  char **states = (char **)malloc(sizeof(char *) * numStates);
  int *statePopulations = (int *)malloc(sizeof(int) * numStates);
  for (i = 0; i < numStates; i++) {
    states[i] = (char *)malloc(sizeof(char) * size);
  }

  // open the file, quit if it fails...
  FILE *instream = fopen(filePath, "r");
  if (instream == NULL) {
    fprintf(stderr, "Unable to open file: %s\n", filePath);
    exit(1);
  }

  // read the file, line by line
  i = 0;
  while (fgets(tempBuffer, size, instream) != NULL) {
    // remove the endline character from the line
    tempBuffer[strlen(tempBuffer) - 1] = '\0';
    // tokenize the line, breaking along commas:
    char *stateToken = strtok(tempBuffer, ",");
    strcpy(states[i], stateToken);
    char *popToken = strtok(NULL, ",");
    statePopulations[i] = atoi(popToken);
    i++;
  }
  fclose(instream);

  // output to the standard output
  int total = 0;
  for (i = 0; i < numStates; i++) {
    printf("%15s %10d\n", states[i], statePopulations[i]);
    total += statePopulations[i];
  }
  printf("%-15s  %10d\n", "TOTAL", total);

  // output to a binary datafile
  FILE *outstream = fopen("data/stateData.dat", "w");
  for (i = 0; i < numStates; i++) {
    // limit the state name to 15 characters
    fwrite(states[i], sizeof(char), 15, outstream);
    // output a single int type
    fwrite(&statePopulations, sizeof(int), 1, outstream);
  }
  fclose(outstream);

  toXMLFile(states, statePopulations, 50);

  return 0;
}

void toXMLFile(char **states, int *populations, int numStates) {
  // TODO: you need to implement this
}

void rtrim(char *str) {
  int n = strlen(str);
  while (n >= 0 && isspace(str[n - 1])) {
    str[n - 1] = '\0';
    n--;
  }
  return;
}

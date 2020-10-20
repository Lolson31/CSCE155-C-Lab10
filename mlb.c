/**
 * This program processes a CSV file of data on major league
 * baseball teams, sorts them according to win percentage and
 * prints them to the standard output.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * A sorting function to sort the teams and their win percentages
 * using the selection sort algorithm which successively finds the
 * "maximum" element and places it at the front of the array
 */
void sortMLB(char **teams, double *winPerc, int numTeams);

/**
 * This function prints the given teams with win percentages
 * to the standard output.
 */
void printMLB(char **teams, double *winPerc, int numTeams);

int main(int argc, char **argv) {
  int const maxSize = 50;
  int const numTeams = 16;
  char filePath[] = "data/mlb_nl_2011.txt";
  char tempBuffer[100];

  int i;
  char **teams = (char **)malloc(sizeof(char *) * numTeams);
  double *winPercentages = (double *)malloc(sizeof(double) * numTeams);
  for (i = 0; i < numTeams; i++) {
    teams[i] = (char *)malloc(sizeof(char) * maxSize);
  }

  // TODO: open the file, read it line by line, tokenize it to get the
  //      team name, wins, and losses, and store the results into
  //      teams[] and winPercentagesp[]
  FILE* read = fopen (filePath, "r");
  for (i = 0; i < numTeams * 3; i++)
  {
    char *team = strtok(line, " ");
    char *win = strtok(NULL, " ");
    char *loss = strtok(NULL, "\n");
    printf("%s\n", team);
    printf("%s\n", win);
    printf("%s\n", loss);
  }

  // sort them
  sortMLB(teams, winPercentages, numTeams);
  // print them out
  printMLB(teams, winPercentages, numTeams);

  return 0;
}

void sortMLB(char **teams, double *winPerc, int numTeams) {
  int i, j, max_index;
  char tmp_str[100];
  double tmp_dbl;
  // for each element i
  for (i = 0; i < numTeams - 1; i++) {
    max_index = i;
    // find the maximum element among elements i+1 thru n-2
    for (j = i + 1; j < numTeams; j++) {
      if (winPerc[max_index] < winPerc[j]) {
        max_index = j;
      }
    }
    // swap the ith element and the maximum element
    // in this case, elements from both arrays need to be swapped
    // at the same time; forgo swapping if it is in-place
    if(i != max_index) {
      tmp_dbl = winPerc[i];
      winPerc[i] = winPerc[max_index];
      winPerc[max_index] = tmp_dbl;
      strcpy(tmp_str, teams[i]);
      strcpy(teams[i], teams[max_index]);
      strcpy(teams[max_index], tmp_str);
    }
  }
}

void printMLB(char **teams, double *winPerc, int numTeams) {
  int i = 0;
  printf("%-12s %-10s\n", "TEAM", "WIN PERC");
  for (i = 0; i < numTeams; i++) {
    printf("%-12s %.3f%%\n", teams[i], winPerc[i] * 100.0);
  }
}

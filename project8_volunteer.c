/*
The program manages and tracks high school students who have expressed
interest in volunteering as assistants in the summer camps for K-8
students. Each volunteer is stored with last name, first name, email, and
grade level. The program allows the user to add, search, print, and clear volunteers.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMAIL_LEN 100
#define NAME_LEN 30

struct volunteer {
  char first[NAME_LEN + 1];
  char last[NAME_LEN + 1];
  char email[EMAIL_LEN + 1];
  int grade_level;
  struct volunteer *next;
};

struct volunteer *add_to_list(struct volunteer *list);
void search_list(struct volunteer *list);
void print_list(struct volunteer *list);
void clear_list(struct volunteer *list);
int read_line(char str[], int n);

int main(void) {
  char code;

  struct volunteer *volunteer_list = NULL;
  printf("Operation Code: a for adding to the list, s for searching"
        ", p for printing the list; q for quit.\n");
  for (;;) {
    printf("Enter operation code: ");
    scanf(" %c", &code);
    while (getchar() != '\n') /* skips to end of line */
      ;
    switch (code) {
    case 'a':
      volunteer_list = add_to_list(volunteer_list);
      break;
    case 's':
      search_list(volunteer_list);
      break;
    case 'p':
      print_list(volunteer_list);
      break;
    case 'q':
      clear_list(volunteer_list);
      return 0;
    default:
      printf("Illegal code\n");
    }
    printf("\n");
  }
}

struct volunteer *add_to_list(struct volunteer *list) {
  // add your code
  struct volunteer *current;

  // saving new volunteer to the memory
  struct volunteer *new_vol = malloc(sizeof(struct volunteer));

  // new volunteer info
  printf("Enter last name: "); // last name is input and read after
  read_line(new_vol->last, NAME_LEN);
  printf("Enter first name: "); // first name is input and read after
  read_line(new_vol->first, NAME_LEN);
  printf("Enter email address: "); // email address is input and read after
  read_line(new_vol->email, EMAIL_LEN);
  printf("Enter grade level: "); // grade is input and read after
  scanf("%d", &(new_vol->grade_level));

  // goes through every node in the linked list
  for (current = list; current != NULL; current = current->next) {
    // if every trait of new volunteer = trait of existing volunteer print that it already exists
    if (strcmp(current->last, new_vol->last) == 0 && strcmp(current->first, new_vol->first) == 0 && strcmp(current->email, new_vol->email) == 0 && (current->grade_level == new_vol->grade_level)) {
      printf("volunteer already exists.\n");
      free(new_vol);
      return list;
    }
  }

  new_vol->next = NULL;

  // if list is empty, new volunteer is the first node
  if (list == NULL) {
    return new_vol;
  // if list is not empty, new volunteer is added to the end of the list
  } else {
    current = list;
    // find the end of the list
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_vol; // add the new node to the end
    return list;
  }
}

void search_list(struct volunteer *list) {
  int search;
  printf("Enter grade level: ");
  scanf("%d", &search);

  struct volunteer *current = list;
  int found = 0; // flag variable starting at not found

  // goes through every node in the linked list
  while (current != NULL) {
    // if grade level of current node = search grade level, print out info
    if (current->grade_level == search) {
      printf("%-12s%-12s%-30s\n", current->last, current->first, current->email);
      found = 1; // flag variable changed to found
    }
    current = current->next; // move the current value to the next node
  }
  // if grade level of current node != search grade level, print not found
  if (!found)
    printf("not found\n");
}

void print_list(struct volunteer *list) {
  struct volunteer *current = list;
  // goes through every node in the linked list and prints them
  while (current != NULL) {
    printf("%-12s%-12s%-30s%5d\n", current->last, current->first, current->email, current->grade_level);
    current = current->next; // move to next node
  }
}

void clear_list(struct volunteer *list) {
  struct volunteer *current;
  // while the list is not empty, free the memory of the first node
  while (list != NULL) {
    current = list;
    list = list->next; // move the beginning of the list to the next node
    free(current); // free the memory of the current node
  }
}

int read_line(char str[], int n) {
  int ch, i = 0;

  while (isspace(ch = getchar()))
    ;
  str[i++] = ch;
  while ((ch = getchar()) != '\n') {
    if (i < n)
      str[i++] = ch;
  }
  str[i] = '\0';
  return i;
}

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack *stack_create(int capacity, char name) {
  // Stack
  Stack *new_stack;
  new_stack = (Stack *)malloc(sizeof(Stack));
  if (new_stack == NULL) { // Check malloc
    printf("Error\n");
    return 0;
  } else {
    // Items in the stack
    int *my_array;
    my_array = (int *)malloc(capacity * sizeof(Stack));
    // Assigning properties to new_stack
    new_stack->name = name;
    new_stack->top = 0;
    new_stack->capacity = capacity;
    new_stack->items = my_array;
    return new_stack;
  }
}

void stack_delete(Stack *s) {
  free(s->items);
  free(s);
  return;
}

int stack_pop(Stack *s) {
  if (s == NULL) {
    return -1;
  }
  if (s->top > 0) {
    int num = s->items[s->top];
    s->top -= 1;
    return num; // Maybe wrong, why would you return the new position of top>
  } else {
    return -1;
  }
}

void stack_push(Stack *s, int item) {
  if (s == NULL) {
    return;
  }
  if (s->items) {
    s->top++;
    s->items[s->top] = item;
  }
  return;
}

bool stack_empty(Stack *s) {
  return s->top == 0;
}

int stack_peek(Stack *s) {
  if (s == NULL) {
    return 0;
  }
  return s->items[s->top];
}

#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int seen[10];

  for(int i = 0 ; i < 9 ; i++){
    for(int k = 0 ; k < 9 ; k++) seen[k] = 0;
    for(int j = 0 ; j < 9 ; j++){
      int valor = n->sudo[i][j];
      if(valor == 0) continue;
      if(seen[valor] == 1) return 0;
      seen[valor] = 1;
      }
      
    }

    for(int i = 0 ; i < 9 ; i++){
      for (int k = 0 ; k < 9 ; k++) seen[k] = 0;
      for (int j = 0 ; j < 9 ; j++){
        int valor = n->sudo[i][j];
        if(valor == 0) continue;
        if(seen[valor] == 1) return 0;
        seen[valor] = 1;
      }
    }
    for(int k = 0 ; k < 9 ; k++){
      for(int i = 1 ; i <= 9 ; i++) seen[i] = 0;
      for (int p = 0 ; p < 9 ; p++){
        int x = 3 * (k/3) + (p/3);
        int y = 3 * (k%3) + (p%3);
        int valor = n->sudo[x][y];
        if(valor == 0) continue;
        if(seen[valor]) return 0;
        seen[valor] = 1;
      }
    }
    return 1;
  }


List* get_adj_nodes(Node* n){
    List* list=createList();
    int found = 0;

    for (int i = 0 ; i < 9 && !found ; i++){
      for(int j = 0 ; j < 9 && !found ; j++){
        if(n->sudo[i][j] == 0){
          found = 1;
          i--;
          j--;
        }
      }
    }
    return list;
}


int is_final(Node* n){
  for(int i = 0 ; i < 9 ; i++){
    for(int j = 0 ; j < 9 ; j++){
      if(n->sudo[i][j] == 0) return 0;
    }
  }
  return 1;
}
Node* DFS(Node* initial, int* cont){
  List* stack = createStack();
  pushBack(stack, initial);

  while (first(stack)) {
    Node* current = first(stack);
    popFront(stack);
    (*cont)++;

    if (is_final(current)) {
      return current;
    }
    if(is_valid(current)){
      List* adj = get_adj_nodes(current);
      Node* adjNode = first(adj);

      while(adjNode){
        pushFront(stack, adjNode);
        adjNode = next(adj);
      }
    }
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/
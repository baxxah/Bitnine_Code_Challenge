#include <stdio.h>
#include <stdlib.h>

long long nodeIps[50] = {};
int intIpIdx = 0;

typedef enum TypeTag {
  ADD, SUB, MUL, FIB, INT
} TypeTag;

typedef struct Node {
  TypeTag type;
  int value;
  struct Node *left;
  struct Node *right;
} Node;

// defenition of makeFunc
typedef Node* (*FuncPtr)(void*, void*);

Node* makeNode(TypeTag type) {
  Node* node = (Node*)malloc(sizeof(Node));
  
  // store it in nodeIps
  nodeIps[intIpIdx] = (int)node;
  intIpIdx++;

  node->type = type;
  node->left = NULL;
  node->right = NULL;
  // return node;
}

Node* makeIntNode(int value) {
  Node *node = makeNode(INT);
  node->value = value;
  // return node;
}


int isNode(void* arg) {
  int found = 0;
  int i = 0;
  while(nodeIps[i] != 0) {    
    if(((int*)(arg)) == nodeIps[i]) {
      found = 1;
      break;
    }
    i++;
  }
  return found;
}



Node* operation(void* arg1, void* arg2, TypeTag type) {
  
  Node* node = makeNode(type);
  
  if(isNode(arg1)) {
    node->left = arg1;
  } else{
    node->left = makeIntNode(arg1);
  }

  if(isNode(arg2)) {
    node->right = arg2;
  } else {
    node->right = makeIntNode(arg2);
  }


  return node;
}


Node* add(void* arg1, void* arg2) {
  return operation(arg1, arg2, ADD);
}

Node* mul(void* arg1, void* arg2) {
  return operation(arg1, arg2, MUL);
}

Node* sub(void* arg1, void* arg2) {
  return operation(arg1, arg2, SUB);
}

Node* fib(void* arg1, void* arg2) {
  return operation(arg1, arg2, FIB);
}



Node* (*makeFunc(TypeTag type))(void*, void*) {
  switch(type) {
    case ADD:
      return &add;
      break;
    case SUB:
      return &sub;
      break;
    case MUL:
      return &mul;
      break;      
    case FIB:
      return &fib;
      break;
    default:
      printf("Unknown TypeTag\n");     
  }
}

int fibonacci(int n) {
  int fib[n+1];
  fib[0] = 0;
  fib[1] = 1;
  for(int i = 2; i <= n; i++) {
      fib[i] = fib[i-1] + fib[i-2];
  }
  return fib[n];
}





int calc(Node* node) {
  int result;
  if (node->type == ADD) {
      result = calc(node->left) + calc(node->right);
  } else if (node->type == SUB) {
      result = calc(node->left) - calc(node->right);
  } else if (node->type == MUL) {
      result = calc(node->left) * calc(node->right);
  } else if (node->type == FIB) {
      int n = calc(node->left);
      result = fibonacci(abs(n));
  } else if (node->type == INT) {
      result = node->value;
  } else {
    printf("Unknown node type %d\n", node->type);
  }
 
  return result;
}





int main() {
  Node *add = (*makeFunc(ADD))(10, 6);
  Node *mul = (*makeFunc(MUL))(5, 4); 
  Node *sub = (*makeFunc(SUB))(add, mul);  
  Node *fibo = (*makeFunc(FIB))(sub, NULL);

  printf("%d\n", calc(add));
  printf("%d\n", calc(mul));
  printf("%d\n", calc(sub));
  printf("%d\n", calc(fibo));
}

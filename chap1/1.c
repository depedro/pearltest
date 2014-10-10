#include<stdio.h>
#include<stdlib.h>
#include<string.h>

inline void swap(int *array, int i, int k) {
  int tmp = array[i];
  array[i] = array[k];
  array[k] = tmp;
}

/* quick sort */
inline int pivot_selection(int *array, int i, int k) {
  int j = (i + k)/2; 
  if(array[i] > array[k] && array[k] > array[j])
    return k;
  else if(array[i] > array[j] && array[j] > array[k])
    return j;
  else 
    return i;
}

int partition(int *array, int left, int right) {
  int p = pivot_selection(array, left, right);
  int pval = array[p];
  int store_index = left;
  int i;

  swap(array, p, right);
  for(i = left; i < right; i++) 
    if(array[i] < pval) 
      swap(array, i, store_index++);
  swap(array, store_index, right);
  return store_index;
}

void quick_sort(int *array, int left, int right) {
  int p;
  if(left < right) {
    p = partition(array, left, right);
    quick_sort(array, left, p - 1);
    quick_sort(array, p + 1, right);
  }
}

/* bubble sort */
void bubble_sort(int *array, int left, int right) {
  int swapped = 1;
  while(swapped) {
    int i = left;
    swapped = 0;
    for(i = left; i < right; i++)
      if(array[i] > array[i+1]) {
	swap(array, i, i+1);
	swapped = 1;
      }
  }
} 

/* insert sort */
typedef struct slist_node {
  int val;
  struct slist_node *next;
} * slist_t;

void insert_val(slist_t *lst, int val) {
  slist_t prev = NULL;
  slist_t cur = *lst;
  slist_t new = (slist_t) malloc(sizeof(struct slist_node));
  new->val = val;

  while(cur != NULL && cur->val < val) {
    prev = cur;
    cur = cur->next;
  }

  if(cur == NULL) {
    new->next = NULL;
    if(prev == NULL)    // new list
      *lst = new;
    else                // add to tail
      prev->next = new; 
  } else {
    if(prev == NULL)    // add to head
      *lst = new; 
    else                // add to middle
      prev->next = new;
    new->next = cur;
  }
}

void free_list(slist_t lst) {
  slist_t prev = NULL;
  while(lst != NULL) {
    prev = lst;
    lst = lst->next;
    free(prev);
  }
}

void insert_sort(int * array, int left, int right) {
  slist_t lst = NULL;
  slist_t cur;
  int i;

  if(left < right) {
    for(i = left; i <= right; i++)
      insert_val(&lst, array[i]);
    cur = lst;
    for(i = left; i <= right; i++) {
      array[i] = cur->val;
      cur = cur->next;
    }
    free_list(lst);
  }
}

/* bottom up merge short */
void merge(int * from, int * to, int index, int size1, int size2) {
  int i = index;
  int j = index + size1;
  int store_index = index;
  while(i < index + size1 || j < index + size1 + size2) { 
    if(i >= index + size1)
      to[store_index++] = from[j++];
    else if(j >= index + size1 + size2)
      to[store_index++] = from[i++];
    else if(from[i] < from[j])
      to[store_index++] = from[i++];
    else
      to[store_index++] = from[j++];
  }
}

void merge_sort(int * array, int left, int right) {
  int size, run_size, i;
  int *tmp, *from, *to;

  size = right + 1 - left;
  if(size <= 1)
    return;
  
  from = &array[left];
  to = (int *) malloc(sizeof(int) * size);

  for(run_size = 1; run_size < size; run_size *= 2) {
    for(i = 0; i < size; i += run_size * 2) 
      if(size - i >= run_size * 2)
	merge(from, to, i, run_size, run_size);
      else if(size - i > run_size)
	merge(from, to, i, run_size, size - i - run_size);
      else {
	memcpy((void*) &to[i], (void*) &from[i], sizeof(int)*(size - i));
	
      }
    tmp = from;
    from = to;
    to = tmp;
  }

  if(to != &array[left])
    memcpy((void *) &array[left], (void *) to, sizeof(int)*size);
}


/* main */
#define ASIZE 13
int A[ASIZE];

int main() {
  time_t t;
  int i;

  srand((unsigned) time(&t));
  for(i = 0; i < ASIZE; i++) {
    A[i] = rand() % ASIZE;
    printf("%3d ", A[i]);
  }
  printf("\n sorted:\n");
  
  //quick_sort(A, 0, ASIZE - 1);
  //bubble_sort(A, 0, ASIZE - 1);
  //insert_sort(A, 0, ASIZE - 1);
  merge_sort(A, 0, ASIZE - 1);

  for(i = 0; i < ASIZE; i++) {
    printf("%3d ", A[i]);
  }  
  printf("\n");
}

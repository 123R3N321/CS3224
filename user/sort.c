//do we care about failed memory alloc?
//parse -r
//parse filepath


#include "user.h"
#define UNSET 0
#define INIT_BUF_SIZE 10

typedef struct {
  char* buff;
  int char_count;
  int capacity;
} Buffer;

// To implement in Step 2
Buffer alloc_buffer(int capacity);
void free_buffer(Buffer* buffer);
void resize_buffer(Buffer* buffer, int capacity);
void read_into_buffer(int fd, Buffer* buffer);
void print_buffer(Buffer* buffer);	//I added this prototype
void cheat_sort(Buffer* buffer, int reversed);	//added

// To implement in Step 3
void sort(Buffer* buffer, int reversed);

int main(int argc, char* argv[]) {
  int reversed = 0, fd = 0;
  // TODO: Step 1: Implement argument parsing to set fd and the reversed flag.
  if(argc>1){	//more than one param, either rev flag, or file passed in
  	if(!strcmp(argv[1], "-r")){	//this is to say, if they are equal, we not a 1
  					//assuming c behavior of literal treated as null-terminated arr of char
  		reversed=1;
  		if(3==argc){	//when we do have -f, and also file path
  			fd = open(argv[2],0);	//read only no modification
  		}
  	}else{	//no -f, but we have file path as argc>1
  		fd = open(argv[1],0);	//read only no modification
  	};
  }
  //implied: when argc<=1, reversed and fd both 0;

  Buffer buffer = alloc_buffer(INIT_BUF_SIZE);
  read_into_buffer(fd, &buffer);	//we ony deal with read into buffer
  if(fd){close(fd);}	//if we have a file passed in, close it.
  cheat_sort(&buffer, reversed);
  //print_buffer(&buffer);
  free_buffer(&buffer);
  exit();
}


Buffer alloc_buffer(int capacity) {
  // TODO: Step 2.1: Initialize Buffer with the correct values,
  // your solution should have NOTHING unset.
 
  return (Buffer) {
      .buff = (char *)malloc((capacity + 1) * sizeof(char)),
      .char_count = 0,
      .capacity = capacity,
  };
  

}

void free_buffer(Buffer* buffer) {	//ask about it. Seems too easy
  // TODO: Step 2.2: Implement basic Buffer helpers
  // This should free up the malloc'd memory used by the buffer.
  free(buffer->buff);
  buffer->char_count = 0;
  buffer->capacity = 0;	//means we only call this func when we ant to kill the buffer! No more capacity!
}

void resize_buffer(Buffer* buffer, int capacity) {	//pass in a doubled capacity as second arg
  // TODO: Step 2.3: Implement basic Buffer helpers
  // This should resize the allocated memory for the buffer to capacity.

  	buffer->buff = realloc(buffer->buff, capacity * sizeof(char));	//migration
  	buffer->capacity = capacity;	//update to new capacity	
}

void read_into_buffer(int fd, Buffer* buffer) {
  // TODO: Step 2.4: Implement basic Buffer helpers
  // This should read everything from fd into the buffer until it reaches EOF.
	int n;
	while((n = read(fd, &(buffer->buff[buffer->char_count]), sizeof(char))) > 0){	//read one char at a time
		buffer->char_count++;
		if(buffer->char_count == buffer->capacity){	//if full capacity, call resize
			resize_buffer(buffer, 2 * buffer->capacity);	//double it
		}
	}	

  // For debugging, you can uncomment this to check the content of the buffer.
  
  printf("buff: %p, capacity: %d, char_count: %d\ncontent:\n", buffer->buff, buffer->capacity, buffer->char_count);
  write(1, buffer->buff, buffer->char_count);
  printf("END OF CONTENT\n");
  //above is debug code !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void iterative_heapify(char* lst, int size) {	//heapify baased on algo notes
    int begin = size - 1;
    while (begin >= 0) {
        int branch_end = begin;
        while (branch_end != 0) {
            int prev = branch_end / 2;
            if (atoi(&lst[branch_end]) > atoi(&lst[prev])) {	//sort
                char temp = lst[branch_end];
                lst[branch_end] = lst[prev];
                lst[prev] = temp;
            }
            branch_end /= 2;
        }
        begin -= 1;
    }
}


void iterative_heapify_rev(char* lst, int size) {	//simply change min to max heap
    int begin = size - 1;
    while (begin >= 0) {
        int branch_end = begin;
        while (branch_end != 0) {
            int prev = branch_end / 2;
            if (atoi(&lst[branch_end]) < atoi(&lst[prev])) {	//rev sort
                int temp = lst[branch_end];
                lst[branch_end] = lst[prev];
                lst[prev] = temp;
            }
            branch_end /= 2;
        }
        begin -= 1;
    }
}


void iterative_extract(char* lst, int length, int reversed) {
    int begin = length - 1;	//redundant var, more but readable
    while (begin > 0) {	//try greater not gretaer equal.
	    if(reversed){
	    	iterative_heapify_rev(lst, begin + 1);
	    }else{
		iterative_heapify(lst, begin + 1);
	    }

        char temp = lst[begin];
        lst[begin] = lst[0];
        lst[0] = temp;
        begin -= 1;
    }
}


void int_rev_heapify(int* lst, int size) {
    int begin = size - 1;
    while (begin >= 0) {
        int branch_end = begin;
        while (branch_end != 0) {
            int prev = branch_end / 2;
            if (lst[branch_end] < lst[prev]) {	//rev sort
                int temp = lst[branch_end];
                lst[branch_end] = lst[prev];
                lst[prev] = temp;
            }
            branch_end /= 2;
        }
        begin -= 1;
    }
}


void int_heapify(int* lst, int size) {
    int begin = size - 1;
    while (begin >= 0) {
        int branch_end = begin;
        while (branch_end != 0) {
            int prev = branch_end / 2;
            if (lst[branch_end] > lst[prev]) {	//forward sort
                int temp = lst[branch_end];
                lst[branch_end] = lst[prev];
                lst[prev] = temp;
            }
            branch_end /= 2;
        }
        begin -= 1;
    }
}

void int_extract(int* lst, int length, int reversed) {
    int begin = length - 1;	//redundant var, more but readable
    while (begin >= 0) {
    	if(reversed){int_rev_heapify(lst, begin + 1);}
        else{int_heapify(lst, begin + 1);}
        int temp = lst[begin];
        lst[begin] = lst[0];
        lst[0] = temp;
        begin -= 1;
    }
}


// try a dumb bubble sort
void bubble_sort(int* arr, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

//I give up. Using an additional array of integers to sort and store result.
//essentially "short circuit" the buffer of char*
void cheat_sort(Buffer* buffer, int reversed){
	
  int* arr = malloc(buffer->capacity);

  int ind = 0; 
  char* cursor = buffer->buff; 
  arr[ind] = atoi(cursor);	//have to do this. essentially we are expecting a whitespace before each number. need to manually load the first one.
  int count = 1;	//keep track how many ints we have loaded
  
  for (int i = 0; i< buffer->char_count; i++) {
      if (*cursor == ' ') {	//strcmp failed. only use == operator. It is more readable anyways.
          cursor++;
          ind++; 
          arr[ind] = atoi(cursor);
          count++;
      }
      cursor++;	
  }
  int_extract(arr, count, reversed);	//sorting happens here

	
	for (int j = 0; j < count; j++) {
		printf("%d ", arr[j]);	//this is the laziest solution without styling need.
	}
	
}


void sort(Buffer* buffer, int reversed) {	//three possible options for sorting. Turns out runtime  matters
	cheat_sort(buffer, reversed);
	//bubble_sort(buffer->buff, buffer->char_count);	//slowest
	//iterative_extract(buffer->buff, buffer->char_count, reversed);	//fastest but not really working for char buffer
  // TODO: Step 3: Implement sort using the buffer
}

void print_buffer(Buffer* buffer){
	write(1, buffer->buff, sizeof(char)*buffer->char_count);	//write the entire thing but not all that capacity.
}




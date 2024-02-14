//do we care about failed memory alloc?
//parse -r
//parse filepath


//tentative plan: forget about file reading, we do std input first


#include <stdlib.h>
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


// To implement in Step 3
void sort(Buffer* buffer, int reversed);

int main(int argc, char* argv[]) {
	int fd=0;
	int reversed=0;

  Buffer buffer = alloc_buffer(INIT_BUF_SIZE);
 
  if(!fd){
  //no file, stdinput, need to take care of argv
		for (int i = 1; i<argc; i++){
			buffer.buff[buffer.char_count] = *argv[i-1];
			buffer.char_count++;
			if(buffer.capacity <= buffer.char_count){	//when bumper catches up to the capacity limit...
				resize_buffer(&buffer, 2 * buffer.capacity);	//double current capacity
			}
		}
  }
  
  sort(&buffer, reversed);
  free_buffer(&buffer);
  exit();
}


Buffer alloc_buffer(int capacity) {	//we do not use any global param here yet
  // TODO: Step 2.1: Initialize Buffer with the correct values,
  // your solution should have NOTHING unset.
	Buffer buffer;	//initialize a buffer
	buffer.buff = (char *)malloc((capacity + 1) * sizeof(char)); // do I need one extra space for \n or \o?
    	//todo: if I need to handle failed memory allocatin, do it !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    	buffer.char_count = 0;	//initially 0
    	buffer.capacity = capacity;
 
 	return buffer;
 /* 
  return (Buffer) {
      .buf = UNSET,
      .char_count = UNSET,
      .capacity = UNSET,
  };
  
*/
}

void free_buffer(Buffer* buffer) {	//ask about it. Seems too easy
  // TODO: Step 2.2: Implement basic Buffer helpers
  // This should free up the malloc'd memory used by the buffer.
  free(buffer->buff);
  buffer->char_count = 0;
  buffer->capacity = 0;
}

void resize_buffer(Buffer* buffer, int capacity) {	//pass in a doubled capacity as second arg
  // TODO: Step 2.3: Implement basic Buffer helpers
  // This should resize the allocated memory for the buffer to capacity.

  	buffer->buff = realloc(buffer->buff, capacity * sizeof(char));	//migration	
}





void iterative_heapify(char* lst, int size) {	//heapify baased on algo notes
    int begin = size - 1;
    while (begin >= 0) {
        int branch_end = begin;
        while (branch_end != 0) {
            int prev = branch_end / 2;
            if (atoi(&lst[branch_end]) > atoi(&lst[prev])) {	//sort
                int temp = lst[branch_end];
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
    while (begin >= 0) {
	    if(reversed){
	    	iterative_heapify_rev(lst, begin + 1);
	    }else{
		iterative_heapify(lst, begin + 1);
	    }

        int temp = lst[begin];
        lst[begin] = lst[0];
        lst[0] = temp;
        begin -= 1;
    }
}


void sort(Buffer* buffer, int reversed) {
	iterative_extract(buffer->buff, buffer->char_count, reversed);
  // TODO: Step 3: Implement sort using the buffer
}









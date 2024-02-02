#include "user.h"
#define UNSET 0
#define INIT_BUF_SIZE 10

typedef struct {
  char* buf;
  int char_count;
  int capacity;
} Buffer;

// To implement in Step 2
Buffer alloc_buffer(int capacity);
void free_buffer(Buffer* buffer);
void resize_buffer(Buffer* buffer, int capacity);
void read_into_buffer(int fd, Buffer* buffer);

// To implement in Step 3
void sort(Buffer* buffer, int reversed);

int main(int argc, char* argv[]) {
  int reversed = 0, fd = 0;
  // TODO: Step 1: Implement argument parsing to set fd and the reversed flag.

  Buffer buffer = alloc_buffer(INIT_BUF_SIZE);
  read_into_buffer(fd, &buffer);
  sort(&buffer, reversed);
  free_buffer(&buffer);
  exit();
}

Buffer alloc_buffer(int capacity) {
  // TODO: Step 2.1: Initialize Buffer with the correct values,
  // your solution should have NOTHING unset.
  return (Buffer) {
      .buf = UNSET,
      .char_count = UNSET,
      .capacity = UNSET,
  };
}

void free_buffer(Buffer* buffer) {
  // TODO: Step 2.2: Implement basic Buffer helpers
  // This should free up the malloc'd memory used by the buffer.
}

void resize_buffer(Buffer* buffer, int capacity) {
  // TODO: Step 2.3: Implement basic Buffer helpers
  // This should resize the allocated memory for the buffer to capacity.
}

void read_into_buffer(int fd, Buffer* buffer) {
  // TODO: Step 2.4: Implement basic Buffer helpers
  // This should read everything from fd into the buffer until it reaches EOF.

  // For debugging, you can uncomment this to check the content of the buffer.
  /*
  printf("buf: %p, capacity: %d, char_count: %d\ncontent:\n", buffer->buf, buffer->capacity, buffer->char_count);
  write(1, buffer->buf, buffer->char_count);
  printf("END OF CONTENT\n");
  */
}

void sort(Buffer* buffer, int reversed) {
  // TODO: Step 3: Implement sort using the buffer
}

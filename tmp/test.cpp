#include <cstdio>
#include <cstdlib>
#include <algorithm>
const int N = 5;
char *buf[N];

typedef size_t INTERNAL_SIZE_T;
struct malloc_chunk {
  INTERNAL_SIZE_T mchunk_prev_size;
  INTERNAL_SIZE_T mchunk_size;
};

typedef struct malloc_chunk* mchunkptr;

void
show(char *buf){
  mchunkptr p = (mchunkptr)(buf-16);
  size_t prev_size = p->mchunk_prev_size;
  size_t size = p->mchunk_size;
  size_t chunk_size = (size>>2)<<2;
  printf("0x%lx->0x%lx (0x%lx):",p,p+chunk_size,chunk_size);
  if(size &1){
    printf("prev is used; prev_size = 0x%lX\n",prev_size);
  }else{
    printf("prev is not used: prev_size = 0x%lX\n",prev_size);
  }
}

void
show_all(void){
  for(int i=0;i<N;i++){
    show(buf[i]);
  }
}

int
main(void){
  size_t SIZE = 0x108;
  for(int i=0;i<N;i++){
    buf[i] = (char*)malloc(SIZE);
    std::fill(buf[i],buf[i]+SIZE,0xAA+0x11*i);
  }
  printf("----before free-----\n");
  show_all();
  free(buf[1]);
  printf("-----after free-----\n");
  show_all();
  buf[1] = (char*)malloc(SIZE*2);
  printf("-----alloc again-----\n");
  show_all();
  for(int i=0;i<N;i++){
    free(buf[i]);
  }
}

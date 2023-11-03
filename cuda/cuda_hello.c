#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

__global__ void kernal(void)
{
    print("hello kernel here.\n");
}

int main()
{
    print("hello host here.\n");
    /*<<grid size - num of blocks && block size - num of threads*/
    kernal << 1, 1 >> ();
    return 0;
}
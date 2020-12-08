#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *code;
    char *out;
    int n = 0;
    int c;
    int i = 0;
    int pos = 0;
    int size = 0;
    char addr[4]={ 0x60, 0xce, 0xff, 0xff };

    // read input file into array 
    FILE *fptr = fopen("hex-sc", "r");
    if(fptr == NULL){
        printf("open input file failed.\n");
        exit(1);
    }
    code = malloc(100);
    out = malloc(500);

    while( (c=fgetc(fptr)) != EOF){
        code[n++] = (char)c;
    }
    // append address bytes
    code[n++] = addr[0];
    code[n++] = addr[1];
    code[n++] = addr[2];
    code[n++] = addr[3];
    code[n] = '\0';
    fclose(fptr);

    // append argument numbers 
    for(i=0; i<n; i++){
        size = sprintf(&out[pos], "%c%d ", code[i], i);
        pos += size;
    }
    out[pos] = '\0';

    printf("length=%d, buf=%s\n", n, code);
    printf("pos=%d, out=%s\n", pos, out);


    // write to output file
    FILE *fout = fopen("out.hex", "w");
    if(fout==NULL){
        printf("open out file failed.\n");
        exit(1);
    }
    fwrite(out, 1, pos, fout);
    fclose(fout);

    exit(0);
}


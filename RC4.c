#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define uchar unsigned char

void RC4(const char *path, const char* key)
{
    uchar *status = (uchar*) malloc( sizeof(uchar) * 256 );//状态矢量
    uchar *temp = (uchar*) malloc( sizeof(uchar) * 256 );//临时矢量

    //初始化
    int i, j;
    for(i = 0, j = 0; i < 256; i++, j++)
    {
        status[i] = (uchar) i;
        if(key[j] == '\0')
            j = 0;
        temp[i] = key[j];
    }
    for(i = 0, j = 0; i < 256; i++)
    {
        j = (j + status[i] + temp[i]) % 256;
        uchar t = status[i];
        status[i] = status[j];
        status[j] = t;
    }

    //构造临时文件名
    int len = strlen(path);
    char *tempPath = (char*) malloc( sizeof(char) * (len + 5) );
    char suffix[] = ".rc4";
    for(i = 0,j = 0; i < (len + 5); i++)
    {
        if(i < len)
            tempPath[i] = path[i];
        else
            tempPath[i] = suffix[j++];
    }

    //生成流密钥并加密
    FILE *fin = fopen(path, "rb");
    FILE *fout = fopen(tempPath, "wb");
    i = 0, j = 0;
    int byte = fgetc(fin);
    while(byte != -1)
    {

        //生成密钥k
        i = (i + 1) % 256;
        j = (j + status[i]) % 256;
        uchar t = status[i];
        status[i] = status[j];
        status[j] = t;
        t = (status[i] + status[j]) % 256;
        uchar k = status[t];

        //异或加密写入
        fputc((uchar)byte ^ k, fout);

        byte = fgetc(fin);
    }
    fclose(fin);
    fclose(fout);


    remove(path);//删除原文件
    rename(tempPath, path);//新文件重命名

    free(tempPath);
    free(temp);
    free(status);
}

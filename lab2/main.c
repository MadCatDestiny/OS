#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>        
#include <dirent.h>
int getFileSize(FILE *input)
{
    int fileSizeBytes;
    fseek(input, 0, SEEK_END);
    fileSizeBytes = ftell(input);
    fseek(input, 0, SEEK_SET);
    return fileSizeBytes;
}

int main(int argc,char** argv)
{
    // puts("-----------------------------");
    // printf("S_IXOTH %d\n",S_IXOTH);
    // printf("S_IWOTH %d\n",S_IWOTH);
    // printf("S_IROTH %d\n",S_IROTH);
    // printf("S_IXGRP %d\n",S_IXGRP);
    // printf("S_IWGRP %d\n",S_IWGRP);
    // printf("S_IRGRP %d\n",S_IRGRP);
    // printf("S_IXUSR %d\n",S_IXUSR);
    // printf("S_IWUSR %d\n",S_IWUSR);
    // printf("S_IRUSR %d\n",S_IRUSR);
    // printf("S_ISVTX %d\n",__S_ISVTX);
    // printf("S_ISGID %d\n",S_ISGID);
    // printf("S_ISUID %d\n",S_ISUID);
    // puts("-----------------------------\n");

    printf("%d\n",getuid());
    system("pwd > res.txt");
    FILE * f = fopen("res.txt","r");
    if (!f)
        exit(1);
    unsigned short file_size = getFileSize(f); 
    printf("file size = %d\n",file_size);
    char * path = (char*)malloc(file_size + strlen(argv[0])+1);
    fgets(path,file_size,f);
    printf("buff size  = %d\n",strlen(path));
    printf(path);
    puts("\n");
    struct dirent ** str;
    int count = scandir(path,&str,0,0);
    if (count == -1)
    {
        puts("Error");
        return 1;
    }
    
    for (int i =0; i < count; i++)
    {
        struct stat* buf;
        char * abs = (char*)malloc(strlen(path) + strlen(str[i]->d_name) + 1);
        strcpy(abs,path);
        strcat(abs,"/");
        strcat(abs,str[i]->d_name);
//        printf(abs);
//        puts("\n");
        stat(abs,buf);
//        char* time  = (char*)malloc(256*sizeof(char));
////        puts("1");
////        printf("%i", strlen(time)); // == 6???????
//        puts("\n");
//        struct tm* modif_time = localtime(&buf->st_ctime);
//        puts("1.5");
//        strftime(time,255,"%b %d %Y",modif_time);
//        puts("2");
        printf("%u\t%lu\t%hu\t%s\t%s\n", buf->st_mode, buf->st_nlink,str[i]->d_reclen,ctime(&buf->st_mtime), str[i]->d_name);
//        free(buf);
    }

    return 0;
}
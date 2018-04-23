#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <utime.h>
#include <sys/time.h>
#define MAX 1024
void startcopy(char *csource, char *ctarget);
void copyfile(char *csource, char *ctarget);

int main(int argc,char *argv[])
{
    struct stat info;
                // struct stat
                // {
                //     dev_t st_dev; //文件的设备编号
                //     ino_t st_ino; //节点
                //     mode_t st_mode; //文件的类型和存取的权限
                //     nlink_t st_nlink; //连到该文件的硬连接数目,刚建立的文件值为1
                //     uid_t st_uid; //用户ID
                //     gid_t st_gid; //组ID
                //     dev_t st_rdev; //(设备类型)若此文件为设备文件,则为其设备编号
                //     off_t st_size; //文件字节数(文件大小)
                //     unsigned long st_blksize; //块大小(文件系统的I/O 缓冲区大小)
                //     unsigned long st_blocks; //块数
                //     time_t st_atime; //最后一次访问时间
                //     time_t st_mtime; //最后一次修改时间
                //     time_t st_ctime; //最后一次改变时间(指属性)
                // };
    struct utimbuf tartime;  
                // struct utimbuf 
                // {
                //     time_t actime;/*access time*/
                //     time_t modtime; /* modify time*/
                // };
    //error in source file,return *dir
    if(opendir(argv[1])==NULL)
    {
        printf("Error open Source File.\n");
    }
    //target file does not exist
    if(opendir(argv[2])==NULL)
    {
        //get information of source file
        stat(argv[1],&info);
        //set up new target file
        mkdir(argv[2],info.st_mode);
        //change the file's time
        tartime.actime=info.st_atime;
        tartime.modtime=info.st_mtime;
        utime(argv[2],&tartime);
    }
    //start copy
    startcopy(argv[1],argv[2]);
    printf("Finish Copy!\n");
    return 0;    
}


void startcopy(char *csource, char *ctarget)
{
    char source[MAX],target[MAX];
    struct stat info;
	struct utimbuf tartime;
    struct timeval ttime[2];
    DIR *dir;
    struct dirent * next;
                    // struct dirent 
                    // {
                    //     ino_t d_ino; /* inode number */
                    //     off_t d_off; /* offset to the next dirent */
                    //     unsigned short d_reclen; /* length of this record */
                    //     unsigned char d_type; /* type of file */
                    //     char
                    //     d_name[256]; /* filename */
                    // };
    strcpy(source, csource);
	strcpy(target, ctarget);
    //open dir
	dir = opendir(source);
    //get next dir
    while((next = readdir(dir)) != NULL)
    {
        if(strcmp(next->d_name,".") != 0 && strcmp(next->d_name,"..") != 0)
        {
            //a directory
            if(next->d_type==4)
            {
                strcat(source, "/");
                strcat(source, next->d_name);
                strcat(target, "/");
                strcat(target, next->d_name);
                stat(source,&info);
                mkdir(target,info.st_mode);
                tartime.actime=info.st_atime;
                tartime.modtime=info.st_mtime;
                utime(target,&tartime);
                //recursion
                startcopy(source,target);
                strcpy(source,csource);
                strcat(target,ctarget);

            }
            //symbolic link
            else if(next->d_type==10)
            {
                strcat(source, "/");
                strcat(source, next->d_name);
                strcat(target, "/");
                strcat(target, next->d_name);
                //same with stat
                lstat(source,&info);
                //creates a symbolic link named target which contains the string source
                int a = symlink(source,target);
                if(a==-1) printf("Symlink error!\n");
                ttime[0].tv_sec = info.st_atime;
                ttime[1].tv_sec = info.st_mtime;
                ttime[0].tv_usec = 0;
                ttime[1].tv_usec = 0;
                lutimes(target, ttime);
			    copyfile(source, target);
    			strcpy(source, csource);
			    strcpy(target, ctarget);
            }
            //a named pipe,a character device,a block device,regular file...
            else
            {
                strcat(source,"/");
                strcat(source,next->d_name);
                strcat(target,"/");
                strcat(target,next->d_name);
                copyfile(source,target);
                strcpy(source,csource);
                strcpy(target,ctarget);
            }
        }   
    }
}

void copyfile(char *source, char *target)
{
    int flags=0;
    int soufd = open(source,flags);
    struct stat info;
    stat(source,&info);
    int tarfd = creat(target,info.st_mode);
    //save the content
    char buf[MAX];
    int cont;
    //write the content
    while((cont = read(soufd, buf, MAX)) > 0) write(tarfd,buf,cont);
    struct utimbuf tartime;
    tartime.actime=info.st_atime;
    tartime.modtime=info.st_mtime;
    utime(target,&tartime);
    close(soufd);
    close(tarfd);
}


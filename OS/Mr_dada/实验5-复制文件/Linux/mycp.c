#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

void copyfile(char *srcfile, char *dstfile)
{
    int srcfd = open(srcfile, O_RDONLY);
	int dstfd = open(dstfile, O_WRONLY | O_CREAT, 0666);
    char buf[1024];   
    ssize_t bytes;
    while((bytes = read(srcfd, buf, sizeof(buf))) > 0)
    {
        write(dstfd, buf, bytes);
    }
    close(srcfd);
    close(dstfd);
}

void copy(char *src, char *dst)
{
	struct stat statbuf;
	lstat(src, &statbuf);

	if (S_ISLNK(statbuf.st_mode))
	{
		char buf[50];
		readlink(src, buf, sizeof(buf));
		symlink(buf, dst);
		return;
	}

	if (!S_ISDIR(statbuf.st_mode))
	{
		copyfile(src, dst);
		return;
	}

	mkdir(dst, statbuf.st_mode);
	DIR *pdir = opendir(src);
	struct dirent *pdirent;
	while ((pdirent = readdir(pdir)) != NULL)
	{
		char *name = pdirent->d_name;
		if (strcmp(name, ".") == 0) continue;
		if (strcmp(name, "..") == 0) continue;

		char srcsub[MAXNAMLEN];
		sprintf(srcsub, "%s/%s", src, name);
		char dstsub[MAXNAMLEN];
		sprintf(dstsub, "%s/%s", dst, name);

		copy(srcsub, dstsub);
	}
}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		printf("mycp: missing file operand\n");
		printf("Usage: mycp <SRC> <DST>\n");
		return 1;
	}
	if (argc == 2)
	{
		printf("mycp: missing destination file ");
		printf("operand after '%s'\n", argv[1]);
		printf("Usage: mycp <SRC> <DST>\n");
		return 1;
	}
	copy(argv[1], argv[2]);
	return 0;
}

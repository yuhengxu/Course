#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <string.h>

//#define DEBUG
#define RUN

using namespace std;

BOOL GetDirectoryTime(char *DirectoryName, FILETIME *lpCreationTime, FILETIME *lpLastAccessTime, FILETIME *lpLastWriteTime) { //得到时间信息
																															  //获取文件夹时间属性信息
	HANDLE hDirectory = CreateFile(DirectoryName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);

	BOOL retval = GetFileTime(hDirectory, lpCreationTime, lpLastAccessTime, lpLastWriteTime);
	CloseHandle(hDirectory);      //关闭文件夹
	return retval;
}
BOOL SetDirectoryTime(char *DirectoryName, FILETIME lpCreationTime, FILETIME lpLastAccessTime, FILETIME lpLastWriteTime) { //设置时间信息
																														   //设置文件夹时间属性
	HANDLE hDirectory = CreateFile(DirectoryName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	BOOL retval = SetFileTime(hDirectory, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime);
	CloseHandle(hDirectory);
	return retval;
}

void CreateFileD(char *source, char *target) {
	FILETIME lpCreationTime;          //创建时间
	FILETIME lpLastAccessTime;        //最近一次访问时间
	FILETIME lpLastWriteTime;         //最近一次修改时间
									  //创建目录
	CreateDirectory(target, NULL);
	GetDirectoryTime(source, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime);
	SetDirectoryTime(target, lpCreationTime, lpLastAccessTime, lpLastWriteTime);
	//return a;
}

void CopyFileA(char *fsource, char *ftarget) {
	WIN32_FIND_DATA lpfindfiledata;
	HANDLE hfind = FindFirstFile(fsource, &lpfindfiledata);   //查找指定文件路径
	HANDLE hsource = CreateFile(fsource, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS,/* 文件若存在则打开*/FILE_ATTRIBUTE_NORMAL, NULL);
	//文件名，访问模式，共享模式，指向安全属性的指针，如何创建，文件属性，复制文件的句柄
	HANDLE htarget = CreateFile(ftarget, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,/*创建一个文件*/ FILE_ATTRIBUTE_NORMAL/* 不设置属性*/, NULL);
	LONG size = lpfindfiledata.nFileSizeLow - lpfindfiledata.nFileSizeHigh;  //length
	DWORD wordbit;
	int *BUFFER = new int[size];  //新开缓冲区,保存数据
	ReadFile(hsource, BUFFER, size, &wordbit, NULL);  //源文件读数据

													  /*
													  WriteFile 函数原型与CreateFile相同
													  */
	WriteFile(htarget, BUFFER, size, &wordbit, NULL); //目标文件写数据
													  //修改文件时间信息
	GetFileTime(hsource, &lpfindfiledata.ftCreationTime, &lpfindfiledata.ftLastAccessTime, &lpfindfiledata.ftLastWriteTime);
	SetFileTime(htarget, &lpfindfiledata.ftCreationTime, &lpfindfiledata.ftLastAccessTime, &lpfindfiledata.ftLastWriteTime);
	CloseHandle(hfind);  //关闭句柄
	CloseHandle(hsource);
	CloseHandle(htarget);
}

//将源目录信息复制到目标目录下
void Mycp(char *fsource, char *ftarget) {
	WIN32_FIND_DATA lpfindfiledata;
	char source[512];
	char target[512];
	FILETIME lpCreationTime;          //创建时间
	FILETIME lpLastAccessTime;        //最近一次访问时间
	FILETIME lpLastWriteTime;         //最近一次修改时间
	strcpy(source, fsource);    //copy  fsource->source
	strcpy(target, ftarget);
	strcat(source, "\\*.*");
	strcat(target, "\\");
	HANDLE hfind = FindFirstFile(source, &lpfindfiledata);
	if (hfind != INVALID_HANDLE_VALUE) {
		while (FindNextFile(hfind, &lpfindfiledata) != 0) {  //查找下一个文件成功
			if (lpfindfiledata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) { //判断文件还是文件夹
				if ((strcmp(lpfindfiledata.cFileName, ".") != 0) && (strcmp(lpfindfiledata.cFileName, "..") != 0)) {
					memset(source, '0', sizeof(source));
					strcpy(source, fsource);
					strcat(source, "\\");
					strcat(source, lpfindfiledata.cFileName);   //追加文件名
					strcat(target, lpfindfiledata.cFileName);
					CreateFileD(source, target);
					Mycp(source, target);   //进入子目录复制
					GetDirectoryTime(source, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime);
					SetDirectoryTime(target, lpCreationTime, lpLastAccessTime, lpLastWriteTime);
					strcpy(source, fsource);
					strcat(source, "\\");
					strcpy(target, ftarget);
					strcat(target, "\\");
				}
			}
			else {    //无目录
					  //直接复制
				memset(source, '0', sizeof(source));
				strcpy(source, fsource);
				strcat(source, "\\");
				strcat(source, lpfindfiledata.cFileName);
				strcat(target, lpfindfiledata.cFileName);
				CopyFileA(source, target);
				strcpy(source, fsource);
				strcat(source, "\\");
				strcpy(target, ftarget);
				strcat(target, "\\");
			}
		}
	}
}

int main(int argc, char *argv[]) {
	WIN32_FIND_DATA lpfindfiledata;
	FILETIME lpCreationTime;          //创建时间
	FILETIME lpLastAccessTime;        //最近一次访问时间
	FILETIME lpLastWriteTime;         //最近一次修改时间

	if (argc != 3) {
		cout << "参数个数错误!" << endl;     //参数出错
		system("PAUSE");
		return 0;
	}
	else {
		if (FindFirstFile(argv[1], &lpfindfiledata) == INVALID_HANDLE_VALUE) {
			cout << "查找源文件路径失败！" << endl;   //查找源文件路径失败
			system("PAUSE");
			return 0;
		}
		if (FindFirstFile(argv[2], &lpfindfiledata) == INVALID_HANDLE_VALUE) {
			CreateFileD(argv[1], argv[2]);	//如果目标路径不存在，则创建该路径文件
		}
		Mycp(argv[1], argv[2]);      //复制
		GetDirectoryTime(argv[1], &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime);
		SetDirectoryTime(argv[2], lpCreationTime, lpLastAccessTime, lpLastWriteTime);
		cout << "复制完成！" << endl;
	}

	return 0;
}

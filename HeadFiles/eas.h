#ifndef _EAS_H
#define _EAS_H

/* 为了防止重复编译标准库文件，这里存放C语言标准库专用头文件。 */
#include "CStandardLibrary.h"

/* EAS 加密算法函数 */
int easEncrypt(char *resPath, char *tarPath);

/* EAS 解密算法函数（虽然解密算法函数和加密算法函数的算法一致），
但是为了增加程序的逻辑性和整体架构，
所以保留此函数）。 */
int easDecrypt(char *resPath, char *tarPath);

#endif
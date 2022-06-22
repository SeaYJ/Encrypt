#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <io.h>
#include <Windows.h>

#define F_OK 0
#define R_OK 2
#define W_OK 4
#define X_OK 6

/// <summary>
/// 定义 ENCRYPTINFO 数据类型
/// 作用：存储加密时需要的有效信息
/// 内部成员：
///		- inFile		输入文件路径（确保存在）
///		- outFile		输出文件路径（确保存在）
///		- encAlgorithm	加密类型（确保支持）
/// </summary>
typedef struct _ENCRYPT_INFO
{
	char inFile[_MAX_PATH];
	char outFile[_MAX_PATH];
	char encAlgorithm[_MAX_FNAME];
} ENCRYPTINFO;
// 提供一个默认变量
ENCRYPTINFO encInfo = { 0 };

// 定义支持的加密类型
char *supportEncAlgorithm[1] = {
	"SHA256"
};

static int errCode = 0;

int paraParsing(int paraCount, char *paras[]);
int encInfoCheck();
int fPathCheck(const char *fPath);
int encAlgoCheck(const char *encAlgo);


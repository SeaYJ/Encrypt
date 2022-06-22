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
/// ���� ENCRYPTINFO ��������
/// ���ã��洢����ʱ��Ҫ����Ч��Ϣ
/// �ڲ���Ա��
///		- inFile		�����ļ�·����ȷ�����ڣ�
///		- outFile		����ļ�·����ȷ�����ڣ�
///		- encAlgorithm	�������ͣ�ȷ��֧�֣�
/// </summary>
typedef struct _ENCRYPT_INFO
{
	char inFile[_MAX_PATH];
	char outFile[_MAX_PATH];
	char encAlgorithm[_MAX_FNAME];
} ENCRYPTINFO;
// �ṩһ��Ĭ�ϱ���
ENCRYPTINFO encInfo = { 0 };

// ����֧�ֵļ�������
char *supportEncAlgorithm[1] = {
	"SHA256"
};

static int errCode = 0;

int paraParsing(int paraCount, char *paras[]);
int encInfoCheck();
int fPathCheck(const char *fPath);
int encAlgoCheck(const char *encAlgo);


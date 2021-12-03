#ifndef _ENCRYPT_H
#define _ENCRYPT_H

/* Ϊ�˷�ֹ�ظ������׼���ļ���������C���Ա�׼��ר��ͷ�ļ��� */
#include "CStandardLibrary.h" 

/* ����д���ǰ汾��Ϣ�� ��Ҫ�޸ľ��������޸ľ����ˣ� */
struct verInfo 
{
	char *version;
	char *author;
	char *officalPage;
	char *statement;
	int astrisksNum; /* �汾��Ϣ���ϲ� * �ŵĸ��� */
} versionInfo = {
	"2021.11.18.1",									/* �汾�� */
	"SeaYJ",										/* ���� */
	"����",											/* ���� */
	"ԭ����(SeaYJ)��������Ȩ�������ս���Ȩ��",		/* ���� */
	49
};

/* ���ڴ洢�����ļ�����Ҫ�ľ�����Ϣ*/
struct EncInfo 
{
	char *inputFilePath; /* Դ�ļ�·�� */
	char *outputFilePath; /* ���ļ�·�� */
	char *encryptMethod; /* ���ܷ�ʽ */
} encryptInfo = {NULL, NULL, NULL};


/* ���ڴ洢Դ�ļ��ľ�����Ϣ
nameSuffix	-	�ļ���׺��
docName		-	�ļ���
fileEnv		-	�ļ�����·��
fileName	-	�ļ�ȫ��
*/
struct InputFilePathSplit
{
	char nameSuffix[_MAX_EXT]; // ������׺ǰ���С����
	char docName[_MAX_FNAME];
	char fileEnv[_MAX_DIR];
	char fileName[_MAX_FNAME + _MAX_EXT];
} resFileInfo;

/* �������򴫵ݵĲ������д���
������Ĳ�����Ϣ�洢�� struct EncInfo EncryptInfo �У�
ע�⣺
�����Ǿ��Դ�������ĺ���ֻ��Ҫ��������Ϣ�����ɣ�
Ҳ����������뱣֤�ļ�����������Ϣ���������������Ƿ���ý��м�飬�о��У���*/
int parameterHandling(int argc, char *argv[]); 

/* �˺������� parameterHandling �������ã�
���ڶԼ���������Ϣ����ȫ���飬
���������Ϣ�Ƿ���ý��м�飡 
���������᳢�Խ���������
�����������˵Ĵ��󽫻������ͷ���ֵ����ʽ��֪�������ĸ�����*/
int infoCheck();

int inputFilePathDeal();

/* [���������� - ·��������������]
��������Ĳ���·������������ */
char* pathCheckFunction(char *res_path);
struct pathDealFunction
{
	char* (*pathCheck)(char *res_path);	/* �ļ�·����� */
} pathDeal = { pathCheckFunction };

int encryptionMethodSelection(char *inputFilePath, char *outputFilePath, char *encryptMethod);

#endif
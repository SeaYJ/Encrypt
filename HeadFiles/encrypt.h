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

/* ����/���ܷ���
���磺
EAS Ϊ�򵥼��ܱ�����
��ô DEAS ��Ϊ��Ӧ�Ľ��ܱ�����
*/
enum EncMethod 
{
	EAS = 0,
	DEAS,

	PEAS,
	DPEAS,

	DES,
	DDES
};

/* ����ǰִ�е�״̬
true	-	����
false	-	����
*/
bool EncOrDec = false;

#define _MAX_FILE_PATH_LENGTH_ 300
#define _MAX_PASSWORD_LENGTH_ 16
/* ���ڴ洢�����ļ�����Ҫ�ľ�����Ϣ*/
struct EncInfo 
{
	char inputFilePath[_MAX_FILE_PATH_LENGTH_]; /* Դ�ļ�·�� */
	char outputFilePath[_MAX_FILE_PATH_LENGTH_]; /* ���ļ�·�� */
	enum EncMethod encryptMethod; /* ���ܷ�ʽ */
	char password[_MAX_PASSWORD_LENGTH_]; /* �������룬��ΪNULL */
} encryptInfo = {{0}, {0}, EAS, "123456"};

/* ���ڴ洢Դ�ļ��ľ�����Ϣ
nameSuffix	-	�ļ���׺��
docName		-	�ļ���
fileEnv		-	�ļ�����·��
fileName	-	�ļ�ȫ��
*/
struct InputFilePathSplit
{
	char suffixName[_MAX_EXT]; // ������׺ǰ���С����
	char docName[_MAX_FNAME];
	char fileEnv[_MAX_DIR];
	char fileName[_MAX_FNAME + _MAX_EXT];
} resFileInfo = {{0}, {0}, {0}, {0}};

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

int inputFilePathDeal(char *inputPath);

/* [���������� - ·��������������]
��������Ĳ���·������������ */
char* pathPolishFunction(char *res_path);
struct pathDealFunction
{
	char* (*pathPolish)(char *res_path);	/* �ļ�·����� */
} pathDeal = { pathPolishFunction };

int encrypt(char *inputFilePath, char *outputFilePath, enum EncMethod encWay);

/* �����洢��������ʱ��Ľṹ�����
�������û�δָ�����·��ʱ���Զ�����һ�����·����
���ɵ������·���ļ���������� -ENCRYPT_XXXX-XX-XX-XX-XX-XX �Է�ֹ�ļ����ܺ󸲸�ͬ���ļ���
���Ƕ����û�ָ���������·���󣬲���Ӻ�׺��
*/
struct TimeNow
{
	char year[5];
	char month[3];
	char day[3];
	char hour[3];
	char minute[3];
	char second[3];
} timer;
int timeGet();

#endif
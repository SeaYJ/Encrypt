#include "eas.h"

/* ���ַ��� ASCLL �����ȡ��������
Ȼ��ȡ����� ASCLL �뷭����ַ��洢��
��ɽ��ܡ� */
int easEncrypt(char *resPath, char *tarPath)
{

	FILE *res_fp = NULL, *tar_fp = NULL;
	char ch;

	if (NULL == (res_fp = fopen(resPath, "r")))
	{
		printf("ERROR(2001):Unable to open the target file!\n");
		return 1;
	}
	if (NULL == (tar_fp = fopen(tarPath, "w")))
	{
		printf("ERROR(2002):Error creating target file!\n");
		return 2;
	}

	while(EOF != (ch = fgetc(res_fp)))
	{
		ch = ~(int)ch;
		fputc(ch, tar_fp);
	}

	fclose(res_fp);
	fclose(tar_fp);

	return (0);
}

/* �Լ����ַ��� ASCLL �����ȡ��������
Ȼ��ȡ����� ASCLL �뷭����ַ��洢��
��ɽ��ܡ� */
int easDncrypt(char *resPath, char *tarPath)
{

	FILE *res_fp = NULL, *tar_fp = NULL;
	char ch;

	if (NULL == (res_fp = fopen(resPath, "r")))
	{
		printf("ERROR(2001):Unable to open the target file!\n");
		return 1;
	}
	if (NULL == (tar_fp = fopen(tarPath, "w")))
	{
		printf("ERROR(2002):Error creating target file!\n");
		return 2;
	}

	while(EOF != (ch = fgetc(res_fp)))
	{
		ch = ~(int)ch;
		fputc(ch, tar_fp);
	}

	fclose(res_fp);
	fclose(tar_fp);

	return (0);
}
#include "eas.h"

/* 对字符的 ASCLL 码进行取反操作，
然后将取反后的 ASCLL 码翻译成字符存储，
完成解密。 */
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

/* 对加密字符的 ASCLL 码进行取反操作，
然后将取反后的 ASCLL 码翻译成字符存储，
完成解密。 */
int easDecrypt(char *resPath, char *tarPath)
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
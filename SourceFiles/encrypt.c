#include "encrypt.h"
#include "eas.h"

int main(int argc,char *argv[])
{
	parameterHandling(argc, argv);

	return (0);
}

int parameterHandling(int argc, char *argv[])
{
	int i,j;
	
	for (i=1; i<argc; i++)
	{
		if( (0==stricmp(argv[i], "-v")) || (0==stricmp(argv[i], "-version")) )	/* ��ȡ�汾��Ϣ���� */
		{
			putchar('\n');
			for(j=0; j<versionInfo.astrisksNum; j++) putchar('*');
			printf("\n* Version\t%s\t\t\t*\n* Author\t%s\t\t\t\t*\n* OfficalPage\t%s\t\t\t\t*\n* %s\t*\n",versionInfo.version, versionInfo.author, versionInfo.officalPage, versionInfo.statement);
			for(j=0; j<versionInfo.astrisksNum; j++) putchar('*');
			putchar('\n');
			return 0;
		}
		else if( (0==stricmp(argv[i], "-renew")) ) /* ������� */
		{
			printf("��ȡ���£�\n");

			return 0;
		}
		else if( (0==stricmp(argv[i], "-i")) ) /* ��ȡԴ�ļ�·�� */
		{
			encryptInfo.inputFilePath = argv[i+1];
			encryptInfo.inputFilePath = pathDeal.pathCheck(encryptInfo.inputFilePath);	 /* Դ�ļ�·����� */
		}
		else if( (0==stricmp(argv[i], "-o")) ) /* ��ȡĿ���ļ�·�� */
		{
			encryptInfo.outputFilePath = argv[i+1];
			encryptInfo.outputFilePath = pathDeal.pathCheck(encryptInfo.outputFilePath); /* Ŀ���ļ�·����� */
		}
		else if( '+' == (*argv[i]) )	/* ��ȡ���ܷ�ʽ */
		{
			if( 0==stricmp(argv[i], "+EAS") )
			{
				encryptInfo.encryptMethod = "EAS";
			}
			else if( 0==stricmp(argv[i], "+PEAS") )
			{
				encryptInfo.encryptMethod = "PEAS";
			}
			else if( 0==stricmp(argv[i], "+DES") )
			{
				encryptInfo.encryptMethod = "DES";
			}
			else if( 0==stricmp(argv[i], "+3DES") )
			{
				encryptInfo.encryptMethod = "3DES";
			}
			else if( 0==stricmp(argv[i], "+IDEA") )
			{
				encryptInfo.encryptMethod = "IDEA";
			}
			else
			{
				encryptInfo.encryptMethod = "EAS";
			}
		}
	}

	infoCheck();

	return (0);
}

int infoCheck()
{
	int numBug = 0, i;

	if (NULL ==  encryptInfo.inputFilePath) // ȷ����������ļ�·���ܽ���Ĭ��ֵ��ȫ��������ô���鲻ͨ��Ӧ��ֱ�ӽ�����飬���������򱨴�
	{
		printf("ERROR:Դ�ļ���ַ�����ڣ�\n");
		return numBug+=2; // Դ·�������ڣ���Ŀ��·����Ӧ�ô���
	}

	if (NULL == encryptInfo.outputFilePath)
	{
		inputFilePathDeal();
	}

	return numBug;
}

int inputFilePathDeal()
{
	bool flagSuf = false, flagDoc = false;
	int i = 0, suffixPoint = 0, docPoint = 0, startPoint = 0, endPoint = 0, index = 0;
	char * ch;

	if (NULL == encryptInfo.inputFilePath) return 1;

	endPoint = strlen(encryptInfo.inputFilePath);

	for(i=endPoint; i>=0; i--)
	{
		if((!flagSuf) && ('.' == ch[i]))
		{
			flagSuf = true;
			suffixPoint = i;
		}

		if((!flagDoc) && ('\\' == ch[i]))
		{
			flagDoc = true;
			docPoint = i;
		}
	}

	for (i=(suffixPoint+1); i<endPoint; i++)
	{
		resFileInfo.nameSuffix[index++] = 
	}

	return 0;
}

char* pathCheckFunction(char *res_path) 
{
	int len = strlen(res_path), i = 0;
	
	static char right_path[500];

	while('\0' != *res_path)
	{
		if ('\\' == *res_path)			
		{
			if(('\\' != *(res_path-1)) && ('\\' != *(res_path+1))) { /* A\B ��� A\\B */
				right_path[i++] = '\\';
				right_path[i++] = *res_path;
			} else if(('\\' == *(res_path-1)) && ('\\' == *(res_path+1))) { /* \\...\...\\ �� \\ */
				 /* ���λ�ò���ɾ��Ŷ~
				 ����Ϊ�˺��������������ϣ���ͬɸѡ */
			} else if(('\\' == *(res_path-1)) || ('\\' == *(res_path+1))) { /* A\\... (�� ...\\B )�� A\ (�� \B)*/
				right_path[i++] = *res_path;
			}
		}else {							// ���������ַ�
			right_path[i++] = *res_path;
		}

		res_path++; // ���������������Ȼ��һ���ַ��޷���ȡ��������Ŷ
	}
	right_path[i] = *res_path;		// ���Ͻ����� '\0'
	
	return right_path;
}

int encryptionMethodSelection(char *inputFilePath, char *outputFilePath, char *encryptMethod)
{
	if( 0==stricmp(encryptMethod, "+EAS") )
	{
		easEncrypt(inputFilePath, outputFilePath);
	}
	else if( 0==stricmp(encryptMethod, "+PEAS") )
	{
		printf("����Ҫ���� %s ���ܺ�����\n", encryptMethod);
	}
	else if( 0==stricmp(encryptMethod, "+DES") )
	{
		printf("����Ҫ���� %s ���ܺ�����\n", encryptMethod);
	}
	else if( 0==stricmp(encryptMethod, "+3DES") )
	{
		printf("����Ҫ���� %s ���ܺ�����\n", encryptMethod);
	}
	else if( 0==stricmp(encryptMethod, "+IDEA") )
	{
		printf("����Ҫ���� %s ���ܺ�����\n", encryptMethod);
	}
	else
	{
		printf("���﷢��δ֪����\n");
	}

	return 0;
}
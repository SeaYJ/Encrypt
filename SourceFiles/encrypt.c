#include "encrypt.h"
#include "eas.h"

int main(int argc,char *argv[])
{
	timeGet();
	parameterHandling(argc, argv);
	encrypt(encryptInfo.inputFilePath, encryptInfo.outputFilePath, encryptInfo.encryptMethod);
	return 0;
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

			return NO_ERROR;
		}
		else if( 0==stricmp(argv[i], "-renew") ) /* ������� */
		{
			system("explorer https://github.com/SeaYJ/Encrypt");

			return NO_ERROR;
		}
		else if( 0==stricmp(argv[i], "-i") ) /* ��ȡԴ�ļ�·�� */
		{
			strcpy(encryptInfo.inputFilePath, argv[i+1]);
			strcpy(encryptInfo.inputFilePath, pathDeal.pathPolish(encryptInfo.inputFilePath)); /* Դ�ļ�·����� */
		}
		else if( 0==stricmp(argv[i], "-o") ) /* ��ȡĿ���ļ�·�� */
		{
			strcpy(encryptInfo.outputFilePath, argv[i+1]);
			strcpy(encryptInfo.outputFilePath, pathDeal.pathPolish(encryptInfo.outputFilePath)); /* Ŀ���ļ�·����� */
		}
		else if( '+' == *argv[i] )	/* ��ȡ���ܷ�ʽ */
		{
			if( 0==stricmp(argv[i], "+EAS") )
			{
				encryptInfo.encryptMethod = EAS;
			}
			else if( 0==stricmp(argv[i], "+PEAS") )
			{
				encryptInfo.encryptMethod = PEAS;
			}
			else if( 0==stricmp(argv[i], "+DES") )
			{
				encryptInfo.encryptMethod = DES;
			}
			else
			{
				printf("ERROR(1001):"
					"There is no such encryption method!\n"
					"From encrypt.exe\n");
				return FUN_ERROR;
			}
			EncOrDec = false;
		}
		else if( ('-' == *argv[i]) && ('-' == *(argv[i]+1)) ) /* ��ȡ���ܷ�ʽ */
		{
			if( 0==stricmp(argv[i], "--EAS") )
			{
				encryptInfo.encryptMethod = DEAS;
			}
			else if( 0==stricmp(argv[i], "--PEAS") )
			{
				encryptInfo.encryptMethod = DPEAS;
			}
			else if( 0==stricmp(argv[i], "--DES") )
			{
				encryptInfo.encryptMethod = DDES;
			}
			else
			{
				printf("ERROR(1002):"
					"There is no such decryption method!\n"
					"From encrypt.exe\n");
				return FUN_ERROR;
			}
			EncOrDec = true;
		}
		else if ( 0 == stricmp(argv[i], "-p")) /* ��ȡ�������� */
		{
			 strcpy(encryptInfo.password, argv[i+1]);
		}
	}

	infoCheck();
	
	return 0;
}

int infoCheck()
{
	if ('\0' ==  encryptInfo.inputFilePath[0]) // ȷ����������ļ�·���ܽ���Ĭ��ֵ��ȫ��������ô���鲻ͨ��Ӧ��ֱ�ӽ�����飬���������򱨴�
	{
		printf("ERROR(1003):"
			"When checking the file path,\n"
			"it was found that the target file path did not exist!\n"
			"From encrypt.exe\n");
		return FUN_ERROR;
	}
	else
	{
		inputFilePathDeal(encryptInfo.inputFilePath);
	}

	if ('\0' == encryptInfo.outputFilePath[0]) // ���û�δ�������·��ʱ����һ��Ĭ�ϵ����·��
	{
		if ((NULL == resFileInfo.docName) || (NULL == resFileInfo.fileEnv) || (NULL == resFileInfo.fileName) || (NULL == resFileInfo.suffixName))
		{
			printf("ERROR(1004):"
				"When we checked the file path and prepared to generate the default output path,\n"
				"we found that the specific information of the input file was incomplete!\n"
				"From encrypt.exe\n");
			return FUN_ERROR;
		}
		strcat(encryptInfo.outputFilePath, resFileInfo.fileEnv);
		strcat(encryptInfo.outputFilePath, resFileInfo.docName);
		(EncOrDec) ? (strcat(encryptInfo.outputFilePath, "_DNCRYPTED_")) : (strcat(encryptInfo.outputFilePath, "_EECRYPTED_"));
		strcat(encryptInfo.outputFilePath, timer.year);
		strcat(encryptInfo.outputFilePath, timer.month);
		strcat(encryptInfo.outputFilePath, timer.day);
		strcat(encryptInfo.outputFilePath, timer.hour);
		strcat(encryptInfo.outputFilePath, timer.minute);
		strcat(encryptInfo.outputFilePath, timer.second);
		strcat(encryptInfo.outputFilePath, ".");
		strcat(encryptInfo.outputFilePath, resFileInfo.suffixName);
	}
	

	return NO_ERROR;
}

/* �˺���������ȡ����·���� �ļ������ļ���չ�����ļ��������ļ�ȫ�� */
int inputFilePathDeal(char *inputPath)
{
	/* ����ȷ����һ�γ��ַֽ��־��
	��һ�γ��ֻὫ��ֵ��Ϊ true �����ڱ�ʾ�Ѿ��ҵ��˷ֽ��־�����ѻ�÷ֽ�㣩�� */
	bool flagSuf = false, flagDoc = false; 

	int i = 0, suffixPoint = 0, docPoint = 0, startPoint = 0, endPoint = 0, index = 0;

	if (NULL == inputPath) return FUN_ERROR;

	endPoint = strlen(encryptInfo.inputFilePath);

	for(i=endPoint; i>=0; i--) /* ȷ���ֽ�� */
	{
		if((!flagSuf) && ('.' == inputPath[i]))
		{
			flagSuf = true;
			suffixPoint = i;
		}

		if((!flagDoc) && ('\\' == inputPath[i]))
		{
			flagDoc = true;
			docPoint = i;
		}
	}

	for (i=(suffixPoint+1); i<endPoint; i++) /* ��ȡ�ļ��� */
	{
		resFileInfo.suffixName[index++] = inputPath[i];
	}
	resFileInfo.suffixName[index] = '\0';
	index = 0;

	for(i=(docPoint+1); i<suffixPoint; i++) /* ��ȡ�ļ���չ�� */
	{
		resFileInfo.docName[index++] = inputPath[i];
	}
	resFileInfo.docName[index] = '\0';
	index = 0;
	
	for(i=(docPoint+1); i<endPoint; i++) /* ��ȡ�ļ�ȫ�� */
	{
		resFileInfo.fileName[index++] = inputPath[i];
	}
	resFileInfo.fileName[index] = '\0';
	index = 0;

	for(i=0; i<=docPoint; i++) /* ��ȡ�ļ����� */
	{
		resFileInfo.fileEnv[index++] = inputPath[i];
	}
	resFileInfo.fileEnv[index] = '\0';
	index = 0;

	return NO_ERROR;
}

char* pathPolishFunction(char *res_path) 
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

int encrypt(char *inputFilePath, char *outputFilePath, enum EncMethod encWay)
{
	switch(encWay)
	{
	case 0:easEncrypt(inputFilePath, outputFilePath);break;
	case 1:easDecrypt(inputFilePath, outputFilePath);break;

	case 2:break;
	case 3:break;
	default:printf("ERROR(1005):"
				"When calling the function according to the encryption method,\n"
				"we did not find the corresponding encryption function or program!\n"
				"From encrypt.exe\n");
	}

	return NO_ERROR;
}

int timeGet()
{
	time_t now;
	struct tm *tm_now;
	time(&now);
	tm_now = localtime(&now);


	itoa((tm_now->tm_year + 1900), timer.year, 10);
	itoa((tm_now->tm_mon + 1), timer.month, 10);
	itoa(tm_now->tm_mday, timer.day, 10);
	itoa(tm_now->tm_hour, timer.hour, 10);
	itoa(tm_now->tm_min, timer.minute, 10);
	itoa(tm_now->tm_sec, timer.second, 10);
	

	return NO_ERROR;
}
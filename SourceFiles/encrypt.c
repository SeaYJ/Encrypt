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
		if( (0==stricmp(argv[i], "-v")) || (0==stricmp(argv[i], "-version")) )	/* 获取版本信息界面 */
		{
			putchar('\n');
			for(j=0; j<versionInfo.astrisksNum; j++) putchar('*');
			printf("\n* Version\t%s\t\t\t*\n* Author\t%s\t\t\t\t*\n* OfficalPage\t%s\t\t\t\t*\n* %s\t*\n",versionInfo.version, versionInfo.author, versionInfo.officalPage, versionInfo.statement);
			for(j=0; j<versionInfo.astrisksNum; j++) putchar('*');
			putchar('\n');

			return NO_ERROR;
		}
		else if( 0==stricmp(argv[i], "-renew") ) /* 程序更新 */
		{
			system("explorer https://github.com/SeaYJ/Encrypt");

			return NO_ERROR;
		}
		else if( 0==stricmp(argv[i], "-i") ) /* 获取源文件路径 */
		{
			strcpy(encryptInfo.inputFilePath, argv[i+1]);
			strcpy(encryptInfo.inputFilePath, pathDeal.pathPolish(encryptInfo.inputFilePath)); /* 源文件路径检查 */
		}
		else if( 0==stricmp(argv[i], "-o") ) /* 获取目标文件路径 */
		{
			strcpy(encryptInfo.outputFilePath, argv[i+1]);
			strcpy(encryptInfo.outputFilePath, pathDeal.pathPolish(encryptInfo.outputFilePath)); /* 目标文件路径检查 */
		}
		else if( '+' == *argv[i] )	/* 获取加密方式 */
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
		else if( ('-' == *argv[i]) && ('-' == *(argv[i]+1)) ) /* 获取解密方式 */
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
		else if ( 0 == stricmp(argv[i], "-p")) /* 获取加密密码 */
		{
			 strcpy(encryptInfo.password, argv[i+1]);
		}
	}

	infoCheck();
	
	return 0;
}

int infoCheck()
{
	if ('\0' ==  encryptInfo.inputFilePath[0]) // 确保后面输出文件路径能进行默认值补全处理，如果该处检查不通过应该直接结束检查，并给主程序报错！
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

	if ('\0' == encryptInfo.outputFilePath[0]) // 当用户未输入输出路径时生产一个默认的输出路径
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

/* 此函数用于提取输入路径的 文件名、文件扩展名、文件环境、文件全称 */
int inputFilePathDeal(char *inputPath)
{
	/* 用于确定第一次出现分界标志：
	第一次出现会将其值改为 true ，用于表示已经找到了分界标志（即已获得分界点）。 */
	bool flagSuf = false, flagDoc = false; 

	int i = 0, suffixPoint = 0, docPoint = 0, startPoint = 0, endPoint = 0, index = 0;

	if (NULL == inputPath) return FUN_ERROR;

	endPoint = strlen(encryptInfo.inputFilePath);

	for(i=endPoint; i>=0; i--) /* 确定分界点 */
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

	for (i=(suffixPoint+1); i<endPoint; i++) /* 提取文件名 */
	{
		resFileInfo.suffixName[index++] = inputPath[i];
	}
	resFileInfo.suffixName[index] = '\0';
	index = 0;

	for(i=(docPoint+1); i<suffixPoint; i++) /* 提取文件扩展名 */
	{
		resFileInfo.docName[index++] = inputPath[i];
	}
	resFileInfo.docName[index] = '\0';
	index = 0;
	
	for(i=(docPoint+1); i<endPoint; i++) /* 提取文件全名 */
	{
		resFileInfo.fileName[index++] = inputPath[i];
	}
	resFileInfo.fileName[index] = '\0';
	index = 0;

	for(i=0; i<=docPoint; i++) /* 提取文件环境 */
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
			if(('\\' != *(res_path-1)) && ('\\' != *(res_path+1))) { /* A\B 变成 A\\B */
				right_path[i++] = '\\';
				right_path[i++] = *res_path;
			} else if(('\\' == *(res_path-1)) && ('\\' == *(res_path+1))) { /* \\...\...\\ 变 \\ */
				 /* 这个位置不能删除哦~
				 这是为了和下面那种情况配合，共同筛选 */
			} else if(('\\' == *(res_path-1)) || ('\\' == *(res_path+1))) { /* A\\... (或 ...\\B )变 A\ (或 \B)*/
				right_path[i++] = *res_path;
			}
		}else {							// 正常复制字符
			right_path[i++] = *res_path;
		}

		res_path++; // 这个必须放在这里，不然第一个字符无法读取到数组里哦
	}
	right_path[i] = *res_path;		// 补上结束符 '\0'
	
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
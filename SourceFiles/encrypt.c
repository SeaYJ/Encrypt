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
		if( (0==stricmp(argv[i], "-v")) || (0==stricmp(argv[i], "-version")) )	/* 获取版本信息界面 */
		{
			putchar('\n');
			for(j=0; j<versionInfo.astrisksNum; j++) putchar('*');
			printf("\n* Version\t%s\t\t\t*\n* Author\t%s\t\t\t\t*\n* OfficalPage\t%s\t\t\t\t*\n* %s\t*\n",versionInfo.version, versionInfo.author, versionInfo.officalPage, versionInfo.statement);
			for(j=0; j<versionInfo.astrisksNum; j++) putchar('*');
			putchar('\n');
			return 0;
		}
		else if( (0==stricmp(argv[i], "-renew")) ) /* 程序更新 */
		{
			printf("获取更新！\n");

			return 0;
		}
		else if( (0==stricmp(argv[i], "-i")) ) /* 获取源文件路径 */
		{
			encryptInfo.inputFilePath = argv[i+1];
			encryptInfo.inputFilePath = pathDeal.pathCheck(encryptInfo.inputFilePath);	 /* 源文件路径检查 */
		}
		else if( (0==stricmp(argv[i], "-o")) ) /* 获取目标文件路径 */
		{
			encryptInfo.outputFilePath = argv[i+1];
			encryptInfo.outputFilePath = pathDeal.pathCheck(encryptInfo.outputFilePath); /* 目标文件路径检查 */
		}
		else if( '+' == (*argv[i]) )	/* 获取加密方式 */
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

	if (NULL ==  encryptInfo.inputFilePath) // 确保后面输出文件路径能进行默认值补全处理，如果该处检查不通过应该直接结束检查，并给主程序报错！
	{
		printf("ERROR:源文件地址不存在！\n");
		return numBug+=2; // 源路径不存在，则目标路径不应该存在
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

int encryptionMethodSelection(char *inputFilePath, char *outputFilePath, char *encryptMethod)
{
	if( 0==stricmp(encryptMethod, "+EAS") )
	{
		easEncrypt(inputFilePath, outputFilePath);
	}
	else if( 0==stricmp(encryptMethod, "+PEAS") )
	{
		printf("这里要调用 %s 加密函数！\n", encryptMethod);
	}
	else if( 0==stricmp(encryptMethod, "+DES") )
	{
		printf("这里要调用 %s 加密函数！\n", encryptMethod);
	}
	else if( 0==stricmp(encryptMethod, "+3DES") )
	{
		printf("这里要调用 %s 加密函数！\n", encryptMethod);
	}
	else if( 0==stricmp(encryptMethod, "+IDEA") )
	{
		printf("这里要调用 %s 加密函数！\n", encryptMethod);
	}
	else
	{
		printf("这里发生未知错误！\n");
	}

	return 0;
}
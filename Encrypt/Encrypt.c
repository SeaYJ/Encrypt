#include "Encrypt.h"

int main(int argc, char* argv[])
{
	int ret;
	
	// 参数列表解析
	ret = paraParsing(argc, argv);
	if (ret)
		return ret;

	// 加密必要信息检查
	ret = encInfoCheck(encInfo);
	if (ret)
		return ret;

	return 0;
}

int paraParsing(int paraCount, char* paras[])
{
	errCode = 0;

	if (paraCount <= 1)
	{
		// 未找到有效参数
		errCode = 1312;
		printf("ERROR(%d): 未找到有效参数！\n", errCode);
		return errCode;
	}

	for (int i = 1; i < paraCount; i++)
	{
		if (_stricmp(paras[i], "-i") == 0)
		{
			if (++i > (paraCount - 1))
			{
				// -i 后缺少指定输入文件路径的参数
				errCode = 1313;
				printf("ERROR(%d): -i 后缺少指定输入文件路径的参数！\n\n"
					"程序获得的参数列表是：\n", errCode);

				// 打印程序获得的参数列表
				int j = 1;
				while (j < paraCount)
				{
					printf("%s ", paras[j++]);
				}
				putchar('\n');

				return errCode;
			}

			// 储存（输入）文件路径
			strcpy(encInfo.inFile, paras[i]);
		}
		else if (_stricmp(paras[i], "-o") == 0)
		{
			if (++i > (paraCount - 1))
			{
				// -o 后缺少指定输出文件路径的参数
				errCode = 1314;
				printf("ERROR(%d): -o 后缺少指定输出文件路径的参数！\n\n"
					"程序获得的参数列表是：\n", errCode);

				// 打印程序获得的参数列表
				int j = 1;
				while (j < paraCount)
				{
					printf("%s ", paras[j++]);
				}
				putchar('\n');

				return errCode;
			}

			
			// 储存（输出）文件路径
			strcpy(encInfo.outFile, paras[i]);
			

			if (++i > (paraCount - 1))
			{
				// 缺少指定“加密类型”的参数，该参数应该跟在输出文件路径后面
				errCode = 1315;
				printf("ERROR(%d): 参数列表个数不匹配！\n\n"
					"可能的原因是：\n"
					"缺少指定“加密类型”的参数，该参数应该跟在输出文件路径后面！\n\n"
					"正确的参数传递应该是:\n"
					"-i [input_file_path] -o [output_file_path] [encrypt_algorithm]\n\n"
					"但是程序获得的参数列表是：\n", errCode);
				// 打印程序获得的参数列表
				int j = 1;
				while (j < paraCount)
				{
					printf("%s ", paras[j++]);
				}
				putchar('\n');

				return errCode;
			}

			// 储存加密类型
			strcpy(encInfo.encAlgorithm, paras[i]);
		}
		else
		{
			// 检测到未知参数
			errCode = 1316;
			printf("ERROR(%d): <\"%s\">\n参数无效！\n\n"
				"程序获得的参数列表是：\n", errCode, paras[i]);

			// 打印程序获得的参数列表
			int j = 1;
			while (j < paraCount)
			{
				printf("%s ", paras[j++]);
			}
			putchar('\n');

			return errCode;
		}
	}

	return 0;
}

int encInfoCheck()
{
	errCode = 0;

	// 检查输入文件路径是否可使用
	switch (fPathCheck(encInfo.inFile))
	{
	case 0:
		// 未发生错误
		break;
	case -1:
		errCode = 1317;
		printf("ERROR(%d): <\"%p\">\n未找到正确的输入文件路径！\n", errCode, encInfo.inFile);
		return errCode;
	case -2:
		errCode = 1318;
		printf("ERROR(%d): <\"%s\">\n输入文件路径未指向任何实例！\n", errCode, encInfo.inFile);
		return errCode;
	case -3:
		errCode = 1319;
		printf("ERROR(%d): <\"%s\">\n无法对目标输入文件进行读写操作！\n", errCode, encInfo.inFile);
		return errCode;
	default:
		puts("ERROR(1000): 未知错误！\n");
		return 1000;
	}

	// 检查输出文件路径是否可使用
	switch (fPathCheck(encInfo.outFile))
	{
	case 0:
		// 未发生错误
		break;
	case -1:
		errCode = 1320;
		printf("ERROR(%d): <\"%p\">\n未找到正确的输出文件路径！\n", errCode, encInfo.outFile);
		return errCode;
	case -2:
		errCode = 1321;
		printf("ERROR(%d): <\"%s\">\n输出文件路径未指向任何实例！\n", errCode, encInfo.outFile);
		return errCode;
	case -3:
		errCode = 1322;
		printf("ERROR(%d): <\"%s\">\n无法对目标输出文件进行读写操作！\n", errCode, encInfo.outFile);
		return errCode;
	default:
		puts("ERROR(1000): 未知错误！\n");
		return 1000;
	}

	// 检查加密类型是否可使用
	switch (encAlgoCheck(encInfo.encAlgorithm))
	{
	case 0:
		// 未找到错误
		break;
	case -1:
		errCode = 1323;
		printf("ERROR(%d): <\"%p\">\n未找到正确的加密类型！\n", errCode, encInfo.encAlgorithm);
		return errCode;
	case -2:
		errCode = 1324;
		printf("ERROR(%d): <\"%s\">\n该加密类型暂不被支持！\n", errCode, encInfo.encAlgorithm);
		return errCode;
	default:
		puts("ERROR(1000): 未知错误！\n");
		return 1000;
	}

	return 0;
}

int fPathCheck(const char* fPath)
{
	if (strlen(fPath) == 0)
	{
		// fPath 指针为空
		return -1;
	}

	if (_access(fPath, F_OK))
	{
		// 文件不存在
		return -2;
	}
	else
	{
		if (_access(fPath, R_OK | W_OK))
		{
			// 文件不可读写
			return -3;
		}
	}

	return 0;
}

int encAlgoCheck(const char* encAlgo)
{
	if (strlen(encAlgo) == 0)
	{
		// encAlgo 指针为空
		return -1;
	}

	// 计算总共有多少个加密类型
	int countEncAlgorithm = sizeof(supportEncAlgorithm) / sizeof(supportEncAlgorithm[0]);

	for (int i = 0; i < countEncAlgorithm; i++)
	{
		// 找到匹配的加密类型，加密类型是支持的类型
		if (_stricmp(supportEncAlgorithm[i], encAlgo) == 0)
			return 0;
	}

	// 加密类型不是所支持类型
	return -2;
}

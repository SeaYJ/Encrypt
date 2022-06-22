#include "Encrypt.h"

int main(int argc, char* argv[])
{
	int ret;
	
	// �����б����
	ret = paraParsing(argc, argv);
	if (ret)
		return ret;

	// ���ܱ�Ҫ��Ϣ���
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
		// δ�ҵ���Ч����
		errCode = 1312;
		printf("ERROR(%d): δ�ҵ���Ч������\n", errCode);
		return errCode;
	}

	for (int i = 1; i < paraCount; i++)
	{
		if (_stricmp(paras[i], "-i") == 0)
		{
			if (++i > (paraCount - 1))
			{
				// -i ��ȱ��ָ�������ļ�·���Ĳ���
				errCode = 1313;
				printf("ERROR(%d): -i ��ȱ��ָ�������ļ�·���Ĳ�����\n\n"
					"�����õĲ����б��ǣ�\n", errCode);

				// ��ӡ�����õĲ����б�
				int j = 1;
				while (j < paraCount)
				{
					printf("%s ", paras[j++]);
				}
				putchar('\n');

				return errCode;
			}

			// ���棨���룩�ļ�·��
			strcpy(encInfo.inFile, paras[i]);
		}
		else if (_stricmp(paras[i], "-o") == 0)
		{
			if (++i > (paraCount - 1))
			{
				// -o ��ȱ��ָ������ļ�·���Ĳ���
				errCode = 1314;
				printf("ERROR(%d): -o ��ȱ��ָ������ļ�·���Ĳ�����\n\n"
					"�����õĲ����б��ǣ�\n", errCode);

				// ��ӡ�����õĲ����б�
				int j = 1;
				while (j < paraCount)
				{
					printf("%s ", paras[j++]);
				}
				putchar('\n');

				return errCode;
			}

			
			// ���棨������ļ�·��
			strcpy(encInfo.outFile, paras[i]);
			

			if (++i > (paraCount - 1))
			{
				// ȱ��ָ�����������͡��Ĳ������ò���Ӧ�ø�������ļ�·������
				errCode = 1315;
				printf("ERROR(%d): �����б������ƥ�䣡\n\n"
					"���ܵ�ԭ���ǣ�\n"
					"ȱ��ָ�����������͡��Ĳ������ò���Ӧ�ø�������ļ�·�����棡\n\n"
					"��ȷ�Ĳ�������Ӧ����:\n"
					"-i [input_file_path] -o [output_file_path] [encrypt_algorithm]\n\n"
					"���ǳ����õĲ����б��ǣ�\n", errCode);
				// ��ӡ�����õĲ����б�
				int j = 1;
				while (j < paraCount)
				{
					printf("%s ", paras[j++]);
				}
				putchar('\n');

				return errCode;
			}

			// �����������
			strcpy(encInfo.encAlgorithm, paras[i]);
		}
		else
		{
			// ��⵽δ֪����
			errCode = 1316;
			printf("ERROR(%d): <\"%s\">\n������Ч��\n\n"
				"�����õĲ����б��ǣ�\n", errCode, paras[i]);

			// ��ӡ�����õĲ����б�
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

	// ��������ļ�·���Ƿ��ʹ��
	switch (fPathCheck(encInfo.inFile))
	{
	case 0:
		// δ��������
		break;
	case -1:
		errCode = 1317;
		printf("ERROR(%d): <\"%p\">\nδ�ҵ���ȷ�������ļ�·����\n", errCode, encInfo.inFile);
		return errCode;
	case -2:
		errCode = 1318;
		printf("ERROR(%d): <\"%s\">\n�����ļ�·��δָ���κ�ʵ����\n", errCode, encInfo.inFile);
		return errCode;
	case -3:
		errCode = 1319;
		printf("ERROR(%d): <\"%s\">\n�޷���Ŀ�������ļ����ж�д������\n", errCode, encInfo.inFile);
		return errCode;
	default:
		puts("ERROR(1000): δ֪����\n");
		return 1000;
	}

	// �������ļ�·���Ƿ��ʹ��
	switch (fPathCheck(encInfo.outFile))
	{
	case 0:
		// δ��������
		break;
	case -1:
		errCode = 1320;
		printf("ERROR(%d): <\"%p\">\nδ�ҵ���ȷ������ļ�·����\n", errCode, encInfo.outFile);
		return errCode;
	case -2:
		errCode = 1321;
		printf("ERROR(%d): <\"%s\">\n����ļ�·��δָ���κ�ʵ����\n", errCode, encInfo.outFile);
		return errCode;
	case -3:
		errCode = 1322;
		printf("ERROR(%d): <\"%s\">\n�޷���Ŀ������ļ����ж�д������\n", errCode, encInfo.outFile);
		return errCode;
	default:
		puts("ERROR(1000): δ֪����\n");
		return 1000;
	}

	// �����������Ƿ��ʹ��
	switch (encAlgoCheck(encInfo.encAlgorithm))
	{
	case 0:
		// δ�ҵ�����
		break;
	case -1:
		errCode = 1323;
		printf("ERROR(%d): <\"%p\">\nδ�ҵ���ȷ�ļ������ͣ�\n", errCode, encInfo.encAlgorithm);
		return errCode;
	case -2:
		errCode = 1324;
		printf("ERROR(%d): <\"%s\">\n�ü��������ݲ���֧�֣�\n", errCode, encInfo.encAlgorithm);
		return errCode;
	default:
		puts("ERROR(1000): δ֪����\n");
		return 1000;
	}

	return 0;
}

int fPathCheck(const char* fPath)
{
	if (strlen(fPath) == 0)
	{
		// fPath ָ��Ϊ��
		return -1;
	}

	if (_access(fPath, F_OK))
	{
		// �ļ�������
		return -2;
	}
	else
	{
		if (_access(fPath, R_OK | W_OK))
		{
			// �ļ����ɶ�д
			return -3;
		}
	}

	return 0;
}

int encAlgoCheck(const char* encAlgo)
{
	if (strlen(encAlgo) == 0)
	{
		// encAlgo ָ��Ϊ��
		return -1;
	}

	// �����ܹ��ж��ٸ���������
	int countEncAlgorithm = sizeof(supportEncAlgorithm) / sizeof(supportEncAlgorithm[0]);

	for (int i = 0; i < countEncAlgorithm; i++)
	{
		// �ҵ�ƥ��ļ������ͣ�����������֧�ֵ�����
		if (_stricmp(supportEncAlgorithm[i], encAlgo) == 0)
			return 0;
	}

	// �������Ͳ�����֧������
	return -2;
}

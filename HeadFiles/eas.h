#ifndef _EAS_H
#define _EAS_H

/* Ϊ�˷�ֹ�ظ������׼���ļ���������C���Ա�׼��ר��ͷ�ļ��� */
#include "CStandardLibrary.h"

/* EAS �����㷨���� */
int easEncrypt(char *resPath, char *tarPath);

/* EAS �����㷨��������Ȼ�����㷨�����ͼ����㷨�������㷨һ�£���
����Ϊ�����ӳ�����߼��Ժ�����ܹ���
���Ա����˺������� */
int easDncrypt(char *resPath, char *tarPath);

#endif
#ifndef _ENCRYPT_H
#define _ENCRYPT_H

/* 为了防止重复编译标准库文件，这里存放C语言标准库专用头文件。 */
#include "CStandardLibrary.h" 

/* 这里写的是版本信息， 需要修改就在这里修改就行了！ */
struct verInfo 
{
	char *version;
	char *author;
	char *officalPage;
	char *statement;
	int astrisksNum; /* 版本信息框上层 * 号的个数 */
} versionInfo = {
	"2021.11.18.1",									/* 版本号 */
	"SeaYJ",										/* 作者 */
	"暂无",											/* 官网 */
	"原作者(SeaYJ)保留所有权力和最终解释权。",		/* 陈述 */
	49
};

/* 用于存储加密文件所需要的具体信息*/
struct EncInfo 
{
	char *inputFilePath; /* 源文件路径 */
	char *outputFilePath; /* 新文件路径 */
	char *encryptMethod; /* 加密方式 */
} encryptInfo = {NULL, NULL, NULL};


/* 用于存储源文件的具体信息
nameSuffix	-	文件后缀名
docName		-	文件名
fileEnv		-	文件所在路径
fileName	-	文件全称
*/
struct InputFilePathSplit
{
	char nameSuffix[_MAX_EXT]; // 包括后缀前面的小数点
	char docName[_MAX_FNAME];
	char fileEnv[_MAX_DIR];
	char fileName[_MAX_FNAME + _MAX_EXT];
} resFileInfo;

/* 对主程序传递的参数进行处理，
把需求的参数信息存储在 struct EncInfo EncryptInfo 中！
注意：
这里是绝对处理，后面的函数只需要进行拿信息处理即可！
也就是这里必须保证文件加密所需信息都完整！（不对是否可用进行检查，有就行！）*/
int parameterHandling(int argc, char *argv[]); 

/* 此函数将被 parameterHandling 函数调用，
用于对加密所需信息进行全面检查，
但不会对信息是否可用进行检查！ 
如果有问题会尝试进行修正，
对于修正不了的错误将会以整型返回值的形式告知该类错误的个数！*/
int infoCheck();

int inputFilePathDeal();

/* [参数处理函数 - 路径检查和修正函数]
将不规则的参数路径进行修正！ */
char* pathCheckFunction(char *res_path);
struct pathDealFunction
{
	char* (*pathCheck)(char *res_path);	/* 文件路径检查 */
} pathDeal = { pathCheckFunction };

int encryptionMethodSelection(char *inputFilePath, char *outputFilePath, char *encryptMethod);

#endif
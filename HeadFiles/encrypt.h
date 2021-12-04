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

/* 加密/解密方法
例如：
EAS 为简单加密变量，
那么 DEAS 就为对应的解密变量。
*/
enum EncMethod 
{
	EAS = 0,
	DEAS,

	PEAS,
	DPEAS,

	DES,
	DDES
};

/* 代表当前执行的状态
true	-	解密
false	-	加密
*/
bool EncOrDec = false;

#define _MAX_FILE_PATH_LENGTH_ 300
#define _MAX_PASSWORD_LENGTH_ 16
/* 用于存储加密文件所需要的具体信息*/
struct EncInfo 
{
	char inputFilePath[_MAX_FILE_PATH_LENGTH_]; /* 源文件路径 */
	char outputFilePath[_MAX_FILE_PATH_LENGTH_]; /* 新文件路径 */
	enum EncMethod encryptMethod; /* 加密方式 */
	char password[_MAX_PASSWORD_LENGTH_]; /* 加密密码，可为NULL */
} encryptInfo = {{0}, {0}, EAS, "123456"};

/* 用于存储源文件的具体信息
nameSuffix	-	文件后缀名
docName		-	文件名
fileEnv		-	文件所在路径
fileName	-	文件全称
*/
struct InputFilePathSplit
{
	char suffixName[_MAX_EXT]; // 包括后缀前面的小数点
	char docName[_MAX_FNAME];
	char fileEnv[_MAX_DIR];
	char fileName[_MAX_FNAME + _MAX_EXT];
} resFileInfo = {{0}, {0}, {0}, {0}};

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

int inputFilePathDeal(char *inputPath);

/* [参数处理函数 - 路径检查和修正函数]
将不规则的参数路径进行修正！ */
char* pathPolishFunction(char *res_path);
struct pathDealFunction
{
	char* (*pathPolish)(char *res_path);	/* 文件路径检查 */
} pathDeal = { pathPolishFunction };

int encrypt(char *inputFilePath, char *outputFilePath, enum EncMethod encWay);

/* 用来存储程序运行时间的结构体变量
用于在用户未指定输出路径时，自动生产一个输出路径。
生成的输出的路径文件名后面添加 -ENCRYPT_XXXX-XX-XX-XX-XX-XX 以防止文件加密后覆盖同名文件！
但是对于用户指定好了输出路径后，不添加后缀！
*/
struct TimeNow
{
	char year[5];
	char month[3];
	char day[3];
	char hour[3];
	char minute[3];
	char second[3];
} timer;
int timeGet();

#endif
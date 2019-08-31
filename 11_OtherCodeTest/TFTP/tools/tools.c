#include <tools.h>
#include <tftpType.h>
#include <string.h>
#include <stdlib.h>
#include <tftpLog.h>

/*
 * FunctionName:
 *     uitoa
 * Description:
 *     INT32整数value转十进制字符串str
 *     并返回字符串首地址，如1235，转成"1235"
 * Notes:
 *     
 */
EXTERN CHAR * uitoa(UINT32 value, CHAR * str)
{
	INT32 high = value;
	INT32 low = 0;
	INT32 i = 0, j = 0, temp = 0;

	if(!value){
		str[0] = '0';
		return str;
	}
	
	/* 余数对应的ASCII码依次存放在数组中 */
	while(high){
		low = high % 10;
		high = high / 10;
		str[i++] = low + '0';
	}
	--i;
	/* 反转，高低位调换字符串顺序 */
	while(i > j){
		temp = str[i];
		str[i--] = str[j];
		str[j++] = temp;
	}
	return str;
}

/*
 * FunctionName:
 *     atoui
 * Description:
 *    十进制的字符串表示形式，转换为十进制数值
 *    只支持无符号UINT32 
 * Notes:
 *     
 */
EXTERN UINT32 atoui(const CHAR * str)
{
	const CHAR *s = str;
	UINT32 value = 0;
	while(*s){
		if(*s < '0' || *s > '9'){
			return -1;
		}
		value = (value << 3) + (value << 1);	/* 即value = value x 10 */
		value += (*s - '0');
		s++;
	}
	return value;
}

/*
 * FunctionName:
 *     uitoxa
 * Description:
 *    INT32整数value转十六进制字符串str
 *    并返回字符串首地址，如1235，转成"0X000004D3"
 * Notes:
 *     
 */
EXTERN CHAR * uitoxa(UINT32 value, CHAR * str)
{
	CHAR * s = str;
	CHAR base[] = "0123456789ABCDEF";
	INT32 high = value, low = 0;
	/* 32bit十六进制，0xFFFFFFFF，占10Byte， 倒序填充index从9开始 */
	INT32 i = 9; 

	while(high){
		low = high % 16;
		high = high / 16;
		s[i--] = base[low];
	}
	while(i > 1){
		s[i--] = '0';
	}
	s[1] = 'X';
	s[0] = '0';
	
	return str;
}

/*
 * FunctionName:
 *     clear_more_space
 * Description:
 *    清除字符串str中多余的空格，两个单词之间只有一个空格
 *    字符串缓冲器开始和结束不能有空格
 * Notes:
 *     
 */
EXTERN CHAR * clear_more_space(CHAR * str) 
{
	INT32 i = 0;
	INT32 j = 0;
	CHAR * target = NULL;
	INT32 len = 0;
	
	if (NULL == str) {
		return NULL;
	}
	
	len = strlen(str);
	target = malloc(len);
	memset(target, 0, len);

	while ((i < len) && (str[i] == 0x20)) {
		i++;
	}
	
	while(i < len) {
		if ((str[i] == 0x20) && (str[i+1] == 0x20)) {
			i++;
		}
		else {
			target[j++] = str[i++];
		}
	}

	memcpy(str, target, len);
	free(target);

	return str;
}

/*
 * FunctionName:
 *     str_ipv4_check
 * Description:
 *     检查IPv4地址格式是否合法:xx.xx.xx.xx
 * Notes:
 *     
 */
EXTERN CONST CHAR * str_ipv4_check(CONST CHAR * str)
{
	CHAR * savePtr = NULL;
	CHAR * strTemp = NULL;
	CHAR * strPtr = NULL;
	INT32 strLen = 0;
	INT32 num = 0;
	INT32 index = 1;
	
	if (NULL == str) {
		return NULL;
	}
	
	strLen = strlen(str);
	if (strLen > 15) {
		return NULL;		/* ipv4最大地址255.255.255.255共15字节 */
	}
	
	strTemp = malloc(strLen + 1);
	memset(strTemp, 0, strLen + 1);
	memcpy(strTemp, str, strLen);
	
	while(strTemp || (savePtr && *savePtr)){
		if (index > 4) {
			free(strTemp);
			return NULL;
		}
		else {
			strPtr = strtok_r(strTemp, ".", &savePtr);
		}

		num = atoui(strPtr);
		if (num < 0 || num > 255) {
			free(strTemp);
			return NULL;
		}
		strTemp = NULL;
		index++;
	}

	free(strTemp);
	return str;
}

/*
 * FunctionName:
 *     str_hex_check
 * Description:
 *     检查十六进制数是否合法
 * Notes:
 *     
 */
EXTERN CONST CHAR * str_hex_check(CONST CHAR * str)
{
	return str;
}
/*
 * FunctionName:
 *     str_uint32_check
 * Description:
 *     检查无符号整数是否合法
 * Notes:
 *     
 */
EXTERN CONST CHAR * str_uint32_check(CONST CHAR * str)
{
	return str;
}
/*
 * FunctionName:
 *     str_int32_check
 * Description:
 *     检查有符号整数是否合法
 * Notes:
 *     
 */
EXTERN CONST CHAR * str_int32_check(CONST CHAR * str)
{
	return str;
}

/*
 * FunctionName:
 *     str_cmdstr_check
 * Description:
 *    检查字符串是否合法
 * Notes:
 *     
 */
EXTERN CONST CHAR * str_cmdstr_check(CONST CHAR * str)
{
	return str;
}

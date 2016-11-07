#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 65536
#define PAUSE printf("Press Enter key to continue..."); fgetc(stdin);
int main(int argc, char *argv[])
{
	FILE *fp,*copy;
	char *buf;
	size_t ret;

	if(argc!=2)
	{
		printf("直接把檔案拖曳到此程式。\n指令用法：此程式檔名稱 要複製的檔案名稱\n");
		PAUSE
		printf("system(\"pause\") for linux!\n");
	}
	else
	{
		printf("複製中...");
		fp=fopen(argc[argv-1],"rb");
		copy=fopen("./copy","wb");
		buf = (char *)malloc(BUFFER_SIZE); //動態配置記憶體給Array
		ret = fread(buf, 1, BUFFER_SIZE, fp); // fread回傳讀取的byte數
		while(ret > 0)
		{
		fwrite(buf, 1, ret, copy);
		printf("loop \n");
		ret = fread(buf, 1, BUFFER_SIZE, fp);
		}
		free(buf);
		fclose(fp);
		fclose(copy);
	}
	return 0;
}
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
		printf("�������ɮש즲�즹�{���C\n���O�Ϊk�G���{���ɦW�� �n�ƻs���ɮצW��\n");
		PAUSE
		printf("system(\"pause\") for linux!\n");
	}
	else
	{
		printf("�ƻs��...");
		fp=fopen(argc[argv-1],"rb");
		copy=fopen("./copy","wb");
		buf = (char *)malloc(BUFFER_SIZE); //�ʺA�t�m�O���鵹Array
		ret = fread(buf, 1, BUFFER_SIZE, fp); // fread�^��Ū����byte��
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
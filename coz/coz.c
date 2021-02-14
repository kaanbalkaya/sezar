#include <stdio.h>
#include "sakla.h"
#define KUCUK_D "avatar.bmp"
#define BIR "son.bmp"

FILE 	*kfp,
	*bir;  //birleþimden oluþan dosya	    
long bir_size;

int dosya_ac();
void dosya_oku_yaz();


int main(int argc,char *argv[])
{
	int hata;
	hata=dosya_ac();
	if(hata)
	{
		printf("\nHata!!!");
		return -1;
	}
	
	dosya_oku_yaz();
	fclose(kfp);
	fclose(bir);
	
}

int dosya_ac()
{	
	
	kfp=fopen(KUCUK_D,"wb");
	if(kfp==NULL)
	{
		printf("acilamadi");
		return -1;
	}
			
	bir=fopen(BIR,"rb");
	if(bir==NULL)
	{
		printf("acilamadi");
		return -1;
	}	
		
	rewind(bir);	     //dosya baþýna dön
	return 0;
}



void dosya_oku_yaz()
{	
	struct VERI datak, 
		    datab,
		    bit,z; 
		
	int j;
	long basla, 
	     bitir,
	     i;
	FILE *vtb;
	vtb=fopen("vtb","r");
	fscanf(vtb,"%d",&basla);
	fscanf(vtb,"%d",&bitir);
	fclose(vtb);
	printf("%d %d\n",basla,bitir);
	z.data=0x1;
	fseek(bir,basla,SEEK_SET);
	while(1)
	{
		datak.data=0;
		for(j=0;j<(sizeof(struct VERI)*8);++j)
		{
			bit.data=0;
			fread(&datab,sizeof(struct VERI),1,bir);
			bit.data=datab.data&z.data;
			bit.data=bit.data<<j;
			datak.data=datak.data|bit.data;
			
		}
		fwrite(&datak,sizeof(struct VERI),1,kfp);
		if(ftell(bir)==bitir)
              break;
	}
}




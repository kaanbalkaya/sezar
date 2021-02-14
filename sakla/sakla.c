#include <stdio.h>
#include <stdlib.h>
#include "sakla.h"
#define KUCUK_D "avatar.bmp"
#define BUYUK_D "impala.bmp"

FILE *kfp,  //küçük dosya
     *bfp,  //büyük dosya
     *bir;  //birleþimden oluþan dosya	
   
long kfp_size, bfp_size;

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
	fclose(bfp);
	fclose(kfp);
	fclose(bir);
}

int dosya_ac()
{	
	
	kfp=fopen(KUCUK_D,"rb");
	if(kfp==NULL)
	{
		printf("acilamadi");
		return -1;
	}
	if(fseek(kfp,0L,SEEK_END)){			//dosya sonuna git
		printf("dosya sonu seek hata");
		return -2;
	}
	kfp_size=ftell(kfp);  //dosya boyutu
	rewind(kfp);	     //dosya baþýna dön	
	
	
	
	
	bfp=fopen(BUYUK_D,"rb");
	if(bfp==NULL)
	{
		printf("acilamadi");
		return -1;
	}
	if(fseek(bfp,0L,SEEK_END)){			//dosya sonuna git
		printf("dosya sonu seek hata");
		return -2;
	}
	bfp_size=ftell(bfp);  //dosya boyutu
	rewind(bfp);	     //dosya baþýna dön

	bir=fopen("son.bmp","wb");
	if(bir==NULL)
	{
		printf("acilamadi");
		return -1;
	}	
	
	return 0;
}



void dosya_oku_yaz()
{
	struct VERI datak, 
	            datab;
	long i,oran,ilk,son;
	char z,k;
	char bit;
	FILE *vtb;
	
	oran=bfp_size-kfp_size*(sizeof(struct VERI)*8);
	
	k=0x0;
	for(i=0;i<(sizeof(struct VERI)*8);++i)              //k=0xfffffffe
	{
		++k;
		k=k<<1;
	}
	printf("bit sayisi=%d\n",kfp_size*(sizeof(struct VERI)*8));
	printf("oran      =%d\n",oran);
	
	for(i=0;i<oran;++i)
	{
		
		fread(&datab,sizeof(struct VERI),1,bfp);
		fwrite(&datab,sizeof(struct VERI),1,bir);
	}
	
	
	ilk=ftell(bir);
	
	
	while(!feof(kfp))
	{	
		z=0x1;
		fread(&datak,sizeof(struct VERI),1,kfp);
		
		for(i=0;i<(sizeof(struct VERI)*8);++i)
		{
			fread(&datab,sizeof(struct VERI),1,bfp);
			bit=datak.data&z;
			bit=bit>>i;
			if(bit==0){
				datab.data=datab.data&k;//(~bit);   				
			}
			else{
				datab.data=datab.data|bit;				    
			}
			
			fwrite(&datab,sizeof(struct VERI),1,bir);
			z=z<<1;
		}
		
	}
	son=ftell(bir);
	while(!feof(bfp))
	{
	
		fread(&datab,sizeof(struct VERI),1,bfp);
		fwrite(&datab,sizeof(struct VERI),1,bir);
	}
	printf("bfp       =%d\n",ftell(bfp));
	printf("bfp_size  =%d\n",bfp_size);
	printf("bir       =%d\n",ftell(bir));
	vtb=fopen("vtb","w");	
	fprintf(vtb,"%d\n",ilk);
	fprintf(vtb,"%d\n",son);
	fclose(vtb);
}



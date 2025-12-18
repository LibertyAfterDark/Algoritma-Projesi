#include <stdio.h>
#include <stdlib.h>

struct Ogrenci {
    int dogruSayisi;
    int yanlisSayisi;
    int bosSayisi;
    int net;
};

int main(int argc, char *argv[])
{
    FILE *ogrenciDosya, *anahtarDosya;
    char ogrCevap, dogruCevap;
    struct Ogrenci ogr;

    ogr.dogruSayisi = 0;
    ogr.yanlisSayisi = 0;
    ogr.bosSayisi = 0;
    ogr.net = 0;

    if (argc != 3)
    {
        printf("Kullanim: %s ogrenci.txt anahtar.txt\n", argv[0]);
        return 1;
    }

    ogrenciDosya = fopen(argv[1], "r");
    anahtarDosya = fopen(argv[2], "r");

    if (ogrenciDosya == NULL || anahtarDosya == NULL)
    {
        perror("Dosya acilamadi");
        return 1;
    }

    while (fscanf(ogrenciDosya, " %c", &ogrCevap) != EOF &&
           fscanf(anahtarDosya, " %c", &dogruCevap) != EOF)
    {
        if (ogrCevap == '-')
        {
            ogr.bosSayisi++;
        }
        else if (ogrCevap == dogruCevap)
        {
            ogr.dogruSayisi++;
        }
        else
        {
            ogr.yanlisSayisi++;
        }
    }

    fclose(ogrenciDosya);
    fclose(anahtarDosya);

    ogr.net = ogr.dogruSayisi - (ogr.yanlisSayisi / 4);

    printf("%s nolu ogrencinin\n", argv[1]);
    printf("Dogru sayisi: %d\n", ogr.dogruSayisi);
    printf("Yanlis sayisi: %d\n", ogr.yanlisSayisi);
    printf("Bos sayisi    : %d\n", ogr.bosSayisi);
    printf("Net           : %d\n", ogr.net);

    return 0;
}

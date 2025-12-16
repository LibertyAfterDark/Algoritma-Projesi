#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    FILE *ogrenciDosya, *anahtarDosya;
    char ogrCevap, dogruCevap;
    int dogru = 0, yanlis = 0, bos = 0;

    if (argc != 3) {
        printf("Dogru kullanim sekli \"./main.exe [ogrencino].txt anahtar.txt\" seklindedir.\n");
        return 1;
    }

    ogrenciDosya = fopen(argv[1], "r");
    anahtarDosya = fopen(argv[2], "r");

    if (ogrenciDosya == NULL || anahtarDosya == NULL) {
        printf("Dosya acilamadi.\n");
        return 1;
    }

    while (fscanf(ogrenciDosya, " %c", &ogrCevap) != EOF && fscanf(anahtarDosya, " %c", &dogruCevap) != EOF) {

        if (ogrCevap == '-')
            bos++;
        else if (ogrCevap == dogruCevap)
            dogru++;
        else
            yanlis++;
    }

    fclose(ogrenciDosya);
    fclose(anahtarDosya);

    char ogrNo[20];
    strcpy(ogrNo, argv[1]);
    char* nokta = strrchr(ogrNo, '.'); // sondan '.' ara
    if (nokta != NULL) {
        *nokta = '\0'; // '.' karakterini string sonu yap
    }

    int net = dogru - (yanlis / 4);

    printf("%s nolu ogrencinin\n", ogrNo);
    printf("Dogru sayisi: %d\n", dogru);
    printf("Yanlis sayisi: %d\n", yanlis);
    printf("Bos sayisi: %d\n", bos);
    printf("Net: %d\n", net);

    return 0;
}

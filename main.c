#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

// Öğrencinin sınav istatistiklerini tutmak için bir yapı (struct) tanımlıyoruz.
struct Ogrenci {
    int dogruSayisi;
    int yanlisSayisi;
    int bosSayisi;
    float net; 
};

int main(int argc, char *argv[])
{
    // Dosya işaretçileri (pointer) tanımlanıyor.
    FILE *ogrenciDosya, *anahtarDosya;
    
    // Okunan karakterleri tutmak için değişkenler.
    char ogrCevap, dogruCevap;
    
    // Öğrenci yapısından bir değişken oluşturuluyor.
    struct Ogrenci ogr;
    
    // Dosya adı işlemleri için pointerlar.
    char *dosyaAdi; 
    char *uzanti;

    // Sayaçlar ve net değeri başlangıçta sıfırlanıyor.
    ogr.dogruSayisi = 0;
    ogr.yanlisSayisi = 0;
    ogr.bosSayisi = 0;
    ogr.net = 0;

    // Komut satırı argümanlarının kontrolü.
    // Beklenen: programAdi ogrenci.txt anahtar.txt (Toplam 3 argüman)
    if (argc != 3)
    {
        printf("Kullanim: %s ogrenci.txt anahtar.txt\n", argv[0]);
        return 1; // Hata kodu ile çıkış.
    }

    // Dosyaları "read" (okuma) modunda açıyoruz.
    // argv[1]: öğrenci cevapları, argv[2]: cevap anahtarı.
    ogrenciDosya = fopen(argv[1], "r");
    anahtarDosya = fopen(argv[2], "r");

    // Dosyaların başarıyla açılıp açılmadığını kontrol ediyoruz.
    if (ogrenciDosya == NULL || anahtarDosya == NULL)
    {
        perror("Dosya acilamadi"); // Hata mesajını ekrana basar.
        return 1;
    }

    // Her iki dosyadan da aynı anda birer karakter (cevap) okuyoruz.
    // Dosyalardan biri bitene kadar (EOF - End Of File) döngü devam eder.
    while (fscanf(ogrenciDosya, " %c", &ogrCevap) != EOF &&
           fscanf(anahtarDosya, " %c", &dogruCevap) != EOF)
    {
        // '-' karakteri öğrencinin soruyu boş bıraktığını temsil eder.
        if (ogrCevap == '-')
        {
            ogr.bosSayisi++;
        }
        // Öğrenci cevabı ile anahtar eşleşiyorsa doğrudur.
        else if (ogrCevap == dogruCevap)
        {
            ogr.dogruSayisi++;
        }
        // Eşleşmiyorsa ve boş değilse yanlıştır.
        else
        {
            ogr.yanlisSayisi++;
        }
    }

    // İşimiz bitince dosyaları kapatıyoruz (Kaynak yönetimi için önemli).
    fclose(ogrenciDosya);
    fclose(anahtarDosya);

   
    // Net hesabı: Doğru Sayısı - (Yanlış Sayısı / 4).
    // (float) dönüşümü (casting) yapmazsak tamsayı bölmesi olur ve küsurat kaybolur.
    ogr.net = ogr.dogruSayisi - ((float)ogr.yanlisSayisi / 4);


    // --- Dosya Adından Uzantıyı Kaldırma İşlemi ---
    dosyaAdi = argv[1]; // Örn: "12345.txt"
    uzanti = strrchr(dosyaAdi, '.'); // String içinde son '.' karakterini bulur.

    if (uzanti != NULL)
    {
        *uzanti = '\0'; // Noktanın olduğu yere string sonlandırıcı (null terminator) koyar.
                        // Böylece "12345.txt" -> "12345" olur.
    }
    // ----------------------------------------------

    // Sonuçların ekrana yazdırılması.
    printf("%s nolu ogrencinin\n", dosyaAdi); 
    printf("Dogru sayisi: %d\n", ogr.dogruSayisi);
    printf("Yanlis sayisi: %d\n", ogr.yanlisSayisi);
    printf("Bos sayisi : %d\n", ogr.bosSayisi);
    
    // %.2f: Virgülden sonra sadece 2 basamak göster.
    printf("Net : %.2f\n", ogr.net); 

    return 0; // Başarılı çıkış.
}

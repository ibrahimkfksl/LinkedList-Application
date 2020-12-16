# LinkedList-Application


		LINKED LIST APPLICATION README

   -Proje Hakkında

– Bu proje temelinde bağlı listede şehir bilgisi tutma projesidir. Dosyadan okunan şehir bilgileri ve bu şehirlerin komşu illeri iki ayrı bağlı listede tutulur. Kullanıcı girişi bulunan projede kullanıcı listeden şehir veya komşu silebilir veya ekleyebilir, isme göre veya bazı koşullara göre şehir aramasında bulunabilir. Son olarak yapılan tüm işlemler bağlı listenin son haline kaydedilir ve çıktı olarak çıktı dosyasının içinde kullanıcıya sunulur.

   -Proje Nasıl Çalışır

Projeyi C programlama dili destekli bir IDE de çalıştırınız.
Projeyi başlatınız.
Karşınızda bir menü çıkacak:
Eğer 1 seçeneğini seçerseniz sehrin adı,sehrin plakasi ve bolge kodu girmeniz istenecek. Bunları girdiğinizde bu bilgilere ait bir şehrin olup olmadığı kontrol edilecek. Eğer varsa ana menüye donulecek. Böyle bir şehir daha önce yoksa yeni eklediğiniz şehrin komşularını eklemeniz istenecektir.
Sonta bu şehir bağıl listeyde yerini almış olacaktır. Ana menüye dönülecektir.

Eğer 2 seçeneğini seçerseniz ekrana 2 seçenekli bir menü çıkacaktır. 1'i seçerseniz size aramak istediğiniz sehrin adını soracak. Aramak istedğiniz sehrin adını girince bu şehri bağıl listeden arayacaktır. Eğer yoksa size bunu bildirecek ve eklemek isteyip istemediğinizi soracaktır.
Eğer eklemek isterseniz ana menüde seçim 1 i işaretlemeniz sonucunda geldiğiniz ekrana donüp yeni şehir ekleyececksiniz.Eğer sehir aramada secenek 2 yi secerseniz bu sefer sehir aramasını sehrin plaka koduna göre yaparsınız. Sonrası seçenek 1 deki gibi devam ediyor.

Eğer 3 seçeneğini seçerseniz 2 secenek önünüze geliyor.Sehir silme ve iki şehir arası komsuluk silme. Sehir silmeyi seçtiğinizde sehrin adınız size sorup sehri ve sehrin komsularından ,silinecek sehrin plakasını siliyor. Eğer iki sehir arasaı komsuluk silmeyi secerseniz size 2 adet plaka soruyor. Bu iki plakanın sehirlerinin komsulugundan diğer plaka numarasını siliyor. Yoksa uyarıyı ekrana yazdırıp ana menuye donuyor

Eğer 4 seçeneğini seçerseniz size bolge kodunu soruyor. Girdiğiniz bölge koduna o bölgede bulunan sehirleri ekrana ve dosyaya yazdirir.

Eğer 5 seçeneğini seçerseniz 3 secenek ekrana geliyor. Sadece minimum deger isteyen,sadece maximum deger isteyen ya da her ikisinide isteyen. Yaptıgınız secim ve girdiğiniz sayılara göre komsu sayısıları kontrol ediliyor . Sizin girdiğiniz aralıkta komsu sayısı olan sehirleri ekrana ve dosyaya yazdiriyor.

Eğer 6 seçeneğini seçerseniz min ve max komsu sayilarini ve komsu isimlerini giriyorsunuz. Girdiğiniz komsu sayisi araliği ve komsu isimlerine uygun olan sehirleri ekrana ve dosyaya yazdiriyor

Eğer 7 seçeneğini seçerseniz program sonlanir.

Eğer başka bir tuşu seçerseniz bir uyarı ekrani ile karşilaşirsiniz ve ana menu tekrar ekrana gelir

Tüm seçimlerinizin sonuçlarini cikti.txt dosyasında kayıt edecektir.
Program kapanırken sehirler bağıl listesinin son halini dosyaya yazar.

   -Oyun Nasıl Oynanır
1-Bilgisayar vs Bilgisayar
Bilgisayar kendi ile savasir. Kartlari iki tarafta rastgele atar. Her kart atisinda iki kartin arasindan hasar puani yuksek olan kart diger karti yener.
Her turda karsi oyunucunun kartini yenen oyuncu 5 puan kazanir. En cok puani kazanan oyunu kazanir.
2-Bilgisayar vs Kullanici
Bilgisayar rastgele kart atar.Kullanici ise atmak istedigi kartin uzerine gelerek karta tiklar. Her kart atisinda iki kartin arasindan hasar puani yuksek olan kart diger karti yener.
Her turda karsi oyunucunun kartini yenen oyuncu 5 puan kazanir. En cok puani kazanan oyunu kazanir.
Oyundan cikmak icin sag ust koseden carpi isaretine basabilirsiniz.
  


   -Projeyi Geliştirirken Kullandığımız Teknoloji

-Proje de C Programlama dili kullanılmıştır.
-CodeBlocks IDE platformu kullanıldı.

-Java da Kullanılan Classlar
 stdio.h
 stdlib.h
 string.h
 ctype.h

-C de Hazır Yazdığımız Fonksiyonlar
 int sehirEkle(struct sehir *);
 void sehirYazdir(struct sehir *);
 void komsuEkle(struct sehir *,int);
 void komsuYazdir(struct sehir *);
 struct sehir* sehirBulIsim(char [30]);
 struct sehir* sehirBulPlaka(int);
 void kullaniciSehirEkleme();
 int plakaNoBul(char [30]);
 void dosyaOku();
 void sehirAdiDuzenle(char[30]);
 void bolgeAdiDuzenle(char [3]);
 void bilgiSil();
 void sehirStructSil(struct sehir *);
 void komsuStructSil(struct sehir *,int);
 void komsulariSil(struct sehir *);
 void komsulukEkle();
 void temizle();
 void kullaniciKriterBonus();
 void komsuBilgileri(struct sehir *);
 void KullaniciBolgeAdi();
 void kullaniciKomsuSayisiKriteri();
 void kullaniciSehirArama();
 void calistir();
 void dosyayaYaz();
 void sehirleriDosyayaYaz(struct sehir *);
 void komsulariDosyayaYaz(struct sehir *);


   -Projeyi Geliştirenler
Abdullah Yaşar KISA
İbrahim KAFKASLI

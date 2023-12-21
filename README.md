# Simulated Annealing ile Minimum Tur Türkiye Haritası

## Proje Tanımı
Bu proje, C++ programlama dilinde Simulated Annealing algoritmasını kullanarak Türkiye haritasında minimum turu bulmayı amaçlamaktadır. Proje, şehirlerin koordinatları, öklid mesafesi hesaplamaları, rastgele tur oluşturma ve simulated annealing algoritmasını içeren temel fonksiyonları içermektedir.

## Kullanılan Teknolojiler ve Kütüphaneler
- C++11 veya daha yeni bir sürümü destekleyen bir derleyici
- `<iostream>`, `<vector>`, `<cmath>`, `<algorithm>`, `<random>`, `<fstreamm>` `<nlohmann/json.hpp>` gibi standart C++ kütüphaneleri `

## Proje Dosyaları
- `simulated_annealing_turkiye.cpp`: Ana program dosyası
- `cities_of_turkey.json`: Türkiye'de bulunan şehirlerin database dosyası

  ## Şehir Veritabanı (cities_of_turkey.json)
Bu proje, şehir verilerini içeren bir JSON dosyası olan `cities_of_turkey.json` kullanmaktadır. Bu dosya, her bir şehir için bir dizi özelliği içermektedir.

Dosyanın Formatı:
```json
{
  "cities": [
    {
      "id": 1,
      "name": "Adana",
      "latitude": 37.0000,
      "longitude": 35.3213,
      "population": 2183167,
      "region": "Akdeniz"
    },
    ///Diğer şehirler...
  ]
}
```

## Kullanım
Programı derlemek ve çalıştırmak için aşağıdaki adımları takip edebilirsiniz:
1. Proje dizininde bir terminal açın.
2. `g++ simulated_annealing_turkiye.cpp -o simulated_annealing_turkiye` komutu ile programı derleyin.
3. `./simulated_annealing_turkiye` komutu ile programı çalıştırın.

## Algoritma Açıklaması
- `distance`: İki şehir arasındaki Öklid mesafesini hesaplayan fonksiyon
- `calculateTourLength`: Bir turun toplam uzunluğunu hesaplayan fonksiyon
- `createRandomTour`: Rastgele tur oluşturan fonksiyon
- `readCitiesFromJson`: JSON dosyasındaki şehir verilerini okuyan fonksiyon
- `simulatedAnnealing`: Simulated Annealing algoritmasını gerçekleştiren fonksiyon

## Katkılar
Katkıda bulunmak istiyorsanız, lütfen yeni bir dal (branch) oluşturun ve değişikliklerinizi orada yapın. Daha sonra bir çekme isteği (pull request) göndererek değişiklikleri incelememizi sağlayabilirsiniz.


## İletişim
Proje ile ilgili herhangi bir sorunuz veya geri bildiriminiz varsa, lütfen bana [beslirum@gmail.com] üzerinden ulaşın.

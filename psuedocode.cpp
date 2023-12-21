

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

// Şehir koordinatlarını temsil eden yapı
struct City {
    int x, y;
};

// İki şehir arasındaki Öklid mesafesini hesaplayan fonksiyon
double distance(const City& a, const City& b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

// Bir turun toplam uzunluğunu hesaplayan fonksiyon
double calculateTourLength(const std::vector<City>& cities, const std::vector<int>& tour) {
    double totalDistance = 0.0;
    for (size_t i = 0; i < tour.size(); i++) {
        int currentCity = tour[i];
        int nextCity = tour[(i + 1) % tour.size()];
        totalDistance += distance(cities[currentCity], cities[nextCity]);
    }
    return totalDistance;
}

// Rastgele tur oluşturan fonksiyon
std::vector<int> createRandomTour(int numberOfCities) {
    std::vector<int> tour(numberOfCities);
    std::iota(tour.begin(), tour.end(), 0); // 0'dan başlayarak şehir indislerini doldur
    std::shuffle(tour.begin(), tour.end(), std::mt19937{std::random_device{}()});
    return tour;
}

Simdi Simulated Annealing algoritmasını içeren ana fonksiyonu ekleyelim:

// Simulated Annealing algoritmasını gerçekleştiren fonksiyon
std::vector<int> simulatedAnnealing(const std::vector<City>& cities, double startTemp, double endTemp, double coolingRate) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    auto currentTour = createRandomTour(cities.size());
    auto bestTour = currentTour;
    double currentTemp = startTemp;

    while (currentTemp > endTemp) {
        auto newTour = currentTour;

        // Rastgele iki şehir seç ve yerlerini değiştir
        int swapIndex1 = dis(gen) * newTour.size();
        int swapIndex2 = dis(gen) * newTour.size();
        std::swap(newTour[swapIndex1], newTour[swapIndex2]);

        // Enerjiyi hesapla ve karşılaştır
        double currentEnergy = calculateTourLength(cities, currentTour);
        double newEnergy = calculateTourLength(cities, newTour);

        // Kabul etme olasılığını hesapla
        if (newEnergy < currentEnergy || exp((currentEnergy - newEnergy) / currentTemp) > dis(gen)) {
            currentTour = newTour;

            if (newEnergy < calculateTourLength(cities, bestTour)) {
                bestTour = newTour;
            }
        }

        // Sıcaklığı azalt
        currentTemp *= 1 - coolingRate;
    }

    return bestTour;
}


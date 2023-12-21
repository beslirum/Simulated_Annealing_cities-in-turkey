#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <fstream>
#include <cities_of_turkey/json.hpp>

using json = cities_of_turkey::json;

// Şehir verilerini temsil eden yapı
struct City {
    int id;
    std::string name;
    double latitude, longitude;
};

// İki şehir arasındaki Öklid mesafesini hesaplayan fonksiyon
double distance(const City& a, const City& b) {
    return std::sqrt(std::pow(a.latitude - b.latitude, 2) + std::pow(a.longitude - b.longitude, 2));
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

// Rastgele bir tur oluşturan fonksiyon
std::vector<int> createRandomTour(int numberOfCities) {
    std::vector<int> tour(numberOfCities);
    std::iota(tour.begin(), tour.end(), 0);
    std::shuffle(tour.begin(), tour.end(), std::mt19937{std::random_device{}()});
    return tour;
}

// JSON dosyasındaki şehir verilerini okuyan fonksiyon
std::vector<City> readCitiesFromJson(const std::string& jsonFileName) {
    std::ifstream ifs(jsonFileName);
    if (!ifs.is_open()) {
        std::cerr << "Error opening file: " << jsonFileName << std::endl;
        exit(EXIT_FAILURE);
    }

    json jsonData;
    ifs >> jsonData;

    std::vector<City> cities;
    for (const auto& cityData : jsonData["cities"]) {
        cities.push_back({
            cityData["id"],
            cityData["name"],
            cityData["latitude"],
            cityData["longitude"]
        });
    }

    return cities;
}

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

int main() {
    // JSON dosyasından şehir verilerini oku
    std::vector<City> cities = readCitiesFromJson("cities_of_turkey.json");

    // Simulated Annealing ile minimum turu bul
    std::vector<int> optimalTour = simulatedAnnealing(cities, 1000.0, 0.01, 0.001);

    // Sonuçları ekrana yazdır
    std::cout << "Optimal Tour: ";
    for (int cityIndex : optimalTour) {
        std::cout << cities[cityIndex].name << " -> ";
    }
    std::cout << cities[optimalTour.front()].name << std::endl;

    return 0;
}


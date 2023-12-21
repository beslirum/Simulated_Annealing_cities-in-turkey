#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>
#include <format>
#include <cstdlib>
#include <xutility>


// Structure representing city data
// Şehir verilerini temsil eden yapı
struct City {
    int id;
    std::string name;
    double latitude, longitude;
};

// Function to calculate Euclidean distance between two cities
// İki şehir arasındaki Öklid mesafesini hesaplayan fonksiyon
double distance(const City& a, const City& b) {
    return std::sqrt(std::pow(a.latitude - b.latitude, 2) + std::pow(a.longitude - b.longitude, 2));
}

// Function to calculate the total length of a tour
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

// Function to create a random tour
// Rastgele bir tur oluşturan fonksiyon
std::vector<int> createRandomTour(int numberOfCities) {
    std::vector<int> tour(numberOfCities);
    std::iota(tour.begin(), tour.end(), 0);
    std::shuffle(tour.begin(), tour.end(), std::mt19937{std::random_device{}()});
    return tour;
}

// Function to read city data from a CSV file
// CSV dosyasındaki şehir verilerini okuyan fonksiyon
std::vector<City> readCitiesFromCSV(const std::string& csvFileName) {
    std::ifstream ifs(csvFileName);
    if (!ifs.is_open()) {
        std::cerr << "Error opening file: " << csvFileName << std::endl;
        exit(EXIT_FAILURE);
    }


    std::vector<City> cities;
    std::string line;
    std::getline(ifs, line); // İlk satırı atla (başlık satırı)

    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        std::string token;

        City city;
        std::getline(iss, token, ','); // Virgülle ayrılmış verileri oku
        city.id = std::stoi(token);

        std::getline(iss, city.name, ',');
        std::getline(iss, token, ',');
        city.latitude = std::stod(token);

        std::getline(iss, token);
        city.longitude = std::stod(token);

        cities.push_back(city);
    }

    return cities;
}

// Function implementing the Simulated Annealing algorithm
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

        // Randomly select two cities and swap their positions
        // Rastgele iki şehir seç ve yerlerini değiştir
        int swapIndex1 = dis(gen) * newTour.size();
        int swapIndex2 = dis(gen) * newTour.size();
        std::swap(newTour[swapIndex1], newTour[swapIndex2]);

        // Calculate energy and compare
        // Enerjiyi hesapla ve karşılaştır
        double currentEnergy = calculateTourLength(cities, currentTour);
        double newEnergy = calculateTourLength(cities, newTour);

        // Calculate acceptance probability
        // Kabul etme olasılığını hesapla
        if (newEnergy < currentEnergy || exp((currentEnergy - newEnergy) / currentTemp) > dis(gen)) {
            currentTour = newTour;

            if (newEnergy < calculateTourLength(cities, bestTour)) {
                bestTour = newTour;
            }
        }

        // Decrease the temperature
        // Sıcaklığı azalt
        currentTemp *= 1 - coolingRate;
    }

    return bestTour;
}

int main() {
    // Read city data from the CSV file
    // CSV dosyasından şehir verilerini oku
    std::vector<City> cities = readCitiesFromCSV("cities_of_turkey.csv");

    // Find the optimal tour using Simulated Annealing
    // Simulated Annealing ile minimum turu bul
    std::vector<int> optimalTour = simulatedAnnealing(cities, 1000.0, 0.01, 0.001);

    // Print the results to the console
    // Sonuçları ekrana yazdır
    std::cout << "Optimal Tour: ";
    for (int cityIndex : optimalTour) {
        std::cout << cities[cityIndex].name << " -> ";
    }
    std::cout << cities[optimalTour.front()].name << std::endl;

    return 0;
}

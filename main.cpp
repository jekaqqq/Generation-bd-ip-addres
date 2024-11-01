#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <fstream>

struct Project {
    int id;
    std::string host_ip;
    int donor_count;
    std::string start_date;
    std::string launch_date;
    std::string end_date;
    std::string donor_ips;
};

std::string generateRandomIP() {
    return std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256);
}

std::string generateRandomDate() {
    int year = 2021 + rand() % 3; // Дата в пределах последних нескольких лет
    int month = 1 + rand() % 12;
    int day = 1 + rand() % 28; // Чтобы избежать проблем с количеством дней в месяце
    std::ostringstream date;
    date << year << "-" << (month < 10 ? "0" : "") << month << "-" << (day < 10 ? "0" : "") << day;
    return date.str();
}

std::string generateDonorIPs(int count) {
    std::ostringstream ips;
    for (int i = 0; i < count; ++i) {
        ips << generateRandomIP();
        if (i < count - 1) ips << ", ";
    }
    return ips.str();
}

Project generateProject(int id) {
    Project project;
    project.id = id;
    project.host_ip = generateRandomIP();
    project.donor_count = 1 + rand() % 5; // Количество доноров от 1 до 5
    project.start_date = generateRandomDate();
    project.launch_date = generateRandomDate();
    project.end_date = generateRandomDate();
    project.donor_ips = generateDonorIPs(project.donor_count);
    return project;
}

void saveProjectsToCSV(const std::vector<Project>& projects, const std::string& filename) {
    std::ofstream file(filename);

    // Запись заголовков
    file << "ID проекта,IP хоста,Количество доноров,Дата открытия,Дата запуска,Дата окончания,IP доноров\n";

    // Запись данных каждого проекта
    for (const auto& project : projects) {
        file << project.id << ","
             << project.host_ip << ","
             << project.donor_count << ","
             << project.start_date << ","
             << project.launch_date << ","
             << project.end_date << ","
             << "\"" << project.donor_ips << "\"\n"; // Заключаем IP доноров в кавычки
    }

    file.close();
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    int num_projects = 5; // Количество проектов для генерации
    std::vector<Project> projects;

    for (int i = 0; i < num_projects; ++i) {
        projects.push_back(generateProject(i + 1));
    }

    // Сохранение в CSV файл
    saveProjectsToCSV(projects, "projects.csv");

    std::cout << "Данные сохранены в файл projects.csv\n";
    return 0;
}

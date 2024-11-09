#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDate>
#include <QRandomGenerator>
#include <QList>
#include <QDebug>

struct Project {
    int id;
    QString hostIp;
    int donorCount;
    QString startDate;
    QString launchDate;
    QString endDate;
    QString donorIps;
};

// Функция генерации случайного IP-адреса
QString generateRandomIP() {
    return QString("%1.%2.%3.%4")
            .arg(QRandomGenerator::global()->bounded(256))
            .arg(QRandomGenerator::global()->bounded(256))
            .arg(QRandomGenerator::global()->bounded(256))
            .arg(QRandomGenerator::global()->bounded(256));
}

// Функция генерации случайной даты в пределах заданного диапазона
QString generateRandomDate(QDate start = QDate(2021, 1, 1), QDate end = QDate(2023, 12, 31)) {
    int daysBetween = start.daysTo(end);
    QDate randomDate = start.addDays(QRandomGenerator::global()->bounded(daysBetween));
    return randomDate.toString("yyyy-MM-dd");
}

// Функция генерации списка IP доноров
QString generateDonorIPs(int count) {
    QStringList ips;
    for (int i = 0; i < count; ++i) {
        ips << generateRandomIP();
    }
    return ips.join(", ");
}

// Функция генерации данных проекта
Project generateProject(int id) {
    Project project;
    project.id = id;
    project.hostIp = generateRandomIP();
    project.donorCount = 1 + QRandomGenerator::global()->bounded(5);

    QDate startDate = QDate::fromString(generateRandomDate(), "yyyy-MM-dd");
    QDate launchDate = startDate.addDays(QRandomGenerator::global()->bounded(30));
    QDate endDate = launchDate.addDays(QRandomGenerator::global()->bounded(30));

    project.startDate = startDate.toString("yyyy-MM-dd");
    project.launchDate = launchDate.toString("yyyy-MM-dd");
    project.endDate = endDate.toString("yyyy-MM-dd");

    project.donorIps = generateDonorIPs(project.donorCount);
    return project;
}

// Функция сохранения проектов в CSV файл
void saveProjectsToCSV(const QList<Project>& projects, const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл для записи.";
        return;
    }

    QTextStream out(&file);
    // Запись заголовков
    out << "ID проекта,IP хоста,Количество доноров,Дата открытия,Дата запуска,Дата окончания,IP доноров\n";

    // Запись данных каждого проекта
    for (const auto& project : projects) {
        out << project.id << ","
            << project.hostIp << ","
            << project.donorCount << ","
            << project.startDate << ","
            << project.launchDate << ","
            << project.endDate << ","
            << "\"" << project.donorIps << "\"\n"; // Заключаем IP доноров в кавычки
    }

    file.close();
    qInfo() << "Данные сохранены в файл" << filename;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    int numProjects = 5; // Количество проектов для генерации
    QList<Project> projects;

    for (int i = 0; i < numProjects; ++i) {
        projects.append(generateProject(i + 1));
    }

    // Сохранение в CSV файл
    saveProjectsToCSV(projects, "projects.csv");

    return a.exec();
}

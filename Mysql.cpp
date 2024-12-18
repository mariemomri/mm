#include "mysql.h"
#include <iostream>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

using namespace std;

Mysql::Mysql(QQmlContext *contexte, session *sess)
{
    m_contexte = contexte;
    m_session = sess;
}

void Mysql::connectToDatabase()
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("localhost");
    m_db.setDatabaseName("robot");
    m_db.setUserName("root");
    m_db.setPassword("");

    if (m_db.open()) {
        cout << "Database connected" << endl;
    } else {
        cout << "Error: Connection not established" << endl;
        qDebug() << "Database error:" << m_db.lastError().text();
    }
}
void Mysql::checkAvailableDrivers() {
    // Your implementation here, e.g., listing available drivers
    qDebug() << "Available drivers:" << QSqlDatabase::drivers();

}


void Mysql::up()
{
    QSqlQuery requete;
    if (!requete.exec("UPDATE `admin_robotmob` SET `moteur gauche`=1, `moteur droite`=0")) {
        qDebug() << "Query failed (up):" << requete.lastError().text();
    }
}

void Mysql::down()
{
    QSqlQuery requete;
    if (!requete.exec("UPDATE `admin_robotmob` SET `moteur gauche`=2, `moteur droite`=0")) {
        qDebug() << "Query failed (down):" << requete.lastError().text();
    }
}

void Mysql::right()
{
    QSqlQuery requete;
    if (!requete.exec("UPDATE `admin_robotmob` SET `moteur droite`=1, `moteur gauche`=0")) {
        qDebug() << "Query failed (right):" << requete.lastError().text();
    }
}

void Mysql::left()
{
    QSqlQuery requete;
    if (!requete.exec("UPDATE `admin_robotmob` SET `moteur droite`=2, `moteur gauche`=0")) {
        qDebug() << "Query failed (left):" << requete.lastError().text();
    }
}

void Mysql::temperature()
{
    QSqlQuery requete;
    if (!requete.exec("SELECT `température`, `humidité` FROM `admin_robotmob` WHERE id=1")) {
        qDebug() << "Query failed (temperature):" << requete.lastError().text();
        return;
    }

    if (requete.next()) {
        double temp = requete.value(0).toDouble();
        double humd = requete.value(1).toDouble();
        cout << "Temperature: " << temp << ", Humidity: " << humd << endl;
    } else {
        qDebug() << "No data returned (temperature):" << requete.lastError().text();
    }
}

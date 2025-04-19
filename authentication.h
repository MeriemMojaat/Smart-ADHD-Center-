#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QDialog>
#include <QDialog>
#include <QString>
#include "employee.h"

namespace Ui {
class Authentication;
}

class Authentication : public QDialog
{
    Q_OBJECT

public:
    explicit Authentication(QWidget *parent = nullptr);
    ~Authentication();
    bool isAuthenticated() const;
    Employee* getLoggedInEmployee() const;

signals:
    void loggedIn(Employee*);

private slots:

    void on_on_loginButton_clicked_clicked();

private:
    Ui::Authentication *ui;
    Employee* findByIdAndPassword(int ID_EMPLOYEE, QString EPASSWORD);
    bool m_authenticated;
    Employee* m_loggedInEmployee;
};

#endif // AUTHENTICATION_H

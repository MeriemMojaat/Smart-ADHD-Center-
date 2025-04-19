#include "authentication.h"
#include "ui_authentication.h"
#include "mainwindow.h"

Authentication::Authentication(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Authentication),
  m_authenticated(false),
  m_loggedInEmployee(nullptr)
{
    ui->setupUi(this);
}

Authentication::~Authentication()
{
    delete ui;
}
//a boolean that keeps track of whether the user is authenticated or not
bool Authentication::isAuthenticated() const {
    return m_authenticated;
}
// a pointer to the currently logged-in employee
Employee* Authentication::getLoggedInEmployee() const {
    return m_loggedInEmployee;
}

//The isAuthenticated method returns the value of m_authenticated



Employee* Authentication::findByIdAndPassword(int ID_EMPLOYEE , QString EPASSWORD) {
    QSqlQuery query;
    query.prepare("SELECT * FROM employee WHERE ID_EMPLOYEE = :ID_EMPLOYEE AND EPASSWORD = :EPASSWORD");
    query.bindValue(":ID_EMPLOYEE", ID_EMPLOYEE);
    query.bindValue(":EPASSWORD", EPASSWORD);

    if (query.exec() && query.next()) {
        Employee* employee = new Employee;
        employee->setID_EMPLOYEE(query.value("ID_EMPLOYEE").toInt());
        employee->setEPASSWORD(query.value("EPASSWORD").toString());
        return employee;
    }

    return nullptr;
}




void Authentication::on_on_loginButton_clicked_clicked()
{
    int ID_EMPLOYEE = ui->idLineEdit->text().toInt();
    QString EPASSWORD = ui->passwordLineEdit->text();

    if (ID_EMPLOYEE == 0 || EPASSWORD.isEmpty()) {
        ui->messageLabel->setText("Please enter both ID and password");
        return;
    }

    // Look up the employee with the given ID and password
    Employee* loggedInEmployee = findByIdAndPassword(ID_EMPLOYEE,EPASSWORD);

    if (loggedInEmployee == nullptr) {
        ui->messageLabel->setText("Invalid ID or password");
        return;
    }
    // Authentication succeeded
    m_authenticated = true;
    m_loggedInEmployee = loggedInEmployee;

    MainWindow *mainWindow = new MainWindow();
        mainWindow->show();

    accept();
}

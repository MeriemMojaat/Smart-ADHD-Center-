#ifndef EXCEL_H
#define EXCEL_H
#include <QObject>
#include <QTableView>
#include <QStringList>
#include <QSqlDatabase>


class EEO_Field1
{
public:
    EEO_Field1(const int ic, const QString &sf, const QString &st):
            iCol(ic),sFieldName(sf),sFieldType(st){}

    int     iCol;
    QString sFieldName;
    QString sFieldType;
};

class EXCEL : public QObject
{
    Q_OBJECT
public:

   EXCEL(const QString &filepath, const QString &sheettitle,
                      QTableView *tableview):excelFilePath(filepath),
                      sheetName(sheettitle), tableView(tableview){}

    ~EXCEL() {QSqlDatabase::removeDatabase("projeqt");}

public:
    void setOutputFilePath(const QString &spath) {excelFilePath = spath;}// blassa bch nsavi fiha file excel
    void setOutputSheetTitle(const QString &ssheet) {sheetName = ssheet;}//nom fichier
    void setTableView(QTableView *tableview) {tableView = tableview;}//mnin bech ne5o les donnees (ml qt)

    void addField(const int iCol, const QString &fieldname, const QString &fieldtype)//ajouter colomnes
         {fieldList << new EEO_Field1(iCol, fieldname, fieldtype);}

    void removeAllFields() //delete tous les colomnes precedentes
         {while (!fieldList.isEmpty()) delete fieldList.takeFirst();}

    int export2Excel(); //exportation fichier

signals:
    void exportedRowCount(int row);

private:
    QString excelFilePath;
    QString sheetName;
    QTableView *tableView;
    QList<EEO_Field1 *> fieldList;
};

#endif // EXPORTEXCELOBJECT_H


#include "excel.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QVariant>

int EXCEL::export2Excel()
{
    if(fieldList.size() <= 0)
    {
        qDebug() << "ExportExcelObject::export2Excel failed: No fields defined.";
        return -1;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "Appointment"); //creation db
    if(!db.isValid())
    {
        qDebug() << "ExportExcelObject::export2Excel failed: QODBC not supported.";
        return -2;
    }

    QString dsn = QString("DRIVER={Microsoft Excel Driver (*.xls)};DSN='';FIRSTROWHASNAMES=1;READONLY=TRUE;CREATE_DB=\"%1\";DBQ=%2").
                  arg(excelFilePath).arg(excelFilePath);
    db.setDatabaseName(dsn);
    if(!db.open())
    {
        qDebug() << "ExportExcelObject::export2Excel failed: Create Excel file failed by DRIVER={Microsoft Excel Driver (*.xls)}.";
        QSqlDatabase::removeDatabase("Appointment");
        return -3;
    }

    QSqlQuery query(db);

    //drop the table if it's already exists
    QString s, sSql = QString("DROP TABLE [%1] (").arg(sheetName);
    query.exec(sSql);

    //create the table (sheet in Excel file)
    sSql = QString("CREATE TABLE [%1] (").arg(sheetName); //creation table
    for (int i = 0; i < fieldList.size(); i++)
    {
        s = QString("[%1] %2").arg(fieldList.at(i)->sFieldName).arg(fieldList.at(i)->sFieldType);
        sSql += s;
        if(i < fieldList.size() - 1) // creation colomuns
            sSql += " , "; // end of columns(fields) creation .
    }

    sSql += ")";
    query.prepare(sSql);

    if(!query.exec())
    {
        qDebug() << "ExportExcelObject::export2Excel failed: Create Excel sheet failed.";
        db.close();
        QSqlDatabase::removeDatabase("Appointment");
        return -4;
    }



    //add all rows
    sSql = QString("INSERT INTO [%1] (").arg(sheetName);
    for (int i = 0; i < fieldList.size(); i++)
    {
        sSql += fieldList.at(i)->sFieldName;
        if(i < fieldList.size() - 1)            //insertion dans le tableau les colomnes
            sSql += " , ";
    }
    sSql += ") VALUES (";
    for (int i = 0; i < fieldList.size(); i++)
    {
        sSql += QString(":data%1").arg(i);
        if(i < fieldList.size() - 1)
            sSql += " , ";
    }
    sSql += ")";                                // insert into tablname (id,nom,prenom) values (:id,:nom,:prenom ) ;

    qDebug() << sSql;

    int r, iRet = 0;
   // int prix=0;
    //int nb=0;
    for(r = 0 ; r < tableView->model()->rowCount() ; r++) // row = ligne
    {
        query.prepare(sSql);
        for (int c = 0; c < fieldList.size(); c++)
        {
            query.bindValue(QString(":data%1").arg(c), tableView->model()->data(tableView->model()->index(r, fieldList.at(c)->iCol)));
        }
       /* prix =  tableView->model()->data(tableView->model()->index(r, fieldList.at(9)->iCol)).toInt();
        nb =  tableView->model()->data(tableView->model()->index(r, fieldList.at(8)->iCol)).toInt();
        query.bindValue(QString(":data%1").arg(10), prix*nb);*/

        if(query.exec())
            iRet++; //n exportees

        if(r % 10 == 0)
            emit exportedRowCount(r); //9adech mn row saretlou l'execution
    }

    emit exportedRowCount(r);

    return iRet;
}

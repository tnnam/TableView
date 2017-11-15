#ifndef DATASERVICES_H
#define DATASERVICES_H

#include "person.h"
#include <QList>
#include <QObject>
#include <QString>
#include <QDebug>
#include <QtXml>
#include <QFile>
#include <QMessageBox>
#include <QXmlStreamAttribute>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

class DataServices
{
public:
    DataServices();
    void GhiFile(QList<person> list, QString);
    person parsePerson(QXmlStreamReader &xmlReader);
    QList<person> DocFile(QString);

    ~DataServices();
};

#endif // DATASERVICES_H

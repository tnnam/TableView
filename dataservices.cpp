#include "dataservices.h"

DataServices::DataServices()
{

}
//____WriteFile___________________________________________________
void DataServices::GhiFile(QList<person> list, QString s){
    QFile file(s);
    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox ms;
        ms.setText("File isn't opened!");
        ms.setStandardButtons(QMessageBox::Ok);
        return;
    }
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

        xmlWriter.writeStartElement("People");
        for(int i = 0; i < list.count(); i++){
            person a = list.at(i);
            xmlWriter.writeStartElement("Person");
                xmlWriter.writeAttribute("ID", QString::number(a.ID));
                xmlWriter.writeTextElement("Name", a.name);
                xmlWriter.writeTextElement("Age", QString::number(a.age));
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();

    xmlWriter.writeEndDocument();
}

//______ReadFile________________________________________________
QList<person> DataServices::DocFile(QString s){
    QList<person> list;
    QFile file(s);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox ms;
        ms.setText("File isn't opened!");
        ms.setStandardButtons(QMessageBox::Ok);
    }
    else{
        QXmlStreamReader xmlReader(&file);
        while(!xmlReader.atEnd() && !xmlReader.hasError()){
            QXmlStreamReader::TokenType token = xmlReader.readNext();
            if(token == QXmlStreamReader::StartDocument){
                continue;
            }
            if(token == QXmlStreamReader::StartElement){
                if(xmlReader.name() == "People"){
                    continue;
                }
                if(xmlReader.name() == "Person"){
                    person a = parsePerson(xmlReader);
                    list.append(a);
                }
            }
        }
    }
    file.close();
    return list;
}

person DataServices::parsePerson(QXmlStreamReader &xmlReader){
    if(xmlReader.tokenType() != QXmlStreamReader::StartElement
        && xmlReader.name() != "Person"){
        QMessageBox ms;
        ms.setText("Fail!");
        ms.setStandardButtons(QMessageBox::Ok);
     }
    else{
         person a;
         a.ID = xmlReader.attributes().value("ID").toString().toInt();
         xmlReader.readNext();
         while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement
                 && xmlReader.name() == "Person")){
             if(xmlReader.tokenType() == QXmlStreamReader::StartElement){
                 if(xmlReader.name() == "Name"){
                     xmlReader.readNext();
                     a.name = xmlReader.text().toString();
                 }
                 if(xmlReader.name() == "Age"){
                     xmlReader.readNext();
                     a.age = xmlReader.text().toString().toInt();
                 }
             }
             xmlReader.readNext();
         }
         return a;
    }
}

DataServices::~DataServices(){

}

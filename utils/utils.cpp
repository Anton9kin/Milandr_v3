#include "utils.h"

#include <QFile>
#include <QDebug>

Utils::Utils()
{

}

Utils::~Utils(){

}

QVector<Processor> Utils::getProcessor(QString filename){

    QVector<Processor> procList;

    //open resource file
    //and read it
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "File isn't exists";
    }
    //fill table view
    else {
        //create stream
        QTextStream in(&file);
        bool header = true;
        //read for end file
        while(!in.atEnd()){
            //line by line
            QString line = in.readLine();
            //add model to line
            QStringList headerList;
            QStringList proccessorData;

            //means that line split with ;
            for (QString item : line.split(";")){
                //create string list for table header
                if (header)
                    headerList << item;
                else
                    proccessorData << item;
            }
            //for header
            if (header){
                header = false;
            }else{
                Processor proc(proccessorData);
                procList.append(proc);
            }
        }
        file.close();
    }

    return procList;
}

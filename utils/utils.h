#ifndef UTILS_H
#define UTILS_H

#include <QJsonValue>
#include <QString>


class Utils
{
public:
    Utils();
    ~Utils();

    enum View_Orientation{
        View_Horizontal,     //horizontal    (text from west to east)
        View_Horizontal_Right,     //horizontal to right   (text from west to east)
        View_Vertical_NS,    //vertical      (text from north to south)
        View_Vertical_SN,    //vertical      (text from south to north)
        View_Diagonal_SWNE,  //diagonal      (text from south-west to north-east)
        View_Diagonal_NWSE,  //diagonal      (text from north-west to south-east)
    };

    static QJsonObject getProcessorFromJson(const QString &filename);
};

#endif // UTILS_H

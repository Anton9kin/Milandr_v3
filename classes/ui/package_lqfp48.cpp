#include "package_lqfp48.h"
#include <QPainter>

Package_LQFP48::Package_LQFP48(Processor *mcu)
    : Package ()
{
    packageName = "LQFP48";

    if (mcu != nullptr)
    {
        MCUName = mcu->Name();
    }

    int pinsOneSide = 48 / 4 + 1;
    stepPin = static_cast<int>(1.1*pinH);
    w = pinsOneSide*stepPin + stepPin;
    h = w;

    setPoints();
}

void Package_LQFP48::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Package::paint(painter, option, widget);

    setPoints();

    QFont font;
    font.setBold(false);
    painter->setFont(font);

    for(int i = 0 ; i < 48; i++){
        QPointF p = pinPosList.at(i);
        //left side
        if (i < 12){
            p.setY(p.y() + 15);
            p.setX(p.x() + pinW + 5);
        }
        //bottom side
        else if (i < 24){
            p.setY(p.y() - 5);
            p.setX(p.x() - 15);
        }
        //right side
        else if (i < 36){
            p.setY(p.y() + 15);
            p.setX(p.x() - 15 - 5);
        }
        //top side
        else if (i < 48){
            p.setY(p.y() + 15);
        }
        painter->drawText(p, QString("%1").arg(i+1));
        if (i == 0){
            painter->drawEllipse(static_cast<int>(p.x() + 15), static_cast<int>(p.y() - 7), 5, 5);
        }
    }
}


void Package_LQFP48::setPoints(){
    for (int i = 0; i < 48; i++){
        QPointF p;

        //left side
        if (i < 12){
            p.setX(-pinW); p.setY(stepPin + (i%12)*stepPin);
            pinOrientationList.append(Utils::View_Horizontal);
        }
        //bottom side
        else if (i < 24){
            p.setY(h); p.setX(2*stepPin + ((i-12)%12)*stepPin);
            pinOrientationList.append(Utils::View_Vertical_NS);
        }
        //right side
        else if (i < 36){
            p.setX(w); p.setY(h - 2*stepPin - ((i-24)%12)*stepPin);
            pinOrientationList.append(Utils::View_Horizontal_Right);
        }
        //top side
        else if (i < 48){
            p.setY(0); p.setX(w - 2*stepPin - ((i-36)%12)*stepPin);
            pinOrientationList.append(Utils::View_Vertical_SN);
        }

        pinPosList.append(p);
    }
}

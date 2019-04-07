#include "package_h16_48_1b.h"
#include <QPainter>

Package_H16_48_1B::Package_H16_48_1B(Processor *mcu)
    : Package ()
{
    packageName = "H16.48-1B";

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

void Package_H16_48_1B::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Package::paint(painter, option, widget);

    setPoints();

    QFont font;
    font.setBold(false);
    painter->setFont(font);

    for(int i = 0 ; i < 48; i++){
        QPointF p = pinPosList.at(i);
        //left side
        if ((i < 6) || (i >= 42)){
            p.setY(p.y() + 15);
            p.setX(p.x() + pinW + 5);
        }
        //bottom side
        else if (i < 18){
            p.setY(p.y() - 5);
            p.setX(p.x() - 15);
            if (i >= 9){
                p.setX(p.x() - 5);
            }

        }
        //right side
        else if (i < 30){
            p.setY(p.y() + 15);
            p.setX(p.x() - 15 - 5);
        }
        //top side
        else if (i < 42){
            p.setY(p.y() + 15);
        }
        painter->drawText(p, QString("%1").arg(i+1));
        if (i == 0){
            QRectF pointFirstPin(p.x()+15, p.y() - 7, 5, 5);
            painter->drawEllipse(pointFirstPin);
        }
    }

}

void Package_H16_48_1B::setPoints()
{
    for (int i = 0; i < 48; i++){
        QPointF p;

        //second half of left side
        if (i < 6){
            p.setX(-pinW); p.setY(h/2 + (i%6)*stepPin);
            pinOrientationList.append(Utils::View_Horizontal);
        }
        //bottom side
        else if (i < 18){
            p.setY(h); p.setX(2*stepPin + ((i-6)%12)*stepPin);
            pinOrientationList.append(Utils::View_Vertical_NS);
        }
        //right side
        else if (i < 30){
            p.setX(w); p.setY(h - 2*stepPin - ((i-18)%12)*stepPin);
            pinOrientationList.append(Utils::View_Horizontal_Right);
        }
        //top side
        else if (i < 42){
            p.setY(0); p.setX(w - 2*stepPin - ((i-30)%12)*stepPin);
            pinOrientationList.append(Utils::View_Vertical_SN);
        }
        //first half of left side
        else{
            p.setX(-pinW); p.setY(stepPin + ((i-42)%6)*stepPin);
            pinOrientationList.append(Utils::View_Horizontal);
        }

        pinPosList.append(p);
    }
}

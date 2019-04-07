#include "package_h18_64_1b.h"

Package_H18_64_1B::Package_H18_64_1B(Processor *mcu)
    : Package ()
{
    packageName = "H18.64-1B";

    if (mcu != nullptr)
    {
        MCUName = mcu->Name();
    }

    int pinsOneSide = 64 / 4 + 1;
    stepPin = static_cast<int>(1.1*pinH);
    w = pinsOneSide*stepPin + stepPin;
    h = w;

    setPoints();
}

void Package_H18_64_1B::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Package::paint(painter, option, widget);

    setPoints();

    QFont font;
    font.setBold(false);
    painter->setFont(font);

    for(int i = 0 ; i < 64; i++){
        QPointF p = pinPosList.at(i);
        //buttom side
        if ((i < 8) || (i >= 56)){
            p.setY(p.y() - 5);
            if (i >= 56)
                p.setX(p.x() - 20);
            else
                p.setX(p.x() - 15);
        }
        //right side
        else if (i < 24){
            p.setY(p.y() + 15);
            p.setX(p.x() - 15 - 5);
        }
        //top side
        else if (i < 40){
            p.setY(p.y() + 15);
        }
        //left side
        else if (i < 56){
            p.setY(p.y() + 15);
            p.setX(p.x() + pinW + 5);
        }
        painter->drawText(p, QString("%1").arg(i+1));
        if (i == 0){
            QRectF pointFirstPin(p.x()+1.5, p.y() - 20, 5, 5);
            painter->drawEllipse(pointFirstPin);
        }
    }
}

void Package_H18_64_1B::setPoints(){
    for (int i = 0; i < 64; i++){
        QPointF p;

        //second half of buttom side
        if (i < 8){
            p.setX(w/2 + stepPin + ((i)%16)*stepPin); p.setY(h);
            pinOrientationList.append(Utils::View_Vertical_NS);
        }
        //right side
        else if (i < 24){
            p.setX(w); p.setY(h - 2*stepPin - ((i-8)%16)*stepPin);
            pinOrientationList.append(Utils::View_Horizontal_Right);
        }
        //top side
        else if (i < 40){
            p.setY(0); p.setX(w - 2*stepPin - ((i-24)%16)*stepPin);
            pinOrientationList.append(Utils::View_Vertical_SN);
        }
        //left side
        else if (i < 56){
            p.setX(-pinW); p.setY(stepPin + ((i-40)%16)*stepPin);
            pinOrientationList.append(Utils::View_Horizontal);
        }
        //first half of bottom side
        else{
            p.setX(2*stepPin + ((i-56)%16)*stepPin); p.setY(h);
            pinOrientationList.append(Utils::View_Vertical_NS);
        }

        pinPosList.append(p);
    }
}

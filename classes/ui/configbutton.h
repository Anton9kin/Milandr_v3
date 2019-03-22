#ifndef CONFIGBUTTON_H
#define CONFIGBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class ConfigButton : public QPushButton
{
    Q_OBJECT

public:
    explicit ConfigButton(QWidget *parent = nullptr);
    explicit ConfigButton(const QString &text, QWidget *parent = nullptr);
    ~ConfigButton();

protected:
    virtual void mousePressEvent(QMouseEvent *e);

};

#endif // CONFIGBUTTON_H

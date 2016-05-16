#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QFrame>
#include <QLayout>
#include <QEvent>
#include <QPainter>

#include <cmath>

struct point {
    double x;
    double y;

    point() {
        x = y = 0.0;
    }
};

class PaintWidget : public QWidget
{
    Q_OBJECT

private:
//	std::vector <std::pair <double, double> > functionData;
    std::vector <point> function;

    QGridLayout *dataLayout;    // общий слой
    QFrame *dataBox;            // окно отображения графика

    void draw(QPainter *);      // отрисовка сетки и графика

protected:
    virtual bool eventFilter(QObject *, QEvent *);

public:
    PaintWidget();
//    ~PaintWidget();

//public slots:
//	void refreshData(std::vector <std::pair <double, double> > &);      // обновление данных графика
    void refreshData(std::vector <point> &);    // обновление данных графика
};

#endif // PAINTWIDGET_H

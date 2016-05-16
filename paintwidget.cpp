#include "paintwidget.h"
#include <QMenu>

PaintWidget::PaintWidget()
{
    dataBox = new QFrame;
    dataBox -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    dataBox -> installEventFilter(this);

    dataLayout = new QGridLayout(this);
    dataLayout -> setMargin(0);
    dataLayout -> addWidget(dataBox);

//	connect(serverStorage, SIGNAL(keyChanged(const char*)), this, SLOT(onKeyChanged(const char*)));
//	refreshData();
    dataBox -> update();
}

//PaintWidget::~PaintWidget() {
//}

//void PaintWidget::refreshData(std::vector </*std::pair <double, double>*/> &xVal) {
void PaintWidget::refreshData(std::vector <point> &xVal) {
    function = xVal;
    dataBox -> update();
}

// = Обработчик событий (перерисовка)   ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
bool PaintWidget::eventFilter(QObject *xObj, QEvent *xEvt) {
    if ((xEvt -> type() == QEvent::Paint) && (xObj == dataBox)) {
        QPainter *p = new QPainter(dataBox);
        draw(p);
        delete p;
    }

    if ((xEvt -> type() == QEvent::MouseButtonPress) && (xObj == dataBox)) {
        QMenu *p = new QMenu();
        p->addAction("Элемент");
        p->exec(QCursor::pos());
    }
    return QWidget::eventFilter(xObj, xEvt);
}

void PaintWidget::draw(QPainter *xPen) {
// = отрисовка сетки     ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
    // рамка
    int bw = int(0.08*width());
    int ew = int(0.75*width());
    int bh = int(0.02*height());
    int eh = int(0.90*height());
    xPen -> setBrush(QBrush(Qt::white, Qt::SolidPattern));
    xPen -> drawRect(bw, bh, ew - bw, eh - bh);

    // настройки отрисовки
    double xmin = 0, xmax = 170, ymin = -2, ymax = 2;
    if (function.size() != 0) {
//        double xmin = 0, xmax = 170, ymin = -2, ymax = 2;
        xmin = function[0].x;
        xmax = function[function.size() - 1].x;
        ymin = -2;
        ymax = 2;
    }

    double zoomx = (ew - bw) / (xmax - xmin);
    double zoomy = (eh - bh) / (ymax - ymin);
    double swx = bw - xmin * zoomx;
    double swy = bh + ymax * zoomy;

    // числа слева и снизу от рамки, ...
    int hor = 6;
    int ver = 8;
    for (int i = 1; i < hor + 1; ++i)
        xPen -> drawText(int(0), int(0.5*bh + i * (eh - bh) / hor), int(0.9*bw), int(0.5*bh + i * (eh - bh) / hor),
            Qt::AlignRight, QString().sprintf("%2.1f", ymax - i * (ymax - ymin) / hor));
    for (int i = 1; i < ver + 1; ++i)
        xPen -> drawText(int(0.5*bw + i * (ew - bw) / ver), int(eh), int(0.5*bw + i * (ew - bw) / ver), int(height() - 1),
            Qt::AlignTop, QString().sprintf("%2.1f", xmin + i * (xmax - xmin) / ver));

    // ... легенда, ...
    int legend = 1;
    xPen -> setPen(QColor("white"));
    xPen -> drawRect(int(0.77*width()), int(0.5*bh + 0.5*(eh - bh) / hor),
             int(0.2*width()), int((legend + 0.5) * (eh - bh) / hor));

    // ... и сетка
    xPen -> setPen(QPen(Qt::gray, 1, Qt::DashLine));
    for (int i = 1; i < hor; ++i) {
        xPen -> drawLine(bw, int(bh + i * (eh - bh) / hor), ew, int(bh + i * (eh - bh) / hor));
    }
    for (int i = 1; i < ver; ++i) {
        xPen -> drawLine(int(bw + i * (ew - bw) / ver), bh, int(bw + i * (ew - bw) / ver), eh);
    }

// = отрисовка данных    ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
    if (function.size() < 2) {
        return; // нечего рисовать без 2-х точек
    }

    xPen -> setPen(QPen(Qt::blue, 2, Qt::SolidLine));
    for (unsigned i = 1; i < function.size(); ++i) {
        int beginLineX = int(swx + zoomx * function[i-1].x);
        int beginLineY = int(swy - zoomy * function[i-1].y);
        int endLineX = int(swx + zoomx * function[i].x);
        int endLineY = int(swy - zoomy * function[i].y);
        if (beginLineX >= bw && beginLineY >= bh && endLineX <= ew && endLineY <= eh) {
            xPen -> drawLine(beginLineX, beginLineY, endLineX, endLineY);
        }
    }
    // текст легенды
    int n = 2;
    xPen -> setPen(QColor("blue"));
    xPen -> drawText(int(0.78*width()), int(0.5*bh + 0.5*n * (eh - bh) / hor), int(width()), int(0.5*bh + 0.5*n * (eh - bh) / hor),
            Qt::AlignLeft, QString("---  Base function"));
}

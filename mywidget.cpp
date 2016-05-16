#include "mywidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
// - настройка окна ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    move(300, 250); // двигаем окно ближе к центру

    setMinimumWidth(800); // задаём минимальные размеры окна
    setMinimumHeight(500);

    setMaximumWidth(1200); // задаём максимальные размеры окна
    setMaximumHeight(700);

// - виджеты на форме    ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    mainVLay = new QVBoxLayout;
    mainLabel = new QLabel("<h2><i>Hello, </i><font color = green>Qt!</font></h2>", 0);
//	mainLabel -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//	mainLabel -> setMaximumHeight(30);

    // выбор задачи
    gbTaskSelect = new QGroupBox();
    gbTaskSelect -> setTitle("Subtask");
    rbgTasks = new QButtonGroup();
    taskSelectLay = new QGridLayout(gbTaskSelect);
    for (int i = 0; i < tasksCount; ++i) {
        rbTask[i] = new QRadioButton(QString(subTaskName[i].c_str()));
        rbgTasks -> addButton(rbTask[i], i);
        taskSelectLay -> addWidget(rbTask[i], i, 0);
    }
    rbTask[0] -> setChecked(true);

    // входные данные
    inputDataFrame = new QFrame();
    inputDataFrame -> setFrameStyle(QFrame::Box);
    inputDataFrame -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    inputLay = new QGridLayout();
    lInData = new QLabel("Parameter A");
    lInData -> setMinimumWidth(125);
    lInData -> setMaximumWidth(125);
    leInData = new QLineEdit();
    leInData -> setMinimumWidth(125);
    leInData -> setMaximumWidth(125);
    leInData -> setText("0.01");
    inputMainText = new QLabel("\tF(x) = sin(A*x)");
//	inputMainText -> setMinimumWidth(125);
//	inputMainText -> setMaximumWidth(125);

    lInMatrix = new QLabel("Input matrix:");
    inMatrixData = new QPlainTextEdit();
    inMatrixData -> setMinimumHeight(40);
    inMatrixData -> setMaximumHeight(80);
    inMatrixData -> setMinimumWidth(125);
    inMatrixData -> setMaximumWidth(125);

    inputButton = new QPushButton("Calculate");
    cancelButton = new QPushButton("Clear");

    // выходные данные 1
    const int dim = 3;
    calcMatrixFrame = new QFrame();
    calcMatrixFrame -> setFrameStyle(QFrame::Box);
    calcMatrixFrame -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//	std::cout << "ok" << std::endl;

    calcMatrixLay = new QGridLayout();
    lRes1 = new QLabel("Determinant");
    lRes2 = new QLabel("Process result");
    lResTotal = new QLabel("Total result");
    leRes1 = new QLineEdit();
    leRes2 = new QTextBrowser();
    tableRes2 = new QTableWidget();
    leResTotal = new QTextBrowser();
    tableTotal = new QTableWidget();
    leRes1 -> setMinimumWidth(100);
    leRes1 -> setMaximumWidth(100);

//    leRes2 -> setMinimumHeight(80);
//    leRes2 -> setMaximumHeight(80);
//    leRes2 -> setMinimumWidth(200);
//    leRes2 -> setMaximumWidth(200);
    tableRes2 -> setMinimumHeight(120);
    tableRes2 -> setMaximumHeight(120);
    tableRes2 -> setMinimumWidth(160);
    tableRes2 -> setMaximumWidth(160);
    tableRes2 -> setRowCount(dim);
    tableRes2 -> setColumnCount(dim);
    for (int i = 0; i < dim; ++i) {
        tableRes2 -> setColumnWidth(i, 45); // Настраиваем ширину столбцов
        tableRes2 -> setHorizontalHeaderItem(i, new QTableWidgetItem (QString::number(i)));
        tableRes2 -> setVerticalHeaderItem(i, new QTableWidgetItem (QString::number(i)));
    }


//    leResTotal -> setMinimumHeight(80);
//    leResTotal -> setMaximumHeight(80);
//    leResTotal -> setMinimumWidth(200);
//    leResTotal -> setMaximumWidth(200);
    tableTotal -> setMinimumHeight(120);
    tableTotal -> setMaximumHeight(120);
    tableTotal -> setMinimumWidth(160);
    tableTotal -> setMaximumWidth(160);
    tableTotal -> setRowCount(dim);
    tableTotal -> setColumnCount(dim);
    for (int i = 0; i < dim; ++i) {
        tableTotal -> setColumnWidth(i, 45); // Настраиваем ширину столбцов
        tableTotal -> setHorizontalHeaderItem(i, new QTableWidgetItem (QString::number(i)));
        tableTotal -> setVerticalHeaderItem(i, new QTableWidgetItem (QString::number(i)));
    }

    // выходные данные 2
    graphFrame = new PaintWidget;
//	graphFrame -> setFrameStyle(QFrame::Box);
    graphFrame -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    graphFrame -> setMinimumWidth(400);
    graphFrame -> setMinimumHeight(250);

// - компоновка виджетов ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    setLayout(mainVLay);
//	mainVLay -> setAlignment(Qt::AlignHCenter);
    mainVLay -> addWidget(mainLabel);
    mainVLay -> addWidget(gbTaskSelect);
    mainVLay -> addWidget(inputDataFrame);
//	mainVLay -> addWidget(outputDataFrame);

    inputDataFrame -> setLayout(inputLay);
    inputLay -> addWidget(lInData, 0, 0);
    inputLay -> addWidget(leInData, 0, 1);
    inputLay -> addWidget(inputMainText, 0, 2);
    inputLay -> addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred), 0, 3);
    inputLay -> addWidget(lInMatrix, 1, 0);
    inputLay -> addWidget(inMatrixData, 1, 1);
    inputLay -> addWidget(inputButton, 2, 0);
    inputLay -> addWidget(cancelButton, 2, 1);

    calcMatrixFrame -> setLayout(calcMatrixLay);
    calcMatrixLay -> addWidget(lRes1, 0, 0);
    calcMatrixLay -> addWidget(leRes1, 1, 0);
    calcMatrixLay -> addWidget(lRes2, 0, 1);
//    calcMatrixLay -> addWidget(leRes2, 1, 1);
    calcMatrixLay -> addWidget(tableRes2, 1, 1);
    calcMatrixLay -> addWidget(lResTotal, 0, 2);
//    calcMatrixLay -> addWidget(leResTotal, 1, 2);
    calcMatrixLay -> addWidget(tableTotal, 1, 2);
    calcMatrixLay -> addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred), 0, 2);

    mainVLay -> addWidget(calcMatrixFrame);
    mainVLay -> addWidget(graphFrame);

    // "пружинка" до нижней кромки
    mainVLay -> addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

// - сигналы / слоты     ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    connect(inputButton, SIGNAL(clicked()), this, SLOT(onInputButtonClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancelButtonClicked()));
    connect(rbgTasks, SIGNAL(buttonPressed(int)), this, SLOT(onSubTaskChanged(int)));

    onSubTaskChanged(0);
}

MainWidget::~MainWidget()
{
}

void MainWidget::calculateFunction(const int M = 0) {
    // M - число точек функции
    std::vector <point> localFunction;
    for (int i = 0; i < M; ++i) {
        point localPoint;
        localPoint.x = i;
        localPoint.y = sin(omega * localPoint.x);
        localFunction.push_back(localPoint);
    }

    graphFrame -> refreshData(localFunction);
}

void MainWidget::calculateMatrix(double A[][3]) {
    // расчёт и вывод определителя
    double detA =   A[0][0] * (A[1][1]*A[2][2] - A[2][1]*A[1][2])
                  - A[0][1] * (A[1][0]*A[2][2] - A[2][0]*A[1][2])
                  + A[0][2] * (A[1][0]*A[2][1] - A[1][1]*A[2][0]);
    leRes1 -> setText(QString::number(detA));

    // алгебраические дополнения
    double Anew[3][3];
    Anew[0][0] =   A[1][1]*A[2][2] - A[2][1]*A[1][2];
    Anew[0][1] = -(A[1][0]*A[2][2] - A[2][0]*A[1][2]);
    Anew[0][2] =   A[1][0]*A[2][1] - A[1][1]*A[2][0];
    Anew[1][0] = -(A[0][1]*A[2][2] - A[0][2]*A[2][1]);
    Anew[1][1] =   A[0][0]*A[2][2] - A[0][2]*A[2][0];
    Anew[1][2] = -(A[0][0]*A[2][1] - A[0][1]*A[2][0]);
    Anew[2][0] =   A[0][1]*A[1][2] - A[0][2]*A[1][1];
    Anew[2][1] = -(A[0][0]*A[1][2] - A[1][0]*A[0][2]);
    Anew[2][2] =   A[0][0]*A[1][1] - A[1][0]*A[0][1];

    QTableWidgetItem *item;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            A[i][j] = Anew[i][j];
            item = new QTableWidgetItem(QString::number(A[i][j]));
            item -> setTextAlignment(Qt::AlignTop | Qt::AlignCenter);
            tableRes2 -> setItem(i, j, item);
        }
    }
    leRes2 -> setText(matrixToOut(A));

    //транспонирование матрицы
    double temp;
    temp = A[0][1]; A[0][1] = A[1][0]; A[1][0] = temp;
    temp = A[0][2]; A[0][2] = A[2][0]; A[2][0] = temp;
    temp = A[1][2]; A[1][2] = A[2][1]; A[2][1] = temp;

    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            A[i][j] /= detA;
            item = new QTableWidgetItem(QString::number(A[i][j], 'g', 2));
            item -> setTextAlignment(Qt::AlignTop | Qt::AlignCenter);
            tableTotal -> setItem(i, j, item);
        }
    }
//    leResTotal -> setText(matrixToOut(A));
}

QString MainWidget::matrixToOut(double A[][3]) {
    QString localStr = "";
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            localStr += QString::number(A[i][j]) + "     ";
        }
        localStr += '\n';
    }
    return localStr;
}

// = ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
// - Class SLOTs
// = ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====

void MainWidget::onInputButtonClicked() {
//	std::cout << "! _ input button is clicked" << std::endl;
//	std::cout << "! _ input val " << leInData -> text().toDouble() << std::endl;

    std::cout << "! curr task " << rbgTasks -> checkedId() << std::endl;
    if (rbgTasks -> checkedId() == 0) {
        // выбрана задача расчёта матрицы
        std::cout << "! _ inputed val (double) " << inMatrixData -> toPlainText().toDouble() << std::endl;
        std::cout << "! _ inputed text " << inMatrixData -> toPlainText().toStdString() << std::endl;

        double inMatrix[3][3];
        QString inputedText = inMatrixData -> toPlainText();

        // анализ введённого текста и преобразование в матрицу
        QStringList subString = inputedText.split('\n'); // разбивка всего текста на строки
    //	std::cout << "! _ inputed size " << subString.size() << std::endl;
        for (int i = 0; i < subString.size(); ++i) {
    //		std::cout << "! _ subStr " << subString[i].toStdString() << std::endl;

            QStringList subVal = subString[i].split(' '); // разбивка строк на значения
    //		std::cout << "! _ subStr[" << i << "] size " << subVal.size() << std::endl;
            for (int j = 0; j < subVal.size(); ++j) {
                std::cout << "! _ subVal " << subVal[j].toDouble() << std::endl;
                inMatrix[i][j] = subVal[j].toDouble();
            }
        }

        calculateMatrix(inMatrix);
    }
    else if (rbgTasks -> checkedId() == 1) {
        // выбрана задача отрисовки графика
        omega = leInData -> text().toDouble();
        calculateFunction(300);
    }
}

void MainWidget::onCancelButtonClicked() {
//	std::cout << "! _ cancel button is clicked" << std::endl;

    std::cout << "! curr task " << rbgTasks -> checkedId() << std::endl;
    if (rbgTasks -> checkedId() == 0) {
        // выбрана задача расчёта матрицы
        inMatrixData -> clear();

        leRes1 -> clear();
//        leRes2 -> clear();
//        leResTotal -> clear();
        tableRes2 -> clear();
        tableTotal -> clear();
        for (int i = 0; i < 3; ++i) {
            tableRes2 -> setHorizontalHeaderItem(i, new QTableWidgetItem (QString::number(i)));
            tableRes2 -> setVerticalHeaderItem(i, new QTableWidgetItem (QString::number(i)));
            tableTotal -> setHorizontalHeaderItem(i, new QTableWidgetItem (QString::number(i)));
            tableTotal -> setVerticalHeaderItem(i, new QTableWidgetItem (QString::number(i)));
        }
    }
    else if (rbgTasks -> checkedId() == 1) {
        // выбрана задача отрисовки графика
        calculateFunction();
    }
}

void MainWidget::onSubTaskChanged(int xVal) {
    std::cout << "! _ subtask is changed " << xVal << std::endl;

    if (xVal == 0) {
        // прячем элементы задачи отрисовки
        lInData -> hide();
        leInData -> hide();
        inputMainText -> hide();
        graphFrame -> hide();

        // отображаем элементы задачи расчёта матрицы
        lInMatrix -> show();
        inMatrixData -> show();
        calcMatrixFrame -> show();
    }
    else if (xVal == 1) {
        lInMatrix -> hide();
        inMatrixData -> hide();
        calcMatrixFrame -> hide();

        lInData -> show();
        leInData -> show();
        inputMainText -> show();
        graphFrame -> show();
    }
}

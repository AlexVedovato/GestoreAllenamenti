#include <QApplication>
#include "View/MainWindow.h"
#include "Allenamento.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":assets/icon.svg")); 
    Allenamento all;
    View::MainWindow main_window(all);
    main_window.resize(1024, 512);
    main_window.show();
    return app.exec();
}

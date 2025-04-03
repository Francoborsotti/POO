#include <QApplication>
#include <QWidget>
#include "login.h"

int main( int argc, char ** argv )  {
    QApplication a( argc, argv );

    Login * login = new Login;
    login->resize( 1536/2, 1024/2 );
    login->setWindowTitle( "Login" );
    login->show();


    return a.exec();
}

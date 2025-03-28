#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>


int main( int argc, char** argv )  {
    QApplication a( argc, argv );

    QWidget * ventana = new QWidget;  // Es la ventana padre (principal)
    ventana->setWindowTitle( "Volumen" );//establece el titulo de la ventana
    ventana->resize( 300, 50 );//ajusta dimenciones

    QSpinBox * spinBox = new QSpinBox;// Crea una cja de selecion de numeros
    QSlider * slider = new QSlider( Qt::Horizontal );// Crea un control deslizante horizontal
    spinBox->setRange( 0, 100 );// Establece el rango de la caja
    slider->setRange( 0, 100 );// Establece el rango de la barra

    QObject::connect( spinBox, SIGNAL( valueChanged( int ) ), slider, SLOT( setValue( int ) ) );
    QObject::connect( slider, SIGNAL( valueChanged( int ) ),  spinBox, SLOT( setValue( int ) ) );
    QObject::connect(slider, &QSlider::valueChanged, [ventana](int value) {
        ventana->setWindowTitle("Volumen: " + QString::number(value));
    });

    spinBox->setValue( 15 );

    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget( spinBox );
    layout->addWidget( slider );
    ventana->setLayout( layout );
    ventana->setVisible( true );

    return a.exec();
}

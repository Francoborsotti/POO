#include "benchmarkgui.h"
#include <QDebug> // Para mensajes de depuración (opcional, pero útil)

BenchmarkGUI::BenchmarkGUI(QWidget *parent)
    : QWidget(parent),
    startButton(new QPushButton("Iniciar Benchmark", this)),
    resultsTextEdit(new QTextEdit(this)),
    statusLabel(new QLabel("Presiona 'Iniciar Benchmark' para comenzar.", this)),
    mySensor(new Sensor()) // Instancia del sensor
{
    setWindowTitle("Benchmark de Funciones Inline/Offline");
    setMinimumSize(600, 400);

    // Configuración del layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(startButton);
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(resultsTextEdit);

    // Configurar el QTextEdit como solo lectura
    resultsTextEdit->setReadOnly(true);

    // Conexiones de señales y slots
    connect(startButton, SIGNAL(clicked()), this, SLOT(on_startButton_clicked()));
}

BenchmarkGUI::~BenchmarkGUI()
{
    // QWidget se encarga de eliminar los widgets hijos.
    // mySensor también será eliminado por QWidget si lo declaramos como QObject*
    // pero como es una clase C++ normal, lo eliminamos manualmente.
    delete mySensor;
}

// Slot: Se ejecuta cuando se hace clic en el botón "Iniciar Benchmark"
void BenchmarkGUI::on_startButton_clicked()
{
    resultsTextEdit->clear(); // Limpia los resultados anteriores
    statusLabel->setText("Ejecutando benchmark...");
    startButton->setEnabled(false); // Deshabilita el botón durante la ejecución

    // Ejecuta el benchmark
    runBenchmark();

    statusLabel->setText("Benchmark completado.");
    startButton->setEnabled(true); // Habilita el botón de nuevo
}

// Función: Realiza las pruebas de rendimiento y muestra los resultados
void BenchmarkGUI::runBenchmark()
{
    QElapsedTimer timer; // Objeto para medir el tiempo

    QString logOutput; // Para acumular los resultados y mostrarlos de una vez

    // --- Benchmark: getValorBruto() (inline implícito) ---
    timer.start();
    for (long long i = 0; i < ITERATIONS; ++i) {
        mySensor->getValorBruto();
    }
    logOutput += QString("Tiempo para getValorBruto() (%1 llamadas): %2 ms\n")
                     .arg(ITERATIONS)
                     .arg(timer.elapsed());
    qDebug() << "Tiempo para getValorBruto():" << timer.elapsed() << "ms"; // También a consola si Debug está activo

    // --- Benchmark: getValorBrutoOffline() (offline) ---
    timer.start();
    for (long long i = 0; i < ITERATIONS; ++i) {
        mySensor->getValorBrutoOffline();
    }
    logOutput += QString("Tiempo para getValorBrutoOffline() (%1 llamadas): %2 ms\n")
                     .arg(ITERATIONS)
                     .arg(timer.elapsed());
    qDebug() << "Tiempo para getValorBrutoOffline():" << timer.elapsed() << "ms";

    // --- Benchmark: getValorNormalizado() (inline explícito) ---
    timer.start();
    for (long long i = 0; i < ITERATIONS; ++i) {
        mySensor->getValorNormalizado();
    }
    logOutput += QString("Tiempo para getValorNormalizado() (%1 llamadas): %2 ms\n")
                     .arg(ITERATIONS)
                     .arg(timer.elapsed());
    qDebug() << "Tiempo para getValorNormalizado():" << timer.elapsed() << "ms";

    // --- Benchmark: getValorNormalizadoOffline() (offline) ---
    timer.start();
    for (long long i = 0; i < ITERATIONS; ++i) {
        mySensor->getValorNormalizadoOffline();
    }
    logOutput += QString("Tiempo para getValorNormalizadoOffline() (%1 llamadas): %2 ms\n")
                     .arg(ITERATIONS)
                     .arg(timer.elapsed());
    qDebug() << "Tiempo para getValorNormalizadoOffline():" << timer.elapsed() << "ms";

    resultsTextEdit->setText(logOutput); // Muestra todos los resultados en el QTextEdit
}

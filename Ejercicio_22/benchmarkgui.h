#ifndef BENCHMARKGUI_H
#define BENCHMARKGUI_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QElapsedTimer> // Para medir el tiempo
#include "sensor.h"      // Incluimos nuestra clase Sensor

#define ITERATIONS 10000000 // 10 millones de veces

class BenchmarkGUI : public QWidget
{
    Q_OBJECT // Macro necesaria para que las señales y slots funcionen

public:
    explicit BenchmarkGUI(QWidget *parent = nullptr);
    ~BenchmarkGUI();

private slots:
    // Slot que se ejecuta cuando se hace clic en el botón de iniciar benchmark
    void on_startButton_clicked();

private:
    QPushButton *startButton; // Botón para iniciar el benchmark
    QTextEdit *resultsTextEdit; // Área para mostrar los resultados
    QLabel *statusLabel;        // Etiqueta de estado

    // Objeto Sensor para las pruebas
    Sensor *mySensor;

    // Métodos para ejecutar cada benchmark
    void runBenchmark();
};

#endif // BENCHMARKGUI_H

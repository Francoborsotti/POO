#ifndef JUEGOTREX_H
#define JUEGOTREX_H

#include <QWidget>
#include <QTimer>
#include <QList>
#include <QKeyEvent>
#include <QPainter>
#include <QMessageBox> // Para la ventana emergente de Game Over
#include <QPushButton> // Para botones en QMessageBox

// Pre-declaraciones
class TRex;
class Cactus;
class Pajaro;

// Constantes del juego (puedes ajustarlas)
const int INTERVALO_GAME_LOOP_MS = 20;    // Aprox 50 FPS
const int INTERVALO_SPAWN_PAJARO_MS = 4500; // Un poco menos que 5 seg
const int VELOCIDAD_INICIAL_JUEGO = 6;
const int INCREMENTO_VELOCIDAD_MS = 8000; // Cada 8 segundos aumenta velocidad
const int PAJARO_ALTO_MAX_OFFSET = 150;   // Cuán alto puede volar el pájaro respecto al TRex

class JuegoTRex : public QWidget
{
    Q_OBJECT

public:
    explicit JuegoTRex(QWidget *parent = nullptr);
    ~JuegoTRex();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    void inicializarJuego();
    void limpiarObstaculos();
    void detectarColisiones();
    void terminarJuego();    // Mostrará el QMessageBox
    void reiniciarJuego();
    void generarCactus();
    // void generarPajaro(); // Se llama desde slotGenerarPajaro

    TRex *miTRex;
    QList<Cactus*> listaCactus;
    QList<Pajaro*> listaPajaros;

    QTimer *gameLoopTimer;
    QTimer *birdSpawnTimer;
    QTimer *velocidadTimer;

    bool gameOver;      // Estado del juego
    bool juegoPausado;  // Para pausar mientras se muestra el QMessageBox
    int velocidadJuego;
    int puntaje;

    // Ya no QImage imgGameOver;

    int alturaSuelo;
    int trexPosX_inicial;

private slots:
    void slotActualizarJuego();
    void slotGenerarPajaro();
    void slotIncrementarVelocidad();
};

#endif // JUEGOTREX_H

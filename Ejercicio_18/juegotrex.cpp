#include "juegotrex.h"
#include "trex.h"
#include "cactus.h"
#include "pajaro.h" // Asegúrate que PAJARO_RADIO está accesible o definido aquí si lo usas
#include <QDebug>
#include <cstdlib>
#include <ctime>

// Si PAJARO_RADIO se usa en juegotrex.cpp, debe estar definido.
// Podría ser mejor pasar la altura del TRex a generarPajaro.
// Por ahora, asumimos que las constantes de Pajaro.h son suficientes
// para calcular alturas de vuelo seguras.

JuegoTRex::JuegoTRex(QWidget *parent)
    : QWidget(parent),
    miTRex(nullptr),
    gameLoopTimer(nullptr),
    birdSpawnTimer(nullptr),
    velocidadTimer(nullptr),
    gameOver(false),
    juegoPausado(false), // Inicialmente no pausado
    velocidadJuego(VELOCIDAD_INICIAL_JUEGO),
    puntaje(0)
{
    this->setFixedSize(800, 300);
    this->setStyleSheet("background-color: #f0f0f0;"); // Un gris claro para el fondo

    alturaSuelo = this->height() - 40;
    trexPosX_inicial = 50;

    // No hay carga de imgGameOver
    std::srand(std::time(nullptr));
    inicializarJuego();
    this->setFocusPolicy(Qt::StrongFocus);
}

JuegoTRex::~JuegoTRex()
{
    limpiarObstaculos();
    // Qt se encarga de los QObjects hijos (Timers, miTRex, y obstáculos si son hijos)
}

void JuegoTRex::inicializarJuego()
{
    gameOver = false;
    juegoPausado = false;
    puntaje = 0;
    velocidadJuego = VELOCIDAD_INICIAL_JUEGO;

    if (!miTRex) {
        miTRex = new TRex(this);
    }
    miTRex->setAlturaSuelo(alturaSuelo);
    miTRex->resetear();
    miTRex->move(trexPosX_inicial, alturaSuelo - miTRex->height());
    miTRex->show();

    limpiarObstaculos();

    if (!gameLoopTimer) {
        gameLoopTimer = new QTimer(this);
        connect(gameLoopTimer, SIGNAL(timeout()), this, SLOT(slotActualizarJuego()));
    }
    gameLoopTimer->start(INTERVALO_GAME_LOOP_MS);

    if (!birdSpawnTimer) {
        birdSpawnTimer = new QTimer(this);
        connect(birdSpawnTimer, SIGNAL(timeout()), this, SLOT(slotGenerarPajaro()));
    }
    birdSpawnTimer->start(INTERVALO_SPAWN_PAJARO_MS);

    if (!velocidadTimer) {
        velocidadTimer = new QTimer(this);
        connect(velocidadTimer, SIGNAL(timeout()), this, SLOT(slotIncrementarVelocidad()));
    }
    velocidadTimer->start(INCREMENTO_VELOCIDAD_MS);

    generarCactus(); // Generar el primer cactus
    this->update();
}

void JuegoTRex::limpiarObstaculos()
{
    qDeleteAll(listaCactus.begin(), listaCactus.end());
    listaCactus.clear();
    qDeleteAll(listaPajaros.begin(), listaPajaros.end());
    listaPajaros.clear();
}

void JuegoTRex::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // Dibujar suelo
    painter.setPen(Qt::black);
    painter.drawLine(0, alturaSuelo, this->width(), alturaSuelo);

    // Dibujar puntaje y velocidad
    painter.setFont(QFont("Consolas", 14)); // Fuente monoespaciada
    painter.drawText(this->width() - 220, 30, "Puntaje: " + QString::number(puntaje));
    painter.drawText(20, 30, "Velocidad: " + QString::number(velocidadJuego));

    // Ya no se dibuja "Game Over" aquí. Se maneja con QMessageBox.
}

void JuegoTRex::keyPressEvent(QKeyEvent *event)
{
    // Si el juego está pausado (mostrando QMessageBox), no procesar teclas de juego
    if (juegoPausado) {
        QWidget::keyPressEvent(event); // Dejar que Qt maneje teclas para el dialogo (ej. Enter, Esc)
        return;
    }

    // Si es gameOver pero el juego aún no está pausado (antes de mostrar el dialogo)
    // O si el juego está activo
    if (!gameOver && !event->isAutoRepeat()) {
        switch (event->key()) {
        case Qt::Key_Space:
        case Qt::Key_Up:
            miTRex->saltar();
            break;
        case Qt::Key_Down:
            miTRex->agacharse();
            break;
        case Qt::Key_Right:
            miTRex->setVelocidadX(25); // Mayor impulso
            break;
        case Qt::Key_Left:
            miTRex->setVelocidadX(-25);
            break;
        default:
            QWidget::keyPressEvent(event);
        }
    } else {
        QWidget::keyPressEvent(event);
    }
}

void JuegoTRex::keyReleaseEvent(QKeyEvent *event) {
    if (juegoPausado || gameOver || event->isAutoRepeat()) {
        QWidget::keyReleaseEvent(event);
        return;
    }

    if (event->key() == Qt::Key_Down) {
        miTRex->dejarDeAgacharse();
    } else {
        QWidget::keyReleaseEvent(event);
    }
}

void JuegoTRex::slotActualizarJuego()
{
    if (gameOver || juegoPausado) return; // No actualizar si el juego terminó o está pausado

    miTRex->actualizarPosicion();

    // Mover y gestionar Cactus
    for (int i = listaCactus.size() - 1; i >= 0; --i) {
        Cactus *cactus = listaCactus.at(i);
        cactus->move(cactus->x() - velocidadJuego, cactus->y());
        if (cactus->x() + cactus->width() < 0) { // Si sale de pantalla
            listaCactus.removeAt(i);
            cactus->deleteLater();
            puntaje += 10 * (velocidadJuego / VELOCIDAD_INICIAL_JUEGO); // Puntos escalados
        }
    }

    // Gestionar Pájaros (se mueven solos, aquí se revisa si salen)
    for (int i = listaPajaros.size() - 1; i >= 0; --i) {
        Pajaro *pajaro = listaPajaros.at(i);
        if (pajaro->x() + pajaro->width() < 0) {
            listaPajaros.removeAt(i);
            pajaro->deleteLater();
            puntaje += 20 * (velocidadJuego / VELOCIDAD_INICIAL_JUEGO);
        }
    }

    // Generar nuevos cactus
    int minSeparacionCactus = miTRex->width() * 2 + velocidadJuego * 15;
    if (std::rand() % 100 < (3 + velocidadJuego/4) ) {
        bool puedeGenerar = listaCactus.isEmpty() ||
                            (this->width() - (listaCactus.last()->x() + listaCactus.last()->width()) > minSeparacionCactus);
        if (puedeGenerar) {
            generarCactus();
        }
    }

    detectarColisiones(); // Esto puede cambiar gameOver a true
    this->update();
}

void JuegoTRex::generarCactus() {
    Cactus* nuevoCactus = new Cactus(this);
    nuevoCactus->setPosicion(this->width(), alturaSuelo - nuevoCactus->height());
    listaCactus.append(nuevoCactus);
}

void JuegoTRex::slotGenerarPajaro()
{
    if (gameOver || juegoPausado) return;

    // AQUÍ ESTÁ LA CORRECCIÓN:
    int trexHeightForBirdCalc = TREX_ALTO_BASE; // Asumir TRex normal para cálculo de altura de pájaro

    int alturaVueloPiso = 20; // Mínima altura desde el suelo para el pájaro
    // El cálculo original para alturaMaxTRexSaltando no era del todo preciso para el punto más alto del salto,
    // pero la idea es que el pájaro vuele por encima de donde el TRex normalmente está o salta.
    // Vamos a simplificar un poco el cálculo de la altura del pájaro.

    // El pájaro debe volar por encima del TRex.
    // Usaremos PAJARO_ALTO_MAX_OFFSET de juegotrex.h para definir un espacio por encima del suelo.
    // Y PAJARO_RADIO_MAX de pajaro.h para asegurar que el cuerpo del pájaro no toque al TRex.

    // Altura mínima a la que puede volar el pájaro (desde la parte inferior del pájaro)
    int minAlturaVueloPajaro = alturaSuelo - PAJARO_ALTO_MAX_OFFSET - (PAJARO_RADIO_MAX * 2);
    if (minAlturaVueloPajaro < alturaVueloPiso) { // No volar por debajo de la altura mínima del piso
        minAlturaVueloPajaro = alturaVueloPiso;
    }

    // Altura máxima a la que puede volar el pájaro (desde la parte inferior del pájaro)
    // Un poco por encima de la cabeza del TRex cuando está corriendo.
    int maxAlturaVueloPajaro = alturaSuelo - trexHeightForBirdCalc - (PAJARO_RADIO_MAX * 2) - 10; // -10 para un pequeño margen
    if (maxAlturaVueloPajaro < minAlturaVueloPajaro) { // Si max es menor que min, ajustar
        maxAlturaVueloPajaro = minAlturaVueloPajaro + PAJARO_RADIO_MAX; // Dar un pequeño rango
    }
    if (maxAlturaVueloPajaro < alturaVueloPiso) {
        maxAlturaVueloPajaro = alturaVueloPiso + PAJARO_RADIO_MAX;
    }


    int alturaAleatoria;
    if (minAlturaVueloPajaro >= maxAlturaVueloPajaro) { // Si el rango no es válido
        alturaAleatoria = minAlturaVueloPajaro; // Usar la altura mínima
    } else {
        alturaAleatoria = minAlturaVueloPajaro + (std::rand() % (maxAlturaVueloPajaro - minAlturaVueloPajaro + 1));
    }

    // Asegurarse que el pájaro (considerando su tamaño completo) no esté por debajo del suelo.
    if (alturaAleatoria + (PAJARO_RADIO_MAX * 2) > alturaSuelo) {
        alturaAleatoria = alturaSuelo - (PAJARO_RADIO_MAX * 2) - 5; // Ajustar para que no toque el suelo
    }
    if (alturaAleatoria < 0) alturaAleatoria = 5; // No volar fuera de la pantalla por arriba

    Pajaro* nuevoPajaro = new Pajaro(this);
    nuevoPajaro->setPosicion(this->width(), alturaAleatoria); // La posición Y es la parte superior del QWidget del pájaro
    nuevoPajaro->iniciarMovimiento(velocidadJuego + std::rand()%4);
    listaPajaros.append(nuevoPajaro);
}



void JuegoTRex::slotIncrementarVelocidad()
{
    if (gameOver || juegoPausado) return;
    velocidadJuego = qMin(velocidadJuego + 1, 30); // Limitar velocidad
}

void JuegoTRex::detectarColisiones()
{
    if (gameOver) return; // No detectar si ya terminó
    QRect rectTRex = miTRex->getRect();

    for (Cactus *cactus : listaCactus) {
        if (rectTRex.intersects(cactus->getRect())) {
            terminarJuego();
            return;
        }
    }
    for (Pajaro *pajaro : listaPajaros) {
        if (rectTRex.intersects(pajaro->getRect())) {
            terminarJuego();
            return;
        }
    }
}

// juegotrex.cpp
// ... (otras inclusiones)

void JuegoTRex::terminarJuego()
{
    if (gameOver) return;

    gameOver = true;
    juegoPausado = true;

    gameLoopTimer->stop();
    birdSpawnTimer->stop();
    velocidadTimer->stop();

    for (Pajaro *pajaro : listaPajaros) {
        pajaro->detenerMovimiento();
    }

    qDebug() << "¡GAME OVER! Puntaje Final:" << puntaje;

    QMessageBox msgBox(this); // 'this' como padre para la modalidad

    // Aplicar un estilo básico al QMessageBox para asegurar visibilidad
    msgBox.setStyleSheet(
        "QMessageBox {"
        "    background-color: #e0e0e0;" // Un fondo gris claro para el diálogo
        "    color: #111111;"            // Texto oscuro
        "}"
        "QLabel {" // El texto del mensaje es un QLabel dentro del QMessageBox
        "    color: #111111;"
        "    background-color: transparent;" // Asegurar que el fondo del label no tape el del QMessageBox
        "}"
        "QPushButton {"
        "    background-color: #c0c0c0;" // Fondo para los botones
        "    color: #111111;"            // Texto oscuro para los botones
        "    border: 1px solid #555555;"
        "    padding: 5px;"
        "    min-width: 70px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #d0d0d0;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #b0b0b0;"
        "}"
        );

    msgBox.setWindowTitle("Juego Terminado");
    msgBox.setIcon(QMessageBox::Information); // Esto podría no ser visible si el tema de iconos falla
    msgBox.setText(QString("¡GAME OVER!\nTu puntaje final es: %1\n\n¿Quieres jugar de nuevo?").arg(puntaje));

    QPushButton *restartButton = msgBox.addButton("Reiniciar", QMessageBox::AcceptRole);
    QPushButton *quitButton = msgBox.addButton("Salir", QMessageBox::RejectRole);
    msgBox.setDefaultButton(restartButton);
    msgBox.setEscapeButton(quitButton);

    this->update();

    msgBox.exec(); // Muestra el diálogo

    if (msgBox.clickedButton() == restartButton) {
        reiniciarJuego();
    } else {
        this->close();
    }
}

// ... (resto del código de juegotrex.cpp)

void JuegoTRex::reiniciarJuego()
{
    qDebug() << "Reiniciando juego...";
    // Limpiar obstáculos es parte de inicializarJuego ahora.
    // Las variables gameOver y juegoPausado se resetean en inicializarJuego.
    inicializarJuego();
}

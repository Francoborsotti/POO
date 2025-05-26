#include "gestionmedicamentoswidget.h"
#include "ui_gestionmedicamentoswidget.h" // IMPORTANTE: Incluir el header generado por el .ui
#include "admindb.h"
#include "cajamedicamento.h"

#include <QMessageBox>
#include <QDebug>
#include <QListWidgetItem> // Para QListWidget
#include <QVariant>        // Para setData con float
#include <QCoreApplication> // Para applicationDirPath
#include <QSqlError>        // Para mostrar el error de la BD

GestionMedicamentosWidget::GestionMedicamentosWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GestionMedicamentosWidget) // Crear instancia de la clase UI
{
    ui->setupUi(this); // Configurar la UI definida en Qt Designer en este widget

    // Título y configuraciones adicionales que no se hicieron en Designer
    this->setWindowTitle("Gestión de Medicamentos - APROSS (UI v2)");

    // Conectar a la base de datos
    if (!AdminDB::getInstance()->conectar()) {
        QMessageBox::critical(this, "Error de Base de Datos",
                              "No se pudo conectar a la base de datos: " +
                                  AdminDB::getInstance()->getLastError().text() +
                                  "\nEl archivo debería estar en: " +
                                  QCoreApplication::applicationDirPath() + "/medicamentos.sqlite" +
                                  "\nLa aplicación no funcionará correctamente.");
        // Podrías deshabilitar la UI aquí si la BD es esencial
        ui->btnAgregar->setEnabled(false);
        ui->btnSumar->setEnabled(false);
        ui->btnComparar->setEnabled(false);
    }

    // Conexiones de señales y slots (los nombres de objeto deben coincidir con los del .ui)
    connect(ui->btnAgregar, SIGNAL(clicked()), this, SLOT(slotAgregarCaja()));
    connect(ui->btnSumar, SIGNAL(clicked()), this, SLOT(slotSumarSeleccionadas()));
    connect(ui->btnComparar, SIGNAL(clicked()), this, SLOT(slotCompararSeleccionadas()));
    connect(ui->lwCajas, SIGNAL(itemSelectionChanged()), this, SLOT(slotActualizarEstadoBotones()));

    // Estado inicial y carga de datos
    actualizarTotalDosisDisplay(); // Muestra los textos fijos y el total de dosis al inicio
    cargarCajasEnLista();          // Carga las cajas existentes
    slotActualizarEstadoBotones(); // Establece el estado inicial de los botones Sumar/Comparar
}

GestionMedicamentosWidget::~GestionMedicamentosWidget()
{
    AdminDB::getInstance()->desconectar();
    delete ui; // Liberar la memoria de la instancia de UI
}

void GestionMedicamentosWidget::actualizarTotalDosisDisplay() {
    float total = AdminDB::getInstance()->obtenerTotalDosisActuales();
    ui->lblTotalDosis->setText(QString("<b>Total Dosis Actuales:</b> %1").arg(total, 0, 'f', 1));

    // Asegurar que los textos fijos también estén (si no se pusieron en Designer)
    ui->lblObraSocial->setText("<b>Obra Social:</b> APROSS (Única)");
    ui->lblLimiteDosis->setText(QString("<b>Límite Total Dosis Permitidas:</b> %1").arg(1000.0, 0, 'f', 1));
}

void GestionMedicamentosWidget::cargarCajasEnLista()
{
    ui->lwCajas->clear();
    QList<CajaMedicamento> cajas = AdminDB::getInstance()->obtenerTodas();
    for (const CajaMedicamento &caja : cajas) {
        QListWidgetItem *item = new QListWidgetItem(caja.toString(), ui->lwCajas);
        item->setData(Qt::UserRole, caja.getId());
        // Guardar dosis como QVariant para recuperarlo como float
        item->setData(Qt::UserRole + 1, QVariant::fromValue(caja.getDosisTotales()));
    }
    actualizarTotalDosisDisplay(); // El total puede haber cambiado
    slotActualizarEstadoBotones(); // La selección cambia (se borra)
}

void GestionMedicamentosWidget::slotAgregarCaja()
{
    float dosis = static_cast<float>(ui->dspDosisIngreso->value());
    if (dosis <= 0.0001f) { // Considerar una pequeña tolerancia para el mínimo
        QMessageBox::warning(this, "Dosis Inválida", "La cantidad de dosis debe ser un valor positivo.");
        return;
    }

    if (AdminDB::getInstance()->insertarCaja(dosis)) {
        QMessageBox::information(this, "Éxito", "Caja de medicamento agregada correctamente.");
        cargarCajasEnLista();
        ui->dspDosisIngreso->setValue(50.0); // Resetear valor del spinbox
    } else {
        float totalActual = AdminDB::getInstance()->obtenerTotalDosisActuales();
        float limiteGlobal = 1000.0f; // Podría ser una constante de AdminDB
        QMessageBox::warning(this, "Límite Excedido o Error",
                             QString("No se pudo agregar la caja.\n"
                                     "Total de dosis actual: %1\n"
                                     "Dosis a agregar: %2\n"
                                     "Límite total permitido: %3\n"
                                     "Verifique que la suma no exceda el límite total o que no haya un error en la BD (%4).")
                                 .arg(totalActual, 0, 'f', 1)
                                 .arg(dosis, 0, 'f', 1)
                                 .arg(limiteGlobal, 0, 'f', 1)
                                 .arg(AdminDB::getInstance()->getLastError().text()));
    }
}

void GestionMedicamentosWidget::slotSumarSeleccionadas()
{
    QList<QListWidgetItem*> seleccionados = ui->lwCajas->selectedItems();
    if (seleccionados.count() != 2) {
        QMessageBox::information(this, "Selección Inválida", "Por favor, seleccione exactamente dos cajas para sumar.");
        return;
    }

    // Reconstruir los objetos CajaMedicamento a partir de los datos guardados
    int id1 = seleccionados.at(0)->data(Qt::UserRole).toInt();
    float dosis1 = seleccionados.at(0)->data(Qt::UserRole + 1).toFloat();
    CajaMedicamento caja1(id1, dosis1);

    int id2 = seleccionados.at(1)->data(Qt::UserRole).toInt();
    float dosis2 = seleccionados.at(1)->data(Qt::UserRole + 1).toFloat();
    CajaMedicamento caja2(id2, dosis2);

    CajaMedicamento cajaSumada = caja1 + caja2; // Usa operator+

    if (cajaSumada.getDosisTotales() > LIMITE_DOSIS_CAJA_SUMADA + 0.001f) { // Tolerancia para float
        QMessageBox::warning(this, "Límite Excedido para Caja Combinada",
                             QString("La suma de las dosis seleccionadas (%1) excede el límite de %2 dosis permitido para una única caja combinada.")
                                 .arg(cajaSumada.getDosisTotales(), 0, 'f', 1)
                                 .arg(LIMITE_DOSIS_CAJA_SUMADA, 0, 'f', 1));
        return;
    }

    QString pregunta = QString("¿Desea reemplazar las cajas seleccionadas:\n"
                               "  %1\n"
                               "  %2\n"
                               "Con una nueva caja de %3 dosis?")
                           .arg(caja1.toString())
                           .arg(caja2.toString())
                           .arg(cajaSumada.getDosisTotales(), 0, 'f', 1);
    QMessageBox::StandardButton respuesta;
    respuesta = QMessageBox::question(this, "Confirmar Suma y Reemplazo", pregunta,
                                      QMessageBox::Yes | QMessageBox::No);

    if (respuesta == QMessageBox::Yes) {
        if (AdminDB::getInstance()->reemplazarDosCajasConSuma(id1, id2, cajaSumada.getDosisTotales())) {
            QMessageBox::information(this, "Éxito", "Las cajas fueron sumadas y reemplazadas correctamente.");
            cargarCajasEnLista(); // Actualizar la lista y el total de dosis
        } else {
            QMessageBox::critical(this, "Error de Base de Datos",
                                  "No se pudieron reemplazar las cajas.\nError: " +
                                      AdminDB::getInstance()->getLastError().text());
        }
    }
}

void GestionMedicamentosWidget::slotCompararSeleccionadas()
{
    QList<QListWidgetItem*> seleccionados = ui->lwCajas->selectedItems();
    if (seleccionados.count() != 2) {
        QMessageBox::information(this, "Selección Inválida", "Por favor, seleccione exactamente dos cajas para comparar.");
        return;
    }

    float dosis1 = seleccionados.at(0)->data(Qt::UserRole + 1).toFloat();
    // No necesitamos el ID para la comparación de dosis, pero sí para reconstruir si quisiéramos el objeto completo
    CajaMedicamento caja1(seleccionados.at(0)->data(Qt::UserRole).toInt(), dosis1);


    float dosis2 = seleccionados.at(1)->data(Qt::UserRole + 1).toFloat();
    CajaMedicamento caja2(seleccionados.at(1)->data(Qt::UserRole).toInt(), dosis2);

    bool sonIguales = (caja1 == caja2); // Usa operator==

    QString mensajeResultado = QString("Comparación de Cajas:\n  %1\n  %2\n\nResultado: Ellas %3 tienen la misma cantidad de dosis.")
                                   .arg(caja1.toString())
                                   .arg(caja2.toString())
                                   .arg(sonIguales ? "SÍ" : "NO");
    qDebug().noquote() << mensajeResultado; // Mostrar por consola
    QMessageBox::information(this, "Resultado de Comparación", mensajeResultado);
}

void GestionMedicamentosWidget::slotActualizarEstadoBotones()
{
    int seleccionados = ui->lwCajas->selectedItems().count();
    ui->btnSumar->setEnabled(seleccionados == 2);
    ui->btnComparar->setEnabled(seleccionados == 2);
}

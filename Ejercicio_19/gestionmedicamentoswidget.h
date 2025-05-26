#ifndef GESTIONMEDICAMENTOSWIDGET_H
#define GESTIONMEDICAMENTOSWIDGET_H

#include <QWidget>

// Forward declaration para la clase generada por el .ui
QT_BEGIN_NAMESPACE
namespace Ui { class GestionMedicamentosWidget; }
QT_END_NAMESPACE

class GestionMedicamentosWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GestionMedicamentosWidget(QWidget *parent = nullptr);
    ~GestionMedicamentosWidget();

private slots:
    void slotAgregarCaja();
    void slotSumarSeleccionadas();
    void slotCompararSeleccionadas();
    void slotActualizarEstadoBotones(); // Habilita/deshabilita botones Sumar/Comparar

private:
    void cargarCajasEnLista(); // Carga/refresca el QListWidget
    void actualizarTotalDosisDisplay(); // Actualiza el QLabel del total

    Ui::GestionMedicamentosWidget *ui; // Puntero a la clase de UI generada

    const float LIMITE_DOSIS_CAJA_SUMADA = 1000.0f; // Límite para una caja individual resultante de una suma
};

#endif // GESTIONMEDICAMENTOSWIDGET_H

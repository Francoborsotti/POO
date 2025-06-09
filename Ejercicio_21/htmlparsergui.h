#ifndef HTMLPARSERGUI_H
#define HTMLPARSERGUI_H

#include <QWidget>        // Clase base para la GUI
#include <QLineEdit>      // Campo de entrada de texto
#include <QPushButton>    // Botones
#include <QTextEdit>      // Área de texto para logs
#include <QLabel>         // Etiquetas de texto
#include <QVBoxLayout>    // Layout vertical
#include <QHBoxLayout>    // Layout horizontal
#include <QNetworkAccessManager> // Gestor de solicitudes de red
#include <QNetworkReply>  // Objeto de respuesta de red
#include <QUrl>           // Para manipular URLs
#include <QFile>          // Para guardar archivos
#include <QFileDialog>    // Cuadro de diálogo para seleccionar archivos/directorios
#include <QDir>           // Para manipular directorios
#include <QRegularExpression> // Para expresiones regulares
#include <QRegularExpressionMatch> // Para resultados de expresiones regulares
#include <QSet>           // Para almacenar URLs únicas y evitar duplicados
#include <QMessageBox>    // Para mostrar mensajes al usuario
#include <QFileInfo>      // Para obtener información de archivos (útil para nombres de archivo)
#include <QCryptographicHash> // Para generar nombres de archivo únicos (en caso de que no tengan extensión)

class HtmlParserGUI : public QWidget
{
    Q_OBJECT // Macro necesaria para que las señales y slots funcionen

public:
    // Constructor de la clase HtmlParserGUI
    explicit HtmlParserGUI(QWidget *parent = nullptr);
    // Destructor de la clase
    ~HtmlParserGUI();

private slots:
    // Slot que se ejecuta cuando se hace clic en el botón de descarga
    void on_downloadButton_clicked();
    // Slot que se ejecuta cuando se hace clic en el botón para buscar directorio
    void on_browseButton_clicked();
    // Slot que maneja la finalización de la descarga del HTML principal
    void on_htmlDownloadFinished(QNetworkReply *reply);
    // Slot que maneja la finalización de la descarga de cada recurso
    void on_resourceDownloadFinished(QNetworkReply *reply);

private:
    // Elementos de la interfaz de usuario
    QLineEdit *urlLineEdit;          // Campo para la URL del sitio
    QLineEdit *downloadDirLineEdit;  // Campo para el directorio de descarga
    QPushButton *browseButton;       // Botón para seleccionar directorio
    QPushButton *downloadButton;     // Botón para iniciar la descarga
    QTextEdit *logTextEdit;          // Área para mostrar el registro de actividad
    QLabel *statusLabel;             // Etiqueta para mostrar el estado actual

    // Gestores de red
    QNetworkAccessManager *networkManager;        // Para la descarga del HTML principal
    QNetworkAccessManager *resourceNetworkManager; // Para la descarga de recursos

    // Información del estado actual de la descarga
    QString baseUrl;            // URL base del sitio web que se está analizando
    QString currentDownloadDir; // Directorio donde se guardarán los archivos
    QSet<QUrl> discoveredUrls;  // Conjunto para guardar las URLs descubiertas (evita duplicados)
    int pendingDownloads;       // Contador de descargas de recursos pendientes

    // Métodos auxiliares
    // Parsea el contenido HTML en busca de URLs de recursos
    void parseHtmlForUrls(const QString &htmlContent);
    // Inicia la descarga de un recurso específico
    void downloadResource(const QUrl &url);
    // Extrae un nombre de archivo válido de una URL
    QString extractFileName(const QUrl &url);
};

#endif // HTMLPARSERGUI_H

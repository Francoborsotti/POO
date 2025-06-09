#include "htmlparsergui.h" // Incluye el archivo de cabecera de nuestra clase
#include <QDebug>          // Para mensajes de depuración (opcional)

// Constructor de la clase HtmlParserGUI
HtmlParserGUI::HtmlParserGUI(QWidget *parent)
    : QWidget(parent), // Llama al constructor de la clase base QWidget
    urlLineEdit(new QLineEdit("https://www.qt.io/", this)), // URL por defecto de ejemplo
    downloadDirLineEdit(new QLineEdit(QDir::homePath(), this)), // Directorio de inicio del usuario por defecto
    browseButton(new QPushButton("Seleccionar Directorio", this)),
    downloadButton(new QPushButton("Descargar Recursos", this)),
    logTextEdit(new QTextEdit(this)),
    statusLabel(new QLabel("Listo", this)),
    networkManager(new QNetworkAccessManager(this)), // Inicializa el gestor para el HTML
    resourceNetworkManager(new QNetworkAccessManager(this)), // Inicializa el gestor para los recursos
    pendingDownloads(0) // Inicializa el contador de descargas pendientes
{
    setWindowTitle("HTML Parser y Descargador de Recursos"); // Título de la ventana
    setMinimumSize(800, 600); // Tamaño mínimo de la ventana

    // --- Configuración de los Layouts (diseño de la interfaz) ---
    QVBoxLayout *mainLayout = new QVBoxLayout(this); // Layout principal vertical
    QHBoxLayout *urlLayout = new QHBoxLayout();      // Layout horizontal para la URL y el botón de descarga
    QHBoxLayout *downloadDirLayout = new QHBoxLayout(); // Layout horizontal para el directorio de descarga

    // --- Sección de Entrada de URL ---
    urlLayout->addWidget(new QLabel("URL del Sitio Web:", this)); // Etiqueta
    urlLayout->addWidget(urlLineEdit);                           // Campo de texto
    urlLayout->addWidget(downloadButton);                        // Botón de descarga

    // --- Sección de Directorio de Descarga ---
    downloadDirLayout->addWidget(new QLabel("Directorio de Descarga:", this)); // Etiqueta
    downloadDirLayout->addWidget(downloadDirLineEdit);                         // Campo de texto
    downloadDirLayout->addWidget(browseButton);                              // Botón para seleccionar directorio

    // --- Área de Registro (Log) ---
    logTextEdit->setReadOnly(true); // El área de log no es editable por el usuario

    // --- Ensamblaje del Layout Principal ---
    mainLayout->addLayout(urlLayout);           // Añade la sección de URL
    mainLayout->addLayout(downloadDirLayout);   // Añade la sección de directorio
    mainLayout->addWidget(new QLabel("Registro de Actividad:", this)); // Etiqueta para el log
    mainLayout->addWidget(logTextEdit);         // Añade el área de log
    mainLayout->addWidget(statusLabel);         // Añade la etiqueta de estado

    // --- Conexiones de Señales y Slots ---
    // Cuando se hace clic en el botón de descarga, se llama a on_downloadButton_clicked()
    connect(downloadButton, SIGNAL(clicked()), this, SLOT(on_downloadButton_clicked()));
    // Cuando se hace clic en el botón de buscar directorio, se llama a on_browseButton_clicked()
    connect(browseButton, SIGNAL(clicked()), this, SLOT(on_browseButton_clicked()));
    // Cuando el networkManager principal termina una descarga, se llama a on_htmlDownloadFinished()
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(on_htmlDownloadFinished(QNetworkReply*)));
    // Cuando el resourceNetworkManager termina una descarga, se llama a on_resourceDownloadFinished()
    connect(resourceNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(on_resourceDownloadFinished(QNetworkReply*)));
}

// Destructor de la clase
HtmlParserGUI::~HtmlParserGUI()
{
    // Los QObjects hijos (widgets, managers) son eliminados automáticamente por Qt
    // cuando su padre es destruido, por lo que no necesitamos delete manual aquí.
}

// Slot: Se ejecuta cuando se hace clic en el botón "Descargar Recursos"
void HtmlParserGUI::on_downloadButton_clicked()
{
    baseUrl = urlLineEdit->text();           // Obtiene la URL ingresada
    currentDownloadDir = downloadDirLineEdit->text(); // Obtiene el directorio de descarga

    // Validaciones básicas de entrada
    if (baseUrl.isEmpty() || currentDownloadDir.isEmpty()) {
        QMessageBox::warning(this, "Error", "Por favor, ingrese una URL y seleccione un directorio de descarga.");
        return; // Sale de la función si los campos están vacíos
    }

    // Verifica y/o crea el directorio de descarga
    QDir dir(currentDownloadDir);
    if (!dir.exists()) { // Si el directorio no existe
        if (!dir.mkpath(".")) { // Intenta crearlo ( "." significa el directorio actual de "dir" )
            QMessageBox::critical(this, "Error", "No se pudo crear el directorio de descarga: " + currentDownloadDir);
            return; // Sale de la función si no se puede crear
        }
    }

    logTextEdit->clear(); // Limpia el log anterior
    logTextEdit->append("Iniciando descarga de: " + baseUrl); // Mensaje en el log
    statusLabel->setText("Descargando HTML..."); // Actualiza el estado
    downloadButton->setEnabled(false); // Deshabilita el botón para evitar clics múltiples

    // Limpia el conjunto de URLs descubiertas y reinicia el contador de descargas pendientes
    discoveredUrls.clear();
    pendingDownloads = 0;

    // Inicia la descarga del HTML principal, envolviendo la QUrl en QNetworkRequest
    networkManager->get(QNetworkRequest(QUrl(baseUrl)));
}

// Slot: Se ejecuta cuando se hace clic en el botón "Seleccionar Directorio"
void HtmlParserGUI::on_browseButton_clicked()
{
    // Abre un diálogo para que el usuario seleccione una carpeta existente
    QString dir = QFileDialog::getExistingDirectory(this, "Seleccionar Directorio de Descarga", QDir::homePath());
    if (!dir.isEmpty()) { // Si el usuario seleccionó un directorio (no canceló)
        downloadDirLineEdit->setText(dir); // Actualiza el campo de texto con la ruta seleccionada
    }
}

// Slot: Se ejecuta cuando la descarga del HTML principal finaliza
void HtmlParserGUI::on_htmlDownloadFinished(QNetworkReply *reply)
{
    // Verifica si hubo un error de red durante la descarga
    if (reply->error() != QNetworkReply::NoError) {
        logTextEdit->append("Error al descargar HTML: " + reply->errorString());
        statusLabel->setText("Error");
        downloadButton->setEnabled(true); // Vuelve a habilitar el botón
        reply->deleteLater(); // Libera la memoria del QNetworkReply
        return; // Sale de la función
    }

    logTextEdit->append("HTML descargado. Analizando...");
    statusLabel->setText("Analizando HTML...");

    QString htmlContent = reply->readAll(); // Lee todo el contenido HTML de la respuesta
    parseHtmlForUrls(htmlContent);          // Llama a la función para analizar el HTML

    reply->deleteLater(); // Libera la memoria del QNetworkReply

    // Si no se encontraron recursos adicionales, la descarga está completa
    if (pendingDownloads == 0) {
        statusLabel->setText("Descarga completa. No se encontraron recursos adicionales.");
        downloadButton->setEnabled(true); // Habilita el botón
        QMessageBox::information(this, "Descarga Completada", "El HTML fue descargado y no se encontraron recursos adicionales.");
    } else {
        statusLabel->setText(QString("Descargando %1 recursos...").arg(pendingDownloads)); // Muestra cuántos recursos se están descargando
    }
}

// Función: Analiza el contenido HTML para encontrar URLs de recursos
void HtmlParserGUI::parseHtmlForUrls(const QString &htmlContent)
{
    // Expresión regular para encontrar URLs en atributos 'src' o 'href'.
    // Captura el contenido dentro de las comillas después de src= o href=
    // Ej: <img src="image.png">, <link href="/style.css">, <a href="page.html">
    QRegularExpression srcHrefRegex("(?:src|href)=\"([^\"]+)\"");
    QRegularExpressionMatchIterator i = srcHrefRegex.globalMatch(htmlContent);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString urlCandidate = match.captured(1); // Obtiene la URL capturada
        // Resuelve la URL candidata respecto a la URL base del sitio
        // Esto convierte URLs relativas (ej. /css/style.css) en absolutas
        QUrl url = QUrl(baseUrl).resolved(QUrl(urlCandidate));
        // Verifica si la URL es válida y si no ha sido descubierta antes
        if (url.isValid() && !discoveredUrls.contains(url)) {
            discoveredUrls.insert(url); // Agrega la URL al conjunto de descubiertas
            logTextEdit->append("URL encontrada: " + url.toString());
            downloadResource(url); // Inicia la descarga del recurso
        }
    }

    // Expresión regular para encontrar URLs dentro de url(...) en CSS (inline o en etiquetas <style>)
    // Captura el contenido entre paréntesis después de url(
    // Ej: background-image: url('image.jpg');
    QRegularExpression urlInCssRegex("url\\(['\"]?([^'\")]+)['\"]?\\)");
    i = urlInCssRegex.globalMatch(htmlContent);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString urlCandidate = match.captured(1); // Obtiene la URL capturada
        QUrl url = QUrl(baseUrl).resolved(QUrl(urlCandidate)); // Resuelve la URL
        if (url.isValid() && !discoveredUrls.contains(url)) {
            discoveredUrls.insert(url); // Agrega la URL al conjunto de descubiertas
            logTextEdit->append("URL encontrada (CSS): " + url.toString());
            downloadResource(url); // Inicia la descarga del recurso
        }
    }

    // Nota: Un parser HTML robusto podría requerir una biblioteca dedicada (como un parser DOM)
    // para manejar todos los casos posibles (HTML mal formado, URLs generadas por JS, etc.).
    // Las expresiones regulares cubren los casos más comunes y directos.
}

// Función: Inicia la descarga de un recurso
void HtmlParserGUI::downloadResource(const QUrl &url)
{
    // Solo descargamos URLs que sean HTTP/HTTPS y que no sean la URL base del sitio
    if (url.scheme().startsWith("http") && url != QUrl(baseUrl)) {
        pendingDownloads++; // Incrementa el contador de descargas pendientes
        // Inicia la descarga del recurso, envolviendo la QUrl en QNetworkRequest
        resourceNetworkManager->get(QNetworkRequest(url));
        statusLabel->setText(QString("Descargando %1 recursos...").arg(pendingDownloads)); // Actualiza el estado
    } else {
        logTextEdit->append("Ignorando URL (no es un recurso descargable o es la URL base): " + url.toString());
    }
}

// Slot: Se ejecuta cuando la descarga de un recurso individual finaliza
void HtmlParserGUI::on_resourceDownloadFinished(QNetworkReply *reply)
{
    pendingDownloads--; // Decrementa el contador de descargas pendientes
    statusLabel->setText(QString("Descargando %1 recursos restantes...").arg(pendingDownloads)); // Actualiza el estado

    // Verifica si hubo un error de red al descargar el recurso
    if (reply->error() != QNetworkReply::NoError) {
        logTextEdit->append("Error al descargar recurso " + reply->url().toString() + ": " + reply->errorString());
        reply->deleteLater(); // Libera la memoria
        return; // Sale de la función
    }

    QString fileName = extractFileName(reply->url()); // Obtiene un nombre de archivo para el recurso
    // Construye la ruta completa donde se guardará el archivo
    QString filePath = QDir(currentDownloadDir).filePath(fileName);

    QFile file(filePath); // Crea un objeto QFile para el archivo
    if (!file.open(QIODevice::WriteOnly)) { // Intenta abrir el archivo en modo escritura
        logTextEdit->append("Error: No se pudo guardar el archivo " + filePath + ": " + file.errorString());
        reply->deleteLater(); // Libera la memoria
        return; // Sale de la función
    }

    file.write(reply->readAll()); // Escribe todo el contenido descargado en el archivo
    file.close(); // Cierra el archivo

    logTextEdit->append("Recurso descargado y guardado: " + filePath);
    reply->deleteLater(); // Libera la memoria del QNetworkReply

    // Si no quedan descargas pendientes, la operación ha finalizado
    if (pendingDownloads == 0) {
        statusLabel->setText("¡Descarga de recursos completada!");
        downloadButton->setEnabled(true); // Vuelve a habilitar el botón de descarga
        QMessageBox::information(this, "Descarga Completada", "Todos los recursos han sido descargados.");
    }
}

// Función: Extrae un nombre de archivo de una URL
QString HtmlParserGUI::extractFileName(const QUrl &url)
{
    QString path = url.path(); // Obtiene la parte de la ruta de la URL
    QFileInfo fileInfo(path);  // Crea un objeto QFileInfo para analizar la ruta
    QString fileName = fileInfo.fileName(); // Obtiene el nombre del archivo (con extensión)

    // Si la URL no termina en un nombre de archivo obvio (ej. "https://example.com/images/"),
    // generamos un nombre de archivo genérico usando un hash MD5 de la URL completa.
    // Esto evita que se sobrescriban archivos y da un nombre único.
    if (fileName.isEmpty()) {
        fileName = QString("resource_%1").arg(QCryptographicHash::hash(url.toString().toUtf8(), QCryptographicHash::Md5).toHex());
        // Podríamos intentar inferir la extensión basándonos en el Content-Type del reply,
        // pero para este ejercicio, el hash es suficiente.
    }
    return fileName;
}

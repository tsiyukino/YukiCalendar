#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QDebug>
#include <QQuickStyle>

// Services
#include "services/EventService.h"
#include "services/EventTypeService.h"
#include "services/ModuleService.h"
#include "services/ActionTreeScriptService.h"
#include "services/ActionExecutionService.h"

// Modules
#include "modules/StartActionModule.h"
#include "modules/ReminderModule.h"
#include "modules/ApiInputModule.h"
#include "modules/VariableModule.h"

// ViewModels
#include "viewmodels/CalendarViewModel.h"
#include "viewmodels/ModulesViewModel.h"
#include "viewmodels/TypesViewModel.h"

// Testing
#include "testing/TestRunner.h"

int main(int argc, char *argv[])
{
    // Force Material style BEFORE creating QApplication
    QQuickStyle::setStyle("Material");

    QApplication app(argc, argv);

    // Set application info
    app.setOrganizationName("YukiCalendar");
    app.setOrganizationDomain("yukicalendar.com");
    app.setApplicationName("YukiCalendar");
    app.setApplicationVersion("1.0.0");

    // Set application icon
    QIcon appIcon(":/icons/app-icon.ico");
    qDebug() << "App icon null?" << appIcon.isNull();
    qDebug() << "App icon sizes:" << appIcon.availableSizes();
    app.setWindowIcon(appIcon);

    // Create services
    auto eventService = new EventService(&app);
    auto eventTypeService = new EventTypeService(&app);
    auto moduleService = new ModuleService(&app);
    auto scriptService = new ActionTreeScriptService(&app);
    auto executionService = new ActionExecutionService(moduleService, eventService, &app);

    // Register modules
    moduleService->registerModule(new StartActionModule(moduleService));
    moduleService->registerModule(new ReminderModule(moduleService));
    moduleService->registerModule(new ApiInputModule(moduleService));
    moduleService->registerModule(new VariableModule(moduleService));

    // Start execution service
    executionService->start();

    // Create view models
    auto calendarVM = new CalendarViewModel(eventService, eventTypeService, &app);
    auto modulesVM = new ModulesViewModel(moduleService, &app);
    auto typesVM = new TypesViewModel(eventTypeService, &app);
    auto testRunner = new TestRunner(eventService, moduleService, &app);

    // Create QML engine
    QQmlApplicationEngine engine;

    // Set context properties
    engine.rootContext()->setContextProperty("calendarViewModel", calendarVM);
    engine.rootContext()->setContextProperty("modulesViewModel", modulesVM);
    engine.rootContext()->setContextProperty("typesViewModel", typesVM);
    engine.rootContext()->setContextProperty("testRunner", testRunner);

    // Load main QML file
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

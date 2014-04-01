#include <QtWidgets>
#include <QString>

namespace patcher
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT
        public:
            MainWindow(const QString& title="");
    };
}

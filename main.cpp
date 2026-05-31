#include <QApplication>
#include <QMainWindow>
#include <QSplitter>
#include <QTreeView>
#include <QFileSystemModel>
#include <QTabBar>
#include <QStackedWidget>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QProcess>
#include <QVBoxLayout>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <queue>
#include <fstream>
#include <iostream>
using ll = long long;
QString fullpath;
class MainWindow : public QMainWindow 
{
public:
    MainWindow() 
    {
        resize(1000, 700);
        //--------------EDITOR------------
        tabBar = new QTabBar();
        editors = new QStackedWidget();

        auto *editorContainer = new QWidget();
        auto *layout = new QVBoxLayout(editorContainer);
        layout->setContentsMargins(0,0,0,0);
        layout->addWidget(tabBar);
        layout->addWidget(editors);
        //---------------SPLITTERS-----------
        auto *rightSplit = new QSplitter(Qt::Vertical);
        rightSplit->addWidget(editorContainer);
        rightSplit->setSizes({600, 150});
        rightSplit->setStretchFactor(0, 4);
        rightSplit->setStretchFactor(1, 1);

        auto *mainSplit = new QSplitter(Qt::Horizontal);
        mainSplit->addWidget(rightSplit);
        mainSplit->setStretchFactor(1, 1);

        setCentralWidget(mainSplit);

        //------------SIGNALS------------
        connect(tabBar, &QTabBar::currentChanged, this, [&](int i)
        {
            editors->setCurrentIndex(i);
        });
        createTab("unsaved");
        //--------kyes--------
        auto *saveAction = new QAction(this);
        saveAction->setShortcut(QKeySequence("Ctrl+S"));
        connect(saveAction, &QAction::triggered, this, [&]() 
        {
            saveFile();
            QString fname = "";
            for (ll i=0; i<fullpath.size(); i++)
            {
                if (fullpath[i]=='/')
                {
                    fname="";
                }
                else
                {
                    fname+=fullpath[i];
                }
            }
            if (fname=="")
            {
                fname="unsaved";
            }
            tabBar->setTabText(tabBar->currentIndex(), fname);
        });
        this->addAction(saveAction);

        auto *openf = new QAction(this);
        openf->setShortcut(QKeySequence("Ctrl+O"));
        connect(openf, &QAction::triggered, this, [&]() 
        {
            openfile();
        });
        this->addAction(openf);
    }

private:
    QTabBar *tabBar;
    QStackedWidget *editors;

    void createTab(const QString &name) 
    {
        auto *edit = new QPlainTextEdit();
        edit->setPlainText("");

        int index = editors->addWidget(edit);
        tabBar->addTab(name);

        tabBar->setCurrentIndex(index);
        editors->setCurrentIndex(index);
    }

    void saveFile() 
    {
        auto *editor = qobject_cast<QPlainTextEdit*>(editors->currentWidget());
        if (!editor) 
        {
            return;
        }
        QString text = editor->toPlainText();
        if (fullpath.isEmpty()) 
        {
            fullpath = QFileDialog::getSaveFileName(this, "Save File");
            if (fullpath.isEmpty()) 
            return;
        }
        QFile file(fullpath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) 
        {
            QTextStream out(&file);
            out << text;
            file.close();
        }
    }
    void openfile()
    {
        auto *editor = qobject_cast<QPlainTextEdit*>(editors->currentWidget());
        if (!editor)
        {
            return;
        }
        QString t = editor->toPlainText();
        auto ofp = QFileDialog::getOpenFileName(this,QDir::homePath());
        if (ofp.isEmpty())
        {
            return;
        }
        QFile file(ofp);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            QString content = in.readAll();
            file.close();

            editor->setPlainText(content);
        }
        QString fname = "";
        for (ll i=0; i<ofp.size(); i++)
        {
            if (ofp[i]=='/')
            {
                fname="";
            }
            else
            {
                fname+=ofp[i];
            }
        }
        if (fname=="")
        {
            fname="unsaved";
        }
        tabBar->setTabText(tabBar->currentIndex(), fname);
    }
};
int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}

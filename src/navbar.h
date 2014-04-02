#ifndef NAVBAR_H
#define NAVBAR_H

#include <QLabel>
#include <QStackedWidget>
#include <QToolBar>
#include <QList>
#include <QActionGroup>
#include <QMenu>
#include "navbarpage.h"
#include "navbarsplitter.h"
#include "navbarpagelistwidget.h"

class NavBarHeader: public QLabel
{
    Q_OBJECT

public:
    explicit NavBarHeader(QWidget *parent = 0, Qt::WindowFlags f = 0);
    explicit NavBarHeader(const QString & text, QWidget *parent = 0, Qt::WindowFlags f = 0);
};

class NavBarToolBar: public QToolBar
{
    Q_OBJECT

public:
    explicit NavBarToolBar(QWidget *parent = 0);
};

class NavBar : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(int   count           READ count)
    Q_PROPERTY(int   currentIndex    READ currentIndex    WRITE setCurrentIndex NOTIFY currentChanged)
    Q_PROPERTY(int   rowHeight       READ rowHeight       WRITE setRowHeight)
    Q_PROPERTY(bool  showHeader      READ showHeader      WRITE setShowHeader)
    Q_PROPERTY(bool  showOptionsMenu READ showOptionsMenu WRITE setShowOptionsMenu)
    Q_PROPERTY(int   visibleRows     READ visibleRows     WRITE setVisibleRows  NOTIFY visibleRowsChanged)
    Q_PROPERTY(QSize smallIconSize   READ smallIconSize   WRITE setSmallIconSize)
    Q_PROPERTY(QSize largeIconSize   READ largeIconSize   WRITE setLargeIconSize)

public:
    explicit NavBar(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~NavBar();

    int      addPage(QWidget *page);
    int      addPage(QWidget *page, const QString &text);
    int      addPage(QWidget *page, const QString &text, const QIcon &icon);
    int      insertPage(int index, QWidget *page);
    int      insertPage(int index, QWidget *page, const QString &text);
    int      insertPage(int index, QWidget *page, const QString &text, const QIcon &icon);

    void     removePage(int index);

    void     setPageText(int index, const QString &text);
    QString  pageText(int index) const;

    void     setPageIcon(int index, const QIcon &icon);
    QIcon    pageIcon(int index) const;

    void     setPageEnabled(int index, bool enabled);
    bool     isPageEnabled(int index);

    void     setPageVisible(int index, bool visible);
    bool     isPageVisible(int index);

    int      currentIndex() const;
    QWidget *currentWidget() const;
    QWidget *widget(int index) const;
    int      indexOf(QWidget *widget) const;
    int      count() const;

    void     setSmallIconSize(const QSize &size);
    QSize    smallIconSize() const;

    void     setLargeIconSize(const QSize &size);
    QSize    largeIconSize() const;

    int      rowHeight() const;
    bool     showHeader() const;
    bool     showOptionsMenu() const;
    int      visibleRows() const;

    QSize    sizeHint() const;

    static QString loadStyle(const QString &filename);

signals:
    void currentChanged(int index);
    void visibleRowsChanged(int rows);

public slots:
    void setCurrentIndex(int index);
    void setCurrentWidget(QWidget *widget);
    void setRowHeight(int height);
    void setShowHeader(bool show);
    void setShowOptionsMenu(bool show);
    void setVisibleRows(int rows);
    int  showOptionsDialog();

protected:
    void resizeEvent(QResizeEvent *e);

private slots:
    void onClickPageButton(QAction *action);
    void onButtonVisibilityChanged(int visCount);
    void changePageVisibility(QAction *action);

private:
    int  createPage(int index, QWidget *page, const QString &text, const QIcon &icon);
    void resizeContent(const QSize &size, int rowheight);
    void recalcPageList();
    void refillToolBar(int visCount);
    void refillPagesMenu();

    QList<NavBarPage> visiblePages();

    NavBarHeader         *header;
    QStackedWidget       *stackedWidget;
    NavBarSplitter       *splitter;
    NavBarPageListWidget *pageListWidget;
    NavBarToolBar        *pageToolBar;
    QActionGroup         *actionGroup;
    QMenu                *pagesMenu;
    QAction              *actionOptions;
    QList<NavBarPage>     pages;
    QStringList           pageOrder;

    bool  optMenuVisible;
    bool  headerVisible;
    int   headerHeight;
    QSize pageIconSize;
    int   uniquePageCount;

    friend class NavBarPageListWidget;
};

#endif // NAVBAR_H

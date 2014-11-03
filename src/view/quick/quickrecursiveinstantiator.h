#ifndef QUICKRECURSIVEINSTANTIATOR
#define QUICKRECURSIVEINSTANTIATOR

#include <QQuickItem>

class QAbstractItemModel;

class QuickRecursiveInstantiator : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel* model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QQmlComponent *delegate READ delegate WRITE setDelegate NOTIFY delegateChanged)
    Q_CLASSINFO("DefaultProperty", "delegate")

public:
    QuickRecursiveInstantiator(QQuickItem* parent = 0);

    QAbstractItemModel* model() const;
    virtual void setModel(QAbstractItemModel* model);

    QQmlComponent* delegate() const;
    void setDelegate(QQmlComponent* delegate);

    QList<QObject*> rootItems() const;

private Q_SLOTS:
    void modelReset();
    void rowsInserted(const QModelIndex& parent, int row, int column);

Q_SIGNALS:
    void modelChanged(QAbstractItemModel* model);
    void delegateChanged(QQmlComponent* delegate);

private:
    QObject* createItems(const QModelIndex& index, QObject* parent);

    QQmlContext* m_currentContext;
    QAbstractItemModel* m_model;
    QQmlComponent* m_delegate;
    QList<QObject*> m_rootItems;
};

#endif

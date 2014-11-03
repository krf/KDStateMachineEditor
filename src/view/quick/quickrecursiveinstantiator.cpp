#include "quickrecursiveinstantiator.h"

#include "layoutitem.h"
#include "layoutitemmodel.h"

#include <QAbstractItemModel>
#include <QDebug>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickItem>

using namespace KDSME;

QuickRecursiveInstantiator::QuickRecursiveInstantiator(QQuickItem* parent)
    : QQuickItem(parent)
    , m_model(nullptr)
    , m_delegate(nullptr)
{
}

QList< QObject* > QuickRecursiveInstantiator::rootItems() const
{
    return m_rootItems;
}

QAbstractItemModel* QuickRecursiveInstantiator::model() const
{
    return m_model;
}

void QuickRecursiveInstantiator::setModel(QAbstractItemModel* model)
{
    if (m_model == model) {
        return;
    }

    m_model = model;

    connect(m_model, &QAbstractItemModel::modelReset, this, &QuickRecursiveInstantiator::modelReset);
    connect(m_model, &QAbstractItemModel::rowsInserted, this, &QuickRecursiveInstantiator::rowsInserted);
    emit modelChanged(m_model);
}

QQmlComponent* QuickRecursiveInstantiator::delegate() const
{
    return m_delegate;
}

void QuickRecursiveInstantiator::setDelegate(QQmlComponent* delegate)
{
    if (m_delegate == delegate) {
        return;
    }

    m_delegate = delegate;
    emit delegateChanged(m_delegate);
}

void QuickRecursiveInstantiator::modelReset()
{
    m_rootItems.clear();

    m_currentContext = QQmlEngine::contextForObject(this);
    for (int i = 0; i < m_model->rowCount(); ++i) {
        auto rootIndex = m_model->index(0, 0);
        m_rootItems << createItems(rootIndex, this);
    }

    //m_rootItems[0]->dumpObjectTree();
}

QObject* QuickRecursiveInstantiator::createItems(const QModelIndex& index, QObject* parent)
{
    if (!m_delegate || !index.isValid()) {
        return nullptr;
    }

    auto obj = index.data(LayoutItemModel::ObjectRole).value<QObject*>();
    auto context = new QQmlContext(m_currentContext);
    context->setContextProperty("object", obj);

    /*
    qDebug() << "Creating component for item" << obj;
    QQmlComponent component(m_currentContext->engine());
    component.setData(
        "import QtQuick 2.0\n"
        "import \"qrc:///kdsme/qml/uml/\"\n"
        "UmlFinalState { width: 100; height: 100; Text { text: object.label } }",
        QUrl()
    );
    if (component.isError()) {
        qDebug() << "Error:" << component.errorString();
    }
    */

    auto createdObject = m_delegate->create(context);
    createdObject->setParent(parent);
    if (auto quickItem = qobject_cast<QQuickItem*>(createdObject)) {
        quickItem->setParentItem(this);
    }

    // create items for child indices recursively
    for (int i = 0; i < m_model->rowCount(index); ++i) {
        auto childIndex = m_model->index(i, 0, index);
        createItems(childIndex, createdObject);
    }

    return createdObject;
}

void QuickRecursiveInstantiator::rowsInserted(const QModelIndex& parent, int row, int column)
{
    qDebug() << "INSERT" << row << column;

    auto engine = QQmlEngine::contextForObject(this)->engine();
    Q_ASSERT(engine);
}



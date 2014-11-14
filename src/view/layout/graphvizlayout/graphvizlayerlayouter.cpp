/*
  graphvizlayerlayouter.cpp

  This file is part of the KDAB State Machine Editor Library.

  Copyright (C) 2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com.
  All rights reserved.
  Author: Kevin Funk <kevin.funk@kdab.com>

  Licensees holding valid commercial KDAB State Machine Editor Library
  licenses may use this file in accordance with the KDAB State Machine Editor
  Library License Agreement provided with the Software.

  This file may be distributed and/or modified under the terms of the
  GNU Lesser General Public License version 2.1 as published by the
  Free Software Foundation and appearing in the file LICENSE.LGPL.txt included.

  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

  Contact info@kdab.com if any conditions of this licensing are not
  clear to you.
*/

#include "graphvizlayerlayouter.h"

#include "graphvizlayouterbackend.h"
#include "element.h"
#include "layoutitem.h"
#include "view.h"

#include <QDebug>
#include <QRectF>

using namespace KDSME;

GraphvizLayerLayouter::GraphvizLayerLayouter(QObject* parent)
    : Layouter(parent)
    , m_backend(new GraphvizLayouterBackend)
{
    // TODO: Get rid off this enum and just provide appropriate methods in the backend
    m_backend->setLayoutMode(GraphvizLayouterBackend::NonRecursiveMode);
}

GraphvizLayerLayouter::~GraphvizLayerLayouter()
{
    delete m_backend;
}

QRectF GraphvizLayerLayouter::layout(StateLayoutItem* state, View* view)
{
    Q_ASSERT(state);
    Q_ASSERT(view);

    // open context
    //const QString id = state->label();
    m_backend->openContext();

    const QList<StateLayoutItem*> childStates = state->childStates();

    // Step 1: Create Graphviz structures out of the State/Transition tree
    // Step 1.1: build nodes
    foreach (StateLayoutItem* state, childStates) {
        m_backend->buildState(state);
    }
    // Step 1.2: build edges
    foreach (StateLayoutItem* state, childStates) {
        foreach (TransitionLayoutItem* transition, state->transitions()) {
            // TODO: What to do with transitions crossing hierarchies?
            if (!childStates.contains(transition->targetState())) {
                continue; // ignore for now
            }
            m_backend->buildTransition(transition);
        }
    }

    m_backend->layout();

    // Step 2: Import the information from the Graphviz structures to the State/Transition tree
    m_backend->import();

    const QRectF boundingRect = m_backend->boundingRect();

#if 0
    //  Debugging
    const QString machineName = (qobject_cast<State*>(state->element())->machine() ? qobject_cast<State*>(state->element())->machine()->label() : state->element()->label());
    const QString fileName = QString("/tmp/gvgraph_%1_%2.png").arg(machineName).arg(state->element()->label());
    m_backend->saveToFile(fileName);
#endif

    m_backend->closeContext();
    return boundingRect;
}
